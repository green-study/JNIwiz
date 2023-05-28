#include "jni_test_instrumented.h"
#include <stdio.h>
#include "TestJNI.h"

using namespace std;


JNIEXPORT jobject JNICALL Java_TestJNI_getIntegerObject
          (JNIEnv *env, jobject thisObj, jint number) {
   printf("[C++] NullTest\n");
   jclass cls = env->FindClass("TestJNI"); 
   jobject nlf = env->NewLocalRef(NULL);
   printf("[C++] Finished transferring NULL to argument.\n");
   printf("[C++] C++ file is still alive.\n");

   return NULL;
}
