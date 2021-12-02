#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QFile>
#include <QVector>

#include "poi.h"

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
    bool loadData();

private:
    Ui::MainWidget *ui;

    QString filename;
    QFile *file;

    QVector<POI*> data;
};
#endif // MAINWIDGET_H
