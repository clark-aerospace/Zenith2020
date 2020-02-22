import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6
Item {
    MapQuickItem {
        id: startMarker

        sourceItem: Image {
            id: greenMarker
            source: "qrc:///wifi-24px.svg"

            width: 100
            height: 100
        }

        coordinate : QtPositioning.coordinate(45.600487, -122.665224)
        anchorPoint.x: greenMarker.width / 2
        anchorPoint.y: greenMarker.height
    }
}


