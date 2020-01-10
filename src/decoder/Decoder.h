#ifndef DECODER_H
#define DECODER_H

#include "QObject"

#include <memory>
#include <QStandardPaths>

class AccessKeyDataModel;

class Decoder : public QObject
{
    Q_OBJECT
public:
    Decoder(std::shared_ptr<AccessKeyDataModel> model, QObject *parent = nullptr);

    void setEncryptKey(QString key);
    void setAccessKey(QString key);
    void setKeyPath(QString path);

    void decode();
    void readKeys();

private:
    void parseKeys(QString key);

private:
    QByteArray encryptKey;
    QByteArray accessKey;

    QString keyPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);

    std::shared_ptr<AccessKeyDataModel> model = nullptr;
};

#endif // DECODER_H
