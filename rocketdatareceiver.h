#ifndef ROCKETDATARECEIVER_H
#define ROCKETDATARECEIVER_H

#include <QObject>
#include <QSerialPort>

class RocketDataReceiver : public QObject
{
    Q_OBJECT
    QSerialPort* _port;
    void handleReadyRead();
    void handleError();

public:
    explicit RocketDataReceiver(QSerialPort* port, QObject *parent = nullptr);

signals:

};

#endif // ROCKETDATARECEIVER_H
