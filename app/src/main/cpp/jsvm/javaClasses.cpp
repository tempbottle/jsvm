//
// Created by ntrrgc on 1/15/17.
//

#include "javaClasses.h"

namespace jsvm {
    jclass      Boolean_Class = NULL;
    jmethodID   Boolean_ctor = NULL;
    jfieldID    Boolean_value = NULL;

    jclass      Double_Class = NULL;
    jmethodID   Double_ctor = NULL;
    jfieldID    Double_value = NULL;

    jclass      JSVM_Class = NULL;
    jfieldID    JSVM_hPriv = NULL;

    jclass      JSVMInternalError_Class = NULL;
    jmethodID   JSVMInternalError_ctor = NULL;

    jclass      JSError_Class = NULL;
    jmethodID   JSError_ctor = NULL;

    jclass      IllegalArgumentException_Class = NULL;
    jmethodID   IllegalArgumentException_ctor = NULL;

    jclass      AttemptedToUseObjectFromOtherVM_Class = NULL;
    jmethodID   AttemptedToUseObjectFromOtherVM_ctor = NULL;

    jclass      JSValue_Class = NULL;
    jfieldID    JSValue_type = NULL;
    jfieldID    JSValue_value = NULL;

    jclass      JSObject_Class = NULL;
    jmethodID   JSObject_ctor = NULL;
    jfieldID    JSObject_jsVM = NULL;
    jfieldID    JSObject_handle = NULL;

    jclass      JSFunction_Class = NULL;
    jmethodID   JSFunction_ctor = NULL;
}

using namespace jsvm;

static jclass
findClass(JNIEnv *env, const char *name) {
    jclass tmpClassRef;

    tmpClassRef = env->FindClass(name);
    jclass ret = (jclass) env->NewGlobalRef(tmpClassRef);
    env->DeleteLocalRef(tmpClassRef);

    return ret;
}

static void
removeClass(JNIEnv *env, jclass *classRef) {
    if (*classRef != NULL) {
        env->DeleteGlobalRef(*classRef);
        *classRef = NULL;
    }
}

void ::jsvm::initClassesAndFields(JNIEnv *env) {
    Boolean_Class = findClass(env, "java/lang/Boolean");
    Boolean_ctor = env->GetMethodID(Boolean_Class, "<init>", "(Z)V");
    Boolean_value = env->GetFieldID(Boolean_Class, "value", "Z");

    Double_Class = findClass(env, "java/lang/Double");
    Double_ctor = env->GetMethodID(Double_Class, "<init>", "(D)V");
    Double_value = env->GetFieldID(Double_Class, "value", "D");

    JSVM_Class = findClass(env, "me/ntrrgc/jsvm/JSVM");
    JSVM_hPriv = env->GetFieldID(JSVM_Class, "hPriv", "J");

    JSVMInternalError_Class = findClass(env, "me/ntrrgc/jsvm/JSVMInternalError");
    JSVMInternalError_ctor = env->GetMethodID(JSVMInternalError_Class, "<init>",
                                              "(Ljava/lang/String;)V");

    JSError_Class = findClass(env, "me/ntrrgc/jsvm/JSError");
    JSError_ctor = env->GetMethodID(JSError_Class, "<init>",
                                    "(Lme/ntrrgc/jsvm/JSValue;)V");

    IllegalArgumentException_Class = findClass(env, "java/lang/IllegalArgumentException");
    IllegalArgumentException_ctor = env->GetMethodID(IllegalArgumentException_Class, "<init>",
                                                     "(Ljava/lang/String;)V");

    AttemptedToUseObjectFromOtherVM_Class = findClass(env, "me/ntrrgc/jsvm/AttemptedToUseObjectFromOtherVM");
    AttemptedToUseObjectFromOtherVM_ctor =
            env->GetMethodID(AttemptedToUseObjectFromOtherVM_Class,
                             "<init>",
                             "(Lme/ntrrgc/jsvm/JSObject;Lme/ntrrgc/jsvm/JSVM;)V");

    JSValue_Class = findClass(env, "me/ntrrgc/jsvm/JSValue");
    JSValue_type = env->GetFieldID(JSValue_Class, "type", "I");
    JSValue_value = env->GetFieldID(JSValue_Class, "value", "L" "java/lang/Object;");

    JSObject_Class = findClass(env, "me/ntrrgc/jsvm/JSObject");
    JSObject_ctor = env->GetMethodID(JSObject_Class, "<init>", "()V");
    JSObject_jsVM = env->GetFieldID(JSObject_Class, "jsVM", "L" "me/ntrrgc/jsvm/JSVM;");
    JSObject_handle = env->GetFieldID(JSObject_Class, "handle", "I");

    JSFunction_Class = findClass(env, "me/ntrrgc/jsvm/JSFunction");
    JSFunction_ctor = env->GetMethodID(JSFunction_Class, "<init>", "()V");
}


void ::jsvm::tearDownClassesAndFields(JNIEnv *env) {
    removeClass(env, &Boolean_Class);
    removeClass(env, &Double_Class);
    removeClass(env, &JSVM_Class);
    removeClass(env, &JSVMInternalError_Class);
    removeClass(env, &JSValue_Class);
    removeClass(env, &JSObject_Class);
}

