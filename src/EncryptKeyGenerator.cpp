#include "EncryptKeyGenerator.h"

#include "cryptopp/include/cryptlib.h"
#include "cryptopp/include/secblock.h"
#include "cryptopp/include/rabbit.h"
//#include "cryptopp/files.h"
#include "cryptopp/include/hex.h"

#include <ConvertTools.h>
#include <QMessageBox>

#include <QDebug>


using namespace CryptoPP;

EncryptKeyGenerator::EncryptKeyGenerator(QObject *parent)
    :QObject(parent)
{
}

void EncryptKeyGenerator::generateEncryptKey()
{
    AutoSeededRandomPool generator;
    SecByteBlock newKey(16);

    generator.GenerateBlock(newKey, newKey.size());

    emit keyGenerated(convertTools::byteBlockToHexString(newKey));
}

void EncryptKeyGenerator::saveEncryptKey(QString newKey)
{
    if (newKey.isEmpty())
        return;

    auto decodedKey = convertTools::fromHex(newKey.toStdString());

    auto data = static_cast<const byte*>(static_cast<void*>(&decodedKey[0]));
    key = SecByteBlock(data, decodedKey.size());
}

SecByteBlock EncryptKeyGenerator::getKey()
{
    return key;
}
