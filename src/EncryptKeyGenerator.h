#ifndef CODER_H
#define CODER_H

#include <QObject>

#include "cryptopp/osrng.h"
#include "QString"

class EncryptKeyGenerator : public QObject
{
    Q_OBJECT
public:
    EncryptKeyGenerator(QObject *parent = nullptr);

    void generateEncryptKey();

    void saveEncryptKey(QString newKey);
    CryptoPP::SecByteBlock getKey();

signals:
    void keyGenerated(std::string newKey);

private:
CryptoPP::SecByteBlock key;
};

#endif // CODER_H
