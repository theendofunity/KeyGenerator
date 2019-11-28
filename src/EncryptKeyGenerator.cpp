#include "EncryptKeyGenerator.h"

#include "cryptopp/cryptlib.h"
#include "cryptopp/secblock.h"
#include "cryptopp/rabbit.h"
#include "cryptopp/osrng.h"
#include "cryptopp/files.h"
#include "cryptopp/hex.h"

#include <QDebug>


using namespace CryptoPP;

EncryptKeyGenerator::EncryptKeyGenerator(QObject *parent)
    :QObject(parent)
{

}

void EncryptKeyGenerator::generateEncryptKey()
{
    AutoSeededRandomPool generator;
    CryptoPP::SecByteBlock newKey(16);

    generator.GenerateBlock(newKey, newKey.size());

    emit keyGenerated(encodeToHex(newKey));
}

std::string EncryptKeyGenerator::encodeToHex(SecByteBlock data)
{
    HexEncoder encoder;
    encoder.Put(static_cast<unsigned char*>(data.data()), data.size());
    encoder.MessageEnd();
    std::string output;
    word64 size = encoder.MaxRetrievable();
    if(size)
    {
        output.resize(size);
        encoder.Get((byte*)&output[0], output.size());
    }
    return output;
}

void EncryptKeyGenerator::decodeFromHex(std::string encoded)
{
    std::string decoded;

    HexDecoder decoder;
    decoder.Put(reinterpret_cast<const byte*>(encoded.data()), encoded.size() );
    decoder.MessageEnd();

    word64 size = decoder.MaxRetrievable();
    if(size && size <= SIZE_MAX)
    {
        decoded.resize(size);
        decoder.Get((byte*)&decoded[0], decoded.size());
    }
//    qDebug() << QString::fromStdString(encoded) << QString::fromStdString(decoded);
}

void EncryptKeyGenerator::saveEncryptKey(QString newKey)
{
    auto str = newKey.toStdString();

    key = SecByteBlock(reinterpret_cast<const byte*>(&str[0]), str.size());
}

SecByteBlock EncryptKeyGenerator::getKey()
{
    return key;
}
