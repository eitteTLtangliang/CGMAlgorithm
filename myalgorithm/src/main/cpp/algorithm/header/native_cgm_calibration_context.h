//
// Created by l.tan on 2021/5/25.
//

#ifndef MYMODULESAPP_NATIVE_CGM_CALIBRATION_CONTEXT_H
#define MYMODULESAPP_NATIVE_CGM_CALIBRATION_CONTEXT_H

#include "native_clipping_filter_context.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct {
    int calibration_flag;  //为1 表示是空腹，为2表示上升沿，为3表示下降沿。
    int bg_index;
    double last_bg;
    double last_sf4_data;
    double last_last_sf4_data;
}jni_cgm_calibration_context_t;

void CGM_Calibration(jni_cgm_calibration_context_t *jni_cgm_calibration_context, jni_clipping_filter_context_t *p_clipping_filter_context, double bg,double sf4_data);

#ifdef  __cplusplus
}
#endif
#endif //MYMODULESAPP_NATIVE_CGM_CALIBRATION_CONTEXT_H
