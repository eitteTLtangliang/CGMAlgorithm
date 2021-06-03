#ifdef _WINDOWS
#include <math.h>
#include "../header/native_current_judgment_context.h"
#endif

#ifdef __ANDROID__
#include <jni.h>
#include <math.h>
#include "../header/native_current_judgment_context.h"
#endif

int Judgment_of_current_abnormality(jni_current_judgment_context_t *p_current_jud_context, double data, int index){

    if(p_current_jud_context != NULL){

        double *tmp_buffer = p_current_jud_context->temp_data_buf;
        tmp_buffer[0] = tmp_buffer[1];
        tmp_buffer[1] = data;
        double mean_data = (tmp_buffer[0]  + tmp_buffer[1]) / 2;
        p_current_jud_context->var_data = ((tmp_buffer[0] - mean_data)*(tmp_buffer[0] - mean_data) + (tmp_buffer[1] - mean_data)*(tmp_buffer[1] - mean_data)) / 2;;

        if((p_current_jud_context->abnormal_flag == 1) && data <= 1){
            p_current_jud_context->abnormal_flag = 0;
        }

        if ((p_current_jud_context->abnormal_flag == 1) && (p_current_jud_context->var_data < 1) && (p_current_jud_context->con_count > 2)){
            p_current_jud_context->abnormal_flag = 0;
        }

        if(p_current_jud_context->var_data > 0.002){
            p_current_jud_context->con_count = p_current_jud_context->con_count + 1;
        }else{
            p_current_jud_context->con_count = 0;
        }

        //find  max  value
        if((fabs(p_current_jud_context->last_current - data) > 2) && (p_current_jud_context->var_data > 1) && (p_current_jud_context->abnormal_flag == 0) && (index > 2)){
            p_current_jud_context->abnormal_flag = 1;
        }else if (data < 1.5 && index < 60){
            p_current_jud_context->abnormal_flag = 1;
        }else{
            if ((p_current_jud_context->last_abnormal_flag == 1) && (data > p_current_jud_context->max_current) && (index > 15) && (p_current_jud_context->max_current > 0)){
                p_current_jud_context->abnormal_flag = 1;
            }
        }

 //////////////////////////////////////////// 60 min bef  //////////////////////////////////
        if (index < 60 && data>70){
            p_current_jud_context->abnormal_flag = 1;
        }

        if((p_current_jud_context->last_current > p_current_jud_context->max_current) && (p_current_jud_context->abnormal_flag == 0) && (index > 15)){
            p_current_jud_context->max_current = p_current_jud_context->last_current;
        }

        p_current_jud_context->last_current = data;
        p_current_jud_context->last_abnormal_flag = p_current_jud_context->abnormal_flag;
        return p_current_jud_context->abnormal_flag;

    }

    return 0;
}


