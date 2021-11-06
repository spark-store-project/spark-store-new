#include "mainwindow-dtk.h"
#include <QObject>
#include <DWidgetUtil>
#include <DApplication>
DWIDGET_USE_NAMESPACE
int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.loadTranslator();     // 载入翻译
    DApplication::setAttribute(Qt::AA_EnableHighDpiScaling);    // 开启 Hidpi 支持
        // 限制单实例运行
    if(!a.setSingleInstance("spark-store"))
    {
        return -1;
    }
    MainWindow w(nullptr);
    a.setProductName(QLabel::tr("Spark Store"));
    w.setWindowTitle(QObject::tr("Spark Store"));
    DApplication::setWindowIcon(QIcon::fromTheme(":/icon/logo.png"));
    w.show();
    Dtk::Widget::moveToCenter(&w);//让窗口居中显示
    return a.exec();
}
