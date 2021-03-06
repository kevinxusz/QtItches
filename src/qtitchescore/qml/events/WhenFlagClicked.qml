import QtItches.Core 1.0
import QtQml 2.2

Block {
    category: Block.EventsCategory
    connectors: Block.BottomConnector

    ConstantParameter {
        string: QT_TR_NOOP("when green flag clicked")
    }

    Connections {
        target: project

        onFlagClicked: {
            script.stop();
            script.run();
        }
    }

    function run() {
        finished();
    }
}
