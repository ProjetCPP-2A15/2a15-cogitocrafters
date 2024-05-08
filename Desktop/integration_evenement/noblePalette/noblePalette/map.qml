import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.2

Rectangle {
    id: window
    width: 800
    height: 600
    signal infoTextChanged(string info) // Déclaration du signal



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
                // Appel de la fonction pour ajouter un marqueur avec les coordonnées du clic
                addMarker(mouseCoordinate.latitude, mouseCoordinate.longitude)
            }
        }
    }

    function addMarker(lat, lng) {
        var marker = comMarker.createObject(window, {
            coordinate: QtPositioning.coordinate(lat, lng)
        })
        mapView.addMapItem(marker)
        // Émettre le signal avec le nom et les coordonnées de la position
        var name = "Nom du lieu"; // Remplacez par le nom réel de la position si vous avez ces données
        infoTextChanged( lat + "," + lng);
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
