#include "userpage.h"
#include <QDebug>
#include <QLabel>
#include <QChartView>
#include <QTime>

UserPage::UserPage(QVector<POI*>* data,QWidget *parent) : QWidget(parent)
{
    this->data=data;
    loadData();

    gridLayout = new QGridLayout();
    QLabel *label = new QLabel("user id:");
    gridLayout->addWidget(label,0,0,1,1);
    input = new QLineEdit();
    gridLayout->addWidget(input,0,1,1,1);

    groupBox = new QGroupBox("Options");
    radio1 = new QRadioButton("time trend");

    radio2 = new QRadioButton("top 10 popular POIs");
    connect(radio1,&QRadioButton::toggled,this,&UserPage::setTimeCharts);
    connect(radio2,&QRadioButton::toggled,this,&UserPage::setPOICharts);

    radio1->setChecked(true);
    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    gridLayout->addWidget(groupBox,1,0,2,2);

    gridLayout->setColumnStretch(0,1);
    gridLayout->setColumnMinimumWidth(0,50);
    for (int i=1;i<gridLayout->columnCount();i++){
        gridLayout->setColumnStretch(i,2);
        gridLayout->setColumnMinimumWidth(i,100);
    }
    this->setLayout(gridLayout);
}

void UserPage::setTimeCharts(bool checked){
    if (!checked){
        return;
    }

    QChartView *chartView = new QChartView(createTimeChart());
    gridLayout->addWidget(chartView,0,2,3,6);


    qDebug() << "draw time chart";
}

void UserPage::setPOICharts(bool checked){
    if (!checked){
        return;
    }

    qDebug() << "draw poi chart";
}

QChart * UserPage::createTimeChart(){

    QChart *chart = new QChart();



    return chart;
}

void UserPage::loadData(){

    for (int i=0;i<data->size();i++){
        int userID = (*data)[i]->userID;
        userData[userID].push_back((*data)[i]);
    }
}
