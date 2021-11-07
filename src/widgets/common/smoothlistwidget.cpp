#include "smoothlistwidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QWheelEvent>
#include <QDebug>
SmoothListWidget::SmoothListWidget(QWidget *parent) : QListWidget(parent)
{
    vScrollBar->setOrientation(Qt::Orientation::Vertical); //将滚动条设置为纵向
    setVerticalScrollBar(vScrollBar); //设置纵向滚动条
    connect(vScrollBar, SIGNAL(valueChanged(int)), this, SLOT(onSliderChanged(int)));
}
void SmoothListWidget::addItem(QString name,QString author,QUrl icons,QUrl spk,QString more)
{
    AppItem *ai=new AppItem(this);
    ai->setAuthor(author);
    ai->setTitle(name);
    ai->setIcon(icons);
    ai->setSpk(spk);
    ai->setMore(more);
    QListWidgetItem* pItem = new QListWidgetItem();
    pItem->setSizeHint(QSize(240, 250));
    addItem(pItem);
    setItemWidget(pItem, ai);
}
void SmoothListWidget::clearItem()
{
    vScrollBar->scrollTop();
    int n=count();
    for(int i=0;i<n;i++)
    {
        QListWidgetItem *item = takeItem(0);
        QWidget *card = itemWidget(item);
        delete card;
        card  = NULL;
        delete item;
        item  = NULL;
    }
    clear();
}
void SmoothListWidget::wheelEvent(QWheelEvent *e)
{
    //当捕获到事件后，调用相对滚动的槽函数
    vScrollBar->scroll(e->angleDelta().y());
}
void SmoothListWidget::onSliderChanged(int p)
{
    int startRow = count();
    if (p == vScrollBar->maximum())
    {
        emit reachedBottom(); // 1
    }
    emit msliderChanged(p);  // 2
}
