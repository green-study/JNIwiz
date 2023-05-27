#include "jni_test_instrumented.h"
#include <stdio.h>
#include "TestJNIField.h"

using namespace std;


JNIEXPORT jobject JNICALL Java_TestJNIField_getIntegerObject
          (JNIEnv *env, jobject thisObj, jint number) {
   // Get a class reference for java.lang.Integer
   jclass cls = env->FindClass("TestJNIField"); // The prefix L is not allowed
   jmethodID myMethodId = env->GetMethodID(cls, "<init>", "()V");
   jfieldID jf = env->GetFieldID(cls,"x","I");
   printf("hello! I'm still running");
   int num = 999;
   jobject myObject = env->NewObject(cls, myMethodId, num);
   return myObject;
}
