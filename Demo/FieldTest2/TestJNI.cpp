#include "jni_test_instrumented.h"
#include <stdio.h>
#include "TestJNI.h"

using namespace std;


JNIEXPORT jobject JNICALL Java_TestJNI_getIntegerObject
          (JNIEnv *env, jobject thisObj, jint number) {
   printf("[C++] FieldTest2\n");
   jclass cls = env->FindClass("TestJNI");
   jfieldID jm = env->GetFieldID(cls,"wrong_field","[I");
   env->ExceptionClear();
   printf("[C++] Finished transferring wrong field to argument.\n");
   printf("[C++] C++ file is still alive.\n");
   return NULL;
}
