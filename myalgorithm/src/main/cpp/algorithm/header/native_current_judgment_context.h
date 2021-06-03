//
// Created by LENOVO on 2021/4/29.
//

#ifndef MY_APPLICATION_NATIVE_CURRENT_JUDGMENT_CONTEXT_H
#define MY_APPLICATION_NATIVE_CURRENT_JUDGMENT_CONTEXT_H

#ifdef  __cplusplus
extern "C" {
#endif

#define  CURRENT_JUDGMENT_NUM_TEMP_DATA   2

typedef struct{
    double last_current;
    int abnormal_flag;
    double temp_data_buf[CURRENT_JUDGMENT_NUM_TEMP_DATA];
    double var_data;
    int con_count;
    int last_abnormal_flag;
    double max_current;
}jni_current_judgment_context_t;

int Judgment_of_current_abnormality(jni_current_judgment_context_t *p_current_jud_context, double data, int index);

#ifdef  __cplusplus
}
#endif
#endif //MY_APPLICATION_NATIVE_CURRENT_CORRECTION_CONTEXT_H
