package com.algorithm.v1_1_0;

import java.io.Serializable;
import java.util.Arrays;

public final class RegularDeconvolutionContext implements Serializable {

    public double[] ig_value_buf;

    @Override
    public String toString() {
        return "RegularDeconvolutionContext{"+
                "\n ig_value_buf=" + Arrays.toString(ig_value_buf) +
                "}";
    }

}


