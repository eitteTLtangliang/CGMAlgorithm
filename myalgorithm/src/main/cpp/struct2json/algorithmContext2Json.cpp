//
// Created by l.tan on 2021/6/2.
//


#include "algorithmContext2Json.h"

cJSON *struct_to_json(jni_algorithm_context_t* struct_obj) {
    jni_algorithm_context_t *struct_algorithm = struct_obj;

    /* create algorithmicContext JSON object */
    s2j_create_json_obj(json_algorithm);

    /* serialize data to algorithmicContext JSON object. */
    s2j_json_set_basic_element(json_algorithm, struct_algorithm, int, esa_calibration_enable);
    s2j_json_set_basic_element(json_algorithm, struct_algorithm, int, finger_blood_calibration_enable);
    s2j_json_set_basic_element(json_algorithm, struct_algorithm, string,version_name);
    s2j_json_set_basic_element(json_algorithm, struct_algorithm, double, IG_data);
    s2j_json_set_basic_element(json_algorithm, struct_algorithm, double, last_IG_data);
    s2j_json_set_basic_element(json_algorithm, struct_algorithm, int, cgm_warning);
    s2j_json_set_basic_element(json_algorithm, struct_algorithm, int, cgm_current_abnormal);
    s2j_json_set_basic_element(json_algorithm, struct_algorithm, int, cgm_temp_abnormal);
    s2j_json_set_basic_element(json_algorithm, struct_algorithm, int, cgm_blood_glucose_trend);


    ///jni_judgment_context_t
    s2j_json_set_struct_element(json_judgment,json_algorithm,struct_judgment,struct_algorithm,jni_judgment_context_t,mJudgmentContext);
    ///第二级 mJudgmentContext下的子属性
    s2j_json_set_array_element(json_judgment,struct_judgment,double,abnormal_flag_buf,MAX_ABNORMAL_FLAG_SIZE);
    s2j_json_set_basic_element(json_judgment,struct_judgment,double,current_abnormal_flag_count);
    s2j_json_set_basic_element(json_judgment,struct_judgment,int,abnormal_count);
    s2j_json_set_struct_element(json_current_judgment,json_judgment,struct_current_judgment,struct_judgment,jni_current_judgment_context_t,m_current_jud_context);
    ///第三级 jni_current_judgment_context_t 下的子属性
    s2j_json_set_basic_element(json_current_judgment,struct_current_judgment,double,last_current);
    s2j_json_set_basic_element(json_current_judgment,struct_current_judgment,int,abnormal_flag);
    s2j_json_set_array_element(json_current_judgment,struct_current_judgment,double,temp_data_buf,CURRENT_JUDGMENT_NUM_TEMP_DATA);
    s2j_json_set_basic_element(json_current_judgment,struct_current_judgment,double,var_data);
    s2j_json_set_basic_element(json_current_judgment,struct_current_judgment,int,con_count);
    s2j_json_set_basic_element(json_current_judgment,struct_current_judgment,int,last_abnormal_flag);
    s2j_json_set_basic_element(json_current_judgment,struct_current_judgment,double,max_current);


    ///第一级 jni_current_correction_context_t
    s2j_json_set_struct_element(json_correction,json_algorithm,struct_correction,struct_algorithm,jni_current_correction_context_t,mCurrentCorrectionContext);
    ///第二级 jni_current_correction_context_t下的子属性
    s2j_json_set_basic_element(json_correction,struct_correction,double,mS);
    s2j_json_set_basic_element(json_correction,struct_correction,double,mLastS);
    s2j_json_set_basic_element(json_correction,struct_correction,int,mSFlag);
    s2j_json_set_basic_element(json_correction,struct_correction,double,mD0);
    s2j_json_set_basic_element(json_correction,struct_correction,double,mSs0);
    s2j_json_set_array_element(json_correction,struct_correction,double,mTimeWindows,TIME_WINDOWS_NUM);
    s2j_json_set_array_element(json_correction,struct_correction,double,mTimeWindows1,TIME_WINDOWS_NUM);


    ///第一级 jni_kalman_context_t
    s2j_json_set_struct_element(json_mKalman,json_algorithm,struct_mKalman,struct_algorithm,jni_kalman_context_t,mKalmanContext);
    ///第二级 jni_kalman_context_t下的子属性
    s2j_json_set_basic_element(json_mKalman,struct_mKalman,double,mStateKalman);
    s2j_json_set_basic_element(json_mKalman,struct_mKalman,double,mStatePre);
    s2j_json_set_basic_element(json_mKalman,struct_mKalman,double,mPminus);
    s2j_json_set_basic_element(json_mKalman,struct_mKalman,double,mK);
    s2j_json_set_basic_element(json_mKalman,struct_mKalman,double,mR);
    s2j_json_set_basic_element(json_mKalman,struct_mKalman,double,mQ);
    s2j_json_set_basic_element(json_mKalman,struct_mKalman,double,mP);


    ///第一级 jni_filter1_context_t
    s2j_json_set_struct_element(json_filter1,json_algorithm,struct_filter1,struct_algorithm,jni_filter_context_t,mFilter1Context);
    ///第二级 jni_filter1_context_t下的子属性
    s2j_json_set_array_element(json_filter1,struct_filter1,double,m_filter_data,3);
    s2j_json_set_array_element(json_filter1,struct_filter1,double,m_temp_data,2);
    s2j_json_set_array_element(json_filter1,struct_filter1,double,m_a_data,3);
    s2j_json_set_array_element(json_filter1,struct_filter1,double,m_b_data,3);


    ///第一级 jni_filter1_context_t
    s2j_json_set_struct_element(json_filter2,json_algorithm,struct_filter2,struct_algorithm,jni_filter_context_t,mFilter2Context);
    ///第二级 jni_filter1_context_t下的子属性
    s2j_json_set_array_element(json_filter2,struct_filter2,double,m_filter_data,3);
    s2j_json_set_array_element(json_filter2,struct_filter2,double,m_temp_data,2);
    s2j_json_set_array_element(json_filter2,struct_filter2,double,m_a_data,3);
    s2j_json_set_array_element(json_filter2,struct_filter2,double,m_b_data,3);


    ///第一级 jni_cal_baseline_context_t
    s2j_json_set_struct_element(json_baseline,json_algorithm,struct_baseline,struct_algorithm,jni_cal_baseline_context_t,mCalBaselineContext);
    ///第二级 jni_cal_baseline_context_t下的子属性
    s2j_json_set_basic_element(json_baseline, struct_baseline, int, fasting_continue_count);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, fasting_min_data);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, last_fasting_min_data);
    s2j_json_set_basic_element(json_baseline, struct_baseline, int, temp_fasting_min_index);
    s2j_json_set_basic_element(json_baseline, struct_baseline, int, last_fasting_min_index);
    s2j_json_set_basic_element(json_baseline, struct_baseline, int, fasting_max_index);
    s2j_json_set_basic_element(json_baseline, struct_baseline, int, fasting_min_index);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, fasting_max_data);
    s2j_json_set_basic_element(json_baseline, struct_baseline, int, fasting_continue_count_sum);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, fasting_continue_count_avg);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, fasting_continue_data_sum);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, fasting_continue_data_avg);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, fasting_count);
    s2j_json_set_basic_element(json_baseline, struct_baseline, int, last_trend_data_count);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, temp_mean_baseline);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, baseline_value);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, last_baseline_value);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, last_last_baseline_value);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, last_data);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, last_last_data);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, fasting_min_sum);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, fasting_min_avg);
    s2j_json_set_basic_element(json_baseline, struct_baseline, int, flag_index);
    s2j_json_set_basic_element(json_baseline, struct_baseline, int, fasting_min_data_count);
    s2j_json_set_basic_element(json_baseline, struct_baseline, int, last_fasting_index);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, fasting_min_value);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, fasting_min_data_sum);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, fasting_min_data_avg);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, last_sf_data);
    s2j_json_set_basic_element(json_baseline, struct_baseline, double, max_point_data);


    ///第一级 jni_clipping_filter_context_t
    s2j_json_set_struct_element(json_mClippingFilter,json_algorithm,struct_mClippingFilter,struct_algorithm,jni_clipping_filter_context_t,mClippingFilterContext);
    ///第二级 jni_clipping_filter_context_t下的子属性
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, int, error_flag);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, int, short_ESA_flag);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, int, count);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, last_min_data);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, min_data);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, continue_down_count);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, int, continue_down_flag);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, continue_down_max_data);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, last_continue_down_max_data);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, continue_down_min_data);
    s2j_json_set_array_element(json_mClippingFilter, struct_mClippingFilter, double, CGM_var_windows,15);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, CGM_var_data);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, int, var_data_count);
    s2j_json_set_array_element(json_mClippingFilter, struct_mClippingFilter, double, min_data_buf,20);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, int, data_count);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, int, seven_point_index);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, data_count0_max);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, data_count0);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, slope);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, int, up_continue_count);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, int, min_data_count);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, up_min_data);
    s2j_json_set_array_element(json_mClippingFilter, struct_mClippingFilter, double, sf4_buf,10);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, sf4_min_data);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, int, sf4_min_data_index);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, Daily_minimum_value);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, last_Daily_minimum_value);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, int, Daily_minimum_value_count);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, Daily_minimum_value_sum);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, Daily_minimum_value_avg);
    s2j_json_set_basic_element(json_mClippingFilter, struct_mClippingFilter, double, max_data);
    s2j_json_set_array_element(json_mClippingFilter, struct_mClippingFilter, double, ret_tmp_data,3);


    ///第一级 jni_esa_compensate_context_t
    s2j_json_set_struct_element(json_mESACompernsate,json_algorithm,struct_mESACompernsater,struct_algorithm,jni_esa_compensate_context_t,mESACompensateContext);
    ///第二级 jni_esa_compensate_context_t下的子属性
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, k_data);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, ESA_min_data);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, int, ESA_flag);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, ESA_sum);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, ESA_average);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, baseline);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, b1_data);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, data_12);
    s2j_json_set_array_element(json_mESACompernsate, struct_mESACompernsater, double, fit10_x,10);
    s2j_json_set_array_element(json_mESACompernsate, struct_mESACompernsater, double, fit10_y,10);
    s2j_json_set_array_element(json_mESACompernsate, struct_mESACompernsater, double, fit36_x,35);
    s2j_json_set_array_element(json_mESACompernsate, struct_mESACompernsater, double, fit36_y,35);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, last_mean_data);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, continue_mean_count);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, bl_last_data);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, bl_last_last_data);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, bl_min_flag);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, last_baseline_cgm);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, slowly_chang_value);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, int, deferred_compensation_flag);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, int, deferred_compensation_count);
    s2j_json_set_basic_element(json_mESACompernsate, struct_mESACompernsater, double, baseline_chang_value);


    ///第一级  jni_cgm_calibration_context_t
    s2j_json_set_struct_element(json_mCalibration, json_algorithm, struct_mCalibration, struct_algorithm, jni_cgm_calibration_context_t, mCGMCalibrationContext);
    ///第二级 jni_cgm_calibration_context_t下的子属性
    s2j_json_set_basic_element(json_mCalibration, struct_mCalibration, int, calibration_flag);
    s2j_json_set_basic_element(json_mCalibration, struct_mCalibration, int, bg_index);
    s2j_json_set_basic_element(json_mCalibration, struct_mCalibration, double , last_bg);
    s2j_json_set_basic_element(json_mCalibration, struct_mCalibration, double , last_sf4_data);
    s2j_json_set_basic_element(json_mCalibration, struct_mCalibration, double, last_last_sf4_data);


    ///第一级 jni_regular_deconvolution_context_t
    s2j_json_set_struct_element(json_mRegularDeconvolution,json_algorithm,struct_mRegularDeconvolution,struct_algorithm,jni_regular_deconvolution_context_t,mRegularDeconvolutionContext);
    ///第二级 jni_regular_deconvolution_context_t下的子属性
    s2j_json_set_array_element(json_mRegularDeconvolution, struct_mRegularDeconvolution, double, ig_value_buf,30);


    ///第一级 jni_arrow_direction_context_t
    s2j_json_set_struct_element(json_ArrowDirection,json_algorithm,struct_ArrowDirection,struct_algorithm,jni_arrow_direction_context_t,mArrowDirectionContext);
    ///第二级 jni_arrow_direction_context_t下的子属性
    s2j_json_set_basic_element(json_ArrowDirection, struct_ArrowDirection, int, blood_glucose_trend);
    s2j_json_set_basic_element(json_ArrowDirection, struct_ArrowDirection, int, last_blood_glucose_trend);
    s2j_json_set_basic_element(json_ArrowDirection, struct_ArrowDirection, double, arrow_direction_data);
    s2j_json_set_basic_element(json_ArrowDirection, struct_ArrowDirection, double, last_arrow_direction_data);
    s2j_json_set_basic_element(json_ArrowDirection, struct_ArrowDirection, double, last_last_arrow_direction_data);
    s2j_json_set_basic_element(json_ArrowDirection, struct_ArrowDirection, int, rise_trend_count);
    s2j_json_set_basic_element(json_ArrowDirection, struct_ArrowDirection, int, decline_trend_count);
    s2j_json_set_basic_element(json_ArrowDirection, struct_ArrowDirection, int, horizontal_direction_count);
    s2j_json_set_basic_element(json_ArrowDirection, struct_ArrowDirection, int, arrow_direction_count);

    /* return Student JSON object pointer */
    return json_algorithm;
}

/**
 * jni_algorithm_context_t JSON object to structure object
 *
 * @param json_obj JSON object
 *
 * @return jni_algorithm_context_t object
 */
jni_algorithm_context_t *json_to_struct(cJSON* json_obj) {
    /* create algorithmicContext structure object */
    s2j_create_struct_obj(struct_algorithm, jni_algorithm_context_t);

    /* deserialize data to algorithmicContext structure object. */
    s2j_struct_get_basic_element(struct_algorithm, json_obj, int, esa_calibration_enable);
    s2j_struct_get_basic_element(struct_algorithm, json_obj, int, finger_blood_calibration_enable);
    s2j_struct_get_basic_element(struct_algorithm, json_obj, string, version_name);
    s2j_struct_get_basic_element(struct_algorithm, json_obj, double, IG_data);
    s2j_struct_get_basic_element(struct_algorithm, json_obj, double, last_IG_data);
    s2j_struct_get_basic_element(struct_algorithm, json_obj, int, cgm_warning);
    s2j_struct_get_basic_element(struct_algorithm, json_obj, int, cgm_current_abnormal);
    s2j_struct_get_basic_element(struct_algorithm, json_obj, int, cgm_temp_abnormal);
    s2j_struct_get_basic_element(struct_algorithm, json_obj, int, cgm_blood_glucose_trend);


    ///第一级 mJudgmentContext
    s2j_struct_get_struct_element(struct_judgment,struct_algorithm,json_judgment,json_obj,jni_judgment_context_t,mJudgmentContext);
    ///第二级 mJudgmentContext下的子属性
    s2j_struct_get_basic_element(struct_judgment,json_judgment,double,current_abnormal_flag_count);
    s2j_struct_get_array_element(struct_judgment,json_judgment,double,abnormal_flag_buf);
    s2j_struct_get_basic_element(struct_judgment,json_judgment,int,abnormal_count);
    s2j_struct_get_struct_element(struct_current_judgment,struct_judgment,json_current_judgment,json_judgment,jni_current_judgment_context_t,m_current_jud_context);
    ///第三级 jni_current_judgment_context_t 下的子属性
    s2j_struct_get_basic_element(struct_current_judgment,json_current_judgment,double,last_current);
    s2j_struct_get_basic_element(struct_current_judgment,json_current_judgment,int,abnormal_flag);
    s2j_struct_get_array_element(struct_current_judgment,json_current_judgment,double,temp_data_buf);
    s2j_struct_get_basic_element(struct_current_judgment,json_current_judgment,double,var_data);
    s2j_struct_get_basic_element(struct_current_judgment,json_current_judgment,int,con_count);
    s2j_struct_get_basic_element(struct_current_judgment,json_current_judgment,int,last_abnormal_flag);
    s2j_struct_get_basic_element(struct_current_judgment,json_current_judgment,double,max_current);


    ///第一级 mJudgmentContext
    s2j_struct_get_struct_element(struct_correction,struct_algorithm,json_correction,json_obj,jni_current_correction_context_t,mCurrentCorrectionContext);
    ///第二级 jni_current_correction_context_t下的子属性
    s2j_struct_get_basic_element(struct_correction,json_correction,double,mS);
    s2j_struct_get_basic_element(struct_correction,json_correction,double,mLastS);
    s2j_struct_get_basic_element(struct_correction,json_correction,int,mSFlag);
    s2j_struct_get_basic_element(struct_correction,json_correction,double,mD0);
    s2j_struct_get_basic_element(struct_correction,json_correction,double,mSs0);
    s2j_struct_get_array_element(struct_correction,json_correction,double,mTimeWindows);
    s2j_struct_get_array_element(struct_correction,json_correction,double,mTimeWindows1);


    ///第一级 jni_kalman_context_t
    s2j_struct_get_struct_element(struct_mKalman,struct_algorithm,json_mKalman,json_obj,jni_kalman_context_t,mKalmanContext);
    ///第二级 jni_kalman_context_t下的子属性
    s2j_struct_get_basic_element(struct_mKalman,json_mKalman,double,mStateKalman);
    s2j_struct_get_basic_element(struct_mKalman,json_mKalman,double,mStatePre);
    s2j_struct_get_basic_element(struct_mKalman,json_mKalman,double,mPminus);
    s2j_struct_get_basic_element(struct_mKalman,json_mKalman,double,mK);
    s2j_struct_get_basic_element(struct_mKalman,json_mKalman,double,mR);
    s2j_struct_get_basic_element(struct_mKalman,json_mKalman,double,mQ);
    s2j_struct_get_basic_element(struct_mKalman,json_mKalman,double,mP);


    ///第一级 jni_filter_context_t
    s2j_struct_get_struct_element(struct_filter1,struct_algorithm,json_filter1,json_obj,jni_filter_context_t,mFilter1Context);
    ///第二级 jni_filter1_context_t下的子属性
    s2j_struct_get_array_element(struct_filter1,json_filter1,double,m_filter_data);
    s2j_struct_get_array_element(struct_filter1,json_filter1,double,m_temp_data);
    s2j_struct_get_array_element(struct_filter1,json_filter1,double,m_a_data);
    s2j_struct_get_array_element(struct_filter1,json_filter1,double,m_b_data);


    ///第一级 jni_filter1_context_t
    s2j_struct_get_struct_element(struct_filter2,struct_algorithm,json_filter2,json_obj,jni_filter_context_t,mFilter2Context);
    ///第二级 jni_filter1_context_t下的子属性
    s2j_struct_get_array_element(struct_filter2,json_filter2,double,m_filter_data);
    s2j_struct_get_array_element(struct_filter2,json_filter2,double,m_temp_data);
    s2j_struct_get_array_element(struct_filter2,json_filter2,double,m_a_data);
    s2j_struct_get_array_element(struct_filter2,json_filter2,double,m_b_data);


    ///第一级 jni_cal_baseline_context_t
    s2j_struct_get_struct_element(struct_baseline,struct_algorithm,json_baseline,json_obj,jni_cal_baseline_context_t,mCalBaselineContext);
    ///第二级 jni_cal_baseline_context_t下的子属性
    s2j_struct_get_basic_element(struct_baseline, json_baseline, int, fasting_continue_count);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, fasting_min_data);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, last_fasting_min_data);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, int, temp_fasting_min_index);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, int, last_fasting_min_index);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, int, fasting_max_index);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, int, fasting_min_index);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, fasting_max_data);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, int, fasting_continue_count_sum);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, fasting_continue_count_avg);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, fasting_continue_data_sum);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, fasting_continue_data_avg);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, fasting_count);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, int, last_trend_data_count);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, temp_mean_baseline);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, baseline_value);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, last_baseline_value);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, last_last_baseline_value);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, last_data);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, last_last_data);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, fasting_min_sum);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, fasting_min_avg);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, int, flag_index);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, int, fasting_min_data_count);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, int, last_fasting_index);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, fasting_min_value);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, fasting_min_data_sum);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, fasting_min_data_avg);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, last_sf_data);
    s2j_struct_get_basic_element(struct_baseline, json_baseline, double, max_point_data);


    ///第一级 jni_clipping_filter_context_t
    s2j_struct_get_struct_element(struct_mClippingFilter,struct_algorithm,json_mClippingFilter,json_obj,jni_clipping_filter_context_t,mClippingFilterContext);
    ///第二级 jni_clipping_filter_context_t下的子属性
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter,int, error_flag);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, int, short_ESA_flag);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, int, count);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, last_min_data);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, min_data);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, continue_down_count);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, int, continue_down_flag);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, continue_down_max_data);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, last_continue_down_max_data);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, continue_down_min_data);
    s2j_struct_get_array_element(struct_mClippingFilter, json_mClippingFilter, double, CGM_var_windows);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, CGM_var_data);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, int, var_data_count);
    s2j_struct_get_array_element(struct_mClippingFilter, json_mClippingFilter, double, min_data_buf);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, int, data_count);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, int, seven_point_index);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, data_count0_max);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, data_count0);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, slope);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, int, up_continue_count);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, int, min_data_count);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, up_min_data);
    s2j_struct_get_array_element(struct_mClippingFilter, json_mClippingFilter, double, sf4_buf);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, sf4_min_data);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, int, sf4_min_data_index);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, Daily_minimum_value);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, last_Daily_minimum_value);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, int, Daily_minimum_value_count);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, Daily_minimum_value_sum);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, Daily_minimum_value_avg);
    s2j_struct_get_basic_element(struct_mClippingFilter, json_mClippingFilter, double, max_data);
    s2j_struct_get_array_element(struct_mClippingFilter, json_mClippingFilter, double, ret_tmp_data);


    ///第一级 jni_esa_compensate_context_t
    s2j_struct_get_struct_element(struct_mESACompensater,struct_algorithm,json_mESACompensate,json_obj,jni_esa_compensate_context_t,mESACompensateContext);
    ///第二级 jni_esa_compensate_context_t下的子属性
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, k_data);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, ESA_min_data);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, int, ESA_flag);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, ESA_sum);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, ESA_average);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, baseline);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, b1_data);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, data_12);
    s2j_struct_get_array_element(struct_mESACompensater,json_mESACompensate, double, fit10_x);
    s2j_struct_get_array_element(struct_mESACompensater,json_mESACompensate, double, fit10_y);
    s2j_struct_get_array_element(struct_mESACompensater,json_mESACompensate, double, fit36_x);
    s2j_struct_get_array_element(struct_mESACompensater,json_mESACompensate, double, fit36_y);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, last_mean_data);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, continue_mean_count);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, bl_last_data);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, bl_last_last_data);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, bl_min_flag);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, last_baseline_cgm);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, slowly_chang_value);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, int, deferred_compensation_flag);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, int, deferred_compensation_count);
    s2j_struct_get_basic_element(struct_mESACompensater,json_mESACompensate, double, baseline_chang_value);


    ///第一级  jni_cgm_calibration_context_t
    s2j_struct_get_struct_element(struct_mCalibration,struct_algorithm,json_mCalibration,json_obj,jni_cgm_calibration_context_t,mCGMCalibrationContext);
    s2j_struct_get_basic_element(struct_mCalibration,json_mCalibration, int, calibration_flag);
    s2j_struct_get_basic_element(struct_mCalibration,json_mCalibration, int, bg_index);
    s2j_struct_get_basic_element(struct_mCalibration,json_mCalibration, double, last_bg);
    s2j_struct_get_basic_element(struct_mCalibration,json_mCalibration, double, last_sf4_data);
    s2j_struct_get_basic_element(struct_mCalibration,json_mCalibration, double, last_last_sf4_data);


    ///第一级 jni_regular_deconvolution_context_t
    s2j_struct_get_struct_element(struct_mRegularDeconvolution,struct_algorithm,json_mRegularDeconvolution,json_obj,jni_regular_deconvolution_context_t,mRegularDeconvolutionContext);
    ///第二级 jni_regular_deconvolution_context_t下的子属性
    s2j_struct_get_array_element(struct_mRegularDeconvolution,json_mRegularDeconvolution, double, ig_value_buf);

    ///第一级 jni_arrow_direction_context_t
    s2j_struct_get_struct_element(struct_ArrowDirection,struct_algorithm,json_ArrowDirection,json_obj,jni_arrow_direction_context_t,mArrowDirectionContext);
    s2j_struct_get_basic_element(struct_ArrowDirection,json_ArrowDirection,int, blood_glucose_trend);
    s2j_struct_get_basic_element(struct_ArrowDirection,json_ArrowDirection, int, last_blood_glucose_trend);
    s2j_struct_get_basic_element(struct_ArrowDirection,json_ArrowDirection, double,arrow_direction_data);
    s2j_struct_get_basic_element(struct_ArrowDirection,json_ArrowDirection,double,last_arrow_direction_data);
    s2j_struct_get_basic_element(struct_ArrowDirection,json_ArrowDirection,double,last_last_arrow_direction_data);
    s2j_struct_get_basic_element(struct_ArrowDirection,json_ArrowDirection,int,rise_trend_count);
    s2j_struct_get_basic_element(struct_ArrowDirection,json_ArrowDirection,int,decline_trend_count);
    s2j_struct_get_basic_element(struct_ArrowDirection,json_ArrowDirection,int,horizontal_direction_count);
    s2j_struct_get_basic_element(struct_ArrowDirection,json_ArrowDirection,int,arrow_direction_count);

    /* return Student structure object pointer */
    return struct_algorithm;
}
