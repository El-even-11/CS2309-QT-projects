#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "welcomedialog.h"
#include "progressdialog.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    WelcomeDialog *wdialog = new WelcomeDialog();
    ProgressDialog *pdialog = new ProgressDialog();
    int res;
    do{
        res = wdialog->exec();
        if (res == QDialog::Accepted){
            filename = wdialog->getFilename();
            file = new QFile(filename);
            file->open(QIODevice::ReadOnly|QIODevice::Text);
            qDebug() << filename;
        }else if (res == QDialog::Rejected){
            exit(0);
        }
        res = pdialog->exec();
    }while (res == QDialog::Rejected);

}

MainWidget::~MainWidget()
{
    delete ui;
}

