#ifndef DATAMODEL_H
#define DATAMODEL_H

#include "QObject"
#include "stdint.h"
#include "QDateTime"

class AccessKeyDataModel : public QObject
{
    Q_OBJECT

public:

    enum UserTypes
    {
        User = 0,
        Admin,
        God
    };

    struct Data
    {
        QString login = "Admin";
        QString pass = "Admin";
        bool noLogin = false;
        uint8_t userType = UserTypes::User;
        QDateTime ttl = QDateTime::currentDateTime().addDays(1);
        bool noTtl = true;
    };
public:
    AccessKeyDataModel(QObject *parent = nullptr);

    void setLogin(QString login);
    void setPass(QString pass);
    void setLoginState(bool hasLogin);
    void setUserType(uint8_t type);
    void setTtl(QDateTime ttl);
    void setTtlState(bool hasTtl);

    void dropToUserAccessMode();

    const Data getData() const;
    void setData(Data newData);

    QStringList dataToList();
    Data listToData(QStringList list);

signals:
    void dataChanged(Data data);

private:
    Data data;
};

#endif // DATAMODEL_H
