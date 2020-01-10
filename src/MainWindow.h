#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

#include "EncryptKeyGenerator.h"
#include "AccessKeyGenerator.h"

class DataModel;

class QLineEdit;
class QCheckBox;
class QComboBox;
class QDateTimeEdit;
class QTextEdit;
class QPushButton;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initInterface();
    void generateAccessKey();
    void setEncryptKey();
    void saveKeysToFile();

private:
    std::shared_ptr<DataModel> model = nullptr;
    std::unique_ptr<EncryptKeyGenerator> encryptCoder = nullptr;
    std::unique_ptr<AccessKeyGenerator> accessCoder = nullptr;

    QLineEdit* login = nullptr;
    QLineEdit* password = nullptr;
    QCheckBox *authDisable = nullptr;
    QComboBox *userType = nullptr;
    QDateTimeEdit *ttl = nullptr;
    QCheckBox *ttlDisable = nullptr;
    QLineEdit *encryptKey = nullptr;
    QPushButton *generateAccessKeyBtn = nullptr;
    QTextEdit *keyField = nullptr;
    QLabel *messageLbl = nullptr;
};
#endif // MAINWINDOW_H
