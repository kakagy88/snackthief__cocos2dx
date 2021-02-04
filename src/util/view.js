(function() {
  'use strict';

  var view = {
    // node配下のView一覧を取得。
    getChildrenRecursive : function(node) {
      const array = [];
      array.push(node);
      node.getChildren()
        .map(child => util.view.getChildrenRecursive(child))
        .forEach(children => Array.prototype.push.apply(array, children));
      return array;
    },
    // 渡されたオブジェクトに、node内のViewの名前と等しいメンバ変数が存在すれば、そのViewをメンバ変数に割り当てる。
    // また、渡されたオブジェクトに、node内のViewの名前の前にonClickをつけたメソッドが存在すれば、そのViewのaddTouchEventListenerでそのメソッドを呼ぶように設定する。
    // 上記の名前の比較は、メンバ変数、メソッドの方は_のプレフィックス付きのものも許容する。
    // オブジェクト、メソッドともに配列にも対応。views = []としておけば、views[0], views[1]という名前のViewを配列に割り当てる。onClickHogeButtonsのメソッドを定義しておけばhogeButtons[0], hogeButtons[1]のクリック時に呼び出され引数として0, 1が渡される。
    injectViewsAndListeners : function(viewTarget, listenerTarget, node) {
      const children = util.view.getChildrenRecursive(node);

      // View -> メンバ変数への割り当て、onClickメソッドへの対応
      children.forEach(view => {

        if (view.getName().length > 0) {
          // 判定する名前、単体か配列か、配列の場合のindexを取得。
          var [name, isArray, index] = (function() {
            var startBracketIndex = view.getName().lastIndexOf('[');
            var endBracketIndex = view.getName().lastIndexOf(']');
            var isArray = startBracketIndex >= 0 && endBracketIndex >= 0;
            var name = (function() {
              if (isArray) {
                return view.getName().slice(0, startBracketIndex);
              } else {
                return view.getName();
              }
            })();
            var index = 0;
            if (isArray) {
              index = Number.parseInt(view.getName().slice(startBracketIndex + 1, endBracketIndex));
            }
            return [name, isArray, index];
          })();

          // メンバ変数への割り当て
          var findMemberNames = [name, '_' + name];
          findMemberNames.forEach(findMemberName => {
            if (viewTarget[findMemberName] !== undefined) {
              if (isArray) {
                viewTarget[findMemberName][index] = view;
              } else {
                viewTarget[findMemberName] = view;
              }
            }
          });

          // onClickメソッドへの対応
          if (view instanceof ccui.Button) {
            var upperCasedName = name[0].toUpperCase() + name.slice(1);
            var onClickMethodName = ['onClick' + upperCasedName, '_onClick' + upperCasedName]
              .find(name => listenerTarget[name] !== undefined);
            if (onClickMethodName != null) {
              view.addTouchEventListener(function(sender, type) {
                if (type === ccui.Widget.TOUCH_ENDED) {
                  if (isArray) {
                    listenerTarget[onClickMethodName].call(listenerTarget, index);
                  } else {
                    listenerTarget[onClickMethodName].call(listenerTarget);
                  }
                }
              });
            }
          }
        }
      });
    },
    injectComponent : function(node) {
      const children = util.view.getChildrenRecursive(node);

      // View -> UserDataに設定されているComponentの追加
      children.forEach(view => {
        // Componentへの対応
        var createCode = view.getComponent('ComExtensionData').getCustomProperty();
        if (createCode != null && createCode !== '') {
          var component = eval(createCode);
          view.addComponent(component);
        }
      });
    },
    // 全てのViewを突っ込んだオブジェクトを返す。必要ないViewもメンバとして入ってしまうので使い方に注意。
    views2Object : function(node) {
      const children = util.view.getChildrenRecursive(node);
      var ret = {};
      children.forEach(child => {
        ret[child.getName()] = child;
      });
      return ret;
    },
    // ボタンに拡大縮小のアニメーションをつける
    setClickCallbackWithScaleAnimation : function(button, node, callback) {
      cc.log('setClickCallbackWithScaleAnimation');
      if (button != null) {
        button.addTouchEventListener(function(sender, type) {
          var duration = 0.0167 * 2;
          if (type === ccui.Widget.TOUCH_BEGAN) {
            node.runAction(cc.ScaleTo.create(duration, 1.2));
          } else if (type === ccui.Widget.TOUCH_ENDED || type === ccui.Widget.TOUCH_CANCELED) {
            node.runAction(cc.ScaleTo.create(duration, 1.0));
          }
          if (type === ccui.Widget.TOUCH_ENDED) {
            if (callback != null) {
              node.runAction(cc.Sequence.create(
                cc.DelayTime.create(duration),
                cc.CallFunc.create(() => callback())
              ));
            }
          }
        });
      }
    }
  };
  util.view = view;
})();
