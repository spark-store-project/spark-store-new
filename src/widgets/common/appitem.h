#ifndef APPITEM_H
#define APPITEM_H
#include <QObject>
#include <QWidget>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QBitmap>
#include <QPainter>
#include <QPainterPath>
#include <QDesktopServices>
#include <QPixmapCache>
namespace Ui {
class AppItem;
}

class AppItem : public QWidget
{
    Q_OBJECT

public:
    void setTitle(QString title);
    void setAuthor(QString author);
    void setSpk(QUrl spk);
    void setIcon(QUrl icon);
    void setMore(QString more);
    explicit AppItem(QWidget *parent = nullptr);
    ~AppItem();
private slots:
    void setPic(QNetworkReply *reply);

private:
    QNetworkAccessManager *naManager;
    QUrl spk;
    Ui::AppItem *ui;
signals:
    void clicked(QUrl spk);

protected:
    void mousePressEvent(QMouseEvent *ev);
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // APPITEM_H
