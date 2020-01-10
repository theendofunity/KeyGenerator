#include "AccessKeyDataModel.h"

#include <QDebug>

AccessKeyDataModel::AccessKeyDataModel(QObject *parent)
    : QObject(parent)
{

}

void AccessKeyDataModel::setLogin(QString login)
{
    data.login = login;
    emit dataChanged(data);
}

void AccessKeyDataModel::setPass(QString pass)
{
    data.pass = pass;
    emit dataChanged(data);
}

void AccessKeyDataModel::setLoginState(bool hasLogin)
{
    data.noLogin = hasLogin;
    emit dataChanged(data);
}

void AccessKeyDataModel::setUserType(uint8_t type)
{
    data.userType = type;
    emit dataChanged(data);
}

void AccessKeyDataModel::setTtl(QDateTime ttl)
{
    data.ttl = ttl;
    emit dataChanged(data);
}

void AccessKeyDataModel::setTtlState(bool hasTtl)
{
    data.noTtl = hasTtl;
    emit dataChanged(data);
}

void AccessKeyDataModel::dropToUserAccessMode()
{
    setUserType(User);
    setTtlState(false);
    setLoginState(false);
}

const AccessKeyDataModel::Data AccessKeyDataModel::getData() const
{
    return data;
}

void AccessKeyDataModel::setData(AccessKeyDataModel::Data newData)
{
    this->data = newData;
    emit dataChanged(data);
}

QStringList AccessKeyDataModel::dataToList()
{
    QStringList dataList;

    dataList << data.login
             << data.pass
             << QString::number(data.noLogin)
             << QString::number(data.userType)
             << QString::number(data.ttl.toMSecsSinceEpoch())
             << QString::number(data.noTtl);

    return  dataList;
}

AccessKeyDataModel::Data AccessKeyDataModel::listToData(QStringList list)
{
    Data newData;

    newData.login = list.at(0);
    newData.pass = list.at(1);
    newData.noLogin = list.at(2).toInt();
    newData.userType = static_cast<uint8_t>(list.at(3).toInt());
    newData.ttl = QDateTime::fromMSecsSinceEpoch(list.at(4).toLong());
    newData.noTtl = list.at(5).toInt();

    return newData;
}
