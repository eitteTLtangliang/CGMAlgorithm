//
// Created by LENOVO on 2021/4/29.
//

#ifndef MY_APPLICATION_NATIVE_ABNORMAL_JUDGMENT_CONTEXT_H
#define MY_APPLICATION_NATIVE_ABNORMAL_JUDGMENT_CONTEXT_H

#ifdef  __cplusplus
extern "C" {
#endif

#define   MAX_ABNORMAL_FLAG_SIZE				15

#define  TEMPERATURE_LOWER                     (0x1<<0)
#define  TEMPERATURE_HIGHER                    (0x1<<1)
#define  MAX_TEMPERATURE_VAL                   (42)
#define  MIN_TEMPERATURE_VAL                   (20)

#define  CURRENT_LOWER			               (0x1<<4)
#define  CURRENT_HIGHER                        (0x1<<5)

#define  MIN_CURRENT_ABNORMAL_COUNT            5
#define  MAX_CURRENT_ABNORMAL_COUNT            7


typedef struct{
    double abnormal_flag_buf[MAX_ABNORMAL_FLAG_SIZE];
    double current_abnormal_flag_count;
    int abnormal_count;
    jni_current_judgment_context_t m_current_jud_context;
}jni_judgment_context_t;


int Abnormal_Judgement(jni_judgment_context_t *p_jud_context, double electric_current, double temperature, int index);

#ifdef  __cplusplus
}
#endif
#endif //MY_APPLICATION_NATIVE_CURRENT_CORRECTION_CONTEXT_H
