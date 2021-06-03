//
// Created by l.tan on 2021/5/25.
//
#ifdef _WINDOWS
#include <math.h>
#include "../header/native_temperature_compensation_context.h"
#endif

#ifdef __ANDROID__
#include <jni.h>
#include <math.h>
#include "../header/native_temperature_compensation_context.h"
#endif

double temperature_compensation(double temperature, double current){

    double temp = 0.0;
    const double coef[6] = { -5.88016277e-01, -6.92303637e+00, 6.73081791e-01, -2.72482356e-02, 5.19478420e-04, -3.84905329e-06 };
    double a = 0.7796610169491518;
    double b = 9.727118644067819;

    if (temperature < 20){
        temperature = 20;
    }

    if (temperature > 41){
        temperature = 32;
    }

    temp = coef[0] * temperature + coef[1] * pow(temperature, 2) + coef[2] * pow(temperature, 3) + coef[3] * pow(temperature, 4) + coef[4] * pow(temperature, 5) + coef[5] * pow(temperature, 6) + 360.13987401;

    current = current + (37 - (temp * a + b + 1)) * 0.02 * (current - 0.5);
    return current;
}