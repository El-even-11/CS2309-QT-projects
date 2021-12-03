#ifndef USERPAGE_H
#define USERPAGE_H

#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QChart>
#include <QVector>
#include <QMap>

#include "poi.h"

class UserPage : public QWidget
{
    Q_OBJECT
public:
    explicit UserPage(QVector<POI*>* data,QWidget *parent = nullptr);

public slots:
    void setTimeCharts(bool checked);
    void setPOICharts(bool checked);

private:
    QChart *createTimeChart();
    void loadData();

private:
    QGridLayout *gridLayout;

    QLineEdit* input;

    QGroupBox* groupBox;

    QRadioButton* radio1;
    QRadioButton* radio2;

    QVector<POI*>* data;

    QMap<int,QVector<POI*>> userData;
};

#endif // USERPAGE_H
