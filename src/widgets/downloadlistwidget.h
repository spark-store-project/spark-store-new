#ifndef DOWNLOADLISTWIDGET_H
#define DOWNLOADLISTWIDGET_H

#include <QWidget>
#include <DBlurEffectWidget>
#include <QNetworkAccessManager>
#include <QDesktopServices>
#include "src/widgets/common/downloaditem.h"
#include "src/backend/sparkapi.h"

DWIDGET_USE_NAMESPACE
namespace Ui {
class DownloadListWidget;
}

class DownloadListWidget : public DBlurEffectWidget
{
    Q_OBJECT

public:
    void addItem(QString name,QString fileName,QString pkgName,const QPixmap icon,QString downloadurl);
    void m_move(int x,int y);
    explicit DownloadListWidget(QWidget *parent = nullptr);
    ~DownloadListWidget();

private:
    bool isBusy = false;
    QStringList dlist;
    QList<DownloadItem*> downloaditemlist;
    int nowdownload=0;
    void clearItem();
    QRect m_rect;
    Ui::DownloadListWidget *ui;
private slots:
    bool eventFilter(QObject *,QEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void on_pushButton_clicked();
};

#endif // DOWNLOADLISTWIDGET_H
