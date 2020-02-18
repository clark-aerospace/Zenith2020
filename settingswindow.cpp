#include "settingswindow.h"

#include <QtWidgets>
#include <QSerialPortInfo>
#include <QActionGroup>
#include "tintableicon.h"

SettingsWindow::SettingsWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("Preferences");

    QToolBar* toolbar = new QToolBar;
    toolbar->setMovable(false);
    toolbar->setFloatable(false);
    toolbar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

    QAction* serialAction = new QAction;
    TintableIcon* serialIcon = new TintableIcon(QString(":/wifi-24px.svg"));
//    serialIcon->setTintColor(QColor("white"));
    serialIcon->setIsMask(true);
    serialAction->setIcon(*serialIcon);
    serialAction->setText("Serial");
    serialAction->setCheckable(true);


    QAction* unitsAction = new QAction;
    TintableIcon* unitsIcon = new TintableIcon(QString(":/straighten-24px.svg"));
    unitsIcon->setIsMask(true);
    unitsAction->setIcon(*unitsIcon);
    unitsAction->setText("Units");
    unitsAction->setCheckable(true);

    QActionGroup* ac = new QActionGroup(this);
    ac->addAction(serialAction);
    ac->addAction(unitsAction);
    serialAction->setChecked(true);

    toolbar->addAction(serialAction);
    toolbar->addAction(unitsAction);

    this->addToolBar(toolbar);

    this->setUnifiedTitleAndToolBarOnMac(true);


    // serial stuff
    QComboBox* serialPort = new QComboBox;
    QComboBox* baudRate = new QComboBox;

    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

    for (int i = 0; i < availablePorts.count(); i++) {
        serialPort->addItem(availablePorts.at(i).portName());
    }

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



    QWidget* serialWidget = new QWidget;
    serialWidget->setLayout(serialLayout);
    serialWidget->setSizePolicy(po);

    // all together
    QStackedWidget* stack = new QStackedWidget;
    stack->addWidget(serialWidget);

    this->setFixedSize(500,350);
    this->setCentralWidget(stack);
}
