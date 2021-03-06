#ifndef UTIL_H_
#define UTIL_H_

#include <jni.h>

#include "caffe/caffe.hpp"
#include "jni_exception.h"


#define EPSILON 1e-30

inline jfieldID getObjField(JNIEnv *env, jobject obj, const char *name, const char *sig) {
    jclass c = env->GetObjectClass(obj);
    return env->GetFieldID(c, name, sig);
}

template <typename T>
T* getInternalObject(JNIEnv *env, jobject obj) {
    jlong ptr = env->GetLongField(obj, getObjField(env, obj, "internalPtr", "J"));
    JNI_ASSERT(ptr != 0, "internalPtr was null");
    return reinterpret_cast<T *>(ptr);
}

template <typename T>
void setInternalPtr(JNIEnv *env, jobject obj, T *t) {
    jlong ptr = reinterpret_cast<jlong>(t);
    env->SetLongField(obj, getObjField(env, obj, "internalPtr", "J"), ptr);
}

template <typename Dtype>
caffe::Blob<Dtype>* cloneWithNewData(const caffe::Blob<Dtype>& old, Dtype* data) {
    caffe::Blob<Dtype> *clone = new caffe::Blob<Dtype>();
    clone->ReshapeLike(old);
    clone->set_cpu_data(data);
    return clone;
}

#endif
