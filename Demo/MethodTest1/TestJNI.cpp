#include "jni_test_instrumented.h"
#include <stdio.h>
#include "TestJNI.h"

using namespace std;


JNIEXPORT jobject JNICALL Java_TestJNI_getIntegerObject
          (JNIEnv *env, jobject thisObj, jint number) {
   printf("[C++] MethodTest1\n");
   jclass cls = env->FindClass("TestJNI"); 
   jmethodID jm = env->GetMethodID(cls,"wrong_method","()V");
   printf("[C++] Finished transferring wrong method to argument.\n");
   printf("[C++] C++ file is still alive.\n");

   return NULL;
}
