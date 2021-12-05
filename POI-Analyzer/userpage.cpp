#include "userpage.h"
#include <QDebug>
#include <QLabel>
#include <QTime>
#include <QSet>
#include <algorithm>

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

    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    gridLayout->addWidget(groupBox,1,0,2,2);
    chartContainer = new QWidget();
    gridLayout->addWidget(chartContainer,0,2,3,6);
    containerLayout = new QGridLayout();
    chartContainer->setLayout(containerLayout);

    gridLayout->setColumnStretch(0,1);
    gridLayout->setColumnMinimumWidth(0,50);
    for (int i=1;i<gridLayout->columnCount();i++){
        gridLayout->setColumnStretch(i,2);
        gridLayout->setColumnMinimumWidth(i,100);
    }
    this->setLayout(gridLayout);

    radio1->setChecked(true);
    connect(input,&QLineEdit::editingFinished,this,&UserPage::setChartViews);
}

void UserPage::setTimeChartViews(bool checked){
    if (!checked){
        return;
    }

    for (QChartView *view : chartviews){
        containerLayout->removeWidget(view);
    }
    chartviews.clear();
    timeChartView = new QChartView();
    timeChartView->setRenderHint(QPainter::Antialiasing,true);
    chartviews << timeChartView;
    containerLayout->addWidget(timeChartView,0,0);

    qDebug() << "draw time chartview";
    createTimeChart();
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
    QSet<int> idset;
    QList<int> ids;

    for (int i=0;i<idsString.size();i++){
        bool ok;
        int id = idsString[i].toInt(&ok);
        if (!ok){
            return;
        }
        if (id >= userCnt){
            qDebug() << userCnt;
            return;
        }
        idset.insert(id);
    }

    if (timeChart!=nullptr){
        timeChart->removeAllSeries();
        delete timeChart;
    }

    QSetIterator<int> it(idset);
    // up to 5 users
    while (it.hasNext()){
        int id=it.next();
        ids << id;
    }

    timeChart = new QChart();
    timeChart->setLocale(QLocale::English);
    timeChart->setAnimationOptions(QChart::SeriesAnimations);
    timeChart->setAnimationDuration(100);

    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(POI::monthRange.size());
    axisX->setFormat("MMM yyyy");
    timeChart->addAxis(axisX,Qt::AlignBottom);
    QValueAxis *axisY = new QValueAxis();
    axisY->setTickCount(8);
    axisY->setLabelFormat("%d");
    axisY->setTitleText("Checking-ins count");
    timeChart->addAxis(axisY,Qt::AlignLeft);

    int maxCnt = 0;
    std::sort(ids.begin(),ids.end());
    // up to 5 users
    for (int i=0;i<ids.size()&&i<5;i++){
        QVector<POI*> userPOI = userData[ids[i]];
        QSplineSeries *series = new QSplineSeries();

        QHash<QDate,int> cnt;
        for (QDate date : POI::monthRange){
            cnt[date]=0;
        }
        for (POI* poi : userPOI){
            QDate date = POI::getDate(poi->time);
            cnt[QDate(date.year(),date.month(),15)]++;
        }
        for (QDate date : POI::monthRange){
            QDateTime momentInTime;
            momentInTime.setDate(date);
            maxCnt = maxCnt>cnt[date]?maxCnt:cnt[date];
            series->append(momentInTime.toMSecsSinceEpoch(),cnt[date]);
        }
        series->setName("user "+QString::number(ids[i]));
        timeChart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }

    axisY->setRange(0,maxCnt*5/4);

    timeChartView->setChart(timeChart);
}

void UserPage::setChartViews(){
    if (radio1->isChecked()){
        setTimeChartViews(true);
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
