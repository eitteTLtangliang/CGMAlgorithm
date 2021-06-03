//
// Created by LENOVO on 2021/5/4.
//

#ifdef _WINDOWS
#include <math.h>
#include "../header/native_cal_baseline_context.h"
#endif

#ifdef __ANDROID__
#include <jni.h>
#include <android/log.h>
#include <math.h>
#include "../header/native_cal_baseline_context.h"
#endif


double Calibration_baseline(jni_cal_baseline_context_t *p_cal_baseline_context, double sf4_data, double sf5_data, int index){

    if(p_cal_baseline_context != NULL){
        if (sf5_data - p_cal_baseline_context->last_sf_data >= 0.05){
            p_cal_baseline_context->fasting_continue_count = p_cal_baseline_context->fasting_continue_count + 1;

            if (p_cal_baseline_context->last_trend_data_count == 1){
                if (p_cal_baseline_context->fasting_max_data - p_cal_baseline_context->last_fasting_min_data > 1){
                    p_cal_baseline_context->fasting_min_data = p_cal_baseline_context->last_fasting_min_data;
                   //  p_cal_baseline_context->last_fasting_min_index = p_cal_baseline_context->last_fasting_min_index;
                }else{
                    p_cal_baseline_context->fasting_min_index = index - 1;
                    p_cal_baseline_context->fasting_min_data = p_cal_baseline_context->last_sf_data;
                }
            }

            p_cal_baseline_context->last_trend_data_count = 0;
            p_cal_baseline_context->fasting_max_data = sf5_data;
            p_cal_baseline_context->fasting_max_index = index;

        }else{

            p_cal_baseline_context->last_fasting_min_data = p_cal_baseline_context->fasting_min_data;
            p_cal_baseline_context->last_fasting_min_index = p_cal_baseline_context->fasting_min_index;
            p_cal_baseline_context->last_trend_data_count = p_cal_baseline_context->last_trend_data_count + 1;

            if ((p_cal_baseline_context->last_trend_data_count == 2) && ((p_cal_baseline_context->fasting_max_data - p_cal_baseline_context->fasting_min_data) > 3.5) && ((p_cal_baseline_context->fasting_max_index - p_cal_baseline_context->fasting_min_index) > 9) && (index > 6) && (p_cal_baseline_context->fasting_min_data > 2.2) && (p_cal_baseline_context->fasting_min_data<10) && (p_cal_baseline_context->fasting_max_data>6.5)){
                p_cal_baseline_context->fasting_count = p_cal_baseline_context->fasting_count + 1;
                p_cal_baseline_context->temp_fasting_min_index = p_cal_baseline_context->fasting_min_index;
                p_cal_baseline_context->fasting_continue_count_sum = p_cal_baseline_context->fasting_continue_count_sum + p_cal_baseline_context->fasting_max_index - p_cal_baseline_context->fasting_min_index;
                p_cal_baseline_context->fasting_continue_data_sum = p_cal_baseline_context->fasting_continue_data_sum + p_cal_baseline_context->fasting_max_data - p_cal_baseline_context->fasting_min_data;
                p_cal_baseline_context->fasting_min_sum = p_cal_baseline_context->fasting_min_sum + p_cal_baseline_context->fasting_min_index;

                if ((p_cal_baseline_context->fasting_min_data > 4.2) && (p_cal_baseline_context->fasting_min_data < 10)){
                    if (p_cal_baseline_context->fasting_min_data_count > 0){
                        if (p_cal_baseline_context->fasting_min_index - p_cal_baseline_context->last_fasting_index > 192){

                            p_cal_baseline_context->fasting_min_data_count = p_cal_baseline_context->fasting_min_data_count + 1;
                            p_cal_baseline_context->fasting_min_value = p_cal_baseline_context->fasting_min_data;
                            p_cal_baseline_context->fasting_min_data_sum = p_cal_baseline_context->fasting_min_data_sum + p_cal_baseline_context->fasting_min_data;
                            p_cal_baseline_context->fasting_min_data_avg = p_cal_baseline_context->fasting_min_data_sum / (p_cal_baseline_context->fasting_min_data_count);
                            p_cal_baseline_context->last_fasting_index = p_cal_baseline_context->fasting_min_index;

                        }
                    }else{

                        p_cal_baseline_context->fasting_min_data_count = p_cal_baseline_context->fasting_min_data_count + 1;
                        p_cal_baseline_context->fasting_min_value = p_cal_baseline_context->fasting_min_data;

                        if (p_cal_baseline_context->fasting_min_data_count == 1){
                            p_cal_baseline_context->flag_index = p_cal_baseline_context->fasting_min_index;
                            p_cal_baseline_context->last_fasting_index = p_cal_baseline_context->fasting_min_index;
                            p_cal_baseline_context->fasting_min_data_sum = p_cal_baseline_context->fasting_min_data_sum + p_cal_baseline_context->fasting_min_data;
                            p_cal_baseline_context->fasting_min_data_avg = p_cal_baseline_context->fasting_min_data_sum / (p_cal_baseline_context->fasting_min_data_count);

                        }
                    }
                }

                p_cal_baseline_context->fasting_continue_count_avg = p_cal_baseline_context->fasting_continue_count_sum / (p_cal_baseline_context->fasting_count);
                p_cal_baseline_context->fasting_continue_data_avg = p_cal_baseline_context->fasting_continue_data_sum / (p_cal_baseline_context->fasting_count);
                p_cal_baseline_context->fasting_min_avg = p_cal_baseline_context->fasting_min_sum / (p_cal_baseline_context->fasting_count);
            }

            if(p_cal_baseline_context->last_trend_data_count != 1){
                p_cal_baseline_context->fasting_min_data = sf5_data;
                p_cal_baseline_context->fasting_min_index = index;
                p_cal_baseline_context->fasting_continue_count = 0;
            }
        }

        p_cal_baseline_context->last_sf_data = sf5_data;

        if (((p_cal_baseline_context->last_data - p_cal_baseline_context->last_last_data) < 0) && ((p_cal_baseline_context->last_data - sf4_data) < 0) && (index >= 3) && (index <= 36)){
            if ((sf4_data > 4.3) && (sf4_data < 5.2)){
                if (sf4_data < p_cal_baseline_context->temp_mean_baseline){
                    p_cal_baseline_context->temp_mean_baseline = sf4_data;
                }
            }

            if (p_cal_baseline_context->fasting_continue_data_avg > 4.5){
                if (p_cal_baseline_context->temp_mean_baseline > p_cal_baseline_context->fasting_continue_data_avg){
                    p_cal_baseline_context->temp_mean_baseline = p_cal_baseline_context->fasting_continue_data_avg;
                }
            }
        }

        if ((index>= 36) && (p_cal_baseline_context->temp_mean_baseline > sf4_data) && (index >= 3) && (sf4_data>4.5) && (sf4_data<p_cal_baseline_context->last_data) && (index<72)){
            p_cal_baseline_context->temp_mean_baseline = sf4_data;
        }

        if ((p_cal_baseline_context->temp_mean_baseline > 4) && (p_cal_baseline_context->temp_mean_baseline < 5.2)){
            p_cal_baseline_context->baseline_value =  p_cal_baseline_context->temp_mean_baseline;
        }else{
            p_cal_baseline_context->baseline_value = 4.7;
        }

        if (p_cal_baseline_context->fasting_min_data_avg > 0){
            if ((p_cal_baseline_context->flag_index < 400) && (index > 288) && (p_cal_baseline_context->fasting_min_value != p_cal_baseline_context->fasting_min_data_avg)){
                if ((fabs(p_cal_baseline_context->fasting_min_value - p_cal_baseline_context->fasting_min_data_avg) < 0.3) && ((p_cal_baseline_context->fasting_min_value-p_cal_baseline_context->fasting_continue_data_avg)<0.5))
                    p_cal_baseline_context->baseline_value = p_cal_baseline_context->fasting_min_value;
                else
                    p_cal_baseline_context->baseline_value = p_cal_baseline_context->last_last_baseline_value;
            }else{
                if (fabs(p_cal_baseline_context->baseline_value - p_cal_baseline_context->fasting_min_data_avg) > 0.6){
                    p_cal_baseline_context->baseline_value = p_cal_baseline_context->last_last_baseline_value;
                }
            }
        }else{
            if ((p_cal_baseline_context->fasting_min_avg > 0) && (fabs(p_cal_baseline_context->fasting_min_avg - p_cal_baseline_context->last_last_baseline_value) > 1)){
                p_cal_baseline_context->baseline_value = p_cal_baseline_context->last_baseline_value;
            }
        }

        p_cal_baseline_context->last_baseline_value = p_cal_baseline_context->baseline_value;
        p_cal_baseline_context->last_last_baseline_value = p_cal_baseline_context->last_baseline_value;
        return p_cal_baseline_context->baseline_value;
    }

    return 0.0;
}





