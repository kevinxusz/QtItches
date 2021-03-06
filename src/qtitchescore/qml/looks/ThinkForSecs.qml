import QtItches.Core 1.0
import QtQml 2.2

SpriteBlock {
    id: thinkForSecs

    property alias text: textParameter.value
    property alias seconds: secondsParameter.value

    category: Block.LooksCategory

    ConstantParameter { string: QT_TR_NOOP("think") }
    StringParameter { id: textParameter }
    ConstantParameter { string: QT_TR_NOOP("for") }
    NumberParameter { id: secondsParameter; decimals: 1; number: 5 }
    ConstantParameter { string: QT_TR_NOOP("secs") }

    function run() {
        sprite.think(text);
        timer.start();
    }

    function stop() {
        timer.stop();
        finished();
    }

    Timer {
        id: timer

        interval: secondsParameter.number * 1000
        repeat: false

        onTriggered: {
            sprite.think("");
            thinkForSecs.finished();
        }
    }
}
