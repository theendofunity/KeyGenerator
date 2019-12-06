#include "Decoder.h"

#include "cryptopp/include/rabbit.h"
#include "cryptopp/include/cryptlib.h"
#include "cryptopp/include/files.h"
#include "cryptopp/include/hex.h"
#include "cryptopp/include/secblock.h"

#include "ConvertTools.h"

#include <DataModel.h>

#include <QFile>
#include <QDebug>

using namespace CryptoPP;

Decoder::Decoder(std::shared_ptr<DataModel> model, QObject *parent)
    : QObject(parent)
    , model(model)
{

}

void Decoder::setEncryptKey(std::string key)
{
    if (key.empty())
        return;

    auto decodedKey = convertTools::fromHex(key);

    auto data = static_cast<const byte*>(static_cast<void*>(&decodedKey[0]));
    encryptKey = SecByteBlock(data, decodedKey.size());
}

void Decoder::setAccessKey(std::string key)
{
    if (key.empty())
        return;

    accessKey = convertTools::fromHex(key);
}

void Decoder::setKeyPath(QString path)
{
    keyPath = path;
}

void Decoder::decode()
{
    if (accessKey.empty() || encryptKey.empty())
    {
        qDebug() << "Can't find keys, running in default mode";
        return;
    }

    std::string recoverData;

    Rabbit::Decryption decoder;
    decoder.SetKey(encryptKey, encryptKey.size());

    recoverData.resize(accessKey.size());

    auto outStr = static_cast<byte*>(static_cast<void*>(&recoverData[0]));
    decoder.ProcessData(outStr, reinterpret_cast<const byte*>(accessKey.data()), accessKey.size());

    qDebug() << "Decoder" << QString::fromStdString(recoverData);

    parseKeys(recoverData);
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
    keys << in.readLine();
    keys << in.readLine();

    file.close();

    QString key1 = keys[0].split(": ")[1];
    setEncryptKey(key1.toStdString());

    QString key2 = keys[1].split(": ")[1];
    setAccessKey(key2.toStdString());
}

void Decoder::parseKeys(std::string key)
{
    QStringList data = QString::fromStdString(key).split("|");

    auto newData = model->listToData(data);
    qDebug() << "Parse" << newData.ttl;
    model->setData(newData);
}
