#include "ConvertTools.h"

#include "cryptopp/hex.h"

#include <QString>
#include <memory>

#include <QDebug>


using namespace CryptoPP;

std::string convertTools::byteBlockToHexString(CryptoPP::SecByteBlock data)
{
    HexEncoder encoder;
    std::string encoded;

    encoder.Attach(new StringSink(encoded));
    encoder.Put(data.data(), data.size());
    encoder.MessageEnd();
    qDebug() << "EncodeTo"  << data.data() << QString::fromStdString(encoded);
    return encoded;
}

std::string convertTools::fromHex(std::string encoded)
{
    std::string decoded;

    HexDecoder decoder;
    decoder.Put(reinterpret_cast<const byte*>(encoded.data()), encoded.size() );

    decoder.MessageEnd();

    word64 size = decoder.MaxRetrievable();
    if(size && size <= SIZE_MAX)
    {
        decoded.resize(size);
        auto data = static_cast<byte*>(static_cast<void*>(&decoded[0]));
        decoder.Get(data, decoded.size());
    }

    qDebug() << "DecodeFrom" << QString::fromStdString(decoded) << QString::fromStdString(encoded);

    return decoded;
}

std::string convertTools::toHex(std::string data)
{
    HexEncoder encoder;
    std::string encoded;

    encoder.Attach(new StringSink(encoded));
    encoder.Put(reinterpret_cast<const byte*>(data.data()), data.size());
    encoder.MessageEnd();

    return encoded;
}
