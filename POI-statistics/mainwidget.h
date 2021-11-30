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
    void setStartingWeek();
    void setEndingWeek();

private:
    QChart* chart;
    QChartView *chartView;
    QSplineSeries *series;
    QGridLayout *container;
    QLabel *starting;
    QLabel *ending;
    QLabel *select;
    QComboBox *startBox;
    QComboBox *endBox;

    QPushButton *btn;

    std::vector<std::pair<int,int>> data;

    void setRange(int start,int end);
};
#endif // MAINWIDGET_H
