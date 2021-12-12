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

    QWebEngineView *map;

    QList<POI*>* data;
};

#endif // MAPPAGE_H
