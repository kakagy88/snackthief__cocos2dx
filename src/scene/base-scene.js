scene.BaseScene = (function() {
  'use strict';

  var BaseScene = cc.Scene.extend({
    _apiCache : new Map(),
    ctor : function(param) {
      this._super();

      this._param = (param != null) ? param : {};

      // 変数関連
      this._comebackFromOtherScene = false;
      this._ccsData = null;

      // View関連
      this._sceneNode = cc.Node.create();
      this._layoutNode = cc.Node.create();
      this._dialogNode = cc.Node.create();
      this._headerLayout = null;
      this._footerLayout = null;
      this._blackPanel = null;
    },
    onEnter : function() {
      this._super();

      // 各Nodeを表示順に追加
      this.addChild(this._sceneNode);
      this.addChild(this._layoutNode);
      this.addChild(this._dialogNode);

      // タッチイベントの追加
      cc.eventManager.addListener({
        event : cc.EventListener.TOUCH_ONE_BY_ONE,
        swallowTouches : false,
        onTouchBegan : this._onTouchBegan.bind(this),
        onTouchMoved : this._onTouchMoved.bind(this),
        onTouchEnded : this._onTouchEnded.bind(this)
      }, this);

      // デバッグ情報表示
      this._updateSceneStackDebug();

      // キーイベント
      this._keyListener = {
        event : cc.EventListener.KEYBOARD,
        onKeyPressed : function(keyCode, event) {
          // F5でリロード
          if (keyCode === 116) {
            this._reload();
          }
        }.bind(this)
      };
      cc.eventManager.addListener(this._keyListener, this);
    },
    // onExit : function() {
    //   this._super();
    //   cc.eventManager.removeAllListeners();
    //   // cc.eventManager.removeListener(this._keyListener);
    // },
    _loadScene : function(jsonPath) {
      this._ccsData = ccs.load(jsonPath);
      this._ccsData.node.runAction(this._ccsData.action);
      this._sceneNode.addChild(this._ccsData.node);
      if (this._views == null) {
        this._views = {};
      }
      util.view.injectViewsAndListeners(this._views, this, this._ccsData.node);
    },
    _reload : function() {
      util.scene.reloadScene();
    },
    _updateSceneStackDebug : function() {
      if (setting.SHOW_SCENE_STACK === true) {
        var textFieldDebug = new ccui.Text();
        textFieldDebug.setFontSize(24);
        textFieldDebug.setName('textSceneStack');
        textFieldDebug.setColor(cc.color.WHITE);
        textFieldDebug.enableOutline(cc.color.GRAY, 3);
        textFieldDebug.setString(util.scene.getStackInfoText());
        textFieldDebug.setAnchorPoint(1, 1);
        textFieldDebug.setPosition(640, 1136);
        this.addChild(textFieldDebug);
      }
    },
    _callApi : function(api, param, useCache) {
      cc.log('callApi : ' + api.path);
      cc.assert(this._onApiComplete != null, 'Sceneクラスで_onApiComplete関数を定義してください。');

      // キャッシュ使用の場合はキャッシュの存在を確認
      if (useCache) {
        var response = this._apiCache.get(api);
        if (response != null) {
          this._onApiComplete(api, response);
          return;
        }
      }

      var callApiPararm = {
        method : api.method,
        path : api.path,
        param : param,
        onSuccess : response => {
          this._hideLoading();

          // キャッシュ対応APIはキャッシュに保存
          if (api.cacheable) {
            this._apiCache.set(api, response);
          }

          // 非同期処理を積む
          var promises = [];

          // シーンへの通知
          promises.push(() => {
            return new Promise((resolve, reject) => {
              this._onApiComplete(api, response);
              resolve();
            });
          });

          // 非同期処理を直列実行
          // reduceを使ったPromiseの直列実行については http://qiita.com/berlysia/items/3aeb1f0ab2494de9e24e
          var firstPromise = promises.shift();
          promises.reduce((m, p) => m.then(p), firstPromise());

        },
        onError : err => {
          this._hideLoading();
          this._showMessageDialog(
            'エラー',
            'サーバでの処理中にエラーが発生しました。\nタイトル画面に戻ります。',
            () => {
              util.scene.clearStack();
              util.scene.pushScene(scene.TitleScene);
            });
        },
        onConnectionError : err => {
          this._hideLoading();
          this._showMessageDialog(
            'エラー',
            'サーバとの接続に失敗しました。\nタイトル画面に戻ります。',
            () => {
              util.scene.clearStack();
              util.scene.pushScene(scene.TitleScene);
            });
        }
      };
      this._showLoading();
      util.network.callApi(callApiPararm);
    },
    _showLoading : function() {
      var layer = ccs.load(res.LoadingDialog);

      // タッチを吸収して、下のレイヤーのボタンを押したりできなくするためにLayoutをかます。
      var layout = new ccui.Layout();
      layout.setPosition(0, 0);
      layout.setContentSize(1136, 640);
      layout.setTouchEnabled(true);
      layout.setName('__loadingLayout__');
      layout.addChild(layer.node);

      this._dialogNode.addChild(layout);
      layer.node.runAction(layer.action);
      layer.action.play('animation0', true);
    },
    _hideLoading : function() {
      var layout = this._dialogNode.getChildByName('__loadingLayout__');
      cc.assert(layout !== null, 'ローディングが表示されていない状態でhideLoadingを呼んでいる可能性があります。');
      if (layout !== null) {
        // TODO:これで本当に全て削除されるのか。
        layout.removeFromParent();
      }
    },
    _showMessageDialog : function(title, message, callback) {
      this.addChild(new dialog.MessageDialog(title, message, callback));
    },
    _showYesNoDialog : function(title, message, callbackYes, callbackNo) {
      this.addChild(new dialog.YesNoDialog(title, message, callbackYes, callbackNo));
    },
    _showScene : function() {
      this._sceneNode.setVisible(true);
      this._layoutNode.setVisible(true);
    },
    _hideScene : function() {
      this._sceneNode.setVisible(false);
      this._layoutNode.setVisible(false);
    },
    _onApiComplete : function(api, response) {
      switch (api) {
      case Api.RANDOM_USER_ID:
        util.scene.clearStack();
        util.scene.replaceScene(scene.OtherScene, { userId : response.userId });
        break;
      }
    },
    _onTouchBegan : function(touch, event) {
      return true;
    },
    _onTouchMoved : function(touch, event) {
    },
    _onTouchEnded : function(touch, event) {
    }
  });
  return BaseScene;
})();
