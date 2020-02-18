#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qt>
#include <QLabel>
#include <QDockWidget>
#include <QStatusBar>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <QQuickWidget>
class MainWindow : public QMainWindow
{
    Q_OBJECT
    QStatusBar* statusBar;
    QLabel* lastUpdatedLabel;
    QLabel* connectedToSerialLabel;

    QQuickWidget* mapView;

    QDockWidget* rocketInfoDockWidget;
    QTreeWidget* rocketTreeWidget;

    QDockWidget* payloadInfoDockWidget;
    QTreeWidget* payloadTreeWidget;


    QTreeWidgetItem* generalCategory;
    QTreeWidgetItem* latItem;
    QTreeWidgetItem* longItem;
    QTreeWidgetItem* altItem;
    QTreeWidgetItem* headingItem;
    QTreeWidgetItem* distItem;
    QTreeWidgetItem* bearingItem;

    QTreeWidgetItem* componentCategory;

    QTreeWidgetItem* component_payloadItem;
    QTreeWidgetItem* component_payloadBatteryItem;
    QTreeWidgetItem* component_payloadTempItem;

    QTreeWidgetItem* component_mainParaItem;

    QTreeWidgetItem* component_avionicsItem;
    QTreeWidgetItem* component_avionicsBatteryItem;
    QTreeWidgetItem* component_avionicsTempItem;

    QTreeWidgetItem* component_drogueParaItem;

    QTreeWidgetItem* component_airbrakesItem;
    QTreeWidgetItem* component_airbrakesBatteryItem;
    QTreeWidgetItem* component_airbrakesTempItem;


public:
    MainWindow(QWidget *parent = nullptr);
    void BuildRocketTreeWidgetItems(QTreeWidget* wid);
    void ShowPreferences();
    ~MainWindow();
};
#endif // MAINWINDOW_H
