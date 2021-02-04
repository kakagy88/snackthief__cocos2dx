/* eslint new-cap: "off" */

(function() {
  'use strict';

  var scene = {
    _sceneStack : [],
    pushScene : function(cls, param) {
      var scene = new cls(param, true);
      this._sceneStack.push({
        cls : cls,
        param : param,
        className : scene._className
      });
      cc.director.runScene(cc.TransitionFade.create(0.3, scene));
    },
    pushSceneWithoutRun : function(cls, param) {
      this._sceneStack.push({
        cls : cls,
        param : param,
        className : 'unknown'
      });
    },
    replaceScene : function(cls, param) {
      this._sceneStack.pop();
      var scene = new cls(param, true);
      this._sceneStack.push({
        cls : cls,
        param : param,
        className : scene._className
      });
      cc.director.runScene(cc.TransitionFade.create(0.3, scene));
    },
    popScene : function(result) {
      cc.assert(this._sceneStack.length >= 2);
      var ended = this._sceneStack.pop();
      var previous = this._sceneStack[this._sceneStack.length - 1];
      var scene = new previous.cls(previous.param);
      cc.director.runScene(cc.TransitionFade.create(0.3, scene));
      if (scene.onResult != null) {
        scene.onResult(ended.cls, result);
      }
    },
    popSceneWithoutRun : function() {
      cc.assert(this._sceneStack.length >= 2);
      this._sceneStack.pop();
    },
    reloadScene : function() {
      var current = this._sceneStack[this._sceneStack.length - 1];
      cc.director.runScene(new current.cls(current.param, true));
    },
    clearStack : function() {
      this._sceneStack.length = 0;
    },
    getStackInfoText : function() {
      var ret = this._sceneStack
        .map(stack => stack.className)
        .reduce((lhs, rhs) => lhs + '\n' + rhs);
      return ret;
    }
  };
  util.scene = scene;
})();
