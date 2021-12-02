#include "progressdialog.h"
#include "ui_progressdialog.h"

ProgressDialog::ProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    this->parent=(MainWidget*)parent;

    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&ProgressDialog::cancel);
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::cancel(){
    this->reject();
}

void ProgressDialog::setRange(int start,int end){
    ui->progressBar->setRange(start,end);
}

void ProgressDialog::setValue(int val){
    ui->progressBar->setValue(val);
}
