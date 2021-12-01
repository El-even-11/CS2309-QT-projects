#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QString>
#include <QFile>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget();

private:
    QString filename;
    QFile file;

};
#endif // MAINWIDGET_H
