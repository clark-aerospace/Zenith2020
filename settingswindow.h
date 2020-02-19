#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include <QtWidgets>

class SettingsWindow : public QMainWindow
{
    Q_OBJECT

    QAction* serialAction;
    QAction* unitsAction;
    QAction* locationAction;


    QStackedWidget* stack;

    QComboBox* serialPort;
    QComboBox* baudRate;

    QWidget* serialWidget;

    QComboBox* units;
    QWidget* unitsWidget;

    QLineEdit* latEntry;
    QLineEdit* longEntry;
    QWidget* locationWidget;


public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    void SetSerialTab();
    void SetUnitsTab();
    void SetLocationTab();

signals:

};

#endif // SETTINGSWINDOW_H
