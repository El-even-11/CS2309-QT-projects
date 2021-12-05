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
    void crearePOIChart();

private:
    QGridLayout *gridLayout;

    QLineEdit* input;
    QGroupBox* groupBox;
    QRadioButton* radio1;
    QRadioButton* radio2;

    QWidget *chartContainer;
    QGridLayout* containerLayout;
    QChartView *timeChartView;
    QChart *timeChart;

    QList<QChartView*> chartviews;

    QVector<POI*>* data;

    int userCnt;
    QMap<int,QVector<POI*>> userData;
};

#endif // USERPAGE_H
