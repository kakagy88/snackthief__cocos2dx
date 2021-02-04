// Web側はダミー実装

cc.LWF = function() {
  this.fitForHeight = function() {};
};

cc.LWFNode = cc.Sprite.extend({
  ctor : function() {
    this._super();
    this.setTexture('res/lwf/logo.png');
    this.lwf = new cc.LWF();
  }
});

cc.LWFNode.create = function() {
  return new cc.LWFNode();
};
