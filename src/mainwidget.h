#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QFile>
#include <QList>

#include "poi.h"
#include "userpage.h"
#include "poipage.h"
#include "mappage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    bool loadData(QFile* file);
    void setTabs();
    void setStyleSheets();

private:
    Ui::MainWidget *ui;

    int filesize;

    int datasize;
    QVector<QList<POI*>> userData;
    QVector<QList<POI*>> poiData;

    UserPage *userPage;
    POIPage *poiPage;
    MapPage *mapPage;
};
#endif // MAINWIDGET_H
