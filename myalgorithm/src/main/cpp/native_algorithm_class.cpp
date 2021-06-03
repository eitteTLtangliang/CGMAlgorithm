//
// Created by ml.gong on 2021/5/21.
//

#ifdef _WINDOWS
#include <string.h>
#include "../header/native_algorithm_class.h"
#include "../header/native_cal_baseline_context.h"
#include "../header/native_esa_compensate_context.h"
#include "../header/native_regular_deconvolution_context.h"
#include "../header/native_arrow_direction_context.h"
#include "../header/cgm_algorithm.h"
#endif

#ifdef __ANDROID__
#include <jni.h>
#include <android/log.h>
#include <string.h>
#include "native_algorithm_class.h"
#include "algorithm/header/native_cal_baseline_context.h"
#include "algorithm/header/native_esa_compensate_context.h"
#include "algorithm/header/native_regular_deconvolution_context.h"
#include "algorithm/header/native_arrow_direction_context.h"
#include "algorithm/header/cgm_algorithm.h"
#include "algorithm/header/native_cgm_calibration_context.h"

#endif

data_kalman_context m_data_kalman_context;
data_judgment_context m_data_judgment_context;
data_current_judgment_context m_data_current_judgment_context;
data_current_correction_context m_data_current_correction_context;
data_filter1_context m_data_filter1_context;
data_cal_baseline_context m_data_cal_baseline_context;
data_clipping_filter_context m_data_clipping_filter_context;
data_esa_compensate_context m_data_esa_compensate_context;
data_cgm_calibration_context m_data_cgm_calibration_context;
data_regular_deconvolution_context m_data_regular_deconvolution_context;
data_arrow_direction_context m_data_arrow_direction_context;
data_algorithm_context m_data_algorithm_context;


//////////////////////////////////////////////////////////////////////////////////////////
int find_class(JNIEnv *env, const char *name, jclass *clazz_out) {

    jclass clazz = env->FindClass(name);

    if (clazz == nullptr) {
        LOGD("Can't find %s", name);
        return -1;
    }
    *clazz_out = (jclass) env->NewGlobalRef(clazz); // 这里必须新建一个全局的引用
    return 0;
}

int get_field(JNIEnv *env, jclass *clazz, const char *name, const char *sig, jfieldID *field_out) {

    jfieldID filed = env->GetFieldID(*clazz, name, sig);

    if (filed == nullptr) {
        LOGD("Can't find. filed name: %s, sig: %s", name, sig);
        return -1;
    }
    *field_out = filed;
    return 0;
}

void register_current_judgment_context_class(JNIEnv *env) {

    int ret = find_class(env, CLASS_ALGORITHM_PATH(JudgmentContext$CurrentJudgmentContext), &m_data_current_judgment_context.clazz);

    if (ret != 0) {
        LOGD("void register_current_judgment_context_class(JNIEnv *env)  failed");
        return;
    }

    jclass clazz = m_data_current_judgment_context.clazz;
    m_data_current_judgment_context.constructor = env->GetMethodID(clazz, "<init>", "()V");
    get_field(env, &clazz, "last_current", "D", &m_data_current_judgment_context.last_current);
    get_field(env, &clazz, "max_current", "D", &m_data_current_judgment_context.max_current);
    get_field(env, &clazz, "abnormal_flag", "I", &m_data_current_judgment_context.abnormal_flag);
    get_field(env, &clazz, "last_abnormal_flag", "I", &m_data_current_judgment_context.last_abnormal_flag);
    get_field(env, &clazz, "temp_data_buf", "[D", &m_data_current_judgment_context.temp_data_buf);
    get_field(env, &clazz, "var_data", "D", &m_data_current_judgment_context.var_data);
    get_field(env, &clazz, "con_count", "I", &m_data_current_judgment_context.con_count);

}

void register_judgment_context_class(JNIEnv *env) {

    int ret = find_class(env, CLASS_ALGORITHM_PATH(JudgmentContext), &m_data_judgment_context.clazz);

    if (ret != 0) {
        LOGD("register_judgment_context_class  failed");
        return;
    }

    jclass clazz = m_data_judgment_context.clazz;
    m_data_judgment_context.constructor = env->GetMethodID(clazz, "<init>", "()V");

    get_field(env, &clazz, "abnormal_flag_buf", "[D", &m_data_judgment_context.abnormal_flag_buf);
    get_field(env, &clazz, "current_abnormal_flag_count", "D", &m_data_judgment_context.current_abnormal_flag_count);
    get_field(env, &clazz, "abnormal_count", "I", &m_data_judgment_context.abnormal_count);
    get_field(env, &clazz, "mCurrentJudgmentContext", LCLASS_ALGORITHM_PATH(JudgmentContext$CurrentJudgmentContext), &m_data_judgment_context.mCurrentJudgmentContext);

}

void register_kalman_context_class(JNIEnv *env) {

    int ret = find_class(env, CLASS_ALGORITHM_PATH(KalmanContext), &m_data_kalman_context.clazz);

    if (ret != 0) {
        LOGD("register_data_bean_class  failed");
        return;
    }

    jclass clazz = m_data_kalman_context.clazz;
    m_data_kalman_context.constructor = env->GetMethodID(clazz, "<init>", "()V");

    get_field(env, &clazz, "mStateKalman", "D", &m_data_kalman_context.mStateKalman);
    get_field(env, &clazz, "mStatePre", "D", &m_data_kalman_context.mStatePre);
    get_field(env, &clazz, "mPminus", "D", &m_data_kalman_context.mPminus);
    get_field(env, &clazz, "mK", "D", &m_data_kalman_context.mK);
    get_field(env, &clazz, "mR", "D", &m_data_kalman_context.mR);
    get_field(env, &clazz, "mQ", "D", &m_data_kalman_context.mQ);
    get_field(env, &clazz, "mP", "D", &m_data_kalman_context.mP);

}

void register_current_correction_context_class(JNIEnv *env){

    int ret = find_class(env, CLASS_ALGORITHM_PATH(AbnormalValueCorrectionContext), &m_data_current_correction_context.clazz);

    if (ret != 0) {
        LOGD("register_current_correction_context_class  failed");
        return;
    }

    jclass clazz = m_data_current_correction_context.clazz;
    m_data_current_correction_context.constructor = env->GetMethodID(clazz, "<init>", "()V");
    get_field(env, &clazz, "mS", "D", &m_data_current_correction_context.mS);
    get_field(env, &clazz, "mLastS", "D", &m_data_current_correction_context.mLastS);
    get_field(env, &clazz, "mSFlag", "I", &m_data_current_correction_context.mSFlag);
    get_field(env, &clazz, "mD0", "D", &m_data_current_correction_context.mD0);
    get_field(env, &clazz, "mSs0", "D", &m_data_current_correction_context.mSs0);
    get_field(env, &clazz, "mTimeWindows", "[D", &m_data_current_correction_context.mTimeWindows);
    get_field(env, &clazz, "mTimeWindows1", "[D", &m_data_current_correction_context.mTimeWindows1);
    LOGD("register_current_correction_context_class  success!!!");
}

void register_filter_context_class(JNIEnv *env){

    int ret = find_class(env, CLASS_ALGORITHM_PATH(FilterContext), &m_data_filter1_context.clazz);

    if (ret != 0) {
        LOGD("register_filter_context_class  failed");
        return;
    }

    jclass clazz = m_data_filter1_context.clazz;
    m_data_filter1_context.constructor = env->GetMethodID(clazz, "<init>", "()V");
    get_field(env, &clazz, "m_filter_data", "[D", &m_data_filter1_context.m_filter_data);
    get_field(env, &clazz, "m_temp_data", "[D", &m_data_filter1_context.m_temp_data);
    get_field(env, &clazz, "m_a_data", "[D", &m_data_filter1_context.m_a_data);
    get_field(env, &clazz, "m_b_data", "[D", &m_data_filter1_context.m_b_data);
    LOGD("register_filter_context_class  success!!!");
}

void register_cal_baseline_context_class(JNIEnv *env){

    int ret = find_class(env, CLASS_ALGORITHM_PATH(CalBaseLineContext), &m_data_cal_baseline_context.clazz);

    if (ret != 0) {
        LOGD("register_cal_baseline_context_class  failed");
        return;
    }

    jclass clazz = m_data_cal_baseline_context.clazz;
    m_data_cal_baseline_context.constructor = env->GetMethodID(clazz, "<init>", "()V");

    get_field(env, &clazz, "fasting_continue_count", "I", &m_data_cal_baseline_context.fasting_continue_count);
    get_field(env, &clazz, "fasting_min_data", "D", &m_data_cal_baseline_context.fasting_min_data);
    get_field(env, &clazz, "last_fasting_min_data", "D", &m_data_cal_baseline_context.last_fasting_min_data);
    get_field(env, &clazz, "temp_fasting_min_index", "I", &m_data_cal_baseline_context.temp_fasting_min_index);
    get_field(env, &clazz, "last_fasting_min_index", "I", &m_data_cal_baseline_context.last_fasting_min_index);
    get_field(env, &clazz, "fasting_max_index", "I", &m_data_cal_baseline_context.fasting_max_index);
    get_field(env, &clazz, "fasting_min_index", "I", &m_data_cal_baseline_context.fasting_min_index);
    get_field(env, &clazz, "fasting_max_data", "D", &m_data_cal_baseline_context.fasting_max_data);
    get_field(env, &clazz, "fasting_continue_count_sum", "I", &m_data_cal_baseline_context.fasting_continue_count_sum);

    get_field(env, &clazz, "fasting_continue_count_avg", "D", &m_data_cal_baseline_context.fasting_continue_count_avg);
    get_field(env, &clazz, "fasting_continue_data_sum", "D", &m_data_cal_baseline_context.fasting_continue_data_sum);
    get_field(env, &clazz, "fasting_continue_data_avg", "D", &m_data_cal_baseline_context.fasting_continue_data_avg);
    get_field(env, &clazz, "fasting_count", "D", &m_data_cal_baseline_context.fasting_count);
    get_field(env, &clazz, "last_trend_data_count", "I", &m_data_cal_baseline_context.last_trend_data_count);
    get_field(env, &clazz, "temp_mean_baseline", "D", &m_data_cal_baseline_context.temp_mean_baseline);
    get_field(env, &clazz, "baseline_value", "D", &m_data_cal_baseline_context.baseline_value);
    get_field(env, &clazz, "last_baseline_value", "D", &m_data_cal_baseline_context.last_baseline_value);

    get_field(env, &clazz, "last_last_baseline_value", "D", &m_data_cal_baseline_context.last_last_baseline_value);
    get_field(env, &clazz, "last_data", "D", &m_data_cal_baseline_context.last_data);
    get_field(env, &clazz, "last_last_data", "D", &m_data_cal_baseline_context.last_last_data);
    get_field(env, &clazz, "fasting_min_sum", "D", &m_data_cal_baseline_context.fasting_min_sum);
    get_field(env, &clazz, "fasting_min_avg", "D", &m_data_cal_baseline_context.fasting_min_avg);
    get_field(env, &clazz, "flag_index", "I", &m_data_cal_baseline_context.flag_index);

    get_field(env, &clazz, "fasting_min_data_count", "I", &m_data_cal_baseline_context.fasting_min_data_count);
    get_field(env, &clazz, "last_fasting_index", "I", &m_data_cal_baseline_context.last_fasting_index);
    get_field(env, &clazz, "fasting_min_value", "D", &m_data_cal_baseline_context.fasting_min_value);
    get_field(env, &clazz, "fasting_min_data_sum", "D", &m_data_cal_baseline_context.fasting_min_data_sum);

    get_field(env, &clazz, "fasting_min_data_avg", "D", &m_data_cal_baseline_context.fasting_min_data_avg);
    get_field(env, &clazz, "last_sf_data", "D", &m_data_cal_baseline_context.last_sf_data);
    get_field(env, &clazz, "max_point_data", "D", &m_data_cal_baseline_context.max_point_data);

}

void register_clipping_filter_context_class(JNIEnv *env){

    int ret = find_class(env, CLASS_ALGORITHM_PATH(ClippingFilterContext), &m_data_clipping_filter_context.clazz);

    if (ret != 0) {
        LOGD("register_clipping_filter_context_class  failed");
        return;
    }

    jclass clazz = m_data_clipping_filter_context.clazz;
    m_data_clipping_filter_context.constructor = env->GetMethodID(clazz, "<init>", "()V");
    get_field(env, &clazz, "error_flag", "I", &m_data_clipping_filter_context.error_flag);
    get_field(env, &clazz, "short_ESA_flag", "I", &m_data_clipping_filter_context.short_ESA_flag);
    get_field(env, &clazz, "count", "I", &m_data_clipping_filter_context.count);

    get_field(env, &clazz, "last_min_data", "D", &m_data_clipping_filter_context.last_min_data);
    get_field(env, &clazz, "min_data", "D", &m_data_clipping_filter_context.min_data);
    get_field(env, &clazz, "continue_down_count", "D", &m_data_clipping_filter_context.continue_down_count);

    get_field(env, &clazz, "continue_down_flag", "I", &m_data_clipping_filter_context.continue_down_flag);
    get_field(env, &clazz, "continue_down_max_data", "D", &m_data_clipping_filter_context.continue_down_max_data);
    get_field(env, &clazz, "last_continue_down_max_data", "D", &m_data_clipping_filter_context.last_continue_down_max_data);
    get_field(env, &clazz, "continue_down_min_data", "D", &m_data_clipping_filter_context.continue_down_min_data);

    get_field(env, &clazz, "CGM_var_windows", "[D", &m_data_clipping_filter_context.CGM_var_windows);
    get_field(env, &clazz, "CGM_var_data", "D", &m_data_clipping_filter_context.CGM_var_data);
    get_field(env, &clazz, "var_data_count", "I", &m_data_clipping_filter_context.var_data_count);
    get_field(env, &clazz, "min_data_buf", "[D", &m_data_clipping_filter_context.min_data_buf);
    get_field(env, &clazz, "data_count", "I", &m_data_clipping_filter_context.data_count);
    get_field(env, &clazz, "seven_point_index", "I", &m_data_clipping_filter_context.seven_point_index);
    get_field(env, &clazz, "data_count0_max", "D", &m_data_clipping_filter_context.data_count0_max);
    get_field(env, &clazz, "data_count0", "D", &m_data_clipping_filter_context.data_count0);
    get_field(env, &clazz, "slope", "D", &m_data_clipping_filter_context.slope);
    get_field(env, &clazz, "up_continue_count", "I", &m_data_clipping_filter_context.up_continue_count);
    get_field(env, &clazz, "min_data_count", "I", &m_data_clipping_filter_context.min_data_count);
    get_field(env, &clazz, "up_min_data", "D", &m_data_clipping_filter_context.up_min_data);

    get_field(env, &clazz, "sf4_buf", "[D", &m_data_clipping_filter_context.sf4_buf);
    get_field(env, &clazz, "sf4_min_data", "D", &m_data_clipping_filter_context.sf4_min_data);
    get_field(env, &clazz, "sf4_min_data_index", "I", &m_data_clipping_filter_context.sf4_min_data_index);
    get_field(env, &clazz, "Daily_minimum_value", "D", &m_data_clipping_filter_context.Daily_minimum_value);
    get_field(env, &clazz, "last_Daily_minimum_value", "D", &m_data_clipping_filter_context.last_Daily_minimum_value);
    get_field(env, &clazz, "Daily_minimum_value_count", "I", &m_data_clipping_filter_context.Daily_minimum_value_count);
    get_field(env, &clazz, "Daily_minimum_value_sum", "D", &m_data_clipping_filter_context.Daily_minimum_value_sum);
    get_field(env, &clazz, "Daily_minimum_value_avg", "D", &m_data_clipping_filter_context.Daily_minimum_value_avg);
    get_field(env, &clazz, "max_data", "D", &m_data_clipping_filter_context.max_data);
    get_field(env, &clazz, "ret_tmp_data", "[D", &m_data_clipping_filter_context.ret_tmp_data);

}

void register_esa_context_class(JNIEnv *env) {
    int ret = find_class(env, CLASS_ALGORITHM_PATH(EsaCompensateContext), &m_data_esa_compensate_context.clazz);
    if (ret != 0) {
        LOGD("register_esa_context_class  failed");
        return;
    }
    jclass clazz = m_data_esa_compensate_context.clazz;
    m_data_esa_compensate_context.constructor = env->GetMethodID(clazz, "<init>", "()V");

    get_field(env, &clazz, "k_data", "D", &m_data_esa_compensate_context.k_data);
    get_field(env, &clazz, "ESA_min_data", "D", &m_data_esa_compensate_context.ESA_min_data);
    get_field(env, &clazz, "ESA_flag", "I", &m_data_esa_compensate_context.ESA_flag);
    get_field(env, &clazz, "ESA_sum", "D", &m_data_esa_compensate_context.ESA_sum);
    get_field(env, &clazz, "ESA_average", "D", &m_data_esa_compensate_context.ESA_average);
    get_field(env, &clazz, "baseline", "D", &m_data_esa_compensate_context.baseline);
    get_field(env, &clazz, "b1_data", "D", &m_data_esa_compensate_context.b1_data);
    get_field(env, &clazz, "data_12", "D", &m_data_esa_compensate_context.data_12);

    get_field(env, &clazz, "fit10_x", "[D", &m_data_esa_compensate_context.fit10_x);
    get_field(env, &clazz, "fit10_y", "[D", &m_data_esa_compensate_context.fit10_y);
    get_field(env, &clazz, "fit36_x", "[D", &m_data_esa_compensate_context.fit36_x);
    get_field(env, &clazz, "fit36_y", "[D", &m_data_esa_compensate_context.fit36_y);

    get_field(env, &clazz, "last_mean_data", "D", &m_data_esa_compensate_context.last_mean_data);
    get_field(env, &clazz, "continue_mean_count", "D", &m_data_esa_compensate_context.continue_mean_count);
    get_field(env, &clazz, "bl_last_data", "D", &m_data_esa_compensate_context.bl_last_data);
    get_field(env, &clazz, "bl_last_last_data", "D", &m_data_esa_compensate_context.bl_last_last_data);
    get_field(env, &clazz, "bl_min_flag", "D", &m_data_esa_compensate_context.bl_min_flag);
    get_field(env, &clazz, "last_baseline_cgm", "D", &m_data_esa_compensate_context.last_baseline_cgm);
    get_field(env, &clazz, "slowly_chang_value", "D", &m_data_esa_compensate_context.slowly_chang_value);
    get_field(env, &clazz, "deferred_compensation_flag", "I", &m_data_esa_compensate_context.deferred_compensation_flag);
    get_field(env, &clazz, "deferred_compensation_count", "I", &m_data_esa_compensate_context.deferred_compensation_count);
    get_field(env, &clazz, "baseline_chang_value", "D", &m_data_esa_compensate_context.baseline_chang_value);

}

void register_cgm_calibration_context_class(JNIEnv *env){

    int ret = find_class(env, CLASS_ALGORITHM_PATH(CGMCalibrationContext), &m_data_cgm_calibration_context.clazz);

    if (ret != 0) {
        LOGD("register_cgm_calibration_context_class  failed");
        return;
    }

    jclass clazz = m_data_cgm_calibration_context.clazz;
    m_data_cgm_calibration_context.constructor = env->GetMethodID(clazz, "<init>", "()V");
    get_field(env, &clazz, "calibration_flag", "I", &m_data_cgm_calibration_context.calibration_flag);
    get_field(env, &clazz, "bg_index", "I", &m_data_cgm_calibration_context.bg_index);
    get_field(env, &clazz, "last_bg", "D", &m_data_cgm_calibration_context.last_bg);
    get_field(env, &clazz, "last_sf4_data", "D", &m_data_cgm_calibration_context.last_sf4_data);
    get_field(env, &clazz, "last_last_sf4_data", "D", &m_data_cgm_calibration_context.last_last_sf4_data);

}

void register_regular_deconvolution_context_class(JNIEnv *env){

    int ret = find_class(env, CLASS_ALGORITHM_PATH(RegularDeconvolutionContext), &m_data_regular_deconvolution_context.clazz);

    if (ret != 0) {
        LOGD("register_regular_deconvolution_context_class  failed");
        return;
    }

    jclass clazz = m_data_regular_deconvolution_context.clazz;
    m_data_regular_deconvolution_context.constructor = env->GetMethodID(clazz, "<init>", "()V");
    get_field(env, &clazz, "ig_value_buf", "[D", &m_data_regular_deconvolution_context.ig_value_buf);

}

void register_arrow_direction_context_class(JNIEnv *env){
    int ret = find_class(env, CLASS_ALGORITHM_PATH(ArrowDirectionContext), &m_data_arrow_direction_context.clazz);
    if (ret != 0) {
        LOGD("register_arrow_direction_context_class  failed");
        return;
    }
    jclass clazz = m_data_arrow_direction_context.clazz;
    m_data_arrow_direction_context.constructor = env->GetMethodID(clazz, "<init>", "()V");
    get_field(env, &clazz, "blood_glucose_trend", "I", &m_data_arrow_direction_context.blood_glucose_trend);
    get_field(env, &clazz, "last_blood_glucose_trend", "I", &m_data_arrow_direction_context.last_blood_glucose_trend);
    get_field(env, &clazz, "arrow_direction_data", "D", &m_data_arrow_direction_context.arrow_direction_data);
    get_field(env, &clazz, "last_arrow_direction_data", "D", &m_data_arrow_direction_context.last_arrow_direction_data);
    get_field(env, &clazz, "last_last_arrow_direction_data", "D", &m_data_arrow_direction_context.last_last_arrow_direction_data);
    get_field(env, &clazz, "rise_trend_count", "I", &m_data_arrow_direction_context.rise_trend_count);
    get_field(env, &clazz, "decline_trend_count", "I", &m_data_arrow_direction_context.decline_trend_count);
    get_field(env, &clazz, "horizontal_direction_count", "I", &m_data_arrow_direction_context.horizontal_direction_count);
    get_field(env, &clazz, "arrow_direction_count", "I", &m_data_arrow_direction_context.arrow_direction_count);

}

void register_algorithm_context_class(JNIEnv *env){

    int ret = find_class(env, CLASS_ALGORITHM_PATH(AlgorithmClassContext), &m_data_algorithm_context.clazz);
    if (ret != 0) {
        LOGD("register_algorithm_context_class  failed");
        return;
    }

    jclass clazz = m_data_algorithm_context.clazz;
    m_data_algorithm_context.constructor = env->GetMethodID(clazz, "<init>", "()V");
    get_field(env, &clazz, "esa_calibration_enable", "I", &m_data_algorithm_context.esa_calibration_enable);
    get_field(env, &clazz, "finger_blood_calibration_enable", "I", &m_data_algorithm_context.finger_blood_calibration_enable);
    get_field(env, &clazz, "version_name", "[C", &m_data_algorithm_context.version_name);

    get_field(env, &clazz, "IG_data", "D", &m_data_algorithm_context.IG_data);
    get_field(env, &clazz, "last_IG_data", "D", &m_data_algorithm_context.last_IG_data);
    get_field(env, &clazz, "cgm_warning", "I", &m_data_algorithm_context.cgm_warning);
    get_field(env, &clazz, "cgm_current_abnormal", "I", &m_data_algorithm_context.cgm_current_abnormal);
    get_field(env, &clazz, "cgm_temp_abnormal", "I", &m_data_algorithm_context.cgm_temp_abnormal);
    get_field(env, &clazz, "cgm_blood_glucose_trend", "I", &m_data_algorithm_context.cgm_blood_glucose_trend);

    get_field(env, &clazz, "mJudgmentContext", LCLASS_ALGORITHM_PATH(JudgmentContext), &m_data_algorithm_context.mJudgmentContext);

    get_field(env, &clazz, "mCurrentCorrectionContext", LCLASS_ALGORITHM_PATH(AbnormalValueCorrectionContext), &m_data_algorithm_context.mCurrentCorrectionContext);
    get_field(env, &clazz, "mKalmanContext", LCLASS_ALGORITHM_PATH(KalmanContext), &m_data_algorithm_context.mKalmanContext);

    get_field(env, &clazz, "mFilter1Context", LCLASS_ALGORITHM_PATH(FilterContext), &m_data_algorithm_context.mFilter1Context);
    get_field(env, &clazz, "mFilter2Context", LCLASS_ALGORITHM_PATH(FilterContext), &m_data_algorithm_context.mFilter2Context);

    get_field(env, &clazz, "mCalBaselineContext", LCLASS_ALGORITHM_PATH(CalBaseLineContext), &m_data_algorithm_context.mCalBaselineContext);

    get_field(env, &clazz, "mClippingFilterContext", LCLASS_ALGORITHM_PATH(ClippingFilterContext), &m_data_algorithm_context.mClippingFilterContext);

    get_field(env, &clazz, "mESACompensateContext", LCLASS_ALGORITHM_PATH(EsaCompensateContext), &m_data_algorithm_context.mESACompensateContext);

    //add
    get_field(env, &clazz, "cgmCalibrationContext", LCLASS_ALGORITHM_PATH(CGMCalibrationContext), &m_data_algorithm_context.mCgmCalibrationContext);

    get_field(env, &clazz, "mRegularDeconvolutionContext", LCLASS_ALGORITHM_PATH(RegularDeconvolutionContext), &m_data_algorithm_context.mRegularDeconvolutionContext);
    get_field(env, &clazz, "mArrowDirectionContext", LCLASS_ALGORITHM_PATH(ArrowDirectionContext), &m_data_algorithm_context.mArrowDirectionContext);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
jobject judgment_context_c_to_java(JNIEnv *env, jni_judgment_context_t *c_judgment_context){

    if (c_judgment_context == nullptr) {
        LOGD("c_judgment_context is null!");
        return nullptr;
    }

    jobject java_current_judgment_context = env->NewObject(m_data_current_judgment_context.clazz, m_data_current_judgment_context.constructor);
    jni_current_judgment_context_t *c_current_judgment_context = &c_judgment_context->m_current_jud_context;
    if(c_current_judgment_context != NULL)
    {
        env->SetDoubleField(java_current_judgment_context,m_data_current_judgment_context.last_current,c_current_judgment_context->last_current);
        env->SetDoubleField(java_current_judgment_context,m_data_current_judgment_context.max_current,c_current_judgment_context->max_current);
        env->SetIntField(java_current_judgment_context,m_data_current_judgment_context.abnormal_flag,c_current_judgment_context->abnormal_flag);
        env->SetIntField(java_current_judgment_context,m_data_current_judgment_context.last_abnormal_flag,c_current_judgment_context->last_abnormal_flag);

        jsize temp_data_buf_len = NELEM(c_current_judgment_context->temp_data_buf);
        jdoubleArray temp_data_array = env->NewDoubleArray(temp_data_buf_len);
        env->SetDoubleArrayRegion(temp_data_array, 0, temp_data_buf_len, c_current_judgment_context->temp_data_buf);
        env->SetObjectField(java_current_judgment_context, m_data_current_judgment_context.temp_data_buf, temp_data_array);

        env->SetDoubleField(java_current_judgment_context,m_data_current_judgment_context.var_data,c_current_judgment_context->var_data);
        env->SetIntField(java_current_judgment_context,m_data_current_judgment_context.con_count,c_current_judgment_context->con_count);
    }

    jobject java_judgment_context = env->NewObject(m_data_judgment_context.clazz, m_data_judgment_context.constructor);
    if(c_judgment_context != NULL) {
        jsize len = NELEM(c_judgment_context->abnormal_flag_buf);
        jdoubleArray double_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(double_array, 0, len, c_judgment_context->abnormal_flag_buf);
        env->SetObjectField(java_judgment_context, m_data_judgment_context.abnormal_flag_buf, double_array);

        env->SetDoubleField(java_judgment_context, m_data_judgment_context.current_abnormal_flag_count, c_judgment_context->current_abnormal_flag_count);
        env->SetIntField(java_judgment_context,m_data_judgment_context.abnormal_count,c_judgment_context->abnormal_count);

        env->SetObjectField(java_judgment_context, m_data_judgment_context.mCurrentJudgmentContext, java_current_judgment_context);
    }

    return java_judgment_context;
}

void judgment_context_java_to_c(JNIEnv *env, jobject judgment_context_in, jni_judgment_context_t *judgment_context_out){
    if (judgment_context_in == nullptr) {
        LOGD("judgment_context_in is null!");
        return;
    }
    if(judgment_context_out == nullptr){
        LOGD("judgment_context_out is null!");
        return;
    }

    jobject java_current_judgment_context = env->GetObjectField(judgment_context_in, m_data_judgment_context.mCurrentJudgmentContext);
    judgment_context_out->m_current_jud_context.last_current = env->GetDoubleField(java_current_judgment_context, m_data_current_judgment_context.last_current);
    judgment_context_out->m_current_jud_context.max_current = env->GetDoubleField(java_current_judgment_context, m_data_current_judgment_context.max_current);
    judgment_context_out->m_current_jud_context.abnormal_flag = env->GetIntField(java_current_judgment_context,m_data_current_judgment_context.abnormal_flag);
    judgment_context_out->m_current_jud_context.last_abnormal_flag = env->GetIntField(java_current_judgment_context,m_data_current_judgment_context.last_abnormal_flag);
    jdoubleArray temp_data_array = (jdoubleArray) env->GetObjectField(java_current_judgment_context, m_data_current_judgment_context.temp_data_buf);
    jdouble *temp_data_buf = env->GetDoubleArrayElements(temp_data_array, 0);
    jsize len = env->GetArrayLength(temp_data_array);
    LOGD("temp_data_array len: %d", len);
    for (int i = 0; i < len; i++) {
        judgment_context_out->m_current_jud_context.temp_data_buf[i] = temp_data_buf[i];
    }
    judgment_context_out->m_current_jud_context.var_data = env->GetDoubleField(java_current_judgment_context, m_data_current_judgment_context.var_data);
    judgment_context_out->m_current_jud_context.con_count = env->GetIntField(java_current_judgment_context,m_data_current_judgment_context.con_count);

    jdoubleArray abnormal_flag_array =  (jdoubleArray) env->GetObjectField(judgment_context_in, m_data_judgment_context.abnormal_flag_buf);
    jdouble *abnormal_flag_buf = env->GetDoubleArrayElements(abnormal_flag_array, 0);
    jsize abnormal_flag_len = env->GetArrayLength(abnormal_flag_array);
    for (int i = 0; i < abnormal_flag_len; i++) {
        judgment_context_out->abnormal_flag_buf[i] = abnormal_flag_buf[i];
    }
    judgment_context_out->current_abnormal_flag_count = env->GetDoubleField(judgment_context_in, m_data_judgment_context.current_abnormal_flag_count);
    judgment_context_out->abnormal_count = env->GetIntField(judgment_context_in,m_data_judgment_context.abnormal_count);

}

void judgment_context_clone_c_to_java(JNIEnv *env, jni_judgment_context_t *judgment_context_src, jobject judgment_context_dst){

    if (judgment_context_src == nullptr) {
        LOGD("judgment_context_src is null!");
        return;
    }

    if(judgment_context_dst == nullptr){
        LOGD("judgment_context_dst is null!");
        return;
    }

    jobject java_current_judgment_context = env->GetObjectField(judgment_context_dst, m_data_judgment_context.mCurrentJudgmentContext);

    env->SetDoubleField(java_current_judgment_context,m_data_current_judgment_context.last_current,judgment_context_src->m_current_jud_context.last_current);
    env->SetDoubleField(java_current_judgment_context,m_data_current_judgment_context.max_current,judgment_context_src->m_current_jud_context.max_current);
    env->SetIntField(java_current_judgment_context,m_data_current_judgment_context.abnormal_flag,judgment_context_src->m_current_jud_context.abnormal_flag);
    env->SetIntField(java_current_judgment_context,m_data_current_judgment_context.last_abnormal_flag,judgment_context_src->m_current_jud_context.last_abnormal_flag);
    jdoubleArray temp_data_array = (jdoubleArray) env->GetObjectField(java_current_judgment_context, m_data_current_judgment_context.temp_data_buf);
    jdouble *temp_data_buf = env->GetDoubleArrayElements(temp_data_array, 0);

    jsize len = env->GetArrayLength(temp_data_array);
    for (int i = 0; i < len; i++) {
        temp_data_buf[i] = judgment_context_src->m_current_jud_context.temp_data_buf[i];
    }
    env->SetDoubleArrayRegion(temp_data_array,0,len,temp_data_buf);

    env->SetDoubleField(java_current_judgment_context,m_data_current_judgment_context.var_data,judgment_context_src->m_current_jud_context.var_data);
    env->SetIntField(java_current_judgment_context,m_data_current_judgment_context.con_count,judgment_context_src->m_current_jud_context.con_count);

    jdoubleArray abnormal_flag_array =  (jdoubleArray) env->GetObjectField(judgment_context_dst, m_data_judgment_context.abnormal_flag_buf);
    jdouble *abnormal_flag_buf = env->GetDoubleArrayElements(abnormal_flag_array, 0);
    jsize abnormal_flag_len = env->GetArrayLength(abnormal_flag_array);
    for (int i = 0; i < abnormal_flag_len; i++) {
        abnormal_flag_buf[i] = judgment_context_src->abnormal_flag_buf[i];
    }
    env->SetDoubleArrayRegion(abnormal_flag_array,0,abnormal_flag_len,abnormal_flag_buf);

    env->SetDoubleField(judgment_context_dst,m_data_judgment_context.current_abnormal_flag_count,judgment_context_src->current_abnormal_flag_count);
    env->SetIntField(judgment_context_dst,m_data_judgment_context.abnormal_count,judgment_context_src->abnormal_count);
}

///////////////////////////current_correction_context///////////////////////////////////////////
jobject current_correction_context_c_to_java(JNIEnv *env, jni_current_correction_context_t *c_current_correction_contexs){
    jobject java_current_correction_context = env->NewObject(m_data_current_correction_context.clazz, m_data_current_correction_context.constructor);

    if(java_current_correction_context != NULL) {
        env->SetDoubleField(java_current_correction_context, m_data_current_correction_context.mS,c_current_correction_contexs->mS);
        env->SetDoubleField(java_current_correction_context, m_data_current_correction_context.mLastS,c_current_correction_contexs->mLastS);
        env->SetIntField(java_current_correction_context, m_data_current_correction_context.mSFlag,c_current_correction_contexs->mSFlag);
        env->SetDoubleField(java_current_correction_context, m_data_current_correction_context.mD0,c_current_correction_contexs->mD0);
        env->SetDoubleField(java_current_correction_context, m_data_current_correction_context.mSs0,c_current_correction_contexs->mSs0);

        jsize len = NELEM(c_current_correction_contexs->mTimeWindows);
        jdoubleArray time_windows_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(time_windows_array, 0, len, c_current_correction_contexs->mTimeWindows);
        env->SetObjectField(java_current_correction_context, m_data_current_correction_context.mTimeWindows, time_windows_array);

        len = NELEM(c_current_correction_contexs->mTimeWindows1);
        jdoubleArray time_windows1_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(time_windows1_array, 0, len, c_current_correction_contexs->mTimeWindows1);
        env->SetObjectField(java_current_correction_context, m_data_current_correction_context.mTimeWindows1, time_windows1_array);
    }

    return java_current_correction_context;
}

void current_correction_context_java_to_c(JNIEnv *env, jobject current_correction_context_in, jni_current_correction_context_t *current_correction_context_out) {

    if (current_correction_context_in == nullptr) {
        LOGD("current_correction_context_in is null!");
        return;
    }

    if (current_correction_context_out == nullptr) {
        LOGD("current_correction_context_out is null!");
        return;
    }

    current_correction_context_out->mS = env->GetDoubleField(current_correction_context_in,m_data_current_correction_context.mS);
    current_correction_context_out->mLastS = env->GetDoubleField(current_correction_context_in,m_data_current_correction_context.mLastS);
    current_correction_context_out->mSFlag = env->GetIntField(current_correction_context_in,m_data_current_correction_context.mSFlag);
    current_correction_context_out->mD0 = env->GetDoubleField(current_correction_context_in,m_data_current_correction_context.mD0);
    current_correction_context_out->mSs0 = env->GetDoubleField(current_correction_context_in,m_data_current_correction_context.mSs0);

    jdoubleArray time_windows_array = (jdoubleArray) env->GetObjectField(current_correction_context_in, m_data_current_correction_context.mTimeWindows);
    jdouble *time_windows_buf = env->GetDoubleArrayElements(time_windows_array, 0);
    jsize time_windows_len = env->GetArrayLength(time_windows_array);

    for (int i = 0; i < time_windows_len; i++) {
        current_correction_context_out->mTimeWindows[i] = time_windows_buf[i];
    }

    jdoubleArray time_windows1_array = (jdoubleArray) env->GetObjectField(current_correction_context_in, m_data_current_correction_context.mTimeWindows1);
    jdouble *time_windows1_buf = env->GetDoubleArrayElements(time_windows1_array, 0);
    jsize time_windows1_len = env->GetArrayLength(time_windows1_array);

    for (int i = 0; i < time_windows1_len; i++) {
        current_correction_context_out->mTimeWindows1[i] = time_windows1_buf[i];
    }

}

void current_correction_context_clone_c_to_java(JNIEnv *env, jni_current_correction_context_t *current_correction_context_src, jobject current_correction_context_dst){

    if (current_correction_context_src == nullptr) {
        LOGD("current_correction_context_src is null!");
        return;
    }

    if(current_correction_context_dst == nullptr){
        LOGD("current_correction_context_dst is null!");
        return;
    }

    env->SetDoubleField(current_correction_context_dst, m_data_current_correction_context.mS,current_correction_context_src->mS);
    env->SetDoubleField(current_correction_context_dst, m_data_current_correction_context.mLastS,current_correction_context_src->mLastS);
    env->SetIntField(current_correction_context_dst, m_data_current_correction_context.mSFlag,current_correction_context_src->mSFlag);
    env->SetDoubleField(current_correction_context_dst, m_data_current_correction_context.mD0,current_correction_context_src->mD0);
    env->SetDoubleField(current_correction_context_dst, m_data_current_correction_context.mSs0,current_correction_context_src->mSs0);

    jdoubleArray time_windows_array = (jdoubleArray) env->GetObjectField(current_correction_context_dst, m_data_current_correction_context.mTimeWindows);
    jdouble *time_windows_buf = env->GetDoubleArrayElements(time_windows_array, 0);
    jsize len = env->GetArrayLength(time_windows_array);

    for (int i = 0; i < len; i++) {
        time_windows_buf[i] = current_correction_context_src->mTimeWindows[i];
    }

    env->SetDoubleArrayRegion(time_windows_array,0,len,time_windows_buf);

    jdoubleArray time_windows1_array = (jdoubleArray) env->GetObjectField(current_correction_context_dst, m_data_current_correction_context.mTimeWindows1);
    jdouble *time_windows1_buf = env->GetDoubleArrayElements(time_windows1_array, 0);
    jsize time_windows1_len = env->GetArrayLength(time_windows1_array);

    for (int i = 0; i < time_windows1_len; i++) {
        time_windows1_buf[i] = current_correction_context_src->mTimeWindows1[i];
    }

    env->SetDoubleArrayRegion(time_windows1_array,0,time_windows1_len,time_windows1_buf);
}

//////////////////////kalman_context////////////////////////////////////////////////
jobject kalman_context_c_to_java(JNIEnv *env, jni_kalman_context_t *c_kalman_contexs){

    jobject java_kalman_context = env->NewObject(m_data_kalman_context.clazz, m_data_kalman_context.constructor);

    if(c_kalman_contexs != NULL) {
        env->SetDoubleField(java_kalman_context, m_data_kalman_context.mStateKalman,c_kalman_contexs->mStateKalman);
        env->SetDoubleField(java_kalman_context,m_data_kalman_context.mStatePre,c_kalman_contexs->mStatePre);
        env->SetDoubleField(java_kalman_context,m_data_kalman_context.mPminus,c_kalman_contexs->mPminus);
        env->SetDoubleField(java_kalman_context,m_data_kalman_context.mK,c_kalman_contexs->mK);
        env->SetDoubleField(java_kalman_context,m_data_kalman_context.mR,c_kalman_contexs->mR);
        env->SetDoubleField(java_kalman_context,m_data_kalman_context.mQ,c_kalman_contexs->mQ);
        env->SetDoubleField(java_kalman_context,m_data_kalman_context.mP,c_kalman_contexs->mP);
    }
    return java_kalman_context;
}

void kalman_context_java_to_c(JNIEnv *env, jobject kalman_context_in, jni_kalman_context_t *kalman_context_out){

    if (kalman_context_in == nullptr) {
        LOGD("kalman_context_in is null!");
        return;
    }

    if(kalman_context_out == nullptr){
        LOGD("kalman_context_out is null!");
        return;
    }

    kalman_context_out->mStateKalman = env->GetDoubleField(kalman_context_in,m_data_kalman_context.mStateKalman);
    kalman_context_out->mStatePre = env->GetDoubleField(kalman_context_in,m_data_kalman_context.mStatePre);
    kalman_context_out->mPminus = env->GetDoubleField(kalman_context_in,m_data_kalman_context.mPminus);
    kalman_context_out->mK = env->GetDoubleField(kalman_context_in,m_data_kalman_context.mK);
    kalman_context_out->mR = env->GetDoubleField(kalman_context_in,m_data_kalman_context.mR);
    kalman_context_out->mQ = env->GetDoubleField(kalman_context_in,m_data_kalman_context.mQ);
    kalman_context_out->mP = env->GetDoubleField(kalman_context_in,m_data_kalman_context.mP);

}

void kalman_contex_clone_c_to_java(JNIEnv *env,jni_kalman_context_t *kalman_context_src, jobject kalman_context_dst){

    if (kalman_context_src == nullptr) {
        LOGD("kalman_context_src is null!");
        return;
    }

    if(kalman_context_dst == nullptr){
        LOGD("kalman_context_dst is null!");
        return;
    }

    env->SetDoubleField(kalman_context_dst, m_data_kalman_context.mStateKalman,kalman_context_src->mStateKalman);
    env->SetDoubleField(kalman_context_dst,m_data_kalman_context.mStatePre,kalman_context_src->mStatePre);
    env->SetDoubleField(kalman_context_dst,m_data_kalman_context.mPminus,kalman_context_src->mPminus);
    env->SetDoubleField(kalman_context_dst,m_data_kalman_context.mK,kalman_context_src->mK);
    env->SetDoubleField(kalman_context_dst,m_data_kalman_context.mR,kalman_context_src->mR);
    env->SetDoubleField(kalman_context_dst,m_data_kalman_context.mQ,kalman_context_src->mQ);
    env->SetDoubleField(kalman_context_dst,m_data_kalman_context.mP,kalman_context_src->mP);
}

/////////////////////////////filter1_context///////////////////////////////////////////////////////////////////////////
jobject filter_context_c_to_java(JNIEnv *env, jni_filter_context_t *c_filter1_contexs){

    jobject java_filter1_context = env->NewObject(m_data_filter1_context.clazz, m_data_filter1_context.constructor);

    if(java_filter1_context != NULL) {

        jsize len = NELEM(c_filter1_contexs->m_filter_data);
        jdoubleArray double_filter_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(double_filter_array, 0, len, c_filter1_contexs->m_filter_data);
        env->SetObjectField(java_filter1_context, m_data_filter1_context.m_filter_data, double_filter_array);

        len = NELEM(c_filter1_contexs->m_temp_data);
        jdoubleArray double_temp_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(double_temp_array, 0, len, c_filter1_contexs->m_temp_data);
        env->SetObjectField(java_filter1_context, m_data_filter1_context.m_temp_data, double_temp_array);

        len = NELEM(c_filter1_contexs->m_a_data);
        jdoubleArray double_a_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(double_a_array, 0, len, c_filter1_contexs->m_a_data);
        env->SetObjectField(java_filter1_context, m_data_filter1_context.m_a_data, double_a_array);

        len = NELEM(c_filter1_contexs->m_b_data);
        jdoubleArray double_b_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(double_b_array, 0, len, c_filter1_contexs->m_b_data);
        env->SetObjectField(java_filter1_context, m_data_filter1_context.m_b_data, double_b_array);

    }
    return java_filter1_context;
}

void filter_context_java_to_c(JNIEnv *env, jobject filter1_context_in, jni_filter_context_t *filter1_context_out) {

    if (filter1_context_in == nullptr) {
        LOGD("filter1_context_in is null!");
        return;
    }

    if (filter1_context_out == nullptr) {
        LOGD("filter1_context_out is null!");
        return;
    }

    jdoubleArray double_filter_array = (jdoubleArray) env->GetObjectField(filter1_context_in, m_data_filter1_context.m_filter_data);
    jdouble *double_filter_buf = env->GetDoubleArrayElements(double_filter_array, 0);
    jsize double_filter_len = env->GetArrayLength(double_filter_array);

    for (int i = 0; i < double_filter_len; i++) {
        filter1_context_out->m_filter_data[i] = double_filter_buf[i];
    }

    jdoubleArray double_temp_array = (jdoubleArray) env->GetObjectField(filter1_context_in, m_data_filter1_context.m_temp_data);
    jdouble *double_temp_buf = env->GetDoubleArrayElements(double_temp_array, 0);
    jsize double_temp_len = env->GetArrayLength(double_temp_array);

    for (int i = 0; i < double_temp_len; i++) {
        filter1_context_out->m_temp_data[i] = double_temp_buf[i];
    }

    jdoubleArray double_a_array = (jdoubleArray) env->GetObjectField(filter1_context_in, m_data_filter1_context.m_a_data);
    jdouble *double_a_buf = env->GetDoubleArrayElements(double_a_array, 0);
    jsize double_a_len = env->GetArrayLength(double_a_array);

    for (int i = 0; i < double_a_len; i++) {
        filter1_context_out->m_a_data[i] = double_a_buf[i];
    }

    jdoubleArray double_b_array = (jdoubleArray) env->GetObjectField(filter1_context_in, m_data_filter1_context.m_b_data);
    jdouble *double_b_buf = env->GetDoubleArrayElements(double_b_array, 0);
    jsize double_b_len = env->GetArrayLength(double_b_array);

    for (int i = 0; i < double_b_len; i++) {
        filter1_context_out->m_b_data[i] = double_b_buf[i];
    }

}

void filter_context_clone_c_to_java(JNIEnv *env, jni_filter_context_t *filter1_context_src, jobject filter1_context_dst) {

    if (filter1_context_src == nullptr) {
        LOGD("filter1_context_src is null!");
        return;
    }

    if (filter1_context_dst == nullptr) {
        LOGD("filter1_context_dst is null!");
        return;
    }

    jdoubleArray double_filter_array = (jdoubleArray) env->GetObjectField(filter1_context_dst, m_data_filter1_context.m_filter_data);
    jdouble *double_filter_buf = env->GetDoubleArrayElements(double_filter_array, 0);
    jsize double_filter_len = env->GetArrayLength(double_filter_array);

    for (int i = 0; i < double_filter_len; i++) {
        double_filter_buf[i] = filter1_context_src->m_filter_data[i];
    }

    env->SetDoubleArrayRegion(double_filter_array,0,double_filter_len,double_filter_buf);

    jdoubleArray double_temp_array = (jdoubleArray) env->GetObjectField(filter1_context_dst, m_data_filter1_context.m_temp_data);
    jdouble *double_temp_buf = env->GetDoubleArrayElements(double_temp_array, 0);
    jsize double_temp_len = env->GetArrayLength(double_temp_array);

    for (int i = 0; i < double_temp_len; i++) {
        double_temp_buf[i] = filter1_context_src->m_temp_data[i];
    }

    env->SetDoubleArrayRegion(double_temp_array,0,double_temp_len,double_temp_buf);

    jdoubleArray double_a_array = (jdoubleArray) env->GetObjectField(filter1_context_dst, m_data_filter1_context.m_a_data);
    jdouble *double_a_buf = env->GetDoubleArrayElements(double_a_array, 0);
    jsize double_a_len = env->GetArrayLength(double_a_array);

    for (int i = 0; i < double_a_len; i++) {
        double_a_buf[i] = filter1_context_src->m_a_data[i];
    }

    env->SetDoubleArrayRegion(double_a_array,0,double_a_len,double_a_buf);

    jdoubleArray double_b_array = (jdoubleArray) env->GetObjectField(filter1_context_dst, m_data_filter1_context.m_b_data);
    jdouble *double_b_buf = env->GetDoubleArrayElements(double_b_array, 0);
    jsize double_b_len = env->GetArrayLength(double_b_array);

    for (int i = 0; i < double_b_len; i++) {
        double_b_buf[i] = filter1_context_src->m_b_data[i];
    }

    env->SetDoubleArrayRegion(double_b_array,0,double_b_len,double_b_buf);
}

/////////////////////////cal_baseline_context/////////////////////////////////////////////
jobject cal_baseline_context_c_to_java(JNIEnv *env, jni_cal_baseline_context_t *c_cal_baseline_context){
    jobject java_cal_baseline_context = env->NewObject(m_data_cal_baseline_context.clazz, m_data_cal_baseline_context.constructor);

    if(c_cal_baseline_context != NULL) {

        env->SetIntField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_continue_count,c_cal_baseline_context->fasting_continue_count);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_min_data,c_cal_baseline_context->fasting_min_data);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.last_fasting_min_data,c_cal_baseline_context->last_fasting_min_data);
        env->SetIntField(java_cal_baseline_context,m_data_cal_baseline_context.temp_fasting_min_index,c_cal_baseline_context->temp_fasting_min_index);
        env->SetIntField(java_cal_baseline_context,m_data_cal_baseline_context.last_fasting_min_index,c_cal_baseline_context->last_fasting_min_index);
        env->SetIntField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_max_index,c_cal_baseline_context->fasting_max_index);
        env->SetIntField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_min_index,c_cal_baseline_context->fasting_min_index);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_max_data,c_cal_baseline_context->fasting_max_data);
        env->SetIntField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_continue_count_sum,c_cal_baseline_context->fasting_continue_count_sum);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_continue_count_avg,c_cal_baseline_context->fasting_continue_count_avg);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_continue_data_sum,c_cal_baseline_context->fasting_continue_data_sum);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_continue_data_avg,c_cal_baseline_context->fasting_continue_data_avg);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_count,c_cal_baseline_context->fasting_count);

        env->SetIntField(java_cal_baseline_context,m_data_cal_baseline_context.last_trend_data_count,c_cal_baseline_context->last_trend_data_count);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.temp_mean_baseline,c_cal_baseline_context->temp_mean_baseline);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.baseline_value,c_cal_baseline_context->baseline_value);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.last_baseline_value,c_cal_baseline_context->last_baseline_value);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.last_last_baseline_value,c_cal_baseline_context->last_last_baseline_value);

        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.last_data,c_cal_baseline_context->last_data);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.last_last_data,c_cal_baseline_context->last_last_data);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_min_sum,c_cal_baseline_context->fasting_min_sum);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_min_avg,c_cal_baseline_context->fasting_min_avg);

        env->SetIntField(java_cal_baseline_context,m_data_cal_baseline_context.flag_index,c_cal_baseline_context->flag_index);
        env->SetIntField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_min_data_count,c_cal_baseline_context->fasting_min_data_count);
        env->SetIntField(java_cal_baseline_context,m_data_cal_baseline_context.last_fasting_index,c_cal_baseline_context->last_fasting_index);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_min_value,c_cal_baseline_context->fasting_min_value);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_min_data_sum,c_cal_baseline_context->fasting_min_data_sum);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.fasting_min_data_avg,c_cal_baseline_context->fasting_min_data_avg);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.last_sf_data,c_cal_baseline_context->last_sf_data);
        env->SetDoubleField(java_cal_baseline_context,m_data_cal_baseline_context.max_point_data,c_cal_baseline_context->max_point_data);

    }
    return java_cal_baseline_context;
}

void cal_baseline_context_java_to_c(JNIEnv *env, jobject cal_baseline_context_in, jni_cal_baseline_context_t *cal_baseline_context_out){

    if (cal_baseline_context_in == nullptr) {
        LOGD("cal_baseline_context_in is null!");
        return;
    }

    if (cal_baseline_context_out == nullptr) {
        LOGD("cal_baseline_context_out is null!");
        return;
    }

    cal_baseline_context_out->fasting_continue_count = env->GetIntField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_continue_count);
    cal_baseline_context_out->fasting_min_data = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_min_data);
    cal_baseline_context_out->last_fasting_min_data = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.last_fasting_min_data);
    cal_baseline_context_out->temp_fasting_min_index = env->GetIntField(cal_baseline_context_in,m_data_cal_baseline_context.temp_fasting_min_index);
    cal_baseline_context_out->last_fasting_min_index = env->GetIntField(cal_baseline_context_in,m_data_cal_baseline_context.last_fasting_min_index);
    cal_baseline_context_out->fasting_max_index = env->GetIntField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_max_index);
    cal_baseline_context_out->fasting_min_index = env->GetIntField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_min_index);
    cal_baseline_context_out->fasting_max_data = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_max_data);
    cal_baseline_context_out->fasting_continue_count_sum = env->GetIntField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_continue_count_sum);
    cal_baseline_context_out->fasting_continue_count_avg = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_continue_count_avg);
    cal_baseline_context_out->fasting_continue_data_sum = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_continue_data_sum);
    cal_baseline_context_out->fasting_continue_data_avg = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_continue_data_avg);
    cal_baseline_context_out->fasting_count = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_count);

    cal_baseline_context_out->last_trend_data_count = env->GetIntField(cal_baseline_context_in,m_data_cal_baseline_context.last_trend_data_count);

    cal_baseline_context_out->temp_mean_baseline = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.temp_mean_baseline);

    cal_baseline_context_out->baseline_value = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.baseline_value);
    cal_baseline_context_out->last_baseline_value = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.last_baseline_value);
    cal_baseline_context_out->last_last_baseline_value = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.last_last_baseline_value);
    cal_baseline_context_out->last_data = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.last_data);
    cal_baseline_context_out->last_last_data = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.last_last_data);
    cal_baseline_context_out->fasting_min_sum = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_min_sum);
    cal_baseline_context_out->fasting_min_avg = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_min_avg);

    cal_baseline_context_out->flag_index = env->GetIntField(cal_baseline_context_in,m_data_cal_baseline_context.flag_index);
    cal_baseline_context_out->fasting_min_data_count = env->GetIntField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_min_data_count);
    cal_baseline_context_out->last_fasting_index = env->GetIntField(cal_baseline_context_in,m_data_cal_baseline_context.last_fasting_index);

    cal_baseline_context_out->fasting_min_value = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_min_value);
    cal_baseline_context_out->fasting_min_data_sum = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_min_data_sum);
    cal_baseline_context_out->fasting_min_data_avg = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.fasting_min_data_avg);
    cal_baseline_context_out->last_sf_data = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.last_sf_data);
    cal_baseline_context_out->max_point_data = env->GetDoubleField(cal_baseline_context_in,m_data_cal_baseline_context.max_point_data);

}

void cal_baseline_context_clone_c_to_java(JNIEnv *env, jni_cal_baseline_context_t *cal_baseline_context_src, jobject cal_baseline_context_dst){

    if (cal_baseline_context_src == nullptr) {
        LOGD("cal_baseline_context_src is null!");
        return;
    }

    if (cal_baseline_context_dst == nullptr) {
        LOGD("cal_baseline_context_dst is null!");
        return;
    }

    env->SetIntField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_continue_count,cal_baseline_context_src->fasting_continue_count);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_min_data,cal_baseline_context_src->fasting_min_data);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.last_fasting_min_data,cal_baseline_context_src->last_fasting_min_data);
    env->SetIntField(cal_baseline_context_dst, m_data_cal_baseline_context.temp_fasting_min_index,cal_baseline_context_src->temp_fasting_min_index);
    env->SetIntField(cal_baseline_context_dst, m_data_cal_baseline_context.last_fasting_min_index,cal_baseline_context_src->last_fasting_min_index);
    env->SetIntField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_max_index,cal_baseline_context_src->fasting_max_index);
    env->SetIntField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_min_index,cal_baseline_context_src->fasting_min_index);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_max_data,cal_baseline_context_src->fasting_max_data);
    env->SetIntField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_continue_count_sum,cal_baseline_context_src->fasting_continue_count_sum);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_continue_count_avg,cal_baseline_context_src->fasting_continue_count_avg);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_continue_data_sum,cal_baseline_context_src->fasting_continue_data_sum);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_continue_data_avg,cal_baseline_context_src->fasting_continue_data_avg);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_count,cal_baseline_context_src->fasting_count);

    env->SetIntField(cal_baseline_context_dst, m_data_cal_baseline_context.last_trend_data_count,cal_baseline_context_src->last_trend_data_count);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.temp_mean_baseline,cal_baseline_context_src->temp_mean_baseline);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.baseline_value,cal_baseline_context_src->baseline_value);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.last_baseline_value,cal_baseline_context_src->last_baseline_value);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.last_last_baseline_value,cal_baseline_context_src->last_last_baseline_value);

    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.last_data,cal_baseline_context_src->last_data);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.last_last_data,cal_baseline_context_src->last_last_data);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_min_sum,cal_baseline_context_src->fasting_min_sum);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_min_avg,cal_baseline_context_src->fasting_min_avg);

    env->SetIntField(cal_baseline_context_dst, m_data_cal_baseline_context.flag_index,cal_baseline_context_src->flag_index);
    env->SetIntField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_min_data_count,cal_baseline_context_src->fasting_min_data_count);
    env->SetIntField(cal_baseline_context_dst, m_data_cal_baseline_context.last_fasting_index,cal_baseline_context_src->last_fasting_index);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_min_value,cal_baseline_context_src->fasting_min_value);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_min_data_sum,cal_baseline_context_src->fasting_min_data_sum);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.fasting_min_data_avg,cal_baseline_context_src->fasting_min_data_avg);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.last_sf_data,cal_baseline_context_src->last_sf_data);
    env->SetDoubleField(cal_baseline_context_dst, m_data_cal_baseline_context.max_point_data,cal_baseline_context_src->max_point_data);

}

/////////////////////////clipping_filter_context//////////////////////////////////////////////
jobject clipping_filter_context_c_to_java(JNIEnv *env, jni_clipping_filter_context_t *c_clipping_filter_context) {

    jobject java_clipping_filter_context = env->NewObject(m_data_clipping_filter_context.clazz, m_data_clipping_filter_context.constructor);

    if (c_clipping_filter_context != NULL) {

        env->SetIntField(java_clipping_filter_context, m_data_clipping_filter_context.error_flag, c_clipping_filter_context->error_flag);
        env->SetIntField(java_clipping_filter_context, m_data_clipping_filter_context.short_ESA_flag, c_clipping_filter_context->short_ESA_flag);
        env->SetIntField(java_clipping_filter_context, m_data_clipping_filter_context.count,c_clipping_filter_context->count);

        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.last_min_data, c_clipping_filter_context->last_min_data);
        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.min_data, c_clipping_filter_context->min_data);
        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.continue_down_count, c_clipping_filter_context->continue_down_count);

        env->SetIntField(java_clipping_filter_context, m_data_clipping_filter_context.continue_down_flag,c_clipping_filter_context->continue_down_flag);
        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.continue_down_max_data, c_clipping_filter_context->continue_down_max_data);

        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.last_continue_down_max_data, c_clipping_filter_context->last_continue_down_max_data);

        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.continue_down_min_data, c_clipping_filter_context->continue_down_min_data);

        jsize len = NELEM(c_clipping_filter_context->CGM_var_windows);
        jdoubleArray double_var_windows_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(double_var_windows_array, 0, len, c_clipping_filter_context->CGM_var_windows);
        env->SetObjectField(java_clipping_filter_context, m_data_clipping_filter_context.CGM_var_windows, double_var_windows_array);

        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.CGM_var_data, c_clipping_filter_context->CGM_var_data);
        env->SetIntField(java_clipping_filter_context, m_data_clipping_filter_context.var_data_count, c_clipping_filter_context->var_data_count);

        len = NELEM(c_clipping_filter_context->min_data_buf);
        jdoubleArray double_min_data_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(double_min_data_array, 0, len, c_clipping_filter_context->min_data_buf);
        env->SetObjectField(java_clipping_filter_context, m_data_clipping_filter_context.min_data_buf, double_min_data_array);

        env->SetIntField(java_clipping_filter_context, m_data_clipping_filter_context.data_count, c_clipping_filter_context->data_count);
        env->SetIntField(java_clipping_filter_context, m_data_clipping_filter_context.seven_point_index, c_clipping_filter_context->seven_point_index);

        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.data_count0_max, c_clipping_filter_context->data_count0_max);
        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.data_count0, c_clipping_filter_context->data_count0);
        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.slope, c_clipping_filter_context->slope);
        env->SetIntField(java_clipping_filter_context, m_data_clipping_filter_context.up_continue_count, c_clipping_filter_context->up_continue_count);
        env->SetIntField(java_clipping_filter_context, m_data_clipping_filter_context.min_data_count, c_clipping_filter_context->min_data_count);
        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.up_min_data, c_clipping_filter_context->up_min_data);

        len = NELEM(c_clipping_filter_context->sf4_buf);
        jdoubleArray double_sf4_buf_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(double_sf4_buf_array, 0, len, c_clipping_filter_context->sf4_buf);
        env->SetObjectField(java_clipping_filter_context, m_data_clipping_filter_context.sf4_buf, double_sf4_buf_array);

        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.sf4_min_data, c_clipping_filter_context->sf4_min_data);
        env->SetIntField(java_clipping_filter_context, m_data_clipping_filter_context.sf4_min_data_index, c_clipping_filter_context->sf4_min_data_index);

        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.Daily_minimum_value, c_clipping_filter_context->Daily_minimum_value);
        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.last_Daily_minimum_value, c_clipping_filter_context->last_Daily_minimum_value);
        env->SetIntField(java_clipping_filter_context, m_data_clipping_filter_context.Daily_minimum_value_count, c_clipping_filter_context->Daily_minimum_value_count);
        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.Daily_minimum_value_sum, c_clipping_filter_context->Daily_minimum_value_sum);
        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.Daily_minimum_value_avg, c_clipping_filter_context->Daily_minimum_value_avg);
        env->SetDoubleField(java_clipping_filter_context, m_data_clipping_filter_context.max_data, c_clipping_filter_context->max_data);
        jsize ret_tmp_len = NELEM(c_clipping_filter_context->ret_tmp_data);
        jdoubleArray ret_tmp_array = env->NewDoubleArray(ret_tmp_len);
        env->SetDoubleArrayRegion(ret_tmp_array, 0, ret_tmp_len, c_clipping_filter_context->ret_tmp_data);
        env->SetObjectField(java_clipping_filter_context, m_data_clipping_filter_context.ret_tmp_data, ret_tmp_array);

    }
    return java_clipping_filter_context;

}

void clipping_filter_context_java_to_c(JNIEnv *env, jobject clipping_filter_context_in, jni_clipping_filter_context_t *clipping_filter_context_out) {

    if (clipping_filter_context_in == nullptr) {
        LOGD("clipping_filter_context_in is null!");
        return;
    }

    if (clipping_filter_context_out == nullptr) {
        LOGD("clipping_filter_context_out is null!");
        return;
    }

    clipping_filter_context_out->error_flag = env->GetIntField(clipping_filter_context_in,m_data_clipping_filter_context.error_flag);
    clipping_filter_context_out->short_ESA_flag = env->GetIntField(clipping_filter_context_in,m_data_clipping_filter_context.short_ESA_flag);
    clipping_filter_context_out->count = env->GetIntField(clipping_filter_context_in,m_data_clipping_filter_context.count);

    clipping_filter_context_out->last_min_data = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.last_min_data);
    clipping_filter_context_out->min_data = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.min_data);
    clipping_filter_context_out->continue_down_count = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.continue_down_count);

    clipping_filter_context_out->continue_down_flag = env->GetIntField(clipping_filter_context_in,m_data_clipping_filter_context.continue_down_flag);
    clipping_filter_context_out->continue_down_max_data = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.continue_down_max_data);
    clipping_filter_context_out->last_continue_down_max_data = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.last_continue_down_max_data);
    clipping_filter_context_out->continue_down_min_data = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.continue_down_min_data);

    jdoubleArray double_var_windows_array = (jdoubleArray) env->GetObjectField(clipping_filter_context_in, m_data_clipping_filter_context.CGM_var_windows);
    jdouble *double_var_windows_buf = env->GetDoubleArrayElements(double_var_windows_array, 0);
    jsize double_var_windows_len = env->GetArrayLength(double_var_windows_array);

    for (int i = 0; i < double_var_windows_len; i++) {
        clipping_filter_context_out->CGM_var_windows[i] = double_var_windows_buf[i];
    }

    clipping_filter_context_out->CGM_var_data = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.CGM_var_data);
    clipping_filter_context_out->var_data_count = env->GetIntField(clipping_filter_context_in,m_data_clipping_filter_context.var_data_count);
    jdoubleArray double_min_data_array = (jdoubleArray) env->GetObjectField(clipping_filter_context_in, m_data_clipping_filter_context.min_data_buf);
    jdouble *double_min_data_buf = env->GetDoubleArrayElements(double_min_data_array, 0);
    jsize double_min_data_len = env->GetArrayLength(double_min_data_array);

    for (int i = 0; i < double_min_data_len; i++) {
        clipping_filter_context_out->min_data_buf[i] = double_min_data_buf[i];
    }

    clipping_filter_context_out->data_count = env->GetIntField(clipping_filter_context_in,m_data_clipping_filter_context.data_count);
    clipping_filter_context_out->seven_point_index = env->GetIntField(clipping_filter_context_in,m_data_clipping_filter_context.seven_point_index);
    clipping_filter_context_out->data_count0_max = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.data_count0_max);
    clipping_filter_context_out->data_count0 = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.data_count0);
    clipping_filter_context_out->slope = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.slope);
    clipping_filter_context_out->up_continue_count = env->GetIntField(clipping_filter_context_in,m_data_clipping_filter_context.up_continue_count);
    clipping_filter_context_out->min_data_count = env->GetIntField(clipping_filter_context_in,m_data_clipping_filter_context.min_data_count);
    clipping_filter_context_out->up_min_data = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.up_min_data);
    jdoubleArray double_sf4_buf_array = (jdoubleArray) env->GetObjectField(clipping_filter_context_in, m_data_clipping_filter_context.sf4_buf);
    jdouble *double_sf4_buf = env->GetDoubleArrayElements(double_sf4_buf_array, 0);
    jsize double_sf4_buf_len = env->GetArrayLength(double_sf4_buf_array);

    for (int i = 0; i < double_sf4_buf_len; i++) {
        clipping_filter_context_out->sf4_buf[i] = double_sf4_buf[i];
    }

    clipping_filter_context_out->sf4_min_data = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.sf4_min_data);
    clipping_filter_context_out->sf4_min_data_index = env->GetIntField(clipping_filter_context_in,m_data_clipping_filter_context.sf4_min_data_index);
    clipping_filter_context_out->Daily_minimum_value = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.Daily_minimum_value);
    clipping_filter_context_out->last_Daily_minimum_value = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.last_Daily_minimum_value);
    clipping_filter_context_out->Daily_minimum_value_count = env->GetIntField(clipping_filter_context_in,m_data_clipping_filter_context.Daily_minimum_value_count);
    clipping_filter_context_out->Daily_minimum_value_sum = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.Daily_minimum_value_sum);
    clipping_filter_context_out->Daily_minimum_value_avg = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.Daily_minimum_value_avg);
    clipping_filter_context_out->max_data = env->GetDoubleField(clipping_filter_context_in,m_data_clipping_filter_context.max_data);

}

void clipping_filter_context_clone_c_to_java(JNIEnv *env, jni_clipping_filter_context_t *clipping_filter_src, jobject clipping_filter_context_dst){

    if (clipping_filter_src == nullptr) {
        LOGD("clipping_filter_src is null!");
        return;
    }

    if (clipping_filter_context_dst == nullptr) {
        LOGD("clipping_filter_context_dst is null!");
        return;
    }

    env->SetIntField(clipping_filter_context_dst, m_data_clipping_filter_context.error_flag,clipping_filter_src->error_flag);
    env->SetIntField(clipping_filter_context_dst, m_data_clipping_filter_context.short_ESA_flag,clipping_filter_src->short_ESA_flag);
    env->SetIntField(clipping_filter_context_dst, m_data_clipping_filter_context.count,clipping_filter_src->count);

    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.last_min_data,clipping_filter_src->last_min_data);
    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.min_data,clipping_filter_src->min_data);
    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.continue_down_count,clipping_filter_src->continue_down_count);
    env->SetIntField(clipping_filter_context_dst, m_data_clipping_filter_context.continue_down_flag,clipping_filter_src->continue_down_flag);
    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.continue_down_max_data,clipping_filter_src->continue_down_max_data);
    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.last_continue_down_max_data,clipping_filter_src->last_continue_down_max_data);
    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.continue_down_min_data,clipping_filter_src->continue_down_min_data);


    jdoubleArray double_var_windows_array = (jdoubleArray) env->GetObjectField(clipping_filter_context_dst, m_data_clipping_filter_context.CGM_var_windows);
    jdouble *double_var_windows_buf = env->GetDoubleArrayElements(double_var_windows_array, 0);
    jsize double_var_windows_len = env->GetArrayLength(double_var_windows_array);

    for (int i = 0; i < double_var_windows_len; i++) {
        double_var_windows_buf[i] = clipping_filter_src->CGM_var_windows[i];
    }

    env->SetDoubleArrayRegion(double_var_windows_array,0,double_var_windows_len,double_var_windows_buf);

    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.CGM_var_data,clipping_filter_src->CGM_var_data);
    env->SetIntField(clipping_filter_context_dst, m_data_clipping_filter_context.var_data_count,clipping_filter_src->var_data_count);

    jdoubleArray double_min_data_array = (jdoubleArray) env->GetObjectField(clipping_filter_context_dst, m_data_clipping_filter_context.min_data_buf);
    jdouble *double_min_data_buf = env->GetDoubleArrayElements(double_min_data_array, 0);
    jsize double_min_data_len = env->GetArrayLength(double_min_data_array);

    for (int i = 0; i < double_min_data_len; i++) {
        double_min_data_buf[i] = clipping_filter_src->min_data_buf[i];
    }

    env->SetDoubleArrayRegion(double_min_data_array,0,double_min_data_len,double_min_data_buf);

    env->SetIntField(clipping_filter_context_dst, m_data_clipping_filter_context.data_count,clipping_filter_src->data_count);
    env->SetIntField(clipping_filter_context_dst, m_data_clipping_filter_context.seven_point_index,clipping_filter_src->seven_point_index);
    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.data_count0_max,clipping_filter_src->data_count0_max);
    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.data_count0,clipping_filter_src->data_count0);
    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.slope,clipping_filter_src->slope);
    env->SetIntField(clipping_filter_context_dst, m_data_clipping_filter_context.up_continue_count,clipping_filter_src->up_continue_count);
    env->SetIntField(clipping_filter_context_dst, m_data_clipping_filter_context.min_data_count,clipping_filter_src->min_data_count);
    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.up_min_data,clipping_filter_src->up_min_data);

    jdoubleArray double_sf4_buf_array = (jdoubleArray) env->GetObjectField(clipping_filter_context_dst, m_data_clipping_filter_context.sf4_buf);
    jdouble *double_sf4_buf = env->GetDoubleArrayElements(double_sf4_buf_array, 0);
    jsize double_sf4_buf_len = env->GetArrayLength(double_sf4_buf_array);

    for (int i = 0; i < double_sf4_buf_len; i++) {
        double_sf4_buf[i] = clipping_filter_src->sf4_buf[i];
    }

    env->SetDoubleArrayRegion(double_sf4_buf_array,0,double_sf4_buf_len,double_sf4_buf);

    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.sf4_min_data,clipping_filter_src->sf4_min_data);
    env->SetIntField(clipping_filter_context_dst, m_data_clipping_filter_context.sf4_min_data_index,clipping_filter_src->sf4_min_data_index);

    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.Daily_minimum_value,clipping_filter_src->Daily_minimum_value);
    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.last_Daily_minimum_value,clipping_filter_src->last_Daily_minimum_value);
    env->SetIntField(clipping_filter_context_dst, m_data_clipping_filter_context.Daily_minimum_value_count,clipping_filter_src->Daily_minimum_value_count);
    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.Daily_minimum_value_sum,clipping_filter_src->Daily_minimum_value_sum);
    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.Daily_minimum_value_avg,clipping_filter_src->Daily_minimum_value_avg);
    env->SetDoubleField(clipping_filter_context_dst, m_data_clipping_filter_context.max_data,clipping_filter_src->max_data);

}

/////////////////////////////esa_compensate_context///////////////////////////////////////////////////
jobject esa_compensate_context_c_to_java(JNIEnv *env, jni_esa_compensate_context_t *c_esa_compensate_context) {
    jobject java_esa_compensate_context = env->NewObject(m_data_esa_compensate_context.clazz, m_data_esa_compensate_context.constructor);
    if (c_esa_compensate_context != NULL) {

        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.k_data, c_esa_compensate_context->k_data);
        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.ESA_min_data, c_esa_compensate_context->ESA_min_data);
        env->SetIntField(java_esa_compensate_context, m_data_esa_compensate_context.ESA_flag, c_esa_compensate_context->ESA_flag);
        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.ESA_sum, c_esa_compensate_context->ESA_sum);
        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.ESA_average, c_esa_compensate_context->ESA_average);
        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.baseline, c_esa_compensate_context->baseline);
        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.b1_data, c_esa_compensate_context->b1_data);
        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.data_12, c_esa_compensate_context->data_12);

        jsize len = NELEM(c_esa_compensate_context->fit10_x);
        jdoubleArray double_fit10_x_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(double_fit10_x_array, 0, len, c_esa_compensate_context->fit10_x);
        env->SetObjectField(java_esa_compensate_context, m_data_esa_compensate_context.fit10_x, double_fit10_x_array);

        len = NELEM(c_esa_compensate_context->fit10_y);
        jdoubleArray double_fit10_y_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(double_fit10_y_array, 0, len, c_esa_compensate_context->fit10_y);
        env->SetObjectField(java_esa_compensate_context, m_data_esa_compensate_context.fit10_y, double_fit10_y_array);

        len = NELEM(c_esa_compensate_context->fit36_x);
        jdoubleArray double_fit36_x_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(double_fit36_x_array, 0, len, c_esa_compensate_context->fit36_x);
        env->SetObjectField(java_esa_compensate_context, m_data_esa_compensate_context.fit36_x, double_fit36_x_array);

        len = NELEM(c_esa_compensate_context->fit36_y);
        jdoubleArray double_fit36_y_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(double_fit36_y_array, 0, len, c_esa_compensate_context->fit36_y);
        env->SetObjectField(java_esa_compensate_context, m_data_esa_compensate_context.fit36_y, double_fit36_y_array);

        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.last_mean_data, c_esa_compensate_context->last_mean_data);
        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.continue_mean_count, c_esa_compensate_context->continue_mean_count);
        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.bl_last_data, c_esa_compensate_context->bl_last_data);
        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.bl_last_last_data, c_esa_compensate_context->bl_last_last_data);
        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.bl_min_flag, c_esa_compensate_context->bl_min_flag);
        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.last_baseline_cgm, c_esa_compensate_context->last_baseline_cgm);
        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.slowly_chang_value, c_esa_compensate_context->slowly_chang_value);
        env->SetIntField(java_esa_compensate_context, m_data_esa_compensate_context.deferred_compensation_flag, c_esa_compensate_context->deferred_compensation_flag);
        env->SetIntField(java_esa_compensate_context, m_data_esa_compensate_context.deferred_compensation_count, c_esa_compensate_context->deferred_compensation_count);
        env->SetDoubleField(java_esa_compensate_context, m_data_esa_compensate_context.baseline_chang_value, c_esa_compensate_context->baseline_chang_value);

    }

    return java_esa_compensate_context;

}

void esa_compensate_context_java_to_c(JNIEnv *env, jobject esa_compensate_context_in, jni_esa_compensate_context_t *esa_compensate_context_out) {

    if (esa_compensate_context_in == nullptr) {
        LOGD("esa_compensate_context_in is null!");
        return;
    }

    if (esa_compensate_context_out == nullptr) {
        LOGD("esa_compensate_context_out is null!");
        return;
    }

    esa_compensate_context_out->k_data = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.k_data);
    esa_compensate_context_out->ESA_min_data = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.ESA_min_data);
    esa_compensate_context_out->ESA_flag = env->GetIntField(esa_compensate_context_in,m_data_esa_compensate_context.ESA_flag);
    esa_compensate_context_out->ESA_sum = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.ESA_sum);
    esa_compensate_context_out->ESA_average = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.ESA_average);
    esa_compensate_context_out->baseline = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.baseline);
    esa_compensate_context_out->b1_data = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.b1_data);
    esa_compensate_context_out->data_12 = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.data_12);

    jdoubleArray double_fit10_x_array = (jdoubleArray) env->GetObjectField(esa_compensate_context_in, m_data_esa_compensate_context.fit10_x);
    jdouble *double_fit10_x_buf = env->GetDoubleArrayElements(double_fit10_x_array, 0);
    jsize double_fit10_x_len = env->GetArrayLength(double_fit10_x_array);

    for (int i = 0; i < double_fit10_x_len; i++) {
        esa_compensate_context_out->fit10_x[i] = double_fit10_x_buf[i];
    }

    jdoubleArray double_fit10_y_array = (jdoubleArray) env->GetObjectField(esa_compensate_context_in, m_data_esa_compensate_context.fit10_y);
    jdouble *double_fit10_y_buf = env->GetDoubleArrayElements(double_fit10_y_array, 0);
    jsize double_fit10_y_len = env->GetArrayLength(double_fit10_y_array);

    for (int i = 0; i < double_fit10_y_len; i++) {
        esa_compensate_context_out->fit10_y[i] = double_fit10_y_buf[i];
    }

    jdoubleArray double_fit36_x_array = (jdoubleArray) env->GetObjectField(esa_compensate_context_in, m_data_esa_compensate_context.fit36_x);
    jdouble *double_fit36_x_buf = env->GetDoubleArrayElements(double_fit36_x_array, 0);
    jsize double_fit36_x_len = env->GetArrayLength(double_fit36_x_array);

    for (int i = 0; i < double_fit36_x_len; i++) {
        esa_compensate_context_out->fit36_x[i] = double_fit36_x_buf[i];
    }

    jdoubleArray double_nihe36_y_array = (jdoubleArray) env->GetObjectField(esa_compensate_context_in, m_data_esa_compensate_context.fit36_y);
    jdouble *double_nihe36_y_buf = env->GetDoubleArrayElements(double_nihe36_y_array, 0);
    jsize double_nihe36_y_len = env->GetArrayLength(double_nihe36_y_array);
    for (int i = 0; i < double_nihe36_y_len; i++) {
        esa_compensate_context_out->fit36_y[i] = double_nihe36_y_buf[i];
    }


    esa_compensate_context_out->last_mean_data = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.last_mean_data);
    esa_compensate_context_out->continue_mean_count = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.continue_mean_count);
    esa_compensate_context_out->bl_last_data = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.bl_last_data);
    esa_compensate_context_out->bl_last_last_data = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.bl_last_last_data);
    esa_compensate_context_out->bl_min_flag = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.bl_min_flag);

    esa_compensate_context_out->last_baseline_cgm = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.last_baseline_cgm);
    esa_compensate_context_out->slowly_chang_value = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.slowly_chang_value);
    esa_compensate_context_out->deferred_compensation_flag = env->GetIntField(esa_compensate_context_in,m_data_esa_compensate_context.deferred_compensation_flag);
    esa_compensate_context_out->deferred_compensation_count = env->GetIntField(esa_compensate_context_in,m_data_esa_compensate_context.deferred_compensation_count);
    esa_compensate_context_out->baseline_chang_value = env->GetDoubleField(esa_compensate_context_in,m_data_esa_compensate_context.baseline_chang_value);

}

void esa_compensate_context_clone_c_to_java(JNIEnv *env, jni_esa_compensate_context_t *esa_compensate_src, jobject esa_compensate_context_dst) {

    if (esa_compensate_src == nullptr) {
        LOGD("esa_compensate_src is null!");
        return;
    }

    if (esa_compensate_context_dst == nullptr) {
        LOGD("esa_compensate_context_dst is null!");
        return;
    }

    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.k_data,esa_compensate_src->k_data);
    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.ESA_min_data,esa_compensate_src->ESA_min_data);
    env->SetIntField(esa_compensate_context_dst, m_data_esa_compensate_context.ESA_flag,esa_compensate_src->ESA_flag);
    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.ESA_sum,esa_compensate_src->ESA_sum);
    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.ESA_average,esa_compensate_src->ESA_average);
    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.baseline,esa_compensate_src->baseline);
    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.b1_data,esa_compensate_src->b1_data);
    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.data_12,esa_compensate_src->data_12);

    jdoubleArray double_fit10_x_array = (jdoubleArray) env->GetObjectField(esa_compensate_context_dst, m_data_esa_compensate_context.fit10_x);
    jdouble *double_fit10_x_buf = env->GetDoubleArrayElements(double_fit10_x_array, 0);
    jsize double_fit10_x_len = env->GetArrayLength(double_fit10_x_array);

    for (int i = 0; i < double_fit10_x_len; i++) {
        double_fit10_x_buf[i] = esa_compensate_src->fit10_x[i];
    }

    env->SetDoubleArrayRegion(double_fit10_x_array,0,double_fit10_x_len,double_fit10_x_buf);


    jdoubleArray double_fit10_y_array = (jdoubleArray) env->GetObjectField(esa_compensate_context_dst, m_data_esa_compensate_context.fit10_y);
    jdouble *double_fit10_y_buf = env->GetDoubleArrayElements(double_fit10_y_array, 0);
    jsize double_fit10_y_len = env->GetArrayLength(double_fit10_y_array);

    for (int i = 0; i < double_fit10_y_len; i++) {
        double_fit10_y_buf[i] = esa_compensate_src->fit10_y[i];
    }

    env->SetDoubleArrayRegion(double_fit10_y_array,0,double_fit10_y_len,double_fit10_y_buf);

    jdoubleArray double_fit36_x_array = (jdoubleArray) env->GetObjectField(esa_compensate_context_dst, m_data_esa_compensate_context.fit36_x);
    jdouble *double_fit36_x_buf = env->GetDoubleArrayElements(double_fit36_x_array, 0);
    jsize double_fit36_x_len = env->GetArrayLength(double_fit36_x_array);

    for (int i = 0; i < double_fit36_x_len; i++) {
        double_fit36_x_buf[i] = esa_compensate_src->fit36_x[i];
    }

    env->SetDoubleArrayRegion(double_fit36_x_array,0,double_fit36_x_len,double_fit36_x_buf);

    jdoubleArray double_fit36_y_array = (jdoubleArray) env->GetObjectField(esa_compensate_context_dst, m_data_esa_compensate_context.fit36_y);
    jdouble *double_fit36_y_buf = env->GetDoubleArrayElements(double_fit36_y_array, 0);
    jsize double_fit36_y_len = env->GetArrayLength(double_fit36_y_array);

    for (int i = 0; i < double_fit36_y_len; i++) {
        double_fit36_y_buf[i] = esa_compensate_src->fit36_y[i];
    }

    env->SetDoubleArrayRegion(double_fit36_y_array,0,double_fit36_y_len,double_fit36_y_buf);
    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.last_mean_data,esa_compensate_src->last_mean_data);
    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.continue_mean_count,esa_compensate_src->continue_mean_count);
    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.bl_last_data,esa_compensate_src->bl_last_data);
    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.bl_last_last_data,esa_compensate_src->bl_last_last_data);
    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.bl_min_flag,esa_compensate_src->bl_min_flag);
    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.last_baseline_cgm,esa_compensate_src->last_baseline_cgm);
    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.slowly_chang_value,esa_compensate_src->slowly_chang_value);
    env->SetIntField(esa_compensate_context_dst, m_data_esa_compensate_context.deferred_compensation_flag,esa_compensate_src->deferred_compensation_flag);
    env->SetIntField(esa_compensate_context_dst, m_data_esa_compensate_context.deferred_compensation_count,esa_compensate_src->deferred_compensation_count);
    env->SetDoubleField(esa_compensate_context_dst, m_data_esa_compensate_context.baseline_chang_value,esa_compensate_src->baseline_chang_value);
}

///////////////////////////////cmg_calibration_context////////////////////////////////////////////////////
jobject cgm_calibration_context_c_to_java(JNIEnv *env, jni_cgm_calibration_context_t *c_cgm_calibration_context){

    jobject java_cgm_calibration_context = env->NewObject(m_data_cgm_calibration_context.clazz, m_data_cgm_calibration_context.constructor);

    if (c_cgm_calibration_context != NULL) {

        env->SetIntField(java_cgm_calibration_context, m_data_cgm_calibration_context.calibration_flag, c_cgm_calibration_context->calibration_flag);
        env->SetIntField(java_cgm_calibration_context, m_data_cgm_calibration_context.bg_index, c_cgm_calibration_context->bg_index);
        env->SetDoubleField(java_cgm_calibration_context, m_data_cgm_calibration_context.last_bg, c_cgm_calibration_context->last_bg);
        env->SetDoubleField(java_cgm_calibration_context, m_data_cgm_calibration_context.last_sf4_data, c_cgm_calibration_context->last_sf4_data);
        env->SetDoubleField(java_cgm_calibration_context, m_data_cgm_calibration_context.last_last_sf4_data, c_cgm_calibration_context->last_last_sf4_data);

    }
    return  java_cgm_calibration_context;
}

void cgm_calibration_context_java_to_c(JNIEnv *env, jobject cgm_calibration_context_in, jni_cgm_calibration_context_t *cgm_calibration_context_out){

    if (cgm_calibration_context_in == nullptr) {
        LOGD("cgm_calibration_context_in is null!");
        return;
    }

    if (cgm_calibration_context_out == nullptr) {
        LOGD("cgm_calibration_context_out is null!");
        return;
    }

    cgm_calibration_context_out->calibration_flag = env->GetIntField(cgm_calibration_context_in, m_data_cgm_calibration_context.calibration_flag);
    cgm_calibration_context_out->bg_index = env->GetIntField(cgm_calibration_context_in, m_data_cgm_calibration_context.bg_index);
    cgm_calibration_context_out->last_bg = env->GetDoubleField(cgm_calibration_context_in, m_data_cgm_calibration_context.last_bg);
    cgm_calibration_context_out->last_sf4_data = env->GetDoubleField(cgm_calibration_context_in, m_data_cgm_calibration_context.last_sf4_data);
    cgm_calibration_context_out->last_last_sf4_data = env->GetDoubleField(cgm_calibration_context_in, m_data_cgm_calibration_context.last_last_sf4_data);
}

void cgm_calibration_context_clone_c_to_java(JNIEnv *env, jni_cgm_calibration_context_t *cgm_calibration_src, jobject cgm_calibration_context_dst){

    if (cgm_calibration_src == nullptr) {
        LOGD("cgm_calibration_src is null!");
        return;
    }

    if (cgm_calibration_context_dst == nullptr) {
        LOGD("cgm_calibration_context_dst is null!");
        return;
    }

    env->SetIntField(cgm_calibration_context_dst, m_data_cgm_calibration_context.calibration_flag, cgm_calibration_src->calibration_flag);
    env->SetIntField(cgm_calibration_context_dst, m_data_cgm_calibration_context.bg_index, cgm_calibration_src->bg_index);
    env->SetDoubleField(cgm_calibration_context_dst, m_data_cgm_calibration_context.last_bg, cgm_calibration_src->last_bg);
    env->SetDoubleField(cgm_calibration_context_dst, m_data_cgm_calibration_context.last_sf4_data, cgm_calibration_src->last_sf4_data);
    env->SetDoubleField(cgm_calibration_context_dst, m_data_cgm_calibration_context.last_last_sf4_data, cgm_calibration_src->last_last_sf4_data);
}

///////////////////////////////regular_deconvolution_context////////////////////////////////////////////////////
jobject regular_deconvolution_context_c_to_java(JNIEnv *env, jni_regular_deconvolution_context_t *c_regular_deconvolution_context){

    jobject java_regular_deconvolution_context = env->NewObject(m_data_regular_deconvolution_context.clazz, m_data_regular_deconvolution_context.constructor);

    if (c_regular_deconvolution_context != NULL) {

        jsize len = NELEM(c_regular_deconvolution_context->ig_value_buf);
        jdoubleArray double_ig_value_array = env->NewDoubleArray(len);
        env->SetDoubleArrayRegion(double_ig_value_array, 0, len, c_regular_deconvolution_context->ig_value_buf);
        env->SetObjectField(java_regular_deconvolution_context, m_data_regular_deconvolution_context.ig_value_buf, double_ig_value_array);

    }
    return  java_regular_deconvolution_context;
}

void regular_deconvolution_context_java_to_c(JNIEnv *env, jobject regular_deconvolution_context_in, jni_regular_deconvolution_context_t *regular_deconvolution_context_out){

    if (regular_deconvolution_context_in == nullptr) {
        LOGD("regular_deconvolution_context_in is null!");
        return;
    }

    if (regular_deconvolution_context_out == nullptr) {
        LOGD("regular_deconvolution_context_out is null!");
        return;
    }

    jdoubleArray double_ig_value_array = (jdoubleArray) env->GetObjectField(regular_deconvolution_context_in, m_data_regular_deconvolution_context.ig_value_buf);
    jdouble *double_ig_value_buf = env->GetDoubleArrayElements(double_ig_value_array, 0);
    jsize double_ig_value_len = env->GetArrayLength(double_ig_value_array);
    for (int i = 0; i < double_ig_value_len; i++) {
        regular_deconvolution_context_out->ig_value_buf[i] = double_ig_value_buf[i];
    }

}

void regular_deconvolution_context_clone_c_to_java(JNIEnv *env, jni_regular_deconvolution_context_t *regular_deconvolution_src, jobject regular_deconvolution_context_dst){

    if (regular_deconvolution_src == nullptr) {
        LOGD("regular_deconvolution_src is null!");
        return;
    }

    if (regular_deconvolution_context_dst == nullptr) {
        LOGD("regular_deconvolution_context_dst is null!");
        return;
    }

    jdoubleArray double_ig_value_array = (jdoubleArray) env->GetObjectField(regular_deconvolution_context_dst, m_data_regular_deconvolution_context.ig_value_buf);
    jdouble *double_ig_value_buf = env->GetDoubleArrayElements(double_ig_value_array, 0);
    jsize double_ig_value_len = env->GetArrayLength(double_ig_value_array);

    for (int i = 0; i < double_ig_value_len; i++) {
        double_ig_value_buf[i] = regular_deconvolution_src->ig_value_buf[i];
    }

    env->SetDoubleArrayRegion(double_ig_value_array,0,double_ig_value_len,double_ig_value_buf);
}

///////////////////////////////arrow_direction_context///////////////////////////////////////////////////////////////
jobject arrow_direction_context_c_to_java(JNIEnv *env, jni_arrow_direction_context_t *c_arrow_direction_context){

    jobject java_arrow_direction_context = env->NewObject(m_data_arrow_direction_context.clazz, m_data_arrow_direction_context.constructor);

    if(c_arrow_direction_context != NULL){

        env->SetIntField(java_arrow_direction_context, m_data_arrow_direction_context.blood_glucose_trend, c_arrow_direction_context->blood_glucose_trend);
        env->SetIntField(java_arrow_direction_context, m_data_arrow_direction_context.last_blood_glucose_trend, c_arrow_direction_context->last_blood_glucose_trend);

        env->SetDoubleField(java_arrow_direction_context, m_data_arrow_direction_context.arrow_direction_data, c_arrow_direction_context->arrow_direction_data);
        env->SetDoubleField(java_arrow_direction_context, m_data_arrow_direction_context.last_arrow_direction_data, c_arrow_direction_context->last_arrow_direction_data);
        env->SetDoubleField(java_arrow_direction_context, m_data_arrow_direction_context.last_last_arrow_direction_data, c_arrow_direction_context->last_last_arrow_direction_data);

        env->SetIntField(java_arrow_direction_context, m_data_arrow_direction_context.rise_trend_count, c_arrow_direction_context->rise_trend_count);
        env->SetIntField(java_arrow_direction_context, m_data_arrow_direction_context.decline_trend_count, c_arrow_direction_context->decline_trend_count);
        env->SetIntField(java_arrow_direction_context, m_data_arrow_direction_context.horizontal_direction_count, c_arrow_direction_context->horizontal_direction_count);
        env->SetIntField(java_arrow_direction_context, m_data_arrow_direction_context.arrow_direction_count, c_arrow_direction_context->arrow_direction_count);

    }
    return java_arrow_direction_context;
}

void arrow_direction_context_java_to_c(JNIEnv *env, jobject arrow_direction_context_in, jni_arrow_direction_context_t *arrow_direction_context_out){

    if (arrow_direction_context_in == nullptr) {
        LOGD("arrow_direction_context_in is null!");
        return;
    }

    if (arrow_direction_context_out == nullptr) {
        LOGD("arrow_direction_context_out is null!");
        return;
    }

    arrow_direction_context_out->blood_glucose_trend = env->GetIntField(arrow_direction_context_in,m_data_arrow_direction_context.blood_glucose_trend);
    arrow_direction_context_out->last_blood_glucose_trend = env->GetIntField(arrow_direction_context_in,m_data_arrow_direction_context.last_blood_glucose_trend);
    arrow_direction_context_out->arrow_direction_data = env->GetDoubleField(arrow_direction_context_in,m_data_arrow_direction_context.arrow_direction_data);
    arrow_direction_context_out->last_arrow_direction_data = env->GetDoubleField(arrow_direction_context_in,m_data_arrow_direction_context.last_arrow_direction_data);
    arrow_direction_context_out->last_last_arrow_direction_data = env->GetDoubleField(arrow_direction_context_in,m_data_arrow_direction_context.last_last_arrow_direction_data);
    arrow_direction_context_out->rise_trend_count = env->GetIntField(arrow_direction_context_in,m_data_arrow_direction_context.rise_trend_count);
    arrow_direction_context_out->decline_trend_count = env->GetIntField(arrow_direction_context_in,m_data_arrow_direction_context.decline_trend_count);
    arrow_direction_context_out->horizontal_direction_count = env->GetIntField(arrow_direction_context_in,m_data_arrow_direction_context.horizontal_direction_count);
    arrow_direction_context_out->arrow_direction_count = env->GetIntField(arrow_direction_context_in,m_data_arrow_direction_context.arrow_direction_count);

}

void arrow_direction_context_clone_c_to_java(JNIEnv *env, jni_arrow_direction_context_t *arrow_direction_src, jobject arrow_direction_context_dst){

    if (arrow_direction_src == nullptr) {
        LOGD("arrow_direction_src is null!");
        return;
    }

    if (arrow_direction_context_dst == nullptr) {
        LOGD("arrow_direction_context_dst is null!");
        return;
    }

    env->SetIntField(arrow_direction_context_dst, m_data_arrow_direction_context.blood_glucose_trend,arrow_direction_src->blood_glucose_trend);
    env->SetIntField(arrow_direction_context_dst, m_data_arrow_direction_context.last_blood_glucose_trend,arrow_direction_src->last_blood_glucose_trend);
    env->SetDoubleField(arrow_direction_context_dst, m_data_arrow_direction_context.arrow_direction_data,arrow_direction_src->arrow_direction_data);
    env->SetDoubleField(arrow_direction_context_dst, m_data_arrow_direction_context.last_arrow_direction_data,arrow_direction_src->last_arrow_direction_data);
    env->SetDoubleField(arrow_direction_context_dst, m_data_arrow_direction_context.last_last_arrow_direction_data,arrow_direction_src->last_last_arrow_direction_data);
    env->SetIntField(arrow_direction_context_dst, m_data_arrow_direction_context.rise_trend_count,arrow_direction_src->rise_trend_count);
    env->SetIntField(arrow_direction_context_dst, m_data_arrow_direction_context.decline_trend_count,arrow_direction_src->decline_trend_count);
    env->SetIntField(arrow_direction_context_dst, m_data_arrow_direction_context.horizontal_direction_count,arrow_direction_src->horizontal_direction_count);
    env->SetIntField(arrow_direction_context_dst, m_data_arrow_direction_context.arrow_direction_count,arrow_direction_src->arrow_direction_count);
}

//////////////////////////////////////////////////////////////////////
jobject algorithm_context_c_to_java(JNIEnv *env, jni_algorithm_context_t *c_algorithm_context){

    if(c_algorithm_context != NULL) {
        jobject java_judgment_context = judgment_context_c_to_java(env, &(c_algorithm_context->mJudgmentContext));

        jobject java_current_correction_context = current_correction_context_c_to_java(env, &(c_algorithm_context->mCurrentCorrectionContext));

        jobject java_kalman_context = kalman_context_c_to_java(env, &(c_algorithm_context->mKalmanContext));

        jobject java_filter1_context = filter_context_c_to_java(env, &(c_algorithm_context->mFilter1Context));
        jobject java_filter2_context = filter_context_c_to_java(env, &(c_algorithm_context->mFilter2Context));

        jobject java_cal_baseline_context = cal_baseline_context_c_to_java(env, &(c_algorithm_context->mCalBaselineContext));
        jobject java_clipping_filter_context = clipping_filter_context_c_to_java(env, &(c_algorithm_context->mClippingFilterContext));

        jobject java_esa_compensate_context = esa_compensate_context_c_to_java(env, &(c_algorithm_context->mESACompensateContext));

        jobject java_cgm_calibration_context = cgm_calibration_context_c_to_java(env, &(c_algorithm_context->mCGMCalibrationContext));

        jobject java_regular_deconvolution_context = regular_deconvolution_context_c_to_java(env, &(c_algorithm_context->mRegularDeconvolutionContext));
        jobject java_arrow_direction_context = arrow_direction_context_c_to_java(env, &(c_algorithm_context->mArrowDirectionContext));

        jobject java_algorithm_context = env->NewObject(m_data_algorithm_context.clazz, m_data_algorithm_context.constructor);
        env->SetIntField(java_algorithm_context, m_data_algorithm_context.esa_calibration_enable, c_algorithm_context->esa_calibration_enable);
        env->SetIntField(java_algorithm_context, m_data_algorithm_context.finger_blood_calibration_enable, c_algorithm_context->finger_blood_calibration_enable);

        env->SetDoubleField(java_algorithm_context, m_data_algorithm_context.IG_data, c_algorithm_context->IG_data);
        env->SetDoubleField(java_algorithm_context, m_data_algorithm_context.last_IG_data, c_algorithm_context->last_IG_data);
        env->SetIntField(java_algorithm_context, m_data_algorithm_context.cgm_warning, c_algorithm_context->cgm_warning);
        env->SetIntField(java_algorithm_context, m_data_algorithm_context.cgm_current_abnormal, c_algorithm_context->cgm_current_abnormal);
        env->SetIntField(java_algorithm_context, m_data_algorithm_context.cgm_temp_abnormal, c_algorithm_context->cgm_temp_abnormal);
        env->SetIntField(java_algorithm_context, m_data_algorithm_context.cgm_blood_glucose_trend, c_algorithm_context->cgm_blood_glucose_trend);

        jsize temp_version_buf_len = MAX_VERSION_NAME_LEN;
        jchar tmp_version_buf[MAX_VERSION_NAME_LEN];
        jcharArray temp_version_array = env->NewCharArray(temp_version_buf_len);
        memset(tmp_version_buf,0x0,MAX_VERSION_NAME_LEN);

        for(int i=0;i<MAX_VERSION_NAME_LEN;i++){
            tmp_version_buf[i] = c_algorithm_context->version_name[i];
        }

        env->SetCharArrayRegion(temp_version_array, 0, temp_version_buf_len, tmp_version_buf);
        env->SetObjectField(java_algorithm_context, m_data_algorithm_context.version_name, temp_version_array);

        env->SetObjectField(java_algorithm_context, m_data_algorithm_context.mJudgmentContext, java_judgment_context);

        env->SetObjectField(java_algorithm_context, m_data_algorithm_context.mCurrentCorrectionContext, java_current_correction_context);

        env->SetObjectField(java_algorithm_context, m_data_algorithm_context.mKalmanContext, java_kalman_context);

        env->SetObjectField(java_algorithm_context, m_data_algorithm_context.mFilter1Context, java_filter1_context);
        env->SetObjectField(java_algorithm_context, m_data_algorithm_context.mFilter2Context, java_filter2_context);

        env->SetObjectField(java_algorithm_context, m_data_algorithm_context.mCalBaselineContext, java_cal_baseline_context);

        env->SetObjectField(java_algorithm_context, m_data_algorithm_context.mClippingFilterContext, java_clipping_filter_context);

        env->SetObjectField(java_algorithm_context, m_data_algorithm_context.mESACompensateContext, java_esa_compensate_context);

        env->SetObjectField(java_algorithm_context, m_data_algorithm_context.mCgmCalibrationContext, java_cgm_calibration_context);

        env->SetObjectField(java_algorithm_context, m_data_algorithm_context.mRegularDeconvolutionContext, java_regular_deconvolution_context);
        env->SetObjectField(java_algorithm_context, m_data_algorithm_context.mArrowDirectionContext, java_arrow_direction_context);

        return java_algorithm_context;
    }

    return NULL;
}

void algorithm_context_java_to_c(JNIEnv *env, jobject algorithm_context_in, jni_algorithm_context_t *algorithm_context_out){

    if (algorithm_context_in == nullptr) {
        LOGD("algorithm_context_in is null!");
        return;
    }

    if (algorithm_context_out == nullptr) {
        LOGD("algorithm_context_out is null!");
        return;
    }

    algorithm_context_out->esa_calibration_enable = env->GetIntField(algorithm_context_in,m_data_algorithm_context.esa_calibration_enable);
    algorithm_context_out->finger_blood_calibration_enable = env->GetIntField(algorithm_context_in,m_data_algorithm_context.finger_blood_calibration_enable);

    jcharArray char_ver_data_array = (jcharArray) env->GetObjectField(algorithm_context_in, m_data_algorithm_context.version_name);
    jchar *char_ver_data_buf = env->GetCharArrayElements(char_ver_data_array, 0);
    jsize char_ver_data_len = env->GetArrayLength(char_ver_data_array);

    for (int i = 0; i < char_ver_data_len; i++) {
        algorithm_context_out->version_name[i] = char_ver_data_buf[i];
    }

    algorithm_context_out->IG_data = env->GetDoubleField(algorithm_context_in,m_data_algorithm_context.IG_data);
    algorithm_context_out->last_IG_data = env->GetDoubleField(algorithm_context_in,m_data_algorithm_context.last_IG_data);
    algorithm_context_out->cgm_warning = env->GetIntField(algorithm_context_in,m_data_algorithm_context.cgm_warning);
    algorithm_context_out->cgm_current_abnormal = env->GetIntField(algorithm_context_in,m_data_algorithm_context.cgm_current_abnormal);
    algorithm_context_out->cgm_temp_abnormal = env->GetIntField(algorithm_context_in,m_data_algorithm_context.cgm_temp_abnormal);
    algorithm_context_out->cgm_blood_glucose_trend = env->GetIntField(algorithm_context_in,m_data_algorithm_context.cgm_blood_glucose_trend);
//////////////////////judgment_context//////////////////////////
    jobject java_judgment_context = env->GetObjectField(algorithm_context_in, m_data_algorithm_context.mJudgmentContext);
    jni_judgment_context_t *p_judgment_context = &algorithm_context_out->mJudgmentContext;
    judgment_context_java_to_c(env, java_judgment_context, p_judgment_context);

//////////////////////mCurrentCorrectionContext//////////////////////////
    jobject java_current_correction_context = env->GetObjectField(algorithm_context_in, m_data_algorithm_context.mCurrentCorrectionContext);
    jni_current_correction_context_t *p_current_correction_context =  &algorithm_context_out->mCurrentCorrectionContext;
    current_correction_context_java_to_c(env, java_current_correction_context, p_current_correction_context);

//////////////////////mKalmanContext//////////////////////////
    jobject java_kalman_context = env->GetObjectField(algorithm_context_in, m_data_algorithm_context.mKalmanContext);
    jni_kalman_context_t *p_kalman_context = &algorithm_context_out->mKalmanContext;
    kalman_context_java_to_c(env, java_kalman_context, p_kalman_context);

//////////////////////mFilter1Context//////////////////////////
    jobject java_filter1_context = env->GetObjectField(algorithm_context_in, m_data_algorithm_context.mFilter1Context);
    jni_filter_context_t *p_filter1_context = &algorithm_context_out->mFilter1Context;
    filter_context_java_to_c(env, java_filter1_context, p_filter1_context);

//////////////////////mFilter2Context//////////////////////////
    jobject java_filter2_context = env->GetObjectField(algorithm_context_in, m_data_algorithm_context.mFilter2Context);
    jni_filter_context_t *p_filter2_context = &algorithm_context_out->mFilter2Context;
    filter_context_java_to_c(env, java_filter2_context, p_filter2_context);

//////////////////////mCalBaselineContext//////////////////////////
    jobject java_cal_baseline_context = env->GetObjectField(algorithm_context_in, m_data_algorithm_context.mCalBaselineContext);
    jni_cal_baseline_context_t *p_cal_baseline_context = &algorithm_context_out->mCalBaselineContext;
    cal_baseline_context_java_to_c(env, java_cal_baseline_context, p_cal_baseline_context);


//////////////////////mClippingFilterContext//////////////////////////
    jobject java_clipping_filter_context = env->GetObjectField(algorithm_context_in, m_data_algorithm_context.mClippingFilterContext);
    jni_clipping_filter_context_t *p_clipping_filter_context = &algorithm_context_out->mClippingFilterContext;
    clipping_filter_context_java_to_c(env, java_clipping_filter_context, p_clipping_filter_context);

//////////////////////mESACompensateContext//////////////////////////
    jobject java_esa_compensate_context = env->GetObjectField(algorithm_context_in, m_data_algorithm_context.mESACompensateContext);
    jni_esa_compensate_context_t *p_esa_compensate_context = &algorithm_context_out->mESACompensateContext;
    esa_compensate_context_java_to_c(env, java_esa_compensate_context, p_esa_compensate_context);

    //////////////////////mCGMCalibrationContext//////////////////////////
    jobject java_cgm_calibration_context = env->GetObjectField(algorithm_context_in, m_data_algorithm_context.mCgmCalibrationContext);
    jni_cgm_calibration_context_t *p_cgm_calibration_context = &algorithm_context_out->mCGMCalibrationContext;
    cgm_calibration_context_java_to_c(env, java_cgm_calibration_context, p_cgm_calibration_context);

//////////////////////mRegularDeconvolutionContext//////////////////////////
    jobject java_regular_deconvolution_context = env->GetObjectField(algorithm_context_in, m_data_algorithm_context.mRegularDeconvolutionContext);
    jni_regular_deconvolution_context_t *p_regular_deconvolution_context = &algorithm_context_out->mRegularDeconvolutionContext;
    regular_deconvolution_context_java_to_c(env, java_regular_deconvolution_context, p_regular_deconvolution_context);

//////////////////////mArrowDirectionContext//////////////////////////
    jobject java_arrow_direction_context = env->GetObjectField(algorithm_context_in, m_data_algorithm_context.mArrowDirectionContext);
    jni_arrow_direction_context_t *c_arrow_direction_context = &algorithm_context_out->mArrowDirectionContext;
    arrow_direction_context_java_to_c(env, java_arrow_direction_context, c_arrow_direction_context);

}

void algorithm_context_clone_c_to_java(JNIEnv *env, jni_algorithm_context_t *algorithm_context_src, jobject algorithm_context_dst){

    if (algorithm_context_src == nullptr) {
        LOGD("algorithm_context_src is null!");
        return;
    }

    if (algorithm_context_dst == nullptr) {
        LOGD("algorithm_context_dst is null!");
        return;
    }

    env->SetIntField(algorithm_context_dst, m_data_algorithm_context.esa_calibration_enable, algorithm_context_src->esa_calibration_enable);

    env->SetIntField(algorithm_context_dst, m_data_algorithm_context.finger_blood_calibration_enable, algorithm_context_src->finger_blood_calibration_enable);

    env->SetDoubleField(algorithm_context_dst, m_data_algorithm_context.IG_data, algorithm_context_src->IG_data);

    env->SetDoubleField(algorithm_context_dst, m_data_algorithm_context.last_IG_data, algorithm_context_src->last_IG_data);

    env->SetIntField(algorithm_context_dst, m_data_algorithm_context.cgm_warning, algorithm_context_src->cgm_warning);

    env->SetIntField(algorithm_context_dst, m_data_algorithm_context.cgm_current_abnormal, algorithm_context_src->cgm_current_abnormal);

    env->SetIntField(algorithm_context_dst, m_data_algorithm_context.cgm_temp_abnormal, algorithm_context_src->cgm_temp_abnormal);

    env->SetIntField(algorithm_context_dst, m_data_algorithm_context.cgm_blood_glucose_trend, algorithm_context_src->cgm_blood_glucose_trend);

    //////////////////////judgment_context//////////////////////////
    jobject java_judgment_context_dst = env->GetObjectField(algorithm_context_dst, m_data_algorithm_context.mJudgmentContext);
    judgment_context_clone_c_to_java(env, &(algorithm_context_src->mJudgmentContext), java_judgment_context_dst);



    //////////////////////mCurrentCorrectionContext//////////////////////////
    jobject java_current_correction_context_dst = env->GetObjectField(algorithm_context_dst, m_data_algorithm_context.mCurrentCorrectionContext);
    current_correction_context_clone_c_to_java(env, &(algorithm_context_src->mCurrentCorrectionContext), java_current_correction_context_dst);

    //////////////////////mKalmanContext//////////////////////////
    jobject java_kalman_context_dst = env->GetObjectField(algorithm_context_dst, m_data_algorithm_context.mKalmanContext);
    kalman_contex_clone_c_to_java(env, &(algorithm_context_src->mKalmanContext), java_kalman_context_dst);

    //////////////////////mFilter1Context//////////////////////////
    jobject java_filter1_context_dst = env->GetObjectField(algorithm_context_dst, m_data_algorithm_context.mFilter1Context);
    filter_context_clone_c_to_java(env, &(algorithm_context_src->mFilter1Context), java_filter1_context_dst);

    //////////////////////mFilter2Context//////////////////////////
    jobject java_filter2_context_dst = env->GetObjectField(algorithm_context_dst, m_data_algorithm_context.mFilter2Context);
    filter_context_clone_c_to_java(env, &(algorithm_context_src->mFilter2Context), java_filter2_context_dst);

    //////////////////////mCalBaselineContext//////////////////////////
    jobject java_cal_baseline_context_dst = env->GetObjectField(algorithm_context_dst, m_data_algorithm_context.mCalBaselineContext);
    cal_baseline_context_clone_c_to_java(env, &(algorithm_context_src->mCalBaselineContext), java_cal_baseline_context_dst);

    //////////////////////mClippingFilterContext//////////////////////////
    jobject java_clipping_filter_context_dst = env->GetObjectField(algorithm_context_dst, m_data_algorithm_context.mClippingFilterContext);
    clipping_filter_context_clone_c_to_java(env, &(algorithm_context_src->mClippingFilterContext), java_clipping_filter_context_dst);

    //////////////////////mESACompensateContext//////////////////////////
    jobject java_esa_compensate_context_dst = env->GetObjectField(algorithm_context_dst, m_data_algorithm_context.mESACompensateContext);
    esa_compensate_context_clone_c_to_java(env, &(algorithm_context_src->mESACompensateContext), java_esa_compensate_context_dst);

    //////////////////////mCGMCalibrationContext//////////////////////////
    jobject java_cgm_calibration_context_dst = env->GetObjectField(algorithm_context_dst, m_data_algorithm_context.mCgmCalibrationContext);
    cgm_calibration_context_clone_c_to_java(env, &(algorithm_context_src->mCGMCalibrationContext), java_cgm_calibration_context_dst);

    //////////////////////mRegularDeconvolutionContext//////////////////////////
    jobject java_regular_deconvolution_context_dst = env->GetObjectField(algorithm_context_dst, m_data_algorithm_context.mRegularDeconvolutionContext);
    regular_deconvolution_context_clone_c_to_java(env, &(algorithm_context_src->mRegularDeconvolutionContext), java_regular_deconvolution_context_dst);

    //////////////////////mArrowDirectionContext//////////////////////////
    jobject java_arrow_direction_context_dst = env->GetObjectField(algorithm_context_dst, m_data_algorithm_context.mArrowDirectionContext);
    arrow_direction_context_clone_c_to_java(env, &(algorithm_context_src->mArrowDirectionContext), java_arrow_direction_context_dst);

}




