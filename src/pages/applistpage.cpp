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
    ui->pushButton->setIcon(QIcon::fromTheme(":/icon/light/refresh.svg"));
}
void AppListPage::getAppList(QString type)
{
    SparkAPI *api=new SparkAPI(this);
    connect(api,&SparkAPI::finished,[=](QJsonArray APPs){
        for(int i=0;i < APPs.size();i++)
        {
           QJsonObject info = APPs.at(i).toObject();
           addItem(info["Name"].toString(),info["Author"].toString(),QUrl(info["icons"].toString()),QUrl("spk://"+type+"/"+info["Pkgname"].toString()),info["More"].toString())
        }
        disconnect(api,&SparkAPI::finished,nullptr,nullptr);
        api->deleteLater();
    });
    api->getAppList(type);
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
    pItem->setSizeHint(QSize(240, 250));
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

void AppListPage::on_pushButton_clicked()
{
    ui->listWidget->clearItem();
    updateUI();
}
