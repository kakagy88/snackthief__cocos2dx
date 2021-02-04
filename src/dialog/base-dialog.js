dialog.BaseDialog = (function() {
  'use strict';
  var BaseDialog = cc.Node.extend({
    ctor : function() {
      this._super();

      this._cancelCallback = null;
      this._ccsData = null;
    },
    _loadDialog : function(jsonPath, fullScreen) {
      fullScreen = (fullScreen != null) ? fullScreen : true;
      // フルスクリーン指定の場合は背面に半透明のボタンを設置
      if (fullScreen) {
        var button = ccui.Button.create('res/images/ui/common/dot_black.png');
        button.setAnchorPoint(0, 0);
        button.setContentSize(1136, 640);
        button.setOpacity(128);
        button.setScale9Enabled(true);
        button.addTouchEventListener((sender, type) => {
          if (type === ccui.Widget.TOUCH_ENDED) {
            // 押されたときは_cancelCallback関数を呼んで消えます
            if (this._cancelCallback != null) {
              if (this._cancelCallback()) {
                return;
              }
            }
            this.dismiss();
          }
        });
        this.addChild(button);
      }

      this._ccsData = ccs.load(jsonPath);
      this.addChild(this._ccsData.node);
      this._ccsData.node.runAction(this._ccsData.action);

      util.view.injectViewsAndListeners(this._views, this, this._ccsData.node);
    },
    // 背景をタップしたときのコールバックを設定
    setCancelCallback : function(cancelCallback) {
      this._cancelCallback = cancelCallback;
    },
    playAnimation : function(name, loop) {
      this._ccsData.action.play(name, loop);
    },
    dismiss : function() {
      this.removeFromParent();
    }
  });
  return BaseDialog;
})();
