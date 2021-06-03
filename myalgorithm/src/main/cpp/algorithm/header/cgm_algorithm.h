#ifndef __ALGORITHM_H
#define __ALGORITHM_H

#ifdef _WINDOWS
#include <windows.h>
#include "native-judgment-context.h"
#include "native-current-correction-context.h"
#include "native-kalman-context.h"
#include "native-filter1-context.h"
#include "native-cal-baseline-context.h"
#include "native-esa-compensate-context.h"
#include "native-regular-deconvolution-context.h"
#include "native-arrow-direction-context.h"
#endif

#ifdef __ANDROID__
#include <jni.h>
#include <android/log.h>
#include "native_current_judgment_context.h"
#include "native_abnormal_value_correction_context.h"
#include "native_kalman_context.h"
#include "native_filter_context.h"
#include "native_cal_baseline_context.h"
#include "native_esa_compensate_context.h"
#include "native_regular_deconvolution_context.h"
#include "native_arrow_direction_context.h"
#include "native_abnormal_judgment_context.h"
#include "native_clipping_filter_context.h"
#include "native_cgm_calibration_context.h"

#endif


#ifdef  __cplusplus
extern "C" {
#endif
#define  MAX_VERSION_NAME_LEN      32

#define  DEF_ESA_CALIBRATION_ENABLE  1
#define  DEF_FINGER_BLOOD_CALIBRATION_ENABLE  1


typedef struct {
	int esa_calibration_enable;
	int finger_blood_calibration_enable;
	char version_name[MAX_VERSION_NAME_LEN];
	double IG_data;
	double last_IG_data;

	int cgm_warning;
	int cgm_current_abnormal;
	int cgm_temp_abnormal;
	int cgm_blood_glucose_trend;


	jni_judgment_context_t mJudgmentContext;
	jni_current_correction_context_t mCurrentCorrectionContext;
	jni_kalman_context_t mKalmanContext;
	jni_filter_context_t mFilter1Context;
	jni_filter_context_t mFilter2Context;
	jni_cal_baseline_context_t  mCalBaselineContext;
	jni_clipping_filter_context_t mClippingFilterContext;
	jni_esa_compensate_context_t mESACompensateContext;
	jni_cgm_calibration_context_t mCGMCalibrationContext;
	jni_regular_deconvolution_context_t mRegularDeconvolutionContext;
	jni_arrow_direction_context_t mArrowDirectionContext;

}jni_algorithm_context_t;


char* get_algorithm_version(void);

int init_algorithm_context(jni_algorithm_context_t* p_algorithm_context);

double algorithm_convert_process(jni_algorithm_context_t * p_algorithm_context,double current_data,double temperature,int index,int *error_status, double low_alarm_value, double high_alarm_value);


#ifdef  __cplusplus
}
#endif

#endif
