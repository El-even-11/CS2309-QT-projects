#ifndef POI_H
#define POI_H

#include <QString>
#include <QDate>
#include <QVector>

class POI
{
public:
    POI(int userID,int locID,QString time,double latitude,double longitude);

    static QDate getDate(QString time);

    int userID;
    int locID;
    QString time;
    double latitude;
    double longitude;

    static QVector<QDate> monthRange;
};
#endif // POI_H
