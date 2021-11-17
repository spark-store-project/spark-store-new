#include "downloadlistwidget.h"
#include "ui_downloadlistwidget.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDebug>
DownloadListWidget::DownloadListWidget(QWidget *parent) :
    DBlurEffectWidget(parent),
    ui(new Ui::DownloadListWidget)
{
    ui->setupUi(this);
    installEventFilter(this);
    setFocus();
    setFixedSize(310,300);
}

DownloadListWidget::~DownloadListWidget()
{
    delete ui;
}
void DownloadListWidget::clearItem()
{
    ui->listWidget->vScrollBar->scrollTop();
    int n=ui->listWidget->count();
    for(int i=0;i<n;i++)
    {
        QListWidgetItem *item = ui->listWidget->takeItem(0);
        QWidget *card = ui->listWidget->itemWidget(item);
        delete card;
        card  = NULL;
        delete item;
        item  = NULL;
    }
    ui->listWidget->clear();
}
void DownloadListWidget::addItemSpk(QUrl spk)
{
    SparkAPI *api=new SparkAPI(this);
    connect(api,&SparkAPI::finished,[=](QJsonArray appinfo){
        QJsonObject info = appinfo.at(0).toObject();
        //获取图标
        QNetworkRequest request;
        naManager=new QNetworkAccessManager(this);
        request.setUrl(QUrl("https://img.jerrywang.top/store"+DownloadItem::spk.path() + "/icon.png"));
        request.setRawHeader("User-Agent", "Mozilla/5.0");
        request.setRawHeader("Content-Type", "charset='utf-8'");
        naManager->get(request);
        QObject::connect(naManager,&QNetworkAccessManager,[=](QNetworkReply *reply){
                QByteArray jpegData = reply->readAll();
                QPixmap pixmap;
                pixmap.loadFromData(jpegData);
                pixmap.scaled(100, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                seticon(pixmap);
                addItem(info["Name"].toString(),info["Filename"].toString(),info["Pkgname"].toString(),pixmap,api->getServerUrl()+"store"+spk.path()+"/"+info["Filename"].toString());
            });
        disconnect(api,&SparkAPI::finished,nullptr,nullptr);
        api->deleteLater();
    });
    api->getAppInfo(spk);
}
void DownloadListWidget::addItem(QString name,QString fileName,QString pkgName,const QPixmap icon,QString downloadurl)
{
    DownloadItem *di=new DownloadItem(this);
    di->setName(name);
    di->setFileName(fileName);
    di->pkgName=pkgName;
    di->seticon(icon);
    di->setUrl(downloadurl);
    connect(di,&DownloadItem::finished,[=](){
        //emit clicked(spk);
    });
    QListWidgetItem* pItem = new QListWidgetItem();
    pItem->setSizeHint(QSize(240, 250));
    ui->listWidget->addItem(pItem);
    ui->listWidget->setItemWidget(pItem, di);
}
void DownloadListWidget::m_move(int x,int y)
{
    m_rect.setX(x);
    m_rect.setY(y);
    move(x,y);
    return;
}
bool DownloadListWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this) {
        if (event->type() == QEvent::FocusOut)
        {
            this->hide();

        }
    }
        return QWidget::eventFilter(watched,event);
}
void DownloadListWidget::mouseMoveEvent(QMouseEvent *event)
{
    setGeometry(m_rect);
}
