package com.algorithm.v1_1_0;

import java.io.Serializable;

public final class CalBaseLineContext implements Serializable {

    public int fasting_continue_count;
    public double fasting_min_data;
    public double last_fasting_min_data;
    public int temp_fasting_min_index;
    public int last_fasting_min_index;
    public int fasting_max_index;
    public int fasting_min_index;
    public double fasting_max_data;
    public int fasting_continue_count_sum;
    public double fasting_continue_count_avg;
    public double fasting_continue_data_sum;
    public double fasting_continue_data_avg;
    public double fasting_count;
    public int last_trend_data_count;
    public double temp_mean_baseline;  // 20
    public double baseline_value;
    public double last_baseline_value;
    public double last_last_baseline_value;

    public double last_data;
    public double last_last_data;
    public double fasting_min_sum;
    public double fasting_min_avg;

    public int flag_index;
    public int fasting_min_data_count;
    public int last_fasting_index;
    public double fasting_min_value;
    public double fasting_min_data_sum;
    public double fasting_min_data_avg;
    public double last_sf_data;
    public double max_point_data;

    @Override
    public String toString() {
        return "CalBaseLineContext{" +
                "fasting_continue_count=" + fasting_continue_count +
                ", fasting_min_data=" + fasting_min_data +
                ", last_fasting_min_data=" + last_fasting_min_data +
                ", temp_fasting_min_index=" + temp_fasting_min_index +
                ", last_fasting_min_index=" + last_fasting_min_index +
                ", fasting_max_index=" + fasting_max_index +
                ", fasting_min_index=" + fasting_min_index +
                ", fasting_max_data=" + fasting_max_data +
                ", fasting_continue_count_sum=" + fasting_continue_count_sum +
                ", fasting_continue_count_avg=" + fasting_continue_count_avg +
                ", fasting_continue_data_sum=" + fasting_continue_data_sum +
                ", fasting_continue_data_avg=" + fasting_continue_data_avg +
                ", fasting_count=" + fasting_count +
                ", last_trend_data_count=" + last_trend_data_count +
                ", temp_mean_baseline=" + temp_mean_baseline +
                ", baseline_value=" + baseline_value +
                ", last_baseline_value=" + last_baseline_value +
                ", last_last_baseline_value=" + last_last_baseline_value +
                ", last_data=" + last_data +
                ", last_last_data=" + last_last_data +
                ", fasting_min_sum=" + fasting_min_sum +
                ", fasting_min_avg=" + fasting_min_avg +
                ", flag_index=" + flag_index +
                ", fasting_min_data_count=" + fasting_min_data_count +
                ", last_fasting_index=" + last_fasting_index +
                ", fasting_min_value=" + fasting_min_value +
                ", fasting_min_data_sum=" + fasting_min_data_sum +
                ", fasting_min_data_avg=" + fasting_min_data_avg +
                ", last_sf_data=" + last_sf_data +
                ", max_point_data=" + max_point_data +
                '}';
    }

}



