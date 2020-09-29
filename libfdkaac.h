#include <jni.h>

JNIEXPORT void JNICALL Java_com_github_serezhka_fdkaacjni_FdkAacLib_init();

JNIEXPORT void JNICALL Java_com_github_serezhka_fdkaacjni_FdkAacLib_decodeFrame
        (JNIEnv *env, jobject object, jbyteArray input, jbyteArray output);
