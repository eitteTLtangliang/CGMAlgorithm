//
// Created by l.tan on 2021/5/25.
//

#ifdef _WINDOWS
#include <math.h>
#include "../header/native_clipping_filter_context.h"
#endif

#ifdef __ANDROID__
#include <jni.h>
#include <android/log.h>
#include <math.h>
#include "../header/native_clipping_filter_context.h"
#endif

void Clipping_filter(jni_clipping_filter_context_t *p_clipping_filter_context, jni_cal_baseline_context_t *p_cal_baseline_context, double sf4_data, double sf5_data, double cgm_data, int index){

    double temp_data = 0;
    double mean_data  = 0;
    double sum = 0.0;
    double temp_buf[3] = { 0,0 };

    int i = 0;

    if((p_clipping_filter_context != NULL) && (p_cal_baseline_context != NULL)) {
        //求方差
        for (i = 0; i < 14; i++) {
            p_clipping_filter_context->CGM_var_windows[i] = p_clipping_filter_context->CGM_var_windows[i + 1];
            sum = sum + p_clipping_filter_context->CGM_var_windows[i + 1];
        }

        p_clipping_filter_context->CGM_var_windows[14] = sf4_data;

        sum = sum + sf4_data;
        mean_data = sum / 15;
        sum = 0;

        for (i = 0; i < 15; i++){
            sum = sum + (p_clipping_filter_context->CGM_var_windows[i] - mean_data)*(p_clipping_filter_context->CGM_var_windows[i] - mean_data);
        }

        p_clipping_filter_context->CGM_var_data = sum / 15;

        //十点方差
        sum = 0;

        for (i = 0; i < 9; i++){
            p_clipping_filter_context->sf4_buf[i] = p_clipping_filter_context->sf4_buf[i + 1];
            sum = sum + p_clipping_filter_context->sf4_buf[i + 1];
        }

        p_clipping_filter_context->sf4_buf[9] = sf4_data;
        sum = sum + sf4_data;
        mean_data = sum / 10;
        sum = 0;

        for (i = 0; i < 10; i++){
            sum = sum + ( p_clipping_filter_context->sf4_buf[i] - mean_data)*( p_clipping_filter_context->sf4_buf[i] - mean_data);
        }

        if ((sf4_data > p_clipping_filter_context->max_data) && (index > 24)){
            p_clipping_filter_context->max_data = sf4_data;
        }

        if (index % 288 == 0){
            p_clipping_filter_context->sf4_min_data = 100;
        }else{
            if ((sf4_data < p_clipping_filter_context->sf4_min_data) && (index > 12)){
                p_clipping_filter_context->sf4_min_data = sf4_data;
                p_clipping_filter_context->sf4_min_data_index = index;
            }
        }

        //判断平稳的时间
        if ((sum/10)*10+5 <= 5.8){
            p_clipping_filter_context->var_data_count = p_clipping_filter_context->var_data_count + 1;
        }else{
            p_clipping_filter_context->var_data_count = 0;
        }

        double sf_data2 = 0;
        sf_data2 = Calibration_baseline(p_cal_baseline_context, sf4_data, sf5_data, index);

        if (index % 288 == 0){
            p_clipping_filter_context->data_count = p_clipping_filter_context->data_count + 1;
            p_clipping_filter_context->min_data_buf[p_clipping_filter_context->data_count - 1] = 100;
        }else{
            if ((p_clipping_filter_context->min_data < p_clipping_filter_context->min_data_buf[p_clipping_filter_context->data_count - 1]) && (p_clipping_filter_context->min_data>0) && (p_clipping_filter_context->count > 2)){
                p_clipping_filter_context->min_data_buf[p_clipping_filter_context->data_count - 1] = p_clipping_filter_context->min_data;
            }
        }

        //求血糖下降时候的极大值
        if (((sf4_data - p_cal_baseline_context->last_data) <= 0) && ((p_cal_baseline_context->last_last_data - p_cal_baseline_context->last_data) <= 0)){
            p_clipping_filter_context->continue_down_flag = 1;
            p_clipping_filter_context->continue_down_count = 0;
            p_clipping_filter_context->last_continue_down_max_data = p_clipping_filter_context->continue_down_max_data;
            p_clipping_filter_context->continue_down_max_data = p_cal_baseline_context->last_data;
        }

        if ((sf4_data < 6) && (p_cal_baseline_context->last_data > 6)){
            p_clipping_filter_context->seven_point_index = index;
        }

        if (p_clipping_filter_context->continue_down_flag == 1){
            p_clipping_filter_context->continue_down_count = p_clipping_filter_context->continue_down_count + 1;
        }else{
            p_clipping_filter_context->continue_down_count = 0;
        }

        if ((p_clipping_filter_context->short_ESA_flag == 0) && (index>4) && (index<864)){
            if (((p_cal_baseline_context->last_data - p_cal_baseline_context->last_last_data) < 0) && ((p_cal_baseline_context->last_data - sf4_data) < 0)){
                if (p_clipping_filter_context->min_data == 0){
                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                }else if ((p_cal_baseline_context->last_data - p_clipping_filter_context->min_data) < 0){
                    if ((p_clipping_filter_context->continue_down_max_data > 3) && (p_clipping_filter_context->continue_down_max_data<6) && ((p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data)>0.7) && (p_cal_baseline_context->last_data < 5) && (p_clipping_filter_context->continue_down_count>2) && (p_clipping_filter_context->continue_down_count<=10) && (p_clipping_filter_context->error_flag == 0) && (index>36)){
                        if ((p_cal_baseline_context->last_data < p_clipping_filter_context->min_data_buf[p_clipping_filter_context->data_count - 1]) && (p_clipping_filter_context->count < 30)){
                            if (p_clipping_filter_context->data_count >= 5){
                                if (p_cal_baseline_context->last_data < p_clipping_filter_context->min_data_buf[4]){
                                    if ((index > 864) && ((index - p_clipping_filter_context->seven_point_index) > 40)){
                                        p_clipping_filter_context->short_ESA_flag = 1;
                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                    }else{
                                        if ((index > 864) && ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) > 0.5)){
                                            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                        }else{
                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                        }
                                    }
                                }else{
                                    if (p_clipping_filter_context->min_data - p_cal_baseline_context->last_data < 0.5){
                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                    }else{
                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                    }
                                }
                            }else{
                                if (p_cal_baseline_context->last_data < 5){
                                    if ((index < 576) && (fabs(p_cal_baseline_context->last_data - p_clipping_filter_context->min_data_buf[p_clipping_filter_context->data_count - 1]) < 0.6) && ((index - p_clipping_filter_context->seven_point_index) < 40) && (p_clipping_filter_context->seven_point_index>0)){
                                        if ((index > 288) && ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) > 0.3)){
                                            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                        }else{
                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                        }
                                    }else{

                                        if (index > 100){
                                            p_clipping_filter_context->slope = (p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data) / (p_clipping_filter_context->continue_down_count);

                                            if ((p_clipping_filter_context->slope > 0.1) && (p_clipping_filter_context->continue_down_max_data <6)){

                                                if (((index - p_clipping_filter_context->seven_point_index) > 30) && (p_clipping_filter_context->continue_down_count <= 8)){
                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                    p_clipping_filter_context->short_ESA_flag = 1;
                                                }else{
                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                }

                                            }else{

                                                if ((p_clipping_filter_context->continue_down_count > 8) && ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) > 0.3)){
                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                }else{
                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                }

                                            }
                                        }else{

                                            if (((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) > 0.3) && (p_clipping_filter_context->var_data_count > 10)){
                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                            }else{

                                                if ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) < 0.3){
                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                }else{
                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                }
                                            }
                                        }
                                    }
                                }else{
                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                }
                            }
                        }else{
                            if ((p_cal_baseline_context->last_data < p_clipping_filter_context->min_data_buf[p_clipping_filter_context->data_count - 1]) && (index < 2880) && ((index-p_clipping_filter_context->seven_point_index)>40)){
                                p_clipping_filter_context->short_ESA_flag = 1;
                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                            }else{
                                if (p_clipping_filter_context->count < 15){
                                    if ((p_clipping_filter_context->count < 5) && ((p_clipping_filter_context->min_data-p_cal_baseline_context->last_data)<0.2)){
                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                    }else{
                                        if ((p_clipping_filter_context->count > 10) && ((p_clipping_filter_context->min_data-p_cal_baseline_context->last_data)<0.5))
                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                        else{
                                            if ((index < 2880) || ((index - p_clipping_filter_context->seven_point_index)>30)){
                                                if (index < 576 && ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data)<0.5) && (p_clipping_filter_context->min_data>p_cal_baseline_context->last_data)){
                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                }else{
                                                    p_clipping_filter_context->short_ESA_flag = 1;
                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                }
                                            }else{
                                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                            }
                                        }
                                    }
                                }else{
                                    if (p_cal_baseline_context->last_data < 5){
                                        if ((p_clipping_filter_context->count > 10) && (p_clipping_filter_context->min_data-p_cal_baseline_context->last_data<0.3) && (p_clipping_filter_context->var_data_count>0)){
                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                        }else{
                                            if ((index < 80) && ((p_clipping_filter_context->max_data - p_cal_baseline_context->last_data)>2) && (p_clipping_filter_context->max_data > 6)){
                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                            }else{
                                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                            }
                                        }
                                    }else{
                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                    }
                                }
                            }
                        }
                    }else{
                        if (p_clipping_filter_context->error_flag == 1){

                            if ((p_clipping_filter_context->continue_down_max_data > 2.5) && (p_clipping_filter_context->continue_down_max_data<6) && ((p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data)>0.7) && (p_clipping_filter_context->continue_down_count > 2) && (p_clipping_filter_context->continue_down_count <= 15) && (index > 50) && (p_clipping_filter_context->count<30) && (p_cal_baseline_context->last_data>2.2)){
                                p_clipping_filter_context->short_ESA_flag = 1;
                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                            }else{

                                if ((index > 80) && ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) > 1) && (p_cal_baseline_context->last_data>2)){
                                    p_clipping_filter_context->short_ESA_flag = 1;
                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                }else{
                                    if ((p_clipping_filter_context->continue_down_count <15) && ((p_clipping_filter_context->last_min_data-p_cal_baseline_context->last_data)>0.6) &&  (index > 80)){
                                        p_clipping_filter_context->short_ESA_flag = 1;
                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                    }else{
                                        if ((p_clipping_filter_context->count > 48) && ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) > 0.5)){
                                            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                        }else{
                                            if (index > 576){
                                                if ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) < 0.5){
                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                }else{
                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                }
                                            }else{
                                                if ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) < 0.8){
                                                    if ((index < 120) && (p_clipping_filter_context->max_data < 5)){
                                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                    }else{
                                                        if ((p_clipping_filter_context->count < 24) && (index < 288) && (p_clipping_filter_context->var_data_count >= 15) && (p_cal_baseline_context->last_data>0)){
                                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                        }else{
                                                            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                        }
                                                    }
                                                }else{
                                                    if (p_clipping_filter_context->var_data_count < 5){
                                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                    }else{
                                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }else{

                            if ((p_clipping_filter_context->continue_down_count > 10) && ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) >= 0.3) && (index > 288) && (p_clipping_filter_context->continue_down_max_data < 5.5) && (p_clipping_filter_context->continue_down_count <= 13) && ((index - p_clipping_filter_context->seven_point_index) >= 30) && (p_cal_baseline_context->last_data < 4) &&  (p_clipping_filter_context->count < 30) ){
                                p_clipping_filter_context->short_ESA_flag = 1;

                                if ((p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data) < 0.6){
                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                }else{
                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                }
                            }else{
                                if ((p_clipping_filter_context->data_count >= 3) && ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) > 0.3) ){
                                    if (p_clipping_filter_context->min_data_buf[p_clipping_filter_context->data_count - 1] != 100){
                                        if (p_clipping_filter_context->min_data_buf[p_clipping_filter_context->data_count - 1] - p_cal_baseline_context->last_data > 0.3){
                                            if (p_clipping_filter_context->count > 48){
                                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                            }else{
                                                if ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) > 0.3){
                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                }else{
                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                }
                                            }
                                        }else{
                                            if ((p_clipping_filter_context->count > 36) && (p_clipping_filter_context->continue_down_count > 10)){
                                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                            }else{
                                                if ((p_clipping_filter_context->continue_down_count > 10) && ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) > 0.5)){
                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                }else{
                                                    p_clipping_filter_context->slope = (p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data) / (p_clipping_filter_context->continue_down_count);
                                                    if ((p_clipping_filter_context->slope > 0.1) && (p_clipping_filter_context->continue_down_max_data < 6) && (p_clipping_filter_context->continue_down_count <= 8)){
                                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                        p_clipping_filter_context->short_ESA_flag = 1;
                                                    }else{
                                                        if ((index > 576) && ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) > 0.3))
                                                            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                        else
                                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                    }
                                                }
                                            }
                                        }
                                    }else{
                                        if ((p_clipping_filter_context->min_data_buf[p_clipping_filter_context->data_count - 2] - p_cal_baseline_context->last_data) > 0.3){
                                            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data-0.1;
                                        }else{
                                            if ((p_clipping_filter_context->count > 46) && (p_clipping_filter_context->continue_down_count > 10)){
                                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                            }else{
                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                            }
                                        }
                                    }
                                }else{
                                    if (((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) > 0.2) && (p_clipping_filter_context->count > 36) && (index > 180)){
                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                    }else{
                                        if ((p_clipping_filter_context->count > 6) && ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) > 0.3) && (index > 160)){
                                            if ((index < 200) && (p_cal_baseline_context->last_data > 4.5)){
                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                            }else{
                                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                            }
                                        }else{
                                            if ((index > 160) && (p_clipping_filter_context->continue_down_count > 6) && (((p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data) / p_clipping_filter_context->continue_down_count) > 0.1)){
                                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                            }else{
                                                if ((index < 160) && (p_cal_baseline_context->last_data < 3.9)){
                                                    if ((p_clipping_filter_context->var_data_count > 15) || ((p_cal_baseline_context->last_data > 4) && ((sf_data2 - p_cal_baseline_context->last_data) < 1))){
                                                        if (p_clipping_filter_context->max_data < 6)
                                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                        else
                                                            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                    }else{
                                                        if ((p_clipping_filter_context->max_data < 6) && (index < 100) && ((p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data) < 2))
                                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                        else
                                                            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                    }
                                                }else{
                                                    if ((index < 160) && (p_clipping_filter_context->max_data < 6)){
                                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                    }else{
                                                        if ((p_clipping_filter_context->count < 24) && ((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) < 0.1)){
                                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                        }else{
                                                            if ((index < 160) && (p_clipping_filter_context->count < 24)){
                                                                if (((p_clipping_filter_context->min_data - p_cal_baseline_context->last_data) > 0.3) && (p_clipping_filter_context->var_data_count > 30)){
                                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                }else{
                                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                                }
                                                            }else{
                                                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }else{
                    if ((p_cal_baseline_context->last_data - p_clipping_filter_context->min_data) >= 0.1){
                        if (((p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data) > 2) && ((p_cal_baseline_context->last_data+0.5) < sf_data2) && (p_clipping_filter_context->count>60)){
                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                        }else{
                            if ((p_clipping_filter_context->count > 80) && (p_cal_baseline_context->last_data < (sf_data2 + 0.5))){
                                if ((index>576) && ((p_cal_baseline_context->last_data-p_clipping_filter_context->min_data)>0.3)){
                                    if (((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.9< (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)) && (p_cal_baseline_context->last_data < sf_data2))
                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                    else if ((p_clipping_filter_context->min_data < p_cal_baseline_context->last_data) && (p_clipping_filter_context->var_data_count >= 20) && (p_cal_baseline_context->last_data < sf_data2)){
                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                    }else{
                                        p_clipping_filter_context->min_data =  p_clipping_filter_context->last_min_data;
                                    }
                                }else{
                                    if (((p_cal_baseline_context->last_data - p_clipping_filter_context->min_data) > 0.3) && ((p_cal_baseline_context->last_data - sf_data2) > 0)){
                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                    }else{
                                        if (((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.9 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)) && (p_cal_baseline_context->last_data<sf_data2))
                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                        else
                                            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                    }
                                }
                            }else{
                                if (p_clipping_filter_context->error_flag == 1){
                                    if ((p_cal_baseline_context->last_data - p_clipping_filter_context->min_data) < 0.3){
                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                    }else{
                                        if ((p_clipping_filter_context->count > 100) && (p_cal_baseline_context->last_data<4) && (p_cal_baseline_context->last_data>2.2)){
                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                        }else{
                                            if ((p_cal_baseline_context->last_data<2) && (p_cal_baseline_context->last_data>p_clipping_filter_context->last_min_data) && ((p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data) > 0.3)){
                                                if(index<200)
                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                            }else{
                                                if (((p_cal_baseline_context->last_data - p_clipping_filter_context->min_data) > 0.4) && (p_cal_baseline_context->last_data < (sf_data2 - 0.3)) && (p_clipping_filter_context->count < 15) && (index < 3168)){
                                                    if ((p_clipping_filter_context->min_data_count > 12) && ((p_clipping_filter_context->continue_down_max_data - p_clipping_filter_context->min_data)*0.8 < (p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data))){
                                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                    }else{
                                                        if ((p_clipping_filter_context->min_data_count <= 12) && ((p_clipping_filter_context->continue_down_max_data-p_clipping_filter_context->min_data) < 2) && ((p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data) > 0.5) && (p_clipping_filter_context->continue_down_count>3)){
                                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                        }else{
                                                            if ((p_clipping_filter_context->min_data_count<10) && ((p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data)>0.5) && (p_clipping_filter_context->continue_down_count >= 3)){
                                                                if (index < 180){
                                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                }else{
                                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                                }
                                                            }else{
                                                                if (p_clipping_filter_context->count < p_clipping_filter_context->min_data_count){
                                                                    if ((p_clipping_filter_context->count < 6) && ((p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data) > 0.5) && (p_clipping_filter_context->continue_down_count>=3)){
                                                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                    }else{
                                                                        if ((p_clipping_filter_context->count < 5) && (index < 288) && (p_clipping_filter_context->min_data < p_cal_baseline_context->last_data) && (p_clipping_filter_context->min_data < 3)){
                                                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                        }else{
                                                                            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                                        }
                                                                    }
                                                                }else{
                                                                    if ((p_clipping_filter_context->continue_down_count <= 3) && ((p_cal_baseline_context->last_data - p_clipping_filter_context->min_data) > 0.8) && (index <= 3)){
                                                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                    }else{
                                                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }else{
                                                    if (((p_cal_baseline_context->last_data - sf_data2) <= 0) && (p_clipping_filter_context->count > 64) && ((p_cal_baseline_context->last_data-p_clipping_filter_context->min_data)<1)){
                                                        p_clipping_filter_context->error_flag = 0;
                                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                    }else{
                                                        if ((p_clipping_filter_context->count > 24) && (index < 576) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.3 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)) && (p_clipping_filter_context->data_count0_max < 6)){
                                                            if ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) > 1.5){
                                                                if ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.7< (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)){
                                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                }else{
                                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                                }
                                                            }else{
                                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                            }
                                                        }else{
                                                            if ((p_clipping_filter_context->count > 12) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.5 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)) && (p_clipping_filter_context->data_count0_max < 6)){
                                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                            }else{
                                                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }else{
                                    if (((p_cal_baseline_context->last_data - p_clipping_filter_context->min_data) > 0.3) && (p_cal_baseline_context->last_data < (sf_data2 - 0.2)) && (p_clipping_filter_context->count < 15) && (p_cal_baseline_context->last_data>3)){
                                        if ((p_cal_baseline_context->last_data - p_clipping_filter_context->min_data) > 0.5){
                                            if ((p_cal_baseline_context->last_data < (sf_data2 - 0.3)) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.7 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)))
                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                            else{
                                                if ((p_clipping_filter_context->count < 4) && (index<100)){
                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                }else{
                                                    if ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.5 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data))
                                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                    else{
                                                        if ((index < 864) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) < 1) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.2 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data))){
                                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                        }else{
                                                            if ((index < 288) && (p_clipping_filter_context->count < 6) && (sf4_data<sf_data2)){
                                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                            }else{
                                                                if ((p_clipping_filter_context->min_data < p_cal_baseline_context->last_data) && (p_clipping_filter_context->var_data_count>36) && (p_clipping_filter_context->count > 5)){
                                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                }else{
                                                                    if ((index < 288) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.5 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data))){
                                                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                    }else{
                                                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }else{
                                            if ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.9 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data))
                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                            else{
                                                if ((p_clipping_filter_context->data_count0_max < 6) && (index<200))
                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                else{
                                                    if ((p_cal_baseline_context->last_data > p_clipping_filter_context->min_data) && (p_clipping_filter_context->var_data_count > 20) && (p_cal_baseline_context->last_data < sf_data2)){
                                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                    }else{
                                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                    }
                                                }
                                            }
                                        }
                                    }else{
                                        if ((p_clipping_filter_context->count > 48) && ((p_cal_baseline_context->last_data - sf_data2) < -0.1) && ((p_clipping_filter_context->continue_down_max_data-p_cal_baseline_context->last_data)>0.1)){
                                            if (index < 200){
                                                if ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.8 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)){
                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                }else{
                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                }
                                            }else{
                                                if ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.8 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)){
                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                }else{
                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                }
                                            }
                                        }else{
                                            if ((p_clipping_filter_context->count <= 8) && ((p_clipping_filter_context->continue_down_max_data - p_clipping_filter_context->min_data) > 0.1) && (p_cal_baseline_context->last_data < sf_data2)){
                                                if ((index > 576) && ((p_cal_baseline_context->last_data - p_clipping_filter_context->min_data) > 0.8)){
                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                }else{
                                                    if ((p_clipping_filter_context->count > 3) && ((p_cal_baseline_context->last_data - p_clipping_filter_context->min_data) > 0.8))
                                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                    else{
                                                        if ((index > 2880) && (p_clipping_filter_context->count > 2) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) * 0.5 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)))
                                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                        else{
                                                            if (((index < 288) || ((p_clipping_filter_context->data_count0_max<5) && (p_clipping_filter_context->count>5) && ((p_clipping_filter_context->data_count0_max-p_cal_baseline_context->last_data)>0.3)) ) && (p_cal_baseline_context->last_data<(sf_data2-0.5)) && (p_clipping_filter_context->sf4_min_data < 1.5))
                                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                            else{
                                                                if ((p_clipping_filter_context->min_data < p_cal_baseline_context->last_data) && (p_clipping_filter_context->var_data_count>20) && (p_cal_baseline_context->last_data < (sf_data2-0.3))){
                                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                }else{
                                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }else{
                                                if ((p_clipping_filter_context->count > 15) && ((p_clipping_filter_context->continue_down_max_data - p_clipping_filter_context->min_data) > 0.1) && (p_cal_baseline_context->last_data < (sf_data2-0.3))){
                                                    if (index < 288){
                                                        if ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.5 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)){
                                                            if ((p_clipping_filter_context->data_count0_max < 6) && (p_cal_baseline_context->last_data < p_clipping_filter_context->min_data)){
                                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                            }else if ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.8 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)){
                                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                            }else{
                                                                if ((p_clipping_filter_context->data_count0_max < 6.5) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) < 3) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) * 0.6 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data))){
                                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                }else{
                                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                                }
                                                            }
                                                        }else{
                                                            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                        }
                                                    }else if ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) > 2){
                                                        if ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.9 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data))
                                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                        else
                                                            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                    }else{
                                                        if (index > 576){
                                                            if ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.7 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data))
                                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                            else{
                                                                if ((p_clipping_filter_context->min_data < p_cal_baseline_context->last_data) && (p_clipping_filter_context->var_data_count>20) && (p_cal_baseline_context->last_data < sf_data2)){
                                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                }else{
                                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                                }
                                                            }
                                                        }else{
                                                            if ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data)*0.7 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data))
                                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                            else{
                                                                if ((p_clipping_filter_context->count > 12) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) * 0.6 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) > 1) && ((p_cal_baseline_context->last_data - p_clipping_filter_context->min_data) < 1)){
                                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                }else{
                                                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }else{
                                                    if (index > 1440){
                                                        if ((p_clipping_filter_context->count > 24) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) * 0.8 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)) && (p_cal_baseline_context->last_data < (sf_data2 - 0.2)))
                                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                        else{
                                                            if ((p_clipping_filter_context->var_data_count > 30) && (p_clipping_filter_context->count > 5) && (p_cal_baseline_context->last_data > p_clipping_filter_context->min_data) && (p_cal_baseline_context->last_data < sf_data2)){
                                                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                            }else{
                                                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                            }
                                                        }
                                                    }else{
                                                        if ((p_clipping_filter_context->count > 24) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) * 0.9 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)) && (p_cal_baseline_context->last_data < sf_data2) && (index > 576))
                                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                        else{
                                                            if (((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) * 0.5 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)) && (p_cal_baseline_context->last_data < sf_data2) && (index < 576)){
                                                                if (((p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data) > 2) && (p_clipping_filter_context->data_count0_max > 6)){
                                                                    if ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) * 0.9 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data))
                                                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                    else
                                                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                                }else{
                                                                    if (((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) > 1) && (p_clipping_filter_context->count > 12) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) * 0.8 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data))){
                                                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                    }else{
                                                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                                    }
                                                                }
                                                            }else{
                                                                if ((p_clipping_filter_context->min_data < p_cal_baseline_context->last_data) && (p_clipping_filter_context->var_data_count > 20) && (p_cal_baseline_context->last_data < sf_data2)){
                                                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                }else{
                                                                    if ((index > 864) && ((sf_data2 - p_clipping_filter_context->last_min_data) > 1) && ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) * 0.5 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data)) && (p_cal_baseline_context->last_data < sf_data2))
                                                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                                                    else
                                                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }else{
                        p_clipping_filter_context->slope = 0;
                        if ((p_clipping_filter_context->count > 10) && (p_cal_baseline_context->max_point_data > 0))
                            p_clipping_filter_context->slope = (p_clipping_filter_context->data_count0_max - sf4_data) / (index - p_cal_baseline_context->max_point_data);
                        if ((p_clipping_filter_context->slope > 0.15) || (p_cal_baseline_context->last_data >= sf_data2)){
                            if (p_cal_baseline_context->last_data > p_clipping_filter_context->last_min_data)
                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                            else
                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                        }else{
                            if (((p_cal_baseline_context->last_data - p_clipping_filter_context->min_data) > 0) && (index > 288)){
                                if ((p_clipping_filter_context->data_count0_max - p_clipping_filter_context->min_data) * 0.9 < (p_clipping_filter_context->data_count0_max - p_cal_baseline_context->last_data))
                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                else
                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                            }else
                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                        }
                    }
                }
                p_clipping_filter_context->continue_down_flag = 0;
            }
        }else{
            if ((index > 4) && (p_clipping_filter_context->short_ESA_flag == 1)){
                if (((p_cal_baseline_context->last_data - p_cal_baseline_context->last_last_data) < 0) && ((p_cal_baseline_context->last_data - sf4_data) < 0)){
                    p_clipping_filter_context->continue_down_flag = 0;
                }

                if (((p_cal_baseline_context->last_data - p_cal_baseline_context->last_last_data) >= 0) && ((p_cal_baseline_context->last_data - sf4_data) >= 0)){
                    if (p_clipping_filter_context->continue_down_count >= 20){
                        if (index > 288){
                            if (p_cal_baseline_context->last_data > 2.2){
                                p_clipping_filter_context->short_ESA_flag = 0;
                                if (p_clipping_filter_context->count < 20){
                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                }else{
                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                }
                            }
                        }else{
                            p_clipping_filter_context->short_ESA_flag = 0;
                            if (p_clipping_filter_context->error_flag == 0){
                                if (p_clipping_filter_context->count > 20){
                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                }else{
                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                }
                            }else{
                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                            }
                        }
                    }else{
                        if ((index > 288) && ((p_cal_baseline_context->last_data-p_cal_baseline_context->last_last_data)<0) && ((p_cal_baseline_context->last_data-sf4_data)<0)){
                            if (p_cal_baseline_context->last_data > 3){
                                p_clipping_filter_context->short_ESA_flag = 0;
                                if (p_clipping_filter_context->min_data > p_cal_baseline_context->last_data)
                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                else{
                                    if (index > 864){
                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                    }else{
                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                    }
                                }
                            }
                        }else{
                            p_clipping_filter_context->short_ESA_flag = 0;
                            if ((fabs(p_clipping_filter_context->continue_down_max_data - p_clipping_filter_context->last_continue_down_max_data) < 0.2) && (p_cal_baseline_context->last_data>p_clipping_filter_context->min_data) && (p_cal_baseline_context->last_data<sf_data2)){
                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                            }
                        }
                    }
                }else{
                    if ((sf4_data > 4) && (sf4_data > p_clipping_filter_context->continue_down_max_data) && (p_clipping_filter_context->continue_down_max_data > 3)){
                        p_clipping_filter_context->short_ESA_flag = 0;
                        if ((p_clipping_filter_context->continue_down_max_data - p_clipping_filter_context->last_min_data) < 1.5){
                            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                        }else{
                            if (p_clipping_filter_context->continue_down_max_data < sf_data2){
                                p_clipping_filter_context->min_data = p_clipping_filter_context->continue_down_max_data;
                            }else{
                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                            }
                        }
                    }else if (p_clipping_filter_context->count > 15){
                        p_clipping_filter_context->short_ESA_flag = 0;
                        if (p_cal_baseline_context->last_data > p_clipping_filter_context->min_data){
                            if ((index > 576) && ((p_cal_baseline_context->last_data - p_clipping_filter_context->continue_down_max_data) < 1))
                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                            else
                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                        }
                    }else{
                        p_clipping_filter_context->short_ESA_flag = 0;
                        if ((p_cal_baseline_context->last_data > p_clipping_filter_context->min_data) && (p_clipping_filter_context->count > 10)){
                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                        }
                    }
                }
            }
        }

        if ((sf4_data < 1.5) &&  (index >4)){
            if (((sf4_data - sf_data2) > 0) && (fabs(p_clipping_filter_context->continue_down_max_data - sf4_data) < 1) && (p_clipping_filter_context->count<15)){
                p_clipping_filter_context->error_flag = 0;
                p_clipping_filter_context->short_ESA_flag = 1;
                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
            }else{
                p_clipping_filter_context->error_flag = 1;
            }
        }

        if ((sf4_data <1.5) && (index>2880 || index< 576) && (index>4)){
            p_clipping_filter_context->error_flag = 1;
        }

        if (p_clipping_filter_context->error_flag == 1 ){
            if (sf4_data > sf_data2){
                p_clipping_filter_context->error_flag = 0;
                p_clipping_filter_context->min_data = p_clipping_filter_context->min_data + (sf_data2 - p_clipping_filter_context->last_min_data) / 2;
            }
        }

        if ((p_clipping_filter_context->var_data_count > 5) && (p_clipping_filter_context->short_ESA_flag == 1)){
            p_clipping_filter_context->short_ESA_flag = 0;
        }

        double temp_last_data = 0;

        if (((p_cal_baseline_context->last_data - p_cal_baseline_context->last_last_data) < 0) && ((p_cal_baseline_context->last_data - sf4_data) < 0) && (index>4)){
            if ((p_clipping_filter_context->var_data_count < 48) && (index < 864)){
                if ((p_clipping_filter_context->min_data != p_clipping_filter_context->last_min_data) && (p_clipping_filter_context->last_min_data > p_cal_baseline_context->last_data)){
                    if (p_clipping_filter_context->continue_down_max_data < p_clipping_filter_context->min_data){
                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                    }else{
                        if ((p_cal_baseline_context->last_data < 3.9) && (p_clipping_filter_context->continue_down_count >= 5) && ((p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data) > 0.5)){
                            temp_last_data = p_clipping_filter_context->min_data;
                            p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 3.8;
                            if (index < 864){
                                if((p_clipping_filter_context->min_data - p_clipping_filter_context->last_min_data) > 0.5){
                                    if ((temp_last_data != p_cal_baseline_context->last_data) && (p_clipping_filter_context->count>12)){
                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                    }else{
                                        p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                    }
                                }
                            }
                        }else{
                            if ((p_clipping_filter_context->last_min_data > sf_data2) && index < 60){
                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                            }else{
                                if ((index < 60) && (p_clipping_filter_context->min_data < p_clipping_filter_context->last_min_data) && (p_clipping_filter_context->min_data > 3.9)){
                                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                }else{
                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                }
                            }
                        }
                    }
                }else{
                    if ((p_cal_baseline_context->last_data < 3.9) && (p_clipping_filter_context->continue_down_count >= 3) && ((p_clipping_filter_context->continue_down_max_data - p_cal_baseline_context->last_data) > 0.5) && (p_clipping_filter_context->short_ESA_flag == 0)){
                        temp_last_data = p_clipping_filter_context->min_data;
                        p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 3.8;
                        if (index < 864){
                            if ((p_clipping_filter_context->min_data - p_clipping_filter_context->last_min_data) > 0.3){
                                if ((temp_last_data != p_cal_baseline_context->last_data) && (p_clipping_filter_context->count>12)){
                                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                }else{
                                    if (p_cal_baseline_context->last_data < 3.8){
                                        p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 3.8;
                                    }else{
                                        if (p_cal_baseline_context->last_data > p_clipping_filter_context->last_min_data)
                                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                                        else
                                            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                    }
                                }
                            }
                        }
                    }
                }
            }else{
                if ((p_cal_baseline_context->last_data <= p_clipping_filter_context->min_data) && (p_cal_baseline_context->last_data < sf_data2) && (index<864)){
                    if ((p_cal_baseline_context->last_data < 3.2) && (sf_data2> 3.9) ){
                        p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 3.9;
                    }else{
                        if (index > 864){
                            if ((sf_data2 - p_cal_baseline_context->last_data) < 0.8){
                                p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                            }
                        }else{
                            p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                        }
                    }
                }
            }
        }

        if (((p_cal_baseline_context->last_data - p_cal_baseline_context->last_last_data) < 0) && ((p_cal_baseline_context->last_data - sf4_data) < 0) && (p_cal_baseline_context->last_data < 2.8) &&  ((sf_data2 + p_cal_baseline_context->last_data - p_clipping_filter_context->min_data) < 2.8) && (index > 4)){
            if (index > 288){
                if ((sf_data2 + p_cal_baseline_context->last_data - p_clipping_filter_context->min_data) < 2.8){
                    if (p_cal_baseline_context->last_data < 2.2){
                        p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 3.0;
                    }else if (p_cal_baseline_context->last_data < 2.8){
                        p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 3.3;
                    }
                }else{
                    if (p_cal_baseline_context->last_data < 3.9)
                        p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 3.9;
                }
            }
        }

        if ((sf4_data < p_cal_baseline_context->last_data) && ((p_clipping_filter_context->continue_down_max_data - sf4_data) > 0.5) && (p_clipping_filter_context->continue_down_count > 5) && (sf4_data < 3.5) && (index<864) && (index>4)){
            temp_last_data = p_clipping_filter_context->min_data;
            p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 3.9;

            if ((p_clipping_filter_context->min_data - p_clipping_filter_context->last_min_data) > 0.3){

                if (temp_last_data != p_cal_baseline_context->last_data){
                    p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                }else{
                    p_clipping_filter_context->min_data = p_cal_baseline_context->last_data;
                }
            }
        }

        if ((index >= 864) && ((p_cal_baseline_context->last_data - p_cal_baseline_context->last_last_data) < 0) && ((p_cal_baseline_context->last_data - sf4_data) < 0)){
            if (p_cal_baseline_context->last_data < 4.1){
                if (p_cal_baseline_context->last_data <= 1)
                    p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 3.5;
                else if (p_cal_baseline_context->last_data <= 2)
                    p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 2.8;
                else if (p_cal_baseline_context->last_data <= 3)
                    p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 3.3;
                else if (p_cal_baseline_context->last_data <= 3.6)
                    p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 3.6;
            }
        }

        if ((index < 12) && (sf4_data < 4.4) && (index > 4)){
            if (sf4_data < p_cal_baseline_context->last_data){
                p_clipping_filter_context->min_data = sf_data2 + sf4_data - 4;
            }
        }else{
            if ((index < 12) && (p_clipping_filter_context->min_data > sf_data2)){
                p_clipping_filter_context->min_data = 4.7;
            }
        }

        if((p_clipping_filter_context->min_data != p_clipping_filter_context->last_min_data) && (index>4)){
            if(((p_cal_baseline_context->last_data-p_cal_baseline_context->last_last_data)<0) && ((p_cal_baseline_context->last_data-sf4_data)<0)){
                if(p_clipping_filter_context->max_data<6){
                    if((sf_data2-p_clipping_filter_context->min_data)<3){
                        if(p_clipping_filter_context->min_data>p_clipping_filter_context->last_min_data){
                            if((sf4_data<3.9) && (p_clipping_filter_context->min_data>p_cal_baseline_context->last_data)){
                                if(((sf_data2+p_cal_baseline_context->last_data-p_clipping_filter_context->last_min_data)>3.8) && ((p_clipping_filter_context->continue_down_max_data-sf4_data)>1) && (p_clipping_filter_context->continue_down_count>6)){
                                    p_clipping_filter_context->min_data=sf_data2+p_cal_baseline_context->last_data-3.9;
                                }else{
                                    p_clipping_filter_context->min_data=p_clipping_filter_context->last_min_data;
                                }
                            }else{
                                p_clipping_filter_context->min_data=p_cal_baseline_context->last_data;
                            }
                        }
                    }
                }else if(p_clipping_filter_context->max_data<7){
                    if(sf_data2<p_clipping_filter_context->min_data){
                        if((sf_data2>p_clipping_filter_context->last_min_data) && ((sf_data2-p_clipping_filter_context->last_min_data)<2)){
                            p_clipping_filter_context->min_data=p_clipping_filter_context->last_min_data;
                        }
                    }else{
                        if(p_clipping_filter_context->min_data>p_clipping_filter_context->last_min_data){
                            if((sf_data2-p_clipping_filter_context->min_data)<1){
                                if((sf_data2 - p_clipping_filter_context->last_min_data)<2){
                                    p_clipping_filter_context->min_data=p_clipping_filter_context->last_min_data;
                                }else{
                                    p_clipping_filter_context->min_data=sf_data2-2;
                                }
                            }
                        }
                    }
                }else if(p_clipping_filter_context->max_data<8){
                    if(sf_data2<p_clipping_filter_context->min_data){
                        if((sf_data2>p_clipping_filter_context->last_min_data) && ((sf_data2-p_clipping_filter_context->last_min_data)<1.5)){
                            p_clipping_filter_context->min_data=p_clipping_filter_context->last_min_data;
                        }
                    }else{
                        if(p_clipping_filter_context->min_data>p_clipping_filter_context->last_min_data){
                            if((sf_data2-p_clipping_filter_context->last_min_data)<1.5){
                                p_clipping_filter_context->min_data=p_clipping_filter_context->last_min_data;
                            }
                        }
                    }
                }else if(p_clipping_filter_context->max_data<9){
                    if(sf_data2<p_clipping_filter_context->min_data){
                        if(sf_data2>p_clipping_filter_context->last_min_data){
                            if((sf_data2-p_clipping_filter_context->last_min_data)<1){
                                p_clipping_filter_context->min_data=p_clipping_filter_context->last_min_data;
                            }else if((p_cal_baseline_context->last_data>p_clipping_filter_context->last_min_data) && (sf_data2-p_cal_baseline_context->last_data)<1){
                                p_clipping_filter_context->min_data=p_cal_baseline_context->last_data;
                            }else{
                                p_clipping_filter_context->min_data=sf_data2-1;
                            }
                        }
                    }else{
                        if((sf_data2>p_clipping_filter_context->last_min_data) && (p_clipping_filter_context->min_data>p_clipping_filter_context->last_min_data)){
                            if(p_clipping_filter_context->last_min_data<1){
                                p_clipping_filter_context->min_data=p_clipping_filter_context->last_min_data;
                            }
                        }
                    }
                }else if(p_clipping_filter_context->max_data<10){
                    if(sf_data2<p_clipping_filter_context->min_data){
                        if((sf_data2 >p_clipping_filter_context->last_min_data) && ((sf_data2-p_clipping_filter_context->last_min_data)<0.6)){
                            p_clipping_filter_context->min_data=p_clipping_filter_context->last_min_data;
                        }
                    }else{
                        if((sf_data2>p_clipping_filter_context->last_min_data) && (p_clipping_filter_context->min_data>p_clipping_filter_context->last_min_data)){
                            if(((sf_data2-p_clipping_filter_context->last_min_data)>(sf_data2-p_cal_baseline_context->last_data)) && ((sf_data2-p_clipping_filter_context->last_min_data)<1)){
                                p_clipping_filter_context->min_data=p_cal_baseline_context->last_data;
                            }else{
                                if(p_clipping_filter_context->min_data<p_clipping_filter_context->last_min_data){
                                    p_clipping_filter_context->min_data=p_clipping_filter_context->last_min_data;
                                }
                            }
                        }else{
                            if((sf_data2-p_clipping_filter_context->last_min_data)>(sf_data2-p_cal_baseline_context->last_data)){
                                p_clipping_filter_context->min_data=p_cal_baseline_context->last_data;
                            }else{
                                p_clipping_filter_context->min_data=p_clipping_filter_context->last_min_data;
                            }
                        }
                    }
                }else{
                    if((sf_data2-p_clipping_filter_context->min_data)>0.3){
                        p_clipping_filter_context->min_data=p_clipping_filter_context->last_min_data;
                    }
                }
            }else{
                if(p_clipping_filter_context->max_data<9){
                    if(((sf_data2-p_clipping_filter_context->min_data)>=0.8) && ((sf_data2-p_clipping_filter_context->last_min_data)<0.8)){
                        if(index>100){
                            p_clipping_filter_context->min_data=p_clipping_filter_context->last_min_data;
                        }
                    }
                }else{
                    if(index<576){
                        if(sf4_data<3.3){
                            p_clipping_filter_context->min_data=sf_data2+sf4_data-3.3;
                        }else if(sf4_data<3.8){
                            p_clipping_filter_context->min_data=sf_data2 + sf4_data-3.8;
                        }
                    }else{
                        if((sf_data2-p_clipping_filter_context->min_data)>0.5){
                            if(sf_data2-p_clipping_filter_context->last_min_data>0.5){
                                p_clipping_filter_context->min_data=sf_data2-0.3;
                            }else{
                                p_clipping_filter_context->min_data=p_clipping_filter_context->last_min_data;
                            }
                        }
                    }
                }
            }
        }else{
            if( p_clipping_filter_context->max_data >= 10 ){
                if (((sf_data2 - p_clipping_filter_context->min_data) > 0) && ((sf4_data - p_cal_baseline_context->last_data) < 0)){
                    if (p_cal_baseline_context->last_data < 2.8){
                        if (index < 288){
                            p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 3.8;
                        }else
                            p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 2.8;
                    }else if ((p_cal_baseline_context->last_data < 3.7) && (index < 864)){
                        p_clipping_filter_context->min_data = sf_data2 + p_cal_baseline_context->last_data - 3.7;
                    }else{
                        if (index < 576){
                            if ((p_clipping_filter_context->sf4_min_data < 2.5) && (index < 320) ){
                                if ((index < 288) && (p_clipping_filter_context->max_data > 11)){
                                    if (p_clipping_filter_context->sf4_min_data < 1){
                                        p_clipping_filter_context->min_data = sf_data2 - 0.5;
                                    }else{
                                        p_clipping_filter_context->min_data = sf_data2 - 0.3 ;
                                    }
                                }else{
                                    p_clipping_filter_context->min_data =sf_data2 - 1;
                                }
                            }else{
                                if ((index > 288) && (p_clipping_filter_context->max_data > 11)){
                                    if (p_clipping_filter_context->sf4_min_data < 1){
                                        p_clipping_filter_context->min_data = sf_data2 - 0.8;
                                    }else if ( p_clipping_filter_context->sf4_min_data < 2){
                                        p_clipping_filter_context-> min_data = sf_data2 - 0.5;
                                    }else if (p_clipping_filter_context->sf4_min_data < 3){
                                        p_clipping_filter_context->min_data = sf_data2 - 0.3;
                                    }
                                }else{
                                    if ((p_clipping_filter_context->sf4_min_data < 2) && ((index - p_clipping_filter_context->sf4_min_data_index) < 288)){
                                        p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                                    }else{
                                        if (p_clipping_filter_context->sf4_min_data < 3.3){
                                            p_clipping_filter_context->min_data = sf_data2 - 0.5;
                                        }else{
                                            p_clipping_filter_context->min_data = sf_data2;
                                        }
                                    }
                                }
                            }
                        }else{
                            if ((p_clipping_filter_context->sf4_min_data < 2) && ((index - p_clipping_filter_context->sf4_min_data_index) < 120)){
                                p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
                            }

                            if (index < 576){
                                if (p_clipping_filter_context->sf4_min_data < 1){
                                    p_clipping_filter_context->min_data = sf_data2 - 1;
                                }else if (p_clipping_filter_context->sf4_min_data < 2){
                                    p_clipping_filter_context->min_data = sf_data2 - 0.5;
                                }else if (p_clipping_filter_context->sf4_min_data < 3){
                                    p_clipping_filter_context->min_data = sf_data2 - 0.3;
                                }else{
                                    p_clipping_filter_context->min_data = sf_data2;
                                }
                            }else{
                                if (index < 864){
                                    if (p_clipping_filter_context->sf4_min_data < 1){
                                        p_clipping_filter_context->min_data = sf_data2 - 1.2;
                                    }else if (p_clipping_filter_context->sf4_min_data < 2){
                                        p_clipping_filter_context->min_data = sf_data2 - 0.8;
                                    }else if (p_clipping_filter_context->sf4_min_data < 3){
                                        p_clipping_filter_context->min_data = sf_data2 - 0.5;
                                    }else{
                                        p_clipping_filter_context->min_data = sf_data2;
                                    }
                                }
                            }
                        }
                    }
                }else{
                    if (((sf4_data - p_cal_baseline_context->last_data) > 0) && ((sf_data2 - p_clipping_filter_context->min_data) > 1)){
                        if (sf_data2 - sf4_data <= 0){
                            if (p_clipping_filter_context->sf4_min_data < 1){
                                p_clipping_filter_context->min_data = sf_data2 -0.8;
                            }else if (p_clipping_filter_context->sf4_min_data < 2){
                                p_clipping_filter_context->min_data = sf_data2 -0.5;
                            }else if (p_clipping_filter_context->sf4_min_data < 3){
                                p_clipping_filter_context->min_data = sf_data2 -0.3;
                            }else{
                                p_clipping_filter_context->min_data = sf_data2;
                            }
                        }
                    }else{
                        if (index > 864){
                            p_clipping_filter_context->min_data = sf_data2;
                        }
                    }
                }
            }else if(p_clipping_filter_context->max_data>9){
                if ((sf_data2 - p_clipping_filter_context->min_data) > 2){
                    if (index < 288){
                        p_clipping_filter_context->min_data =sf_data2 - 2;
                    }else{
                        p_clipping_filter_context->min_data = sf_data2 - 0.8;
                    }
                }
            }else if (p_clipping_filter_context->max_data >= 8){
                if (index > 576){
                    if ((sf_data2 - p_clipping_filter_context->min_data) > 0.3){
                        p_clipping_filter_context->min_data = sf_data2 -0.3;
                    }
                }
            }else if (p_clipping_filter_context->max_data >= 7){
                if (index > 576){
                    if ((sf_data2 - p_clipping_filter_context->min_data) > 0.6){
                        p_clipping_filter_context->min_data = sf_data2 -0.5;
                    }
                }
            }
        }

        if ((p_clipping_filter_context->min_data > 0) && (p_clipping_filter_context->last_min_data == 0)){
            if (sf4_data < 3.9){
                if ((sf_data2 + sf4_data - p_clipping_filter_context->min_data) > 3.9){
                    p_clipping_filter_context->min_data = sf_data2 + sf4_data - 3.9;
                }
            }
        }

        if ((p_clipping_filter_context->min_data < 0) && (p_cal_baseline_context->last_data < 0)){
            p_clipping_filter_context->min_data = p_clipping_filter_context->last_min_data;
        }

        if ((p_clipping_filter_context->count > 0) && ((p_clipping_filter_context->min_data + p_clipping_filter_context->count * 0.002) >= sf4_data)){
            if ((p_clipping_filter_context->count > 75) && (p_clipping_filter_context->var_data_count>0)){
                p_clipping_filter_context->min_data = sf4_data;
            }
            p_clipping_filter_context->count = 0;
        }

        if (index > 576){
            if (index % 288 == 0){
                p_clipping_filter_context->Daily_minimum_value_sum = p_clipping_filter_context->Daily_minimum_value + p_clipping_filter_context->Daily_minimum_value_sum;
                p_clipping_filter_context->Daily_minimum_value_count = p_clipping_filter_context->Daily_minimum_value_count + 1;
                if (index < 3168){
                    p_clipping_filter_context->Daily_minimum_value_avg = p_clipping_filter_context->Daily_minimum_value_sum / p_clipping_filter_context->Daily_minimum_value_count;
                }
                p_clipping_filter_context->last_Daily_minimum_value = p_clipping_filter_context->Daily_minimum_value;
                p_clipping_filter_context->Daily_minimum_value = 100;
            }else{
                if ((sf4_data < p_clipping_filter_context->Daily_minimum_value) &&  ((p_cal_baseline_context->last_data - p_cal_baseline_context->last_last_data) < 0) && ((p_cal_baseline_context->last_data - sf4_data) < 0)){
                    p_clipping_filter_context->Daily_minimum_value = sf4_data;
                }
            }

            if (index >= 2304){
                if (p_clipping_filter_context->Daily_minimum_value_avg > p_clipping_filter_context->Daily_minimum_value){
                    if ((2.5 < p_clipping_filter_context->Daily_minimum_value) && (p_clipping_filter_context->Daily_minimum_value < 4) && (p_clipping_filter_context->Daily_minimum_value_avg > 4)){
                        cgm_data = cgm_data;
                    }else{
                        if (p_clipping_filter_context->Daily_minimum_value >= p_clipping_filter_context->last_Daily_minimum_value){
                            cgm_data = cgm_data + p_clipping_filter_context->Daily_minimum_value_avg - p_clipping_filter_context->Daily_minimum_value;
                        }else if( (p_clipping_filter_context->Daily_minimum_value < p_clipping_filter_context->last_Daily_minimum_value) && (p_clipping_filter_context->last_Daily_minimum_value < p_clipping_filter_context->Daily_minimum_value_avg)){
                            cgm_data = cgm_data + p_clipping_filter_context->Daily_minimum_value_avg - p_clipping_filter_context->last_Daily_minimum_value;
                        }
                    }
                }else{
                    if ((p_clipping_filter_context->Daily_minimum_value_avg <= p_clipping_filter_context->Daily_minimum_value) && (p_clipping_filter_context->Daily_minimum_value_avg > p_clipping_filter_context->last_Daily_minimum_value) && (p_clipping_filter_context->last_Daily_minimum_value < 2.5) && (p_clipping_filter_context->Daily_minimum_value_avg < 4))
                        cgm_data = cgm_data + p_clipping_filter_context->Daily_minimum_value_avg - p_clipping_filter_context->last_Daily_minimum_value;
                }
            }
        }

        if (p_clipping_filter_context->short_ESA_flag == 1){
            temp_data = p_clipping_filter_context->min_data;
        }else{
            if (p_clipping_filter_context->min_data > sf4_data){
                temp_data = p_clipping_filter_context->min_data;
            }else{
                if (p_clipping_filter_context->min_data == 0.0){
                    if (index >= 4){
                        temp_data = sf4_data;
                    }else{
                        p_clipping_filter_context->min_data = sf_data2;
                        temp_data = sf_data2;
                    }
                }else{
                    if (sf_data2 == sf4_data && sf_data2 > sf4_data){
                        temp_data = sf4_data;
                    }else{
                        temp_data = p_clipping_filter_context->min_data ;
                    }
                }
            }
        }

        if (temp_data < sf4_data - 0.2){
            p_clipping_filter_context->min_data_count = p_clipping_filter_context->min_data_count + 1;
        }else{
            p_clipping_filter_context->min_data_count = 0;
        }

        if (temp_data < sf4_data){
            if (p_clipping_filter_context->data_count0_max < sf4_data){
                p_clipping_filter_context->data_count0_max = sf4_data;
                p_cal_baseline_context->max_point_data = index;
            }
        }else{
            if ((p_clipping_filter_context->count >= 12) && (p_cal_baseline_context->max_point_data > 0)){
                p_clipping_filter_context->slope = (p_clipping_filter_context->data_count0_max - sf4_data) / (index - p_cal_baseline_context->max_point_data);
                if (p_clipping_filter_context->slope < 0.1){
                    if ((p_clipping_filter_context->continue_down_max_data - sf4_data) / ((p_clipping_filter_context->continue_down_count) < 0.15) && (p_clipping_filter_context->continue_down_count > 3)){
                        p_clipping_filter_context->min_data = sf4_data;
                    }
                }
            }

            p_cal_baseline_context->max_point_data = 0;
            p_clipping_filter_context->data_count0_max = 0;
            p_clipping_filter_context->data_count0 = sf4_data;
        }

        if (p_clipping_filter_context->min_data == p_clipping_filter_context->last_min_data){
            p_clipping_filter_context->count = p_clipping_filter_context->count + 1;
        }else{
            p_clipping_filter_context->count = 0;
        }

        if ((sf4_data - p_cal_baseline_context->last_data) > 0){
            p_clipping_filter_context->up_continue_count = p_clipping_filter_context->up_continue_count + 1;
        }else{
            p_clipping_filter_context->up_min_data = sf4_data;
            p_clipping_filter_context->up_continue_count = 0;
        }

        p_cal_baseline_context->last_last_data = p_cal_baseline_context->last_data;
        p_cal_baseline_context->last_data = sf4_data;
        p_clipping_filter_context->last_min_data = p_clipping_filter_context->min_data;
        temp_buf[0] = cgm_data;
        temp_buf[1] = sf_data2;
        temp_buf[2] = temp_data;

        p_clipping_filter_context->ret_tmp_data[0] = cgm_data;
        p_clipping_filter_context->ret_tmp_data[1] = sf_data2;
        p_clipping_filter_context->ret_tmp_data[2] = temp_data;
    }
}

