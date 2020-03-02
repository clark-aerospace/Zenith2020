#include "settingswindow.h"

#include <QSerialPortInfo>
#include <QActionGroup>
#include "tintableicon.h"
#include "mainwindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) : QMainWindow(parent)
{

//    this->parent = (MainWindow*)parent;
    this->setParent(parent);

    this->setWindowTitle("Preferences");

    QToolBar* toolbar = new QToolBar;
    toolbar->setMovable(false);
    toolbar->setFloatable(false);
    toolbar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

    this->serialAction = new QAction;
    TintableIcon* serialIcon = new TintableIcon(QString(":/wifi-24px.svg"));
//    serialIcon->setTintColor(QColor("white"));
    serialIcon->setIsMask(true);
    this->serialAction->setIcon(*serialIcon);
    this->serialAction->setText("Serial");
    this->serialAction->setCheckable(true);
    connect(this->serialAction, &QAction::triggered, this, &SettingsWindow::SetSerialTab);


    this->unitsAction = new QAction;
    TintableIcon* unitsIcon = new TintableIcon(QString(":/straighten-24px.svg"));
    unitsIcon->setIsMask(true);
    this->unitsAction->setIcon(*unitsIcon);
    this->unitsAction->setText("Units");
    this->unitsAction->setCheckable(true);
    connect(this->unitsAction, &QAction::triggered, this, &SettingsWindow::SetUnitsTab);


    this->locationAction = new QAction;
    TintableIcon* locationIcon = new TintableIcon(QString(":/my_location-24px.svg"));
    locationIcon->setIsMask(true);
    this->locationAction->setIcon(*locationIcon);
    this->locationAction->setText("Location");
    this->locationAction->setCheckable(true);
    connect(this->locationAction, &QAction::triggered, this, &SettingsWindow::SetLocationTab);

    QActionGroup* ac = new QActionGroup(this);
    ac->addAction(this->serialAction);
    ac->addAction(this->unitsAction);
    ac->addAction(this->locationAction);
    this->serialAction->setChecked(true);

    toolbar->addAction(this->serialAction);
    toolbar->addAction(this->unitsAction);
    toolbar->addAction(this->locationAction);

    this->addToolBar(toolbar);

    this->setUnifiedTitleAndToolBarOnMac(true);


    // serial stuff
    this->serialPort = new QComboBox;
    this->baudRate = new QComboBox;

    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

    for (int i = 0; i < availablePorts.count(); i++) {
        serialPort->addItem(availablePorts.at(i).portName());
    }

    this->baudRate->addItems({"1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200"});
    QFormLayout* serialLayout = new QFormLayout;
    serialLayout->addRow(new QLabel("Serial port"), serialPort);
    serialLayout->addRow(new QLabel("Baud rate"), baudRate);
    serialLayout->setFormAlignment(Qt::AlignLeft);
    serialLayout->setFieldGrowthPolicy(QFormLayout::FieldGrowthPolicy::AllNonFixedFieldsGrow);
    serialLayout->setSpacing(50);

    QSizePolicy po;
    po.setHorizontalPolicy(QSizePolicy::Maximum);
    po.setVerticalPolicy(QSizePolicy::Preferred);
    po.setVerticalStretch(1);
    po.setHorizontalStretch(1);

    this->serialWidget = new QWidget;
    serialWidget->setLayout(serialLayout);
    serialWidget->setSizePolicy(po);


    // units stuff
    this->distUnits = new QComboBox;
    this->distUnits->addItems({"Metric", "Imperial"});

    this->tempUnits = new QComboBox;
    this->tempUnits->addItems({"Celsius", "Kelvin", "Fahrenheit"});

    QFormLayout* unitsLayout = new QFormLayout;
    unitsLayout->addRow(new QLabel("Distance"), this->distUnits);
    unitsLayout->addRow(new QLabel("Temperature"), this->tempUnits);
    unitsLayout->setFormAlignment(Qt::AlignLeft);
    unitsLayout->setFieldGrowthPolicy(QFormLayout::FieldGrowthPolicy::AllNonFixedFieldsGrow);
    unitsLayout->setSpacing(50);

    this->unitsWidget = new QWidget;
    unitsWidget->setLayout(unitsLayout);
    unitsWidget->setSizePolicy(po);


    // location stuff
    this->latEntry = new QLineEdit;
    this->longEntry = new QLineEdit;

    QFormLayout* locationLayout = new QFormLayout;
    locationLayout->addRow(new QLabel("Latitutde"), latEntry);
    locationLayout->addRow(new QLabel("Longitude"), longEntry);

    locationLayout->setFormAlignment(Qt::AlignLeft);
    locationLayout->setFieldGrowthPolicy(QFormLayout::FieldGrowthPolicy::AllNonFixedFieldsGrow);
    locationLayout->setSpacing(50);

    this->locationWidget = new QWidget;
    this->locationWidget->setLayout(locationLayout);
    this->locationWidget->setSizePolicy(po);


    // all together
    this->stack = new QStackedWidget;
    this->stack->addWidget(this->serialWidget);
    this->stack->addWidget(this->unitsWidget);
    this->stack->addWidget(this->locationWidget);

    this->setFixedSize(500,350);
    this->setCentralWidget(stack);


    QSettings settings;
    qDebug() << settings.allKeys();
    if (settings.contains("serial/port")) this->serialPort->setCurrentText(settings.value("serial/port", "").toString());
    if (settings.contains("serial/baud")) this->baudRate->setCurrentText(settings.value("serial/baud", "9600").toString());
    if (settings.contains("units/dist")) this->distUnits->setCurrentText(settings.value("units/dist", "Metric").toString());
    if (settings.contains("units/temp")) this->tempUnits->setCurrentText(settings.value("units/temp", "Celsius").toString());
    if (settings.contains("location/lat")) this->latEntry->setText(settings.value("location/lat", 0).toString());
    if (settings.contains("location/long")) this->longEntry->setText(settings.value("location/long", 0).toString());
    else qDebug() << "no long";
}

void SettingsWindow::SetSerialTab() {
    this->stack->setCurrentIndex(0);
}

void SettingsWindow::SetUnitsTab() {
    this->stack->setCurrentIndex(1);
}

void SettingsWindow::SetLocationTab() {
    this->stack->setCurrentIndex(2);
}


void SettingsWindow::closeEvent(QCloseEvent* ev) {
    qDebug() << "close event";
    QSettings settings;
    settings.setValue("serial/port", this->serialPort->currentText());
    settings.setValue("serial/baud", this->baudRate->currentText().toInt());
    settings.setValue("units/dist", this->distUnits->currentText());
    settings.setValue("units/temp", this->tempUnits->currentText());
    settings.setValue("location/lat", this->latEntry->text().toDouble());
    settings.setValue("location/long", this->longEntry->text().toDouble());

    ((MainWindow*)(this->parent()))->UpdatePrefs();

    qDebug() << "closed";

}
