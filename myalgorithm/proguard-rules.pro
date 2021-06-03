# Add project specific ProGuard rules here.
# You can control the set of applied configuration files using the
# proguardFiles setting in build.gradle.
#
# For more details, see
#   http://developer.android.com/guide/developing/tools/proguard.html

# If your project uses WebView with JS, uncomment the following
# and specify the fully qualified class name to the JavaScript interface
# class:
#-keepclassmembers class fqcn.of.javascript.interface.for.webview {
#   public *;
#}

# Uncomment this to preserve the line number information for
# debugging stack traces.
#-keepattributes SourceFile,LineNumberTable

# If you keep the line number information, uncomment this to
# hide the original source file name.
#-renamesourcefileattribute SourceFile

#################################以下是自己添加的混淆协议###################################
#下面代码中的路径配置,你要修改成与你相对应的路径
#引入依赖包rt.jar（jdk路径）(注意：如在makeJar的时候提示指定了两次，可以将其注释掉)
-libraryjars 'C:\Program Files\Java\jdk1.8.0_181\jre\lib\rt.jar'
#引入依赖包android.jar(android SDK路径)(注意：如在makeJar的时候提示指定了两次，可以将其注释掉)
#-libraryjars 'C:\Android_Develop_Tools\sdk\platforms\android-27\android.jar'

#忽略警告
-ignorewarnings
#保证是独立的jar,没有任何项目引用,如果不写就会认为我们所有的代码是无用的,从而把所有的代码压缩掉,导出一个空的jar
#-dontshrink
#保护泛型
-keepattributes Signature
#指定代码的压缩级别
-optimizationpasses 5
#包明不混合大小写
-dontusemixedcaseclassnames
#不去忽略非公共的库类
-dontskipnonpubliclibraryclasses
 #优化  不优化输入的类文件
-dontoptimize
 #预校验
-dontpreverify
 #混淆时是否记录日志
-verbose
 # 混淆时所采用的算法
-optimizations !code/simplification/arithmetic,!field/*,!class/merging/*

-keep class com.algorithm.v1_1_0.AlgorithmClassContext{
    public *;
}
-keep class com.algorithm.v1_1_0.JudgmentContext{
    public *;
}
-keep class com.algorithm.v1_1_0.JudgmentContext$CurrentJudgmentContext{
    public *;
}
-keep class com.algorithm.v1_1_0.AbnormalValueCorrectionContext{
    public *;
}

-keep class com.algorithm.v1_1_0.KalmanContext{
    public *;
}

-keep class com.algorithm.v1_1_0.FilterContext{
    public *;
}

-keep class com.algorithm.v1_1_0.CalBaseLineContext{
    public *;
}

-keep class com.algorithm.v1_1_0.ClippingFilterContext{
    public *;
}

-keep class com.algorithm.v1_1_0.EsaCompensateContext{
    public *;
}

-keep class com.algorithm.v1_1_0.RegularDeconvolutionContext{
    public *;
}

-keep class com.algorithm.v1_1_0.CGMCalibrationContext{
    public *;
}

-keep class com.algorithm.v1_1_0.ArrowDirectionContext{
    public *;
}
-keep class com.algorithm.v1_1_0.NativeAlgorithmLibraryV1_1_0{
    public *;
}

###### uitls  ########
-keep class com.algorithm.v1_1_0.utils.FileHelper{
    public *;
}
-keep class com.algorithm.v1_1_0.utils.JTest{
    public *;
}

-keep public interface com.algorithm.v1_1_0.utils.JTest$Callback{ *; }

-keep class com.algorithm.v1_1_0.utils.LogUtil{
    public *;
}



