package com.algorithm.v1_1_0;

import java.io.Serializable;
import java.util.Arrays;

public final class AbnormalValueCorrectionContext implements Serializable {

    public double  mS;
    public double mLastS;
    public int mSFlag;
    public double mD0;
    public double mSs0;
    public double[] mTimeWindows;
    public double[] mTimeWindows1;

    @Override
    public String toString() {

        return "AbnormalValueCorrectionContext{"+
                "\n mS=" + mS +
                "\n mLastS=" + mLastS +
                "\n mSFlag=" + mSFlag +
                "\n mD0=" + mD0 +
                "\n mSs0=" + mSs0 +
                "\n mTimeWindows=" + Arrays.toString(mTimeWindows) +
                "\n mTimeWindows1=" + Arrays.toString(mTimeWindows1) +
                "}";
    }

}
