package jp.united.app.snackthief;

import org.cocos2dx.lib.Cocos2dxActivity;

/**
 * Created by atsushi-ota on 2017/09/05.
 */

public class JniBridge {
    // C++関数
    public static native void onReceivePushNotification(String iconUrl, String message);
    public static native void onReceiveDeviceToken(String token);

    public static void callOnReceivePushNotification(final String iconUrl, final String message) {
        ((Cocos2dxActivity) Cocos2dxActivity.getContext()).runOnGLThread(new Runnable() {
            @Override
            public void run() {
                onReceivePushNotification(iconUrl, message);
            }
        });
    }
}
