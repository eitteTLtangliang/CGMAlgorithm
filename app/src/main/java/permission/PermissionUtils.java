package permission;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;

/**
 * projectName: sibionicsCGM
 * packageName: com.sibionics.sibblelibrary.permission
 * author: tanLiang
 * Date: 2019/7/18  10:42
 * Description:
 **/
public final class PermissionUtils {

    private PermissionUtils(){}

    public static boolean hasCameraPermission(Context context) {
        return hasCameraP(context);
    }

    private static boolean hasCameraP(Context context) {
        int res = context.checkCallingOrSelfPermission(Manifest.permission.CAMERA);
        return (res == PackageManager.PERMISSION_GRANTED);
    }

    public static boolean hasLocationPermissions(Context context) {
        return hasLocationP(context);
    }

    private static boolean hasLocationP(Context context) {
        int res1 = context.checkCallingOrSelfPermission(Manifest.permission.ACCESS_COARSE_LOCATION);
        int res2 = context.checkCallingOrSelfPermission(Manifest.permission.ACCESS_FINE_LOCATION);
        return (res1 == PackageManager.PERMISSION_GRANTED && res2 == PackageManager.PERMISSION_GRANTED);
    }

    public static boolean hasStoragePermission(Context context) {
        return hasStorageP(context);
    }

    private static boolean hasStorageP(Context context) {
        int res1 = context.checkCallingOrSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE);
        int res2 = context.checkCallingOrSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE);
        return (res1 == PackageManager.PERMISSION_GRANTED && res2 == PackageManager.PERMISSION_GRANTED);
    }

}
