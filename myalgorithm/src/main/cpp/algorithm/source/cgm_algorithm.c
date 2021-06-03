#ifdef _WINDOWS
#include <math.h>
#include "algorithm/algorithm.h"
#endif

#ifdef __ANDROID__
#include <jni.h>
#include <android/log.h>
#include <math.h>
#include <string.h>
#include "../header/cgm_algorithm.h"
#include "../header/native_temperature_compensation_context.h"

#endif

const char global_algorithm_version[] = "ALGORITHM VER 1.0 (2021_05_19B)";

double On_data_in_five_minute(double data, int i){
	if ((i + 1) % 5 == 0){
		return data;
	}else{
		return -1;
	}
}

char* get_algorithm_version(void){
	return (char *)global_algorithm_version;
}

void init_judgment_context(jni_judgment_context_t *p_judgment_context){
	if (p_judgment_context != NULL){
		int i = 0;
		jni_current_judgment_context_t* p_current_judgment_context = NULL;
		p_current_judgment_context = &p_judgment_context->m_current_jud_context;

		for (i = 0; i < MAX_ABNORMAL_FLAG_SIZE; i++){
			p_judgment_context->abnormal_flag_buf[i] = 0.0;
		}

		p_judgment_context->current_abnormal_flag_count = 0.0;
		p_judgment_context->abnormal_count = 0;

		if (p_current_judgment_context != NULL){
			p_current_judgment_context->abnormal_flag = 0;
			p_current_judgment_context->con_count = 0;
			p_current_judgment_context->last_abnormal_flag = 0;
			p_current_judgment_context->last_current = 0.0;
			p_current_judgment_context->max_current = 0.0;
			p_current_judgment_context->var_data = 0.0;

			for(i=0; i<CURRENT_JUDGMENT_NUM_TEMP_DATA; i++){
				p_current_judgment_context->temp_data_buf[i] = 0.0;
			}
		}
	}
}

void init_current_correction_context(jni_current_correction_context_t * p_cor_context){
	if (p_cor_context != NULL){
		int i = 0;
		p_cor_context->mS = 1.41;
		p_cor_context->mLastS = 0.0;
		p_cor_context->mSFlag = 0;
		p_cor_context->mD0 = 0.5;
		p_cor_context->mSs0 = 0.0;
		for (i = 0; i < TIME_WINDOWS_NUM; i++){
			p_cor_context->mTimeWindows[i] = 0.0;
			p_cor_context->mTimeWindows1[i] = 0.0;
		}
	}
}

void init_kalman_context(jni_kalman_context_t* p_kalman_context){
	if (p_kalman_context != NULL){
		p_kalman_context->mStateKalman = 0.0;
		p_kalman_context->mStatePre = 0.0;
		p_kalman_context->mPminus = 0.0;
		p_kalman_context->mK = 0.0;
		p_kalman_context->mR = 1.2;
		p_kalman_context->mQ = 0.5;
		p_kalman_context->mP = 0.0001;
	}
}

void init_cal_baseline_context(jni_cal_baseline_context_t* p_cal_baseline_context){
	if (p_cal_baseline_context != NULL){
		p_cal_baseline_context->fasting_continue_count = 0;
		p_cal_baseline_context->fasting_min_data = 0.0;
		p_cal_baseline_context->last_fasting_min_data = 0.0;
		p_cal_baseline_context->temp_fasting_min_index = 0;
		p_cal_baseline_context->last_fasting_min_index = 0;
		p_cal_baseline_context->fasting_max_index = 0;
		p_cal_baseline_context->fasting_min_index = 0;
		p_cal_baseline_context->fasting_max_data = 0.0;
		p_cal_baseline_context->fasting_continue_count_sum = 0;
		p_cal_baseline_context->fasting_continue_count_avg = 0.0;
		p_cal_baseline_context->fasting_continue_data_sum = 0.0;
		p_cal_baseline_context->fasting_count = 0.0;
		p_cal_baseline_context->last_trend_data_count = 0;
		p_cal_baseline_context->temp_mean_baseline = 20.0;
		p_cal_baseline_context->baseline_value = 0.0;
		p_cal_baseline_context->last_baseline_value = 0.0;
		p_cal_baseline_context->last_last_baseline_value = 0.0;

		p_cal_baseline_context->last_data = 0.0;
		p_cal_baseline_context->last_last_data = 0.0;
		p_cal_baseline_context->fasting_min_sum = 0.0;
		p_cal_baseline_context->fasting_min_avg = 0.0;
		p_cal_baseline_context->flag_index = 0;
		p_cal_baseline_context->fasting_min_data_count = 0;
		p_cal_baseline_context->last_fasting_index = 0;
		p_cal_baseline_context->fasting_min_value = 0.0;
		p_cal_baseline_context->fasting_min_data_sum = 0.0;
		p_cal_baseline_context->fasting_min_data_avg = 0.0;
		p_cal_baseline_context->last_sf_data = 0.0;
		p_cal_baseline_context->max_point_data = 0.0;
	}
}

void init_clipping_filter_context(jni_clipping_filter_context_t* p_clipping_filter_context){
	if (p_clipping_filter_context != NULL){
		int i = 0;
		p_clipping_filter_context->error_flag = 0;
		p_clipping_filter_context->short_ESA_flag = 0;
		p_clipping_filter_context->count = 0;
		p_clipping_filter_context->last_min_data = 0.0;
		p_clipping_filter_context->min_data = 0.0;
		p_clipping_filter_context->continue_down_count = 0.0;
		p_clipping_filter_context->continue_down_flag = 0;
		p_clipping_filter_context->continue_down_max_data = 0.0;
		p_clipping_filter_context->last_continue_down_max_data = 0.0;
		p_clipping_filter_context->continue_down_min_data = 0.0;

		for (i = 0; i < 15; i++){
			p_clipping_filter_context->CGM_var_windows[i] = 0.0;
		}

		p_clipping_filter_context->CGM_var_data = 0.0;
		p_clipping_filter_context->var_data_count = 0;

		for (i = 0; i < 15; i++){
			p_clipping_filter_context->min_data_buf[i] = 100.0;
		}

		p_clipping_filter_context->data_count = 0;
		p_clipping_filter_context->seven_point_index = 0;
		p_clipping_filter_context->data_count0_max = 0.0;
		p_clipping_filter_context->data_count0 = 0.0;
		p_clipping_filter_context->slope = 0.0;
		p_clipping_filter_context->up_continue_count = 0;
		p_clipping_filter_context->min_data_count = 0;
		p_clipping_filter_context->up_min_data = 0.0;

		for (i = 0; i < 10; i++){
			p_clipping_filter_context->sf4_buf[i] = 0.0;
		}

		p_clipping_filter_context->sf4_min_data = 100.0;
		p_clipping_filter_context->sf4_min_data_index = 0;
		p_clipping_filter_context->Daily_minimum_value = 100.0;
		p_clipping_filter_context->last_Daily_minimum_value = 0.0;
		p_clipping_filter_context->Daily_minimum_value_count = 0;
		p_clipping_filter_context->Daily_minimum_value_sum = 0.0;
		p_clipping_filter_context->Daily_minimum_value_avg = 0.0;
		p_clipping_filter_context->max_data = 0.0;
	}
}

void init_esa_compensate_context(jni_esa_compensate_context_t *p_esa_compensate_context){
	if (p_esa_compensate_context != NULL){
		int i = 0;
		p_esa_compensate_context->k_data = 0.0;
		p_esa_compensate_context->ESA_min_data = 100.0;
		p_esa_compensate_context->ESA_flag = 0;
		p_esa_compensate_context->ESA_sum = 0.0;
		p_esa_compensate_context->ESA_average = 0.0;
		p_esa_compensate_context->baseline = 0.0;
		p_esa_compensate_context->b1_data = 0.0;
		p_esa_compensate_context->data_12 = 0.0;

		for (i = 0; i < 10; i++){
			p_esa_compensate_context->fit10_x[i] = 0.0;
			p_esa_compensate_context->fit10_y[i] = 0.0;
		}

		for (i = 0; i < 35; i++){
			p_esa_compensate_context->fit36_x[i] = 0.0;
			p_esa_compensate_context->fit36_y[i] = 0.0;
		}

		p_esa_compensate_context->last_mean_data = 0.0;
		p_esa_compensate_context->continue_mean_count = 0.0;
		p_esa_compensate_context->bl_last_data = 0.0;
		p_esa_compensate_context->bl_last_last_data = 0.0;
		p_esa_compensate_context->bl_min_flag = 0.0;
		p_esa_compensate_context->last_baseline_cgm = 0.0;
		p_esa_compensate_context->slowly_chang_value = 0.0;
		p_esa_compensate_context->deferred_compensation_flag = 0;
		p_esa_compensate_context->deferred_compensation_count = 0;
		p_esa_compensate_context->baseline_chang_value = 0.0;
	}
}

void init_regular_deconvolution_context(jni_regular_deconvolution_context_t* p_regular_deconvolution_context){
	if (p_regular_deconvolution_context != NULL){
		int i = 0;
		for (i = 0; i < 30; i++){
			p_regular_deconvolution_context->ig_value_buf[i] = 0.0;
		}
	}
}

void init_filter1_context(jni_filter_context_t* p_filter1_context){
	if (p_filter1_context != NULL){
		int i = 0;
		for (i = 0; i < 3; i++){
			p_filter1_context->m_a_data[i] = 0.0;
			p_filter1_context->m_b_data[i] = 0.0;
			p_filter1_context->m_filter_data[i] = 0.0;
			p_filter1_context->m_temp_data[i] = 0.0;
		}
	}
}

void init_arrow_direction_context(jni_arrow_direction_context_t* p_arrow_direction_context_t){
	if (p_arrow_direction_context_t != NULL){
		p_arrow_direction_context_t->blood_glucose_trend = 0;
		p_arrow_direction_context_t->last_blood_glucose_trend = 0;

		p_arrow_direction_context_t->arrow_direction_data = 0.0;

		p_arrow_direction_context_t->last_arrow_direction_data = 0.0;
		p_arrow_direction_context_t->last_last_arrow_direction_data = 0.0;

		p_arrow_direction_context_t->rise_trend_count = 0;

		p_arrow_direction_context_t->decline_trend_count = 0;

		p_arrow_direction_context_t->horizontal_direction_count = 0;

		p_arrow_direction_context_t->arrow_direction_count = 0;
	}
}

int init_algorithm_context(jni_algorithm_context_t* p_algorithm_context){
	int ret = -1;
	if (p_algorithm_context != NULL){
		char* cur_version_name = get_algorithm_version();

		if ((cur_version_name != NULL) && (strlen(cur_version_name) < MAX_VERSION_NAME_LEN)){
			memset(p_algorithm_context->version_name, 0x0, MAX_VERSION_NAME_LEN);
			strcpy(p_algorithm_context->version_name, cur_version_name);
			p_algorithm_context->esa_calibration_enable = DEF_ESA_CALIBRATION_ENABLE;
			p_algorithm_context->finger_blood_calibration_enable = DEF_FINGER_BLOOD_CALIBRATION_ENABLE;

			p_algorithm_context->IG_data = 0.0;
			p_algorithm_context->last_IG_data = 0.0;
			p_algorithm_context->cgm_warning = 0;
			p_algorithm_context->cgm_current_abnormal = 0;
			p_algorithm_context->cgm_temp_abnormal = 0;
			p_algorithm_context->cgm_blood_glucose_trend = 0;

			init_judgment_context(&(p_algorithm_context->mJudgmentContext));
			init_current_correction_context(&(p_algorithm_context->mCurrentCorrectionContext));

			init_kalman_context(&(p_algorithm_context->mKalmanContext));

			init_cal_baseline_context(&(p_algorithm_context->mCalBaselineContext));

			init_clipping_filter_context(&(p_algorithm_context->mClippingFilterContext));

            init_esa_compensate_context(&(p_algorithm_context->mESACompensateContext));

			init_filter1_context(&p_algorithm_context->mFilter1Context);

			init_filter1_context(&p_algorithm_context->mFilter2Context);

			init_regular_deconvolution_context(&(p_algorithm_context->mRegularDeconvolutionContext));

			init_arrow_direction_context(&(p_algorithm_context->mArrowDirectionContext));
			ret = 0;
		}		
	}
	return ret;
}

double algorithm_convert_process(jni_algorithm_context_t* p_algorithm_context, double current_data, double temperature, int index, int* error_status, double low_alarm_value, double high_alarm_value){

    int  abnormal_status = 0;
	double m_current_data = current_data;
	double m_temperature = temperature;
	double CGM_data = 0.0;   //存放ESA和异常值处理后的血糖值
	index = index -1;

	if (p_algorithm_context != NULL){
		jni_judgment_context_t* p_judgment_context = &p_algorithm_context->mJudgmentContext;
		jni_current_correction_context_t* p_cor_context = &p_algorithm_context->mCurrentCorrectionContext;
		jni_kalman_context_t* p_kalman_context = &p_algorithm_context->mKalmanContext;
		jni_cal_baseline_context_t* p_cal_baseline_context = &p_algorithm_context->mCalBaselineContext;
		jni_clipping_filter_context_t* p_clipping_filter_context = &p_algorithm_context->mClippingFilterContext;
		jni_esa_compensate_context_t* p_esa_compensate_context = &p_algorithm_context->mESACompensateContext;
		jni_regular_deconvolution_context_t* p_regular_deconvolution_context = &p_algorithm_context->mRegularDeconvolutionContext;
		jni_arrow_direction_context_t *p_arrow_direction_context = &p_algorithm_context->mArrowDirectionContext;

		double sf4 = 0.0;
		double sf5 = 0.0;

		if (p_judgment_context != NULL){
			abnormal_status = Abnormal_Judgement(p_judgment_context, m_current_data, m_temperature, index);

			if ((abnormal_status & TEMPERATURE_LOWER) == TEMPERATURE_LOWER){
				p_algorithm_context->cgm_temp_abnormal = 1;
			}else if ((abnormal_status & TEMPERATURE_HIGHER) == TEMPERATURE_HIGHER){
				p_algorithm_context->cgm_temp_abnormal = 2;
			}else{
				p_algorithm_context->cgm_temp_abnormal = 0;
			}

			if ((abnormal_status & CURRENT_LOWER) == CURRENT_LOWER){
				p_algorithm_context->cgm_current_abnormal = 1;
			}else if ((abnormal_status & CURRENT_HIGHER) == CURRENT_HIGHER){
				p_algorithm_context->cgm_current_abnormal = 2;
			}else{
				p_algorithm_context->cgm_current_abnormal = 0;
			}
		}

		if (p_cor_context != NULL){
			m_current_data = Abnormal_Value_Correction(p_cor_context, p_cor_context->mS, m_current_data, index);
		}

		if (p_kalman_context != NULL){
			m_current_data = Kalman_Filter(p_kalman_context, m_current_data, index + 1);
		}

		m_current_data = temperature_compensation(m_temperature, m_current_data);

		CGM_data = On_data_in_five_minute(((m_current_data - 0.5) / p_cor_context->mS), index);

        p_algorithm_context->last_IG_data = p_algorithm_context->IG_data;

		if (CGM_data != -1){
			jni_filter_context_t* p_filter1_context = &(p_algorithm_context->mFilter1Context);
			jni_filter_context_t* p_filter2_context = &(p_algorithm_context->mFilter2Context);

			p_filter1_context->m_a_data[0] = 1.0;
			p_filter1_context->m_a_data[1] = 1.56101808;
			p_filter1_context->m_a_data[2] = 0.64135154;
			p_filter1_context->m_b_data[0] = 0.8005924;
			p_filter1_context->m_b_data[1] = 1.60118481;
			p_filter1_context->m_b_data[2] = 0.8005924;
			sf4 = functionFilter(CGM_data, p_filter1_context->m_filter_data,
								 p_filter1_context->m_temp_data, p_filter1_context->m_a_data,
								 p_filter1_context->m_b_data, ((index + 1) / 5 - 1));


			p_filter2_context->m_a_data[0] = 1.0;
			p_filter2_context->m_a_data[1] = -0.74778918;
			p_filter2_context->m_a_data[2] = 0.27221494;
			p_filter2_context->m_b_data[0] = 0.13110644;
			p_filter2_context->m_b_data[1] = 0.26221288;
			p_filter2_context->m_b_data[2] = 0.13110644;

			sf5 = functionFilter(CGM_data, p_filter2_context->m_filter_data,
								 p_filter2_context->m_temp_data, p_filter2_context->m_a_data,
								 p_filter2_context->m_b_data, ((index + 1) / 5 - 1));

			if ((p_cal_baseline_context != NULL) && (p_clipping_filter_context != NULL)){
				double temp_cgm_data = 0;
				double up_trend_data = 0;
				double data_avg = 0;
				Clipping_filter(p_clipping_filter_context, p_cal_baseline_context, sf4, sf5, CGM_data, ((index + 1) / 5 - 1));

				up_trend_data = p_clipping_filter_context->ret_tmp_data[0];
				data_avg = p_clipping_filter_context->ret_tmp_data[1];
				temp_cgm_data = p_clipping_filter_context->ret_tmp_data[2];

				if (p_esa_compensate_context != NULL){
					p_algorithm_context->IG_data = ESA_Compensate(p_esa_compensate_context, up_trend_data, temp_cgm_data, data_avg, ((index + 1) / 5 - 1));
					if(p_regular_deconvolution_context != NULL)
						p_algorithm_context->IG_data = Regular_deconvolution(p_regular_deconvolution_context, p_algorithm_context->IG_data, ((index + 1) / 5 - 1));

					int n = 1;
					if (p_algorithm_context->IG_data < 4.2){
						p_algorithm_context->IG_data = (double)((int)(p_algorithm_context->IG_data * pow(10, n))) / pow(10, n);
					}else{
						p_algorithm_context->IG_data = (double)((int)(p_algorithm_context->IG_data * pow(10, n) + 0.5)) / pow(10, n);
					}					
				}
			}

			if (p_arrow_direction_context != NULL){
				p_arrow_direction_context->blood_glucose_trend = Arrow_direction(p_arrow_direction_context, p_algorithm_context->IG_data, ((index + 1) / 5 - 1));
				p_algorithm_context->cgm_blood_glucose_trend = p_arrow_direction_context->blood_glucose_trend;
			}

			if (p_algorithm_context->IG_data < low_alarm_value){
				p_algorithm_context->cgm_warning = 1;
			}else if (p_algorithm_context->IG_data >= high_alarm_value){
				p_algorithm_context->cgm_warning = 2;
			}else{
				p_algorithm_context->cgm_warning = 0;
			}			
		}
	}

    double CGM_value = p_algorithm_context->IG_data;
    if (CGM_data == -1) CGM_value = 0;
    if (CGM_value < 0) CGM_value = 0;

	return  CGM_value;
}


#if 0
typedef struct {
	char *cal_name ,//= "ver 1.0"

	double (*cal_func)(double );


}kkk;

kkk[3]={
{"ver 1.0",my_cal_func}
{"ver 2.0",my_cal_func}
{"ver 3.0",my_cal_func}

};
#endif

