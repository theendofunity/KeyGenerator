#include "AccessKeyGenerator.h"

#include "AES/qaesencryption.h"
#include <QString>
#include <QStringList>

#include <AccessKeyDataModel.h>

#include <QDebug>

AccessKeyGenerator::AccessKeyGenerator(std::shared_ptr<AccessKeyDataModel> model, QObject *parent)
        : QObject(parent)
        , model(model)
{

}

void AccessKeyGenerator::generateAccessKey(QByteArray encryptKey)
{
    if (encryptKey.isEmpty())
        return;

    QAESEncryption encoder (QAESEncryption::AES_256, QAESEncryption::ECB);

    auto data = createDataString();

    QByteArray accessKey = encoder.encode(data.toLocal8Bit(), encryptKey);

    emit accessKeyGenerated(accessKey.toHex());
}

QString AccessKeyGenerator::createDataString()
{
    auto modelData = model->dataToList();
    modelData.last() += "|";
    auto dataString = modelData.join("|");

    return dataString;
}
