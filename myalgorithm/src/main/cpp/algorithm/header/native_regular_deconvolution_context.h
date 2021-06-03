//
// Created by LENOVO on 2021/5/7.
//

#ifndef MY_APPLICATION_NATIVE_REGULAR_DECONVOLUTION_CONTEXT_H
#define MY_APPLICATION_NATIVE_REGULAR_DECONVOLUTION_CONTEXT_H
#ifdef  __cplusplus
extern "C" {
#endif


typedef struct{

    double ig_value_buf[30];

}jni_regular_deconvolution_context_t;

double Regular_deconvolution(jni_regular_deconvolution_context_t *p_regular_deconvolution_context,double IG_value,int index);

#ifdef  __cplusplus
}
#endif
#endif //MY_APPLICATION_NATIVE_REGULAR_DECONVOLUTION_CONTEXT_H



