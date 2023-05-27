#include "jni_test_instrumented.h"
#include <stdio.h>
#include "TestJNIConstructor.h"

using namespace std;


JNIEXPORT jobject JNICALL Java_TestJNIConstructor_getIntegerObject
          (JNIEnv *env, jobject thisObj, jint number) {
   // Get a class reference for java.lang.Integer
   jclass cls = env->FindClass("TestJNIClass"); // The prefix L is not allowed
   // Get the Method ID of the constructor which takes an int
   //jobject nlf = env->NewLocalRef(NULL);
   //jfieldID midInit = env->GetStaticFieldID(cls, "narr", "[I");
   //if (NULL == midInit) return NULL;
   //if (NULL == midToString) return NULL;
   printf("I'm still running\n");
   printf("10\n9\n8\n7\n6\n5\n4\n3\n2\n1\n0\n");
   printf("Still runnung bad....");

   //May need to call releaseStringUTFChars() before return
   return NULL;
}
