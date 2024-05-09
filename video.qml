import QtQuick 2.0
import QtMultimedia 5.0

Rectangle {
    width: 640
    height: 480

    Video {
        id: videoItem
        width: parent.width
        height: parent.height
        source: "C:/Users/meddh/Desktop/0507.mp4"
        autoPlay: true
        muted: false
    }
}
