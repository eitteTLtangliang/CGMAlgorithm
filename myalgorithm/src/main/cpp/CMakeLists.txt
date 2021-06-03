# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# 这一句用来导出编译生成的so库
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/jniLibs/${ANDROID_ABI})

# Declares and names the project.

#project("myapplication")

include_directories(
		src/main/cpp
		src/main/cpp/algorithm/header
)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
		native-algorithm-v1_1_0

		# Sets the library as a shared library.
		SHARED

		# Provides a relative path to your source file(s).
		native_lib.h
		native_lib.cpp

		algorithm/source/native_current_judgment_context.c
        algorithm/source/native_abnormal_judgment_context.c
		algorithm/source/native_kalman_context.c
		algorithm/source/native_temperature_compensation_context.c
		algorithm/source/native_abnormal_value_correction_context.c
		algorithm/source/native_least_square_linear_fit_context.c
		algorithm/source/native_esa_compensate_context.c
		algorithm/source/native_filter_context.c
		algorithm/source/native_cal_baseline_context.c
		algorithm/source/native_clipping_filter_context.c
		algorithm/source/native_cgm_calibration_context.c
		algorithm/source/native_regular_deconvolution_context.c
		algorithm/source/native_arrow_direction_context.c


		algorithm/source/native_blood_glucose_index.cpp

        native_algorithm_class.cpp
		algorithm/source/cgm_algorithm.c

		struct2json/cJSON/cJSON.c
		struct2json/cJSON/cJSON_Utils.c
		struct2json/src/s2j.c
		struct2json/algorithmContext2Json.cpp

		)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
		log-lib

		# Specifies the name of the NDK library that
		# you want CMake to locate.
		log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
		native-algorithm-v1_1_0

		# Links the target library to the log library
		# included in the NDK.
		${log-lib} )