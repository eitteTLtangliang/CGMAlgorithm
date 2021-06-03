//
// Created by LENOVO on 2021/5/7.
//

#ifndef MY_APPLICATION_NATIVE_ARROW_DIRECTION_CONTEXT_H
#define MY_APPLICATION_NATIVE_ARROW_DIRECTION_CONTEXT_H

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct{
    int blood_glucose_trend;
    int last_blood_glucose_trend;
    double arrow_direction_data;
    double last_arrow_direction_data;
    double last_last_arrow_direction_data;
    int rise_trend_count;
    int decline_trend_count;
    int horizontal_direction_count;
    int arrow_direction_count;
}jni_arrow_direction_context_t;

int Arrow_direction(jni_arrow_direction_context_t *p_arrow_direction_context,double cgm_data,int index);

#ifdef  __cplusplus
}
#endif

#endif //MY_APPLICATION_NATIVE_ARROW_DIRECTION_CONTEXT_H



