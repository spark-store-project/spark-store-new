#ifndef DOWNLOADLISTWIDGET_H
#define DOWNLOADLISTWIDGET_H

#include <QWidget>
#include <DBlurEffectWidget>
#include "src/widgets/common/downloadditem.h"
#include "src/backend/sparkapi.h"

DWIDGET_USE_NAMESPACE
namespace Ui {
class DownloadListWidget;
}

class DownloadListWidget : public DBlurEffectWidget
{
    Q_OBJECT

public:
    void addItemSpk(QUrl spk);
    void addItem(QString name,QString fileName,QString pkgName,const QPixmap icon,QString downloadurl);
    void m_move(int x,int y);
    explicit DownloadListWidget(QWidget *parent = nullptr);
    ~DownloadListWidget();

private:
    void clearItem();
    QRect m_rect;
    Ui::DownloadListWidget *ui;
private slots:
    bool eventFilter(QObject *,QEvent *);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // DOWNLOADLISTWIDGET_H
