#include "EncryptKeyGenerator.h"

#include "cryptopp/cryptlib.h"
#include "cryptopp/secblock.h"
#include "cryptopp/rabbit.h"
#include "cryptopp/files.h"
#include "cryptopp/hex.h"

#include <ConvertTools.h>

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

    emit keyGenerated(convertTools::byteBlockToHex(newKey));
}


void EncryptKeyGenerator::saveEncryptKey(QString newKey)
{
    auto decodedKey = convertTools::fromHex(newKey.toStdString());

    key = SecByteBlock(reinterpret_cast<const byte*>(&decodedKey[0]), decodedKey.size());
}

SecByteBlock EncryptKeyGenerator::getKey()
{
    return key;
}
