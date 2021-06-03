package com.example.mymodulesapp;

import android.Manifest;
import android.os.Bundle;
import android.os.Environment;
import android.text.TextUtils;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.algorithm.v1_1_0.AlgorithmClassContext;
import com.algorithm.v1_1_0.NativeAlgorithmLibraryV1_1_0;
import com.algorithm.v1_1_0.utils.FileHelper;
import com.algorithm.v1_1_0.utils.JTest;
import com.algorithm.v1_1_0.utils.LogUtil;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import permission.CheckCallback;
import permission.PermissionManager;

public class MainActivity extends AppCompatActivity {

    private AlgorithmClassContext mAlgorithmContext;

    private double raw_currents[] = {17.3, 12.7, 6.4, 4.5, 4.7, 5.4,
            6.1, 6.5, 7.0, 7.2, 7.4, 7.5, 7.9, 8.2, 8.4, 8.4, 8.5, 8.5,
            8.5, 8.5, 8.6, 8.9, 8.9, 8.8, 8.6, 8.7, 8.7, 8.7, 8.7,
            8.7, 8.6, 8.6, 8.6, 8.5, 8.4, 8.4, 8.3, 8.3, 8.3,};

    private double raw_temperature[] = {
            22.1, 22.8, 23.4, 23.9, 24.3, 24.6, 24.7, 24.8, 24.9, 25.1, 25.1,
            25.2, 25.4, 25.4, 25.4, 25.4, 25.5, 25.4, 25.4, 25.5, 25.5, 25.4,
            25.3, 25.3, 25.4, 25.4, 25.5, 25.6, 25.6, 25.7, 25.6, 25.7,
            25.7, 25.7, 25.7, 25.8, 25.8, 25.7, 25.7};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        PermissionManager.with(this).permissions(Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.READ_EXTERNAL_STORAGE).request(new CheckCallback() {
            @Override
            public void onAllGranted() {
                //new Thread(() -> testFile()).start();

                test();
            }
        });




    }

    private void test(){
        try {
            TextView tv = findViewById(R.id.sample_text);
            tv.setText(NativeAlgorithmLibraryV1_1_0.getAlgorithmVersion());
            mAlgorithmContext = NativeAlgorithmLibraryV1_1_0.getAlgorithmContextFromNative();
            mAlgorithmContext.mCurrentCorrectionContext.mS  = 1.343;

            for(int i = 0; i < 35; i++) {
                double glucoseValue = NativeAlgorithmLibraryV1_1_0.processAlgorithmConvert(mAlgorithmContext, i, raw_currents[i], raw_temperature[i], 3.9f, 7.8f);
                LogUtil.i("index=" + (i+1) + ", current=" + raw_currents[i] + ", glucoseValue=" + glucoseValue);

            }
            String json = NativeAlgorithmLibraryV1_1_0.getJsonAlgorithmContext(mAlgorithmContext);
            saveStringToFile(json);

        }catch (Exception e){
            e.printStackTrace();
        }
    }

    public static void saveStringToFile(String toSaveString){
        String filePath = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "CGM_TEST" + File.separator  + "test.txt";
        if (TextUtils.isEmpty(toSaveString) || TextUtils.isEmpty(filePath)) return;
        try{
            File saveFile = new File(filePath);
            if (!saveFile.exists()){
                File dir = new File(saveFile.getParent());
                dir.mkdirs();
                saveFile.createNewFile();
            }
            FileOutputStream outStream = new FileOutputStream(saveFile, true);
            outStream.write("\n".getBytes());
            outStream.flush();
            outStream.write(toSaveString.getBytes());
            outStream.flush();
            outStream.close();
        } catch (FileNotFoundException e){
            e.printStackTrace();
        } catch (IOException e){
            e.printStackTrace();
        }
    }

    private void testFile() {
        try {
            Thread.sleep(50);

            String version = NativeAlgorithmLibraryV1_1_0.getAlgorithmVersion();
            LogUtil.i("version-->"+version);

            mAlgorithmContext = NativeAlgorithmLibraryV1_1_0.getAlgorithmContextFromNative();

            //AlgorithmClassContext classContext = FileHelper.getAlgorithmObjFromFile(FileHelper.mPathname);
            //if (classContext != null) mAlgorithmContext = classContext;

            mAlgorithmContext.mCurrentCorrectionContext.mS = 1.487;

           JTest.loadData(FileHelper.mRootPath+ File.separator+"testDemo.txt", mAlgorithmContext, (index, currentValue, temperatureValue, cur_cgm_data) -> {

                LogUtil.e("index="+index+" ,currentValue=" + currentValue + " ,temperatureValue=" + temperatureValue + " ,cur_cgm_data=" + cur_cgm_data);
            }, 1, 500, 3.9f, 7.8f);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

}


