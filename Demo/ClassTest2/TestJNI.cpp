#include "jni_test_instrumented.h"
#include <stdio.h>
#include "TestJNI.h"

using namespace std;


JNIEXPORT jobject JNICALL Java_TestJNI_getIntegerObject
          (JNIEnv *env, jobject thisObj, jint number) {
   printf("[C++] ClassTest2\n");
   jclass cls = env->FindClass("TestJNIwrong");
   env->ExceptionClear();
   printf("[C++] Finished transferring Wrong Class Name to argument.\n");
   printf("[C++] C++ file is still alive.\n");
   return NULL;
}
