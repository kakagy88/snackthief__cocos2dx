(function() {
  'use strict';

  var score = {
    initializeScore : function(override) {
      Object.keys(DifficultyType).forEach(key => {
        var difficultyType = DifficultyType[key];
        var key = this._getKey(difficultyType);

        if (!override && cc.sys.localStorage.getItem(key) != null) {
          return;
        }
        cc.sys.localStorage.setItem(key, 999.9);
      });
    },
    getScore : function(difficultyType) {
      var key = this._getKey(difficultyType);
      var score = cc.sys.localStorage.getItem(key);
      return (score == null) ? 0 : parseFloat(score).toFixed(1);
    },
    updateScore : function(difficultyType, score) {
      var key = this._getKey(difficultyType);
      var oldScore = cc.sys.localStorage.getItem(key);
      if (oldScore == null || oldScore > score) {
        cc.sys.localStorage.setItem(key, score);
      }
    },
    _getKey : function(difficultyType) {
      return 'game_score_difficulty_' + difficultyType;
    }
  };
  util.score = score;
})();
