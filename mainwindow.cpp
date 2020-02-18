#include "mainwindow.h"

#include <iostream>

#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    this->setWindowTitle(QString("Zenith"));


    mapView = new QQuickWidget;
    mapView->setSource(QUrl("qrc:/map.qml"));
    mapView->setResizeMode(QQuickWidget::SizeRootObjectToView);

    this->setCentralWidget(mapView);


    // Rocket data
    rocketInfoDockWidget = new QDockWidget(QString("Rocket"));

    rocketTreeWidget = new QTreeWidget();
    rocketTreeWidget->setHeaderLabels({"", ""});
    rocketTreeWidget->setColumnCount(2);
    rocketTreeWidget->setColumnWidth(0, 200);

    BuildRocketTreeWidgetItems(rocketTreeWidget);

    rocketInfoDockWidget->setWidget(rocketTreeWidget);

    // Payload data
    payloadInfoDockWidget = new QDockWidget(QString("Payload"));
    payloadTreeWidget = new QTreeWidget();
    payloadTreeWidget->setHeaderHidden(true);

    payloadInfoDockWidget->setWidget(payloadTreeWidget);


    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, rocketInfoDockWidget);
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, payloadInfoDockWidget);

    // Set up footer
    statusBar = new QStatusBar();

    lastUpdatedLabel = new QLabel(QString("Last data received 3 seconds ago"));
    statusBar->addWidget(lastUpdatedLabel);

    connectedToSerialLabel = new QLabel(QString("Connected to serial /dev/tty0"));
    statusBar->addPermanentWidget(connectedToSerialLabel);

    this->setStatusBar(statusBar);

    this->showMaximized();


}

void MainWindow::BuildRocketTreeWidgetItems(QTreeWidget* wid) {
    // general
    generalCategory = new QTreeWidgetItem(wid);
    generalCategory->setText(0, QString("General"));

    // latitude
    latItem = new QTreeWidgetItem(generalCategory);
    latItem->setText(0, QString("Latitude"));
    latItem->setText(1, QString("120°"));

    // longitude
    longItem = new QTreeWidgetItem(generalCategory);
    longItem->setText(0, QString("Longitude"));
    longItem->setText(1, QString("32°"));

    // altitude
    altItem = new QTreeWidgetItem(generalCategory);
    altItem->setText(0, QString("Altitude"));
    altItem->setText(1, QString("300 m"));

    // heading
    headingItem = new QTreeWidgetItem(generalCategory);
    headingItem->setText(0, QString("Heading"));
    headingItem->setText(1, QString("120°"));

    // distance
    distItem = new QTreeWidgetItem(generalCategory);
    distItem->setText(0, QString("Distance"));
    distItem->setText(1, QString("0.8 km"));

    // bearing
    bearingItem = new QTreeWidgetItem(generalCategory);
    bearingItem->setText(0, QString("Bearing"));
    bearingItem->setText(1, QString("120°"));


    ////////////////
    // Components //
    ////////////////
    componentCategory = new QTreeWidgetItem(wid);
    componentCategory->setText(0, QString("Components"));

    // payload
    component_payloadItem = new QTreeWidgetItem(componentCategory);
    component_payloadItem->setText(0, QString("Payload"));

        // payload - battery
        component_payloadBatteryItem = new QTreeWidgetItem(component_payloadItem);
        component_payloadBatteryItem->setText(0, QString("Battery"));
        component_payloadBatteryItem->setText(1, QString("95%"));
//        component_payloadBatteryItem->setIcon(0, QIcon(":/Battery.png"));

        // payload - temperature
        component_payloadTempItem = new QTreeWidgetItem(component_payloadItem);
        component_payloadTempItem->setText(0, QString("Temperature"));
        component_payloadTempItem->setText(1, QString("102°C"));

    // main para
    component_mainParaItem = new QTreeWidgetItem(componentCategory);
    component_mainParaItem->setText(0, QString("Main Parachute"));

    // avionics
    component_avionicsItem = new QTreeWidgetItem(componentCategory);
    component_avionicsItem->setText(0, QString("Avionics"));

        // avionics - battery
        component_avionicsBatteryItem = new QTreeWidgetItem(component_avionicsItem);
        component_avionicsBatteryItem->setText(0, QString("Battery"));
        component_avionicsBatteryItem->setText(1, QString("95%"));

        // avionics - temperature
        component_avionicsTempItem = new QTreeWidgetItem(component_avionicsItem);
        component_avionicsTempItem->setText(0, QString("Temperature"));
        component_avionicsTempItem->setText(1, QString("102°C"));

    // drogue para
    component_drogueParaItem = new QTreeWidgetItem(componentCategory);
    component_drogueParaItem->setText(0, QString("Drogue Parachute"));

    // airbrakes
    component_airbrakesItem = new QTreeWidgetItem(componentCategory);
    component_airbrakesItem->setText(0, QString("Airbrakes"));

        // airbrakes - battery
        component_airbrakesBatteryItem = new QTreeWidgetItem(component_airbrakesItem);
        component_airbrakesBatteryItem->setText(0, QString("Battery"));
        component_airbrakesBatteryItem->setText(1, QString("95%"));

        // airbrakes - temperature
        component_airbrakesTempItem = new QTreeWidgetItem(component_airbrakesItem);
        component_airbrakesTempItem->setText(0, QString("Temperature"));
        component_airbrakesTempItem->setText(1, QString("102°C"));
}

MainWindow::~MainWindow()
{

}

