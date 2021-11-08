#include "appitem.h"
#include "ui_appitem.h"

AppItem::AppItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppItem)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_Hover,true);
    this->installEventFilter(this);
    auto *defaultShadow = new QGraphicsDropShadowEffect(this);
    defaultShadow->setBlurRadius(14.0);
    defaultShadow->setColor(QColor(0, 0, 0, 30));
    defaultShadow->setOffset(0, 0);
    ui->widget->setGraphicsEffect(defaultShadow);
    delete defaultShadow;
    ui->widget->setStyleSheet("#widget{background-color: rgba(255,255,255,0.8);border-radius:14px;}");
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

    // 画成圆形图片
    int width = ui->pic->width();
    int height = ui->pic->height();
    QSize size(width, height);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 14, 14);//修改这个值，可以改弧度，和直径相等就是圆形
    QPixmap image = pixmap.scaled(size);
    image.setMask(mask);


    ui->pic->setPixmap(image);
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
void AppItem::resizeEvent(QResizeEvent *event)
{
    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();
    ui->widget->setGeometry(5,10,x-5,y-15);
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
            a1->setStartValue(QPoint(5, 10));
            a1->setEndValue(QPoint(5, 3));
            a1->setEasingCurve(QEasingCurve::OutBack);
            a1->start();
            return true;
        }else if(event->type()== QEvent::HoverLeave){
            QPropertyAnimation *a1 = new QPropertyAnimation(ui->widget, "pos");
            a1->setDuration(500);
            a1->setStartValue(QPoint(5, 3));
            a1->setEndValue(QPoint(5, 10));
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
