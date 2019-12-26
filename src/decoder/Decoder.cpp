#include "Decoder.h"


#include "AES/qaesencryption.h"

#include <DataModel.h>

#include <QFile>
#include <QDebug>


Decoder::Decoder(std::shared_ptr<DataModel> model, QObject *parent)
    : QObject(parent)
    , model(model)
{

}

void Decoder::setEncryptKey(QString key)
{
    if (key.isEmpty())
        return;

   encryptKey = QByteArray::fromHex(key.toLocal8Bit());
}

void Decoder::setAccessKey(QString key)
{
    if (key.isEmpty())
        return;

    accessKey = QByteArray::fromHex(key.toLocal8Bit());
}

void Decoder::setKeyPath(QString path)
{
    if (not path.isEmpty())
        keyPath = path;
}

void Decoder::decode()
{
    if (accessKey.isEmpty() || encryptKey.isEmpty())
    {
        qDebug() << "Can't find keys, running in default mode";

        return;
    }

    QAESEncryption decoder(QAESEncryption::AES_256, QAESEncryption::ECB);

    auto recoverData = decoder.decode(accessKey, encryptKey);
    auto dataString = QString(recoverData.data()); // метод data используется чтобы удалить лишние символы

    parseKeys(dataString);
}

void Decoder::readKeys()
{
    QFile file(keyPath + "/keys.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error " << file.errorString();
        return;
    }

    QTextStream in(&file);

    QStringList keys;
    while (!in.atEnd())
    {
        keys << in.readLine();
    }

    file.close();

    if (keys.size() == 2) //2 ключа
    {
        QString key1 = keys[0].split(": ")[1];
        setEncryptKey(key1);

        QString key2 = keys[1].split(": ")[1];
        setAccessKey(key2);
    }
}

void Decoder::parseKeys(QString key)
{
    QStringList list = key.split("|");
    if (list.size() != 5) //5 параметров в модели
    {
        qDebug() << "Error! Incorrect Key";
        model->dropToUserAccessMode();
        return;
    }
    auto newData = model->listToData(list);

    model->setData(newData);
}
