package com.algorithm.v1_1_0;

import java.io.Serializable;

public final class KalmanContext implements Serializable {
    
    public double mStateKalman;
    public double mStatePre;
    public double mPminus;
    public double mK;
    public double mR;
    public double mQ;
    public double mP;

    @Override
    public String toString() {
        return "KalmanContext{" +
                "\n mStateKalman=" + mStateKalman +
                "\n mStatePre=" + mStatePre +
                "\n mPminus=" + mPminus +
                "\n mK=" + mK +
                "\n mR=" + mR +
                "\n mQ=" + mQ +
                "\n mP=" + mP +
                "}";
    }

}
