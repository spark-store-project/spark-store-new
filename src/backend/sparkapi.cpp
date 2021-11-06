#include "sparkapi.h"
#include <QDebug>
SparkAPI::SparkAPI(QObject *parent) : QObject(parent)
{

}
void getAppList(QString type)
{
    QNetworkRequest request;
    HttpRequest *httprequest=new HttpRequest;
    request.setUrl(QUrl("https://json.jerrywang.top/store/"+type+"/applist.json"));
    connect(httprequest,&HttpRequest::finished,[=](QString data){
        QByteArray arr = data.toUtf8();
            //解析Json
            QJsonParseError error;
            QJsonDocument doc = QJsonDocument::fromJson(arr,&error);
            QJsonObject obj = doc.object();
            emit finished(obj.value("data").toObject().value("list").toArray());
            httprequest->deleteLater();
    });
    httprequest->getRequest(request);
}
