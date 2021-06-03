package permission;

import android.app.Activity;
import android.app.FragmentManager;

/**
 * projectName: SibionicsCGM
 * packageName: com.sibionics.sibblelibrary.permission
 * author: tanLiang
 * Date: 2019/5/24  16:00
 * Description:
 **/
public class PermissionManager {

    private CheckFragment checkFragment;
    private String[] permissions;

    private PermissionManager(Activity activity) {
        permissionM(activity);
    }

    private void permissionM(Activity activity) {
        if(this.checkFragment == null) {
            this.checkFragment = (CheckFragment)activity.getFragmentManager().findFragmentByTag("PermissionManager");
            if(this.checkFragment == null) {
                this.checkFragment = new CheckFragment();
                FragmentManager fragmentManager = activity.getFragmentManager();
                fragmentManager.beginTransaction().add(this.checkFragment, "PermissionManager").commitAllowingStateLoss();
                fragmentManager.executePendingTransactions();
            }
        }
    }

    public static PermissionManager with(Activity activity) {
        return new PermissionManager(activity);
    }

    public PermissionManager permissions(String... permissions) {
        if(permissions != null && permissions.length != 0) {
            this.permissions = permissions;
            return this;
        } else {
            throw new IllegalArgumentException("PermissionManager requires at least one input permission");
        }
    }

    public boolean check() {
        return this.checkFragment != null ? this.checkFragment.check(this.permissions):false;
    }

    public void request(CheckCallback checkCallback) {
        if(this.checkFragment != null) {
            this.checkFragment.setCheckCallback(checkCallback);
            this.checkFragment.checkAndRequest(this.permissions);
        }
    }

}
