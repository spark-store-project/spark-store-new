#ifndef APPLISTPAGE_H
#define APPLISTPAGE_H

#include <QWidget>
#include <QListWidgetItem>
#include "src/backend/sparkapi.h"
#include "src/widgets/common/appitem.h"
namespace Ui {
class AppListPage;
}

class AppListPage : public QWidget
{
    Q_OBJECT

public:
    void getSearchList(QString keyword);
    void getAppList(QString type);
    explicit AppListPage(QWidget *parent = nullptr);
    ~AppListPage();

private slots:
    void on_pushButton_clicked();
private:
    void clearItem();
    void addItem(QString name,QString author,QUrl icons,QUrl spk,QString more);
    Ui::AppListPage *ui;
signals:
    void clicked(QUrl spk);
};

#endif // APPLISTPAGE_H
