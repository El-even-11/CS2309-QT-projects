#ifndef MAPPAGE_H
#define MAPPAGE_H

#include <QWidget>
#include <QList>
#include <QWebEngineView>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QVector>
#include <QMap>
#include <QDateEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>

#include "poi.h"

class MapPage : public QWidget
{
    Q_OBJECT
public:
    explicit MapPage(QVector<QList<POI*>> *userData,QVector<QList<POI*>> *poiData,int totalCnt,QWidget *parent = nullptr);

public slots:
    void updateUI();
    void showEdit();
    void resetFilters();
    void init();

private:
    void updatePOI();
    void updateUser();

private:
    QGridLayout *gridLayout;


    QGroupBox* optionBox;
    QRadioButton* radio1;
    QRadioButton* radio2;
    QLineEdit* lineEdit;

    QGroupBox* diagramBox;
    QRadioButton* radio3;
    QRadioButton* radio4;

    QGroupBox* filters;
    QGroupBox* dateFilter;
    QDateEdit* dateFrom;
    QDateEdit* dateTo;
    QGroupBox* longitudeFilter;
    QDoubleSpinBox* longitudeFrom;
    QDoubleSpinBox* longitudeTo;
    QGroupBox* latitudeFilter;
    QDoubleSpinBox* latitudeFrom;
    QDoubleSpinBox* latitudeTo;
    QPushButton* filterApply;
    QPushButton* filterReset;
    QLabel* filterLabel;

    QWebEngineView *map;

    int totalCnt;

    int userCnt;
    QVector<QList<POI*>> *userData;

    int poiCnt;
    QVector<QList<POI*>> *poiData;

};

#endif // MAPPAGE_H
