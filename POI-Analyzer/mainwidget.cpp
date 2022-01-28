#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "welcomedialog.h"
#include "loadthread.h"

#include <QProgressDialog>
#include <QGroupBox>
#include <QRadioButton>


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    WelcomeDialog *wdialog = new WelcomeDialog();

    QString filename;
    QFile *file;
    bool finished=false;

    while (!finished){
        int res = wdialog->exec();
        if (res == QDialog::Accepted){
            filename = wdialog->getFilename();
            file = new QFile(filename);
            file->open(QIODevice::ReadOnly|QIODevice::Text);
            qDebug() << filename;
            filesize = file->size();
            finished = loadData(file);
        }else if (res == QDialog::Rejected){
            exit(0);
        }
    }
    delete wdialog;
    delete file;
    setStyleSheets();
    setTabs();
}

MainWidget::~MainWidget()
{
    delete ui;
}

bool MainWidget::loadData(QFile* file){
    QProgressDialog *dialog = new QProgressDialog();
    dialog->setLabelText("LOADING...");

    dialog->setFixedSize(450,250);
    dialog->setRange(0,file->size());
    dialog->setWindowModality(Qt::WindowModal);
    dialog->show();

    LoadThread *lt = new LoadThread();
    connect(lt,&LoadThread::sendNum,dialog,&QProgressDialog::setValue);
    connect(dialog,&QProgressDialog::canceled,lt,&LoadThread::terminate);
    connect(lt,&LoadThread::sendData,this,&MainWidget::getData);
    lt->setFile(file);
    lt->start();
    lt->wait();
    bool finished = !dialog->wasCanceled();

    dialog->close();
    delete dialog;
    return finished;
}

void MainWidget::setTabs(){

    userPage = new UserPage(&userData,datasize);
    poiPage = new POIPage(&poiData,datasize);
    mapPage = new MapPage(&userData,&poiData,datasize);

    ui->tabWidget->addTab(userPage,"USER");
    ui->tabWidget->addTab(poiPage,"POI");
    ui->tabWidget->addTab(mapPage,"MAP");
}

void MainWidget::getData(QList<POI*>* data){
    datasize = data->size();
    QListIterator<POI*> it1(*data);
    while (it1.hasNext()){
        POI* poi = it1.next();
        int userID = poi->userID;
        if (userID>=userData.size()){
            userData << QList<POI*>();
        }
        userData[userID] << poi;
    }

    QListIterator<POI*> it2(*data);
    while (it2.hasNext()){
        POI* poi = it2.next();
        int locID = poi->locID;
        if (locID>=poiData.size()){
            poiData << QList<POI*>();
        }
        poiData[locID] << poi;
    }
    delete data;
}

void MainWidget::setStyleSheets(){
    setStyleSheet(
            "QHeaderView::section{"
                "border-top:1px solid #D8D8D8;"
                "border-left:1px solid #D8D8D8;"
                "border-right:1px solid #D8D8D8;"
                "border-bottom: 1px solid #D8D8D8;"
                "background-color:white;"
                "padding:4px;"
            "}"
            "QTableCornerButton::section{"
                "border-top:0px solid #D8D8D8;"
                "border-left:0px solid #D8D8D8;"
                "border-right:0px solid #D8D8D8;"
                "border-bottom:0px solid #D8D8D8;"
                "background-color:white;"
            "}"
            "QScrollBar:vertical{"
                "border-top:1px solid #D8D8D8;"
                "border-left:0px solid #D8D8D8;"
                "border-right:0px solid #D8D8D8;"
                "border-bottom:0px solid #D8D8D8;"
            "}"
            "QScrollBar:horizontal{"
                "border-top:0px solid #D8D8D8;"
                "border-left:1px solid #D8D8D8;"
                "border-right:0px solid #D8D8D8;"
                "border-bottom:0px solid #D8D8D8;"
            "}"
            );
}



