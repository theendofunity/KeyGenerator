#include "DataModel.h"

#include <QDebug>

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

void DataModel::setData(DataModel::Data newData)
{
    this->data = newData;
    emit dataChanged(data);
}

QStringList DataModel::dataToList()
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

DataModel::Data DataModel::listToData(QStringList list)
{
    Data newData;

    newData.login = list[0];
    newData.pass = list[1];
    newData.noLogin = list[2].toInt();
    newData.userType = static_cast<uint8_t>(list[3].toInt());
    newData.ttl = QDateTime::fromMSecsSinceEpoch(list[4].toLong());
    newData.noTtl = list[5].toInt();

    return newData;
}
