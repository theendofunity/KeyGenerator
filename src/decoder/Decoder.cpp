#include "Decoder.h"

#include "cryptopp/rabbit.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/files.h"
#include "cryptopp/hex.h"
#include "cryptopp/secblock.h"

#include "ConvertTools.h"

#include <QDebug>

using namespace CryptoPP;

Decoder::Decoder(QObject *parent)
    : QObject(parent)
{

}

void Decoder::setEncryptKey(SecByteBlock key)
{
    encryptKey = key;
}

void Decoder::setAccessKey(std::string key)
{
    accessKey = key;
}

void Decoder::decode()
{
    std::string recoverData;

    Rabbit::Decryption decoder;
    decoder.SetKey(encryptKey, encryptKey.size());

    recoverData.resize(accessKey.size());

    decoder.ProcessData((byte*)&recoverData[0], (const byte*)accessKey.data(), accessKey.size());
    qDebug() << "Decoder"<< QString::fromStdString(recoverData);
}

void Decoder::readKeys()
{

}
