dialog.YesNoDialog = (function() {
  'use strict';

  // ダイアログ
  var YesNoDialog = dialog.BaseDialog.extend({
    ctor : function(title, message, callbackYes, callbackNo) {
      this._super();

      this._title = title;
      this._message = message;
      this._callbackYes = callbackYes;
      this._callbackNo = callbackNo;
      this.setCancelCallback(callbackNo);

      this._views = {
        labelTitle : null,
        labelMessage : null
      };
    },
    onEnter : function() {
      this._super();

      this._loadDialog(res.YesNoDialog);

      this._views.labelTitle.setString(this._title);
      this._views.labelMessage.setString(this._message);
    },
    _onClickButtonYes : function() {
      if (this._callbackYes != null) {
        this._callbackYes();
      }
      this.dismiss();
    },
    _onClickButtonNo : function() {
      if (this._callbackNo != null) {
        this._callbackNo();
      }
      this.dismiss();
    }
  });
  return YesNoDialog;
}());
