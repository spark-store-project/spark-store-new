#include "sparkapi.h"
#include <QDebug>
SparkAPI::SparkAPI(QObject *parent) : QObject(parent)
{

}
void SparkAPI::get(QUrl url)
{
    QNetworkRequest request;
    HttpRequest *httprequest=new HttpRequest;
    request.setUrl(url);
    connect(httprequest,&HttpRequest::finished,[=](QString data){
        QByteArray arr = data.toUtf8();
            //解析Json
            QJsonParseError error;
            QJsonDocument doc = QJsonDocument::fromJson(arr,&error);
            QJsonObject obj = doc.object();
            emit finished(obj.toArray());
            httprequest->deleteLater();
    });
    httprequest->getRequest(request);
}
void SparkAPI::getAppList(QString type)
{
    get(QUrl("https://json.jerrywang.top/store/"+type+"/applist.json"));
}
void SparkAPI::getSearchList(QString keyword)
{
    get(QUrl("https://search.deepinos.org.cn/appinfo/search?"+keyword));
}