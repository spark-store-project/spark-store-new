#include "appitem.h"
#include "ui_appitem.h"

AppItem::AppItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppItem)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_Hover,true);
    this->installEventFilter(this);
    ui->widget->setStyleSheet("#widget{background-color: rgba(255,255,255,1);border-radius:14px;border:1px solid rgb(229,229,229);}");
}
void AppItem::setTitle(QString title)
{
    ui->cardtitle->setText(title);
}
void AppItem::setIcon(QUrl icon)
{
    QNetworkRequest request;
    naManager=new QNetworkAccessManager(this);
    request.setUrl(icon);
    request.setRawHeader("User-Agent", "Mozilla/5.0");

    request.setRawHeader("Content-Type", "charset='utf-8'");
    request.setRawHeader("Content-Type", "application/json");

    naManager->get(request);
    QObject::connect(naManager,&QNetworkAccessManager::finished,this,&AppItem::setPic);
}
void AppItem::setPic(QNetworkReply *reply)
{
    QByteArray jpegData = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(jpegData);
    pixmap.scaled(100, 70, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui->pic->setPixmap(pixmap);
    ui->pic->setScaledContents(true);
}
void AppItem::setMore(QString more)
{
    ui->more->setText(more);
}
void AppItem::setAuthor(QString author)
{
    ui->author->setText(author);
}
void AppItem::setSpk(QUrl spk)
{
    AppItem::spk=spk;
}
void AppItem::mousePressEvent(QMouseEvent *ev)
{
    emit clicked(spk);
}
bool AppItem::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == this) {
        if(event->type() == QEvent::HoverEnter) {
            QPropertyAnimation *a1 = new QPropertyAnimation(ui->widget, "pos");
            a1->setDuration(500);
            a1->setStartValue(QPoint(8, 8));
            a1->setEndValue(QPoint(8, 1));
            a1->setEasingCurve(QEasingCurve::OutBack);
            a1->start();
            return true;
        }else if(event->type()== QEvent::HoverLeave){
            QPropertyAnimation *a1 = new QPropertyAnimation(ui->widget, "pos");
            a1->setDuration(500);
            a1->setStartValue(QPoint(8, 1));
            a1->setEndValue(QPoint(8, 8));
            a1->setEasingCurve(QEasingCurve::OutBack);
            a1->start();
        }
    }
    return QWidget::eventFilter(obj,event);
}
AppItem::~AppItem()
{
    QPixmapCache::clear();
    delete naManager;
    delete ui;
    naManager = NULL;
    ui = NULL;
}
