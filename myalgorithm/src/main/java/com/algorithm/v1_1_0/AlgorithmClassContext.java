package com.algorithm.v1_1_0;

import java.io.Serializable;
import java.util.Arrays;

public final class AlgorithmClassContext implements Serializable {

    public int esa_calibration_enable;
    public int finger_blood_calibration_enable;
    public char [] version_name;
    public double IG_data;
    public double last_IG_data;

    public int cgm_warning;
    public int cgm_current_abnormal;
    public int cgm_temp_abnormal;
    public int cgm_blood_glucose_trend;
    public JudgmentContext mJudgmentContext;
    public AbnormalValueCorrectionContext mCurrentCorrectionContext;
    public KalmanContext mKalmanContext;
    public FilterContext mFilter1Context;
    public FilterContext mFilter2Context;
    public CalBaseLineContext mCalBaselineContext;
    public ClippingFilterContext mClippingFilterContext;
    public EsaCompensateContext mESACompensateContext;
    public RegularDeconvolutionContext mRegularDeconvolutionContext;
    public CGMCalibrationContext cgmCalibrationContext;
    public ArrowDirectionContext mArrowDirectionContext;

    @Override
    public String toString() {
        return "AlgorithmClassContext{" +
                "esa_calibration_enable=" + esa_calibration_enable +
                ", finger_blood_calibration_enable=" + finger_blood_calibration_enable +
                ", version_name=" + Arrays.toString(version_name) +
                ", IG_data=" + IG_data +
                ", last_IG_data=" + last_IG_data +
                ", cgm_warning=" + cgm_warning +
                ", cgm_current_abnormal=" + cgm_current_abnormal +
                ", cgm_temp_abnormal=" + cgm_temp_abnormal +
                ", cgm_blood_glucose_trend=" + cgm_blood_glucose_trend +
                ", mJudgmentContext=" + mJudgmentContext +
                ", mCurrentCorrectionContext=" + mCurrentCorrectionContext +
                ", mKalmanContext=" + mKalmanContext +
                ", mFilter1Context=" + mFilter1Context +
                ", mFilter2Context=" + mFilter2Context +
                ", mCalBaselineContext=" + mCalBaselineContext +
                ", mClippingFilterContext=" + mClippingFilterContext +
                ", mESACompensateContext=" + mESACompensateContext +
                ", mRegularDeconvolutionContext=" + mRegularDeconvolutionContext +
                ", cgmCalibrationContext=" + cgmCalibrationContext +
                ", mArrowDirectionContext=" + mArrowDirectionContext +
                '}';
    }
}


