#include "userpage.h"
#include <QDebug>
#include <QLabel>
#include <QTime>
#include <QSet>
#include <algorithm>
#include <queue>

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

    qDebug() << "set time chartview";
    for (QChartView *view : chartviews){
        containerLayout->removeWidget(view);
        qDebug() << "remove";
    }
    chartviews.clear();
    timeChartView = new QChartView();
    timeChartView->setRenderHint(QPainter::Antialiasing,true);
    chartviews << timeChartView;
    containerLayout->addWidget(timeChartView,0,0);

    createTimeChart();
}

void UserPage::setPOIChartViews(bool checked){
    if (!checked){
        return;
    }

    qDebug() << "set poi chartview";
    for (QChartView *view : chartviews){
        containerLayout->removeWidget(view);
        qDebug() << "remove";
    }
    chartviews.clear();
    poiChartView = new QChartView();
    poiChartView->setRenderHint(QPainter::Antialiasing,true);
    chartviews << poiChartView;
    containerLayout->addWidget(poiChartView,0,0);

    createPOIChart();
}

void UserPage::createTimeChart(){
    qDebug() << "create time chart";

    for (QChart* chart : charts){
        if (chart){
            delete chart;
        }
    }
    charts.clear();
    timeChart = nullptr;

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

    QSetIterator<int> it(idset);
    while (it.hasNext()){
        int id=it.next();
        ids << id;
    }
    std::sort(ids.begin(),ids.end());

    timeChart = new QChart();
    charts << timeChart;
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

    int ymax = 0;
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
            ymax = ymax>cnt[date]?ymax:cnt[date];
            series->append(momentInTime.toMSecsSinceEpoch(),cnt[date]);
        }
        series->setName("user "+QString::number(ids[i]));
        timeChart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }

    axisY->setRange(0,ymax*5/4);

    qDebug() << "here1";
    timeChartView->setChart(timeChart);
}

void UserPage::createPOIChart(){
    qDebug() << "create poi chart";
    for (QChart* chart : charts){
        if (chart){
            delete chart;
        }
    }
    charts.clear();
    poiChart = nullptr;

    QString text = input->text();
    QStringList idsString = text.split(",");
    QSet<int> idset;
    QList<int> ids;

    // up to 10 users
    for (int i=0;i<idsString.size()&&i<10;i++){
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

    QSetIterator<int> idIT(idset);
    while (idIT.hasNext()){
        int id=idIT.next();
        ids << id;
    }
    std::sort(ids.begin(),ids.end());

    poiChart = new QChart();
    charts << poiChart;
    poiChart->setAnimationOptions(QChart::SeriesAnimations);
    poiChart->setAnimationDuration(100);

    QHash<int,int> poiCnt;
    for (int i=0;i<ids.size();i++){
        for (POI* poi :userData[ids[i]]){
            poiCnt[poi->locID]++;
        }
    }

    struct cmp{
        bool operator()(const std::pair<int,int> p1, const std::pair<int,int> p2){
            return p1.second < p2.second;
        }
    };

    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,cmp> q;

    QHashIterator<int,int> cntIT(poiCnt);
    while (cntIT.hasNext()){
        cntIT.next();
        q.push(std::pair(cntIT.key(),cntIT.value()));
    }

    QList<std::pair<int,int>> popularPOIs;
    for (int i=0;i<10&&i<q.size();i++){
        popularPOIs << q.top();
        q.pop();
    }
    int ymax=popularPOIs[0].second;

    QStackedBarSeries *series = new QStackedBarSeries();
    if (ids.size()<=5){
        // up to 5 bars
        for (int i=0;i<ids.size();i++){
            QBarSet *set = new QBarSet("user "+QString::number(ids[i]));
            for (int j=0;j<popularPOIs.size();j++){
                int cnt=0;
                for (POI* poi :userData[ids[i]]){
                    if (poi->locID==popularPOIs[j].first){
                        cnt++;
                    }
                }
                *set << cnt;
            }
            series->append(set);
        }
    }else{
        QString users;
        for (int i=0;i<ids.size();i++){
            users += (" "+QString::number(ids[i]));
        }

        QBarSet *set = new QBarSet("user "+users);
        for (int i=0;i<popularPOIs.size();i++){
            *set << popularPOIs[i].second;
        }
        series->append(set);
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setTitleText("Location id");
    for (int i=0;i<popularPOIs.size();i++){
        axisX->append(QString::number(popularPOIs[i].first));
    }
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Checking-ins count");
    axisY->setTickCount(8);
    axisY->setRange(0,ymax*5/4);
    axisY->setLabelFormat("%d");
    poiChart->addAxis(axisX,Qt::AlignBottom);
    poiChart->addAxis(axisY,Qt::AlignLeft);
    poiChart->addSeries(series);
    series->attachAxis(axisY);
    poiChartView->setChart(poiChart);
}

void UserPage::setChartViews(){
    if (radio1->isChecked()){
        setTimeChartViews(true);
    }else if (radio2->isChecked()){
        setPOIChartViews(true);
    }
}

void UserPage::loadData(){

    for (int i=0;i<data->size();i++){
        int userID = (*data)[i]->userID;
        userData[userID].push_back((*data)[i]);
    }
    userCnt = userData.size();
}
