#ifndef DECODER_H
#define DECODER_H

#include "QObject"

#include "cryptopp/include/osrng.h"
#include <QStandardPaths>

class DataModel;

class Decoder : public QObject
{
    Q_OBJECT
public:
    Decoder(std::shared_ptr<DataModel> model, QObject *parent = nullptr);

    void setEncryptKey(std::string key);
    void setAccessKey(std::string key);
    void setKeyPath(QString path);

    void decode();
    void readKeys();

private:
    void parseKeys(std::string key);

private:
    CryptoPP::SecByteBlock encryptKey;
    std::string accessKey;

    QString keyPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);

    std::shared_ptr<DataModel> model = nullptr;
};

#endif // DECODER_H
