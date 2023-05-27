#include "jni_test_instrumented.h"
#include <stdio.h>
#include "TestJNIConstructor.h"

using namespace std;


JNIEXPORT jobject JNICALL Java_TestJNIConstructor_getIntegerObject
          (JNIEnv *env, jobject thisObj, jint number) {
   // Get a class reference for java.lang.Integer
   jclass cls = env->FindClass("TestJNIConstructor"); // The prefix L is not allowed
   // Get the Method ID of the constructor which takes an int
   //jobject nlf = env->NewLocalRef(NULL);
   jmethodID midInit = env->GetStaticMethodID(cls, "<init>", "()V");
   //if (NULL == midInit) return NULL;
   //jmethodID midClinit = env->GetStaticMethodID(cls, "<clinit>", "()V"); // The prefix L is required
   //if (NULL == midToString) return NULL;
   printf("I'm still running");

   //May need to call releaseStringUTFChars() before return
   return NULL;
}