#ifndef ACCESSCONTROLLER_H
#define ACCESSCONTROLLER_H

#include <QObject>
#include <memory>

#include "Decoder.h"

class AccessKeyDataModel;
class QTimer;

class AccessController : public QObject
{
    Q_OBJECT
public:
    AccessController(QString pathToKeys = QString(), QObject *parent = nullptr);
    int userType();
    QString password();
    bool noLogin();

private:
    void controlTtl();
    void resetUserTypeToDefault();
signals:
    void ttlEnded();

private:
    std::shared_ptr<AccessKeyDataModel> model = nullptr;
    Decoder* decoder = nullptr;

    QTimer *timer = nullptr;
};

#endif // ACCESSCONTROLLER_H
