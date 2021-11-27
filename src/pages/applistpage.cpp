#include "applistpage.h"
#include "ui_applistpage.h"

AppListPage::AppListPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppListPage)
{
    ui->setupUi(this);
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setFlow(QListView::LeftToRight);
    ui->listWidget->setResizeMode(QListView::Adjust);
}
void AppListPage::setTheme(bool dark)
{
    if(dark)
    {}else {
        //亮色模式
        this->setStyleSheet("#frame{background-color: #fbfbfb;border-radius:14px;border:1px solid rgb(229,229,229);}");
    }
}
void AppListPage::setTitle(QString title)
{
    ui->title->setText(title);
}
void AppListPage::getAppList(QString type)
{
    clearItem();
    SparkAPI *api=new SparkAPI(this);
    connect(api,&SparkAPI::finished,[=](QJsonArray APPs){
        for(int i=0;i < APPs.size();i++)
        {
           QJsonObject info = APPs.at(i).toObject();
           addItem(info["Name"].toString(),info["Author"].toString(),QUrl(api->getImgServerUrl()+"store/"+type+"/"+info["Pkgname"].toString()+"/icon.png"),QUrl("spk://store/"+type+"/"+info["Pkgname"].toString()),info["More"].toString());
        }
        disconnect(api,&SparkAPI::finished,nullptr,nullptr);
        api->deleteLater();
    });
    api->getAppList(type);
}
void AppListPage::getSearchList(QString keyword)
{
    if(!mutex.tryLock())
    {
        return;
    }
    clearItem();
    ui->title->setText(tr("搜索 ")+keyword);
    SparkAPI *api=new SparkAPI(this);
    connect(api,&SparkAPI::finished,[=](QJsonArray APPs){
        for(int i=0;i < APPs.size();i++)
        {
           QJsonObject info = APPs.at(i).toObject();
           addItem(info["name"].toString(),info["author"].toString(),QUrl(info["icon"].toString()),QUrl("spk://store/"+info["category_slug"].toString()+"/"+info["pkgname"].toString()),info["more"].toString());
        }
        disconnect(api,&SparkAPI::finished,nullptr,nullptr);
        api->deleteLater();
        mutex.unlock();
    });
    api->getSearchList(keyword);
}
void AppListPage::addItem(QString name,QString author,QUrl icons,QUrl spk,QString more)
{
    AppItem *ai=new AppItem(this);
    ai->setAuthor(author);
    ai->setTitle(name);
    ai->setIcon(icons);
    ai->setSpk(spk);
    ai->setMore(more);
    connect(ai,&AppItem::clicked,[=](QUrl spk){
        emit clicked(spk);
    });
    QListWidgetItem* pItem = new QListWidgetItem();
    pItem->setSizeHint(QSize(300, 100));
    ui->listWidget->addItem(pItem);
    ui->listWidget->setItemWidget(pItem, ai);
}
void AppListPage::clearItem()
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
AppListPage::~AppListPage()
{
    delete ui;
}
