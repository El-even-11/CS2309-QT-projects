#include "mappage.h"

#include <QHeaderView>
#include <QWebEngineSettings>

MapPage::MapPage(QList<POI*>* data,QWidget *parent) : QWidget(parent)
{
    this->data=data;

    loadData();

    gridLayout = new QGridLayout();

    optionBox = new QGroupBox("Options");
    radio1 = new QRadioButton("POI heatmap");
    radio2 = new QRadioButton("USER trajectory");
    lineEdit = new QLineEdit();
    QGridLayout *grid1 = new QGridLayout();
    grid1->addWidget(radio1,0,0,1,1);
    grid1->addWidget(radio2,1,0,1,1);
    grid1->addWidget(lineEdit,1,1,1,1);
    optionBox->setLayout(grid1);
    gridLayout->addWidget(optionBox,0,0,2,2);

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
    QLabel *label1 = new QLabel(QString::number(data->size())+" records loaded");
    filterLabel = new QLabel("0 records filtered");
    filters = new QGroupBox("Filters");
    QGridLayout* grid6 = new QGridLayout();
    grid6->addWidget(dateFilter,0,0,2,2);
    grid6->addWidget(latitudeFilter,2,0,2,2);
    grid6->addWidget(longitudeFilter,4,0,2,2);
    grid6->addWidget(filterReset,6,0,1,1);
    grid6->addWidget(filterApply,6,1,1,1);
    grid6->addWidget(label1,7,0,1,1);
    grid6->addWidget(filterLabel,7,1,1,1);
    filters->setLayout(grid6);

    gridLayout->addWidget(filters,2,0,8,2);

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
    gridLayout->addWidget(tableContainer,10,0,13,2);

    map = new QWebEngineView();
    map->page()->settings()->setAttribute(QWebEngineSettings::ShowScrollBars,false);
    map->load(QUrl("qrc:/new/prefix1/map.html"));
    gridLayout->addWidget(map,0,2,23,6);

    gridLayout->setColumnStretch(0,1);
    gridLayout->setColumnMinimumWidth(0,50);
    for (int i=1;i<gridLayout->columnCount();i++){
        gridLayout->setColumnStretch(i,2);
        gridLayout->setColumnMinimumWidth(i,100);
    }
    this->setLayout(gridLayout);

    connect(radio1,&QRadioButton::toggled,this,&MapPage::updatePOI);
    connect(radio2,&QRadioButton::toggled,this,&MapPage::showEdit);
    connect(filterApply,&QPushButton::clicked,this,&MapPage::updateUI);
    connect(filterReset,&QPushButton::clicked,this,&MapPage::resetFilters);
    connect(lineEdit,&QLineEdit::editingFinished,this,&MapPage::updateUser);


    connect(map,&QWebEngineView::loadFinished,this,&MapPage::init);
}

void MapPage::updatePOI(){
    lineEdit->hide();

    QVector<int> cnt;

    QDate mindate = dateFrom->date();
    QDate maxdate = dateTo->date();
    double minLat = latitudeFrom->value();
    double maxLat = latitudeTo->value();
    double minLng = longitudeFrom->value();
    double maxLng = longitudeTo->value();

    qDebug() << "here1";
    int maxcnt = 1;
    int maxindex = -1;
    for (int i=0;i<poiCnt;i++){
        int a = POI::filter(poiData[i],mindate,maxdate,QTime(0,0,0),QTime(23,59,59),minLng,maxLng,minLat,maxLat).size();
        cnt << a;
        if (a > maxcnt){
            maxcnt = a;
            maxindex = i;
        }
    }

    qDebug() << maxcnt;
    qDebug() << maxindex;

    QString para;
    para.reserve(30*poiCnt);
    para += "[";
    for (int i=0;i<poiCnt;i++){
        if (cnt[i]*1.0/maxcnt < 0.01){
            continue;
        }
        int size = cnt[i]*15/maxcnt+1;
        para += ("[" + QString::number(poiData[i][0]->latitude,'f',2) + "," + QString::number(poiData[i][0]->longitude,'f',2) + "," + QString::number(size+2)+","+QString::number(i)+","+QString::number(cnt[i])+"],");
    }
    para += "]";
    qDebug() << "here3";

    map->page()->runJavaScript(QString("setPoints(%1)").arg(para));
    map->page()->runJavaScript(QString("setArea(%1,%2,%3,%4)").arg(minLat).arg(maxLat).arg(minLng).arg(maxLng));

}

void MapPage::updateUser(){

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
}

void MapPage::loadData(){
    QListIterator<POI*> it(*data);
    while (it.hasNext()){
        POI* poi = it.next();
        int locID = poi->locID;
        if (locID>=poiData.size()){
            poiData << QList<POI*>();
        }
        poiData[locID] << poi;
    }
    poiCnt = poiData.size();
}

void MapPage::init(){
    radio1->setChecked(true);
}
