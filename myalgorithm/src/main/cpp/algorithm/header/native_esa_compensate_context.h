//
// Created by LENOVO on 2021/5/6.
//

#ifndef MY_APPLICATION_NATIVE_ESA_COMPENSATE_CONTEXT_H
#define MY_APPLICATION_NATIVE_ESA_COMPENSATE_CONTEXT_H


#ifdef  __cplusplus
extern "C" {
#endif

typedef struct {
    double k_data;

    double ESA_min_data;
    int ESA_flag;
    double ESA_sum;
    double ESA_average;
    double baseline;

    double b1_data;
    double data_12;

    double fit10_x[10];//存放用于线性回归的数据的下标数组
    double fit10_y[10];//存放用于线性回归的电流值
    double fit36_x[35];//存放用于线性回归的数据的下标数组
    double fit36_y[35];//存放用于线性回归的电流值


    double last_mean_data;
    double continue_mean_count;
    double bl_last_data;
    double bl_last_last_data;
    double bl_min_flag;

    double last_baseline_cgm;
    double slowly_chang_value;
    int deferred_compensation_flag;
    int deferred_compensation_count;
    double baseline_chang_value;

}jni_esa_compensate_context_t;

double ESA_Compensate(jni_esa_compensate_context_t *p_esa_compensate_context,double data , double sf_data, double avg_data, int index);

#ifdef  __cplusplus
}
#endif
#endif //MY_APPLICATION_NATIVE_ESA_COMPENSATE_CONTEXT_H



