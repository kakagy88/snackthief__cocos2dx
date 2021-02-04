(function() {
  'use strict';

  var network = {
    callApi : function(param) {
      cc.assert(param != null);
      cc.assert(param.method != null);
      cc.assert(param.path != null);

      var xhr = cc.loader.getXMLHttpRequest();
      xhr.timeout = 30000; // 30秒
      // GETではparamはクエリ
      if (param.param != null && param.method === 'GET') {
        var url = 'http://' + setting.API_HOST + ':' + setting.API_PORT + param.path;
        Object.keys(param.param).forEach((key, i) => {
          url += (i === 0 ? '?' : '&') + key + '=' + param.param[key];
        });
        xhr.open(param.method, url, true);
      } else {
        xhr.open(param.method, 'http://' + setting.API_HOST + ':' + setting.API_PORT + param.path, true);
      }
      xhr.withCredentials = true;
      if (param.headers != null) {
        Object.keys(param.headers).forEach(key => {
          xhr.setRequestHeader(key, param.headers[key]);
        });
      }
      // PUT、POSTではparamはjsonにして投げる
      if (param.param != null && (param.method === 'POST' || param.method === 'PUT')) {
        xhr.setRequestHeader('Content-Type', 'application/json');
      }
      xhr.onload = () => {
        if (xhr.status === 200) {
          var response = JSON.parse(xhr.response);
          // セッション切れチェック
          if (response.sessionExists === false) {
            var event = new cc.EventCustom('showMessageDialog');
            event.setUserData({
              title : 'エラー',
              message : 'セッションが無効です。タイトル画面に戻ります。',
              callback : () => {
                util.scene.clearStack();
                util.scene.pushScene(scene.TitleScene);
              }
            });
            cc.eventManager.dispatchEvent(event);

            return;
          }
          if (response.success === true) {
            if (param.onSuccess != null) {
              param.onSuccess(response);
            }
          } else {
            if (param.onError != null) {
              param.onError();
            }
          }
        } else {
          if (param.onConnectionError != null) {
            param.onConnectionError();
          }
        }
      };
      xhr.onerror = xhr.ontimeout = xhr.onabort = function(err) {
        if (param.onConnectionError != null) {
          param.onConnectionError(err);
        }
      };
      if (param.param != null) {
        xhr.send(JSON.stringify(param.param));
      } else {
        xhr.send();
      }
    }
  };
  util.network = network;
})();
