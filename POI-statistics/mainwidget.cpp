#include "mainwidget.h"
#include <QFileDialog>
#include <QString>
#include <QFile>

MainWidget::MainWidget()
{
    setMinimumSize(500,500);
    series = new QSplineSeries(this);
    chart = new QChart();

    chart->addSeries(series);
    chart->createDefaultAxes();
    ChartView = new QChartView(this);
    ChartView->setChart(chart);

    btn = new QPushButton("select");

    container = new QVBoxLayout();
    container->addWidget(ChartView);
    container->addWidget(btn);

    this->setLayout(container);

    connect(btn,&QPushButton::clicked,this,&MainWidget::setData);
}

void MainWidget::setData(){
    QString filename=QFileDialog::getOpenFileName(0,"Select csv file","/","(*.csv)");
    QFile file(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);

    QTextStream in(&file);
    in.readLine();
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList list=line.split(",");
        std::pair<int,int> p;
        p.first=list[0].toInt();
        p.second=list[1].toInt();
        data.push_back(p);
    }

    series->clear();
    for (int i=0;i<data.size();i++){
        series->append(data[i].first,data[i].second);
    }
    chart->createDefaultAxes();
}
