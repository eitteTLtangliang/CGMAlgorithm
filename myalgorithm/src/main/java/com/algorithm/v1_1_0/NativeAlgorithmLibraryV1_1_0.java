package com.algorithm.v1_1_0;

public final class NativeAlgorithmLibraryV1_1_0 {

    static {
        System.loadLibrary("native-algorithm-v1_1_0");
    }

    /**
     * 获取算法版本信息
     * @return 算法版本信息
     */
    public static native String getAlgorithmVersion();

    /**
     * 获取AlgorithmClassContext对象，第一次使用 由底层创建
     * 中途使用过程 其对象的成员属性值即为算法中间值
     * @return AlgorithmClassContext对象
     */
    public static native AlgorithmClassContext getAlgorithmContextFromNative();

    /**
     * 重置AlgorithmClassContext对象，即对算法中间值重置。
     * @param mAlgorithmContext AlgorithmClassContext对象
     */
    public static native void resetAlgorithmContext(AlgorithmClassContext mAlgorithmContext);

    /**
     * 免校准血糖算法执行
     * @param mAlgorithmContext AlgorithmClassContext对象
     * @param index 血糖笔数
     * @param current_data 电流值
     * @param temperature_data 温度值
     * @param lowAlarmValue 低血糖报警阙值
     * @param highAlarmValue 高血糖报警阙值
     * @return 血糖值
     */
    public static native double processAlgorithmConvert(AlgorithmClassContext mAlgorithmContext, int index, double current_data, double temperature_data, double lowAlarmValue, double highAlarmValue);

    /**
     * AlgorithmContext对象转json
     * @param mAlgorithmContext AlgorithmContext对象
     * @return 转化后的json字符串
     */
    public static native String getJsonAlgorithmContext(AlgorithmClassContext mAlgorithmContext);

    /**
     * 输入最近使用的json字符串
     * @param mAlgorithmContext AlgorithmContext对象
     * @param mJsonContext json字符串
     * @return 状态值 -1.成功  0.失败
     */
    public static native int setJsonAlgorithmContext(AlgorithmClassContext mAlgorithmContext,String mJsonContext);

    /**
     * 滤波算法，使曲线变得圆滑。
     * @param agp 原始数据。
     * @return 滤波后的数据。
     */
    public static native float[] getAGPFunction(float agp[]);

    /**
     * AGP暴露量计算
     * @param agpData 中位数
     * @return 暴露量大小
     */
    public static native float getGEFunction(float []agpData);

    /**
     * 计算十分位距
     * @param agpData10 十分位下限
     * @param agpData90 十分位上限
     * @return 十分位距
     */
    public static native float getIDRFunction(float []agpData10, float []agpData90);

    /**
     * 计算AGP四分位距
     * @param agpData25 四分位下限
     * @param agpData75 四分位上限
     * @return 四分位距
     */
    public static native float getIQRFunction(float []agpData25, float []agpData75);

    /**
     * AGP稳定性计算
     * @param agpData 中位数
     * @return 稳定性大小
     */
    public static native float getCMFunction(float []agpData);

    /**
     * 计算AGP低血糖风险
     * @param agpData 十分位下限
     * @param defaultLow 低血糖阙值
     * @return 低血糖风险大小
     */
    public static native float getLBGRFunction(float []agpData, float defaultLow);

    /**
     * 计算AGP高血糖风险
     * @param agp_data 十分位上限
     * @param defaultHigh 高血糖阙值
     * @return 高血糖风险大小
     */
    public static native float getHBGRFunction(float []agp_data, float defaultHigh);

}
