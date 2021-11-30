#include "mainwidget.h"
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QDebug>

MainWidget::MainWidget()
{
    setMinimumSize(500,500);
    chart = new QChart();

    chartView = new QChartView(this);
    chartView->setChart(chart);

    btn = new QPushButton("select");
    starting = new QLabel("starting week");
    ending = new QLabel("ending week");
    select = new QLabel("select a .csv file");
    startBox = new QComboBox();
    endBox = new QComboBox();

    container = new QGridLayout();
    container->addWidget(chartView,0,0,3,5);
    container->addWidget(starting,3,0);
    container->addWidget(startBox,3,1);
    container->addWidget(ending,4,0);
    container->addWidget(endBox,4,1);
    container->addWidget(select,3,3);
    container->addWidget(btn,3,4);

    this->setLayout(container);

    connect(btn,&QPushButton::clicked,this,&MainWidget::setData);
    connect(startBox,&QComboBox::currentIndexChanged,this,&MainWidget::setStartingWeek);
    connect(endBox,&QComboBox::currentIndexChanged,this,&MainWidget::setEndingWeek);
}

void MainWidget::setData(){
    QString filename=QFileDialog::getOpenFileName(0,"Select csv file","/","(*.csv)");
    QFile file(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);

    QTextStream in(&file);
    in.readLine();

    data.clear();
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList list=line.split(",");
        std::pair<int,int> p;
        p.first=list[0].toInt();
        p.second=list[1].toInt();
        data.push_back(p);
    }

    series = new QSplineSeries(this);
    for (int i=0;i<data.size();i++){
        series->append(data[i].first,data[i].second);
    }
    file.close();
    chart->removeAllSeries();
    chart->addSeries(series);
    chart->createDefaultAxes();


    startBox->clear();
    endBox->clear();

    for (int i=0;i<data.size();i++){
        startBox->addItem(QString::number(i+1),i);
        endBox->addItem(QString::number(i+1),i);
    }

    endBox->setCurrentIndex(data.size()-1);
}

void MainWidget::setStartingWeek(){
    int start = startBox->currentIndex();
    int end = endBox->currentIndex();

    if (start>end){
        start=end;
    }
    setRange(start,end);
}

void MainWidget::setEndingWeek(){
    int start = startBox->currentIndex();
    int end = endBox->currentIndex();

    if (end<start){
        end=start;
    }
    setRange(start,end);
}

void MainWidget::setRange(int start, int end){
    series = new QSplineSeries(this);
    for (int i=start;i<=end;i++){
        series->append(data[i].first,data[i].second);
    }

    chart->removeAllSeries();
    chart->addSeries(series);
    chart->createDefaultAxes();
}
