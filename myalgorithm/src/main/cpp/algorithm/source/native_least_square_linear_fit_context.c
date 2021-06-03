//
// Created by l.tan on 2021/5/25.
//

#ifdef _WINDOWS
#include <math.h>
#include "../header/native_least_square_linear_fit_context.h"
#endif

#ifdef __ANDROID__
#include <jni.h>
#include <math.h>
#include "../header/native_least_square_linear_fit_context.h"
#endif

double leastSquareLinearFit(double x[], double y[], const int num){

    double sum_x2 = 0.0;
    double sum_y = 0.0;
    double sum_x = 0.0;
    double sum_xy = 0.0;
    double a = 0.0;
    double b = 0.0;

    for (int i = 0; i < num; ++i) {
        sum_x2 += x[i] * x[i];
        sum_y += y[i];
        sum_x += x[i];
        sum_xy += x[i] * y[i];
    }

    a = (num*sum_xy - sum_x * sum_y) / (num*sum_x2 - sum_x * sum_x);
    b = (sum_x2*sum_y - sum_x * sum_xy) / (num*sum_x2 - sum_x * sum_x);

    //  k_data = a;
    return a;
}