#include "AccessKeyGenerator.h"

#include "libs/cryptopp/rabbit.h"
#include "libs/cryptopp/cryptlib.h"
#include "libs/cryptopp/secblock.h"

#include <QString>
#include <QStringList>

#include <DataModel.h>
#include <ConvertTools.h>

#include "libs/cryptopp/hex.h"
#include "libs/cryptopp/files.h"

#include <QDebug>

using namespace CryptoPP;

AccessKeyGenerator::AccessKeyGenerator(std::shared_ptr<DataModel> model, QObject *parent)
        : QObject(parent)
        , model(model)
{

}

void AccessKeyGenerator::generateAccessKey(SecByteBlock encryptKey)
{
    if (encryptKey.empty())
        return;

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
    auto dataList = model->dataToList();

    return dataList.join("|");
}
