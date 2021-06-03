//
// Created by ml.gong on 2021/5/21.
//

#ifndef MYMODULESAPP_NATIVE_ALGORITHM_CLASS_H
#define MYMODULESAPP_NATIVE_ALGORITHM_CLASS_H

#include <jni.h>
#include <android/log.h>
#include "algorithm/header/cgm_algorithm.h"
#define LOG_TAG  "C_TAG"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

#define CLASS_ALGORITHM_PATH(X)     "com/algorithm/v1_1_0/"#X
#define LCLASS_ALGORITHM_PATH(X)    "Lcom/algorithm/v1_1_0/"#X";"
#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))


typedef struct data_current_judgment_context_t {
    jclass clazz;
    jfieldID last_current;
    jfieldID max_current;
    jfieldID abnormal_flag;
    jfieldID last_abnormal_flag;
    jfieldID temp_data_buf;
    jfieldID var_data;
    jfieldID con_count;
    jmethodID constructor;
} data_current_judgment_context;

typedef struct data_judgment_context_t {
    jclass clazz;
    jfieldID abnormal_flag_buf;
    jfieldID current_abnormal_flag_count;
    jfieldID abnormal_count;
    jfieldID mCurrentJudgmentContext;
    jmethodID constructor;
}data_judgment_context;

typedef struct data_kalman_context_t {
    jclass clazz;
    jfieldID mStateKalman;
    jfieldID mStatePre;
    jfieldID mPminus;
    jfieldID mK;
    jfieldID mR;
    jfieldID mQ;
    jfieldID mP;
    jmethodID constructor;
} data_kalman_context;

typedef struct data_current_correction_context_t {
    jclass clazz;
    jfieldID mS;
    jfieldID mLastS;
    jfieldID mSFlag;
    jfieldID mD0;
    jfieldID mSs0;
    jfieldID mTimeWindows;
    jfieldID mTimeWindows1;
    jmethodID constructor;
}data_current_correction_context;

typedef struct data_filter1_context_t {
    jclass clazz;
    jfieldID m_filter_data;
    jfieldID m_temp_data;
    jfieldID m_a_data;
    jfieldID m_b_data;
    jmethodID constructor;
}data_filter1_context;

typedef struct data_cal_baseline_context_t {
    jclass clazz;
    jfieldID fasting_continue_count;
    jfieldID fasting_min_data;
    jfieldID last_fasting_min_data;
    jfieldID temp_fasting_min_index;
    jfieldID last_fasting_min_index;
    jfieldID fasting_max_index;
    jfieldID fasting_min_index;
    jfieldID fasting_max_data;
    jfieldID fasting_continue_count_sum;
    jfieldID fasting_continue_count_avg;
    jfieldID fasting_continue_data_sum;
    jfieldID fasting_continue_data_avg;
    jfieldID fasting_count;

    jfieldID last_trend_data_count;

    jfieldID temp_mean_baseline;
    jfieldID baseline_value;
    jfieldID last_baseline_value;
    jfieldID last_last_baseline_value;

    jfieldID last_data;
    jfieldID last_last_data;
    jfieldID fasting_min_sum;
    jfieldID fasting_min_avg;

    jfieldID flag_index;
    jfieldID fasting_min_data_count;
    jfieldID last_fasting_index;
    jfieldID fasting_min_value;
    jfieldID fasting_min_data_sum;
    jfieldID fasting_min_data_avg;
    jfieldID last_sf_data;
    jfieldID  max_point_data;
    jmethodID constructor;
}data_cal_baseline_context;

typedef struct data_clipping_filter_context_t {
    jclass clazz;
    jfieldID error_flag;
    jfieldID short_ESA_flag;

    jfieldID count;
    jfieldID last_min_data;
    jfieldID min_data;
    jfieldID continue_down_count;
    jfieldID continue_down_flag;
    jfieldID continue_down_max_data;
    jfieldID last_continue_down_max_data;
    jfieldID continue_down_min_data;

    jfieldID CGM_var_windows;
    jfieldID CGM_var_data;
    jfieldID var_data_count;
    jfieldID min_data_buf;
    jfieldID data_count;
    jfieldID seven_point_index;
    jfieldID data_count0_max;
    jfieldID data_count0;
    jfieldID slope;
    jfieldID up_continue_count;
    jfieldID min_data_count;
    jfieldID up_min_data;

    jfieldID sf4_buf;
    jfieldID sf4_min_data;
    jfieldID sf4_min_data_index;


    jfieldID Daily_minimum_value;
    jfieldID last_Daily_minimum_value;
    jfieldID Daily_minimum_value_count;
    jfieldID Daily_minimum_value_sum;
    jfieldID Daily_minimum_value_avg;
    jfieldID max_data;

    jfieldID  ret_tmp_data;
    jmethodID constructor;
}data_clipping_filter_context;

typedef struct data_esa_compensate_context_t {
    jclass clazz;
    jfieldID k_data;

    jfieldID ESA_min_data;
    jfieldID ESA_flag;
    jfieldID ESA_sum;
    jfieldID ESA_average;
    jfieldID baseline;

    jfieldID b1_data;
    jfieldID data_12;

    jfieldID fit10_x;
    jfieldID fit10_y;        //存放用于线性回归的电流值
    jfieldID fit36_x;        //存放用于线性回归的数据的下标数组
    jfieldID fit36_y;        //存放用于线性回归的电流值


    jfieldID last_mean_data;
    jfieldID continue_mean_count;
    jfieldID bl_last_data;
    jfieldID bl_last_last_data;
    jfieldID bl_min_flag;

    jfieldID last_baseline_cgm;
    jfieldID slowly_chang_value;
    jfieldID deferred_compensation_flag;
    jfieldID deferred_compensation_count;
    jfieldID baseline_chang_value;

    jmethodID constructor;
}data_esa_compensate_context;

typedef struct data_cgm_calibration_context_t {
    jclass clazz;
    jfieldID calibration_flag;
    jfieldID bg_index;
    jfieldID last_bg;
    jfieldID last_sf4_data;
    jfieldID last_last_sf4_data;
    jmethodID constructor;
}data_cgm_calibration_context;

typedef struct data_regular_deconvolution_context_t {
    jclass clazz;
    jfieldID ig_value_buf;
    jmethodID constructor;
}data_regular_deconvolution_context;

typedef struct data_arrow_direction_context_t {
    jclass clazz;
    jfieldID blood_glucose_trend;
    jfieldID last_blood_glucose_trend;
    jfieldID arrow_direction_data;
    jfieldID last_arrow_direction_data;
    jfieldID last_last_arrow_direction_data;
    jfieldID rise_trend_count;
    jfieldID decline_trend_count;
    jfieldID horizontal_direction_count;
    jfieldID arrow_direction_count;
    jmethodID constructor;
}data_arrow_direction_context;

typedef struct data_algorithm_context_t {
    jclass clazz;
    jfieldID esa_calibration_enable;
    jfieldID finger_blood_calibration_enable;
    jfieldID version_name;
    jfieldID IG_data;
    jfieldID last_IG_data;
    jfieldID cgm_warning;
    jfieldID cgm_current_abnormal;
    jfieldID cgm_temp_abnormal;
    jfieldID cgm_blood_glucose_trend;
    jfieldID mJudgmentContext;
    jfieldID mCurrentCorrectionContext;
    jfieldID mKalmanContext;
    jfieldID mFilter1Context;
    jfieldID mFilter2Context;
    jfieldID mCalBaselineContext;
    jfieldID mClippingFilterContext;
    jfieldID mESACompensateContext;
    jfieldID mCgmCalibrationContext;
    jfieldID mRegularDeconvolutionContext;
    jfieldID mArrowDirectionContext;
    jmethodID constructor;
}data_algorithm_context;

void register_current_judgment_context_class(JNIEnv *env);
void register_judgment_context_class(JNIEnv *env);
void register_kalman_context_class(JNIEnv *env);
void register_current_correction_context_class(JNIEnv *env);
void register_filter_context_class(JNIEnv *env);
void register_cal_baseline_context_class(JNIEnv *env);
void register_clipping_filter_context_class(JNIEnv *env);
void register_esa_context_class(JNIEnv *env);
void register_cgm_calibration_context_class(JNIEnv *env);
void register_regular_deconvolution_context_class(JNIEnv *env);
void register_arrow_direction_context_class(JNIEnv *env);
void register_algorithm_context_class(JNIEnv *env);

jobject algorithm_context_c_to_java(JNIEnv *env, jni_algorithm_context_t *c_algorithm_context);
void algorithm_context_java_to_c(JNIEnv *env, jobject algorithm_context_in, jni_algorithm_context_t *algorithm_context_out);
void algorithm_context_clone_c_to_java(JNIEnv *env, jni_algorithm_context_t *algorithm_context_src, jobject algorithm_context_dst);

#endif //MYMODULESAPP_NATIVE_ALGORITHM_CLASS_H



