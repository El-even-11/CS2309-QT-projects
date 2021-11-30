#include "mainwidget.h"
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QDebug>

MainWidget::MainWidget()
{
    setMinimumSize(1000,500);
    chart = new QChart();
    chart->legend()->setVisible(false);

    chartView = new QChartView(this);
    chartView->setChart(chart);

    btn = new QPushButton("select");
    starting = new QLabel("start week:");
    ending = new QLabel("end week:");
    select = new QLabel("select a .csv file:");
    warning = new QLabel("");
    startBox = new QComboBox();
    endBox = new QComboBox();

    container = new QGridLayout();

    container->addWidget(chartView,0,0,3,5);
    container->addWidget(starting,3,0);
    container->addWidget(startBox,3,1);
    container->addWidget(ending,4,0);
    container->addWidget(endBox,4,1);
    container->addWidget(select,3,3);
    container->addWidget(warning,4,2);
    container->addWidget(btn,3,4);

    this->setLayout(container);

    connect(btn,&QPushButton::clicked,this,&MainWidget::setData);
    connect(startBox,&QComboBox::currentIndexChanged,this,&MainWidget::setRange);
    connect(endBox,&QComboBox::currentIndexChanged,this,&MainWidget::setRange);
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
    file.close();
    chart->removeAllSeries();
    chart->addSeries(series);
    chart->removeAxis(axisX);
    chart->removeAxis(axisY);

    axisX = new QValueAxis();
    axisY = new QValueAxis();

    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);

    startBox->clear();
    endBox->clear();

    for (int i=0;i<data.size();i++){
        startBox->addItem(QString::number(i+1),i);
        endBox->addItem(QString::number(i+1),i);
    }

    endBox->setCurrentIndex(data.size()-1);
}


void MainWidget::setRange(){
    int start = startBox->currentIndex();
    int end = endBox->currentIndex();

    warning->setText("");
    chart->removeAllSeries();

    if (start>end){
        warning->setText("start week should be earlier");
        return;
    }

    series = new QSplineSeries(this);

    int max = -1;
    for (int i=start;i<=end;i++){
        series->append(data[i].first,data[i].second);
        max = data[i].second>max?data[i].second:max;
    }

    chart->addSeries(series);

    axisX->setTickCount((end-start+1)>10?10:(end-start+1));
    axisX->setRange(start+1,end+1);
    axisX->setLabelFormat("%d");

    axisY->setTickCount(8);
    axisY->setRange(0,int(max*4/3));
    axisY->setLabelFormat("%d");

    series->attachAxis(axisX);
    series->attachAxis(axisY);
}
