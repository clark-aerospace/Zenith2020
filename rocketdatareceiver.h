#ifndef ROCKETDATARECEIVER_H
#define ROCKETDATARECEIVER_H

#include <QObject>
#include <QSerialPort>

#include "RocketData.h"

class RocketDataReceiver : public QObject
{
    Q_OBJECT
    QSerialPort* _port;
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);

    RocketData currentRocketData;

public:
    explicit RocketDataReceiver(QSerialPort* port, QObject *parent = nullptr);

signals:
    void rocketDataUpdated(RocketData updated);
};

#endif // ROCKETDATARECEIVER_H
