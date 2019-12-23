#ifndef ACCESSKEYGENERATOR_H
#define ACCESSKEYGENERATOR_H

#include <QObject>
#include <memory>

class QString;
class DataModel;

class AccessKeyGenerator : public QObject
{
    Q_OBJECT

public:
    AccessKeyGenerator(std::shared_ptr<DataModel> model, QObject *parent = nullptr);
    void generateAccessKey(QByteArray encryptKey);

private:
    QString createDataString();

signals:
    void accessKeyGenerated(QString key);

private:
    std::shared_ptr<DataModel> model;
    QByteArray key;
};

#endif // ACCESSKEYGENERATOR_H
