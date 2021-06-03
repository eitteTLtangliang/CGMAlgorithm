//
// Created by LENOVO on 2021/5/6.
//
#ifdef _WINDOWS
#include <math.h>
#include "../header/native_esa_compensate_context.h"
#include "../header/native_least_square_linear_fit_context.h"
#endif

#ifdef __ANDROID__
#include <jni.h>
#include <android/log.h>
#include <math.h>
#include "../header/native_esa_compensate_context.h"
#include "../header/native_least_square_linear_fit_context.h"

#endif

double ESA_Compensate(jni_esa_compensate_context_t *p_esa_compensate_context,double data , double sf_data, double avg_data, int index){

    double temp_CGM_data = 0;
    double bl_mindata = 100;
    double bl_mindata_index = 0;

    if(p_esa_compensate_context != NULL){

        p_esa_compensate_context->ESA_sum = p_esa_compensate_context->ESA_sum + data;
        p_esa_compensate_context->ESA_average = p_esa_compensate_context->ESA_sum/(index + 1);

        if ((p_esa_compensate_context->last_mean_data - p_esa_compensate_context->ESA_average) > 0){
            p_esa_compensate_context->continue_mean_count = p_esa_compensate_context->continue_mean_count + 1;
        }else{
            p_esa_compensate_context->continue_mean_count = 0;
        }

        p_esa_compensate_context->last_mean_data = p_esa_compensate_context->ESA_average;

        if (((p_esa_compensate_context->bl_last_data - p_esa_compensate_context->bl_last_last_data) < 0) && ((p_esa_compensate_context->bl_last_data - p_esa_compensate_context->ESA_average) < 0)){
            p_esa_compensate_context->bl_min_flag = 1;
        }

        p_esa_compensate_context->bl_last_last_data = p_esa_compensate_context->bl_last_data;
        p_esa_compensate_context->bl_last_data = p_esa_compensate_context->ESA_average;

        if ((p_esa_compensate_context->ESA_min_data > data) && (index > 3)){
            p_esa_compensate_context->ESA_min_data = data;
        }

        if (index > 2 && index <= 12){
            p_esa_compensate_context->fit10_x[index - 3 ] = index;
            p_esa_compensate_context->fit10_y[index - 3] = data;
        }

        if (index> 1 && index <= 36){
            p_esa_compensate_context->fit36_x[index - 2] = index;
            p_esa_compensate_context->fit36_y[index - 2] = data;
        }

        if ((index >= 11) && (index < 36)){

            p_esa_compensate_context->baseline = avg_data;

            if (index == 12){
                p_esa_compensate_context->data_12 = data;
                p_esa_compensate_context->k_data = leastSquareLinearFit(p_esa_compensate_context->fit10_x, p_esa_compensate_context->fit10_y, 10);

                if ((p_esa_compensate_context->k_data < 0.2) || (p_esa_compensate_context->ESA_min_data < 3.5)){
                    p_esa_compensate_context->ESA_flag = 1;
                }
            }

            if (p_esa_compensate_context->ESA_flag == 0){
                temp_CGM_data = data;
            }else{

                if ((fabs(p_esa_compensate_context->baseline - sf_data - p_esa_compensate_context->last_baseline_cgm) > 0.3) && (p_esa_compensate_context->last_baseline_cgm > 0)){
                    p_esa_compensate_context->deferred_compensation_flag = 1;
                    p_esa_compensate_context->baseline_chang_value = p_esa_compensate_context->last_baseline_cgm;
                    p_esa_compensate_context->slowly_chang_value = fabs(p_esa_compensate_context->baseline - sf_data - p_esa_compensate_context->last_baseline_cgm);
                }

                if (p_esa_compensate_context->deferred_compensation_flag == 1){
                    p_esa_compensate_context->deferred_compensation_count = p_esa_compensate_context->deferred_compensation_count + 1;
                }else{
                    p_esa_compensate_context->deferred_compensation_count = 0;
                }

                if ((p_esa_compensate_context->deferred_compensation_flag == 1) && fabs(p_esa_compensate_context->slowly_chang_value - p_esa_compensate_context->deferred_compensation_count * 0.2) < 0.2){
                    p_esa_compensate_context->deferred_compensation_flag = 0;
                }

                if (p_esa_compensate_context->deferred_compensation_flag == 0){
                    if ((p_esa_compensate_context->baseline - sf_data) > 0){
                        temp_CGM_data = p_esa_compensate_context->baseline - sf_data + data;
                    }else{
                        temp_CGM_data = data;
                    }
                }else{
                    if ((p_esa_compensate_context->slowly_chang_value - p_esa_compensate_context->deferred_compensation_count * 0.2) >= 0.2){
                        if ((p_esa_compensate_context->baseline - sf_data - p_esa_compensate_context->baseline_chang_value) > 0){
                            temp_CGM_data = p_esa_compensate_context->baseline_chang_value + 0.2 *p_esa_compensate_context->deferred_compensation_count + data;
                        }else{
                            temp_CGM_data = p_esa_compensate_context->baseline_chang_value - 0.2 *p_esa_compensate_context->deferred_compensation_count + data;
                        }
                    }else{
                        if ((p_esa_compensate_context->baseline - sf_data) > 0){
                            temp_CGM_data = p_esa_compensate_context->baseline - sf_data + data;
                        }else{
                            temp_CGM_data = data;
                        }
                    }
                }

                p_esa_compensate_context->last_baseline_cgm = p_esa_compensate_context->baseline - sf_data;
            }
        }else if (index >= 36){

            if (index == 36){

                p_esa_compensate_context->k_data = leastSquareLinearFit(p_esa_compensate_context->fit36_x, p_esa_compensate_context->fit36_y, 35);

                if ((p_esa_compensate_context->bl_min_flag == 1) && (p_esa_compensate_context->ESA_min_data>3) && (p_esa_compensate_context->ESA_min_data<4)){
                    p_esa_compensate_context->baseline = p_esa_compensate_context->ESA_min_data;
                }else{

                    if ((p_esa_compensate_context->ESA_min_data > 4.4) && (p_esa_compensate_context->ESA_min_data < 6.6)){
                        p_esa_compensate_context->baseline = p_esa_compensate_context->ESA_min_data;
                    }

                    if ((p_esa_compensate_context->ESA_min_data < 4 )&& (p_esa_compensate_context->data_12 >4.4) && (p_esa_compensate_context->data_12 < 6.6)){
                        p_esa_compensate_context->baseline = p_esa_compensate_context->data_12-0.3;
                    }

                }

                if (p_esa_compensate_context->baseline > 6){
                    p_esa_compensate_context->baseline = avg_data;
                }

                if ((p_esa_compensate_context->k_data < -0.01) || (p_esa_compensate_context->ESA_min_data < 4.4)){
                    p_esa_compensate_context->ESA_flag = 1;
                }else{

                    if ((p_esa_compensate_context->ESA_flag == 1) && (p_esa_compensate_context->k_data < 0.008)){
                        p_esa_compensate_context->ESA_flag = 1;
                    }else{
                        p_esa_compensate_context->ESA_flag = 0;
                    }
                }
            }

            if ((p_esa_compensate_context->baseline > 5) && (p_esa_compensate_context->ESA_min_data <p_esa_compensate_context->baseline) && (p_esa_compensate_context->ESA_min_data >=3.5)){

                if (index <= 100){
                    p_esa_compensate_context->baseline = p_esa_compensate_context->ESA_min_data;
                }

            }

            if((p_esa_compensate_context->ESA_flag == 0) && (index > 2880)){
                p_esa_compensate_context->ESA_flag = 1;
            }

            if (p_esa_compensate_context->ESA_flag == 1){

                p_esa_compensate_context->baseline = avg_data;

                if ((fabs(p_esa_compensate_context->baseline - sf_data - p_esa_compensate_context->last_baseline_cgm) > 0.3) && (p_esa_compensate_context->last_baseline_cgm > 0)){
                    p_esa_compensate_context->deferred_compensation_flag = 1;
                    p_esa_compensate_context->baseline_chang_value = p_esa_compensate_context->last_baseline_cgm;
                    p_esa_compensate_context->slowly_chang_value = fabs(p_esa_compensate_context->baseline - sf_data - p_esa_compensate_context->last_baseline_cgm);
                }

                if (p_esa_compensate_context->deferred_compensation_flag == 1){
                    p_esa_compensate_context->deferred_compensation_count = p_esa_compensate_context->deferred_compensation_count + 1;
                }else{
                    p_esa_compensate_context->deferred_compensation_count = 0;
                }

                if ((p_esa_compensate_context->deferred_compensation_flag == 1) && (fabs(p_esa_compensate_context->slowly_chang_value - p_esa_compensate_context->deferred_compensation_count * 0.2) < 0.2)){
                    p_esa_compensate_context->deferred_compensation_flag = 0;
                }

                if (p_esa_compensate_context->deferred_compensation_flag == 0){

                    if (p_esa_compensate_context->baseline - sf_data > 0){
                        temp_CGM_data = p_esa_compensate_context->baseline - sf_data + data;
                    }else{
                        temp_CGM_data = data;
                    }
                }else{

                    if ((p_esa_compensate_context->slowly_chang_value - p_esa_compensate_context->deferred_compensation_count * 0.2) >= 0.2){
                        if ((p_esa_compensate_context->baseline - sf_data - p_esa_compensate_context->baseline_chang_value) > 0){
                            temp_CGM_data = p_esa_compensate_context->baseline_chang_value + 0.2 *p_esa_compensate_context->deferred_compensation_count + data;
                        }else{
                            temp_CGM_data = p_esa_compensate_context->baseline_chang_value - 0.2 *p_esa_compensate_context->deferred_compensation_count + data;
                        }
                    }else{

                        if ((p_esa_compensate_context->baseline - sf_data) > 0){
                            temp_CGM_data = p_esa_compensate_context->baseline - sf_data + data;
                        }else{
                            temp_CGM_data =  data;
                        }
                    }
                }
                p_esa_compensate_context->last_baseline_cgm = p_esa_compensate_context->baseline - sf_data;
            }else{

                if ((data < 4) && (p_esa_compensate_context->continue_mean_count>10) && (index<288)){
                    p_esa_compensate_context->ESA_flag = 1;
                }

                if ((index < 288) && (data < 2.2)){
                    p_esa_compensate_context->ESA_flag = 1;
                }
                temp_CGM_data = data;
            }
        }else{
            temp_CGM_data = data;
        }
    }

    return temp_CGM_data;
}



