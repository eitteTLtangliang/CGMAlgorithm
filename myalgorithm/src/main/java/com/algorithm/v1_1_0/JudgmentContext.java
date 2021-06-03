package com.algorithm.v1_1_0;


import java.io.Serializable;
import java.util.Arrays;

public final class JudgmentContext implements Serializable {

    public double[] abnormal_flag_buf;
    public double current_abnormal_flag_count;
    public int abnormal_count;
    public CurrentJudgmentContext mCurrentJudgmentContext;

    public final class CurrentJudgmentContext implements Serializable{

        public double last_current;
        public double max_current;
        public int abnormal_flag;
        public int last_abnormal_flag;
        public double[] temp_data_buf;
        public double var_data;
        public int con_count;

        @Override
        public String toString() {

            return "CurrentJudgmentContext{" +
                    "\n last_current=" + last_current +
                    "\n max_current=" + max_current +
                    "\n abnormal_flag=" + abnormal_flag +
                    "\n last_abnormal_flag=" + last_abnormal_flag +
                    "\n temp_data_buf=" + Arrays.toString(temp_data_buf) +
                    "\n var_data=" + var_data +
                    "\n con_count=" + con_count +
                    "}";
        }
    }

    @Override
    public String toString() {

        return "JudgmentContext{"+
                "\n"+mCurrentJudgmentContext.toString()+
                "\n abnormal_flag_buf=" + Arrays.toString(abnormal_flag_buf) +
                "\n current_abnormal_flag_count=" + current_abnormal_flag_count +
                "\n abnormal_count=" + abnormal_count +
                "}";
    }

}
