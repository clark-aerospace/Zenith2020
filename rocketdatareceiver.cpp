#include "rocketdatareceiver.h"

#include <QtWidgets>
#include <QDebug>

RocketDataReceiver::RocketDataReceiver(QSerialPort* port, QObject *parent) : QObject(parent)
{
    this->_port = port;
    connect(port, &QSerialPort::readyRead, this, &RocketDataReceiver::handleReadyRead);
    connect(port, &QSerialPort::errorOccurred, this, &RocketDataReceiver::handleError);
    qDebug() << "RocketDataReceiver initialized";
}

void RocketDataReceiver::handleReadyRead() {

    // once we got the stuff
    emit rocketDataUpdated(currentRocketData);
}

void RocketDataReceiver::handleError(QSerialPort::SerialPortError error) {
//    qDebug() << "handleError() for serial port";
//    qDebug() << this->_port->errorString();

    QMessageBox* errorMsgBox = new QMessageBox;

    errorMsgBox->setIcon(QMessageBox::Critical);
    errorMsgBox->setText(QString("The serial port \"%1\" could not be opened.").arg(this->_port->portName()));
    errorMsgBox->setInformativeText(QString("Error: %1").arg(error));
    errorMsgBox->open();
}
