#include "MainWindow.h"

#include "QVBoxLayout"
#include "QLabel"
#include "QLineEdit"
#include "QCheckBox"
#include "QComboBox"
#include "QDateTimeEdit"
#include "QPushButton"
#include "QTextEdit"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
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
    QLineEdit* login = new QLineEdit;
    dataLayout->addWidget(login, 0, 1);

    dataLayout->addWidget(new QLabel(tr("Password")), 0, 2);
    QLineEdit* password = new QLineEdit;
    dataLayout->addWidget(password, 0, 3);

    QCheckBox *authDisable = new QCheckBox(tr("Without Login and Password"));
    authDisable->setChecked(false);
    dataLayout->addWidget(authDisable, 0, 4);

    //Тип пользователя
    dataLayout->addWidget(new QLabel(tr("User Type")), 1, 0);

    QComboBox *userType = new QComboBox;
    userType->addItems({"User", "Admin", "God"});
    dataLayout->addWidget(userType, 1, 1);

    //Время действия
    dataLayout->addWidget(new QLabel(tr("Time to live")), 2, 0);

    QDateTimeEdit *ttl = new QDateTimeEdit(QDateTime::currentDateTime());
    ttl->setMinimumDate(QDate::currentDate().addDays(-365));
    ttl->setMaximumDate(QDate::currentDate().addDays(365));
    dataLayout->addWidget(ttl, 2, 1);

    QCheckBox *ttlDisable = new QCheckBox(tr("Without time to live"));
    ttlDisable->setChecked(false);
    dataLayout->addWidget(ttlDisable, 2, 4);

    mainLayout->addStretch(1);

    //Генерация ключа
    QPushButton *generateBtn = new QPushButton(tr("Generate Key"));
    mainLayout->addWidget(generateBtn);

    QHBoxLayout *keyLayout = new QHBoxLayout;
    mainLayout->addLayout(keyLayout);

    QTextEdit *keyField = new QTextEdit();
    keyField->setReadOnly(true);
    keyLayout->addWidget(keyField);

    QPushButton *saveBtn = new QPushButton(tr("Save to file"));
    keyLayout->addWidget(saveBtn);
}

MainWindow::~MainWindow()
{
}

