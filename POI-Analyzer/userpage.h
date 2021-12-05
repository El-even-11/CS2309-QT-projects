#ifndef USERPAGE_H
#define USERPAGE_H

#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QtCharts>
#include <QVector>
#include <QMap>

#include "poi.h"

class UserPage : public QWidget
{
    Q_OBJECT
public:
    explicit UserPage(QVector<POI*>* data,QWidget *parent = nullptr);

public slots:
    void setTimeChartViews(bool checked);
    void setPOIChartViews(bool checked);
    void setChartViews();

private:
    void loadData();
    void createTimeChart();
    void createPOIChart();

private:
    QGridLayout *gridLayout = nullptr;

    QLineEdit* input = nullptr;
    QGroupBox* groupBox = nullptr;
    QRadioButton* radio1 = nullptr;
    QRadioButton* radio2 = nullptr;

    QWidget *chartContainer = nullptr;
    QGridLayout* containerLayout = nullptr;
    QChartView *timeChartView = nullptr;
    QChart *timeChart = nullptr;
    QChartView *poiChartView = nullptr;
    QChart *poiChart = nullptr;

    QList<QChartView*> chartviews;
    QList<QChart*> charts;

    QVector<POI*>* data = nullptr;

    int userCnt;
    QMap<int,QVector<POI*>> userData;
};

#endif // USERPAGE_H
