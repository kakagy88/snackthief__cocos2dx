scene.GameClearScene = (function() {
  'use strict';

  var GameClearScene = scene.BaseScene.extend({
    _className : 'GameClearScene',
    ctor : function(param) {
      this._super(param);
      this._views = {
        labelTime : null
      };
    },
    onEnter : function() {
      this._super();
      this._loadScene(res.GameClearScene);
      this._views.labelTime.setString('Time : ' + this._param.time.toFixed(1));

      var bgm = cc.audioEngine;
      bgm.playMusic('res/bgm/trumpet2.mp3', false);

      // アニメーション再生
      this._ccsData.action.play('gameclear', false);

    },

    _onClickButtonTap : function(index) {
      cc.audioEngine.playEffect('res/se/se_tap.mp3', false);
      util.scene.pushScene(scene.DifficultyScene, {
      });
    }
  });
  return GameClearScene;
})();

