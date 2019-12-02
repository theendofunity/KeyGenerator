#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class DataModel;
class AccessKeyGenerator;
class EncryptKeyGenerator;
class Decoder;

class QLineEdit;
class QCheckBox;
class QComboBox;
class QDateTimeEdit;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initInterface();
    void generateAccessCode();
    void saveKeysToFile();

private:
    std::shared_ptr<DataModel> model = nullptr;
    EncryptKeyGenerator *encryptCoder = nullptr;
    AccessKeyGenerator *accessCoder = nullptr;
    Decoder *decoder = nullptr;

    QLineEdit* login = nullptr;
    QLineEdit* password = nullptr;
    QCheckBox *authDisable = nullptr;
    QComboBox *userType = nullptr;
    QDateTimeEdit *ttl = nullptr;
    QCheckBox *ttlDisable = nullptr;
    QLineEdit *encryptKey = nullptr;
    QTextEdit *keyField = nullptr;
};
#endif // MAINWINDOW_H
