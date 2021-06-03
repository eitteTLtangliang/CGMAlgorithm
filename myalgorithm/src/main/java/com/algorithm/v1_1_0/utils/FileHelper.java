package com.algorithm.v1_1_0.utils;

import android.os.Environment;

import com.algorithm.v1_1_0.AlgorithmClassContext;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

/**
 * projectName: MyModulesApp
 * packageName: com.example.mymodulesapp
 * author: tanLiang
 * Date: 2021/5/26  15:53
 * Description:
 **/
public final class FileHelper {

    public final static String mRootPath = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "SiSensingCGM";
    public final static String mPathname = mRootPath + File.separator + "AlgorithmObj.txt";

    private FileHelper(){}

    public static void saveAlgorithmObjToFile(AlgorithmClassContext writeObject, String pathname){
        saveObjectToFile(writeObject, pathname);
    }

    public static AlgorithmClassContext getAlgorithmObjFromFile(String pathname){
        return getObjFromFile(pathname);
    }

    private static void saveObjectToFile(Object writeObject, String pathname){
        try {
            File file = new File(pathname);
            if (!file.exists()) file.createNewFile();
            ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(file));
            oos.writeObject(writeObject);
            oos.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static AlgorithmClassContext getObjFromFile(String pathname){
        try {
            File file = new File(pathname);

            if (!file.exists())  {
                file.createNewFile();
                return null;
            }

            if (file.length() == 0){
                return null;
            }

            FileInputStream fis = new FileInputStream(file);
            ObjectInputStream ois = new ObjectInputStream(fis);
            return (AlgorithmClassContext)ois.readObject();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

}
