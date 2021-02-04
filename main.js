/* exported scene dialog layout util node setting */

/**
 * A brief explanation for "project.json":
 * Here is the content of project.json file, this is the global configuration for your game, you can modify it to customize some behavior.
 * The detail of each field is under it.
 {
    "project_type": "javascript",
    // "project_type" indicate the program language of your project, you can ignore this field

    "debugMode"     : 1,
    // "debugMode" possible values :
    //      0 - No message will be printed.
    //      1 - cc.error, cc.assert, cc.warn, cc.log will print in console.
    //      2 - cc.error, cc.assert, cc.warn will print in console.
    //      3 - cc.error, cc.assert will print in console.
    //      4 - cc.error, cc.assert, cc.warn, cc.log will print on canvas, available only on web.
    //      5 - cc.error, cc.assert, cc.warn will print on canvas, available only on web.
    //      6 - cc.error, cc.assert will print on canvas, available only on web.

    "showFPS"       : true,
    // Left bottom corner fps information will show when "showFPS" equals true, otherwise it will be hide.

    "frameRate"     : 60,
    // "frameRate" set the wanted frame rate for your game, but the real fps depends on your game implementation and the running environment.

    "noCache"       : false,
    // "noCache" set whether your resources will be loaded with a timestamp suffix in the url.
    // In this way, your resources will be force updated even if the browser holds a cache of it.
    // It's very useful for mobile browser debuging.

    "id"            : "gameCanvas",
    // "gameCanvas" sets the id of your canvas element on the web page, it's useful only on web.

    "renderMode"    : 0,
    // "renderMode" sets the renderer type, only useful on web :
    //      0 - Automatically chosen by engine
    //      1 - Forced to use canvas renderer
    //      2 - Forced to use WebGL renderer, but this will be ignored on mobile browsers

    "engineDir"     : "frameworks/cocos2d-html5/",
    // In debug mode, if you use the whole engine to develop your game, you should specify its relative path with "engineDir",
    // but if you are using a single engine file, you can ignore it.

    "modules"       : ["cocos2d"],
    // "modules" defines which modules you will need in your game, it's useful only on web,
    // using this can greatly reduce your game's resource size, and the cocos console tool can package your game with only the modules you set.
    // For details about modules definitions, you can refer to "../../frameworks/cocos2d-html5/modulesConfig.json".

    "jsList"        : [
    ]
    // "jsList" sets the list of js files in your game.
 }
 *
 */

var scene = {};
var dialog = {};
var layout = {};
var util = {};
var node = {};
var setting = {
  SHOW_SCENE_STACK : false,
  SHOW_PUSH_NOTIFICATION : false,
  API_HOST : 'localhost',
  API_PORT : 8080
};


cc.game.onStart = function() {
  var sys = cc.sys;
  // If referenced loading.js, please remove it
  if (!sys.isNative && document.getElementById('cocosLoading')) {
    document.body.removeChild(document.getElementById('cocosLoading'));
  }

  // Pass true to enable retina display, on Android disabled by default to improve performance
  cc.view.enableRetina(sys.os === sys.OS_IOS);

  // Disable auto full screen on baidu and wechat, you might also want to eliminate sys.BROWSER_TYPE_MOBILE_QQ
  if (sys.isMobile &&
      sys.browserType !== sys.BROWSER_TYPE_BAIDU &&
      sys.browserType !== sys.BROWSER_TYPE_WECHAT) {
    cc.view.enableAutoFullScreen(true);
  }

  // Adjust viewport meta
  cc.view.adjustViewPort(true);

  // Uncomment the following line to set a fixed orientation for your game
  // cc.view.setOrientation(cc.ORIENTATION_PORTRAIT);

  // Setup the resolution policy and design resolution size
  // TODO:FIXED_WIDTHにして縦に遊び領域を作る方が良い気がする。
  cc.view.setDesignResolutionSize(1136, 640, cc.ResolutionPolicy.SHOW_ALL);
  // cc.view.setDesignResolutionSize(640, 1136, cc.ResolutionPolicy.FIXED_WIDTH);

  // The game will be resized when browser size change
  cc.view.resizeWithBrowserSize(true);

  // スコア初期化
  util.score.initializeScore(false);

  // load resources
  cc.LoaderScene.preload(gResources, function() {
    util.scene.pushScene(scene.TitleScene);
  }, this);
};
cc.game.run();
