//
// Created by LENOVO on 2021/5/4.
//

#ifndef MY_APPLICATION_NATIVE_FILTER1_CONTEXT_H
#define MY_APPLICATION_NATIVE_FILTER1_CONTEXT_H

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct{
 double m_filter_data[3];
 double m_temp_data[2];
 double m_a_data[3];
 double m_b_data[3];
}jni_filter_context_t;

double functionFilter(double data, double *filter_data, double *temp_data, double *a, double *b, int index);

#ifdef  __cplusplus
}
#endif

#endif //MY_APPLICATION_NATIVE_FILTER1_CONTEXT_H
