package com.algorithm.v1_1_0;

import java.io.Serializable;
import java.util.Arrays;

public final class ClippingFilterContext implements Serializable {

    public int error_flag;
    public int short_ESA_flag;

    public int count;
    public double last_min_data;
    public double min_data;

    public double continue_down_count;
    public int continue_down_flag;
    public double continue_down_max_data;
    public double last_continue_down_max_data;
    public double continue_down_min_data;

    public double[] CGM_var_windows;
    public double CGM_var_data;
    public int var_data_count;
    public double[] min_data_buf;
    public int data_count;
    public int seven_point_index;
    public double data_count0_max;
    public double  data_count0;
    public double slope;
    public int up_continue_count;
    public int min_data_count;
    public double up_min_data;

    public double[] sf4_buf;
    public double sf4_min_data;
    public int sf4_min_data_index;

    public double Daily_minimum_value;
    public double last_Daily_minimum_value;
    public int Daily_minimum_value_count;
    public double Daily_minimum_value_sum;
    public double Daily_minimum_value_avg;
    public double max_data;

    public double[] ret_tmp_data;

    @Override
    public String toString() {


        return "FilterContext{"+
                "\n error_flag=" + error_flag +
                "\n short_ESA_flag=" + short_ESA_flag +
                "\n count=" + count +
                "\n last_min_data=" + last_min_data +
                "\n min_data=" + min_data +
                "\n continue_down_count=" + continue_down_count +
                "\n continue_down_flag=" + continue_down_flag +
                "\n continue_down_max_data=" + continue_down_max_data +
                "\n last_continue_down_max_data=" + last_continue_down_max_data +
                "\n continue_down_min_data=" + continue_down_min_data +
                "\n CGM_var_windows=" + Arrays.toString(CGM_var_windows) +
                "\n CGM_var_data=" + CGM_var_data +
                "\n var_data_count=" + var_data_count +
                "\n min_data_buf=" + Arrays.toString(min_data_buf) +
                "\n data_count=" + data_count +
                "\n seven_point_index=" + seven_point_index +
                "\n data_count0_max=" + data_count0_max +
                "\n data_count0=" + data_count0 +
                "\n slope=" + slope +
                "\n up_continue_count=" + up_continue_count +
                "\n min_data_count=" + min_data_count +
                "\n up_min_data=" + up_min_data +
                "\n sf4_buf=" + Arrays.toString(sf4_buf) +
                "\n sf4_min_data=" + sf4_min_data +
                "\n sf4_min_data_index=" + sf4_min_data_index +
                "\n Daily_minimum_value=" + Daily_minimum_value +
                "\n last_Daily_minimum_value=" + last_Daily_minimum_value +
                "\n Daily_minimum_value_count=" + Daily_minimum_value_count +
                "\n Daily_minimum_value_sum=" + Daily_minimum_value_sum +
                "\n Daily_minimum_value_avg=" + Daily_minimum_value_avg +
                "\n max_data=" + max_data +
                "\n ret_tmp_data=" + Arrays.toString(ret_tmp_data) +
                "}";
    }

}
