import bb.cascades 1.0

Container {
    objectName: "manConatiner"
    layout: DockLayout {
    }
    Label {
        objectName: "label"
        verticalAlignment: VerticalAlignment.Top
        horizontalAlignment: HorizontalAlignment.Center
        textStyle.fontSize: FontSize.XXLarge
    }
    ImageView {
        objectName: "imageView"
        imageSource: "asset:///images/picture3.png"
        horizontalAlignment: HorizontalAlignment.Center
        verticalAlignment: VerticalAlignment.Center
    }
}
