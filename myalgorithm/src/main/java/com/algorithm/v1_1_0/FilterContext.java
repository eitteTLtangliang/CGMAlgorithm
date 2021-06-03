package com.algorithm.v1_1_0;

import java.io.Serializable;
import java.util.Arrays;

public final class FilterContext implements Serializable {

    public double[] m_filter_data;
    public double[] m_temp_data;
    public double [] m_a_data;
    public double [] m_b_data;

    @Override
    public String toString() {
        return "FilterContext{"+
                "\n m_filter_data=" + Arrays.toString(m_filter_data) +
                "\n m_temp_data=" + Arrays.toString(m_temp_data) +
                "\n m_a_data=" + Arrays.toString(m_a_data) +
                "\n m_b_data=" + Arrays.toString(m_b_data) +
                "}";
    }

}
