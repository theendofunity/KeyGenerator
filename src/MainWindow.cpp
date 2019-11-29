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
#include "EncryptKeyGenerator.h"
#include "AccessKeyGenerator.h"

#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , model(std::make_shared<DataModel>(this))
    , encryptCoder(new EncryptKeyGenerator(this))
    , accessCoder(new AccessKeyGenerator(model, this))
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
    QLineEdit *encryptKey = new QLineEdit;
    dataLayout->addWidget(encryptKey, 3, 1, 1, 2);
    QPushButton *saveEncryptKeyBtn = new QPushButton(tr("Save"));
    dataLayout->addWidget(saveEncryptKeyBtn, 3, 3);
    QPushButton *generateEncryptKeyBtn = new QPushButton(tr("Generate"));
    dataLayout->addWidget(generateEncryptKeyBtn, 3, 4);

    mainLayout->addStretch(1);

    //Генерация ключа
    QPushButton *generateAccessKeyBtn = new QPushButton(tr("Generate Access Key"));
    mainLayout->addWidget(generateAccessKeyBtn);


    QHBoxLayout *keyLayout = new QHBoxLayout;
    mainLayout->addLayout(keyLayout);

    QTextEdit *keyField = new QTextEdit();
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

    connect(generateEncryptKeyBtn, &QPushButton::clicked, encryptCoder, &EncryptKeyGenerator::generateEncryptKey);
    connect(encryptCoder, &EncryptKeyGenerator::keyGenerated, [encryptKey](std::string string)
    {
        encryptKey->setText(QString::fromStdString(string));
    });
    connect(saveEncryptKeyBtn, &QPushButton::clicked, [encryptKey, this]()
    {
        this->encryptCoder->saveEncryptKey(encryptKey->text());
    });

    connect(generateAccessKeyBtn, &QPushButton::clicked, this, &MainWindow::generateAccessCode);
    connect(accessCoder, &AccessKeyGenerator::accessKeyGenerated, [keyField](std::string key)
    {
       keyField->setText(QString::fromStdString(key));
    });
    initInterface();
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
    accessCoder->generateAccessKey(encryptCoder->getKey());
}

