#ifndef ACCESSCONTROLLER_H
#define ACCESSCONTROLLER_H

#include <QObject>
#include <memory>

#include "Decoder.h"

class DataModel;
class QTimer;

class AccessController : public QObject
{
    Q_OBJECT
public:
    AccessController(QObject *parent = nullptr);
    int userType();
    QString password();
    bool noLogin();

private:
    void controlTtl();
    void resetUserTypeToDefault();
signals:
    void ttlEnded();

private:
    std::shared_ptr<DataModel> model = nullptr;
    std::unique_ptr<Decoder> decoder = nullptr;

    QTimer *timer = nullptr;
};

#endif // ACCESSCONTROLLER_H
