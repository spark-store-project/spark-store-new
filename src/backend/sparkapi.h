#ifndef SPARKAPI_H
#define SPARKAPI_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include "src/utils/httprequest.h"

class SparkAPI : public QObject
{
    Q_OBJECT
public:
    void getSearchList(QString keyword,int page);
    void get(QUrl url);
    void getAppList(QString type);
    explicit SparkAPI(QObject *parent = nullptr);
signals:
    void finished(QJsonArray);

public slots:
};

#endif // SPARKAPI_H
