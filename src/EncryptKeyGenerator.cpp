#include "EncryptKeyGenerator.h"

#include <QMessageBox>

#include <QRandomGenerator>
#include <QCryptographicHash>
#include "AES/qaesencryption.h"

#include <QDebug>


EncryptKeyGenerator::EncryptKeyGenerator(QObject *parent)
    :QObject(parent)
{
}

void EncryptKeyGenerator::generateEncryptKey()
{
    auto randomNumber = QRandomGenerator::global()->generate();

    QString str = QString::number(randomNumber);

    QByteArray newKey = QCryptographicHash::hash(str.toLocal8Bit(), QCryptographicHash::Sha256);

    emit keyGenerated(newKey.toHex());
}

void EncryptKeyGenerator::saveEncryptKey(QString newKey)
{
    if (newKey.isEmpty())
        return;

    auto decodedKey = QByteArray::fromHex(newKey.toLocal8Bit());

    key = decodedKey;
}

QByteArray EncryptKeyGenerator::getKey()
{
    return key;
}
