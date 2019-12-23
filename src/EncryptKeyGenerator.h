#ifndef CODER_H
#define CODER_H

#include <QObject>

#include "QString"

class EncryptKeyGenerator : public QObject
{
    Q_OBJECT
public:
    EncryptKeyGenerator(QObject *parent = nullptr);

    void generateEncryptKey();

    void saveEncryptKey(QString newKey);
    QByteArray getKey();

signals:
    void keyGenerated(QString newKey);

private:

    QByteArray key;
};

#endif // CODER_H
