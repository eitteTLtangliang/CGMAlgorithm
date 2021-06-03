//
// Created by LENOVO on 2021/5/7.
//
#ifdef _WINDOWS
#include <math.h>
#include "../header/native_regular_deconvolution_context.h"
#endif
#ifdef __ANDROID__
#include <jni.h>
#include <android/log.h>
#include <math.h>
#include "../header/native_regular_deconvolution_context.h"
#endif

double Regular_deconvolution(jni_regular_deconvolution_context_t *p_regular_deconvolution_context, double IG_value, int index){

    double result = 0.0;

    if(p_regular_deconvolution_context != NULL){

        int i = 0;

        double g[30] = { 2.12986954e-01,-1.56069197e-02, -1.16342456e-02, -8.67279838e-03,-6.46517451e-03,-4.81949149e-03,-3.59270964e-03,-2.67819938e-03,-1.99647318e-03,
                         -1.48827670e-03,-1.10943843e-03,-8.27030480e-04,-6.16506464e-04, -4.59568035e-04,-3.42574398e-04,-2.55356686e-04,-1.90334098e-04,-1.41854993e-04,
                         -1.05705658e-04,-7.87440606e-05,-5.86267495e-05,-4.36051657e-05,-3.23736611e-05,-2.39560144e-05,-1.76205797e-05,-1.28166926e-05,-9.12680852e-06,
                         -6.23020949e-06,-3.87512860e-06,-1.85686662e-06 };

        for(i = 0; i < 29; i++){
            p_regular_deconvolution_context->ig_value_buf[i] = p_regular_deconvolution_context->ig_value_buf[i + 1];
        }

        p_regular_deconvolution_context->ig_value_buf[29] = IG_value;

        for (i = 0; i < 30; i++){
            result = result + (p_regular_deconvolution_context->ig_value_buf)[29-i]*g[i];
        }

        result = result * 6.8;

        if (IG_value < 3 ){
            result = IG_value;
        }else{
            if (index<576 && IG_value < 5.5){
                result = IG_value;
            }
        }
    }

    return result;
}



