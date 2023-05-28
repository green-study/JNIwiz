#include "jni_test_instrumented.h"
#include <stdio.h>
#include "TestJNI.h"

using namespace std;


JNIEXPORT jobject JNICALL Java_TestJNI_getIntegerObject
          (JNIEnv *env, jobject thisObj, jint number) {
   printf("[C++] StaticMethodTest1\n");
   jclass cls = env->FindClass("TestJNI");
   jmethodID jm = env->GetStaticMethodID(cls,"wrong_static_method","(II)V");
   printf("[C++] Finished transferring wrong static method to argument.\n");
   printf("[C++] C++ file is still alive.\n");
   return NULL;
}
