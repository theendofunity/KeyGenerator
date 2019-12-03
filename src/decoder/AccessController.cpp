#include "AccessController.h"

#include <DataModel.h>
#include <QTimer>

#include <QMessageBox>
#include <QDebug>

AccessController::AccessController(QObject *parent)
    : QObject(parent)
{
    model = std::make_shared<DataModel>();
    decoder = std::make_unique<Decoder>(model, this);

//    decoder->setKeyPath()
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

    model->setUserType(model->User);
    model->setTtlState(false);
    model->setLoginState(false);

    emit ttlEnded();
}
