#include "progressdialog.h"
#include "ui_progressdialog.h"

ProgressDialog::ProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
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
