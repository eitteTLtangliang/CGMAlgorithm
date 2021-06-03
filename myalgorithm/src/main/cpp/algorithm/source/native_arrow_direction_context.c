//
// Created by LENOVO on 2021/5/7.
//
#ifdef _WINDOWS
#include <math.h>
#include "../header/native_arrow_direction_context.h"
#endif
#ifdef __ANDROID__
#include <jni.h>
#include <android/log.h>
#include <math.h>
#include "../header/native_arrow_direction_context.h"
#endif


int Arrow_direction(jni_arrow_direction_context_t *p_arrow_direction_context,double cgm_data,int index) {

    int n = 1;

    if(p_arrow_direction_context != NULL){
        p_arrow_direction_context->arrow_direction_data = (double)((int)(cgm_data * pow(10, n) + 0.5)) / pow(10, n);
        if (fabs(p_arrow_direction_context->arrow_direction_data - p_arrow_direction_context->last_arrow_direction_data) < 0.3){
            if (p_arrow_direction_context->arrow_direction_data < 4.5){
                if (fabs(p_arrow_direction_context->arrow_direction_data - p_arrow_direction_context->last_arrow_direction_data) < 0.1){
                    p_arrow_direction_context->blood_glucose_trend = 0;
                }else{
                    if (p_arrow_direction_context->arrow_direction_data - p_arrow_direction_context->last_arrow_direction_data < 0){
                        p_arrow_direction_context->blood_glucose_trend = -1;
                    }else{
                        p_arrow_direction_context->blood_glucose_trend = 1;
                    }
                }
            }else{
                p_arrow_direction_context->blood_glucose_trend = 0;
            }
        }else if (fabs(p_arrow_direction_context->arrow_direction_data - p_arrow_direction_context->last_arrow_direction_data) < 0.55){
            if ((p_arrow_direction_context->arrow_direction_data - p_arrow_direction_context->last_arrow_direction_data) < 0){
                p_arrow_direction_context->blood_glucose_trend = -1;
            }else{
                p_arrow_direction_context->blood_glucose_trend = 1;
            }
        }else{
            if ((p_arrow_direction_context->arrow_direction_data - p_arrow_direction_context->last_arrow_direction_data) < 0){
                if ((p_arrow_direction_context->last_blood_glucose_trend != -1) && (p_arrow_direction_context->last_blood_glucose_trend != -2)){
                    p_arrow_direction_context->blood_glucose_trend = -1;
                }else{
                    p_arrow_direction_context->blood_glucose_trend = -2;
                }
            }else{
                if ((p_arrow_direction_context->last_blood_glucose_trend != 1) && (p_arrow_direction_context->last_blood_glucose_trend != 2)){
                    p_arrow_direction_context->blood_glucose_trend = 1;
                }else{
                    p_arrow_direction_context->blood_glucose_trend = 2;
                }
            }
        }

        //向下降
        if((p_arrow_direction_context->arrow_direction_data - p_arrow_direction_context->last_arrow_direction_data) < -0.1){
            p_arrow_direction_context->decline_trend_count = p_arrow_direction_context->decline_trend_count + 1;
        }else{
            p_arrow_direction_context->decline_trend_count = 0;
        }

        //向上增
        if((p_arrow_direction_context->arrow_direction_data - p_arrow_direction_context->last_arrow_direction_data) > 0.1){
            p_arrow_direction_context->rise_trend_count = p_arrow_direction_context->rise_trend_count + 1;
        }else{
            p_arrow_direction_context->rise_trend_count = 0;
        }

        //平稳
        if (p_arrow_direction_context->blood_glucose_trend == 0){
            p_arrow_direction_context->horizontal_direction_count = p_arrow_direction_context->horizontal_direction_count + 1;
        }else{
            p_arrow_direction_context->horizontal_direction_count = 0;
        }

        if ((p_arrow_direction_context->rise_trend_count >= 2) && (p_arrow_direction_context->blood_glucose_trend == 0)){
            p_arrow_direction_context->blood_glucose_trend = 1;
        }

        if ((p_arrow_direction_context->decline_trend_count >= 2) && (p_arrow_direction_context->blood_glucose_trend == 0)){
            p_arrow_direction_context->blood_glucose_trend = -1;
        }

        if (p_arrow_direction_context->horizontal_direction_count >= 2){
            if (p_arrow_direction_context->last_blood_glucose_trend > 1){
                p_arrow_direction_context->blood_glucose_trend = 1;
            }

            if (p_arrow_direction_context->last_blood_glucose_trend < -1){
                p_arrow_direction_context->blood_glucose_trend = -1;
            }
        }

        if (p_arrow_direction_context->last_blood_glucose_trend == p_arrow_direction_context->blood_glucose_trend){
            p_arrow_direction_context->arrow_direction_count = p_arrow_direction_context->arrow_direction_count + 1;
        }else{
            if (p_arrow_direction_context->arrow_direction_count > 2){
                p_arrow_direction_context->blood_glucose_trend = p_arrow_direction_context->last_blood_glucose_trend;
            }
            p_arrow_direction_context->arrow_direction_count = 0;
        }

        if (index == 0){
            p_arrow_direction_context->blood_glucose_trend = 5;
        }

        p_arrow_direction_context->last_blood_glucose_trend = p_arrow_direction_context->blood_glucose_trend;
        p_arrow_direction_context->last_last_arrow_direction_data = p_arrow_direction_context->last_arrow_direction_data;
        p_arrow_direction_context->last_arrow_direction_data = p_arrow_direction_context->arrow_direction_data;
        return p_arrow_direction_context->blood_glucose_trend;
    }

    return 0;
}












