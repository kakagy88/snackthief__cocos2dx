package jp.united.app.snackthief;

import android.util.Log;

import com.google.firebase.iid.FirebaseInstanceId;
import com.google.firebase.iid.FirebaseInstanceIdService;

import org.cocos2dx.lib.Cocos2dxLocalStorage;

public class MyInstanceIDListenerService extends FirebaseInstanceIdService {

    private static final String TAG = MyInstanceIDListenerService.class.getSimpleName();

    @Override
    public void onTokenRefresh() {
        // TODO:ここで取得したInstanceIDをサーバー管理者に伝える

        String refreshedToken = FirebaseInstanceId.getInstance().getToken();
        Log.d(TAG, "Refreshed token: " + refreshedToken);
        // JniBridge.callOnReceiveDeviceToken(refreshedToken);
        Cocos2dxLocalStorage.setItem("deviceToken", refreshedToken);
    }
}