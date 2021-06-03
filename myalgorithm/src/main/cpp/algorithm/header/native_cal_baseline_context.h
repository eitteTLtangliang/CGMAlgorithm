//
// Created by LENOVO on 2021/5/4.
//

#ifndef MY_APPLICATION_NATIVE_CAL_BASELINE_CONTEXT_H
#define MY_APPLICATION_NATIVE_CAL_BASELINE_CONTEXT_H

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct{
    int fasting_continue_count;
    double fasting_min_data;
    double last_fasting_min_data;
    int temp_fasting_min_index;
    int last_fasting_min_index;
    int fasting_max_index;
    int fasting_min_index;
    double fasting_max_data;
    int fasting_continue_count_sum;
    double fasting_continue_count_avg;
    double fasting_continue_data_sum;
    double fasting_continue_data_avg;
    double fasting_count;

    int last_trend_data_count;
    double temp_mean_baseline;       // 20

    double baseline_value;
    double last_baseline_value;
    double last_last_baseline_value;

    double last_data;
    double last_last_data;
    double fasting_min_sum;
    double fasting_min_avg;

    int flag_index;
    int fasting_min_data_count;
    int last_fasting_index;
    double fasting_min_value;
    double fasting_min_data_sum;
    double fasting_min_data_avg;
    double last_sf_data;

    double max_point_data;
}jni_cal_baseline_context_t;

double Calibration_baseline(jni_cal_baseline_context_t *p_cal_baseline_context, double sf4_data, double sf5_data, int index);

#ifdef  __cplusplus
}
#endif
#endif //MY_APPLICATION_NATIVE_CAL_BASELINE_CONTEXT_H
