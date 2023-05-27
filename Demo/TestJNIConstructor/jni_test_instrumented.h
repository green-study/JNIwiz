/*
 * Copyright (c) 1996, 2016, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

/*
 * We used part of Netscape's Java Runtime Interface (JRI) as the starting
 * point of our design and implementation.
 */

/******************************************************************************
 * Java Runtime Interface
 * Copyright (c) 1996 Netscape Communications Corporation. All rights reserved.
 *****************************************************************************/

#ifndef _JAVASOFT_JNI_H_
#define _JAVASOFT_JNI_H_

#include <stdio.h>
#include <stdarg.h>
//test code 2023.03.25
#ifdef __cplusplus
#include <map>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
#endif
//test code end
/* jni_md.h contains the machine-dependent typedefs for jbyte, jint
   and jlong */

#include "jni_md.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * JNI Types
 */

#ifndef JNI_TYPES_ALREADY_DEFINED_IN_JNI_MD_H

typedef unsigned char   jboolean;
typedef unsigned short  jchar;
typedef short           jshort;
typedef float           jfloat;
typedef double          jdouble;

typedef jint            jsize;

#ifdef __cplusplus

class _jobject {};
class _jclass : public _jobject {};
class _jthrowable : public _jobject {};
class _jstring : public _jobject {};
class _jarray : public _jobject {};
class _jbooleanArray : public _jarray {};
class _jbyteArray : public _jarray {};
class _jcharArray : public _jarray {};
class _jshortArray : public _jarray {};
class _jintArray : public _jarray {};
class _jlongArray : public _jarray {};
class _jfloatArray : public _jarray {};
class _jdoubleArray : public _jarray {};
class _jobjectArray : public _jarray {};

typedef _jobject *jobject;
typedef _jclass *jclass;
typedef _jthrowable *jthrowable;
typedef _jstring *jstring;
typedef _jarray *jarray;
typedef _jbooleanArray *jbooleanArray;
typedef _jbyteArray *jbyteArray;
typedef _jcharArray *jcharArray;
typedef _jshortArray *jshortArray;
typedef _jintArray *jintArray;
typedef _jlongArray *jlongArray;
typedef _jfloatArray *jfloatArray;
typedef _jdoubleArray *jdoubleArray;
typedef _jobjectArray *jobjectArray;

#else

struct _jobject;

typedef struct _jobject *jobject;
typedef jobject jclass;
typedef jobject jthrowable;
typedef jobject jstring;
typedef jobject jarray;
typedef jarray jbooleanArray;
typedef jarray jbyteArray;
typedef jarray jcharArray;
typedef jarray jshortArray;
typedef jarray jintArray;
typedef jarray jlongArray;
typedef jarray jfloatArray;
typedef jarray jdoubleArray;
typedef jarray jobjectArray;

#endif

typedef jobject jweak;

typedef union jvalue {
    jboolean z;
    jbyte    b;
    jchar    c;
    jshort   s;
    jint     i;
    jlong    j;
    jfloat   f;
    jdouble  d;
    jobject  l;
} jvalue;

struct _jfieldID;
typedef struct _jfieldID *jfieldID;

struct _jmethodID;
typedef struct _jmethodID *jmethodID;

/* Return values from jobjectRefType */
typedef enum _jobjectType {
     JNIInvalidRefType    = 0,
     JNILocalRefType      = 1,
     JNIGlobalRefType     = 2,
     JNIWeakGlobalRefType = 3
} jobjectRefType;


#endif /* JNI_TYPES_ALREADY_DEFINED_IN_JNI_MD_H */

/*
 * jboolean constants
 */

#define JNI_FALSE 0
#define JNI_TRUE 1

/*
 * possible return values for JNI functions.
 */

#define JNI_OK           0                 /* success */
#define JNI_ERR          (-1)              /* unknown error */
#define JNI_EDETACHED    (-2)              /* thread detached from the VM */
#define JNI_EVERSION     (-3)              /* JNI version error */
#define JNI_ENOMEM       (-4)              /* not enough memory */
#define JNI_EEXIST       (-5)              /* VM already created */
#define JNI_EINVAL       (-6)              /* invalid arguments */

/*
	 * used in ReleaseScalarArrayElements */

#define JNI_COMMIT 1
#define JNI_ABORT 2

/*
 * used in RegisterNatives to describe native method name, signature,
 * and function pointer.
 */

typedef struct {
    char *name;
    char *signature;
    void *fnPtr;
} JNINativeMethod;

/*
 * JNI Native Method Interface.
 */

struct JNINativeInterface_;

struct JNIEnv_;

#ifdef __cplusplus
typedef JNIEnv_ JNIEnv;
#else
typedef const struct JNINativeInterface_ *JNIEnv;
#endif

/*
 * JNI Invocation Interface.
 */

struct JNIInvokeInterface_;

struct JavaVM_;

#ifdef __cplusplus
typedef JavaVM_ JavaVM;
#else
typedef const struct JNIInvokeInterface_ *JavaVM;
#endif

struct JNINativeInterface_ {
    void *reserved0;
    void *reserved1;
    void *reserved2;

    void *reserved3;
    jint (JNICALL *GetVersion)(JNIEnv *env);

    jclass (JNICALL *DefineClass)
      (JNIEnv *env, const char *name, jobject loader, const jbyte *buf,
       jsize len);
    jclass (JNICALL *FindClass)
      (JNIEnv *env, const char *name);

    jmethodID (JNICALL *FromReflectedMethod)
      (JNIEnv *env, jobject method);
    jfieldID (JNICALL *FromReflectedField)
      (JNIEnv *env, jobject field);

    jobject (JNICALL *ToReflectedMethod)
      (JNIEnv *env, jclass cls, jmethodID methodID, jboolean isStatic);

    jclass (JNICALL *GetSuperclass)
      (JNIEnv *env, jclass sub);
    jboolean (JNICALL *IsAssignableFrom)
      (JNIEnv *env, jclass sub, jclass sup);

    jobject (JNICALL *ToReflectedField)
      (JNIEnv *env, jclass cls, jfieldID fieldID, jboolean isStatic);

    jint (JNICALL *Throw)
      (JNIEnv *env, jthrowable obj);
    jint (JNICALL *ThrowNew)
      (JNIEnv *env, jclass clazz, const char *msg);
    jthrowable (JNICALL *ExceptionOccurred)
      (JNIEnv *env);
    void (JNICALL *ExceptionDescribe)
      (JNIEnv *env);
    void (JNICALL *ExceptionClear)
      (JNIEnv *env);
    void (JNICALL *FatalError)
      (JNIEnv *env, const char *msg);

    jint (JNICALL *PushLocalFrame)
      (JNIEnv *env, jint capacity);
    jobject (JNICALL *PopLocalFrame)
      (JNIEnv *env, jobject result);

    jobject (JNICALL *NewGlobalRef)
      (JNIEnv *env, jobject lobj);
    void (JNICALL *DeleteGlobalRef)
      (JNIEnv *env, jobject gref);
    void (JNICALL *DeleteLocalRef)
      (JNIEnv *env, jobject obj);
    jboolean (JNICALL *IsSameObject)
      (JNIEnv *env, jobject obj1, jobject obj2);
    jobject (JNICALL *NewLocalRef)
      (JNIEnv *env, jobject ref);
    jint (JNICALL *EnsureLocalCapacity)
      (JNIEnv *env, jint capacity);

    jobject (JNICALL *AllocObject)
      (JNIEnv *env, jclass clazz);
    jobject (JNICALL *NewObject)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jobject (JNICALL *NewObjectV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jobject (JNICALL *NewObjectA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jclass (JNICALL *GetObjectClass)
      (JNIEnv *env, jobject obj);
    jboolean (JNICALL *IsInstanceOf)
      (JNIEnv *env, jobject obj, jclass clazz);

    jmethodID (JNICALL *GetMethodID)
      (JNIEnv *env, jclass clazz, const char *name, const char *sig);

    jobject (JNICALL *CallObjectMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jobject (JNICALL *CallObjectMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jobject (JNICALL *CallObjectMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue * args);

    jboolean (JNICALL *CallBooleanMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jboolean (JNICALL *CallBooleanMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jboolean (JNICALL *CallBooleanMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue * args);

    jbyte (JNICALL *CallByteMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jbyte (JNICALL *CallByteMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jbyte (JNICALL *CallByteMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue *args);

    jchar (JNICALL *CallCharMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jchar (JNICALL *CallCharMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jchar (JNICALL *CallCharMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue *args);

    jshort (JNICALL *CallShortMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jshort (JNICALL *CallShortMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jshort (JNICALL *CallShortMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue *args);

    jint (JNICALL *CallIntMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jint (JNICALL *CallIntMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jint (JNICALL *CallIntMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue *args);

    jlong (JNICALL *CallLongMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jlong (JNICALL *CallLongMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jlong (JNICALL *CallLongMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue *args);

    jfloat (JNICALL *CallFloatMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jfloat (JNICALL *CallFloatMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jfloat (JNICALL *CallFloatMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue *args);

    jdouble (JNICALL *CallDoubleMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jdouble (JNICALL *CallDoubleMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jdouble (JNICALL *CallDoubleMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue *args);

    void (JNICALL *CallVoidMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    void (JNICALL *CallVoidMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    void (JNICALL *CallVoidMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue * args);

    jobject (JNICALL *CallNonvirtualObjectMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jobject (JNICALL *CallNonvirtualObjectMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jobject (JNICALL *CallNonvirtualObjectMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue * args);

    jboolean (JNICALL *CallNonvirtualBooleanMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jboolean (JNICALL *CallNonvirtualBooleanMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jboolean (JNICALL *CallNonvirtualBooleanMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue * args);

    jbyte (JNICALL *CallNonvirtualByteMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jbyte (JNICALL *CallNonvirtualByteMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jbyte (JNICALL *CallNonvirtualByteMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue *args);

    jchar (JNICALL *CallNonvirtualCharMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jchar (JNICALL *CallNonvirtualCharMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jchar (JNICALL *CallNonvirtualCharMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue *args);

    jshort (JNICALL *CallNonvirtualShortMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jshort (JNICALL *CallNonvirtualShortMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jshort (JNICALL *CallNonvirtualShortMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue *args);

    jint (JNICALL *CallNonvirtualIntMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jint (JNICALL *CallNonvirtualIntMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jint (JNICALL *CallNonvirtualIntMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue *args);

    jlong (JNICALL *CallNonvirtualLongMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jlong (JNICALL *CallNonvirtualLongMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jlong (JNICALL *CallNonvirtualLongMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue *args);

    jfloat (JNICALL *CallNonvirtualFloatMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jfloat (JNICALL *CallNonvirtualFloatMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jfloat (JNICALL *CallNonvirtualFloatMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue *args);

    jdouble (JNICALL *CallNonvirtualDoubleMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jdouble (JNICALL *CallNonvirtualDoubleMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jdouble (JNICALL *CallNonvirtualDoubleMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue *args);

    void (JNICALL *CallNonvirtualVoidMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    void (JNICALL *CallNonvirtualVoidMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    void (JNICALL *CallNonvirtualVoidMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue * args);

    jfieldID (JNICALL *GetFieldID)
      (JNIEnv *env, jclass clazz, const char *name, const char *sig);

    jobject (JNICALL *GetObjectField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jboolean (JNICALL *GetBooleanField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jbyte (JNICALL *GetByteField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jchar (JNICALL *GetCharField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jshort (JNICALL *GetShortField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jint (JNICALL *GetIntField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jlong (JNICALL *GetLongField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jfloat (JNICALL *GetFloatField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jdouble (JNICALL *GetDoubleField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);

    void (JNICALL *SetObjectField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jobject val);
    void (JNICALL *SetBooleanField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jboolean val);
    void (JNICALL *SetByteField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jbyte val);
    void (JNICALL *SetCharField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jchar val);
    void (JNICALL *SetShortField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jshort val);
    void (JNICALL *SetIntField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jint val);
    void (JNICALL *SetLongField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jlong val);
    void (JNICALL *SetFloatField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jfloat val);
    void (JNICALL *SetDoubleField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jdouble val);

    jmethodID (JNICALL *GetStaticMethodID)
      (JNIEnv *env, jclass clazz, const char *name, const char *sig);

    jobject (JNICALL *CallStaticObjectMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jobject (JNICALL *CallStaticObjectMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jobject (JNICALL *CallStaticObjectMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jboolean (JNICALL *CallStaticBooleanMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jboolean (JNICALL *CallStaticBooleanMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jboolean (JNICALL *CallStaticBooleanMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jbyte (JNICALL *CallStaticByteMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jbyte (JNICALL *CallStaticByteMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jbyte (JNICALL *CallStaticByteMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jchar (JNICALL *CallStaticCharMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jchar (JNICALL *CallStaticCharMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jchar (JNICALL *CallStaticCharMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jshort (JNICALL *CallStaticShortMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jshort (JNICALL *CallStaticShortMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jshort (JNICALL *CallStaticShortMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jint (JNICALL *CallStaticIntMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jint (JNICALL *CallStaticIntMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jint (JNICALL *CallStaticIntMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jlong (JNICALL *CallStaticLongMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jlong (JNICALL *CallStaticLongMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jlong (JNICALL *CallStaticLongMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jfloat (JNICALL *CallStaticFloatMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jfloat (JNICALL *CallStaticFloatMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jfloat (JNICALL *CallStaticFloatMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jdouble (JNICALL *CallStaticDoubleMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jdouble (JNICALL *CallStaticDoubleMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jdouble (JNICALL *CallStaticDoubleMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    void (JNICALL *CallStaticVoidMethod)
      (JNIEnv *env, jclass cls, jmethodID methodID, ...);
    void (JNICALL *CallStaticVoidMethodV)
      (JNIEnv *env, jclass cls, jmethodID methodID, va_list args);
    void (JNICALL *CallStaticVoidMethodA)
      (JNIEnv *env, jclass cls, jmethodID methodID, const jvalue * args);

    jfieldID (JNICALL *GetStaticFieldID)
      (JNIEnv *env, jclass clazz, const char *name, const char *sig);
    jobject (JNICALL *GetStaticObjectField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jboolean (JNICALL *GetStaticBooleanField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jbyte (JNICALL *GetStaticByteField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jchar (JNICALL *GetStaticCharField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jshort (JNICALL *GetStaticShortField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jint (JNICALL *GetStaticIntField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jlong (JNICALL *GetStaticLongField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jfloat (JNICALL *GetStaticFloatField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jdouble (JNICALL *GetStaticDoubleField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);

    void (JNICALL *SetStaticObjectField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jobject value);
    void (JNICALL *SetStaticBooleanField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jboolean value);
    void (JNICALL *SetStaticByteField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jbyte value);
    void (JNICALL *SetStaticCharField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jchar value);
    void (JNICALL *SetStaticShortField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jshort value);
    void (JNICALL *SetStaticIntField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jint value);
    void (JNICALL *SetStaticLongField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jlong value);
    void (JNICALL *SetStaticFloatField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jfloat value);
    void (JNICALL *SetStaticDoubleField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jdouble value);

    jstring (JNICALL *NewString)
      (JNIEnv *env, const jchar *unicode, jsize len);
    jsize (JNICALL *GetStringLength)
      (JNIEnv *env, jstring str);
    const jchar *(JNICALL *GetStringChars)
      (JNIEnv *env, jstring str, jboolean *isCopy);
    void (JNICALL *ReleaseStringChars)
      (JNIEnv *env, jstring str, const jchar *chars);

    jstring (JNICALL *NewStringUTF)
      (JNIEnv *env, const char *utf);
    jsize (JNICALL *GetStringUTFLength)
      (JNIEnv *env, jstring str);
    const char* (JNICALL *GetStringUTFChars)
      (JNIEnv *env, jstring str, jboolean *isCopy);
    void (JNICALL *ReleaseStringUTFChars)
      (JNIEnv *env, jstring str, const char* chars);


    jsize (JNICALL *GetArrayLength)
      (JNIEnv *env, jarray array);

    jobjectArray (JNICALL *NewObjectArray)
      (JNIEnv *env, jsize len, jclass clazz, jobject init);
    jobject (JNICALL *GetObjectArrayElement)
      (JNIEnv *env, jobjectArray array, jsize index);
    void (JNICALL *SetObjectArrayElement)
      (JNIEnv *env, jobjectArray array, jsize index, jobject val);

    jbooleanArray (JNICALL *NewBooleanArray)
      (JNIEnv *env, jsize len);
    jbyteArray (JNICALL *NewByteArray)
      (JNIEnv *env, jsize len);
    jcharArray (JNICALL *NewCharArray)
      (JNIEnv *env, jsize len);
    jshortArray (JNICALL *NewShortArray)
      (JNIEnv *env, jsize len);
    jintArray (JNICALL *NewIntArray)
      (JNIEnv *env, jsize len);
    jlongArray (JNICALL *NewLongArray)
      (JNIEnv *env, jsize len);
    jfloatArray (JNICALL *NewFloatArray)
      (JNIEnv *env, jsize len);
    jdoubleArray (JNICALL *NewDoubleArray)
      (JNIEnv *env, jsize len);

    jboolean * (JNICALL *GetBooleanArrayElements)
      (JNIEnv *env, jbooleanArray array, jboolean *isCopy);
    jbyte * (JNICALL *GetByteArrayElements)
      (JNIEnv *env, jbyteArray array, jboolean *isCopy);
    jchar * (JNICALL *GetCharArrayElements)
      (JNIEnv *env, jcharArray array, jboolean *isCopy);
    jshort * (JNICALL *GetShortArrayElements)
      (JNIEnv *env, jshortArray array, jboolean *isCopy);
    jint * (JNICALL *GetIntArrayElements)
      (JNIEnv *env, jintArray array, jboolean *isCopy);
    jlong * (JNICALL *GetLongArrayElements)
      (JNIEnv *env, jlongArray array, jboolean *isCopy);
    jfloat * (JNICALL *GetFloatArrayElements)
      (JNIEnv *env, jfloatArray array, jboolean *isCopy);
    jdouble * (JNICALL *GetDoubleArrayElements)
      (JNIEnv *env, jdoubleArray array, jboolean *isCopy);

    void (JNICALL *ReleaseBooleanArrayElements)
      (JNIEnv *env, jbooleanArray array, jboolean *elems, jint mode);
    void (JNICALL *ReleaseByteArrayElements)
      (JNIEnv *env, jbyteArray array, jbyte *elems, jint mode);
    void (JNICALL *ReleaseCharArrayElements)
      (JNIEnv *env, jcharArray array, jchar *elems, jint mode);
    void (JNICALL *ReleaseShortArrayElements)
      (JNIEnv *env, jshortArray array, jshort *elems, jint mode);
    void (JNICALL *ReleaseIntArrayElements)
      (JNIEnv *env, jintArray array, jint *elems, jint mode);
    void (JNICALL *ReleaseLongArrayElements)
      (JNIEnv *env, jlongArray array, jlong *elems, jint mode);
    void (JNICALL *ReleaseFloatArrayElements)
      (JNIEnv *env, jfloatArray array, jfloat *elems, jint mode);
    void (JNICALL *ReleaseDoubleArrayElements)
      (JNIEnv *env, jdoubleArray array, jdouble *elems, jint mode);

    void (JNICALL *GetBooleanArrayRegion)
      (JNIEnv *env, jbooleanArray array, jsize start, jsize l, jboolean *buf);
    void (JNICALL *GetByteArrayRegion)
      (JNIEnv *env, jbyteArray array, jsize start, jsize len, jbyte *buf);
    void (JNICALL *GetCharArrayRegion)
      (JNIEnv *env, jcharArray array, jsize start, jsize len, jchar *buf);
    void (JNICALL *GetShortArrayRegion)
      (JNIEnv *env, jshortArray array, jsize start, jsize len, jshort *buf);
    void (JNICALL *GetIntArrayRegion)
      (JNIEnv *env, jintArray array, jsize start, jsize len, jint *buf);
    void (JNICALL *GetLongArrayRegion)
      (JNIEnv *env, jlongArray array, jsize start, jsize len, jlong *buf);
    void (JNICALL *GetFloatArrayRegion)
      (JNIEnv *env, jfloatArray array, jsize start, jsize len, jfloat *buf);
    void (JNICALL *GetDoubleArrayRegion)
      (JNIEnv *env, jdoubleArray array, jsize start, jsize len, jdouble *buf);

    void (JNICALL *SetBooleanArrayRegion)
      (JNIEnv *env, jbooleanArray array, jsize start, jsize l, const jboolean *buf);
    void (JNICALL *SetByteArrayRegion)
      (JNIEnv *env, jbyteArray array, jsize start, jsize len, const jbyte *buf);
    void (JNICALL *SetCharArrayRegion)
      (JNIEnv *env, jcharArray array, jsize start, jsize len, const jchar *buf);
    void (JNICALL *SetShortArrayRegion)
      (JNIEnv *env, jshortArray array, jsize start, jsize len, const jshort *buf);
    void (JNICALL *SetIntArrayRegion)
      (JNIEnv *env, jintArray array, jsize start, jsize len, const jint *buf);
    void (JNICALL *SetLongArrayRegion)
      (JNIEnv *env, jlongArray array, jsize start, jsize len, const jlong *buf);
    void (JNICALL *SetFloatArrayRegion)
      (JNIEnv *env, jfloatArray array, jsize start, jsize len, const jfloat *buf);
    void (JNICALL *SetDoubleArrayRegion)
      (JNIEnv *env, jdoubleArray array, jsize start, jsize len, const jdouble *buf);

    jint (JNICALL *RegisterNatives)
      (JNIEnv *env, jclass clazz, const JNINativeMethod *methods,
       jint nMethods);
    jint (JNICALL *UnregisterNatives)
      (JNIEnv *env, jclass clazz);

    jint (JNICALL *MonitorEnter)
      (JNIEnv *env, jobject obj);
    jint (JNICALL *MonitorExit)
      (JNIEnv *env, jobject obj);

    jint (JNICALL *GetJavaVM)
      (JNIEnv *env, JavaVM **vm);

    void (JNICALL *GetStringRegion)
      (JNIEnv *env, jstring str, jsize start, jsize len, jchar *buf);
    void (JNICALL *GetStringUTFRegion)
      (JNIEnv *env, jstring str, jsize start, jsize len, char *buf);

    void * (JNICALL *GetPrimitiveArrayCritical)
      (JNIEnv *env, jarray array, jboolean *isCopy);
    void (JNICALL *ReleasePrimitiveArrayCritical)
      (JNIEnv *env, jarray array, void *carray, jint mode);

    const jchar * (JNICALL *GetStringCritical)
      (JNIEnv *env, jstring string, jboolean *isCopy);
    void (JNICALL *ReleaseStringCritical)
      (JNIEnv *env, jstring string, const jchar *cstring);

    jweak (JNICALL *NewWeakGlobalRef)
       (JNIEnv *env, jobject obj);
    void (JNICALL *DeleteWeakGlobalRef)
       (JNIEnv *env, jweak ref);

    jboolean (JNICALL *ExceptionCheck)
       (JNIEnv *env);

    jobject (JNICALL *NewDirectByteBuffer)
       (JNIEnv* env, void* address, jlong capacity);
    void* (JNICALL *GetDirectBufferAddress)
       (JNIEnv* env, jobject buf);
    jlong (JNICALL *GetDirectBufferCapacity)
       (JNIEnv* env, jobject buf);

    /* New JNI 1.6 Features */

    jobjectRefType (JNICALL *GetObjectRefType)
        (JNIEnv* env, jobject obj);

    /* Module Features */

    jobject (JNICALL *GetModule)
       (JNIEnv* env, jclass clazz);
};

/*
 * We use inlined functions for C++ so that programmers can write:
 *
 *    env->FindClass("java/lang/String")
 *
 * in C++ rather than:
 *
 *    (*env)->FindClass(env, "java/lang/String")
 *
 * in C.
 */
map<jclass, string> class_map;
vector<string> class_vector;
map<string, vector<pair<string, string>>> func_map;
map<string, vector<pair<string, string>>> static_func_map;
map<string, vector<pair<string, string>>> field_map;
map<string, vector<pair<string, string>>> static_field_map;

struct JNIEnv_ {
    const struct JNINativeInterface_ *functions;
#ifdef __cplusplus
    //test code 2023.03.25

    void Java_JNI_init(){
	if(class_map.empty() && class_vector.empty()){
		class_vector.push_back("TestJNIConstructor");
	}
	if(func_map.empty() && static_func_map.empty()){
		vector<pair<string, string>> v;
		vector<pair<string, string>> sv;
		v.push_back(make_pair("toString", "()Ljava/lang/String;"));
		v.push_back(make_pair("getIntegerObject", "(I)Ljava/lang/Integer;"));
		v.push_back(make_pair("getClass", "()Ljava/lang/Class;"));
		v.push_back(make_pair("finalize", "()V"));
		v.push_back(make_pair("hashCode", "()I"));
		v.push_back(make_pair("clone", "()Ljava/lang/Object;"));
		v.push_back(make_pair("<init>", "()V"));
		v.push_back(make_pair("wait", "(JI)V"));
		v.push_back(make_pair("<init>", "()V"));
		v.push_back(make_pair("notify", "()V"));
		v.push_back(make_pair("wait", "()V"));
		v.push_back(make_pair("notifyAll", "()V"));
		v.push_back(make_pair("equals", "(Ljava/lang/Object;)Z"));
		v.push_back(make_pair("wait", "(J)V"));
		sv.push_back(make_pair("<clinit>", "()V"));
		sv.push_back(make_pair("registerNatives", "()V"));
		sv.push_back(make_pair("<clinit>", "()V"));
		sv.push_back(make_pair("main", "([Ljava/lang/String;)V"));
		func_map["TestJNIConstructor"] = v;
		static_func_map["TestJNIConstructor"] = sv;
		v.clear();
		sv.clear();
	}
	if(field_map.empty() && static_field_map.empty()){
		vector<pair<string, string>> f;
		vector<pair<string, string>> sf;
		field_map["TestJNIConstructor"] = f;
		static_field_map["TestJNIConstructor"] = sf;
		f.clear();
		sf.clear();
	}
    }    
    //test code end
    jint GetVersion() {
        return functions->GetVersion(this);
    }
    jclass DefineClass(const char *name, jobject loader, const jbyte *buf,
                       jsize len) {
	if(!name) {
		printf("[JNI DefineClass] name parameter: null-pointer\n");
		exit(-1);
	}
	if(!loader) {
		printf("[JNI DefineClass] loader parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI DefineClass] buf parameter: null-pointer\n");
		exit(-1);
	}
    	return functions->DefineClass(this, name, loader, buf, len);
    }
    jclass FindClass(const char *name) {
	if(!name) {
		printf("[JNI FindClass] name parameter: null-pointer\n");
		exit(-1);
	}
    	Java_JNI_init();
        for(auto cname : class_vector){
                if(strcmp(cname.c_str(), name) == 0){
			jclass temp = functions->FindClass(this, name);
                	class_map[temp] = name;
                        return temp;
                }
        }
        printf("[JNI FindClass] java class %s doesn't exist\n", name);
        exit(-1);
    }
    jmethodID FromReflectedMethod(jobject method) {
	if(!method) {
		printf("[JNI FromReflectedMethod] method parameter: null-pointer\n");
		exit(-1);
	}
        return functions->FromReflectedMethod(this,method);
    }
    jfieldID FromReflectedField(jobject field) {
	if(!field) {
		printf("[JNI FromReflectedField] field parameter: null-pointer\n");
		exit(-1);
	}
        return functions->FromReflectedField(this,field);
    }

    jobject ToReflectedMethod(jclass cls, jmethodID methodID, jboolean isStatic) {
	if(!cls) {
		printf("[JNI ToReflectedMethod] cls parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI ToReflectedMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->ToReflectedMethod(this, cls, methodID, isStatic);
    }

    jclass GetSuperclass(jclass sub) {
	if(!sub) {
		printf("[JNI GetSuperclass] sub parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetSuperclass(this, sub);
    }
    jboolean IsAssignableFrom(jclass sub, jclass sup) {
	if(!sub) {
		printf("[JNI IsAssignableFrom] sub parameter: null-pointer\n");
		exit(-1);
	}
	if(!sup) {
		printf("[JNI IsAssignableFrom] sup parameter: null-pointer\n");
		exit(-1);
	}
        return functions->IsAssignableFrom(this, sub, sup);
    }

    jobject ToReflectedField(jclass cls, jfieldID fieldID, jboolean isStatic) {
	if(!cls) {
		printf("[JNI ToReflectedField] cls parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI ToReflectedField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->ToReflectedField(this,cls,fieldID,isStatic);
    }

    jint Throw(jthrowable obj) {
	if(!obj) {
		printf("[JNI Throw] obj parameter: null-pointer\n");
		exit(-1);
	}
        return functions->Throw(this, obj);
    }
    jint ThrowNew(jclass clazz, const char *msg) {
	if(!clazz) {
		printf("[JNI ThrowNew] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!msg) {
		printf("[JNI ThrowNew] msg parameter: null-pointer\n");
		exit(-1);
	}
        return functions->ThrowNew(this, clazz, msg);
    }
    jthrowable ExceptionOccurred() {
        return functions->ExceptionOccurred(this);
    }
    void ExceptionDescribe() {
        functions->ExceptionDescribe(this);
    }
    void ExceptionClear() {
        functions->ExceptionClear(this);
    }
    void FatalError(const char *msg) {
	if(!msg) {
		printf("[JNI FatalError] msg parameter: null-pointer\n");
		exit(-1);
	}
        functions->FatalError(this, msg);
    }

    jint PushLocalFrame(jint capacity) {
        return functions->PushLocalFrame(this,capacity);
    }
    jobject PopLocalFrame(jobject result) {
	if(!result) {
		printf("[JNI PopLocalFrame] result parameter: null-pointer\n");
		exit(-1);
	}
        return functions->PopLocalFrame(this,result);
    }

    jobject NewGlobalRef(jobject lobj) {
	if(!lobj) {
		printf("[JNI NewGlobalRef] lobj parameter: null-pointer\n");
		exit(-1);
	}
        return functions->NewGlobalRef(this,lobj);
    }
    void DeleteGlobalRef(jobject gref) {
	if(!gref) {
		printf("[JNI DeleteGlobalRef] gref parameter: null-pointer\n");
		exit(-1);
	}
        functions->DeleteGlobalRef(this,gref);
    }
    void DeleteLocalRef(jobject obj) {
	if(!obj) {
		printf("[JNI DeleteLocalRef] obj parameter: null-pointer\n");
		exit(-1);
	}
        functions->DeleteLocalRef(this, obj);
    }

    jboolean IsSameObject(jobject obj1, jobject obj2) {
	if(!obj1) {
		printf("[JNI IsSameObject] obj1 parameter: null-pointer\n");
		exit(-1);
	}
	if(!obj2) {
		printf("[JNI IsSameObject] obj2 parameter: null-pointer\n");
		exit(-1);
	}
        return functions->IsSameObject(this,obj1,obj2);
    }

    jobject NewLocalRef(jobject ref) {
	if(!ref) {
		printf("[JNI NewLocalRef] ref parameter: null-pointer\n");
		exit(-1);
	}
        return functions->NewLocalRef(this,ref);
    }
    jint EnsureLocalCapacity(jint capacity) {
        return functions->EnsureLocalCapacity(this,capacity);
    }

    jobject AllocObject(jclass clazz) {
	if(!clazz) {
		printf("[JNI AllocObject] clazz parameter: null-pointer\n");
		exit(-1);
	}
        return functions->AllocObject(this,clazz);
    }
    jobject NewObject(jclass clazz, jmethodID methodID, ...) {
	if(!clazz) {
		printf("[JNI NewObject] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI NewObject] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jobject result;
        va_start(args, methodID);
        result = functions->NewObjectV(this,clazz,methodID,args);
        va_end(args);
        return result;
    }
    jobject NewObjectV(jclass clazz, jmethodID methodID,
                       va_list args) {
	if(!clazz) {
		printf("[JNI NewObjectV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI NewObjectV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI NewObjectV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->NewObjectV(this,clazz,methodID,args);
    }
    jobject NewObjectA(jclass clazz, jmethodID methodID,
                       const jvalue *args) {
	if(!clazz) {
		printf("[JNI NewObjectA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI NewObjectA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI NewObjectA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->NewObjectA(this,clazz,methodID,args);
    }

    jclass GetObjectClass(jobject obj) {
	if(!obj) {
		printf("[JNI GetObjectClass] obj parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetObjectClass(this,obj);
    }
    jboolean IsInstanceOf(jobject obj, jclass clazz) {
	if(!obj) {
		printf("[JNI IsInstanceOf] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI IsInstanceOf] clazz parameter: null-pointer\n");
		exit(-1);
	}
        return functions->IsInstanceOf(this,obj,clazz);
    }

    jmethodID GetMethodID(jclass clazz, const char *name,
                          const char *sig) {
	if(!clazz) {
		printf("[JNI GetMethodID] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!name) {
		printf("[JNI GetMethodID] name parameter: null-pointer\n");
		exit(-1);
	}
	if(!sig) {
		printf("[JNI GetMethodID] sig parameter: null-pointer\n");
		exit(-1);
	}
    	Java_JNI_init();
        const char* clz_name = class_map[clazz].c_str();
        auto func_vector = func_map[clz_name];

        for(auto iter : func_vector){
                if((strcmp(iter.first.c_str(),name) == 0) && (strcmp(iter.second.c_str(),sig) == 0)){
                        return functions->GetMethodID(this,clazz,name,sig);
                }
        }
        printf("[JNI GetMethodID] java method name: %s, sig: %s doesn't exist in java class %s \n", name, sig, clz_name);
        exit(-1);
    }

    jobject CallObjectMethod(jobject obj, jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallObjectMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallObjectMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jobject result;
        va_start(args,methodID);
        result = functions->CallObjectMethodV(this,obj,methodID,args);
        va_end(args);
        return result;
    }
    jobject CallObjectMethodV(jobject obj, jmethodID methodID,
                        va_list args) {
	if(!obj) {
		printf("[JNI CallObjectMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallObjectMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallObjectMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallObjectMethodV(this,obj,methodID,args);
    }
    jobject CallObjectMethodA(jobject obj, jmethodID methodID,
                        const jvalue * args) {
	if(!obj) {
		printf("[JNI CallObjectMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallObjectMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallObjectMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallObjectMethodA(this,obj,methodID,args);
    }

    jboolean CallBooleanMethod(jobject obj,
                               jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallBooleanMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallBooleanMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jboolean result;
        va_start(args,methodID);
        result = functions->CallBooleanMethodV(this,obj,methodID,args);
        va_end(args);
        return result;
    }
    jboolean CallBooleanMethodV(jobject obj, jmethodID methodID,
                                va_list args) {
	if(!obj) {
		printf("[JNI CallBooleanMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallBooleanMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallBooleanMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallBooleanMethodV(this,obj,methodID,args);
    }
    jboolean CallBooleanMethodA(jobject obj, jmethodID methodID,
                                const jvalue * args) {
	if(!obj) {
		printf("[JNI CallBooleanMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallBooleanMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallBooleanMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallBooleanMethodA(this,obj,methodID, args);
    }

    jbyte CallByteMethod(jobject obj, jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallByteMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallByteMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jbyte result;
        va_start(args,methodID);
        result = functions->CallByteMethodV(this,obj,methodID,args);
        va_end(args);
        return result;
    }
    jbyte CallByteMethodV(jobject obj, jmethodID methodID,
                          va_list args) {
	if(!obj) {
		printf("[JNI CallByteMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallByteMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallByteMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallByteMethodV(this,obj,methodID,args);
    }
    jbyte CallByteMethodA(jobject obj, jmethodID methodID,
                          const jvalue * args) {
	if(!obj) {
		printf("[JNI CallByteMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallByteMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallByteMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallByteMethodA(this,obj,methodID,args);
    }

    jchar CallCharMethod(jobject obj, jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallCharMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallCharMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jchar result;
        va_start(args,methodID);
        result = functions->CallCharMethodV(this,obj,methodID,args);
        va_end(args);
        return result;
    }
    jchar CallCharMethodV(jobject obj, jmethodID methodID,
                          va_list args) {
	if(!obj) {
		printf("[JNI CallCharMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallCharMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallCharMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallCharMethodV(this,obj,methodID,args);
    }
    jchar CallCharMethodA(jobject obj, jmethodID methodID,
                          const jvalue * args) {
	if(!obj) {
		printf("[JNI CallCharMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallCharMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallCharMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallCharMethodA(this,obj,methodID,args);
    }

    jshort CallShortMethod(jobject obj, jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallShortMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallShortMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jshort result;
        va_start(args,methodID);
        result = functions->CallShortMethodV(this,obj,methodID,args);
        va_end(args);
        return result;
    }
    jshort CallShortMethodV(jobject obj, jmethodID methodID,
                            va_list args) {
	if(!obj) {
		printf("[JNI CallShortMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallShortMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallShortMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallShortMethodV(this,obj,methodID,args);
    }
    jshort CallShortMethodA(jobject obj, jmethodID methodID,
                            const jvalue * args) {
	if(!obj) {
		printf("[JNI CallShortMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallShortMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallShortMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallShortMethodA(this,obj,methodID,args);
    }

    jint CallIntMethod(jobject obj, jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallIntMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallIntMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jint result;
        va_start(args,methodID);
        result = functions->CallIntMethodV(this,obj,methodID,args);
        va_end(args);
        return result;
    }
    jint CallIntMethodV(jobject obj, jmethodID methodID,
                        va_list args) {
	if(!obj) {
		printf("[JNI CallIntMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallIntMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallIntMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallIntMethodV(this,obj,methodID,args);
    }
    jint CallIntMethodA(jobject obj, jmethodID methodID,
                        const jvalue * args) {
	if(!obj) {
		printf("[JNI CallIntMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallIntMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallIntMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallIntMethodA(this,obj,methodID,args);
    }

    jlong CallLongMethod(jobject obj, jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallLongMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallLongMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jlong result;
        va_start(args,methodID);
        result = functions->CallLongMethodV(this,obj,methodID,args);
        va_end(args);
        return result;
    }
    jlong CallLongMethodV(jobject obj, jmethodID methodID,
                          va_list args) {
	if(!obj) {
		printf("[JNI CallLongMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallLongMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallLongMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallLongMethodV(this,obj,methodID,args);
    }
    jlong CallLongMethodA(jobject obj, jmethodID methodID,
                          const jvalue * args) {
	if(!obj) {
		printf("[JNI CallLongMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallLongMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallLongMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallLongMethodA(this,obj,methodID,args);
    }

    jfloat CallFloatMethod(jobject obj, jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallFloatMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallFloatMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jfloat result;
        va_start(args,methodID);
        result = functions->CallFloatMethodV(this,obj,methodID,args);
        va_end(args);
        return result;
    }
    jfloat CallFloatMethodV(jobject obj, jmethodID methodID,
                            va_list args) {
	if(!obj) {
		printf("[JNI CallFloatMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallFloatMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallFloatMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallFloatMethodV(this,obj,methodID,args);
    }
    jfloat CallFloatMethodA(jobject obj, jmethodID methodID,
                            const jvalue * args) {
	if(!obj) {
		printf("[JNI CallFloatMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallFloatMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallFloatMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallFloatMethodA(this,obj,methodID,args);
    }

    jdouble CallDoubleMethod(jobject obj, jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallDoubleMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallDoubleMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jdouble result;
        va_start(args,methodID);
        result = functions->CallDoubleMethodV(this,obj,methodID,args);
        va_end(args);
        return result;
    }
    jdouble CallDoubleMethodV(jobject obj, jmethodID methodID,
                        va_list args) {
	if(!obj) {
		printf("[JNI CallDoubleMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallDoubleMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallDoubleMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallDoubleMethodV(this,obj,methodID,args);
    }
    jdouble CallDoubleMethodA(jobject obj, jmethodID methodID,
                        const jvalue * args) {
	if(!obj) {
		printf("[JNI CallDoubleMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallDoubleMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallDoubleMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallDoubleMethodA(this,obj,methodID,args);
    }

    void CallVoidMethod(jobject obj, jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallVoidMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallVoidMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        va_start(args,methodID);
        functions->CallVoidMethodV(this,obj,methodID,args);
        va_end(args);
    }
    void CallVoidMethodV(jobject obj, jmethodID methodID,
                         va_list args) {
	if(!obj) {
		printf("[JNI CallVoidMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallVoidMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallVoidMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        functions->CallVoidMethodV(this,obj,methodID,args);
    }
    void CallVoidMethodA(jobject obj, jmethodID methodID,
                         const jvalue * args) {
	if(!obj) {
		printf("[JNI CallVoidMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallVoidMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallVoidMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        functions->CallVoidMethodA(this,obj,methodID,args);
    }

    jobject CallNonvirtualObjectMethod(jobject obj, jclass clazz,
                                       jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallNonvirtualObjectMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualObjectMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualObjectMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jobject result;
        va_start(args,methodID);
        result = functions->CallNonvirtualObjectMethodV(this,obj,clazz,
                                                        methodID,args);
        va_end(args);
        return result;
    }
    jobject CallNonvirtualObjectMethodV(jobject obj, jclass clazz,
                                        jmethodID methodID, va_list args) {
	if(!obj) {
		printf("[JNI CallNonvirtualObjectMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualObjectMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualObjectMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualObjectMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualObjectMethodV(this,obj,clazz,
                                                      methodID,args);
    }
    jobject CallNonvirtualObjectMethodA(jobject obj, jclass clazz,
                                        jmethodID methodID, const jvalue * args) {
	if(!obj) {
		printf("[JNI CallNonvirtualObjectMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualObjectMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualObjectMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualObjectMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualObjectMethodA(this,obj,clazz,
                                                      methodID,args);
    }

    jboolean CallNonvirtualBooleanMethod(jobject obj, jclass clazz,
                                         jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallNonvirtualBooleanMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualBooleanMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualBooleanMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jboolean result;
        va_start(args,methodID);
        result = functions->CallNonvirtualBooleanMethodV(this,obj,clazz,
                                                         methodID,args);
        va_end(args);
        return result;
    }
    jboolean CallNonvirtualBooleanMethodV(jobject obj, jclass clazz,
                                          jmethodID methodID, va_list args) {
	if(!obj) {
		printf("[JNI CallNonvirtualBooleanMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualBooleanMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualBooleanMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualBooleanMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualBooleanMethodV(this,obj,clazz,
                                                       methodID,args);
    }
    jboolean CallNonvirtualBooleanMethodA(jobject obj, jclass clazz,
                                          jmethodID methodID, const jvalue * args) {
	if(!obj) {
		printf("[JNI CallNonvirtualBooleanMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualBooleanMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualBooleanMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualBooleanMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualBooleanMethodA(this,obj,clazz,
                                                       methodID, args);
    }

    jbyte CallNonvirtualByteMethod(jobject obj, jclass clazz,
                                   jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallNonvirtualByteMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualByteMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualByteMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jbyte result;
        va_start(args,methodID);
        result = functions->CallNonvirtualByteMethodV(this,obj,clazz,
                                                      methodID,args);
        va_end(args);
        return result;
    }
    jbyte CallNonvirtualByteMethodV(jobject obj, jclass clazz,
                                    jmethodID methodID, va_list args) {
	if(!obj) {
		printf("[JNI CallNonvirtualByteMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualByteMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualByteMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualByteMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualByteMethodV(this,obj,clazz,
                                                    methodID,args);
    }
    jbyte CallNonvirtualByteMethodA(jobject obj, jclass clazz,
                                    jmethodID methodID, const jvalue * args) {
	if(!obj) {
		printf("[JNI CallNonvirtualByteMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualByteMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualByteMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualByteMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualByteMethodA(this,obj,clazz,
                                                    methodID,args);
    }

    jchar CallNonvirtualCharMethod(jobject obj, jclass clazz,
                                   jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallNonvirtualCharMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualCharMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualCharMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jchar result;
        va_start(args,methodID);
        result = functions->CallNonvirtualCharMethodV(this,obj,clazz,
                                                      methodID,args);
        va_end(args);
        return result;
    }
    jchar CallNonvirtualCharMethodV(jobject obj, jclass clazz,
                                    jmethodID methodID, va_list args) {
	if(!obj) {
		printf("[JNI CallNonvirtualCharMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualCharMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualCharMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualCharMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualCharMethodV(this,obj,clazz,
                                                    methodID,args);
    }
    jchar CallNonvirtualCharMethodA(jobject obj, jclass clazz,
                                    jmethodID methodID, const jvalue * args) {
	if(!obj) {
		printf("[JNI CallNonvirtualCharMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualCharMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualCharMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualCharMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualCharMethodA(this,obj,clazz,
                                                    methodID,args);
    }

    jshort CallNonvirtualShortMethod(jobject obj, jclass clazz,
                                     jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallNonvirtualShortMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualShortMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualShortMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jshort result;
        va_start(args,methodID);
        result = functions->CallNonvirtualShortMethodV(this,obj,clazz,
                                                       methodID,args);
        va_end(args);
        return result;
    }
    jshort CallNonvirtualShortMethodV(jobject obj, jclass clazz,
                                      jmethodID methodID, va_list args) {
	if(!obj) {
		printf("[JNI CallNonvirtualShortMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualShortMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualShortMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualShortMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualShortMethodV(this,obj,clazz,
                                                     methodID,args);
    }
    jshort CallNonvirtualShortMethodA(jobject obj, jclass clazz,
                                      jmethodID methodID, const jvalue * args) {
	if(!obj) {
		printf("[JNI CallNonvirtualShortMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualShortMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualShortMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualShortMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualShortMethodA(this,obj,clazz,
                                                     methodID,args);
    }

    jint CallNonvirtualIntMethod(jobject obj, jclass clazz,
                                 jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallNonvirtualIntMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualIntMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualIntMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jint result;
        va_start(args,methodID);
        result = functions->CallNonvirtualIntMethodV(this,obj,clazz,
                                                     methodID,args);
        va_end(args);
        return result;
    }
    jint CallNonvirtualIntMethodV(jobject obj, jclass clazz,
                                  jmethodID methodID, va_list args) {
	if(!obj) {
		printf("[JNI CallNonvirtualIntMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualIntMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualIntMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualIntMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualIntMethodV(this,obj,clazz,
                                                   methodID,args);
    }
    jint CallNonvirtualIntMethodA(jobject obj, jclass clazz,
                                  jmethodID methodID, const jvalue * args) {
	if(!obj) {
		printf("[JNI CallNonvirtualIntMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualIntMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualIntMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualIntMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualIntMethodA(this,obj,clazz,
                                                   methodID,args);
    }

    jlong CallNonvirtualLongMethod(jobject obj, jclass clazz,
                                   jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallNonvirtualLongMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualLongMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualLongMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jlong result;
        va_start(args,methodID);
        result = functions->CallNonvirtualLongMethodV(this,obj,clazz,
                                                      methodID,args);
        va_end(args);
        return result;
    }
    jlong CallNonvirtualLongMethodV(jobject obj, jclass clazz,
                                    jmethodID methodID, va_list args) {
	if(!obj) {
		printf("[JNI CallNonvirtualLongMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualLongMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualLongMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualLongMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualLongMethodV(this,obj,clazz,
                                                    methodID,args);
    }
    jlong CallNonvirtualLongMethodA(jobject obj, jclass clazz,
                                    jmethodID methodID, const jvalue * args) {
	if(!obj) {
		printf("[JNI CallNonvirtualLongMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualLongMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualLongMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualLongMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualLongMethodA(this,obj,clazz,
                                                    methodID,args);
    }

    jfloat CallNonvirtualFloatMethod(jobject obj, jclass clazz,
                                     jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallNonvirtualFloatMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualFloatMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualFloatMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jfloat result;
        va_start(args,methodID);
        result = functions->CallNonvirtualFloatMethodV(this,obj,clazz,
                                                       methodID,args);
        va_end(args);
        return result;
    }
    jfloat CallNonvirtualFloatMethodV(jobject obj, jclass clazz,
                                      jmethodID methodID,
                                      va_list args) {
	if(!obj) {
		printf("[JNI CallNonvirtualFloatMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualFloatMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualFloatMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualFloatMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualFloatMethodV(this,obj,clazz,
                                                     methodID,args);
    }
    jfloat CallNonvirtualFloatMethodA(jobject obj, jclass clazz,
                                      jmethodID methodID,
                                      const jvalue * args) {
	if(!obj) {
		printf("[JNI CallNonvirtualFloatMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualFloatMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualFloatMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualFloatMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualFloatMethodA(this,obj,clazz,
                                                     methodID,args);
    }

    jdouble CallNonvirtualDoubleMethod(jobject obj, jclass clazz,
                                       jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallNonvirtualDoubleMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualDoubleMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualDoubleMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jdouble result;
        va_start(args,methodID);
        result = functions->CallNonvirtualDoubleMethodV(this,obj,clazz,
                                                        methodID,args);
        va_end(args);
        return result;
    }
    jdouble CallNonvirtualDoubleMethodV(jobject obj, jclass clazz,
                                        jmethodID methodID,
                                        va_list args) {
	if(!obj) {
		printf("[JNI CallNonvirtualDoubleMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualDoubleMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualDoubleMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualDoubleMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualDoubleMethodV(this,obj,clazz,
                                                      methodID,args);
    }
    jdouble CallNonvirtualDoubleMethodA(jobject obj, jclass clazz,
                                        jmethodID methodID,
                                        const jvalue * args) {
	if(!obj) {
		printf("[JNI CallNonvirtualDoubleMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualDoubleMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualDoubleMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualDoubleMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallNonvirtualDoubleMethodA(this,obj,clazz,
                                                      methodID,args);
    }

    void CallNonvirtualVoidMethod(jobject obj, jclass clazz,
                                  jmethodID methodID, ...) {
	if(!obj) {
		printf("[JNI CallNonvirtualVoidMethod] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualVoidMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualVoidMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        va_start(args,methodID);
        functions->CallNonvirtualVoidMethodV(this,obj,clazz,methodID,args);
        va_end(args);
    }
    void CallNonvirtualVoidMethodV(jobject obj, jclass clazz,
                                   jmethodID methodID,
                                   va_list args) {
	if(!obj) {
		printf("[JNI CallNonvirtualVoidMethodV] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualVoidMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualVoidMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualVoidMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        functions->CallNonvirtualVoidMethodV(this,obj,clazz,methodID,args);
    }
    void CallNonvirtualVoidMethodA(jobject obj, jclass clazz,
                                   jmethodID methodID,
                                   const jvalue * args) {
	if(!obj) {
		printf("[JNI CallNonvirtualVoidMethodA] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!clazz) {
		printf("[JNI CallNonvirtualVoidMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallNonvirtualVoidMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallNonvirtualVoidMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        functions->CallNonvirtualVoidMethodA(this,obj,clazz,methodID,args);
    }

    jfieldID GetFieldID(jclass clazz, const char *name,
                        const char *sig) {
	if(!clazz) {
		printf("[JNI GetFieldID] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!name) {
		printf("[JNI GetFieldID] name parameter: null-pointer\n");
		exit(-1);
	}
	if(!sig) {
		printf("[JNI GetFieldID] sig parameter: null-pointer\n");
		exit(-1);
	}
	Java_JNI_init();
        const char* clz_name = class_map[clazz].c_str();
        auto field_vector = field_map[clz_name];

        for(auto iter : field_vector){
                if((strcmp(iter.first.c_str(),name) == 0) && (strcmp(iter.second.c_str(),sig) == 0)){
                        return functions->GetFieldID(this,clazz,name,sig);
                }
        }
        printf("[JNI GetFieldID] java field name: %s, sig: %s doesn't exist in java class %s \n", name, sig, clz_name);
	exit(-1);
    }

    jobject GetObjectField(jobject obj, jfieldID fieldID) {
	if(!obj) {
		printf("[JNI GetObjectField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetObjectField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetObjectField(this,obj,fieldID);
    }
    jboolean GetBooleanField(jobject obj, jfieldID fieldID) {
	if(!obj) {
		printf("[JNI GetBooleanField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetBooleanField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetBooleanField(this,obj,fieldID);
    }
    jbyte GetByteField(jobject obj, jfieldID fieldID) {
	if(!obj) {
		printf("[JNI GetByteField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetByteField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetByteField(this,obj,fieldID);
    }
    jchar GetCharField(jobject obj, jfieldID fieldID) {
	if(!obj) {
		printf("[JNI GetCharField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetCharField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetCharField(this,obj,fieldID);
    }
    jshort GetShortField(jobject obj, jfieldID fieldID) {
	if(!obj) {
		printf("[JNI GetShortField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetShortField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetShortField(this,obj,fieldID);
    }
    jint GetIntField(jobject obj, jfieldID fieldID) {
	if(!obj) {
		printf("[JNI GetIntField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetIntField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetIntField(this,obj,fieldID);
    }
    jlong GetLongField(jobject obj, jfieldID fieldID) {
	if(!obj) {
		printf("[JNI GetLongField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetLongField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetLongField(this,obj,fieldID);
    }
    jfloat GetFloatField(jobject obj, jfieldID fieldID) {
	if(!obj) {
		printf("[JNI GetFloatField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetFloatField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetFloatField(this,obj,fieldID);
    }
    jdouble GetDoubleField(jobject obj, jfieldID fieldID) {
	if(!obj) {
		printf("[JNI GetDoubleField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetDoubleField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetDoubleField(this,obj,fieldID);
    }

    void SetObjectField(jobject obj, jfieldID fieldID, jobject val) {
	if(!obj) {
		printf("[JNI SetObjectField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetObjectField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
	if(!val) {
		printf("[JNI SetObjectField] val parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetObjectField(this,obj,fieldID,val);
    }
    void SetBooleanField(jobject obj, jfieldID fieldID,
                         jboolean val) {
	if(!obj) {
		printf("[JNI SetBooleanField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetBooleanField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetBooleanField(this,obj,fieldID,val);
    }
    void SetByteField(jobject obj, jfieldID fieldID,
                      jbyte val) {
	if(!obj) {
		printf("[JNI SetByteField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetByteField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetByteField(this,obj,fieldID,val);
    }
    void SetCharField(jobject obj, jfieldID fieldID,
                      jchar val) {
	if(!obj) {
		printf("[JNI SetCharField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetCharField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetCharField(this,obj,fieldID,val);
    }
    void SetShortField(jobject obj, jfieldID fieldID,
                       jshort val) {
	if(!obj) {
		printf("[JNI SetShortField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetShortField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetShortField(this,obj,fieldID,val);
    }
    void SetIntField(jobject obj, jfieldID fieldID,
                     jint val) {
	if(!obj) {
		printf("[JNI SetIntField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetIntField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetIntField(this,obj,fieldID,val);
    }
    void SetLongField(jobject obj, jfieldID fieldID,
                      jlong val) {
	if(!obj) {
		printf("[JNI SetLongField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetLongField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetLongField(this,obj,fieldID,val);
    }
    void SetFloatField(jobject obj, jfieldID fieldID,
                       jfloat val) {
	if(!obj) {
		printf("[JNI SetFloatField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetFloatField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetFloatField(this,obj,fieldID,val);
    }
    void SetDoubleField(jobject obj, jfieldID fieldID,
                        jdouble val) {
	if(!obj) {
		printf("[JNI SetDoubleField] obj parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetDoubleField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetDoubleField(this,obj,fieldID,val);
    }

    jmethodID GetStaticMethodID(jclass clazz, const char *name,
                                const char *sig) {
	if(!clazz) {
		printf("[JNI GetStaticMethodID] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!name) {
		printf("[JNI GetStaticMethodID] name parameter: null-pointer\n");
		exit(-1);
	}
	if(!sig) {
		printf("[JNI GetStaticMethodID] sig parameter: null-pointer\n");
		exit(-1);
	}
	Java_JNI_init();
        const char* clz_name = class_map[clazz].c_str();
        auto func_vector = static_func_map[clz_name];

        for(auto iter : func_vector){
                if((strcmp(iter.first.c_str(),name) == 0) && (strcmp(iter.second.c_str(),sig) == 0)){
                        return functions->GetStaticMethodID(this,clazz,name,sig);
                }
        }
        printf("[JNI GetStaticMethodID] java static method name: %s, sig: %s doesn't exist in java class %s \n", name, sig, clz_name);
        exit(-1);
    }

    jobject CallStaticObjectMethod(jclass clazz, jmethodID methodID,
                             ...) {
	if(!clazz) {
		printf("[JNI CallStaticObjectMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticObjectMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jobject result;
        va_start(args,methodID);
        result = functions->CallStaticObjectMethodV(this,clazz,methodID,args);
        va_end(args);
        return result;
    }
    jobject CallStaticObjectMethodV(jclass clazz, jmethodID methodID,
                              va_list args) {
	if(!clazz) {
		printf("[JNI CallStaticObjectMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticObjectMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticObjectMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticObjectMethodV(this,clazz,methodID,args);
    }
    jobject CallStaticObjectMethodA(jclass clazz, jmethodID methodID,
                              const jvalue *args) {
	if(!clazz) {
		printf("[JNI CallStaticObjectMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticObjectMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticObjectMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticObjectMethodA(this,clazz,methodID,args);
    }

    jboolean CallStaticBooleanMethod(jclass clazz,
                                     jmethodID methodID, ...) {
	if(!clazz) {
		printf("[JNI CallStaticBooleanMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticBooleanMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jboolean result;
        va_start(args,methodID);
        result = functions->CallStaticBooleanMethodV(this,clazz,methodID,args);
        va_end(args);
        return result;
    }
    jboolean CallStaticBooleanMethodV(jclass clazz,
                                      jmethodID methodID, va_list args) {
	if(!clazz) {
		printf("[JNI CallStaticBooleanMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticBooleanMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticBooleanMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticBooleanMethodV(this,clazz,methodID,args);
    }
    jboolean CallStaticBooleanMethodA(jclass clazz,
                                      jmethodID methodID, const jvalue *args) {
	if(!clazz) {
		printf("[JNI CallStaticBooleanMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticBooleanMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticBooleanMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticBooleanMethodA(this,clazz,methodID,args);
    }

    jbyte CallStaticByteMethod(jclass clazz,
                               jmethodID methodID, ...) {
	if(!clazz) {
		printf("[JNI CallStaticByteMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticByteMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jbyte result;
        va_start(args,methodID);
        result = functions->CallStaticByteMethodV(this,clazz,methodID,args);
        va_end(args);
        return result;
    }
    jbyte CallStaticByteMethodV(jclass clazz,
                                jmethodID methodID, va_list args) {
	if(!clazz) {
		printf("[JNI CallStaticByteMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticByteMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticByteMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticByteMethodV(this,clazz,methodID,args);
    }
    jbyte CallStaticByteMethodA(jclass clazz,
                                jmethodID methodID, const jvalue *args) {
	if(!clazz) {
		printf("[JNI CallStaticByteMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticByteMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticByteMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticByteMethodA(this,clazz,methodID,args);
    }

    jchar CallStaticCharMethod(jclass clazz,
                               jmethodID methodID, ...) {
	if(!clazz) {
		printf("[JNI CallStaticCharMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticCharMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jchar result;
        va_start(args,methodID);
        result = functions->CallStaticCharMethodV(this,clazz,methodID,args);
        va_end(args);
        return result;
    }
    jchar CallStaticCharMethodV(jclass clazz,
                                jmethodID methodID, va_list args) {
	if(!clazz) {
		printf("[JNI CallStaticCharMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticCharMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticCharMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticCharMethodV(this,clazz,methodID,args);
    }
    jchar CallStaticCharMethodA(jclass clazz,
                                jmethodID methodID, const jvalue *args) {
	if(!clazz) {
		printf("[JNI CallStaticCharMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticCharMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticCharMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticCharMethodA(this,clazz,methodID,args);
    }

    jshort CallStaticShortMethod(jclass clazz,
                                 jmethodID methodID, ...) {
	if(!clazz) {
		printf("[JNI CallStaticShortMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticShortMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jshort result;
        va_start(args,methodID);
        result = functions->CallStaticShortMethodV(this,clazz,methodID,args);
        va_end(args);
        return result;
    }
    jshort CallStaticShortMethodV(jclass clazz,
                                  jmethodID methodID, va_list args) {
	if(!clazz) {
		printf("[JNI CallStaticShortMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticShortMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticShortMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticShortMethodV(this,clazz,methodID,args);
    }
    jshort CallStaticShortMethodA(jclass clazz,
                                  jmethodID methodID, const jvalue *args) {
	if(!clazz) {
		printf("[JNI CallStaticShortMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticShortMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticShortMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticShortMethodA(this,clazz,methodID,args);
    }

    jint CallStaticIntMethod(jclass clazz,
                             jmethodID methodID, ...) {
	if(!clazz) {
		printf("[JNI CallStaticIntMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticIntMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jint result;
        va_start(args,methodID);
        result = functions->CallStaticIntMethodV(this,clazz,methodID,args);
        va_end(args);
        return result;
    }
    jint CallStaticIntMethodV(jclass clazz,
                              jmethodID methodID, va_list args) {
	if(!clazz) {
		printf("[JNI CallStaticIntMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticIntMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticIntMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticIntMethodV(this,clazz,methodID,args);
    }
    jint CallStaticIntMethodA(jclass clazz,
                              jmethodID methodID, const jvalue *args) {
	if(!clazz) {
		printf("[JNI CallStaticIntMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticIntMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticIntMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticIntMethodA(this,clazz,methodID,args);
    }

    jlong CallStaticLongMethod(jclass clazz,
                               jmethodID methodID, ...) {
	if(!clazz) {
		printf("[JNI CallStaticLongMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticLongMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jlong result;
        va_start(args,methodID);
        result = functions->CallStaticLongMethodV(this,clazz,methodID,args);
        va_end(args);
        return result;
    }
    jlong CallStaticLongMethodV(jclass clazz,
                                jmethodID methodID, va_list args) {
	if(!clazz) {
		printf("[JNI CallStaticLongMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticLongMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticLongMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticLongMethodV(this,clazz,methodID,args);
    }
    jlong CallStaticLongMethodA(jclass clazz,
                                jmethodID methodID, const jvalue *args) {
	if(!clazz) {
		printf("[JNI CallStaticLongMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticLongMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticLongMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticLongMethodA(this,clazz,methodID,args);
    }

    jfloat CallStaticFloatMethod(jclass clazz,
                                 jmethodID methodID, ...) {
	if(!clazz) {
		printf("[JNI CallStaticFloatMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticFloatMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jfloat result;
        va_start(args,methodID);
        result = functions->CallStaticFloatMethodV(this,clazz,methodID,args);
        va_end(args);
        return result;
    }
    jfloat CallStaticFloatMethodV(jclass clazz,
                                  jmethodID methodID, va_list args) {
	if(!clazz) {
		printf("[JNI CallStaticFloatMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticFloatMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticFloatMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticFloatMethodV(this,clazz,methodID,args);
    }
    jfloat CallStaticFloatMethodA(jclass clazz,
                                  jmethodID methodID, const jvalue *args) {
	if(!clazz) {
		printf("[JNI CallStaticFloatMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticFloatMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticFloatMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticFloatMethodA(this,clazz,methodID,args);
    }

    jdouble CallStaticDoubleMethod(jclass clazz,
                                   jmethodID methodID, ...) {
	if(!clazz) {
		printf("[JNI CallStaticDoubleMethod] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticDoubleMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        jdouble result;
        va_start(args,methodID);
        result = functions->CallStaticDoubleMethodV(this,clazz,methodID,args);
        va_end(args);
        return result;
    }
    jdouble CallStaticDoubleMethodV(jclass clazz,
                                    jmethodID methodID, va_list args) {
	if(!clazz) {
		printf("[JNI CallStaticDoubleMethodV] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticDoubleMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticDoubleMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticDoubleMethodV(this,clazz,methodID,args);
    }
    jdouble CallStaticDoubleMethodA(jclass clazz,
                                    jmethodID methodID, const jvalue *args) {
	if(!clazz) {
		printf("[JNI CallStaticDoubleMethodA] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticDoubleMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticDoubleMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        return functions->CallStaticDoubleMethodA(this,clazz,methodID,args);
    }

    void CallStaticVoidMethod(jclass cls, jmethodID methodID, ...) {
	if(!cls) {
		printf("[JNI CallStaticVoidMethod] cls parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticVoidMethod] methodID parameter: null-pointer\n");
		exit(-1);
	}
        va_list args;
        va_start(args,methodID);
        functions->CallStaticVoidMethodV(this,cls,methodID,args);
        va_end(args);
    }
    void CallStaticVoidMethodV(jclass cls, jmethodID methodID,
                               va_list args) {
	if(!cls) {
		printf("[JNI CallStaticVoidMethodV] cls parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticVoidMethodV] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticVoidMethodV] args parameter: null-pointer\n");
		exit(-1);
	}
        functions->CallStaticVoidMethodV(this,cls,methodID,args);
    }
    void CallStaticVoidMethodA(jclass cls, jmethodID methodID,
                               const jvalue * args) {
	if(!cls) {
		printf("[JNI CallStaticVoidMethodA] cls parameter: null-pointer\n");
		exit(-1);
	}
	if(!methodID) {
		printf("[JNI CallStaticVoidMethodA] methodID parameter: null-pointer\n");
		exit(-1);
	}
	if(!args) {
		printf("[JNI CallStaticVoidMethodA] args parameter: null-pointer\n");
		exit(-1);
	}
        functions->CallStaticVoidMethodA(this,cls,methodID,args);
    }

    jfieldID GetStaticFieldID(jclass clazz, const char *name,
                              const char *sig) {
	if(!clazz) {
		printf("[JNI GetStaticFieldID] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!name) {
		printf("[JNI GetStaticFieldID] name parameter: null-pointer\n");
		exit(-1);
	}
	if(!sig) {
		printf("[JNI GetStaticFieldID] sig parameter: null-pointer\n");
		exit(-1);
	}
	Java_JNI_init();
        const char* clz_name = class_map[clazz].c_str();
        auto field_vector = static_field_map[clz_name];

        for(auto iter : field_vector){
                if((strcmp(iter.first.c_str(),name) == 0) && (strcmp(iter.second.c_str(),sig) == 0)){
                        return functions->GetStaticFieldID(this,clazz,name,sig);
                }
        }
        printf("[JNI GetStaticFieldID] java static field name: %s, sig: %s doesn't exist in java class %s \n", name, sig, clz_name);
        exit(-1);
    }
    jobject GetStaticObjectField(jclass clazz, jfieldID fieldID) {
	if(!clazz) {
		printf("[JNI GetStaticObjectField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetStaticObjectField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetStaticObjectField(this,clazz,fieldID);
    }
    jboolean GetStaticBooleanField(jclass clazz, jfieldID fieldID) {
	if(!clazz) {
		printf("[JNI GetStaticBooleanField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetStaticBooleanField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetStaticBooleanField(this,clazz,fieldID);
    }
    jbyte GetStaticByteField(jclass clazz, jfieldID fieldID) {
	if(!clazz) {
		printf("[JNI GetStaticByteField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetStaticByteField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetStaticByteField(this,clazz,fieldID);
    }
    jchar GetStaticCharField(jclass clazz, jfieldID fieldID) {
	if(!clazz) {
		printf("[JNI GetStaticCharField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetStaticCharField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetStaticCharField(this,clazz,fieldID);
    }
    jshort GetStaticShortField(jclass clazz, jfieldID fieldID) {
	if(!clazz) {
		printf("[JNI GetStaticShortField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetStaticShortField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetStaticShortField(this,clazz,fieldID);
    }
    jint GetStaticIntField(jclass clazz, jfieldID fieldID) {
	if(!clazz) {
		printf("[JNI GetStaticIntField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetStaticIntField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetStaticIntField(this,clazz,fieldID);
    }
    jlong GetStaticLongField(jclass clazz, jfieldID fieldID) {
	if(!clazz) {
		printf("[JNI GetStaticLongField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetStaticLongField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetStaticLongField(this,clazz,fieldID);
    }
    jfloat GetStaticFloatField(jclass clazz, jfieldID fieldID) {
	if(!clazz) {
		printf("[JNI GetStaticFloatField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetStaticFloatField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetStaticFloatField(this,clazz,fieldID);
    }
    jdouble GetStaticDoubleField(jclass clazz, jfieldID fieldID) {
	if(!clazz) {
		printf("[JNI GetStaticDoubleField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI GetStaticDoubleField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetStaticDoubleField(this,clazz,fieldID);
    }

    void SetStaticObjectField(jclass clazz, jfieldID fieldID,
                        jobject value) {
	if(!clazz) {
		printf("[JNI SetStaticObjectField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetStaticObjectField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
	if(!value) {
		printf("[JNI SetStaticObjectField] value parameter: null-pointer\n");
		exit(-1);
	}
      functions->SetStaticObjectField(this,clazz,fieldID,value);
    }
    void SetStaticBooleanField(jclass clazz, jfieldID fieldID,
                        jboolean value) {
	if(!clazz) {
		printf("[JNI SetStaticBooleanField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetStaticBooleanField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
      functions->SetStaticBooleanField(this,clazz,fieldID,value);
    }
    void SetStaticByteField(jclass clazz, jfieldID fieldID,
                        jbyte value) {
	if(!clazz) {
		printf("[JNI SetStaticByteField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetStaticByteField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
      functions->SetStaticByteField(this,clazz,fieldID,value);
    }
    void SetStaticCharField(jclass clazz, jfieldID fieldID,
                        jchar value) {
	if(!clazz) {
		printf("[JNI SetStaticCharField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetStaticCharField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
      functions->SetStaticCharField(this,clazz,fieldID,value);
    }
    void SetStaticShortField(jclass clazz, jfieldID fieldID,
                        jshort value) {
	if(!clazz) {
		printf("[JNI SetStaticShortField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetStaticShortField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
      functions->SetStaticShortField(this,clazz,fieldID,value);
    }
    void SetStaticIntField(jclass clazz, jfieldID fieldID,
                        jint value) {
	if(!clazz) {
		printf("[JNI SetStaticIntField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetStaticIntField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
      functions->SetStaticIntField(this,clazz,fieldID,value);
    }
    void SetStaticLongField(jclass clazz, jfieldID fieldID,
                        jlong value) {
	if(!clazz) {
		printf("[JNI SetStaticLongField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetStaticLongField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
      functions->SetStaticLongField(this,clazz,fieldID,value);
    }
    void SetStaticFloatField(jclass clazz, jfieldID fieldID,
                        jfloat value) {
	if(!clazz) {
		printf("[JNI SetStaticFloatField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetStaticFloatField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
      functions->SetStaticFloatField(this,clazz,fieldID,value);
    }
    void SetStaticDoubleField(jclass clazz, jfieldID fieldID,
                        jdouble value) {
	if(!clazz) {
		printf("[JNI SetStaticDoubleField] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!fieldID) {
		printf("[JNI SetStaticDoubleField] fieldID parameter: null-pointer\n");
		exit(-1);
	}
      functions->SetStaticDoubleField(this,clazz,fieldID,value);
    }

    jstring NewString(const jchar *unicode, jsize len) {
	if(!unicode) {
		printf("[JNI NewString] unicode parameter: null-pointer\n");
		exit(-1);
	}
        return functions->NewString(this,unicode,len);
    }
    jsize GetStringLength(jstring str) {
	if(!str) {
		printf("[JNI GetStringLength] str parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetStringLength(this,str);
    }
    const jchar *GetStringChars(jstring str, jboolean *isCopy) {
	if(!str) {
		printf("[JNI GetStringChars] str parameter: null-pointer\n");
		exit(-1);
	}
	if(!isCopy) {
		printf("[JNI GetStringChars] isCopy parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetStringChars(this,str,isCopy);
    }
    void ReleaseStringChars(jstring str, const jchar *chars) {
	if(!str) {
		printf("[JNI ReleaseStringChars] str parameter: null-pointer\n");
		exit(-1);
	}
	if(!chars) {
		printf("[JNI ReleaseStringChars] chars parameter: null-pointer\n");
		exit(-1);
	}
        functions->ReleaseStringChars(this,str,chars);
    }

    jstring NewStringUTF(const char *utf) {
	if(!utf) {
		printf("[JNI NewStringUTF] utf parameter: null-pointer\n");
		exit(-1);
	}
        return functions->NewStringUTF(this,utf);
    }
    jsize GetStringUTFLength(jstring str) {
	if(!str) {
		printf("[JNI GetStringUTFLength] str parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetStringUTFLength(this,str);
    }
    const char* GetStringUTFChars(jstring str, jboolean *isCopy) {
	if(!str) {
		printf("[JNI GetStringUTFChars] str parameter: null-pointer\n");
		exit(-1);
	}
	if(!isCopy) {
		printf("[JNI GetStringUTFChars] isCopy parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetStringUTFChars(this,str,isCopy);
    }
    void ReleaseStringUTFChars(jstring str, const char* chars) {
	if(!str) {
		printf("[JNI ReleaseStringUTFChars] str parameter: null-pointer\n");
		exit(-1);
	}
	if(!chars) {
		printf("[JNI ReleaseStringUTFChars] chars parameter: null-pointer\n");
		exit(-1);
	}
        functions->ReleaseStringUTFChars(this,str,chars);
    }

    jsize GetArrayLength(jarray array) {
	if(!array) {
		printf("[JNI GetArrayLength] array parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetArrayLength(this,array);
    }

    jobjectArray NewObjectArray(jsize len, jclass clazz,
                                jobject init) {
	if(!clazz) {
		printf("[JNI NewObjectArray] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!init) {
		printf("[JNI NewObjectArray] init parameter: null-pointer\n");
		exit(-1);
	}
        return functions->NewObjectArray(this,len,clazz,init);
    }
    jobject GetObjectArrayElement(jobjectArray array, jsize index) {
	if(!array) {
		printf("[JNI GetObjectArrayElement] array parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetObjectArrayElement(this,array,index);
    }
    void SetObjectArrayElement(jobjectArray array, jsize index,
                               jobject val) {
	if(!array) {
		printf("[JNI SetObjectArrayElement] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!val) {
		printf("[JNI SetObjectArrayElement] val parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetObjectArrayElement(this,array,index,val);
    }

    jbooleanArray NewBooleanArray(jsize len) {
        return functions->NewBooleanArray(this,len);
    }
    jbyteArray NewByteArray(jsize len) {
        return functions->NewByteArray(this,len);
    }
    jcharArray NewCharArray(jsize len) {
        return functions->NewCharArray(this,len);
    }
    jshortArray NewShortArray(jsize len) {
        return functions->NewShortArray(this,len);
    }
    jintArray NewIntArray(jsize len) {
        return functions->NewIntArray(this,len);
    }
    jlongArray NewLongArray(jsize len) {
        return functions->NewLongArray(this,len);
    }
    jfloatArray NewFloatArray(jsize len) {
        return functions->NewFloatArray(this,len);
    }
    jdoubleArray NewDoubleArray(jsize len) {
        return functions->NewDoubleArray(this,len);
    }

    jboolean * GetBooleanArrayElements(jbooleanArray array, jboolean *isCopy) {
	if(!array) {
		printf("[JNI GetBooleanArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!isCopy) {
		printf("[JNI GetBooleanArrayElements] isCopy parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetBooleanArrayElements(this,array,isCopy);
    }
    jbyte * GetByteArrayElements(jbyteArray array, jboolean *isCopy) {
	if(!array) {
		printf("[JNI GetByteArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!isCopy) {
		printf("[JNI GetByteArrayElements] isCopy parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetByteArrayElements(this,array,isCopy);
    }
    jchar * GetCharArrayElements(jcharArray array, jboolean *isCopy) {
	if(!array) {
		printf("[JNI GetCharArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!isCopy) {
		printf("[JNI GetCharArrayElements] isCopy parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetCharArrayElements(this,array,isCopy);
    }
    jshort * GetShortArrayElements(jshortArray array, jboolean *isCopy) {
	if(!array) {
		printf("[JNI GetShortArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!isCopy) {
		printf("[JNI GetShortArrayElements] isCopy parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetShortArrayElements(this,array,isCopy);
    }
    jint * GetIntArrayElements(jintArray array, jboolean *isCopy) {
	if(!array) {
		printf("[JNI GetIntArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!isCopy) {
		printf("[JNI GetIntArrayElements] isCopy parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetIntArrayElements(this,array,isCopy);
    }
    jlong * GetLongArrayElements(jlongArray array, jboolean *isCopy) {
	if(!array) {
		printf("[JNI GetLongArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!isCopy) {
		printf("[JNI GetLongArrayElements] isCopy parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetLongArrayElements(this,array,isCopy);
    }
    jfloat * GetFloatArrayElements(jfloatArray array, jboolean *isCopy) {
	if(!array) {
		printf("[JNI GetFloatArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!isCopy) {
		printf("[JNI GetFloatArrayElements] isCopy parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetFloatArrayElements(this,array,isCopy);
    }
    jdouble * GetDoubleArrayElements(jdoubleArray array, jboolean *isCopy) {
	if(!array) {
		printf("[JNI GetDoubleArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!isCopy) {
		printf("[JNI GetDoubleArrayElements] isCopy parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetDoubleArrayElements(this,array,isCopy);
    }

    void ReleaseBooleanArrayElements(jbooleanArray array,
                                     jboolean *elems,
                                     jint mode) {
	if(!array) {
		printf("[JNI ReleaseBooleanArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!elems) {
		printf("[JNI ReleaseBooleanArrayElements] elems parameter: null-pointer\n");
		exit(-1);
	}
        functions->ReleaseBooleanArrayElements(this,array,elems,mode);
    }
    void ReleaseByteArrayElements(jbyteArray array,
                                  jbyte *elems,
                                  jint mode) {
	if(!array) {
		printf("[JNI ReleaseByteArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!elems) {
		printf("[JNI ReleaseByteArrayElements] elems parameter: null-pointer\n");
		exit(-1);
	}
        functions->ReleaseByteArrayElements(this,array,elems,mode);
    }
    void ReleaseCharArrayElements(jcharArray array,
                                  jchar *elems,
                                  jint mode) {
	if(!array) {
		printf("[JNI ReleaseCharArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!elems) {
		printf("[JNI ReleaseCharArrayElements] elems parameter: null-pointer\n");
		exit(-1);
	}
        functions->ReleaseCharArrayElements(this,array,elems,mode);
    }
    void ReleaseShortArrayElements(jshortArray array,
                                   jshort *elems,
                                   jint mode) {
	if(!array) {
		printf("[JNI ReleaseShortArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!elems) {
		printf("[JNI ReleaseShortArrayElements] elems parameter: null-pointer\n");
		exit(-1);
	}
        functions->ReleaseShortArrayElements(this,array,elems,mode);
    }
    void ReleaseIntArrayElements(jintArray array,
                                 jint *elems,
                                 jint mode) {
	if(!array) {
		printf("[JNI ReleaseIntArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!elems) {
		printf("[JNI ReleaseIntArrayElements] elems parameter: null-pointer\n");
		exit(-1);
	}
        functions->ReleaseIntArrayElements(this,array,elems,mode);
    }
    void ReleaseLongArrayElements(jlongArray array,
                                  jlong *elems,
                                  jint mode) {
	if(!array) {
		printf("[JNI ReleaseLongArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!elems) {
		printf("[JNI ReleaseLongArrayElements] elems parameter: null-pointer\n");
		exit(-1);
	}
        functions->ReleaseLongArrayElements(this,array,elems,mode);
    }
    void ReleaseFloatArrayElements(jfloatArray array,
                                   jfloat *elems,
                                   jint mode) {
	if(!array) {
		printf("[JNI ReleaseFloatArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!elems) {
		printf("[JNI ReleaseFloatArrayElements] elems parameter: null-pointer\n");
		exit(-1);
	}
        functions->ReleaseFloatArrayElements(this,array,elems,mode);
    }
    void ReleaseDoubleArrayElements(jdoubleArray array,
                                    jdouble *elems,
                                    jint mode) {
	if(!array) {
		printf("[JNI ReleaseDoubleArrayElements] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!elems) {
		printf("[JNI ReleaseDoubleArrayElements] elems parameter: null-pointer\n");
		exit(-1);
	}
        functions->ReleaseDoubleArrayElements(this,array,elems,mode);
    }

    void GetBooleanArrayRegion(jbooleanArray array,
                               jsize start, jsize len, jboolean *buf) {
	if(!array) {
		printf("[JNI GetBooleanArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI GetBooleanArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->GetBooleanArrayRegion(this,array,start,len,buf);
    }
    void GetByteArrayRegion(jbyteArray array,
                            jsize start, jsize len, jbyte *buf) {
	if(!array) {
		printf("[JNI GetByteArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI GetByteArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->GetByteArrayRegion(this,array,start,len,buf);
    }
    void GetCharArrayRegion(jcharArray array,
                            jsize start, jsize len, jchar *buf) {
	if(!array) {
		printf("[JNI GetCharArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI GetCharArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->GetCharArrayRegion(this,array,start,len,buf);
    }
    void GetShortArrayRegion(jshortArray array,
                             jsize start, jsize len, jshort *buf) {
	if(!array) {
		printf("[JNI GetShortArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI GetShortArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->GetShortArrayRegion(this,array,start,len,buf);
    }
    void GetIntArrayRegion(jintArray array,
                           jsize start, jsize len, jint *buf) {
	if(!array) {
		printf("[JNI GetIntArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI GetIntArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->GetIntArrayRegion(this,array,start,len,buf);
    }
    void GetLongArrayRegion(jlongArray array,
                            jsize start, jsize len, jlong *buf) {
	if(!array) {
		printf("[JNI GetLongArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI GetLongArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->GetLongArrayRegion(this,array,start,len,buf);
    }
    void GetFloatArrayRegion(jfloatArray array,
                             jsize start, jsize len, jfloat *buf) {
	if(!array) {
		printf("[JNI GetFloatArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI GetFloatArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->GetFloatArrayRegion(this,array,start,len,buf);
    }
    void GetDoubleArrayRegion(jdoubleArray array,
                              jsize start, jsize len, jdouble *buf) {
	if(!array) {
		printf("[JNI GetDoubleArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI GetDoubleArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->GetDoubleArrayRegion(this,array,start,len,buf);
    }

    void SetBooleanArrayRegion(jbooleanArray array, jsize start, jsize len,
                               const jboolean *buf) {
	if(!array) {
		printf("[JNI SetBooleanArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI SetBooleanArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetBooleanArrayRegion(this,array,start,len,buf);
    }
    void SetByteArrayRegion(jbyteArray array, jsize start, jsize len,
                            const jbyte *buf) {
	if(!array) {
		printf("[JNI SetByteArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI SetByteArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetByteArrayRegion(this,array,start,len,buf);
    }
    void SetCharArrayRegion(jcharArray array, jsize start, jsize len,
                            const jchar *buf) {
	if(!array) {
		printf("[JNI SetCharArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI SetCharArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetCharArrayRegion(this,array,start,len,buf);
    }
    void SetShortArrayRegion(jshortArray array, jsize start, jsize len,
                             const jshort *buf) {
	if(!array) {
		printf("[JNI SetShortArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI SetShortArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetShortArrayRegion(this,array,start,len,buf);
    }
    void SetIntArrayRegion(jintArray array, jsize start, jsize len,
                           const jint *buf) {
	if(!array) {
		printf("[JNI SetIntArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI SetIntArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetIntArrayRegion(this,array,start,len,buf);
    }
    void SetLongArrayRegion(jlongArray array, jsize start, jsize len,
                            const jlong *buf) {
	if(!array) {
		printf("[JNI SetLongArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI SetLongArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetLongArrayRegion(this,array,start,len,buf);
    }
    void SetFloatArrayRegion(jfloatArray array, jsize start, jsize len,
                             const jfloat *buf) {
	if(!array) {
		printf("[JNI SetFloatArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI SetFloatArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetFloatArrayRegion(this,array,start,len,buf);
    }
    void SetDoubleArrayRegion(jdoubleArray array, jsize start, jsize len,
                              const jdouble *buf) {
	if(!array) {
		printf("[JNI SetDoubleArrayRegion] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI SetDoubleArrayRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->SetDoubleArrayRegion(this,array,start,len,buf);
    }

    jint RegisterNatives(jclass clazz, const JNINativeMethod *methods,
                         jint nMethods) {
	if(!clazz) {
		printf("[JNI RegisterNatives] clazz parameter: null-pointer\n");
		exit(-1);
	}
	if(!methods) {
		printf("[JNI RegisterNatives] methods parameter: null-pointer\n");
		exit(-1);
	}
        return functions->RegisterNatives(this,clazz,methods,nMethods);
    }
    jint UnregisterNatives(jclass clazz) {
	if(!clazz) {
		printf("[JNI UnregisterNatives] clazz parameter: null-pointer\n");
		exit(-1);
	}
        return functions->UnregisterNatives(this,clazz);
    }

    jint MonitorEnter(jobject obj) {
	if(!obj) {
		printf("[JNI MonitorEnter] obj parameter: null-pointer\n");
		exit(-1);
	}
        return functions->MonitorEnter(this,obj);
    }
    jint MonitorExit(jobject obj) {
	if(!obj) {
		printf("[JNI MonitorExit] obj parameter: null-pointer\n");
		exit(-1);
	}
        return functions->MonitorExit(this,obj);
    }

    jint GetJavaVM(JavaVM **vm) {
	if(!vm) {
		printf("[JNI GetJavaVM] vm parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetJavaVM(this,vm);
    }

    void GetStringRegion(jstring str, jsize start, jsize len, jchar *buf) {
	if(!str) {
		printf("[JNI GetStringRegion] str parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI GetStringRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->GetStringRegion(this,str,start,len,buf);
    }
    void GetStringUTFRegion(jstring str, jsize start, jsize len, char *buf) {
	if(!str) {
		printf("[JNI GetStringUTFRegion] str parameter: null-pointer\n");
		exit(-1);
	}
	if(!buf) {
		printf("[JNI GetStringUTFRegion] buf parameter: null-pointer\n");
		exit(-1);
	}
        functions->GetStringUTFRegion(this,str,start,len,buf);
    }

    void * GetPrimitiveArrayCritical(jarray array, jboolean *isCopy) {
	if(!array) {
		printf("[JNI GetPrimitiveArrayCritical] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!isCopy) {
		printf("[JNI GetPrimitiveArrayCritical] isCopy parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetPrimitiveArrayCritical(this,array,isCopy);
    }
    void ReleasePrimitiveArrayCritical(jarray array, void *carray, jint mode) {
	if(!array) {
		printf("[JNI ReleasePrimitiveArrayCritical] array parameter: null-pointer\n");
		exit(-1);
	}
	if(!carray) {
		printf("[JNI ReleasePrimitiveArrayCritical] carray parameter: null-pointer\n");
		exit(-1);
	}
        functions->ReleasePrimitiveArrayCritical(this,array,carray,mode);
    }

    const jchar * GetStringCritical(jstring string, jboolean *isCopy) {
	if(!string) {
		printf("[JNI GetStringCritical] string parameter: null-pointer\n");
		exit(-1);
	}
	if(!isCopy) {
		printf("[JNI GetStringCritical] isCopy parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetStringCritical(this,string,isCopy);
    }
    void ReleaseStringCritical(jstring string, const jchar *cstring) {
	if(!string) {
		printf("[JNI ReleaseStringCritical] string parameter: null-pointer\n");
		exit(-1);
	}
	if(!cstring) {
		printf("[JNI ReleaseStringCritical] cstring parameter: null-pointer\n");
		exit(-1);
	}
        functions->ReleaseStringCritical(this,string,cstring);
    }

    jweak NewWeakGlobalRef(jobject obj) {
	if(!obj) {
		printf("[JNI NewWeakGlobalRef] obj parameter: null-pointer\n");
		exit(-1);
	}
        return functions->NewWeakGlobalRef(this,obj);
    }
    void DeleteWeakGlobalRef(jweak ref) {
	if(!ref) {
		printf("[JNI DeleteWeakGlobalRef] ref parameter: null-pointer\n");
		exit(-1);
	}
        functions->DeleteWeakGlobalRef(this,ref);
    }

    jboolean ExceptionCheck() {
        return functions->ExceptionCheck(this);
    }

    jobject NewDirectByteBuffer(void* address, jlong capacity) {
	if(!address) {
		printf("[JNI NewDirectByteBuffer] address parameter: null-pointer\n");
		exit(-1);
	}
        return functions->NewDirectByteBuffer(this, address, capacity);
    }
    void* GetDirectBufferAddress(jobject buf) {
	if(!buf) {
		printf("[JNI GetDirectBufferAddress] buf parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetDirectBufferAddress(this, buf);
    }
    jlong GetDirectBufferCapacity(jobject buf) {
	if(!buf) {
		printf("[JNI GetDirectBufferCapacity] buf parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetDirectBufferCapacity(this, buf);
    }
    jobjectRefType GetObjectRefType(jobject obj) {
	if(!obj) {
		printf("[JNI GetObjectRefType] obj parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetObjectRefType(this, obj);
    }

    /* Module Features */

    jobject GetModule(jclass clazz) {
	if(!clazz) {
		printf("[JNI GetModule] clazz parameter: null-pointer\n");
		exit(-1);
	}
        return functions->GetModule(this, clazz);
    }

#endif /* __cplusplus */
};

typedef struct JavaVMOption {
    char *optionString;
    void *extraInfo;
} JavaVMOption;

typedef struct JavaVMInitArgs {
    jint version;

    jint nOptions;
    JavaVMOption *options;
    jboolean ignoreUnrecognized;
} JavaVMInitArgs;

typedef struct JavaVMAttachArgs {
    jint version;

    char *name;
    jobject group;
} JavaVMAttachArgs;

/* These will be VM-specific. */

#define JDK1_2
#define JDK1_4

/* End VM-specific. */

struct JNIInvokeInterface_ {
    void *reserved0;
    void *reserved1;
    void *reserved2;

    jint (JNICALL *DestroyJavaVM)(JavaVM *vm);

    jint (JNICALL *AttachCurrentThread)(JavaVM *vm, void **penv, void *args);

    jint (JNICALL *DetachCurrentThread)(JavaVM *vm);

    jint (JNICALL *GetEnv)(JavaVM *vm, void **penv, jint version);

    jint (JNICALL *AttachCurrentThreadAsDaemon)(JavaVM *vm, void **penv, void *args);
};

struct JavaVM_ {
    const struct JNIInvokeInterface_ *functions;
#ifdef __cplusplus

    jint DestroyJavaVM() {
        return functions->DestroyJavaVM(this);
    }
    jint AttachCurrentThread(void **penv, void *args) {
        return functions->AttachCurrentThread(this, penv, args);
    }
    jint DetachCurrentThread() {
        return functions->DetachCurrentThread(this);
    }

    jint GetEnv(void **penv, jint version) {
        return functions->GetEnv(this, penv, version);
    }
    jint AttachCurrentThreadAsDaemon(void **penv, void *args) {
        return functions->AttachCurrentThreadAsDaemon(this, penv, args);
    }
#endif
};

#ifdef _JNI_IMPLEMENTATION_
#define _JNI_IMPORT_OR_EXPORT_ JNIEXPORT
#else
#define _JNI_IMPORT_OR_EXPORT_ JNIIMPORT
#endif
_JNI_IMPORT_OR_EXPORT_ jint JNICALL
JNI_GetDefaultJavaVMInitArgs(void *args);

_JNI_IMPORT_OR_EXPORT_ jint JNICALL
JNI_CreateJavaVM(JavaVM **pvm, void **penv, void *args);

_JNI_IMPORT_OR_EXPORT_ jint JNICALL
JNI_GetCreatedJavaVMs(JavaVM **, jsize, jsize *);

/* Defined by native libraries. */
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved);

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM *vm, void *reserved);

#define JNI_VERSION_1_1 0x00010001
#define JNI_VERSION_1_2 0x00010002
#define JNI_VERSION_1_4 0x00010004
#define JNI_VERSION_1_6 0x00010006
#define JNI_VERSION_1_8 0x00010008
#define JNI_VERSION_9   0x00090000
#define JNI_VERSION_10  0x000a0000

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !_JAVASOFT_JNI_H_ */
