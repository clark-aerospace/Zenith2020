/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

Item {
    width: 1920
    height: 1000
    visible: true

    Plugin {
        id: mapPlugin
        name: "mapboxgl" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        PluginParameter {
            name: "mapboxgl.mapping.additional_style_urls"
            value: "mapbox://styles/mapbox/streets-v9"
//            value: "mapbox://styles/mapbox/satellite-streets-v9"
        }

        // PluginParameter {
        //     name:
        //     value:
        // }
    }

    Map {
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(45.6342791, -122.6516062)
        zoomLevel: 16
        objectName: "map"
        id: map

        MapItemView {
            id: iconContainer
            objectName: "iconContainer"

            MapQuickItem {
                id: homeLocation
                objectName: "homeLocation"

                sourceItem: Image {
                    id: testmarker
                    source: "qrc:///home-24px.svg"

                    width: 40
                    height: 40
                }

                coordinate : QtPositioning.coordinate(45.6342791, -122.6516062)
                anchorPoint.x: testmarker.width / 2
                anchorPoint.y: testmarker.height
            }

            MapQuickItem {
                id: rocketLocation
                objectName: "rocketLocation"

                sourceItem: Image {
                    id: bomp
                    source: "qrc:///my_location-24px.svg"

                    width: 40
                    height: 40
                }

                coordinate : QtPositioning.coordinate(43.6342791, -127.6516062)
                anchorPoint.x: bomp.width / 2
                anchorPoint.y: bomp.height
            }
        }


    }
}
