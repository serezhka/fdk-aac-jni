#include <jni.h>

JNIEXPORT void JNICALL Java_com_github_serezhka_jap2server_internal_handler_audio_AudioHandler_init();

JNIEXPORT void JNICALL Java_com_github_serezhka_jap2server_internal_handler_audio_AudioHandler_decodeFrame
        (JNIEnv *env, jobject object, jbyteArray input, jbyteArray output);
