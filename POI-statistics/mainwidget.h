#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtCharts>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget();


private:
    QChart* chart;
    QChartView *ChartView;
    QSplineSeries *series;
};
#endif // MAINWIDGET_H
