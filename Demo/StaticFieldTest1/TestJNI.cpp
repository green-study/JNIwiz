#include "jni_test_instrumented.h"
#include <stdio.h>
#include "TestJNI.h"

using namespace std;


JNIEXPORT jobject JNICALL Java_TestJNI_getIntegerObject
          (JNIEnv *env, jobject thisObj, jint number) {
   printf("[C++] StaticFieldTest1\n");
   jclass cls = env->FindClass("TestJNI");
   jfieldID jm = env->GetStaticFieldID(cls,"wrong_static_field","[I");
   printf("[C++] Finished transferring wrong static field to argument.\n");
   printf("[C++] C++ file is still alive.\n");
   return NULL;
}
