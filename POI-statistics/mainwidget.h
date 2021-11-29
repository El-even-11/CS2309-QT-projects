#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtCharts>
#include <QPushButton>
#include <vector>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget();

public slots:
    void setData();


private:
    QChart* chart;
    QChartView *ChartView;
    QSplineSeries *series;
    QVBoxLayout *container;

    QPushButton *btn;

    std::vector<std::pair<int,int>> data;
};
#endif // MAINWIDGET_H
