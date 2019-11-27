#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DataModel;

class QLineEdit;
class QCheckBox;
class QComboBox;
class QDateTimeEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initInterface();
private:
    DataModel *model = nullptr;

    QLineEdit* login = nullptr;
    QLineEdit* password = nullptr;
    QCheckBox *authDisable = nullptr;
    QComboBox *userType = nullptr;
    QDateTimeEdit *ttl = nullptr;
    QCheckBox *ttlDisable = nullptr;
};
#endif // MAINWINDOW_H
