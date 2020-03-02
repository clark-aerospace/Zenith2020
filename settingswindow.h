#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include <QtWidgets>

class SettingsWindow : public QMainWindow
{
    Q_OBJECT

    QWidget* mainWindow;

    QAction* serialAction;
    QAction* unitsAction;
    QAction* locationAction;


    QStackedWidget* stack;

    QComboBox* serialPort;
    QComboBox* baudRate;

    QWidget* serialWidget;

    QComboBox* distUnits;
    QComboBox* tempUnits;

    QWidget* unitsWidget;

    QLineEdit* latEntry;
    QLineEdit* longEntry;
    QWidget* locationWidget;


public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    void SetSerialTab();
    void SetUnitsTab();
    void SetLocationTab();
    void closeEvent(QCloseEvent* ev);

signals:

};

#endif // SETTINGSWINDOW_H
