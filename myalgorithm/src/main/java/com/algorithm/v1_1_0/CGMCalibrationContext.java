package com.algorithm.v1_1_0;

import java.io.Serializable;

/**
 * projectName: MyModulesApp
 * packageName: com.algorithm.v1_1_0
 * author: tanLiang
 * Date: 2021/5/26  10:02
 * Description:
 **/
public final class CGMCalibrationContext implements Serializable {

    public int calibration_flag;  //为1 表示是空腹，为2表示上升沿，为3表示下降沿。
    public int bg_index;
    public double last_bg;
    public double last_sf4_data;
    public double last_last_sf4_data;


    @Override
    public String toString() {
        return "CGMCalibrationContext{" +
                "calibration_flag=" + calibration_flag +
                ", bg_index=" + bg_index +
                ", last_bg=" + last_bg +
                ", last_sf4_data=" + last_sf4_data +
                ", last_last_sf4_data=" + last_last_sf4_data +
                '}';
    }

}
