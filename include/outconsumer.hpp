#pragma once

#include<QObject>
#include<QString>
#include<QByteArray>
#include<QJsonArray>
#include<QtQml/qqmlregistration.h>
#include"nodeConnection.hpp"
#include"account.hpp"


using namespace qiota::qblocks;
using namespace qiota;

class OutConsumer : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    OutConsumer(QObject *parent = nullptr):QObject(parent){};

    Q_INVOKABLE void consume(std::vector<qiota::Node_output>  outs, const QJsonValue & address, QVector<quint32> subpath={0,0,0},QString amountneedit="0");


signals:
    void finish(QJsonObject addreses, qiota::AddressBundle bundle);


private:


};
