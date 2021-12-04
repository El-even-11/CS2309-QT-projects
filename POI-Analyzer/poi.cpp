#include "poi.h"

POI::POI(int userID,int locID,QString time,double latitude,double longitude):
    userID(userID),
    locID(locID),
    time(time),
    latitude(latitude),
    longitude(longitude)
{

}

QDate POI::getDate(QString time){
    QStringList values = time.split("T");
    QStringList ymd = values[0].split("-");
    return QDate(ymd[0].toInt(),ymd[1].toInt(),ymd[2].toInt());
}

QVector<QDate> POI::monthRange{QDate(2009,2,15),
                              QDate(2009,3,15),
                              QDate(2009,4,15),
                              QDate(2009,5,15),
                              QDate(2009,6,15),
                              QDate(2009,7,15),
                              QDate(2009,8,15),
                              QDate(2009,9,15),
                              QDate(2009,10,15),
                              QDate(2009,11,15),
                              QDate(2009,12,15),
                              QDate(2010,1,15),
                              QDate(2010,2,15),
                              QDate(2010,3,15),
                              QDate(2010,4,15),
                              QDate(2010,5,15),
                              QDate(2010,6,15),
                              QDate(2010,7,15),
                              QDate(2010,8,15),
                              QDate(2010,9,15),
                              QDate(2010,10,15),
                              };
