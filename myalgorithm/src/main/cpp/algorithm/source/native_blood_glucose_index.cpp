//
// Created by l.tan on 2021/5/24.
//
#ifdef _WINDOWS
#include <math.h>
#include "../header/native_blood_glucose_index.h"
#endif

#ifdef __ANDROID__
#include <jni.h>
#include <android/log.h>
#include <math.h>
#include "../header/native_blood_glucose_index.h"
#endif

double sum_idr = 0;

void AGP_Kalman_Filter(float *p_data){
    double agp_state_kalman = 0.0;
    double agp_state_pre = 0.0;
    double agp_Pminus = 0.0;
    double agp_K = 0.0;
    double agp_R = 1.2;
    double agp_Q = 0.5;
    double agp_P = 0.01;
    for (int i = 1; i < 288; i++){
        if (i > 1){
            agp_state_pre = agp_state_kalman;
            agp_Pminus = agp_P + agp_Q;
            agp_K = agp_Pminus / (agp_Pminus + agp_R);
            agp_state_kalman = agp_state_pre + agp_K * (p_data[i] - agp_state_pre);
            agp_P = (1 - agp_K)*agp_Pminus;
        }else{
            agp_state_kalman = p_data[i];
        }
        p_data[i] = (float)agp_state_kalman;
    }
}

void Reversal_function(float *p){

    float temp_data = 0;
    int i = 0;

    for (i = 0; i < 144; i++){
        temp_data = p[i];
        p[i] = p[287 - i];
        p[287 - i] = temp_data;
    }
}

float *Agp_value(float *p_data){
    Reversal_function(p_data);
    AGP_Kalman_Filter(p_data);
    Reversal_function(p_data);
    AGP_Kalman_Filter(p_data);
    Reversal_function(p_data);
    AGP_Kalman_Filter(p_data);
    Reversal_function(p_data);
    AGP_Kalman_Filter(p_data);
    Reversal_function(p_data);
    AGP_Kalman_Filter(p_data);
    Reversal_function(p_data);
    AGP_Kalman_Filter(p_data);
    Reversal_function(p_data);
    AGP_Kalman_Filter(p_data);
    Reversal_function(p_data);
    AGP_Kalman_Filter(p_data);
    Reversal_function(p_data);
    AGP_Kalman_Filter(p_data);
    Reversal_function(p_data);
    AGP_Kalman_Filter(p_data);
    Reversal_function(p_data);
    AGP_Kalman_Filter(p_data);
    Reversal_function(p_data);
    AGP_Kalman_Filter(p_data);
    Reversal_function(p_data);
    AGP_Kalman_Filter(p_data);
    Reversal_function(p_data);
    AGP_Kalman_Filter(p_data);

    return p_data;
}

float function_GE(float *agp_data){
    double sum_ge = 0;
    double v_ge = 0;
    for (int i=0; i< 288;i++){
        sum_ge = sum_ge + agp_data[i] * 5;
    }
    v_ge = sum_ge/60/24;
    return (float)v_ge;
}

float function_IDR(float *agp_data10, float *agp_data90){
    sum_idr = 0;
    int i = 0;
    double avg_idr;
    for (i = 0; i < 288; i++){
        sum_idr = sum_idr + agp_data90[i] - agp_data10[i];
    }
    avg_idr = sum_idr / 288;
    return (float)avg_idr;
}

float function_IQR(float *agp_data25, float *agp_data75){
    double sum_iqr = 0;
    int i = 0;
    double avg_iqr;
    for (i = 0; i < 288; i++){
        sum_iqr = sum_iqr + agp_data75[i] - agp_data25[i];
    }
    avg_iqr = sum_iqr / 288;
    return (float)avg_iqr;
}

float function_CM(float *agp_data){
    double sum_cm = 0;
    int i = 0;
    double avg_cm;
    for (i = 0; i < 287; i++){
        sum_cm = sum_cm + fabs(agp_data[i + 1] - agp_data[i]);
    }
    avg_cm = sum_cm / 287 * 12;
    return avg_cm;
}

float function_LBGR(float *agp_data, float defaultLow){
    double sum_lbgr = 0;
    int i = 0;
    double v_lbgr;
    for (i = 0; i < 288; i++){
        if (agp_data[i] - defaultLow < 0)
            sum_lbgr = sum_lbgr + defaultLow - agp_data[i];
    }
    v_lbgr = sum_lbgr / sum_idr;
    return (float)v_lbgr;
}

float function_HBGR(float *agp_data, float defaultHigh){
    double sum_hbgr = 0;
    int i = 0;
    double v_hbgr;
    for (i = 0; i < 288; i++){
        if (agp_data[i] > defaultHigh)
            sum_hbgr = sum_hbgr + agp_data[i] - defaultHigh;
    }
    v_hbgr = sum_hbgr / sum_idr;
    return (float)v_hbgr;
}