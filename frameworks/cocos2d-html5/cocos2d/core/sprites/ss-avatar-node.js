// Web側はダミー実装

cc.SsAvatarNode = cc.Node.extend({
  ctor : function() {
    this._super();

    var sprite = cc.Sprite.create('res/ss/icon.png');
    this.addChild(sprite);
  },
  attachEquipment : function(arg0, arg1) {},
  detachEquipment : function(arg0) {},
  setPose : function(arg0) {}
});

cc.SsAvatarNode.create = function() {
  return new cc.SsAvatarNode();
};

cc.SsAvatarNode.setSsDirectoryPath = function(arg0) {};

cc.SsAvatarNode.setSsUrl = function(arg0) {};