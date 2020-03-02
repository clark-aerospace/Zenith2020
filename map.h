#ifndef MAP_H
#define MAP_H

#include <QtWidgets>
#include <QQuickWidget>
#include <QDebug>
#include <QQmlContext>
#include <QQuickItem>
#include <QtPositioning>
#include <QQmlProperty>
#include <QQuickView>

class Map : public QQuickWidget
{
    Q_OBJECT

    QGeoCoordinate lastCoords;

public:
    explicit Map(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    bool addMarker(QGeoCoordinate coords);
    QGeoCoordinate coordinates();
    bool setCoordinates(QGeoCoordinate coords);

    bool setHomeCoordinates(QGeoCoordinate coords);
    bool setRocketCoordinates(QGeoCoordinate coords);

    QObject* map;

signals:
    void coordinatesChanged(QGeoCoordinate coords);
};

#endif // MAP_H
