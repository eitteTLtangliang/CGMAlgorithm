package com.algorithm.v1_1_0;

import java.io.Serializable;

public final class ArrowDirectionContext implements Serializable {

    public int blood_glucose_trend;
    public int last_blood_glucose_trend;
    public double arrow_direction_data;
    public double last_arrow_direction_data;
    public double last_last_arrow_direction_data;
    public int rise_trend_count;
    public int decline_trend_count;
    public int horizontal_direction_count;
    public int arrow_direction_count;

    @Override
    public String toString() {
        return "ArrowDirectionContext{"+
                "\n blood_glucose_trend=" + blood_glucose_trend +
                "\n last_blood_glucose_trend=" + last_blood_glucose_trend +
                "\n arrow_direction_data=" + arrow_direction_data +
                "\n last_arrow_direction_data=" + last_arrow_direction_data +
                "\n last_last_arrow_direction_data=" + last_last_arrow_direction_data +
                "\n rise_trend_count=" + rise_trend_count +
                "\n decline_trend_count=" + decline_trend_count +
                "\n horizontal_direction_count=" + horizontal_direction_count +
                "\n arrow_direction_count=" + arrow_direction_count +
                "}";
    }
}


