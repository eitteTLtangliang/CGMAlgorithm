package permission;

import android.annotation.TargetApi;
import android.app.Fragment;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;

import androidx.annotation.RequiresApi;

import java.util.ArrayList;

/**
 * projectName: SibionicsCGM
 * packageName: com.sibionics.sibblelibrary.permission
 * author: tanLiang
 * Date: 2019/5/24  15:59
 * Description:
 **/
public final class CheckFragment extends Fragment {

    private static final int PERMISSIONS_REQUEST_CODE = 66;
    private CheckCallback checkCallback;

    public CheckFragment() {
    }

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.setRetainInstance(true);
    }

    @TargetApi(23)
    public boolean check(String[] permissions) {
        return checkP(permissions);
    }

    private boolean checkP(String[] permissions) {
        if(permissions != null && permissions.length != 0) {
            if(!this.isMarshmallow()) {
                Log.e("CheckFragment", "Android sdk < 23!");
                return true;
            } else {
                ArrayList permissionList = new ArrayList();
                String[] var3 = permissions;
                int var4 = permissions.length;
                for(int var5 = 0; var5 < var4; ++var5) {
                    String permission = var3[var5];
                    if(this.getActivity().checkSelfPermission(permission) != PackageManager.PERMISSION_GRANTED) {
                        permissionList.add(permission);
                    }
                }
                return permissionList.size() == 0;
            }
        } else {
            return true;
        }
    }

    @TargetApi(23)
    public void checkAndRequest(String[] permissions) {
        checkR(permissions);
    }

    private void checkR(String[] permissions) {
        if(permissions != null && permissions.length != 0) {
            if(!this.isMarshmallow()) {
                Log.e("CheckFragment", "Android sdk < 23!");
                if(this.checkCallback != null) {
                    this.checkCallback.onAllGranted();
                }
            } else {
                ArrayList permissionList = new ArrayList();
                String[] var3 = permissions;
                int var4 = permissions.length;
                for(int var5 = 0; var5 < var4; ++var5) {
                    String permission = var3[var5];
                    if(this.getActivity().checkSelfPermission(permission) != PackageManager.PERMISSION_GRANTED) {
                        permissionList.add(permission);
                    }
                }
                if(permissionList.size() > 0) {
                    this.requestPermissions((String[])permissionList.toArray(new String[permissionList.size()]), PERMISSIONS_REQUEST_CODE);
                } else if(this.checkCallback != null) {
                    this.checkCallback.onAllGranted();
                }
            }
        }
    }

    @TargetApi(23)
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        onR(requestCode, permissions, grantResults);
    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    private void onR(int requestCode, String[] permissions, int[] grantResults) {
        if(requestCode == PERMISSIONS_REQUEST_CODE) {
            boolean isAllGranted = true;
            ArrayList deniedWithNextAskList = new ArrayList();
            ArrayList deniedWithNoAskList = new ArrayList();
            for(int i = 0; i < grantResults.length; ++i) {
                if(grantResults[i] != 0) {
                    isAllGranted = false;
                    if(this.shouldShowRequestPermissionRationale(permissions[i])) {
                        deniedWithNextAskList.add(permissions[i]);
                    } else {
                        deniedWithNoAskList.add(permissions[i]);
                    }
                }
            }

            if(this.checkCallback != null) {
                if(isAllGranted) {
                    this.checkCallback.onAllGranted();
                } else {
                    this.checkCallback.onDenied(deniedWithNextAskList, deniedWithNoAskList);
                }
            }
        }
    }

    boolean isMarshmallow() {
        return Build.VERSION.SDK_INT >= 23;
    }

    public CheckCallback getCheckCallback() {
        return this.checkCallback;
    }

    public void setCheckCallback(CheckCallback checkCallback) {
        this.checkCallback = checkCallback;
    }

}
