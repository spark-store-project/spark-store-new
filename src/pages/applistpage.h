#ifndef APPLISTPAGE_H
#define APPLISTPAGE_H
#include <QMutex>
#include <QWidget>
#include <QListWidgetItem>
#include "backend/sparkapi.h"
#include "widgets/common/appitem.h"
namespace Ui {
class AppListPage;
}

class AppListPage : public QWidget
{
    Q_OBJECT

public:
    void setTheme(bool dark);
    void setTitle(QString title);
    void getSearchList(QString keyword);
    void getAppList(QString type);
    explicit AppListPage(QWidget *parent = nullptr);
    ~AppListPage();

private:
    QMutex mutex; // 禁止多次搜索事件同时发生
    void clearItem();
    void addItem(QString name, QString author, QUrl icons, QUrl spk, QString more);
    Ui::AppListPage *ui;
signals:
    void clicked(QUrl spk);
};

#endif // APPLISTPAGE_H
