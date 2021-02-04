scene.TitleScene = (function() {
  'use strict';

  var TitleScene = scene.BaseScene.extend({
    _className : 'TitleScene',
    ctor : function(param) {
      this._super(param);
    },
    onEnter : function() {
      this._super();
      this._loadScene(res.TitleScene);

      var bgm = cc.audioEngine;
      bgm.playMusic('res/bgm/park2.mp3', false);

      // アニメーション再生
      this._ccsData.action.play('wait', true);
    },
    _onClickButtonTap : function(index) {
      util.scene.replaceScene(scene.DifficultyScene);
    }
  });
  return TitleScene;
})();