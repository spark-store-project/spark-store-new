#include "mainwindow-dtk.h"
#include "ui_mainwindow-dtk.h"

MainWindow::MainWindow(QWidget *parent) :
    DMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->titlebar->setBackgroundTransparent(true);
    titlebar()->setFixedSize(0,0);//隐藏标题栏
    setTitlebarShadowEnabled(false);//去除标题栏阴影
    //ui->titlebar->setMenuVisible(false);//去除dtk标题栏菜单
    auto *defaultShadow = new QGraphicsDropShadowEffect();
    defaultShadow->setBlurRadius(14.0);
    defaultShadow->setColor(QColor(0, 0, 0, 30));
    defaultShadow->setOffset(0, 0);
    ui->mainpage->setGraphicsEffect(defaultShadow);


    //主题切换
    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged, this, [=](DGuiApplicationHelper::ColorType themeType) {
        if(themeType==DGuiApplicationHelper::DarkType){
            //深色模式

        }else {
            //亮色模式
            this->setStyleSheet("#mainpage{background-color: rgba(249,249,249,0.8);border-radius:14px;}\
                                QWidget#leftbar QPushButton{text-align: left;padding-left: 10px;background-color:transparent;}\
                                QWidget#leftbar QPushButton:hover{text-align: left;padding-left: 10px;background-color:#eAeAeA;border:0px;border-radius:8px;}\
                                QWidget#leftbar QPushButton:checked{text-align: left;padding-left: 10px;background-color:#dddddd;border:0px;border-radius:8px;}\
                                QLabel#cardtitle,QLabel#title {color:#000000}\
                                ");
        }
    });


    //初始化标题栏控件
    downloadButton=new QPushButton(this);
    backButtom=new QPushButton(this);
    backButtom->hide();
    ui->titlebar->setIcon(QIcon::fromTheme(":/icon/logo.png"));
    QWidget *w_titlebar = new QWidget(this);
    QHBoxLayout *ly_titlebar = new QHBoxLayout(this);
    w_titlebar->setLayout(ly_titlebar);
    QLabel *title=new QLabel(this);
    title->setText(tr("Spark Store"));
    searchEdit->setPlaceholderText(tr("Search or enter spk://"));
    ly_titlebar->addWidget(title);
    ly_titlebar->addWidget(backButtom);
    ly_titlebar->addSpacing(10);
    ly_titlebar->addStretch();
    ly_titlebar->addWidget(searchEdit);
    ly_titlebar->addWidget(downloadButton);
    ly_titlebar->addStretch();

    ui->titlebar->setCustomWidget(w_titlebar);

    //侧边栏按钮
    int i=0;
    while (i<ui->buttonGroup->buttons().size()) {
        ui->buttonGroup->buttons()[i]->setIcon(QIcon::fromTheme(":/icon/light/"+QString::number(i)+".svg"));
        connect(ui->buttonGroup->buttons()[i],&QPushButton::toggled,[=](){
            updateUi(i);
        });
        i++;
    }

    // 搜索事件
    connect(searchEdit, &DSearchEdit::returnPressed, this, [=]()
    {
        QString searchtext = searchEdit->text();
        if(!searchtext.isEmpty())
        {
            if(text.left(6) == "spk://")
            {
                openUrl(searchtext);
                searchEdit->clearEdit();
            }else{
                ui->applistpage->getSearchList(searchtext);
                switchPage(1028);
                searchEdit->clearEdit();
            }
        }
        this->setFocus();
    });

}
void MainWindow::initConfig()
{
    // 新建临时文件夹
    QDir dir("/tmp");
    dir.mkdir("spark-store");
}
void MainWindow::openUrl(QUrl url)
{
    if(url.toString().left(6) == "spk://")
    {
        ui->appintopage->openUrl(url);
    }else{
        QDesktopServices::openUrl(url);
    }
}
void MainWindow::switchPage(int now)//临时方案，回家后修改
{
    if(pageHistory.count()>1)
    {
        backButtom->show();
    }else{
        backButtom->hide();
    }
    ui->stackedWidget->setCurrentIndex(now);
    pageHistory<<now;
}

//刷新界面
void MainWindow::updateUi(int now)
{
    pageHistory.clear();
    if(now == 0)
    {
        switchPage(0);
    }else{
        QStringList itemlist;
        itemlist<<"network"<<"chat"<<"music"<<"video"<<"image_graphics"<<"games"<<"office"<<"reading"<<"development"<<"tools"<<"themes"<<"others";
        ui->applistpage->getAppList(itemlist[now+1]);
        switchPage(1);
    }
}
MainWindow::~MainWindow()
{
    delete searchEdit;
    delete ui;
}
