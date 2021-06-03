//
// Created by l.tan on 2021/5/25.
//

#ifdef _WINDOWS
#include <math.h>
#include "../header/native_cgm_calibration_context.h"
#endif

#ifdef __ANDROID__
#include <jni.h>
#include <android/log.h>
#include <math.h>
#include "../header/native_cgm_calibration_context.h"
#endif

void CGM_Calibration(jni_cgm_calibration_context_t *p_cgm_calibration_context, jni_clipping_filter_context_t *p_clipping_filter_context, double bg, double sf4_data){

    if (p_cgm_calibration_context != NULL && p_clipping_filter_context != NULL){

        if (bg > 0){
            if (p_clipping_filter_context->CGM_var_data < 0.5){
                p_cgm_calibration_context->calibration_flag = 1;
            }else if ((sf4_data - p_cgm_calibration_context->last_sf4_data > 0 && p_cgm_calibration_context->last_sf4_data - p_cgm_calibration_context->last_last_sf4_data > 0 && p_clipping_filter_context->CGM_var_data > 0.5) || (p_clipping_filter_context->up_continue_count > 3 && sf4_data - p_clipping_filter_context->up_min_data > 1)){
                p_cgm_calibration_context->calibration_flag = 2;
            }else if ((sf4_data - p_cgm_calibration_context->last_sf4_data < 0 && p_cgm_calibration_context->last_sf4_data - p_cgm_calibration_context->last_last_sf4_data < 0 && p_clipping_filter_context->CGM_var_data > 0.5) || (p_clipping_filter_context->continue_down_count > 3)){
                p_cgm_calibration_context->calibration_flag = 3;
            }else{
                p_cgm_calibration_context->calibration_flag = 1;
            }
        }
    }

}
