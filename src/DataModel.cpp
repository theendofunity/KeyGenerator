#include "DataModel.h"

DataModel::DataModel(QObject *parent)
    : QObject(parent)
{

}

void DataModel::setLogin(QString login)
{
    data.login = login;
    emit dataChanged(data);
}

void DataModel::setPass(QString pass)
{
    data.pass = pass;
    emit dataChanged(data);
}

void DataModel::setLoginState(bool hasLogin)
{
    data.noLogin = hasLogin;
    emit dataChanged(data);
}

void DataModel::setUserType(uint8_t type)
{
    data.userType = type;
    emit dataChanged(data);
}

void DataModel::setTtl(QDateTime ttl)
{
    data.ttl = ttl;
    emit dataChanged(data);
}

void DataModel::setTtlState(bool hasTtl)
{
    data.noTtl = hasTtl;
    emit dataChanged(data);
}

const DataModel::Data DataModel::getData() const
{
    return data;
}
