#ifndef ACCESSKEYGENERATOR_H
#define ACCESSKEYGENERATOR_H

#include "cryptopp/osrng.h"

#include <QObject>
#include <memory>

class QString;
class DataModel;

class AccessKeyGenerator : public QObject
{
    Q_OBJECT

public:
    AccessKeyGenerator(std::shared_ptr<DataModel> model, QObject *parent = nullptr);
    void generateAccessKey(CryptoPP::SecByteBlock encryptKey);

private:
    QString createDataString();

signals:
    void accessKeyGenerated(std::string key);

private:
    std::shared_ptr<DataModel> model;
    std::string key;
};

#endif // ACCESSKEYGENERATOR_H
