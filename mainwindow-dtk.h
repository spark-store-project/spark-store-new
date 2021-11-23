#ifndef MAINWINDOWDTK_H
#define MAINWINDOWDTK_H

#include <DMainWindow>
#include <DTitlebar>
#include <DSearchEdit>
#include <QGraphicsDropShadowEffect>
#include <DGuiApplicationHelper>
#include <QPushButton>
#include <QDir>
#include <QDesktopServices>
#include "src/widgets/downloadlistwidget.h"
DWIDGET_USE_NAMESPACE
namespace Ui {
class MainWindow;
}

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    void openUrl(QUrl);
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
private:
    QList<int> pageHistory;
    void switchPage(int now)
    void initConfig();
    void updateUi(int now);
    DownloadListWidget *downloadlistwidget;
    QPushButton *downloadButton;
    QPushButton *backButton;
    DSearchEdit *searchEdit=new DSearchEdit;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOWDTK_H
