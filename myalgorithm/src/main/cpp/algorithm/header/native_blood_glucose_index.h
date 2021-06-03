//
// Created by l.tan on 2021/5/24.
//
#include <math.h>

#ifndef MYMODULESAPP_BLOODGLUCOSE_H
#define MYMODULESAPP_BLOODGLUCOSE_H

#endif //MYMODULESAPP_BLOODGLUCOSE_H

//agp index
extern double sum_idr;

void AGP_Kalman_Filter(float *p_data);
void Reversal_function(float *p);
float *Agp_value(float *p);
float function_GE(float *agp_data);
float function_IDR(float *agp_data10, float *agp_data90);
float function_IQR(float *agp_data25, float *agp_data75);
float function_CM(float *agp_data);
float function_LBGR(float *agp_data, float defaultLow);
float function_HBGR(float *agp_data, float defaultHigh);