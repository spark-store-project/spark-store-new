#include "appintopage.h"
#include "ui_appintopage.h"
AppIntoPage::AppIntoPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppIntoPage)
{
    ui->setupUi(this);
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setMovement(QListView::Static);
    ui->listWidget->setMaximumHeight(200);
    ui->listWidget->setFlow(QListView::TopToBottom);
    clear();
}

void AppIntoPage::clear()
{
    ui->tag_a2d->hide();
    ui->tag_uos->hide();
    ui->tag_dtk5->hide();
    ui->tag_deepin->hide();
    ui->tag_dwine2->hide();
    ui->tag_dwine5->hide();
    ui->tag_ubuntu->hide();
    ui->tag_community->hide();
    ui->icon->clear();
    ui->title->clear();
    ui->author->clear();
    ui->label_2->clear();
    ui->downloadButton->hide();
    ui->pushButton_3->hide();
    int n=ui->listWidget->count();
    for(int i=0;i<n;i++)
    {
        QListWidgetItem *item = ui->listWidget->takeItem(0);
        QWidget *card = ui->listWidget->itemWidget(item);
        delete card;
        card  = NULL;
        delete item;
        item  = NULL;
    }
    ui->listWidget->clear();
}
void AppIntoPage::setDownloadWidget(DownloadListWidget *w)
{
    dw=w;
}
void AppIntoPage::openUrl(QUrl url)
{
    spk=url;
    SparkAPI *api=new SparkAPI(this);
    connect(api,&SparkAPI::finishedObject,[=](QJsonObject appinfo){

        info = appinfo;
        qDebug()<<url;
        //获取图标
        QNetworkAccessManager *naManager;
        QNetworkRequest request;
        naManager=new QNetworkAccessManager(this);
        request.setUrl(QUrl(api->getImgServerUrl()+"store"+url.path() + "/icon.png"));
        request.setRawHeader("User-Agent", "Mozilla/5.0");
        request.setRawHeader("Content-Type", "charset='utf-8'");
        naManager->get(request);
        QObject::connect(naManager,&QNetworkAccessManager::finished,[=](QNetworkReply *reply){
                QByteArray jpegData = reply->readAll();
                iconpixmap.loadFromData(jpegData);
                iconpixmap.scaled(210, 200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                ui->icon->setPixmap(iconpixmap);
                ui->icon->setScaledContents(true);
            });
        ui->title->setText(info["Name"].toString());
        ui->author->setText(info["Author"].toString());
        ui->d_author->setText(info["Author"].toString());
        ui->d_size->setText(info["Size"].toString());
        ui->d_update->setText(info["Update"].toString());
        ui->d_pkgname->setText(info["Pkgname"].toString());
        ui->d_website->setText("<a href=\""+info["Website"].toString()+"\">"+tr("Click Open"));
        ui->d_contributor->setText(info["Contributor"].toString());
        ui->label_2->setText(info["More"].toString());

        QProcess isInstall;
        bool isInstalled;
        bool isUpdated;
        QString packagename = info["Pkgname"].toString();
        isInstall.start("dpkg -s " + info["Pkgname"].toString());
        isInstall.waitForFinished();
        int error = QString::fromStdString(isInstall.readAllStandardError().toStdString()).length();
        if(error == 0)
        {
            isInstalled = true;

            QProcess isUpdate;
            isUpdate.start("dpkg-query --showformat='${Version}' --show " + info["Pkgname"].toString());
            isUpdate.waitForFinished();
            QString localVersion = isUpdate.readAllStandardOutput();
            localVersion.replace("'", "");

            isUpdate.start("dpkg --compare-versions " + localVersion + " ge " + info["Version"].toString());
            isUpdate.waitForFinished();
            if(!isUpdate.exitCode())
            {
                isUpdated = true;
            }
            else
            {
                isUpdated = false;
            }
        }
        else
        {
            isInstalled = false;
            isUpdated = false;
        }

        if(isInstalled)
        {
            if(isUpdated)
            {
                ui->downloadButton->setText(tr("Reinstall"));
                ui->pushButton_3->show();
            }
            else
            {
                ui->downloadButton->setText(tr("Upgrade"));
                ui->pushButton_3->show();
            }
        }
        else
        {
            ui->downloadButton->setText(tr("Install"));
            ui->downloadButton->show();
        }
        QStringList taglist = info["Tags"].toString().split(";");
        QString tmp=info["img_urls"].toString();
        qDebug()<<tmp;
        if(tmp.left(2)=="[\"")
        {
            tmp.remove(0,2);
        }
        if(tmp.right(2)=="\"]")
        {
            tmp.remove(tmp.size()-2,tmp.size());
        }
        QStringList imglist = tmp.split("\",\"");
        qDebug()<<imglist;
        for(int i=0;i < imglist.size();i++)
        {
            QNetworkAccessManager *naManager;
            QNetworkRequest request;
            naManager=new QNetworkAccessManager(this);
            request.setUrl(QUrl(imglist[i]));
            request.setRawHeader("User-Agent", "Mozilla/5.0");
            request.setRawHeader("Content-Type", "charset='utf-8'");
            naManager->get(request);
            QObject::connect(naManager,&QNetworkAccessManager::finished,[=](QNetworkReply *reply){
                    QByteArray jpegData = reply->readAll();
                    QPixmap pixmap;
                    pixmap.loadFromData(jpegData);
                    pixmap.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                    image_show *img=new image_show(this);
                    img->setImage(pixmap);
                    //img->setScaledContents(true);
                    QListWidgetItem* pItem = new QListWidgetItem();
                    pItem->setSizeHint(QSize(280, 200));
                    ui->listWidget->addItem(pItem);
                    ui->listWidget->setItemWidget(pItem, img);
                });
        }
        this->sltAppinfoTags(&taglist);
        disconnect(api,&SparkAPI::finished,nullptr,nullptr);
        api->deleteLater();
    });
    api->getAppInfo(url);
}
void AppIntoPage::sltAppinfoTags(QStringList *tagList)
{
    foreach(const QString &tag, *tagList)
    {
        if(tag=="community")
        {
            ui->tag_community->show();
        }
        else if(tag=="ubuntu")
        {
            ui->tag_ubuntu->show();
        }
        else if(tag=="deepin")
        {
            ui->tag_deepin->show();
        }
        else if(tag=="uos")
        {
            ui->tag_uos->show();
        }
        else if(tag=="dtk5")
        {
            ui->tag_dtk5->show();
        }
        else if(tag=="dwine2")
        {
            ui->tag_dwine2->show();
        }
        else if(tag=="dwine5")
        {
            ui->tag_dwine5->show();
        }
        else if(tag=="a2d")
        {
            ui->tag_a2d->show();
        }
    }
}
void AppIntoPage::setTheme(bool dark)
{
    if(dark)
    {}else {
        //亮色模式
        this->setStyleSheet("#frame{background-color: #fbfbfb;border-radius:14px;border:1px solid rgb(229,229,229);}\
                             #frame_2{background-color: #fbfbfb;border-radius:14px;border:1px solid rgb(229,229,229);}\
                             #frame_3{background-color: #fbfbfb;border-radius:14px;border:1px solid rgb(229,229,229);}\
                             #frame_4{background-color: #fbfbfb;border-radius:14px;border:1px solid rgb(229,229,229);}");

        ui->icon_1->setPixmap(QPixmap(":/icon/light/box.svg"));
        ui->icon_2->setPixmap(QPixmap(":/icon/light/box.svg"));
        ui->icon_3->setPixmap(QPixmap(":/icon/light/calendar.svg"));
        ui->icon_4->setPixmap(QPixmap(":/icon/light/text.svg"));
        ui->icon_5->setPixmap(QPixmap(":/icon/light/folder.svg"));
        ui->icon_6->setPixmap(QPixmap(":/icon/light/globe.svg"));

    }
}
AppIntoPage::~AppIntoPage()
{
    delete ui;
}

void AppIntoPage::on_downloadButton_clicked()
{
    dw->addItem(info["Name"].toString(),info["Filename"].toString(),info["Pkgname"].toString(),iconpixmap,SparkAPI::getServerUrl()+"store"+spk.path()+"/"+info["Filename"].toString());
}

void AppIntoPage::on_pushButton_3_clicked()
{
    QtConcurrent::run([=]()
    {
                                    ui->downloadButton->setEnabled(false);
                                    ui->pushButton_3->setEnabled(false);

                                    QProcess uninstall;
                                    uninstall.start("pkexec", QStringList() << "apt" << "purge" << "-y" << info["Pkgname"].toString().toLower());
                                    uninstall.waitForFinished();

                                    QProcess check;
                                    check.start("dpkg", QStringList() << "-s" << info["Pkgname"].toString().toLower());
                                    check.waitForFinished();

                                    if (check.readAllStandardOutput().isEmpty())
                                    {
                                        ui->downloadButton->setText(tr("Install"));
                                        ui->pushButton_3->hide();

                                        updatesEnabled();
                                        //sendNotification(tr("Uninstall succeeded"));
                                    }

                                    ui->downloadButton->setEnabled(true);
                                    ui->pushButton_3->setEnabled(true);
                                });
}
