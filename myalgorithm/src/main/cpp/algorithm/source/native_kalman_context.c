//
// Created by LENOVO on 2021/4/29.
//
#ifdef _WINDOWS
#include <stdio.h>
#include "../header/native_kalman_context.h"
#endif
#ifdef __ANDROID__
#include <jni.h>
#include <android/log.h>
#include "../header/native_kalman_context.h"
#endif


double Kalman_Filter(jni_kalman_context_t *p_kalman_context,double data, int index){

    double ret_state_kalman = 0.0;

    if(p_kalman_context != NULL){

        if(index > 1){
            p_kalman_context->mStatePre = p_kalman_context->mStateKalman;
            p_kalman_context->mPminus = p_kalman_context->mP + p_kalman_context->mQ;

            p_kalman_context->mK = p_kalman_context->mPminus / (p_kalman_context->mPminus + p_kalman_context->mR);

            p_kalman_context->mStateKalman = p_kalman_context->mStatePre + p_kalman_context->mK * (data - p_kalman_context->mStatePre);

            p_kalman_context->mP = (1 - p_kalman_context->mK)*p_kalman_context->mPminus;
        }else{
            p_kalman_context->mStateKalman = data;
        }

        ret_state_kalman = p_kalman_context->mStateKalman;

    }
    return ret_state_kalman;
}
