#ifndef DECODER_H
#define DECODER_H

#include "QObject"

#include "cryptopp/osrng.h"

class Decoder : public QObject
{
    Q_OBJECT
public:
    Decoder(QObject *parent = nullptr);

    void setEncryptKey(CryptoPP::SecByteBlock key);
    void setAccessKey(std::string key);

    void decode();
private:
    void readKeys();

private:
    CryptoPP::SecByteBlock encryptKey;
    std::string accessKey;
};

#endif // DECODER_H
