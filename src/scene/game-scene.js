scene.GameScene = (function() {
  'use strict';

  // scaleの調整
  var scaleModified = 0.8;
  // 障害物の配列
  var birdArray = [];
  var bananaArray = [];
  var canArray = [];
  var flowerArray = [];
  var angryBirdArray = [];

  // 初期設定
  var distance = 0;
  var ySpeed = 0;
  var xSpeed = 0;
  var realSpeed = 0;
  var scrollSpeed = 3 * scaleModified;
  var jumpTrigger = false;
  var jumpTrigger2 = false;
  var damageIgnore = false;
  var combo = 0;
  var playerPositionX = (1136 * 0.4) * scaleModified;
  var playerPositionY = 180 * scaleModified;
  var collisionTrigger = true;
  var birdAttack = false;
  var bananaAttack = false;
  var canAttack = false;
  var characterAttackPower = 0;
  var playerRunWalkTrigger = true;
  var difficulty;


  var GameScene = scene.BaseScene.extend({
    _className : 'GameScene',
    ctor : function(param) {
      this._super(param);
      this._time = 0;
      this._views = {
        labelSpeed : null,
        labelTime : null,
        labelCombo : null,
        labelResult : null,
        labelDamage : null,
        labelDistance : null,
        labelSpeedUP : null,
        buttonTap : null,
        buttonBack : null
      };

      // 当たり判定の無効化時間調整
      this._collisionTimeInterval = 10;
      this._collisionTimeRemaining = this._collisionTimeInterval;

      // スクロールによる男の子出ノード整
      this._attackTimeInterval = 1000;
      this._attackTimeRemaining = this._attackTimeInterval;

      // スナちゃん速度上がり幅調整
      this._speedTimeInterval = 10;
      this._speedTimeRemaining = this._speedTimeInterval;

      // Jumpしている時間の初期化
      this.jumpTimer = 0;

      // 雲の配置
      this.cloud = cc.Sprite.create('res/images/game/sorakumoyama.png');
      this.cloud.setAnchorPoint(0, 0);
      this.cloud.setPosition(0, 90);
      this.addChild(this.cloud);

      // 地面の配置
      this.backgroundObject = cc.Sprite.create('res/images/game/backgroundObject.png');
      this.backgroundObject.setAnchorPoint(0, 0);
      this.backgroundObject.setPosition(0, 50);
      this.addChild(this.backgroundObject);


      // 地面の配置
      this.ground = cc.Sprite.create('res/images/game/zimen_x2_tatemono.png');
      this.ground.setAnchorPoint(0, 0);
      this.ground.setPosition(0, 0);
      this.addChild(this.ground);

      this.cloud.setScale(scaleModified);
      this.ground.setScale(scaleModified);
      this.backgroundObject.setScale(scaleModified);


      // 男の子のノード
      this.boy = Boy.create(this);
      this.addChild(this.boy);

      // 主人公の配置
      this.addPlayer(playerPositionX, playerPositionY);

      // 主人公悲しい顔
      this.sadPlayer = cc.Sprite.create('res/images/game/icon_me_lose.png');
      this.addChild(this.sadPlayer);
      this.sadPlayer.setOpacity(0);

      // 主人公早いエフェクト
      this.speedPlayer = cc.Sprite.create('res/images/game/kasoku01.png');
      this.speedPlayer.setScale(1.0);
      this.addChild(this.speedPlayer);
      this.speedPlayer.setOpacity(0);

      // 主人公セリフ
      this.talk = cc.Sprite.create('res/images/game/talk1.png');
      this.talk.setScale(0.25);
      this.addChild(this.talk);
      this.talk.setOpacity(0);

      // スピードゲージーの配置(UI)
      this.progressBar = ProgressBar.create(this);
      this.progressBar.setAnchorPoint(0.5, 0.5);
      this.progressBar.setPosition(320, 580);
      this.addChild(this.progressBar);

      // BGMを再生する
      cc.audioEngine.playMusic('res/bgm/bgm.wav', true);
      this.scheduleUpdate();
    },

    onEnter : function() {
      this._super();
      this._loadScene(res.GameScene);

      // レベル毎の設定
      difficulty = this._param.difficulty;
      switch (difficulty) {
      case DifficultyType.EASY:
        break;
      case DifficultyType.NORMAL:
        break;
      case DifficultyType.HARD:
        break;
      }

      cc.audioEngine.playEffect('res/bgm/girl_first.mp3', false);

      // UIを初期化
      this._views.buttonTap.setVisible(false);

      // アニメーション再生
      this._ccsData.action.play('ready', false);

      // readyアニメーションが終わったら呼ばれる処理
      this._ccsData.action.setLastFrameCallFunc(() => {
        // nullを設定しないとgoアニメーションの後にも繰り返し呼ばれるので注意！
        this._ccsData.action.setLastFrameCallFunc(null);
        this._ccsData.action.play('go', false);

        // ゲーム開始
        this._views.buttonTap.setVisible(true);

        // updateを毎フレーム呼ぶように
        this.scheduleUpdate();
      });
    },

    update : function(dt) {
      this._time += dt;
      this._views.labelTime.setString('Time : ' + this._time.toFixed(1) + ' ');
      this._views.labelCombo.setString('Combo : ' + combo);
      distance = this.boy.boyPositionX - this.player.getPositionX();
      this._views.labelDistance.setString('Distance : ' + Math.floor(distance));
      this._views.labelSpeed.setString('Speed : ' + scrollSpeed.toFixed(1));

      if (this.player.getPositionX() < 0 || this.progressBar._remaining < 0) {
        util.scene.replaceScene(scene.GameOverScene, {});

        // init
        this._init();
        this._ready = false;
        this._interval = 40;
        this._remaining = this._interval;
        this._remainingHP = this._remaining;
        this.attackTime = 2000;
        this.attackTimeRemaining = this.attackTime;
        this.turnNightTime = 0;
        this.boyPositionY = 480;
        this.boyPositionX = 1136 * 0.9;
        characterAttackPower = 10;
        this.turnNightTrigger = true;
      }

      this.talk.setPosition(this.player.getPositionX() + 50, this.player.getPositionY() + 130);

      // 雲の移動
      this.cloudscroll(this.cloud, 15904 - 1136, 0);
      // 地面の移動
      this.scroll(this.ground, 7838, 1.5);

      // 背景オブジェクトの移動
      this.backgroundscroll(this.backgroundObject, 8000, 0);
      // 花壇の移動
      this.kadanScroll(flowerArray, 1.5);

      // 主人公のジャンプ実行
      var pos = this.player.getPosition();
      if (jumpTrigger) {
        ySpeed -= 0.7 * scaleModified;
        xSpeed = 3 * scaleModified;
        this.jumpTimer++;
        this.player.setPosition(pos.x + xSpeed, pos.y + ySpeed);

        // 主人公のジャンプ落下制限
        if (pos.y < playerPositionY && this.jumpTimer > 5) {
          ySpeed = 0;
          xSpeed = 0;
          this.player.setPositionY(playerPositionY);
          jumpTrigger = false;
          jumpTrigger2 = false;
          this.jumpTimer = 0;
        }
      }

      if (pos.y < playerPositionY && jumpTrigger == false) {
        this.player.setPositionY(playerPositionY);
      }
      if (pos.y > playerPositionY && jumpTrigger == false) {
        this.player.setPositionY(pos.y - 1);
      }

      // キャラクターの枠を取得する
      var playerRect = this.player.getBoundingBox();
      playerRect.height = playerRect.height * 0.8;
      playerRect.width = playerRect.width * 0.8;
      playerRect.x = playerRect.x + (playerRect.width / 8);
      var boyRect = this.boy.boySprite.getBoundingBox();
      boyRect.height = boyRect.height * 0.8;
      boyRect.width = boyRect.width * 0.8;
      boyRect.x = boyRect.x + (boyRect.width / 8);

      if (cc.rectIntersectsRect(playerRect, boyRect)) {
        this.collisionBoy(this.boy.boySprite, this.player);
      }

      // スピードの上限
      if (scrollSpeed >= 7) {
        scrollSpeed = 7;
      }

      if (scrollSpeed > 6) {
        // this._ccsData.action.play('speed', false);
        this.speedPlayer.setOpacity(1000);
        this.speedPlayer.setPosition(this.player.getPositionX(), this.player.getPositionY());


      } else {
        this.speedPlayer.setOpacity(0);
      }

      if (scrollSpeed >= 4 && playerRunWalkTrigger == false) {
        playerRunWalkTrigger = true;
        this.playerRun();
        // this._ccsData.action.play('speed', false);
      }

      if (scrollSpeed < 4 && playerRunWalkTrigger) {
        playerRunWalkTrigger = false;
        this.playerWalk();
        // this._ccsData.action.play('speed', false);
      }
      if (scrollSpeed < 1) {
        scrollSpeed = 1;
      }

      // スピードの増加
      scrollSpeed = scrollSpeed + 0.003;


      // 主人公のスクロール移動速度調整
      realSpeed = (scrollSpeed - 4) * 0.3;


      // 主人公の速度による障害物のスピード調整
      if (this.bird) {
        this.bird.setPositionX(this.bird.getPositionX() - (scrollSpeed * 1.5));
      }
      if (this.banana) {
        this.banana.setPositionX(this.banana.getPositionX() - (scrollSpeed * 1.5));
      }
      if (this.can) {
        this.can.setPositionX(this.can.getPositionX() - (scrollSpeed * 1.5));
      }

      // 男の子の位置調整
      if (this.boy.boyPositionX > 1136 * 0.8) {
        playerPositionX = playerPositionX + realSpeed;
        if (this.player.getPositionX() < playerPositionX) {
          this.player.setPositionX(this.player.getPositionX() + 1);
        } else if (this.player.getPositionX() > playerPositionX) {
          this.player.setPositionX(this.player.getPositionX() - 1);
        }
        this.boy.boyPositionX = this.boy.boyPositionX - realSpeed;
      } else if (this.boy.boyPositionX < 1136 * 0.8) {
        playerPositionX = playerPositionX + (realSpeed * 2);
        if (this.player.getPositionX() < playerPositionX) {
          this.player.setPositionX(this.player.getPositionX() + 2);
        } else if (this.player.getPositionX() > playerPositionX) {
          this.player.setPositionX(this.player.getPositionX() - 2);
        }
        this.boy.boyPositionX = this.boy.boyPositionX + 1;
      }
      if (playerPositionX > 1136 * 0.8) {
        playerPositionX = playerPositionX - 10;
      }


      // 鳥の当たり判定のコントローラー
      for (var i = 0; i < birdArray.length; i++) {
        // birdArray[i].retain();
        var birdRect = birdArray[i].getBoundingBox();
        birdRect.height = birdRect.height * 0.5;
        birdRect.width = birdRect.width * 0.5;
        birdRect.x = birdRect.x + (birdRect.width / 2);
        if (cc.rectIntersectsRect(playerRect, birdRect)) {
          var bird = birdArray[i];
          birdArray.splice(i, 1);
          this.collisionBird(bird).next();
        }
        if (cc.rectIntersectsRect(boyRect, birdRect)) {
          if (birdAttack) {
            this.collisionBoyFromBlock(this.boy.boySprite, birdArray[i]);
            birdAttack = false;
          }
        }
      }

      // 怒った鳥の当たり判定のコントローラー
      for (var l = 0; l < angryBirdArray.length; l++) {
        var angryBirdRect = angryBirdArray[l].getBoundingBox();
        angryBirdRect.height = angryBirdRect.height * 0.5;
        angryBirdRect.width = angryBirdRect.width * 0.5;
        angryBirdRect.x = angryBirdRect.x + (angryBirdRect.width / 2);
        if (cc.rectIntersectsRect(playerRect, angryBirdRect)) {
          var angryBird = angryBirdArray[l];
          angryBirdArray.splice(l, 1);
          this.collisionAngryBird(angryBird).next();
        }
      }

      // バナナの当たり判定のコントローラー
      for (var j = 0; j < bananaArray.length; j++) {
        // bananaArray[i].retain();
        var bananaRect = bananaArray[j].getBoundingBox();
        bananaRect.height = bananaRect.height * 0.5;
        bananaRect.width = bananaRect.width * 0.5;
        bananaRect.x = bananaRect.x + (bananaRect.width / 2);
        if (cc.rectIntersectsRect(playerRect, bananaRect)) {
          var banana = bananaArray[j];
          bananaArray.splice(j, 1);
          this.collisionBanana(banana).next();
        }
        if (cc.rectIntersectsRect(boyRect, bananaRect)) {
          if (bananaAttack) {
            this.collisionBoyFromBlock(this.boy.boySprite, bananaArray[j]);
            bananaAttack = false;
          }
        }
      }

      // カンの当たり判定のコントローラー
      for (var k = 0; k < canArray.length; k++) {
        // canArray[i].retain();
        var canRect = canArray[k].getBoundingBox();
        canRect.height = canRect.height * 0.5;
        canRect.width = canRect.width * 0.5;
        canRect.x = canRect.x + (canRect.width / 2);
        if (cc.rectIntersectsRect(playerRect, canRect)) {
          var can = canArray[k];
          canArray.splice(k, 1);
          this.collisionCan(can).next();
        }
        if (cc.rectIntersectsRect(boyRect, canRect)) {
          if (canAttack) {
            this.collisionBoyFromBlock(this.boy.boySprite, canArray[k]);
            canAttack = false;
          }
        }
      }

      // スクロールによる障害物の出現調整
      --this._attackTimeRemaining;
      if (this._attackTimeRemaining % 200 == 0) {
        var birdY = (Math.random() * 150) + 200;
        this.addBird(1300, birdY);
      }
      if (this._attackTimeRemaining % 500 == 0) {
        var birdY2 = (Math.random() * 150) + 200;
        this.addBird(1300, birdY2);
      }

      if (this._attackTimeRemaining === 0) {
        this._attackTimeRemaining = this._attackTimeInterval;
      }

      // 当たり判定無効化の時間調整
      if (collisionTrigger == false) {
        --this._collisionTimeRemaining;
        if (this._collisionTimeRemaining === 0) {
          collisionTrigger = true;
          this._collisionTimeRemaining = this._collisionTimeInterval;
        }
      }

      // 当たった時に操作出来なくなる
      if (damageIgnore) {
        this._views.buttonTap.setVisible(false);
        --this._speedTimeRemaining;
      }
      if (this._speedTimeRemaining === 0) {
        damageIgnore = false;
        this._views.buttonTap.setVisible(true);
        this._speedTimeRemaining = this._speedTimeInterval;
      }
    },

    _onClickButtonTap : function() {
      // 主人公のジャンプ
      if (jumpTrigger == false && damageIgnore == false) {
        jumpTrigger2 = true;
        this.playerJump(20 * scaleModified);
      }

      if (jumpTrigger && jumpTrigger2) {
        jumpTrigger2 = false;
        this.playerJump(15 * scaleModified);
      }
    },

    // 初期化コード
    _init : function() {
      scaleModified = 0.8;
      // 障害物の配列
      birdArray = [];
      bananaArray = [];
      canArray = [];
      flowerArray = [];
      angryBirdArray = [];
      distance = 0;

      ySpeed = 0;
      xSpeed = 0;
      realSpeed = 0;
      scrollSpeed = 3 * scaleModified;

      jumpTrigger = false;
      damageIgnore = false;
      combo = 0;
      playerPositionX = (1136 * 0.4) * scaleModified;
      playerPositionY = 180 * scaleModified;
      collisionTrigger = true;

      birdAttack = false;
      bananaAttack = false;
      canAttack = false;
      difficulty;
      characterAttackPower = 0;
      playerRunWalkTrigger = true;
    },

    // 背景移動
    scroll : function(sprite, width, speedRate) {
      if (scrollSpeed != 0) {
        sprite.setPosition(sprite.getPosition().x - (scrollSpeed * speedRate) - 4, sprite.getPosition().y);
      }
      if (sprite.getPosition().x < -width) {
        sprite.setPosition(sprite.getPosition().x + width, sprite.getPosition().y);
        this.talk.setOpacity(200);
      }
    },

    // 雲の移動
    cloudscroll : function(sprite, width, speedRate) {
      if (scrollSpeed != 0) {
        sprite.setPosition(sprite.getPosition().x - (scrollSpeed * speedRate) - 1, sprite.getPosition().y);
      }
      if (sprite.getPosition().x < -width) {
        sprite.setPosition(sprite.getPosition().x + width, sprite.getPosition().y);
      }
    },

    // 背景移動
    backgroundscroll : function(sprite, width, speedRate) {
      if (scrollSpeed != 0) {
        sprite.setPosition(sprite.getPosition().x - (scrollSpeed * speedRate) - 2, sprite.getPosition().y);
      }
      if (sprite.getPosition().x < -width) {
        sprite.setPosition(sprite.getPosition().x + width, sprite.getPosition().y);
      }
    },

    // 障害物移動
    blockScroll : function* (sprite) {
      if (sprite.getTexture() != null) {
        var spriteTexture = sprite.getTexture().url;
      }
      var blockScrollSequence = [
        cc.moveBy(10, -4000, 0),
        cc.callFunc(() => {
          if (spriteTexture == 'res/images/game/asiba_tori.png') {
            birdArray.shift();
          }
          if (spriteTexture == 'res/images/game/akikan.png') {
            canArray.shift();
          }
          if (spriteTexture == 'res/images/game/banana.png') {
            bananaArray.shift();
          }
          sprite.removeFromParent();
        })
      ];
      sprite.runAction(
        cc.Sequence.create(blockScrollSequence)
      );
      yield;
    },

    // 怒った鳥の移動
    angryBirdScroll : function* (sprite) {
      if (sprite.getTexture() != null) {
        var spriteTexture = sprite.getTexture().url;
      }
      var angryBridSequence = [
        cc.delayTime(1),
        cc.moveTo(1, this.player.getPositionX() - 300, this.player.getPositionY() - 100),
        cc.callFunc(() => {
          if (spriteTexture == 'res/images/game/asiba_tori.png') {
            angryBirdArray.shift();
          }
          sprite.removeFromParent();
        })
      ];
      sprite.runAction(
        cc.Sequence.create(angryBridSequence)
      );
      yield;
    },

    // 花壇移動
    kadanScroll : function(spriteArray, speedRate, scene) {
      if (scrollSpeed != 0) {
        spriteArray.forEach(function(value) {
          value.setPosition(value.getPosition().x - (scrollSpeed * speedRate) - 4, value.getPosition().y);
          if (value.getPositionX() < -1500) {
            value.removeFromParent();
            flowerArray.shift();
          }
        });
      }
    },

    // 主人公
    addPlayer : function(posX, posY) {
      this.player = cc.Sprite.create('res/images/game/run1.png');
      this.player.setScale(4.0);
      this.player.setOpacity(0);
      this.player.setPosition(posX, posY);
      this.addChild(this.player, 2);

      var sequenceAction = [
        cc.Spawn.create(
          cc.FadeIn.create(0.5),
          cc.ScaleTo.create(0.5, scaleModified, scaleModified).easing(cc.easeSineOut())
        ),
        cc.callFunc(() => {
          if (scrollSpeed > 4) {
            playerRunWalkTrigger = true;
            this.playerRun();
          }
          if (scrollSpeed < 4) {
            playerRunWalkTrigger = false;
            this.playerWalk();
          }
          this._ready = true;
        })
      ];

      var action =
        cc.Sequence.create(sequenceAction);

      this.player.runAction(action);
    },

    // 主人公の走るモーション
    playerRun : function() {
      this.player.stopAllActions();
      this.delayTime = 0.2 - (scrollSpeed * (1 / 70));
      var playerRunSequence = [
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/run1.png')),
        cc.DelayTime.create(this.delayTime),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/run2.png')),
        cc.DelayTime.create(this.delayTime),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/run3.png')),
        cc.DelayTime.create(this.delayTime),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/run4.png')),
        cc.DelayTime.create(this.delayTime),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/run5.png')),
        cc.DelayTime.create(this.delayTime),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/run6.png')),
        cc.callFunc(() => {
        })

      ];
      this.player.runAction(
        cc.RepeatForever.create(
          cc.Sequence.create(playerRunSequence)
        )
      );
    },

    // 主人公のヘトヘトモーション
    playerWalk : function() {
      this.delayTime = 0.2 - (scrollSpeed * (1 / 140));
      var playerWalkSequence = [
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/gensoku01.png')),
        cc.DelayTime.create(this.delayTime),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/gensoku02.png')),
        cc.DelayTime.create(this.delayTime),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/gensoku03.png')),
        cc.DelayTime.create(this.delayTime),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/gensoku04.png')),
        cc.DelayTime.create(this.delayTime),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/gensoku05.png')),
        cc.DelayTime.create(this.delayTime),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/gensoku06.png')),
        cc.callFunc(() => {
        })
      ];
      this.player.runAction(
        cc.RepeatForever.create(
          cc.Sequence.create(playerWalkSequence)
        )
      );
    },

    // 主人公のジャンプモーション
    playerJump : function(ySpeedNumber) {
      this.player.stopAllActions();
      if (scrollSpeed > 7) {
        var speedUp = new cc.ParticleSystem(res.speedUpPlist);
        this.addChild(speedUp);
      }
      cc.audioEngine.playEffect('res/bgm/jump.mp3', false);
      this.scheduleOnce(function() {
        ySpeed = ySpeedNumber;
        jumpTrigger = true;
      }, 0);
      var playerJumpAction = [
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/jump1.png')),
        cc.DelayTime.create(0.05),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/jump2.png')),
        cc.DelayTime.create(0.1),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/jump3.png')),
        cc.DelayTime.create(0.4),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/jump4.png')),
        cc.DelayTime.create(0.2),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/jump5.png')),
        cc.DelayTime.create(0.2),
        cc.CallFunc.create(() => this.player.setTexture('res/images/game/jump6.png')),
        cc.callFunc(() => {
          if (scrollSpeed > 4) {
            playerRunWalkTrigger = true;
            this.talk.setOpacity(0);
            this.playerRun();
          }
          if (scrollSpeed < 4) {
            playerRunWalkTrigger = false;
            this.playerWalk();
          }
        })
      ];
      this.player.runAction(
        cc.Sequence.create(playerJumpAction)
      );
    },

    // 主人公がダメージを受けた時
    playerDamaged : function() {
      if (damageIgnore == false) {
        damageIgnore = true;
        cc.audioEngine.playEffect('res/bgm/damage.mp3', false);
        this.player.stopAllActions();
        var posX = this.player.getPositionX();
        var posY = this.player.getPositionY();
        var playerDamagedSequence = [
          cc.CallFunc.create(() => this.player.setTexture('res/images/game/hit.png')),
          cc.bezierTo(0.4, [cc.p(posX - 80 * scaleModified, posY + 150 * scaleModified), cc.p(posX - 140 * scaleModified, posY + 0 * scaleModified), cc.p(posX - 200 * scaleModified, 140 * scaleModified)]),
          cc.callFunc(() => {
            scrollSpeed = scrollSpeed - 3;
            playerPositionX = playerPositionX - 100 * scaleModified;
            if (scrollSpeed > 4) {
              playerRunWalkTrigger = true;
              this.playerRun();
            }
            if (scrollSpeed < 4) {
              playerRunWalkTrigger = false;
              this.playerWalk();
            }
          })
        ];
        this.player.runAction(
          cc.Sequence.create(playerDamagedSequence)
        );
      }
    },

    // 鳥の生成メソッド
    addBird : function(posX, posY) {
      birdAttack = false;
      this.bird = cc.Sprite.create('res/images/game/asiba_tori.png');
      this.bird.retain();
      this.bird.setPosition(posX, posY);
      this.bird.setOpacity(0);
      this.bird.setScale(scaleModified);
      this._birdAnimation(this.bird).next();
      this.addChild(this.bird, 1, 'bird' + this.bird.getPositionY());
      birdArray.push(this.getChildByName('bird' + this.bird.getPositionY()));
      this.blockScroll(this.bird).next();
    },

    // 鳥のアニメーション
    _birdAnimation : function* (sprite) {
      var birdAnimationSequence1 = [
        cc.Spawn.create(
          cc.FadeIn.create(0.5)
        ),
        cc.callFunc(() => {
          var birdAnimationSequence2 = [
            cc.CallFunc.create(() => sprite.setTexture('res/images/game/asiba_tori1.png')),
            cc.DelayTime.create(0.3),
            cc.CallFunc.create(() => sprite.setTexture('res/images/game/asiba_tori.png')),
            cc.DelayTime.create(0.3)
          ];
          sprite.runAction(cc.RepeatForever.create(
            cc.Sequence.create(birdAnimationSequence2)
          ));
        })
      ];
      sprite.runAction(
        cc.Sequence.create(birdAnimationSequence1)
      );
      yield;
    },

    // 怒った鳥の生成メソッド
    addAngryBird : function(posX, posY) {
      // birdAttack = false;
      this.angryBird = cc.Sprite.create('res/images/game/asiba_tori.png');
      this.angryBird.retain();
      this.angryBird.setPosition(posX, posY);
      this.angryBird.setOpacity(0);
      this.angryBird.setScale(scaleModified);
      this._angryBirdAnimation(this.angryBird).next();
      this.addChild(this.angryBird, 1, 'angryBird' + this.angryBird.getPositionY());
      // this.angryBird.release();
      angryBirdArray.push(this.getChildByName('angryBird' + this.angryBird.getPositionY()));
      this.angryBirdScroll(this.angryBird).next();
    },

    // 怒った鳥のアニメーション
    _angryBirdAnimation : function* (sprite) {
      var angryBirdAnimationSequence1 = [
        cc.Spawn.create(
          cc.TintTo.create(1, 236, 128, 147),
          cc.FadeIn.create(0.5)
        ),
        cc.callFunc(() => {
          var angryBirdAnimationSequence2 = [
            cc.CallFunc.create(() => sprite.setTexture('res/images/game/asiba_tori1.png')),
            cc.DelayTime.create(0.3),
            cc.CallFunc.create(() => sprite.setTexture('res/images/game/asiba_tori.png')),
            cc.DelayTime.create(0.3)
          ];
          sprite.runAction(cc.RepeatForever.create(
            cc.Sequence.create(angryBirdAnimationSequence2)
          ));
        })
      ];
      sprite.runAction(
        cc.Sequence.create(angryBirdAnimationSequence1)
      );
      yield;
    },


    // 花壇の生成メソッド
    addFlower : function(posX, posY) {
      this.flower = Flower.create(this, 6);
      this.flower.setPosition(posX, posY);
      this.flower.setScale(scaleModified);
      this.addChild(this.flower, 3, 'flower' + this.flower.getPositionX());
      flowerArray.push(this.getChildByName('flower' + this.flower.getPositionX()));
    },


    // バナナの生成メソッド
    addBanana : function(posX, posY) {
      bananaAttack = false;
      this.banana = cc.Sprite.create('res/images/game/banana.png');
      this.banana.retain();
      this.banana.setPosition(posX, posY);
      this.banana.setScale(scaleModified);
      this.addChild(this.banana, 1, 'banana' + this.banana.getPositionY());
      // this.banana.release();
      bananaArray.push(this.getChildByName('banana' + this.banana.getPositionY()));
      this.blockScroll(this.banana).next();
    },

    // 男の子から、バナナを生成するメソッド
    addBananaAlot : function(posX, posY) {
      this.bananaThrowing = cc.Sprite.create('res/images/game/banana_throwing.png');
      this.bananaThrowing.retain();
      this.bananaThrowing.setPosition(posX, posY);
      this.bananaThrowing.setScale(scaleModified);
      this.addChild(this.bananaThrowing, 1);
      this._throwingBananaCorouotine(this.bananaThrowing).next();
    },

    _throwingBananaCorouotine : function* (sprite) {
      var posX = sprite.getPositionX();
      var posY = sprite.getPositionY();
      var _throwingBananaCorouotineSequence = [
        cc.bezierTo(1, [cc.p(posX + 50 * scaleModified, posY + 200 * scaleModified), cc.p(posX + 100 * scaleModified, posY + 0 * scaleModified), cc.p(posX + 0 * scaleModified, 140 * scaleModified)]),
        cc.callFunc(() => {
          this.addBanana(sprite.getPositionX(), sprite.getPositionY());
          sprite.removeFromParent();
        })
      ];
      sprite.runAction(
        cc.Sequence.create(_throwingBananaCorouotineSequence)
      );
      // sprite.release();
      yield;
    },

    // 空き缶の生成メソッド
    addCan : function(posX, posY) {
      canAttack = false;
      this.can = cc.Sprite.create('res/images/game/akikan.png');
      this.can.retain();
      this.can.setPosition(posX, posY);
      this.can.setScale(scaleModified);
      this.addChild(this.can, 1, 'can' + this.can.getPositionY());
      canArray.push(this.getChildByName('can' + this.can.getPositionY()));
      this.blockScroll(this.can).next();
    },

    // 男の子から、カンを生成するメソッド
    addCanAlot : function(posX, posY) {
      this.canThrowing = cc.Sprite.create('res/images/game/akikan_throwing.png');
      this.canThrowing.retain();
      this.canThrowing.setPosition(posX, posY);
      this.canThrowing.setScale(scaleModified);
      this.addChild(this.canThrowing, 1);
      this._throwingCanCorouotine(this.canThrowing).next();
      // this.canThrowing.release();
    },

    _throwingCanCorouotine : function* (sprite) {
      var posX = sprite.getPositionX();
      var posY = sprite.getPositionY();
      var _throwingCanCorouotineSequence = [
        cc.bezierTo(1, [cc.p(posX - 100 * scaleModified, posY + 200 * scaleModified), cc.p(posX - 200 * scaleModified, posY + 0 * scaleModified), cc.p(posX - 300 * scaleModified, 140 * scaleModified)]),
        cc.callFunc(() => {
          sprite.removeFromParent();
          this.addCan(sprite.getPositionX(), sprite.getPositionY());
        })
      ];
      sprite.runAction(
        cc.Sequence.create(_throwingCanCorouotineSequence)
      );
      // sprite.release();
      yield;
    },

    // （当たった時の）星の生成メソッド
    addStar : function(posX, posY) {
      this.starSprite = cc.Sprite.create('res/images/game/star.png');
      this.starSprite.retain();
      this.starSprite.setPosition(posX, posY);
      this.starSprite.setScale(0.5);
      this.starSprite.setScale(scaleModified);
      this.addChild(this.starSprite, 2, 'star' + this.starSprite.getPositionX());
      var addStarSequence = [
        cc.Spawn.create(
          cc.FadeOut.create(0.5),
          cc.RotateBy.create(0.5, 180),
          cc.ScaleTo.create(0.5, scaleModified)
        ),
        cc.DelayTime.create(0.5),
        // 出現後の処理
        cc.callFunc(() => {
          this.removeFromParent();
        })
      ];
      this.starSprite.runAction(
        cc.Sequence.create(addStarSequence)
      );
      // this.starSprite.release();
    },

    // 男の子が主人公と当たった時に実行される
    collisionBoy : function(boy, target) {
      if (collisionTrigger) {
        // collisionBoyTrigger = true;
        collisionTrigger = false;
        this.boy.boyDamaged();
        this.addStar((boy.getPositionX() + target.getPositionX()) / 2, (boy.getPositionY() + target.getPositionY()) / 2);
      }
    },

    // 男の子が障害物と当たった時に実行される
    collisionBoyFromBlock : function(boy, target) {
      if (collisionTrigger) {
        this.boy.boyDamagedFromBlock();
        this.addStar((boy.getPositionX() + target.getPositionX()) / 2, (boy.getPositionY() + target.getPositionY()) / 2);
      }
    },

    // 鳥と当たった時に実行される
    collisionBird : function* (bird) {
      if (collisionTrigger) {
        cc.audioEngine.playEffect('res/bgm/tori.mp3', false);
        combo++;
        this._ccsData.action.play('combo', false);
        this._ccsData.action.setLastFrameCallFunc(() => {
          this._ccsData.action.setLastFrameCallFunc(null);
          this._views.labelSpeedUP.setVisible(false);
        });
        scrollSpeed = scrollSpeed + (0.3 * combo);
        collisionTrigger = false;
        var posX = bird.getPositionX();
        var posY = bird.getPositionY();
        var i = Math.random() * 20;
        bird.stopAllActions();

        var collisionBirdSequence = [
          cc.CallFunc.create(() => {
            // this.playerJump(17 * scaleModified);
            bird.setTexture('res/images/game/asiba_tori2.png');
            this.addStar((bird.getPositionX() + this.player.getPositionX()) / 2, (bird.getPositionY() + this.player.getPositionY()) / 2);
            this.happyPlayer = cc.Sprite.create('res/images/game/icon_me_happy.png');
            this.happyPlayer.setPosition(this.player.getPositionX(), this.player.getPositionY() + 100);
            this.addChild(this.happyPlayer);
            this.happyPlayer.runAction(cc.FadeOut.create(1));
            this.happyPlayer.runAction(cc.ScaleTo.create(1, 2));
            if (i > 1) {
              bird.runAction(
                cc.Spawn.create(
                  cc.bezierTo(0.5, [cc.p(posX + 200 * scaleModified, posY + 200 * scaleModified), cc.p(posX + 400 * scaleModified, posY + 0 * scaleModified), cc.p(posX + 500 * scaleModified, 140 * scaleModified)]),
                  cc.rotateBy(0.5, 360)
                )
              );
            } else {
              cc.audioEngine.playEffect('res/bgm/girl_second.mp3', false);
              var collisionBirdSequence2 = [
                cc.Spawn.create(
                  cc.moveTo(0.5, this.boy.boySprite.getPositionX() + 50 * scaleModified, this.boy.boySprite.getPositionY() - 100 * scaleModified),
                  cc.rotateBy(0.5, 360)
                ),
                cc.callFunc(() => {
                  this.collisionBoyFromBlock(this.boy.boySprite, bird);
                })
              ];
              bird.runAction(
                cc.Sequence.create(collisionBirdSequence2)
              );
            }
          }),
          cc.fadeOut(1.5),
          cc.callFunc(() => {
            bird.removeFromParent();
            this.happyPlayer.removeFromParent();
          })
        ];
        bird.runAction(
          cc.Sequence.create(collisionBirdSequence)
        );
        yield;
      }
    },

    // 怒った鳥と当たった時に実行される
    collisionAngryBird : function* (bird) {
      if (collisionTrigger) {
        collisionTrigger = false;
        var posX = bird.getPositionX();
        var posY = bird.getPositionY();
        bird.stopAllActions();
        var collisionAngryBird = [
          cc.CallFunc.create(() => {
            this.playerDamaged();
            combo = 0;
            bird.setTexture('res/images/game/asiba_tori2.png');
            this.addStar((bird.getPositionX() + this.player.getPositionX()) / 2, (bird.getPositionY() + this.player.getPositionY()) / 2);
            bird.runAction(
              cc.Spawn.create(
                cc.bezierTo(0.5, [cc.p(posX + 200 * scaleModified, posY + 200 * scaleModified), cc.p(posX + 400 * scaleModified, posY + 0 * scaleModified), cc.p(posX + 500 * scaleModified, 140 * scaleModified)]),
                cc.rotateBy(0.5, 360)
              )
            );
          }),
          cc.fadeOut(1.5),
          cc.callFunc(() => {
            bird.removeFromParent();
          })
        ];
        bird.runAction(
          cc.Sequence.create(collisionAngryBird)
        );
        // bird.release();
        yield;
      }
    },

    // バナナと当たった時に実行される
    collisionBanana : function* (banana) {
      if (collisionTrigger) {
        bananaAttack = true;
        collisionTrigger = false;
        var posX = banana.getPositionX();
        var posY = banana.getPositionY();
        banana.stopAllActions();
        var i = Math.random() * 10;
        var collisionBananaSequence = [
          cc.CallFunc.create(() => {
            this.playerDamaged();
            combo = 0;
            this.addStar((banana.getPositionX() + this.player.getPositionX()) / 2, (banana.getPositionY() + this.player.getPositionY()) / 2);
            if (i > 1) {
              banana.runAction(
                cc.Spawn.create(
                  cc.bezierTo(0.5, [cc.p(posX + 200 * scaleModified, posY + 200 * scaleModified), cc.p(posX + 400 * scaleModified, posY + 0 * scaleModified), cc.p(posX + 500 * scaleModified, 140 * scaleModified)]),
                  cc.rotateBy(0.5, 360)
                )
              );
            } else {
              cc.audioEngine.playEffect('res/bgm/girl_second.mp3', false);
              var collisionBananaSequence2 = [
                cc.Spawn.create(
                  cc.moveTo(0.5, this.boy.boySprite.getPositionX() + 50 * scaleModified, this.boy.boySprite.getPositionY() - 100 * scaleModified),
                  cc.rotateBy(0.5, 360)
                ),
                cc.callFunc(() => {
                  this.collisionBoyFromBlock(this.boy.boySprite, banana);
                })
              ];
              banana.runAction(
                cc.Sequence.create(collisionBananaSequence2)
              );
            }
          }),
          // collisionStar,
          cc.fadeOut(1),
          cc.callFunc(() => {
            banana.removeFromParent();
          })
        ];
        banana.runAction(
          cc.Sequence.create(collisionBananaSequence)
        );
        // banana.release();
        yield;
      }
    },

    // カンと当たった時に実行される
    collisionCan : function* (can) {
      if (collisionTrigger) {
        canAttack = true;
        collisionTrigger = false;
        // collisionCanTrigger = true;
        var posX = can.getPositionX();
        var posY = can.getPositionY();
        var i = Math.random() * 10;
        can.stopAllActions();
        var collisionCanSequence = [
          cc.CallFunc.create(() => {
            this.playerDamaged();
            can.setTexture('res/images/game/akikan_throwing.png');
            combo = 0;
            this.addStar((can.getPositionX() + this.player.getPositionX()) / 2, (can.getPositionY() + this.player.getPositionY()) / 2);
            if (i > 1) {
              can.runAction(
                cc.Spawn.create(
                  cc.bezierTo(0.5, [cc.p(posX + 200 * scaleModified, posY + 200 * scaleModified), cc.p(posX + 400 * scaleModified, posY + 0 * scaleModified), cc.p(posX + 500 * scaleModified, 140 * scaleModified)]),
                  cc.rotateBy(0.5, 360)
                )
              );
            } else {
              cc.audioEngine.playEffect('res/bgm/girl_second.mp3', false);
              var collisionCanSequence2 = [
                cc.Spawn.create(
                  cc.moveTo(0.5, this.boy.boySprite.getPositionX() + 50 * scaleModified, this.boy.boySprite.getPositionY() - 100 * scaleModified),
                  cc.rotateBy(0.5, 360)
                ),
                cc.callFunc(() => {
                  this.collisionBoyFromBlock(this.boy.boySprite, can);
                })
              ];
              can.runAction(
                cc.Sequence.create(collisionCanSequence2)
              );
            }
          }),
          cc.fadeOut(1),
          cc.callFunc(() => {
            can.removeFromParent();
          })
        ];
        can.runAction(
          cc.Sequence.create(collisionCanSequence)
        );
        // can.release();
        yield;
      }
    },

    _onClickButtonBack : function() {
      util.scene.popScene();
    }
  });

  // 男の子のノード
  var Boy = cc.Node.extend({
    ctor : function(scene) {
      this._super();
      this._scene = scene;
      this._moveOffsetX = 1;
      this._moveOffsetY = 1;
      this._ready = false;
      this._interval = 40;
      this._remaining = this._interval;
      this._remainingHP = this._remaining;
      this.attackTime = 2000;
      this.attackTimeRemaining = this.attackTime;
      this.turnNightTime = 0;
      this._gauge = null;
      this.boyPositionY = 480 * scaleModified;
      this.boyPositionX = 1136 * 0.9;
      characterAttackPower = 10;
      this.turnNightTrigger = true;

      this.boySprite = cc.Sprite.create('res/images/game/boy.png');
      // this.boySprite.setOpacity(100);
      this.boySprite.setPosition(this.boyPositionX, this.boyPositionY);
      this.addChild(this.boySprite, 1);

      // 青い風船のスプライト
      this.balloon1Sprite = cc.Sprite.create('res/images/game/blewhuusen.png');
      this.addChild(this.balloon1Sprite);

      // 赤い風船のスプライト
      this.balloon2Sprite = cc.Sprite.create('res/images/game/redhuusen.png');
      this.addChild(this.balloon2Sprite);

      // 黄色い風船のスプライト
      this.balloon3Sprite = cc.Sprite.create('res/images/game/kiirohuusen.png');
      this.addChild(this.balloon3Sprite);


      // ゲージ
      this.gaugeBg = cc.Sprite.create('res/images/game/gauge-bg.png');
      this.gaugeBg.setAnchorPoint(0, 0);
      this.addChild(this.gaugeBg);
      this._gauge = cc.Sprite.create('res/images/game/gauge.png');
      this._gauge.setAnchorPoint(0, 0);
      this.addChild(this._gauge);

      this.scheduleUpdate();
    },
    update : function(dt) {
      this._super(dt);

      // スケール修正
      this.boySprite.setScale(scaleModified);
      this.boyPositionY = 480 * scaleModified;
      this.balloon1Sprite.setScale(scaleModified);
      this.balloon2Sprite.setScale(scaleModified);
      this.balloon3Sprite.setScale(scaleModified);
      this.gaugeBg.setScale(scaleModified);
      this._gauge.setScale(scaleModified);


      this.balloon1Sprite.setPosition(this.boySprite.getPositionX(), this.boySprite.getPositionY());
      this.balloon2Sprite.setPosition(this.boySprite.getPositionX(), this.boySprite.getPositionY());
      this.balloon3Sprite.setPosition(this.boySprite.getPositionX(), this.boySprite.getPositionY());
      this.gaugeBg.setPosition((-73 * scaleModified) + this.boySprite.getPositionX(), (-200 * scaleModified) + this.boySprite.getPositionY());
      this._gauge.setPosition((-70 * scaleModified) + this.boySprite.getPositionX(), (-200 * scaleModified) + this.boySprite.getPositionY());

      // 左右移動
      if (this.boySprite.getPositionX() < this.boyPositionX + 50 * scaleModified) {
        this._moveOffsetX = 1;
      } else if (this.boySprite.getPositionX() > this.boyPositionX - 50 * scaleModified) {
        this._moveOffsetX = -1;
      }
      this.boySprite.setPositionX(this.boySprite.getPositionX() + this._moveOffsetX);

      // 上下移動
      if (this.boySprite.getPositionY() > this.boyPositionY + 30 * scaleModified) {
        this._moveOffsetY = -1;
      } else if (this.boySprite.getPositionY() < this.boyPositionY - 30 * scaleModified) {
        this._moveOffsetY = 1;
      }
      this.boySprite.setPositionY(this.boySprite.getPositionY() + this._moveOffsetY);

      --this.attackTimeRemaining;
      // easyMode
      if (difficulty == 0) {
        if (this._attackTimeRemaining === 0) {
          this.attackTimeRemaining = this.attackTime;
        }

        if (this.attackTimeRemaining % 600 == 0) {
          this.boyCanAttack();
        }
        if (this.attackTimeRemaining % 700 == 0) {
          var angryBirdY = (Math.random() * 200 * scaleModified) + 200 * scaleModified;
          this._scene.addAngryBird(1100, angryBirdY);
          this.boyBananaAttack();
        }
      }

      // hardMode
      if (difficulty == 1) {
        if (this.attackTimeRemaining % 600 == 0) {
          this.boyCanAttack();
          var angryBirdY = (Math.random() * 200 * scaleModified) + 200 * scaleModified;
          this._scene.addAngryBird(1100, angryBirdY);
        }
        if (this.attackTimeRemaining % 700 == 0) {
          this.boyBananaAttack();
          var angryBirdY = (Math.random() * 200 * scaleModified) + 200 * scaleModified;
          this._scene.addAngryBird(1100, angryBirdY);
        }

        if (this.attackTimeRemaining % 1500 == 0) {
          var angryBirdY = (Math.random() * 200 * scaleModified) + 200 * scaleModified;
          this._scene.addAngryBird(1100, angryBirdY);
        }
      }


      // ゲージ
      this._gauge.setTextureRect(cc.rect(0, 0, 140 * (this._remaining / this._interval), 16));

      if (this._remaining >= this._remainingHP) {
        --this._remaining;
      }

      // 男の子のノードによるエフェクト
      if (this._remaining === 20 && this.turnNightTrigger) {
        this.balloon3Sprite.stopAllActions();
        this._gauge.runAction(cc.TintTo.create(1, 116, 170, 93));
        var balloon3SpriteSequence = [
          cc.Spawn.create(
            cc.FadeOut.create(2),
            cc.ScaleTo.create(2, 2)
          ),
          // 出現後の処理
          cc.callFunc(() => {
            this.removeFromParent;
          })
        ];
        var action =
          cc.Sequence.create(balloon3SpriteSequence);
        this.balloon3Sprite.runAction(action);

        var turnNightAnimation = [
          cc.CallFunc.create(() => this._scene.cloud.runAction(cc.tintTo(5, 105, 79, 198))),
          cc.DelayTime.create(5)
        ];
        this._scene.cloud.runAction(
          cc.Sequence.create(turnNightAnimation)
        );
        this.turnNightTrigger = false;
      }

      if (this._remaining === 10) {
        this.balloon1Sprite.stopAllActions();
        this._gauge.runAction(cc.TintTo.create(1, 236, 128, 147));
        var balloon1SpriteSequence = [
          cc.Spawn.create(
            cc.FadeOut.create(2),
            cc.ScaleTo.create(2, 2)
          ),
          // 出現後の処理
          cc.callFunc(() => {
            this.removeFromParent;
          })
        ];
        var action =
          cc.Sequence.create(balloon1SpriteSequence);
        this.balloon1Sprite.runAction(action);
      }

      if (this._remaining === 1) {
        this.balloon2Sprite.stopAllActions();
        scrollSpeed = 0;
        var endingSequence2 = [
          cc.Spawn.create(
            cc.FadeOut.create(0.5),
            cc.ScaleTo.create(0.5, 2)
          ),
          // 出現後の処理
          cc.callFunc(() => {
            this.removeFromParent;
            this._scene.boy.stopAllActions();
            this._scene.player.stopAllActions();
            this._scene.unscheduleUpdate();
            this.boySprite.setTexture('res/images/game/boyhit2.png');
            this._scene.player.setTexture('res/images/game/_win.png');
            this._scene.player.runAction(cc.moveTo(0.5, this._scene.player.getPositionX(), 160));
            this.boySprite.runAction(cc.rotateBy(1, 1440));
            var endingSequence = [
              cc.moveTo(0.5, this.boySprite.getPositionX() - 300, 0),
              cc.callFunc(() => {
                this._scene.addStar(this.boySprite.getPositionX(), this.boySprite.getPositionY());
              }),
              cc.moveTo(0.5, this.boySprite.getPositionX() - 300, 1000),
              cc.callFunc(() => {
                util.scene.replaceScene(scene.GameClearScene, {
                  time : this._scene._time
                });
                // playerPositionX = (1136 * 0.4) * scaleModified;
                // this._scene.player.setPositionX(playerPositionX);
                // init
                this._scene._init();
                this._ready = false;
                this._interval = 40;
                this._remaining = this._interval;
                this._remainingHP = this._remaining;
                this.attackTime = 2000;
                this.attackTimeRemaining = this.attackTime;
                this.turnNightTime = 0;
                this.boyPositionY = 480;
                this.boyPositionX = 1136 * 0.9;
                characterAttackPower = 10;
                this.turnNightTrigger = true;
                util.score.updateScore(this._scene._param.difficulty, this._scene._time);

              }
              )
            ];
            this.boySprite.runAction(
              cc.Sequence.create(endingSequence)
            );
            // updateを呼ばないように
            this._scene.unscheduleUpdate();
          })
        ];
        var action =
          cc.Sequence.create(endingSequence2);
        this.balloon2Sprite.runAction(action);
      }
    },

    // 男の子のカン攻撃
    boyCanAttack : function() {
      var boyX = this.boySprite.getPositionX();
      var boyY = this.boySprite.getPositionY();
      this._scene.addCanAlot(boyX, boyY - 10 * scaleModified);
    },
    // 男の子のバナナ攻撃
    boyBananaAttack : function() {
      var boyX = this.boySprite.getPositionX();
      var boyY = this.boySprite.getPositionY();
      this._scene.addBananaAlot(boyX, boyY - 10 * scaleModified);
    },

    // 男の子が主人公に攻撃された時に実行される
    boyDamaged : function() {
      cc.audioEngine.playEffect('res/bgm/damage.mp3', false);
      this._remainingHP = this._remaining - characterAttackPower;
      var playerX = this._scene.player.getPositionX();
      var playerY = this._scene.player.getPositionY();

      // ダメージの表示
      this._scene._views.labelDamage.setVisible(true);
      this._scene._views.labelDamage.setString('-' + characterAttackPower);
      this._scene._ccsData.action.play('damage', false);
      this._scene._ccsData.action.setLastFrameCallFunc(() => {
        this._scene._ccsData.action.setLastFrameCallFunc(null);
        this._scene._views.labelDamage.setVisible(false);
      });

      this.scheduleOnce(function() {
        this._scene.player.runAction(cc.bezierTo(1.5, [cc.p(playerX - 800, playerY + 250), cc.p(playerX - 450, playerY), cc.p(playerX - 500, 150)]));
      }, 0);

      var boySpriteSequence = [
        cc.CallFunc.create(() => this.boySprite.setTexture('res/images/game/boyhit.png')),
        cc.bezierBy(1.5, [cc.p(400 * scaleModified, 400 * scaleModified), cc.p(100 * scaleModified, -100 * scaleModified), cc.p(50 * scaleModified, 50 * scaleModified)]),
        cc.DelayTime.create(0.3),
        cc.callFunc(() => {
          this.boySprite.setTexture('res/images/game/boy.png');
        })
      ];
      this.boySprite.runAction(
        cc.Sequence.create(boySpriteSequence)
      );
    },

    // 男の子が障害物に攻撃された時に実行される
    boyDamagedFromBlock : function() {
      cc.audioEngine.playEffect('res/bgm/damage.mp3', false);
      this._remainingHP = this._remaining - characterAttackPower;
      // ダメージの表示
      this._scene._views.labelDamage.setVisible(true);
      this._scene._views.labelDamage.setString('-' + characterAttackPower);
      this._scene._ccsData.action.play('damage', false);
      this._scene._ccsData.action.setLastFrameCallFunc(() => {
        this._scene._ccsData.action.setLastFrameCallFunc(null);
        this._scene._views.labelDamage.setVisible(false);
      });
      var boySpriteSequence2 = [
        cc.CallFunc.create(() => this.boySprite.setTexture('res/images/game/boyhit.png')),
        cc.bezierBy(1.5, [cc.p(400 * scaleModified, 400 * scaleModified), cc.p(100 * scaleModified, -100 * scaleModified), cc.p(50 * scaleModified, 50 * scaleModified)]),
        cc.DelayTime.create(0.3),
        cc.callFunc(() => {
          this.boySprite.setTexture('res/images/game/boy.png');
        })
      ];
      this.boySprite.runAction(
        cc.Sequence.create(boySpriteSequence2)
      );
    }
  });
  Boy.create = function(scene) {
    return new Boy(scene);
  };


  // 花壇の配置
  var Flower = cc.Node.extend({
    ctor : function(scene, flowerNumber) {
      this._super();
      this._scene = scene;
      this.flowerNumber = flowerNumber;

      // 花壇
      for (var i = 0; i < flowerNumber; i++) {
        var flower = cc.Sprite.create('res/images/game/kadan.png');
        flower.setAnchorPoint(0, 0);
        flower.setPosition(49 + (134 * i), 0);
        this.addChild(flower);
      }

      // 花壇（右）名所が反対になっている。。
      this.flowerL = cc.Sprite.create('res/images/game/kadanL.png');
      this.flowerL.setAnchorPoint(0, 0);
      this.flowerL.setPosition(134 * flowerNumber, 0);

      // 花壇（左）
      var flowerR = cc.Sprite.create('res/images/game/kadanR.png');
      flowerR.setAnchorPoint(0, 0);
      flowerR.setPosition(0, 0);

      // 看板
      var kanban = cc.Sprite.create('res/images/game/kanban.png');
      kanban.setAnchorPoint(0, 0);
      kanban.setPosition(-300 * scaleModified, 0);

      this.addChild(this.flowerL);
      this.addChild(flowerR);
      this.addChild(kanban);

      this.scheduleUpdate();
    },
    update : function(dt) {
      this._super(dt);

      if (this._scene.flower.getPositionX() < this._scene.player.getPositionX() && this._scene.flower.getPositionX() + (this.flowerNumber * 160) > this._scene.player.getPositionX() && this._scene.flower.getPositionY() + 70 == this._scene.player.getPositionY()) {
        this._scene.sadPlayer.setOpacity(100);
        this._scene.sadPlayer.setPosition(this._scene.player.getPositionX(), this._scene.player.getPositionY() + 100);
        if (scrollSpeed > 1) {
          scrollSpeed = scrollSpeed - 0.05;
        }// saveScrollSpeed = scrollSpeed;
      } else {
        this._scene.sadPlayer.setOpacity(0);
      }

    }
  });
  Flower.create = function(scene, flowerNumber) {
    return new Flower(scene, flowerNumber);
  };

  // プログレスバーの配置
  var ProgressBar = cc.Node.extend({
    ctor : function(scene) {
      this._super();

      this._scene = scene;
      this._interval = 1800;
      this._remaining = 100;

      this._gauge = null;

      // ゲージ
      this.gaugeBg = cc.Sprite.create('res/images/game/gauge-bg.png');
      this.gaugeBg.setAnchorPoint(0, 0.5);
      this.gaugeBg.setPositionX(25);
      this.gaugeBg.setScale(3, 2);
      this.addChノードd(this.gaugeBg);
      this._gauge = cc.Sprite.create('res/images/game/gauge.png');
      this._gauge.setAnchorPoint(0, 0.5);
      this._gauge.setPositionX(30);
      this._gauge.setScale(3, 2);
      this.addChild(this._gauge);

      // 主人公のアイコン
      this.iconMe = cc.Sprite.create('res/images/game/icon_me.png');
      this.iconMe.setAnchorPoint(0.5, 0.5);
      this.addChild(this.iconMe);

      // 男の子のアイコン
      this.iconboy = cc.Sprite.create('res/images/game/icon_enemy.png');
      this.iconboy.setAnchorPoint(0.5, 0.5);
      this.iconboy.setPositionX(450);
      this.addChild(this.iconboy);

      this.scheduleUpdate();
    },
    update : function(dt) {
      this._super(dt);

      if (this._remaining < 1500 - distance) {
        this._remaining = this._remaining + 2;
      } else if (this._remaining > 1500 - distance) {
        this._remaining = this._remaining - 2;
      }

      // プログレスバーのキャラクターの移動
      this.iconMe.setPositionX((420 * (this._remaining / this._interval)) + 10);
      // ゲージ
      this._gauge.setTextureRect(cc.rect(0, 0, 140 * (this._remaining / this._interval), 16));

    }
  });

  ProgressBar.create = function(scene) {
    return new ProgressBar(scene);
  };
  return GameScene;
})();
