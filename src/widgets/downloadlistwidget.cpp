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
