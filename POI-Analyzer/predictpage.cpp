#include "predictpage.h"

PredictPage::PredictPage(QVector<QList<POI*>> *userData,QVector<QList<POI*>> *poiData,QWidget *parent) : QWidget(parent)
{
    this->userData=userData;
    this->poiData=poiData;
    userCnt=userData->size();
    poiCnt=poiData->size();

    gridLayout = new QGridLayout();
    userBox = new QGroupBox();
    poiBox = new QGroupBox();
    userLineEdit = new QLineEdit();
    poiLineEdit = new QLineEdit();


    QGridLayout *grid1 = new QGridLayout();
    QGridLayout *grid2 = new QGridLayout();

}
