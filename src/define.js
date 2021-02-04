/* exported Api HttpMethod DifficultyType */

var Api = null;
var HttpMethod = null;
var DifficultyType = null;

(function() {
  'use strict';

  HttpMethod = {
    GET : 'GET',
    POST : 'POST',
    PUT : 'PUT',
    DELETE : 'DELETE'
  };

  Api = {
    LOGIN : {
      path : '/v1/account/login',
      method : HttpMethod.POST
    }
  };


  DifficultyType = {
    EASY : 0,
    NORMAL : 1,
    HARD : 2
  };


  // cc.Spriteを拡張。ネットワーク経由で画像を読み込む。
  cc.Sprite.prototype.loadFromUrl = function(url, callback) {
    if (cc.sys.isNative) {
      var loader = cc.NetworkImageLoader.getInstance();
      loader.loadTextureFromUrlASync(
        url,
        (tex) => {
          if (tex != null) {
            this.setTexture(tex);
            this.setTextureRect(cc.rect(0, 0, tex.getContentSize().width, tex.getContentSize().height));
          }
          if (callback != null) {
            callback('', tex);
          }
        }
      );
    } else {
      cc.loader.loadImg(url, (err, tex) => {
        if (err == null) {
          var texture2d = new cc.Texture2D();
          texture2d.initWithElement(tex);
          texture2d.handleLoadedTexture();
          this.setTexture(texture2d);
        }
        if (callback != null) {
          callback(err, tex);
        }
      });
    }
  };

  // NodeにViewComponent関連のコードを追加。
  cc.Node.prototype.getViewComponent = function() {
    return this.getComponent('viewComponent');
  };

  cc.Node.prototype.addViewComponent = function(component) {
    component.onEnter = component.setup;
    component.onAdd = component.setup;
    component.setName('viewComponent');
    this.addComponent(component);
  };

  // Arrayを拡張
  Array.prototype.shuffle = function() {
    for (var i = this.length - 1; i > 0; i--) {
      var r = Math.floor(Math.random() * (i + 1));
      var tmp = this[i];
      this[i] = this[r];
      this[r] = tmp;
    }
  };

  // ccui.Textを拡張。
  // FIXME:アプリがスリープに入ってscheduleが中断されたのちにに再開された場合に、カウントがおかしくなるので対策を考える。scheduleの引数のdtを利用できそう。
  ccui.Text.prototype.setTimeSec = function(timeSec) {
    this._timeMs = timeSec * 1000;
    this.setString(util.time.msToTimeString(this._timeMs));
  };
  ccui.Text.prototype.setTimeMs = function(timeMs) {
    this._timeMs = timeMs;
    this.setString(util.time.msToTimeString(this._timeMs));
  };
  ccui.Text.prototype.startCountDown = function() {
    this.unschedule(this._countScheduler);
    this.schedule(this._countScheduler, 1.0);
  },
  ccui.Text.prototype._countScheduler = function(dt) {
    if (this._timeMs <= 0) {
      this._timeMs = 0;
      this.unschedule(this._countScheduler);
    }
    this.setString(util.time.msToTimeString(this._timeMs));
    this._timeMs -= 1000;
  };

  // ccs.ActionTimelineを拡張。再生と同時にタイムライン名を保持しておく
  ccs.ActionTimeline.prototype.playTimeline = function(name, loop) {
    this.name = name;
    this.play(name, loop);
  };
})();
