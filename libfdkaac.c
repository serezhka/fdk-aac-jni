#include "libfdkaac.h"

#include "aacdecoder_lib.h"
#include <jni.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

HANDLE_AACDECODER aac_decoder;

unsigned char *as_unsigned_char_array(JNIEnv *env, jbyteArray array) {
    int num_bytes = (*env)->GetArrayLength(env, array);
    unsigned char *buffer;
    buffer = (unsigned char *) malloc(num_bytes);
    jbyte *lib = (*env)->GetByteArrayElements(env, array, 0);
    memcpy(buffer, lib, num_bytes);
    return buffer;
}

JNIEXPORT void JNICALL Java_com_github_serezhka_fdkaacjni_FdkAacLib_init() {
    unsigned char *tmp = (unsigned char *) malloc(16);
    fprintf(stderr, "[libfdk-aac]: Init %s\n", tmp);

    aac_decoder = aacDecoder_Open(TT_MP4_RAW, 1);
    if (aac_decoder == NULL) {
        fprintf(stderr, "[libfdk-aac]: aacDecoder_Open failed\n");
        return;
    }
    fprintf(stderr, "[libfdk-aac]: AAC decoder initialized\n");

    /* ASC config binary data */
    UCHAR eld_conf[] = {0xF8, 0xE8, 0x50, 0x00};
    UCHAR *conf[] = {eld_conf};

    static UINT conf_len = sizeof(eld_conf);
    int ret = aacDecoder_ConfigRaw(aac_decoder, conf, &conf_len);
    if (ret != AAC_DEC_OK) {
        fprintf(stderr, "[libfdk-aac]: aacDecoder_ConfigRaw failed\n");
        return;
    }
    CStreamInfo *aac_stream_info = aacDecoder_GetStreamInfo(aac_decoder);
    if (aac_stream_info == NULL) {
        fprintf(stderr, "[libfdk-aac]: aacDecoder_GetStreamInfo failed\n");
        return;
    }
    fprintf(stderr,
            "[libfdk-aac]: stream info: channel = %d\tsample_rate = %d\tframe_size = %d\taot = %d\tbitrate = %d\n",
            aac_stream_info->channelConfig, aac_stream_info->aacSampleRate,
            aac_stream_info->aacSamplesPerFrame, aac_stream_info->aot, aac_stream_info->bitRate);

    fflush(stderr);
}

JNIEXPORT void JNICALL Java_com_github_serezhka_fdkaacjni_FdkAacLib_decodeFrame
        (JNIEnv *env, jobject object, jbyteArray input, jbyteArray output) {

    int input_size = (*env)->GetArrayLength(env, input);
    unsigned char *input_buf = as_unsigned_char_array(env, input);

    int ret = 0;
    UCHAR *p_buffer[1] = {input_buf};
    UINT buffer_size = input_size;
    UINT bytes_valid = input_size;
    ret = aacDecoder_Fill(aac_decoder, p_buffer, &buffer_size, &bytes_valid);
    if (ret != AAC_DEC_OK) {
        fprintf(stderr, "[libfdk-aac]: aacDecoder_Fill error : %x", ret);
        return;
    }
    INT time_data_size = 4 * 480;
    INT_PCM *p_time_data = malloc(time_data_size);
    ret = aacDecoder_DecodeFrame(aac_decoder, p_time_data, time_data_size, 0);
    if (ret != AAC_DEC_OK) {
        fprintf(stderr, "[libfdk-aac]: aacDecoder_DecodeFrame error : 0x%x", ret);
    }

    (*env)->SetByteArrayRegion(env, output, 0, time_data_size, (jbyte *) p_time_data);

    fflush(stderr);
}
