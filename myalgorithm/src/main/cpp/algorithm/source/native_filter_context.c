//
// Created by LENOVO on 2021/5/4.
//

#ifdef _WINDOWS
#include "../header/native_filter_context.h"
#endif

#ifdef __ANDROID__
#include "../header/native_filter_context.h"
#endif

double functionFilter(double data, double *filter_data, double *temp_data, double *a, double *b, int index){

	if (index == 0){
		filter_data[0] = b[0] * data;
		temp_data[0] = data;
		return filter_data[0];
	}else if (index == 1){
		filter_data[1] = b[0] * data + b[1] * temp_data[0] - a[1] * filter_data[0];
		temp_data[1] = data;
		return filter_data[1];
	}else{
		filter_data[2] = b[0] * data + b[1] * temp_data[1] + b[2] * temp_data[0] - a[1] * filter_data[1] - a[2] * filter_data[0];
		temp_data[0] = temp_data[1];
		temp_data[1] = data;
		filter_data[0] = filter_data[1];
		filter_data[1] = filter_data[2];
		return filter_data[2];
	}

}





