#ifdef _WINDOWS
#include <math.h>
#include "../header/native_current_judgment_context.h"
#include "../header/native_abnormal_judgment_context.h"
#endif

#ifdef __ANDROID__
#include <jni.h>
#include <math.h>
#include "../header/native_current_judgment_context.h"
#include "../header/native_abnormal_judgment_context.h"
#endif

int Abnormal_Judgement(jni_judgment_context_t *p_jud_context, double electric_current, double temperature, int index){

    int ret = 0;
    jni_current_judgment_context_t *p_current_jud_context = NULL;

    if(p_jud_context != NULL){
        int i = 0;
        double *p_flag_buffer = p_jud_context->abnormal_flag_buf;
        p_current_jud_context = &p_jud_context->m_current_jud_context;

        for(i=0; i<(MAX_ABNORMAL_FLAG_SIZE-1);i++){
            p_flag_buffer[i] = p_flag_buffer[i+1];
        }

        p_flag_buffer[MAX_ABNORMAL_FLAG_SIZE-1] = Judgment_of_current_abnormality(p_current_jud_context, electric_current, index);
        p_jud_context->current_abnormal_flag_count = 0;

        if (index >= MAX_ABNORMAL_FLAG_SIZE){
            for (i = 0; i < MAX_ABNORMAL_FLAG_SIZE; i++){
                if(p_flag_buffer[i] == 1){
                    p_jud_context->current_abnormal_flag_count = p_jud_context->current_abnormal_flag_count + 1;
                }
            }
        }

        if(electric_current < 1){
            p_jud_context->abnormal_count = p_jud_context->abnormal_count + 1;
        }else{
            p_jud_context->abnormal_count = 0;
        }

        if (temperature < MIN_TEMPERATURE_VAL){
            ret |= TEMPERATURE_LOWER;
        }else if (temperature > MAX_TEMPERATURE_VAL){
            ret |= TEMPERATURE_HIGHER;
        }

        if (p_jud_context->abnormal_count >= MIN_CURRENT_ABNORMAL_COUNT){
            ret |= CURRENT_LOWER;
        }else if(p_jud_context->current_abnormal_flag_count >= MAX_CURRENT_ABNORMAL_COUNT){
            ret |= CURRENT_HIGHER;
        }
    }

    return ret;
}


