#include "map.h"

Map::Map(QWidget *parent) : QQuickWidget(parent)
{
    this->setSource(QUrl("qrc:/map.qml"));
    this->setResizeMode(QQuickWidget::SizeRootObjectToView);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setClearColor(Qt::white);

    this->map = this->rootObject()->findChild<QObject*>("map");

    this->lastCoords = this->coordinates();
}

void Map::paintEvent(QPaintEvent *event) {
    if (this->coordinates().distanceTo(this->lastCoords) >= 100) {
        emit coordinatesChanged(this->coordinates());
        this->lastCoords = this->coordinates();
    }


}

bool Map::addMarker(QGeoCoordinate coords) {
    QQmlComponent newMarker(this->engine(), QUrl("qrc:/map_marker.qml"));
    qDebug() << newMarker.status();
    qDebug() << newMarker.errorString();

    QObject* newMarkerObject = newMarker.create();


    QQuickItem* item = (QQuickItem*)newMarkerObject;
    item->setParentItem((QQuickItem*)this->map->findChild<QObject*>("itemContainer"));
    item->setParent(this->map->findChild<QObject*>("itemContainer"));
    item->setVisible(true);

    qDebug() << item->parentItem();
    qDebug() << item->parent();

    return true;
}

QGeoCoordinate Map::coordinates() {
        return this->map->property("center").value<QGeoCoordinate>();
}

bool Map::setCoordinates(QGeoCoordinate coords) {
    return this->map->setProperty("center", QVariant::fromValue(coords));
}
