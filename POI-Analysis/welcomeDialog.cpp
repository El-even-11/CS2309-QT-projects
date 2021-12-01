#include "welcomeDialog.h"

#include <QFileDialog>

WelcomeDialog::WelcomeDialog(){
    this->resize(300,200);

    container = new QVBoxLayout();
    label = new QLabel("Welcome to POI Analyzer! Select a csv file to start.");
    btn = new QPushButton("select");

    label->setAlignment(Qt::AlignCenter);

    container->addWidget(label);
    container->addWidget(btn);
    this->setLayout(container);

    connect(btn,&QPushButton::clicked,this,&WelcomeDialog::setFile);
}

void WelcomeDialog::setFile(){
    filename=QFileDialog::getOpenFileName(0,"Select csv file","/","(*.csv)");

    qDebug() << filename;

    this->accept();
}

QString WelcomeDialog::getFilename(){
    return filename;
}
