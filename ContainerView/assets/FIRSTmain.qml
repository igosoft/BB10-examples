// Default empty project template
import bb.cascades 1.0

Page {
    Container {
        id: mainCon
        property int containerWidth: mainCon.maxWidth
        layout: AbsoluteLayout {
        }
        background: Color.create("#E0E0E0")
        Container {
            id: con0
            background: Color.create("#FF00FF")
            layoutProperties: AbsoluteLayoutProperties {
                id: con0Pos
                positionX: - 768
                positionY: 0
            }
            preferredWidth: 768
            preferredHeight: 200
        }
        Container {
            id: con1
            background: Color.create("#FFFFFF")
            layoutProperties: AbsoluteLayoutProperties {
                id: con1Pos
                positionX: 0
                positionY: 0
            }
            preferredWidth: 768
            preferredHeight: 200
        }
        Container {
            id: con2
            background: Color.create("#000000")
            layoutProperties: AbsoluteLayoutProperties {
                id: con2Pos
                positionX: 768
                positionY: 0
            }
            preferredWidth: 768
            preferredHeight: 200
        }
        Label {
            id: label
            text: String(mainCon.containerWidth)
            layoutProperties: AbsoluteLayoutProperties {
                positionX: 0
                positionY: 300
            }
        }
        property int latestTouchXPos
        property int startTouchXPos
        function showContainer(index) { //0 - left, 1 - middle, 2 - right
            var cos1Pos = containerWidth * (- index + 1)
            con0Pos.positionX = cos1Pos - containerWidth
            con1Pos.positionX = cos1Pos
            con2Pos.positionX = cos1Pos + containerWidth
        }
        onTouch: {
            if (event.isDown()) { // Touch
                latestTouchXPos = event.windowX
                startTouchXPos = event.windowX
            }
            if (event.isUp()) { // Release
                if (con1Pos.positionX > containerWidth / 2) {
                    showContainer(0)
                    return
                }
                if (con1Pos.positionX < - containerWidth / 2 && con1Pos.positionX < 0) {
                    showContainer(2)
                    return
                }
                showContainer(1)
            }
            if (event.isMove()) { // Moving
                var shift = event.windowX - latestTouchXPos
                if (shift > 0) { // Shift to right, check right boundaries
                    if (con1Pos.positionX + shift <= containerWidth) {
                        con0Pos.positionX += shift
                        con1Pos.positionX += shift
                        con2Pos.positionX += shift
                    }
                } else { // Shift to left, check left boundaries
                    if (con1Pos.positionX + shift >= - containerWidth) {
                        con0Pos.positionX += shift
                        con1Pos.positionX += shift
                        con2Pos.positionX += shift
                    }
                }
                latestTouchXPos = event.windowX
            }
        }
    }
}
