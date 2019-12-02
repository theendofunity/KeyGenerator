#include "AccessKeyGenerator.h"

#include "cryptopp/rabbit.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/secblock.h"

#include <QString>
#include <QStringList>

#include <DataModel.h>
#include <ConvertTools.h>

#include "cryptopp/hex.h"
#include "cryptopp/files.h"

#include <QDebug>

using namespace CryptoPP;

AccessKeyGenerator::AccessKeyGenerator(std::shared_ptr<DataModel> model, QObject *parent)
        : QObject(parent)
        , model(model)
{

}

void AccessKeyGenerator::generateAccessKey(SecByteBlock encryptKey)
{
    Rabbit::Encryption encoder;
    encoder.SetKey(encryptKey, encryptKey.size());

    auto data = createDataString().toStdString();
    std::string cipher;
    cipher.resize(data.size());

    auto outStr = static_cast<byte*>(static_cast<void*>(&cipher[0]));
    encoder.ProcessData(outStr, reinterpret_cast<const byte*>(data.data()), data.size());

    key = cipher;

    emit accessKeyGenerated(cipher);
}

QString AccessKeyGenerator::createDataString()
{
    auto data = model->getData();

    QStringList dataList;

    dataList << data.login
             << data.pass
             << QString::number(data.noLogin)
             << QString::number(data.userType)
             << data.ttl.toString()
             << QString::number(data.noTtl);

    return dataList.join("|");
}
