dialog.MessageDialog = (function() {
  'use strict';

  // ダイアログ
  var MessageDialog = dialog.BaseDialog.extend({
    ctor : function(title, message, callback) {
      this._super();

      this._title = title;
      this._message = message;
      this._callback = callback;
      this.setCancelCallback(callback);

      this._views = {
        labelTitle : null,
        labelMessage : null
      };
    },
    onEnter : function() {
      this._super();

      this._loadDialog(res.MessageDialog);

      this._views.labelTitle.setString(this._title);
      this._views.labelMessage.setString(this._message);
    },
    _onClickButtonOk : function() {
      if (this._callback != null) {
        this._callback();
      }
      this.dismiss();
    }
  });
  return MessageDialog;
}());
