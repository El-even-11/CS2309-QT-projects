#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "welcomedialog.h"

#include <QProgressDialog>
#include <QGroupBox>
#include <QRadioButton>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    WelcomeDialog *wdialog = new WelcomeDialog();

    bool finished=false;

    while (!finished){
        int res = wdialog->exec();
        if (res == QDialog::Accepted){
            filename = wdialog->getFilename();
            file = new QFile(filename);
            file->open(QIODevice::ReadOnly|QIODevice::Text);
            qDebug() << filename;
        }else if (res == QDialog::Rejected){
            exit(0);
        }
        finished = loadData();
    }
    setStyleSheets();
    setTabs();
}

MainWidget::~MainWidget()
{
    delete ui;

    QListIterator<POI*> it(data);
    while (it.hasNext()){
        POI *poi = it.next();
        delete poi;
    }
}

bool MainWidget::loadData(){
    QProgressDialog *dialog = new QProgressDialog();
    dialog->setLabelText("LOADING...");

    qint64 size=file->size();
    qDebug() << size;

    dialog->setFixedSize(450,250);
    dialog->setRange(0,size);
    dialog->setWindowModality(Qt::WindowModal);
    dialog->show();

    QTextStream in(file);

    int readBytes = 0;
    bool finished = true;
    int factor = 0;
    int interval = size / 100;
    while (!in.atEnd()){
        QString line = in.readLine();
        readBytes+=line.length()+2;
        QStringList list=line.split(",");

        POI* poi=new POI(list[0].toInt(),list[1].toInt(),list[2],list[3].toDouble(),list[4].toDouble());
        data << poi;

        if (readBytes > interval*factor){
            dialog->setValue(readBytes);
            factor++;
        }

        if (dialog->wasCanceled()){
            finished=false;
            data.clear();
            break;
        }
    }
    if (finished){
        dialog->setValue(size);
        qDebug() << readBytes;
    }
    dialog->close();
    delete dialog;

    return finished;
}

void MainWidget::setTabs(){

    QListIterator<POI*> it1(data);
    while (it1.hasNext()){
        POI* poi = it1.next();
        int userID = poi->userID;
        if (userID>=userData.size()){
            userData << QList<POI*>();
        }
        userData[userID] << poi;
    }

    QListIterator<POI*> it2(data);
    while (it2.hasNext()){
        POI* poi = it2.next();
        int locID = poi->locID;
        if (locID>=poiData.size()){
            poiData << QList<POI*>();
        }
        poiData[locID] << poi;
    }

    userPage = new UserPage(&userData,data.size());
    poiPage = new POIPage(&poiData,data.size());
    mapPage = new MapPage(&userData,&poiData,data.size());

    ui->tabWidget->addTab(userPage,"USER");
    ui->tabWidget->addTab(poiPage,"POI");
    ui->tabWidget->addTab(mapPage,"MAP");
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
