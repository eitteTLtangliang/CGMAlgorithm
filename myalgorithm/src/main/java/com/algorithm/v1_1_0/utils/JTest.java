package com.algorithm.v1_1_0.utils;

import com.algorithm.v1_1_0.AlgorithmClassContext;
import com.algorithm.v1_1_0.NativeAlgorithmLibraryV1_1_0;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

/**
 * projectName: MyModulesApp
 * packageName: com.algorithm.v1_1_0.utils
 * author: tanLiang
 * Date: 2021/5/27  13:52
 * Description:
 **/
public final class JTest {

    public static void loadData(String pathname, AlgorithmClassContext mAlgorithmContext, Callback callback, int leftIndex, int rightIndex, float lowAlarm, float highAlarm) throws Exception{
        loadTxtData(pathname, mAlgorithmContext, callback, leftIndex, rightIndex, lowAlarm, highAlarm);
    }

    private static void loadTxtData(String pathname, AlgorithmClassContext mAlgorithmContext, Callback callback, int leftIndex, int rightIndex, float lowAlarm, float highAlarm) throws Exception{
        String result = "";
        File file = new File(pathname);
        BufferedReader br = new BufferedReader(new FileReader(file));
        String s = null;
        while((s = br.readLine()) != null) {
            result = result + "\n" + s;
            String[] split = s.split("\t");
            int index = Integer.parseInt(split[0]);
            float currentValue = Float.parseFloat(split[1]);
            float temperatureValue = Float.parseFloat(split[2]);
            float sens = Float.parseFloat(split[3]);
            float intercept = Float.parseFloat(split[4]);

            if (index >= leftIndex && index <= rightIndex){
                double cur_cgm_data = NativeAlgorithmLibraryV1_1_0.processAlgorithmConvert(mAlgorithmContext, index, currentValue, temperatureValue, lowAlarm, highAlarm);
                if (callback != null) callback.onLoad(index, currentValue, temperatureValue, cur_cgm_data);
                FileHelper.saveAlgorithmObjToFile(mAlgorithmContext, FileHelper.mPathname);
            }else break;

        }
        br.close();
    }

    public interface Callback{
        void onLoad(int index, float currentValue, float temperatureValue, double cur_cgm_data);
    }

}
