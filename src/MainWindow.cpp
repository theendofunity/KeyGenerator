#include "MainWindow.h"

#include "QVBoxLayout"
#include "QLabel"
#include "QLineEdit"
#include "QCheckBox"
#include "QComboBox"
#include "QDateTimeEdit"
#include "QPushButton"
#include "QTextEdit"

#include "DataModel.h"
#include "ConvertTools.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include <Decoder.h>
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , model(std::make_shared<DataModel>(this))
    , encryptCoder(std::make_unique<EncryptKeyGenerator>(this))
    , accessCoder(std::make_unique<AccessKeyGenerator>(model, this))
{
    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainWidget->setLayout(mainLayout);
    mainWidget->setMinimumSize(500, 500);
    this->setCentralWidget(mainWidget);

    QGridLayout* dataLayout = new QGridLayout;
    dataLayout->setSpacing(10);
    dataLayout->setMargin(10);
    mainLayout->addLayout(dataLayout);

    //Логин и Пароль
    dataLayout->addWidget(new QLabel(tr("Login")), 0, 0);
    login = new QLineEdit;
    dataLayout->addWidget(login, 0, 1);

    dataLayout->addWidget(new QLabel(tr("Password")), 0, 2);
    password = new QLineEdit;
    dataLayout->addWidget(password, 0, 3);

    authDisable = new QCheckBox(tr("Without Login and Password"));
    dataLayout->addWidget(authDisable, 0, 4);

    //Тип пользователя
    dataLayout->addWidget(new QLabel(tr("User Type")), 1, 0);

    userType = new QComboBox;
    userType->addItems({"User", "Admin", "God"});
    dataLayout->addWidget(userType, 1, 1);

    //Время действия
    dataLayout->addWidget(new QLabel(tr("Time to live")), 2, 0);

    ttl = new QDateTimeEdit(QDateTime::currentDateTime());
    ttl->setMinimumDate(QDate::currentDate().addDays(-365));
    ttl->setMaximumDate(QDate::currentDate().addDays(365));
    dataLayout->addWidget(ttl, 2, 1);

    ttlDisable = new QCheckBox(tr("Without time to live"));
    ttlDisable->setChecked(false);
    dataLayout->addWidget(ttlDisable, 2, 4);

    //Ключ шифрования
    dataLayout->addWidget(new QLabel(tr("Encrypt key")), 3, 0);
    encryptKey = new QLineEdit;
    dataLayout->addWidget(encryptKey, 3, 1, 1, 2);

    QPushButton *setEncryptKeyBtn = new QPushButton(tr("Set"));
    dataLayout->addWidget(setEncryptKeyBtn, 3, 3);

    QPushButton *generateEncryptKeyBtn = new QPushButton(tr("Generate"));
    dataLayout->addWidget(generateEncryptKeyBtn, 3, 4);

    mainLayout->addStretch(1);

    //Генерация ключа
    QPushButton *generateAccessKeyBtn = new QPushButton(tr("Generate Access Key"));
    mainLayout->addWidget(generateAccessKeyBtn);

    QHBoxLayout *keyLayout = new QHBoxLayout;
    mainLayout->addLayout(keyLayout);

    keyField = new QTextEdit;
    keyField->setReadOnly(true);
    keyLayout->addWidget(keyField);

    QPushButton *saveBtn = new QPushButton(tr("Save to file"));
    keyLayout->addWidget(saveBtn);
    saveBtn->setDisabled(true);

    //Подключение к кодерам и модели данных
    connect(login, &QLineEdit::textChanged, model.get(), &DataModel::setLogin);
    connect(password, &QLineEdit::textChanged, model.get(), &DataModel::setPass);
    connect(userType, QOverload<int>::of(&QComboBox::activated), [=](int index)
    {
        model->setUserType(static_cast<uint8_t>(index));
    });
    connect(ttl, &QDateTimeEdit::dateTimeChanged, model.get(), &DataModel::setTtl);
    connect(authDisable, &QCheckBox::toggled, [this](const bool isChecked)
    {
        this->login->setDisabled(isChecked);
        this->password->setDisabled(isChecked);

        this->model->setLoginState(isChecked);
    });
    connect(ttlDisable, &QCheckBox::toggled, [this](const bool isChecked)
    {
        this->ttl->setDisabled(isChecked);
        this->model->setTtlState(isChecked);
    });

    connect(generateEncryptKeyBtn, &QPushButton::clicked, encryptCoder.get(), &EncryptKeyGenerator::generateEncryptKey);
    connect(encryptCoder.get(), &EncryptKeyGenerator::keyGenerated, [this](std::string string)
    {
        encryptKey->setText(QString::fromStdString(string));
    });
    connect(setEncryptKeyBtn, &QPushButton::clicked, this, &MainWindow::setEncryptKey);

    connect(generateAccessKeyBtn, &QPushButton::clicked, this, &MainWindow::generateAccessCode);
    connect(accessCoder.get(), &AccessKeyGenerator::accessKeyGenerated, [this, saveBtn](std::string key)
    {
//       decoder->setAccessKey(key);
       keyField->setText(QString::fromStdString(convertTools::toHex(key)));
//       decoder->decode();
       saveBtn->setEnabled(true);
    });
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::saveKeysToFile);

    initInterface();

    Decoder dec(model);
}
MainWindow::~MainWindow()
{
}

void MainWindow::initInterface()
{
    auto data = model->getData();

    login->setText(data.login);
    password->setText(data.pass);
    authDisable->setChecked(data.noLogin);
    userType->setCurrentIndex(data.userType);
    ttl->setDateTime(data.ttl);
    ttlDisable->setChecked(data.noTtl);
}

void MainWindow::generateAccessCode()
{
    if (encryptKey->text().isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Enter or Generate Encrypt Key"));
        return;
    }

    accessCoder->generateAccessKey(encryptCoder->getKey());
}

void MainWindow::setEncryptKey()
{
    if (encryptKey->text().isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Enter or Generate Encrypt Key"));
        return;
    }

    encryptCoder->saveEncryptKey(encryptKey->text());
//    decoder->setEncryptKey(encryptCoder->getKey());
}

void MainWindow::saveKeysToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Keys"), QStringLiteral("keys.txt"),
            tr("Text file (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }
        QTextStream out(&file);

        out << "Encrypt Key: " << encryptKey->text() << "\n";
        out << "Access Key: " << keyField->toPlainText() << "\n";

        file.close();
    }
}

