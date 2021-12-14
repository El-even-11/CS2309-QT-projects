#ifndef PREDICTPAGE_H
#define PREDICTPAGE_H

#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include "poi.h"

class PredictPage : public QWidget
{
    Q_OBJECT
public:
    explicit PredictPage(QVector<QList<POI*>> *userData,QVector<QList<POI*>> *poiData,QWidget *parent = nullptr);

private:
    QGridLayout *gridLayout;
    QGroupBox* userBox;
    QGroupBox* poiBox;
    QLineEdit *userLineEdit;
    QLineEdit *poiLineEdit;

    QLabel* userPredictionLabel;
    QLabel* poiPredictionLabel;

    int userCnt;
    QVector<QList<POI*>> *userData;

    int poiCnt;
    QVector<QList<POI*>> *poiData;
};

#endif // PREDICTPAGE_H

