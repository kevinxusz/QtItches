import QtItches.Core 1.0

Block {
    property alias text: textParameter.string

    category: Block.LooksCategory
    parameters: [
        ConstantParameter { string: qsTr("think:") },
        StringParameter { id: textParameter }
    ]

    function run() {
        actor.think(text);
        finished();
    }
}