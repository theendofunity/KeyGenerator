#include "AccessController.h"

#include "AccessKeyDataModel.h"
#include <QTimer>

#include <QMessageBox>
#include <QDebug>

AccessController::AccessController(QString pathToKeys, QObject *parent)
    : QObject(parent)
{
    model = std::make_shared<AccessKeyDataModel>();
    decoder = new Decoder(model, this);

    decoder->setKeyPath(pathToKeys);
    decoder->readKeys();
    decoder->decode();
    controlTtl();
}

int AccessController::userType()
{
    return model->getData().userType;
}

QString AccessController::password()
{
    return model->getData().pass;
}

bool AccessController::noLogin()
{
    return model->getData().noLogin;
}

void AccessController::controlTtl()
{
    auto data = model->getData();

    if (data.noTtl)
        return;

    QDateTime ttl = data.ttl;
    QDateTime current = QDateTime::currentDateTime();

    if (ttl < current)
        resetUserTypeToDefault();

    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &AccessController::resetUserTypeToDefault);

    auto msecDelta = ttl.toMSecsSinceEpoch() - current.toMSecsSinceEpoch();

    timer->setInterval(static_cast<int>(msecDelta));
    timer->start();
}

void AccessController::resetUserTypeToDefault()
{
    QMessageBox::information(nullptr, tr("Timeout"), tr("Time to live for Key is ended. Running default mode"));

    emit ttlEnded();

    model->dropToUserAccessMode();
}
