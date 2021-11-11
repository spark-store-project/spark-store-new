#ifndef DOWNLOADLISTWIDGET_H
#define DOWNLOADLISTWIDGET_H

#include <QWidget>
#include <DBlurEffectWidget>
DWIDGET_USE_NAMESPACE
namespace Ui {
class DownloadListWidget;
}

class DownloadListWidget : public DBlurEffectWidget
{
    Q_OBJECT

public:
    void m_move(int x,int y);
    explicit DownloadListWidget(QWidget *parent = nullptr);
    ~DownloadListWidget();

private:
    QRect m_rect;
    Ui::DownloadListWidget *ui;
private slots:
    bool eventFilter(QObject *,QEvent *);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // DOWNLOADLISTWIDGET_H
