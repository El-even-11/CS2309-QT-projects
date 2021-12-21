#include "mappage.h"

#include <QHeaderView>
#include <QWebEngineSettings>

MapPage::MapPage(QVector<QList<POI*>> *userData,QVector<QList<POI*>> *poiData,int totalCnt,QWidget *parent) : QWidget(parent)
{
    this->userData=userData;
    this->poiData=poiData;
    this->totalCnt=totalCnt;
    userCnt=userData->size();
    poiCnt=poiData->size();
    map = new QWebEngineView();
    map->page()->settings()->setAttribute(QWebEngineSettings::ShowScrollBars,false);
    map->load(QUrl("qrc:/new/prefix1/map.html"));
    connect(map,&QWebEngineView::loadFinished,this,&MapPage::init);
}

void MapPage::init(){
    gridLayout = new QGridLayout();
    optionBox = new QGroupBox("Options");
    radio1 = new QRadioButton("POI checking-ins");
    radio2 = new QRadioButton("USER trajectory");
    lineEdit = new QLineEdit();
    QGridLayout *grid1 = new QGridLayout();
    grid1->addWidget(radio1,0,0,1,1);
    grid1->addWidget(radio2,1,0,1,1);
    grid1->addWidget(lineEdit,1,1,1,1);
    optionBox->setLayout(grid1);
    gridLayout->addWidget(optionBox,0,0,2,2);

    diagramBox = new QGroupBox("Diagrams");
    radio3 = new QRadioButton("Scatter");
    radio4 = new QRadioButton("Heatmap");
    radio5 = new QRadioButton("Trajectory");
    QGridLayout *grid5 = new QGridLayout();
    grid5->addWidget(radio3,0,0,1,1);
    grid5->addWidget(radio4,1,0,1,1);
    grid5->addWidget(radio5,0,1,1,1);
    diagramBox->setLayout(grid5);
    gridLayout->addWidget(diagramBox,2,0,2,2);

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

    longitudeFilter = new QGroupBox("Longitude");
    QGridLayout* grid3 = new QGridLayout();
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
    grid3->addWidget(new QLabel("from"),0,0,1,1);
    grid3->addWidget(new QLabel("to"),1,0,1,1);
    grid3->addWidget(longitudeFrom,0,1,1,1);
    grid3->addWidget(longitudeTo,1,1,1,1);
    longitudeFilter->setLayout(grid3);

    latitudeFilter = new QGroupBox("Latitude");
    QGridLayout* grid4 = new QGridLayout();
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
    grid4->addWidget(new QLabel("from"),0,0,1,1);
    grid4->addWidget(new QLabel("to"),1,0,1,1);
    grid4->addWidget(latitudeFrom,0,1,1,1);
    grid4->addWidget(latitudeTo,1,1,1,1);
    latitudeFilter->setLayout(grid4);

    filterReset = new QPushButton("Reset");
    filterApply = new QPushButton("Apply");

    totalCntLabel = new QLabel("");

    filters = new QGroupBox("Filters");
    QGridLayout* grid6 = new QGridLayout();
    grid6->addWidget(dateFilter,0,0,2,2);
    grid6->addWidget(latitudeFilter,2,0,2,2);
    grid6->addWidget(longitudeFilter,4,0,2,2);
    grid6->addWidget(filterReset,6,0,1,1);
    grid6->addWidget(filterApply,6,1,1,1);
    grid6->addWidget(totalCntLabel,7,0,1,2);

    filters->setLayout(grid6);

    gridLayout->addWidget(filters,4,0,8,2);

    gridLayout->setRowStretch(12,1);

    gridLayout->addWidget(map,0,2,23,6);

    gridLayout->setColumnStretch(0,1);
    gridLayout->setColumnMinimumWidth(0,50);
    for (int i=1;i<gridLayout->columnCount();i++){
        gridLayout->setColumnStretch(i,2);
        gridLayout->setColumnMinimumWidth(i,100);
    }
    this->setLayout(gridLayout);

    radio1->setChecked(true);
    radio3->setChecked(true);

    connect(radio1,&QRadioButton::toggled,this,&MapPage::updateUI);
    connect(radio2,&QRadioButton::toggled,this,&MapPage::showEdit);
    connect(filterApply,&QPushButton::clicked,this,&MapPage::updateUI);
    connect(filterReset,&QPushButton::clicked,this,&MapPage::resetFilters);
    connect(lineEdit,&QLineEdit::editingFinished,this,&MapPage::updateUI);
    connect(radio3,&QPushButton::clicked,this,&MapPage::updateUI);
    connect(radio4,&QPushButton::clicked,this,&MapPage::updateUI);
    connect(radio5,&QPushButton::clicked,this,&MapPage::updateUI);
    updateUI();
}

void MapPage::updatePOI(){
    lineEdit->hide();
    radio5->hide();

    QVector<int> cnt;

    QDate mindate = dateFrom->date();
    QDate maxdate = dateTo->date();
    double minLat = latitudeFrom->value();
    double maxLat = latitudeTo->value();
    double minLng = longitudeFrom->value();
    double maxLng = longitudeTo->value();

    int maxcnt = 1;
    int allcnt = 0;
    for (int i=0;i<poiCnt;i++){
        int a = POI::filter((*poiData)[i],mindate,maxdate,QTime(0,0,0),QTime(23,59,59),minLng,maxLng,minLat,maxLat).size();
        cnt << a;
        allcnt += a;
        if (a > maxcnt){
            maxcnt = a;
        }
    }

    totalCntLabel->setText(QString::number(allcnt)+" checking-in records in total");

    if (radio3->isChecked()){
        QString para;
        para.reserve(30*poiCnt);
        para += "[";
        for (int i=0;i<poiCnt;i++){
            if (cnt[i]*1.0/maxcnt < 0.01){
                continue;
            }
            int size = cnt[i]*15/maxcnt+1;
            para += ("[" + QString::number((*poiData)[i][0]->latitude,'f',4) + "," + QString::number((*poiData)[i][0]->longitude,'f',4) + "," + QString::number(size+2)+","+QString::number(i)+","+QString::number(cnt[i])+"],");
        }
        para += "]";

        map->page()->runJavaScript(QString("setPoints(%1)").arg(para));
        map->page()->runJavaScript(QString("setArea(%1,%2,%3,%4)").arg(minLat).arg(maxLat).arg(minLng).arg(maxLng));
    }else if (radio4->isChecked()){
        QString para;
        para.reserve(30*poiCnt);
        para += ("{max:"+QString::number(maxcnt)+",data:[");
        for (int i=0;i<poiCnt;i++){
            if (cnt[i]*1.0/maxcnt < 0.01){
                continue;
            }
            para += ("{lat:" + QString::number((*poiData)[i][0]->latitude,'f',2) + ",lng:" + QString::number((*poiData)[i][0]->longitude,'f',2) + ",count:"+QString::number(cnt[i])+"},");
        }
        para += "]}";
        map->page()->runJavaScript(QString("setHeatmap(%1)").arg(para));
        map->page()->runJavaScript(QString("setArea(%1,%2,%3,%4)").arg(minLat).arg(maxLat).arg(minLng).arg(maxLng));
    }else{
        radio3->setChecked(true);
    }
}

void MapPage::updateUser(){
    QString text = lineEdit->text();
    bool ok;
    int id = text.toInt(&ok);
    if (!ok){
        return;
    }
    if (id >= userCnt){
        return;
    }

    QDate mindate = dateFrom->date();
    QDate maxdate = dateTo->date();
    double minLat = latitudeFrom->value();
    double maxLat = latitudeTo->value();
    double minLng = longitudeFrom->value();
    double maxLng = longitudeTo->value();

    QList<POI*> pois = POI::filter((*userData)[id],mindate,maxdate,QTime(0,0,0),QTime(23,59,59),minLng,maxLng,minLat,maxLat);
    QHash<int,int> cnt;
    int maxcnt=1;

    for (int i=0;i<pois.size();i++){
        cnt[pois[i]->locID]++;
        if (cnt[pois[i]->locID]>maxcnt){
            maxcnt=cnt[pois[i]->locID];
        }
    }

    QHashIterator<int,int> it(cnt);
    if (radio3->isChecked()){
        QString para;
        para.reserve(30*cnt.size());
        para+="[";
        while (it.hasNext()){
            it.next();
            int size = it.value()*15/maxcnt+1;
            para += ("[" + QString::number((*poiData)[it.key()][0]->latitude,'f',4) + "," + QString::number((*poiData)[it.key()][0]->longitude,'f',4) + "," + QString::number(size+2)+","+QString::number(it.key())+","+QString::number(it.value())+"],");
        }
        para += "]";
        map->page()->runJavaScript(QString("setPoints(%1)").arg(para));
        map->page()->runJavaScript(QString("setArea(%1,%2,%3,%4)").arg(minLat).arg(maxLat).arg(minLng).arg(maxLng));
    }else if (radio4->isChecked()){
        QString para;
        para.reserve(30*cnt.size());
        para += ("{max:"+QString::number(maxcnt)+",data:[");
        while (it.hasNext()){
            it.next();
            para += ("{lat:" + QString::number((*poiData)[it.key()][0]->latitude,'f',2) + ",lng:" + QString::number((*poiData)[it.key()][0]->longitude,'f',2) + ",count:"+QString::number(it.value())+"},");
        }
        para += "]}";
        map->page()->runJavaScript(QString("setHeatmap(%1)").arg(para));
        map->page()->runJavaScript(QString("setArea(%1,%2,%3,%4)").arg(minLat).arg(maxLat).arg(minLng).arg(maxLng));
    }else{
        QString para1;
        QString para2;
        para1.reserve(25*pois.size());
        para2.reserve(6*pois.size());
        para1+="[";
        para2+="[";

        int locid = -1;
        for (POI* poi : pois){
            if (poi->locID==locid){
                continue;
            }
            locid=poi->locID;
            para1 += "["+QString::number(poi->latitude,'f',4)+","+QString::number(poi->longitude,'f',4)+"],";
            para2 += QString::number(locid)+",";
        }
        para1+="]";
        para2+="]";
        map->page()->runJavaScript(QString("setTrajectory(%1,%2)").arg(para1).arg(para2));
        map->page()->runJavaScript(QString("setArea(%1,%2,%3,%4)").arg(minLat).arg(maxLat).arg(minLng).arg(maxLng));
    }

    totalCntLabel->setText(QString::number(pois.size())+" checking-in records in total");
}

void MapPage::updateUI(){
    if (radio1->isChecked()){
        updatePOI();
    }else{
        updateUser();
    }
}

void MapPage::resetFilters(){
    dateFrom->setDate(QDate(2009,2,1));
    dateTo->setDate(QDate(2010,10,31));
    longitudeFrom->setValue(-180.0);
    longitudeTo->setValue(180.0);
    latitudeFrom->setValue(-90.0);
    latitudeTo->setValue(90.0);
}

void MapPage::showEdit(){
    lineEdit->show();
    radio5->show();
}

