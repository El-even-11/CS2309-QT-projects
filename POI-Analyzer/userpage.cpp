#include "userpage.h"
#include <QLabel>
#include <QTime>
#include <QSet>
#include <algorithm>
#include <queue>

UserPage::UserPage(QList<POI*>* data,QWidget *parent) : QWidget(parent)
{
    this->data=data;
    loadData();

    gridLayout = new QGridLayout();
    QLabel *label = new QLabel("user id:");
    gridLayout->addWidget(label,0,0,1,1);
    lineEdit = new QLineEdit();
    gridLayout->addWidget(lineEdit,0,1,1,1);

    optionBox = new QGroupBox("Options");
    radio1 = new QRadioButton("General trends");
    radio2 = new QRadioButton("Top 10 popular POIs");
    radio3 = new QRadioButton("Comparison");
    radio4 = new QRadioButton("Daily trends");
    QGridLayout *grid1 = new QGridLayout();
    grid1->addWidget(radio1,0,0,1,1);
    grid1->addWidget(radio2,1,0,1,1);
    grid1->addWidget(radio3,2,0,1,1);
    grid1->addWidget(radio4,0,1,1,1);
    optionBox->setLayout(grid1);
    gridLayout->addWidget(optionBox,1,0,3,2);

    dateFilter = new QGroupBox("Date");
    QGridLayout* grid2 = new QGridLayout();
    dateFrom = new QDateEdit();
    dateTo = new QDateEdit();
    dateFrom->setDateRange(QDate(2009,2,1),QDate(2010,10,31));
    dateTo->setDateRange(QDate(2009,2,1),QDate(2010,10,31));
    dateFrom->setDate(QDate(2009,2,1));
    dateTo->setDate(QDate(2010,10,31));
    grid2->addWidget(new QLabel("from"),0,0,1,1);
    grid2->addWidget(new QLabel("to"),1,0,1,1);
    grid2->addWidget(dateFrom,0,1,1,1);
    grid2->addWidget(dateTo,1,1,1,1);
    dateFilter->setLayout(grid2);

    timeFilter = new QGroupBox("Time");
    QGridLayout* grid3 = new QGridLayout();
    timeFrom = new QTimeEdit();
    timeTo = new QTimeEdit();
    timeFrom->setTimeRange(QTime(0,0,0),QTime(23,59,59));
    timeTo->setTimeRange(QTime(0,0,0),QTime(23,59,59));
    timeFrom->setTime(QTime(0,0,0));
    timeTo->setTime(QTime(23,59,59));
    grid3->addWidget(new QLabel("from"),0,0,1,1);
    grid3->addWidget(new QLabel("to"),1,0,1,1);
    grid3->addWidget(timeFrom,0,1,1,1);
    grid3->addWidget(timeTo,1,1,1,1);
    timeFilter->setLayout(grid3);

    longitudeFilter = new QGroupBox("Longitude");
    QGridLayout* grid4 = new QGridLayout();
    longitudeFrom = new QDoubleSpinBox();
    longitudeTo = new QDoubleSpinBox();
    longitudeFrom->setRange(-180.0,180.0);
    longitudeTo->setRange(-180.0,180.0);
    longitudeFrom->setValue(-180.0);
    longitudeTo->setValue(180.0);
    longitudeFrom->setSingleStep(0.1);
    longitudeTo->setSingleStep(0.1);
    longitudeFrom->setDecimals(1);
    longitudeTo->setDecimals(1);
    longitudeFrom->setSuffix("°");
    longitudeTo->setSuffix("°");
    grid4->addWidget(new QLabel("from"),0,0,1,1);
    grid4->addWidget(new QLabel("to"),1,0,1,1);
    grid4->addWidget(longitudeFrom,0,1,1,1);
    grid4->addWidget(longitudeTo,1,1,1,1);
    longitudeFilter->setLayout(grid4);

    latitudeFilter = new QGroupBox("Latitude");
    QGridLayout* grid5 = new QGridLayout();
    latitudeFrom = new QDoubleSpinBox();
    latitudeTo = new QDoubleSpinBox();
    latitudeFrom->setRange(-90.0,90.0);
    latitudeTo->setRange(-90.0,90.0);
    latitudeFrom->setValue(-90.0);
    latitudeTo->setValue(90.0);
    latitudeFrom->setSingleStep(0.1);
    latitudeTo->setSingleStep(0.1);
    latitudeFrom->setDecimals(1);
    latitudeTo->setDecimals(1);
    latitudeFrom->setSuffix("°");
    latitudeTo->setSuffix("°");
    grid5->addWidget(new QLabel("from"),0,0,1,1);
    grid5->addWidget(new QLabel("to"),1,0,1,1);
    grid5->addWidget(latitudeFrom,0,1,1,1);
    grid5->addWidget(latitudeTo,1,1,1,1);
    latitudeFilter->setLayout(grid5);

    filterReset = new QPushButton("Reset");
    filterApply = new QPushButton("Apply");
    filters = new QGroupBox("Filters");
    QGridLayout* grid6 = new QGridLayout();
    grid6->addWidget(dateFilter,0,0,2,2);
    grid6->addWidget(timeFilter,2,0,2,2);
    grid6->addWidget(latitudeFilter,4,0,2,2);
    grid6->addWidget(longitudeFilter,6,0,2,2);
    grid6->addWidget(filterReset,8,0,1,1);
    grid6->addWidget(filterApply,8,1,1,1);
    filters->setLayout(grid6);

    gridLayout->addWidget(filters,4,0,9,2);

    table = new QTableWidget();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    table->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->horizontalHeader()->setDisabled(true);
    table->verticalHeader()->setDisabled(true);
    table->setColumnCount(6);

    QStringList header;
    header << "UserID" << "LocID" << "Date" << "Time" << "Latitude" << "Longitude";
    table->setHorizontalHeaderLabels(header);
    tableContainer = new QGroupBox("Records");
    QVBoxLayout *vbox2 = new QVBoxLayout();
    vbox2->addWidget(table);
    tableContainer->setLayout(vbox2);
    gridLayout->addWidget(tableContainer,13,0,10,2);

    chartContainer = new QWidget();
    gridLayout->addWidget(chartContainer,0,2,23,6);
    containerLayout = new QGridLayout();
    containerLayout->setColumnStretch(0,1);
    containerLayout->setColumnStretch(1,1);
    containerLayout->setRowStretch(0,1);
    containerLayout->setRowStretch(1,1);
    chartContainer->setLayout(containerLayout);

    gridLayout->setColumnStretch(0,1);
    gridLayout->setColumnMinimumWidth(0,50);
    for (int i=1;i<gridLayout->columnCount();i++){
        gridLayout->setColumnStretch(i,2);
        gridLayout->setColumnMinimumWidth(i,100);
    }
    this->setLayout(gridLayout);

    connect(radio1,&QRadioButton::toggled,this,&UserPage::optionChanged);
    connect(radio2,&QRadioButton::toggled,this,&UserPage::optionChanged);
    connect(radio3,&QRadioButton::toggled,this,&UserPage::optionChanged);
    connect(radio4,&QRadioButton::toggled,this,&UserPage::optionChanged);
    connect(filterApply,&QPushButton::clicked,this,&UserPage::updateUI);
    connect(filterReset,&QPushButton::clicked,this,&UserPage::resetFilters);
    connect(lineEdit,&QLineEdit::editingFinished,this,&UserPage::updateUI);
    radio1->setChecked(true);
}

void UserPage::setGeneralChart(const QVector<int>& ids,const QList<POI*>& tuples){
    for (QChartView *view : chartviews){
        delete view;
    }
    chartviews.clear();
    generalChartView = new QChartView();
    generalChartView->setRenderHint(QPainter::Antialiasing,true);
    chartviews << generalChartView;
    containerLayout->addWidget(generalChartView,0,0,2,2);
    charts.clear();
    generalChart = new QChart();
    charts << generalChart;
    generalChart->setLocale(QLocale::English);
    generalChart->setAnimationOptions(QChart::SeriesAnimations);
    generalChart->setAnimationDuration(100);
    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(POI::monthRange.size());
    axisX->setFormat("MMM yyyy");
    generalChart->addAxis(axisX,Qt::AlignBottom);
    QValueAxis *axisY = new QValueAxis();
    axisY->setTickCount(8);
    axisY->setLabelFormat("%d");
    axisY->setTitleText("Checking-ins count");
    generalChart->addAxis(axisY,Qt::AlignLeft);

    if (tuples.size()==0){
        return;
    }

    QHash<int,QVector<POI*>> userTuples;
    QListIterator<POI*> it(tuples);
    while (it.hasNext()){
        POI *poi = it.next();
        userTuples[poi->userID] << poi;
    }

    int ymax = 0;
    // up to 5 users
    for (int i=0;i<ids.size()&&i<5;i++){
        QVector<POI*> userPOI = userTuples[ids[i]];
        QSplineSeries *series = new QSplineSeries();

        QHash<QDate,int> cnt;
        for (QDate date : POI::monthRange){
            cnt[date]=0;
        }
        for (POI* poi : userPOI){
            QDate date = poi->date;
            cnt[QDate(date.year(),date.month(),15)]++;
        }
        for (QDate date : POI::monthRange){
            QDateTime momentInTime;
            momentInTime.setDate(date);
            ymax = ymax>cnt[date]?ymax:cnt[date];
            series->append(momentInTime.toMSecsSinceEpoch(),cnt[date]);
        }
        series->setName("user "+QString::number(ids[i]));
        generalChart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }

    axisY->setRange(0,ymax*5/4);
    generalChartView->setChart(generalChart);
}

void UserPage::setPOIChart(const QVector<int>& ids,const QList<POI*>& tuples){
    for (QChartView *view : chartviews){
        delete view;
    }
    chartviews.clear();
    poiChartView = new QChartView();
    chartviews << poiChartView;
    containerLayout->addWidget(poiChartView,0,0,2,2);
    charts.clear();
    poiChart = new QChart();
    charts << poiChart;
    poiChart->setAnimationOptions(QChart::SeriesAnimations);
    poiChart->setAnimationDuration(100);

    if (tuples.size()==0){
        return;
    }

    QHash<int,QVector<POI*>> userTuples;
    QListIterator<POI*> it(tuples);
    while (it.hasNext()){
        POI *poi = it.next();
        userTuples[poi->userID] << poi;
    }

    QHash<int,int> poiCnt;
    for (int i=0;i<ids.size();i++){
        for (POI* poi :userTuples[ids[i]]){
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

    QVector<std::pair<int,int>> popularPOIs;
    for (int i=0;i<10&&!q.empty();i++){
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
                for (POI* poi : userTuples[ids[i]]){
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

void UserPage::setCmpChart(const QVector<int>& ids,const QList<POI*>& tuples){
    for (QChartView *view : chartviews){
        delete view;
    }
    chartviews.clear();
    cmpChartView1 = new QChartView();
    cmpChartView2 = new QChartView();
    cmpChartView3 = new QChartView();
    cmpChartView4 = new QChartView();
    cmpChartView1->setRenderHint(QPainter::Antialiasing,true);
    cmpChartView2->setRenderHint(QPainter::Antialiasing,true);
    cmpChartView3->setRenderHint(QPainter::Antialiasing,true);
    cmpChartView4->setRenderHint(QPainter::Antialiasing,true);
    chartviews << cmpChartView1 << cmpChartView2 << cmpChartView3 << cmpChartView4;
    containerLayout->addWidget(cmpChartView1,0,0,1,1);
    containerLayout->addWidget(cmpChartView2,0,1,1,1);
    containerLayout->addWidget(cmpChartView3,1,0,1,1);
    containerLayout->addWidget(cmpChartView4,1,1,1,1);
    charts.clear();
    cmpChart1 = new QChart();
    cmpChart2 = new QChart();
    cmpChart3 = new QChart();
    cmpChart4 = new QChart();
    charts << cmpChart1 << cmpChart2 <<cmpChart3 <<cmpChart4;
    cmpChart1->setAnimationOptions(QChart::SeriesAnimations);
    cmpChart2->setAnimationOptions(QChart::SeriesAnimations);
    cmpChart3->setAnimationOptions(QChart::SeriesAnimations);
    cmpChart4->setAnimationOptions(QChart::SeriesAnimations);
    cmpChart1->setAnimationDuration(100);
    cmpChart2->setAnimationDuration(100);
    cmpChart3->setAnimationDuration(100);
    cmpChart4->setAnimationDuration(100);
    cmpChart3->setTheme(QChart::ChartThemeQt);
    cmpChart4->setTheme(QChart::ChartThemeQt);

    if (tuples.size()==0){
        return;
    }

    QHash<int,QVector<POI*>> userTuples;
    QListIterator<POI*> it(tuples);
    while (it.hasNext()){
        POI *poi = it.next();
        userTuples[poi->userID] << poi;
    }

    if (ids.size()==1){
        // popular pois
        QHash<int,int> poiCnt;

        for (POI* poi :userTuples[ids[0]]){
            poiCnt[poi->locID]++;
        }

        struct cmp{
            bool operator()(const std::pair<int,int> p1, const std::pair<int,int> p2){
                return p1.second <= p2.second;
            }
        };

        std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,cmp> q;

        QHashIterator<int,int> cntIT(poiCnt);
        while (cntIT.hasNext()){
            cntIT.next();
            q.push(std::pair(cntIT.key(),cntIT.value()));
        }

        QVector<std::pair<int,int>> popularPOIs;
        for (int i=0;i<7&&!q.empty();i++){
            popularPOIs << q.top();
            q.pop();
        }

        QPieSeries *series1 = new QPieSeries();
        for (int i=0;i<popularPOIs.size();i++){
            QPieSlice *slice = series1->append("loc "+QString::number(popularPOIs[i].first),popularPOIs[i].second);
            if (i==0){
                slice->setLabelVisible();
                slice->setExploded();
                slice->setExplodeDistanceFactor(0.1);
            }
        }
        series1->setPieSize(0.4);
        cmpChart1->addSeries(series1);
        cmpChart1->setTitle("POIs with most checking-ins by user "+QString::number(ids[0]));

        // daily checking-ins
        QHash<QString,int> timeCnt;
        for (int i=0;i<userTuples[ids[0]].size();i++){
            POI *poi = userTuples[ids[0]][i];
            timeCnt[POI::timeInterval(poi->time)]++;
        }

        int maxCnt= 0;
        int maxIndex = 0;
        for (int i=0;i<POI::timeIntervals.size();i++){
            if (timeCnt[POI::timeIntervals[i]]>maxCnt){
                maxCnt=timeCnt[POI::timeIntervals[i]];
                maxIndex = i;
            }
        }
        QPieSeries *series3 = new QPieSeries();
        for (int i=0;i<POI::timeIntervals.size();i++){
            QPieSlice *slice = series3->append(POI::timeIntervals[i],timeCnt[POI::timeIntervals[i]]);
            if (i==maxIndex){
                slice->setLabelVisible();
                slice->setExploded();
                slice->setExplodeDistanceFactor(0.1);
            }
        }
        series3->setPieSize(0.4);
        cmpChart3->addSeries(series3);
        cmpChart3->setTitle("Daily active period of user "+QString::number(ids[0]));
    }else{
        // popular pois
        QHash<int,int> poiCnt;

        for (POI* poi :userTuples[ids[0]]){
            poiCnt[poi->locID]++;
        }

        struct cmp{
            bool operator()(const std::pair<int,int> p1, const std::pair<int,int> p2){
                return p1.second <= p2.second;
            }
        };

        std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,cmp> q;

        QHashIterator<int,int> cntIT(poiCnt);
        while (cntIT.hasNext()){
            cntIT.next();
            q.push(std::pair(cntIT.key(),cntIT.value()));
        }

        QVector<std::pair<int,int>> popularPOIs;
        for (int i=0;i<7&&!q.empty();i++){
            popularPOIs << q.top();
            q.pop();
        }

        QPieSeries *series1 = new QPieSeries();
        for (int i=0;i<popularPOIs.size();i++){
            QPieSlice *slice = series1->append("loc "+QString::number(popularPOIs[i].first),popularPOIs[i].second);
            if (i==0){
                slice->setLabelVisible();
                slice->setExploded();
                slice->setExplodeDistanceFactor(0.1);
            }
        }
        series1->setPieSize(0.4);
        cmpChart1->addSeries(series1);
        cmpChart1->setTitle("POIs with most checking-ins by user "+QString::number(ids[0]));

        poiCnt.clear();

        for (POI* poi :userTuples[ids[1]]){
            poiCnt[poi->locID]++;
        }

        while (!q.empty()){
            q.pop();
        }

        QHashIterator<int,int> cntIT1(poiCnt);
        while (cntIT1.hasNext()){
            cntIT1.next();
            q.push(std::pair(cntIT1.key(),cntIT1.value()));
        }

        popularPOIs.clear();
        for (int i=0;i<7&&!q.empty();i++){
            popularPOIs << q.top();
            q.pop();
        }

        QPieSeries *series2 = new QPieSeries();
        for (int i=0;i<popularPOIs.size();i++){
            QPieSlice *slice = series2->append("loc "+QString::number(popularPOIs[i].first),popularPOIs[i].second);
            if (i==0){
                slice->setLabelVisible();
                slice->setExploded();
                slice->setExplodeDistanceFactor(0.1);
            }
        }
        series2->setPieSize(0.4);
        cmpChart2->addSeries(series2);
        cmpChart2->setTitle("POIs with most checking-ins by user "+QString::number(ids[1]));

        // daily checking-ins
        QHash<QString,int> timeCnt;
        for (int i=0;i<userTuples[ids[0]].size();i++){
            POI *poi = userTuples[ids[0]][i];
            timeCnt[POI::timeInterval(poi->time)]++;
        }

        int maxCnt= 0;
        int maxIndex = 0;
        for (int i=0;i<POI::timeIntervals.size();i++){
            if (timeCnt[POI::timeIntervals[i]]>maxCnt){
                maxCnt=timeCnt[POI::timeIntervals[i]];
                maxIndex = i;
            }
        }
        QPieSeries *series3 = new QPieSeries();
        for (int i=0;i<POI::timeIntervals.size();i++){
            QPieSlice *slice = series3->append(POI::timeIntervals[i],timeCnt[POI::timeIntervals[i]]);
            if (i==maxIndex){
                slice->setLabelVisible();
                slice->setExploded();
                slice->setExplodeDistanceFactor(0.1);
            }
        }
        series3->setPieSize(0.4);
        cmpChart3->addSeries(series3);
        cmpChart3->setTitle("Daily active period of user "+QString::number(ids[0]));

        timeCnt.clear();
        for (int i=0;i<userTuples[ids[1]].size();i++){
            POI *poi = userTuples[ids[1]][i];
            timeCnt[POI::timeInterval(poi->time)]++;
        }

        maxCnt= 0;
        maxIndex = 0;
        for (int i=0;i<POI::timeIntervals.size();i++){
            if (timeCnt[POI::timeIntervals[i]]>maxCnt){
                maxCnt=timeCnt[POI::timeIntervals[i]];
                maxIndex = i;
            }
        }
        QPieSeries *series4 = new QPieSeries();
        for (int i=0;i<POI::timeIntervals.size();i++){
            QPieSlice *slice = series4->append(POI::timeIntervals[i],timeCnt[POI::timeIntervals[i]]);
            if (i==maxIndex){
                slice->setLabelVisible();
                slice->setExploded();
                slice->setExplodeDistanceFactor(0.1);
            }
        }
        series4->setPieSize(0.4);
        cmpChart4->addSeries(series4);
        cmpChart4->setTitle("Daily active period of user "+QString::number(ids[1]));
    }

    cmpChartView1->setChart(cmpChart1);
    cmpChartView2->setChart(cmpChart2);
    cmpChartView3->setChart(cmpChart3);
    cmpChartView4->setChart(cmpChart4);
}

void UserPage::setDailyChart(const QVector<int>& ids,const QList<POI*>& tuples){
    for (QChartView *view : chartviews){
        delete view;
    }
    chartviews.clear();
    dailyChartView = new QChartView();
    chartviews << dailyChartView;
    containerLayout->addWidget(dailyChartView,0,0,2,2);
    charts.clear();
    dailyChart = new QChart();
    charts << dailyChart;
    dailyChart->setAnimationOptions(QChart::SeriesAnimations);
    dailyChart->setAnimationDuration(100);

    if (tuples.size()==0){
        return;
    }

    QHash<int,QVector<POI*>> userTuples;
    QListIterator<POI*> it(tuples);
    while (it.hasNext()){
        POI *poi = it.next();
        userTuples[poi->userID] << poi;
    }

    int ymax=0;
    QBarSeries *series = new QBarSeries();
    for (int i=0;i<ids.size()&&i<5;i++){
        QHash<QString,int> cnt;
        for (POI* poi : userTuples[ids[i]]){
            cnt[POI::timeInterval(poi->time)]++;
        }
        QBarSet *set = new QBarSet("user "+QString::number(ids[i]));
        for (QString timeInterval : POI::timeIntervals){
            ymax = cnt[timeInterval]>ymax?cnt[timeInterval]:ymax;
            *set << cnt[timeInterval];
        }
        series->append(set);
    }

    QStringList categories;
    for (QString timeInterval : POI::timeIntervals){
        categories << timeInterval;
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Checking-ins count");
    axisY->setTickCount(8);
    axisY->setRange(0,ymax*5/4);
    axisY->setLabelFormat("%d");
    dailyChart->addAxis(axisX,Qt::AlignBottom);
    dailyChart->addAxis(axisY,Qt::AlignLeft);
    dailyChart->addSeries(series);
    series->attachAxis(axisY);
    dailyChartView->setChart(dailyChart);
}

void UserPage::resetFilters(){
    dateFrom->setDate(QDate(2009,2,1));
    dateTo->setDate(QDate(2010,10,31));
    timeFrom->setTime(QTime(0,0,0));
    timeTo->setTime(QTime(23,59,59));
    longitudeFrom->setValue(-180.0);
    longitudeTo->setValue(180.0);
    latitudeFrom->setValue(-90.0);
    latitudeTo->setValue(90.0);
}

void UserPage::loadData(){

    QListIterator<POI*> it(*data);
    while (it.hasNext()){
        POI* poi = it.next();
        int userID = poi->userID;
        if (userID>=userData.size()){
            userData << QList<POI*>();
        }
        userData[userID] << poi;
    }

    userCnt = userData.size();
}

void UserPage::updateUI(){
    QString text = lineEdit->text();
    QList<POI*> tuples;
    QVector<int> ids;

    QStringList idsString = text.split(",");
    QSet<int> idset;

    for (int i=0;i<idsString.size();i++){
        bool ok;
        int id = idsString[i].toInt(&ok);
        if (!ok){
            return;
        }
        if (id >= userCnt){
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

    for (int i=0;i<ids.size();i++){
        tuples.append(userData[ids[i]]);
    }

    QList<POI*> filtered = POI::filter(tuples,dateFrom->date(),dateTo->date(),timeFrom->time(),timeTo->time(),longitudeFrom->value(),longitudeTo->value(),latitudeFrom->value(),latitudeTo->value());

    if (radio1->isChecked()){
        setGeneralChart(ids,filtered);
    }else if (radio2->isChecked()){
        setPOIChart(ids,filtered);
    }else if (radio3->isChecked()){
        setCmpChart(ids,filtered);
    }else if (radio4->isChecked()){
        setDailyChart(ids,filtered);
    }

    table->clearContents();
    table->setRowCount(filtered.size());

    QListIterator<POI*> it1(filtered);
    int row = 0;
    while (it1.hasNext()){
        POI* poi = it1.next();
        table->setItem(row,0,new QTableWidgetItem(QString::number(poi->userID)));
        table->setItem(row,1,new QTableWidgetItem(QString::number(poi->locID)));
        table->setItem(row,2,new QTableWidgetItem(poi->date.toString("yyyy-MM-dd")));
        table->setItem(row,3,new QTableWidgetItem(poi->time.toString()));
        table->setItem(row,4,new QTableWidgetItem(QString::number(poi->latitude)));
        table->setItem(row,5,new QTableWidgetItem(QString::number(poi->longitude)));
        row++;
    }

    for (int i=0;i<filtered.size();i++){
        for (int j=0;j<6;j++){
            table->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void UserPage::optionChanged(bool checked){
    if (!checked){
        return;
    }
    updateUI();
}
