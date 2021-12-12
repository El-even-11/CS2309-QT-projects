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
    explicit MapPage(QList<POI*>* data,QWidget *parent = nullptr);

public slots:
    void updatePOI();
    void updateUser();
    void updateUI();
    void showEdit();
    void resetFilters();
    void init();

private:
    void loadData();

private:
    QGridLayout *gridLayout;


    QGroupBox* optionBox;
    QRadioButton* radio1;
    QRadioButton* radio2;
    QLineEdit* lineEdit;

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
    QGroupBox* tableContainer;
    QTableWidget* table;

    QWebEngineView *map;

    QList<POI*>* data;

    int poiCnt;
    QVector<QList<POI*>> poiData;
};

#endif // MAPPAGE_H
