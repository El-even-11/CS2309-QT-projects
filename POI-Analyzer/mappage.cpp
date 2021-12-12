#include "mappage.h"

#include <QHeaderView>
#include <QWebEngineSettings>

MapPage::MapPage(QList<POI*>* data,QWidget *parent) : QWidget(parent)
{
    this->data=data;

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
    grid1->addWidget(radio3,1,1,1,1);
    grid1->addWidget(radio4,0,1,1,1);
    optionBox->setLayout(grid1);
    gridLayout->addWidget(optionBox,1,0,2,2);

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
    QLabel *label1 = new QLabel(QString::number(data->size())+" records loaded");
    filterLabel = new QLabel("0 records filtered");
    filters = new QGroupBox("Filters");
    QGridLayout* grid6 = new QGridLayout();
    grid6->addWidget(dateFilter,0,0,2,2);
    grid6->addWidget(timeFilter,2,0,2,2);
    grid6->addWidget(latitudeFilter,4,0,2,2);
    grid6->addWidget(longitudeFilter,6,0,2,2);
    grid6->addWidget(filterReset,8,0,1,1);
    grid6->addWidget(filterApply,8,1,1,1);
    grid6->addWidget(label1,9,0,1,1);
    grid6->addWidget(filterLabel,9,1,1,1);
    filters->setLayout(grid6);

    gridLayout->addWidget(filters,3,0,10,2);

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
}
