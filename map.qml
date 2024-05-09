import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.5

Rectangle {
    id: window
    width: 800
    height: 600
    signal infoTextChanged(string info) // Declaration of the signal

    property Component comMarker: mapMarker

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        id: mapView
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(oldLat, oldLng)
        zoomLevel: 15

        MouseArea {
            anchors.fill: parent
            onClicked: {
                var mouseCoordinate = mapView.toCoordinate(Qt.point(mouse.x, mouse.y))
                // Call the function to add a marker with the click coordinates
                addMarker(mouseCoordinate.latitude, mouseCoordinate.longitude)
            }
        }
    }

    function addMarker(lat, lng) {
        var marker = comMarker.createObject(window, {
            coordinate: QtPositioning.coordinate(lat, lng)
        })
        mapView.addMapItem(marker)
        // Emit the signal with the name and coordinates of the position
        var name = "Nom du lieu"; // Replace with the actual name of the location if you have this data
        infoTextChanged(lat + "," + lng);
    }

    Component {
        id: mapMarker
        MapQuickItem {
            id: markerImg
            anchorPoint.x: image.width / 4
            anchorPoint.y: image.height
            coordinate: position

            sourceItem: Image {
                id: image
                source: "http://maps.gstatic.com/mapfiles/ridefinder-images/mm_20_red.png"
            }
        }
    }
}
