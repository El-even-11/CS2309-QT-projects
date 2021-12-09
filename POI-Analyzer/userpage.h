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
    explicit UserPage(QList<POI*>* data,QWidget *parent = nullptr);

public slots:
    void resetFilters();
    void updateUI();
    void optionChanged(bool checked);

private:
    void loadData();

    void setGeneralChart(const QVector<int>& ids,const QList<POI*>& tuples);
    void setPOIChart(const QVector<int>& ids,const QList<POI*>& tuples);
    void setCmpChart(const QVector<int>& ids,const QList<POI*>& tuples);
    void setDailyChart(const QVector<int>& ids,const QList<POI*>& tuples);

private:
    QGridLayout *gridLayout;

    QLineEdit* lineEdit;
    QGroupBox* optionBox;
    QRadioButton* radio1;
    QRadioButton* radio2;
    QRadioButton* radio3;
    QRadioButton* radio4;
    QGroupBox* filters;
    QGroupBox* dateFilter;
    QDateEdit* dateFrom;
    QDateEdit* dateTo;
    QGroupBox* timeFilter;
    QTimeEdit* timeFrom;
    QTimeEdit* timeTo;
    QGroupBox* longitudeFilter;
    QDoubleSpinBox* longitudeFrom;
    QDoubleSpinBox* longitudeTo;
    QGroupBox* latitudeFilter;
    QDoubleSpinBox* latitudeFrom;
    QDoubleSpinBox* latitudeTo;
    QPushButton* filterApply;
    QPushButton* filterReset;
    QLabel* filterLabel;
    QGroupBox* tableContainer;
    QTableWidget* table;

    QWidget *chartContainer;
    QGridLayout* containerLayout;
    QChartView *generalChartView;
    QChart *generalChart;
    QChartView *poiChartView;
    QChart *poiChart;
    QChartView *dailyChartView;
    QChart *dailyChart;
    QChartView *cmpChartView1;
    QChartView *cmpChartView2;
    QChartView *cmpChartView3;
    QChartView *cmpChartView4;
    QChart *cmpChart1;
    QChart *cmpChart2;
    QChart *cmpChart3;
    QChart *cmpChart4;

    QList<QChartView*> chartviews;
    QList<QChart*> charts;

    QList<POI*>* data;

    int userCnt;
    QVector<QList<POI*>> userData;
};

#endif // USERPAGE_H
