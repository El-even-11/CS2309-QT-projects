#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "welcomedialog.h"

#include <QProgressDialog>

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
}

MainWidget::~MainWidget()
{
    delete ui;

    for (int i=0;i<data.size();i++){
        delete data[i];
    }
}

bool MainWidget::loadData(){
    QProgressDialog *dialog = new QProgressDialog();
    dialog->setLabelText("LOADING...");

    qint64 size=file->size();
    qDebug() << size;

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
        data.push_back(poi);

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

