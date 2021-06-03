//
// Created by LENOVO on 2021/5/3.
//

#ifndef MY_APPLICATION_NATIVE_CURRENT_CORRECTION_CONTEXT_H
#define MY_APPLICATION_NATIVE_CURRENT_CORRECTION_CONTEXT_H
#ifdef  __cplusplus
extern "C" {
#endif


#define  TIME_WINDOWS_NUM      3

typedef struct{
    double  mS;
    double mLastS;
    int mSFlag;
    double mD0;
    double mSs0;
    double mTimeWindows[TIME_WINDOWS_NUM];
    double mTimeWindows1[TIME_WINDOWS_NUM];
}jni_current_correction_context_t;

double Abnormal_Value_Correction(jni_current_correction_context_t *p_cor_context,double m_s, double data, int index);

#ifdef  __cplusplus
}
#endif

#endif //MY_APPLICATION_NATIVE_CURRENT_CORRECTION_CONTEXT_H
