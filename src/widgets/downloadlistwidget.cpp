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
    this->setAttribute(Qt::WA_Hover,true);
    setFocus();
    setFixedSize(500,400);
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
void DownloadListWidget::addItem(QString name,QString fileName,QString pkgName,const QPixmap icon,QString downloadurl)
{
    if(dlist.contains(downloadurl))
    {
        return;
    }
    if(fileName.isEmpty())
    {
        return;
    }
    DownloadItem *di=new DownloadItem(this);
    dlist<<downloadurl;
    downloaditemlist<<di;
    di->setName(name);
    di->setFileName(fileName);
    di->pkgName=pkgName;
    di->seticon(icon);
    di->setUrl(downloadurl);
    connect(di,&DownloadItem::finished,[=](){
        if(nowdownload<downloaditemlist.size()-1)
        {
            nowdownload++;
            downloaditemlist[nowdownload]->start();
        }else {
            isBusy=false;
        }

    });
    QListWidgetItem* pItem = new QListWidgetItem();
    pItem->setSizeHint(QSize(240, 50));
    ui->listWidget->addItem(pItem);
    ui->listWidget->setItemWidget(pItem, di);
    if(!isBusy)
    {
        isBusy=true;
        di->start();
        nowdownload=downloaditemlist.size()-1;
    }
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
    if (Q_NULLPTR == watched) {
        return false;
    }
    if (QEvent::ActivationChange == event->type()) {
        if(QApplication::activeWindow() != this){
            this->close();
        }
    }
    return QWidget::eventFilter(watched, event);
}
void DownloadListWidget::mouseMoveEvent(QMouseEvent *event)
{
    setGeometry(m_rect);
}

void DownloadListWidget::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("file:///tmp/spark-store", QUrl::TolerantMode));
}
