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
    connect(radio1,&QRadioButton::toggled,this,&UserPage::setTimeChartViews);
    connect(radio2,&QRadioButton::toggled,this,&UserPage::setPOIChartViews);

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

    connect(input,&QLineEdit::editingFinished,this,&UserPage::createChart);
}

void UserPage::setTimeChartViews(bool checked){
    if (!checked){
        return;
    }

    for (QChartView *view : chartviews){
        gridLayout->removeWidget(view);
    }

    chartviews.clear();
    timeChartView = new QChartView();
    chartviews << timeChartView;
    gridLayout->addWidget(timeChartView,0,2,3,6);

    qDebug() << "draw time chartview";
}

void UserPage::setPOIChartViews(bool checked){
    if (!checked){
        return;
    }

    qDebug() << "draw poi chart";
}

void UserPage::createTimeChart(){
    QString text = input->text();
    QStringList idsString = text.split(",");
    QVector<int> ids;
    for (int i=0;i<idsString.size();i++){
        bool ok;
        int id = idsString[i].toInt(&ok);
        if (!ok){
            return;
        }
        if (id >= userCnt){
            return;
        }
        ids.push_back(id);
    }

    // up to 3 users
    for (int i=0;i<3&&i<ids.size();i++){
        QVector<POI*> userPOI = userData[ids[i]];
        for (POI* poi : userPOI){

        }
    }
}

void UserPage::createChart(){
    if (radio1->isChecked()){
        createTimeChart();
    }else if (radio2->isChecked()){

    }

}

void UserPage::loadData(){

    for (int i=0;i<data->size();i++){
        int userID = (*data)[i]->userID;
        userData[userID].push_back((*data)[i]);
    }
    userCnt = userData.size();
}
