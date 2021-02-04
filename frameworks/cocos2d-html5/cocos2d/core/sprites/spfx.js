// Web側はダミー実装

cc.SPFXManager = cc.Layer.extend({});

cc.SPFXManager.create = function() {
  return new cc.SPFXManager();
};

cc.SPFXNode = cc.Sprite.extend({
  ctor : function() {
    this._super();
  },
  play : function() {
  }
});

cc.SPFXNode.create = function() {
  return new cc.SPFXNode();
};
