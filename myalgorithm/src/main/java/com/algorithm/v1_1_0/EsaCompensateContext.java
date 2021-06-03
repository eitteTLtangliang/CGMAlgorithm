package com.algorithm.v1_1_0;

import java.io.Serializable;
import java.util.Arrays;

public final class EsaCompensateContext implements Serializable {

    public double k_data;
    public double ESA_min_data;
    public int ESA_flag;
    public double ESA_sum;
    public double ESA_average;
    public double baseline;
    public double b1_data;
    public double data_12;
    public double[] fit10_x;//存放用于线性回归的数据的下标数组
    public double[] fit10_y;//存放用于线性回归的电流值
    public double[] fit36_x;//存放用于线性回归的数据的下标数组
    public double[] fit36_y;//存放用于线性回归的电流值
    public double last_mean_data;
    public double continue_mean_count;
    public double bl_last_data;
    public double bl_last_last_data;
    public double bl_min_flag;
    public double last_baseline_cgm;
    public double slowly_chang_value;
    public int deferred_compensation_flag;
    public int deferred_compensation_count;
    public double baseline_chang_value;

    @Override
    public String toString() {

        return "EsaCompensateContext{"+
                "\n k_data=" + k_data +
                "\n ESA_min_data=" + ESA_min_data +
                "\n ESA_flag=" + ESA_flag +
                "\n ESA_sum=" + ESA_sum +
                "\n ESA_average=" + ESA_average +
                "\n baseline=" + baseline +
                "\n b1_data=" + b1_data +
                "\n data_12=" + data_12 +
                "\n fit10_x=" + Arrays.toString(fit10_x) +
                "\n fit10_y=" + Arrays.toString(fit10_y) +
                "\n fit36_x=" + Arrays.toString(fit36_x) +
                "\n fit36_y=" + Arrays.toString(fit36_y) +
                "\n last_mean_data=" + last_mean_data +
                "\n continue_mean_count=" + continue_mean_count +
                "\n bl_last_data=" + bl_last_data +
                "\n bl_last_last_data=" + bl_last_last_data +
                "\n bl_min_flag=" + bl_min_flag +
                "\n last_baseline_cgm=" + last_baseline_cgm +
                "\n slowly_chang_value=" + slowly_chang_value +
                "\n deferred_compensation_flag=" + deferred_compensation_flag +
                "\n deferred_compensation_count=" + deferred_compensation_count +
                "\n baseline_chang_value=" + baseline_chang_value +
                "}";
    }

}
