#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum UserTypes
    {
        User = 0,
        Admin,
        God
    };
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

};
#endif // MAINWINDOW_H
