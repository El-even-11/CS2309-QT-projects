#include "welcomedialog.h"
#include "ui_welcomedialog.h"

#include <QFileDialog>

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeDialog)
{
    ui->setupUi(this);

    connect(ui->pushButton,&QPushButton::clicked,this,&WelcomeDialog::setFile);
}

WelcomeDialog::~WelcomeDialog()
{
    delete ui;
}

void WelcomeDialog::setFile(){
    filename=QFileDialog::getOpenFileName(0,"Select csv file","/","(*.csv)");
    if (!filename.isEmpty()){
        this->accept();
    }
}

QString WelcomeDialog::getFilename(){
    return filename;
}
