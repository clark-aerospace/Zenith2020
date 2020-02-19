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
    qDebug() << this->coordinates().distanceTo(this->lastCoords);

    if (this->coordinates().distanceTo(this->lastCoords) >= 100) {
        emit coordinatesChanged(this->coordinates());
        this->lastCoords = this->coordinates();
    }


}

QGeoCoordinate Map::coordinates() {
        return this->map->property("center").value<QGeoCoordinate>();
}

bool Map::setCoordinates(QGeoCoordinate coords) {
    return this->map->setProperty("center", QVariant::fromValue(coords));
}
