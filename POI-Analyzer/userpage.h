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
    void setTimeChartView(bool checked);
    void setPOIChartView(bool checked);
    void setCmpChartView(bool checked);
    void setChartViews();
    void resetFilters();
    void updateFilters();

private:
    void loadData();
    void createTimeChart();
    void createPOIChart();
    void createCmpChart();

private:
    QGridLayout *gridLayout;

    QLineEdit* lineEdit;
    QGroupBox* optionBox;
    QRadioButton* radio1;
    QRadioButton* radio2;
    QRadioButton* radio3;
    QGroupBox* filters;
    QGroupBox* timeFilter;
    QDateEdit* dateFrom;
    QDateEdit* dateTo;
    QGroupBox* gpsFilter;
    QGroupBox* longitudeFilter;
    QDoubleSpinBox* longitudeFrom;
    QDoubleSpinBox* longitudeTo;
    QGroupBox* latitudeFilter;
    QDoubleSpinBox* latitudeFrom;
    QDoubleSpinBox* latitudeTo;
    QPushButton* filterApply;
    QPushButton* filterReset;

    QWidget *chartContainer;
    QGridLayout* containerLayout;
    QChartView *timeChartView;
    QChart *timeChart;
    QChartView *poiChartView;
    QChart *poiChart;

    QList<QChartView*> chartviews;
    QList<QChart*> charts;

    QVector<POI*>* data;

    int userCnt;
    QMap<int,QVector<POI*>> userData;
};

#endif // USERPAGE_H
