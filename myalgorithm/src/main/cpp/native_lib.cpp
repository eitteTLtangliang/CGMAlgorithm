
#ifdef _WINDOWS
#include <string>
#include "native_lib.h"
#include "algorithm/header/cgm_algorithm.h"
#include "algorithm/header/native_blood_glucose_index.h"
#include "algorithm/header/native_algorithm_class.h"
#endif

#ifdef __ANDROID__
#include <jni.h>
#include <math.h>
#include <string>
#include <android/log.h>
#include "native_lib.h"
#include "algorithm/header/cgm_algorithm.h"
#include "algorithm/header/native_blood_glucose_index.h"
#include "native_algorithm_class.h"
#include "struct2json/cJSON/cJSON.h"
#include "struct2json/algorithmContext2Json.h"

#endif


jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = JNI_ERR;
    LOGD("#@===== JNI_OnLoad  start =====@#");
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }
    register_current_judgment_context_class(env);
    register_judgment_context_class(env);
    register_kalman_context_class(env);
    register_current_correction_context_class(env);
    register_filter_context_class(env);
    register_cal_baseline_context_class(env);
    register_clipping_filter_context_class(env);
    register_esa_context_class(env);
    register_cgm_calibration_context_class(env);
    register_regular_deconvolution_context_class(env);
    register_arrow_direction_context_class(env);
    register_algorithm_context_class(env);

    return JNI_VERSION_1_6;
}

extern "C" {

JNIEXPORT jstring JNICALL Java_com_algorithm_v1_11_10_NativeAlgorithmLibraryV1_11_10_getAlgorithmVersion(JNIEnv *env, jclass) {
    return env->NewStringUTF(get_algorithm_version());
}

JNIEXPORT jobject JNICALL Java_com_algorithm_v1_11_10_NativeAlgorithmLibraryV1_11_10_getAlgorithmContextFromNative(JNIEnv *env, jclass) {
    jni_algorithm_context_t m_algorithm_context;
    int ret = init_algorithm_context(&m_algorithm_context);
    if (ret == 0) {
        jobject java_algorithm_context = algorithm_context_c_to_java(env, &m_algorithm_context);
        return java_algorithm_context;
    }
    return NULL;
}

JNIEXPORT jdouble JNICALL Java_com_algorithm_v1_11_10_NativeAlgorithmLibraryV1_11_10_processAlgorithmConvert(JNIEnv *env, jclass, jobject m_algorithm_context, jint index, jdouble current_data, jdouble temperature_data, jdouble low_alarm_value, jdouble high_alarm_value) {
    jni_algorithm_context_t m_jni_algorithm_context;
    int error_status = 0;
    double cgm_data = 0.0;
    algorithm_context_java_to_c(env, m_algorithm_context, &m_jni_algorithm_context);
    cgm_data = algorithm_convert_process(&m_jni_algorithm_context, current_data, temperature_data, index, &error_status, low_alarm_value, high_alarm_value);
    algorithm_context_clone_c_to_java(env, &m_jni_algorithm_context, m_algorithm_context);
    return cgm_data;
}

JNIEXPORT jfloatArray JNICALL Java_com_algorithm_v1_11_10_NativeAlgorithmLibraryV1_11_10_getAGPFunction(JNIEnv *jniEnv, jclass, jfloatArray agps) {

    jfloat *p_data = (*jniEnv).GetFloatArrayElements(agps, NULL);
    jfloat *agp = Agp_value(p_data);

    int length = 288;
    jfloatArray jfloatArr = jniEnv->NewFloatArray(length);
    jsize len = jniEnv->GetArrayLength(jfloatArr);
    jniEnv->SetFloatArrayRegion(jfloatArr, 0, len, agp);

    return jfloatArr;
}

JNIEXPORT jfloat JNICALL Java_com_algorithm_v1_11_10_NativeAlgorithmLibraryV1_11_10_getGEFunction(JNIEnv *jniEnv, jclass , jfloatArray agp_data) {

    jfloat *p_data = (*jniEnv).GetFloatArrayElements(agp_data, NULL);
    jfloat ge = function_GE(p_data);

    return ge;
}

JNIEXPORT jfloat JNICALL Java_com_algorithm_v1_11_10_NativeAlgorithmLibraryV1_11_10_getIDRFunction(JNIEnv *jniEnv, jclass, jfloatArray agp_data10, jfloatArray agp_data90) {

    jfloat *p_data = (*jniEnv).GetFloatArrayElements(agp_data10, NULL);
    jfloat *p_data1 = (*jniEnv).GetFloatArrayElements(agp_data90, NULL);
    jfloat idr = function_IDR(p_data, p_data1);

    return idr;
}

JNIEXPORT jfloat JNICALL Java_com_algorithm_v1_11_10_NativeAlgorithmLibraryV1_11_10_getIQRFunction(JNIEnv *jniEnv, jclass , jfloatArray agp_data25, jfloatArray agp_data75) {

    jfloat *p_data = (*jniEnv).GetFloatArrayElements(agp_data25, NULL);
    jfloat *p_data1 = (*jniEnv).GetFloatArrayElements(agp_data75, NULL);
    jfloat iqr = function_IQR(p_data, p_data1);

    return iqr;
}

JNIEXPORT jfloat JNICALL Java_com_algorithm_v1_11_10_NativeAlgorithmLibraryV1_11_10_getCMFunction(JNIEnv *jniEnv, jclass, jfloatArray agp_data) {

    jfloat *p_data = (*jniEnv).GetFloatArrayElements(agp_data, NULL);
    jfloat cm = function_CM(p_data);

    return cm;
}

JNIEXPORT jfloat JNICALL Java_com_algorithm_v1_11_10_NativeAlgorithmLibraryV1_11_10_getLBGRFunction(JNIEnv *jniEnv, jclass, jfloatArray agp_data, jfloat defaultLow) {

    jfloat *p_data = (*jniEnv).GetFloatArrayElements(agp_data, NULL);
    jfloat lbgr = function_LBGR(p_data, defaultLow);

    return lbgr;
}

JNIEXPORT jfloat JNICALL Java_com_algorithm_v1_11_10_NativeAlgorithmLibraryV1_11_10_getHBGRFunction(JNIEnv *jniEnv, jclass, jfloatArray agp_data, jfloat defaultHigh) {

    jfloat *p_data = (*jniEnv).GetFloatArrayElements(agp_data, NULL);
    jfloat hbgr = function_HBGR(p_data, defaultHigh);

    return hbgr;
}

JNIEXPORT void JNICALL Java_com_algorithm_v1_11_10_NativeAlgorithmLibraryV1_11_10_resetAlgorithmContext(JNIEnv *env, jclass, jobject mAlgorithmContext) {

    jni_algorithm_context_t m_jni_algorithm_context;
    algorithm_context_java_to_c(env, mAlgorithmContext, &m_jni_algorithm_context);
    int ret = init_algorithm_context(&m_jni_algorithm_context);
    algorithm_context_clone_c_to_java(env, &m_jni_algorithm_context, mAlgorithmContext);
}

JNIEXPORT jstring JNICALL Java_com_algorithm_v1_11_10_NativeAlgorithmLibraryV1_11_10_getJsonAlgorithmContext(JNIEnv *env, jclass, jobject mAlgorithmContext) {

    jstring ret_json_buffer = NULL;
    jni_algorithm_context_t m_jni_algorithm_context;
    algorithm_context_java_to_c(env, mAlgorithmContext, &m_jni_algorithm_context);

    cJSON *p_json_algorithm =  struct_to_json(&m_jni_algorithm_context);
    if(p_json_algorithm != NULL) {
        char *algorithmChar = cJSON_Print(p_json_algorithm);
        if(algorithmChar != NULL) {
            ret_json_buffer = env->NewStringUTF(algorithmChar);
            free(algorithmChar);
        }
        s2j_delete_json_obj(p_json_algorithm);
    }

    return ret_json_buffer;
}

JNIEXPORT jint JNICALL Java_com_algorithm_v1_11_10_NativeAlgorithmLibraryV1_11_10_setJsonAlgorithmContext(JNIEnv *env,jclass,jobject mAlgorithmContext,jstring mJsonContext_) {

    const char *mJsonContext = env->GetStringUTFChars(mJsonContext_, 0);
    int ret = 0;

    if(mJsonContext != NULL){
        cJSON * localCJson = cJSON_Parse(mJsonContext);
        if(localCJson != NULL){
            jni_algorithm_context_t *p_jni_algorithm_context  = json_to_struct(localCJson);
            if(p_jni_algorithm_context != NULL){
                algorithm_context_clone_c_to_java(env, p_jni_algorithm_context, mAlgorithmContext);
                free(p_jni_algorithm_context);
                ret = 1;
            }
            s2j_delete_json_obj(localCJson);
        }
    }
    env->ReleaseStringUTFChars(mJsonContext_, mJsonContext);

    return ret;
}


}