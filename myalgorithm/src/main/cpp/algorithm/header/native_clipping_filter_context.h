//
// Created by l.tan on 2021/5/25.
//

#ifndef MYMODULESAPP_NATIVE_CLIPPING_FILTER_CONTEXT_H
#define MYMODULESAPP_NATIVE_CLIPPING_FILTER_CONTEXT_H

#include "native_cal_baseline_context.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct{
    int error_flag;
    int short_ESA_flag;

    int count;
    double last_min_data;
    double min_data;

    double continue_down_count;
    int continue_down_flag;
    double continue_down_max_data;
    double last_continue_down_max_data;
    double continue_down_min_data;

    double CGM_var_windows[15];
    double CGM_var_data;
    int var_data_count;
    double min_data_buf[20];
    int data_count;
    int seven_point_index;
    double data_count0_max;
    double  data_count0;
    double slope;
    int up_continue_count;
    int min_data_count;
    double up_min_data;

    double sf4_buf[10];
    double sf4_min_data;
    int sf4_min_data_index;

    double Daily_minimum_value;
    double last_Daily_minimum_value;
    int Daily_minimum_value_count;
    double Daily_minimum_value_sum;
    double Daily_minimum_value_avg;
    double max_data;

    double ret_tmp_data[3];

}jni_clipping_filter_context_t;

void Clipping_filter(jni_clipping_filter_context_t *p_clipping_filter_context, jni_cal_baseline_context_t *p_cal_baseline_context, double sf4_data, double sf5_data, double cgm_data, int index);

#ifdef  __cplusplus
}
#endif
#endif //MYMODULESAPP_NATIVE_CLIPPING_FILTER_CONTEXT_H
