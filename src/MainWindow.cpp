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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , model(new DataModel(this))
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

    mainLayout->addStretch(1);

    //Генерация ключа
    QPushButton *generateBtn = new QPushButton(tr("Generate Key"));
    generateBtn->setDisabled(true);
    mainLayout->addWidget(generateBtn);

    QHBoxLayout *keyLayout = new QHBoxLayout;
    mainLayout->addLayout(keyLayout);

    QTextEdit *keyField = new QTextEdit();
    keyField->setReadOnly(true);
    keyLayout->addWidget(keyField);

    QPushButton *saveBtn = new QPushButton(tr("Save to file"));
    keyLayout->addWidget(saveBtn);
    saveBtn->setDisabled(true);

    connect(model, &DataModel::dataChanged, [generateBtn]()
    {
       generateBtn->setEnabled(true);
    });
    connect(login, &QLineEdit::textChanged, model, &DataModel::setLogin);
    connect(password, &QLineEdit::textChanged, model, &DataModel::setPass);
    connect(userType, QOverload<int>::of(&QComboBox::activated), [=](int index)
    {
        model->setUserType(static_cast<uint8_t>(index));
    });
    connect(ttl, &QDateTimeEdit::dateTimeChanged, model, &DataModel::setTtl);
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

