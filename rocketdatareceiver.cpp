#include "rocketdatareceiver.h"

#include "RocketData.h"

#include <QDebug>

RocketDataReceiver::RocketDataReceiver(QSerialPort* port, QObject *parent) : QObject(parent)
{
    this->_port = port;
    connect(port, &QSerialPort::readyRead, this, &RocketDataReceiver::handleReadyRead);
    connect(port, &QSerialPort::errorOccurred, this, &RocketDataReceiver::handleError);
    qDebug() << "RocketDataReceiver initialized";
}

void RocketDataReceiver::handleReadyRead() {

}

void RocketDataReceiver::handleError() {
    qDebug() << this->_port->errorString();
}
