#include "mainwindow.h"

#include <iostream>
#include <QDebug>
#include <QQmlContext>
#include <QQuickItem>
#include <QtPositioning>
#include <QQmlProperty>

#include "rocketdatareceiver.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    this->setWindowTitle(QString("Zenith"));
//    this->setUnifiedTitleAndToolBarOnMac(true);

    this->menuBar = new QMenuBar(0);
    this->setMenuBar(menuBar);

    this->prefAction = new QAction();
    this->prefAction->setText("Preferences");
    this->prefAction->setMenuRole(QAction::MenuRole::PreferencesRole);
    connect(this->prefAction, &QAction::triggered, this, &MainWindow::ShowPreferences);
    this->menu = new QMenu(0);
    this->menuBar->addMenu(this->menu);

    this->menu->addAction(this->prefAction);

    // Toolbar
    this->toolbar = new QToolBar();
    this->toolbar->setMovable(false);
    this->toolbar->setFloatable(false);
    this->toolbar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

    // Play/Stop action
    this->playStopAction = new QAction();
    this->playStopAction->setIcon(QIcon(":/play_arrow-24px.svg"));
    this->playStopAction->setText("Collect");
    connect(this->playStopAction, &QAction::triggered, this, &MainWindow::TogglePlayStop);

    this->toolbar->addAction(this->playStopAction);


    this->addToolBar(this->toolbar);

    this->mapView = new Map;
    connect(this->mapView, &Map::coordinatesChanged, this, &MainWindow::UpdateMap);
    this->setCentralWidget(this->mapView);

    this->mapView->addMarker(QGeoCoordinate(0,0));


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
    this->statusBar = new QStatusBar();

    this->currentCoordinatesLabel = new QLabel(QString("---"));
    this->statusBar->addWidget(currentCoordinatesLabel);

    this->connectedToSerialLabel = new QLabel(QString("Connected to serial /dev/tty0"));
    this->statusBar->addPermanentWidget(connectedToSerialLabel);

    this->setStatusBar(statusBar);

    this->showMaximized();


    // Set up serial


    this->rocketDataReciever = new RocketDataReceiver(&serialPort);

    connect(this->rocketDataReciever, &RocketDataReceiver::rocketDataUpdated, this, &MainWindow::UpdateRocketData);

    this->UpdatePrefs();
}

void MainWindow::UpdateRocketData(RocketData updatedData) {
    this->latItem->setText(1, QString("owo"));
    this->longItem->setText(1, QString("uwu"));
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
        component_payloadBatteryItem->setIcon(0, QIcon(":/wifi-24px.svg"));

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

void MainWindow::ShowPreferences() {
    SettingsWindow* beep = new SettingsWindow((QWidget*)this);
    beep->show();
}

void MainWindow::TogglePlayStop() {
    this->mapView->setHomeCoordinates(QGeoCoordinate(0,0));
    this->mapView->setRocketCoordinates(QGeoCoordinate(20,40));

    QSettings settings;
    this->serialPort.setPortName(settings.value("serial/port", "").toString());
    this->serialPort.setBaudRate(settings.value("serial/baud", 9600).toInt());
    qDebug() << this->serialPort.baudRate();

    if (this->serialPort.open(QIODevice::ReadOnly)) {
//        qDebug() << serialPort.errorString();
    }
}

void MainWindow::UpdateMap(QGeoCoordinate coords) {
//    qDebug() << coords;

//    this->currentCoordinatesLabel->setText(QString::number(coords.latitude()) + " " + QString::number(coords.longitude()));
//    QApplication::processEvents();
}


void MainWindow::UpdatePrefs() {
    QSettings settings;
    this->mapView->setHomeCoordinates(QGeoCoordinate(settings.value("location/lat", "0").toDouble(), settings.value("location/long", "0").toDouble()));
}


MainWindow::~MainWindow()
{
    qDebug() << "WINGKSKDKSKWKIWID";
}

