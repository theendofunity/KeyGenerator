#ifndef ACCESSKEYGENERATOR_H
#define ACCESSKEYGENERATOR_H

#include <QObject>
#include <memory>

class QString;
class AccessKeyDataModel;

class AccessKeyGenerator : public QObject
{
    Q_OBJECT

public:
    AccessKeyGenerator(std::shared_ptr<AccessKeyDataModel> model, QObject *parent = nullptr);
    void generateAccessKey(QByteArray encryptKey);

private:
    QString createDataString();

signals:
    void accessKeyGenerated(QString key);

private:
    std::shared_ptr<AccessKeyDataModel> model;
    QByteArray key;
};

#endif // ACCESSKEYGENERATOR_H
