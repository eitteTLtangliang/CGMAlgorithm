package permission;

import java.util.List;

/**
 * projectName: SibionicsCGM
 * packageName: com.sibionics.sibblelibrary.permission
 * author: tanLiang
 * Date: 2019/5/24  15:58
 * Description:
 **/
public abstract class CheckCallback {

    public CheckCallback() {
    }

    public abstract void onAllGranted();

    public void onDenied(List<String> deniedWithNextAskList, List<String> deniedWithNoAskList) {
    }

}
