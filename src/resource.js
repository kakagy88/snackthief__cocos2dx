var res = {
  // Scene
  TitleScene : 'res/scene/TitleScene.json',
  GameScene : 'res/scene/GameScene.json',
  DifficultyScene : 'res/scene/DifficultyScene.json',
  GameOverScene : 'res/scene/GameOverScene.json',
  GameClearScene : 'res/scene/GameClearScene.json',

  // Dialog
  MessageDialog : 'res/dialog/MessageDialog.json',
  YesNoDialog : 'res/dialog/YesNoDialog.json',

  speedUpImage : 'res/speedUp.png',
  speedUpPlist : 'res/speedUp.plist'
};

var gResources = [];
for (var i in res) {
  gResources.push(res[i]);
}
