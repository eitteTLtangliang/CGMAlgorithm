//
// Created by LENOVO on 2021/5/3.
//


#ifdef _WINDOWS
#include <math.h>
#include "../header/native_abnormal_value_correction_context.h"
#endif

#ifdef __ANDROID__
#include <jni.h>
#include <android/log.h>
#include <math.h>
#include "../header/native_abnormal_value_correction_context.h"
#endif

double Abnormal_Value_Correction(jni_current_correction_context_t *p_cor_context,double m_s, double data, int index){

    int i = 0;
    double current_data = 0.0;

    if(p_cor_context != NULL){

        if (m_s == 0){
            m_s = 1;
        }

        for (i = 0; i < (TIME_WINDOWS_NUM-1); i++){
            p_cor_context->mTimeWindows[i] = p_cor_context->mTimeWindows[i + 1];
        }

        p_cor_context->mTimeWindows[TIME_WINDOWS_NUM-1] = data;

        if (index >= 60){

            if ((fabs(p_cor_context->mTimeWindows[2] - p_cor_context->mTimeWindows[1]) <= 2*m_s) && (fabs(p_cor_context->mTimeWindows[2] - p_cor_context->mTimeWindows[0]) <= 2*m_s)){
                current_data = p_cor_context->mTimeWindows[2];
            }else{

                if ((((p_cor_context->mTimeWindows[2] - p_cor_context->mTimeWindows[1]) > 2*m_s) || (p_cor_context->mTimeWindows[2] - p_cor_context->mTimeWindows[0]) > 2*m_s)){
                    p_cor_context->mTimeWindows[2] = p_cor_context->mTimeWindows[1] + 0.1;
                }else if((((p_cor_context->mTimeWindows[2] - p_cor_context->mTimeWindows[1]) <=-2*m_s) || (p_cor_context->mTimeWindows[2] - p_cor_context->mTimeWindows[0]) <= -2*m_s) ){
                    p_cor_context->mTimeWindows[2] = p_cor_context->mTimeWindows[1] - 0.1;
                }

                current_data = p_cor_context->mTimeWindows[2];
            }
        }else{
            current_data = data;
        }
    }

    return current_data;
}





