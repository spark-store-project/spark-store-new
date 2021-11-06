#ifndef MAINWINDOWDTK_H
#define MAINWINDOWDTK_H

#include <DMainWindow>
#include <DTitlebar>
#include <DSearchEdit>
#include <QGraphicsDropShadowEffect>
#include <DGuiApplicationHelper>
#include <QPushButton>
DWIDGET_USE_NAMESPACE
namespace Ui {
class MainWindow;
}

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
private:
    void initPage(int now);
    void updateUi(int now);
    DSearchEdit *searchEdit=new DSearchEdit;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOWDTK_H
