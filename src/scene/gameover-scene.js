scene.GameOverScene = (function() {
  'use strict';

  var GameOverScene = scene.BaseScene.extend({
    _className : 'GameOverScene',
    ctor : function(param) {
      this._super(param);
    },
    onEnter : function() {
      this._super();
      this._loadScene(res.GameOverScene);

      var bgm = cc.audioEngine;
      bgm.playMusic('res/bgm/crows1.mp3', false);
      cc.audioEngine.playEffect('res/bgm/gameover.mp3', false);
      // アニメーション再生
      this._ccsData.action.play('gameover', false);
    },

    _onClickButtonTap : function(index) {
      cc.audioEngine.playEffect('res/se/se_tap.mp3', false);
      util.scene.pushScene(scene.DifficultyScene, {
      });
    }
  });
  return GameOverScene;
})();

