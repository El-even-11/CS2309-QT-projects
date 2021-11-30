#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtCharts>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <vector>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget();

public slots:
    void setData();
    void setRange();

private:
    QChart* chart;
    QChartView *chartView;
    QSplineSeries *series;
    QGridLayout *container;
    QLabel *starting;
    QLabel *ending;
    QLabel *select;
    QLabel *warning;
    QComboBox *startBox;
    QComboBox *endBox;
    QValueAxis *axisX;
    QValueAxis *axisY;

    QPushButton *btn;

    std::vector<std::pair<int,int>> data;


};
#endif // MAINWIDGET_H
