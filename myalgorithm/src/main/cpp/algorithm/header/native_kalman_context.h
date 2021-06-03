//
// Created by LENOVO on 2021/4/28.
//

#ifndef MY_APPLICATION_NATIVE_KALMAN_CONTEXT_H
#define MY_APPLICATION_NATIVE_KALMAN_CONTEXT_H

#ifdef  __cplusplus
extern "C" {
#endif


typedef struct{
    double mStateKalman;
    double mStatePre;
    double mPminus;
    double mK;
    double mR;
    double mQ;
    double mP;
}jni_kalman_context_t;


double Kalman_Filter(jni_kalman_context_t *p_kalman_context,double data, int index);

#ifdef  __cplusplus
}
#endif

#endif //MY_APPLICATION_NATIVE_KALMAN_CONTEXT_H
