#include "jni_test_instrumented.h"
#include <stdio.h>
#include "TestJNINull.h"

using namespace std;


JNIEXPORT jobject JNICALL Java_TestJNIField_gettingIntegerObject
          (JNIEnv *env, jobject thisObj, jint number) {
   // Get a class reference for java.lang.Integer
   jclass cls = env->FindClass("TestJNINull"); // The prefix L is not allowed
   jmethodID myMethodId = env->GetMethodID(cls, "<init>", "()V");
   jfieldID jf = env->GetFieldID(cls,"n","I");
   jobject nlf = env->NewLocalRef(NULL);
   printf("hello! I'm still running");
   int num = 999;
   jobject myObject = env->NewObject(cls, myMethodId, num);
   return myObject;
}
