#ifndef POI_H
#define POI_H

#include <QString>
#include <QDate>
#include <QVector>
#include <QList>

class POI
{
public:
    POI(int userID,int locID,QString datetime,double latitude,double longitude);

    static QList<POI*> filter(const QList<POI*>& tuples,QDate minDate,QDate maxDate,QTime minTime,QTime maxTime,double minLng,double maxLng,double minLat,double maxLat);
    static QString timeInterval(QTime time);

    int userID;
    int locID;
    QDate date;
    QTime time;
    double latitude;
    double longitude;

    static QVector<QDate> monthRange;
    static QVector<QString> timeIntervals;

private:
    static QList<POI*> dateFilter(const QList<POI*>& tuples,QDate minDate,QDate maxDate);
    static QList<POI*> timeFilter(const QList<POI*>& tuples,QTime minTime,QTime maxTime);
    static QList<POI*> lngFilter(const QList<POI*>& tuples,double minLng,double maxLng);
    static QList<POI*> latFilter(const QList<POI*>& tuples,double minLat,double maxLat);
};
#endif // POI_H
