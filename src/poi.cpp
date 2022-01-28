#include "poi.h"

POI::POI(int userID,int locID,QString datetime,double latitude,double longitude):
    userID(userID),
    locID(locID),
    latitude(latitude),
    longitude(longitude)
{
    QStringList values = datetime.split("T");
    QStringList ymd = values[0].split("-");
    date = QDate(ymd[0].toInt(),ymd[1].toInt(),ymd[2].toInt());
    values[1].chop(1);
    QStringList hms = values[1].split(":");
    time = QTime(hms[0].toInt(),hms[1].toInt(),hms[2].toInt());
}

QList<POI*> POI::filter(const QList<POI*>& tuples,QDate minDate,QDate maxDate,QTime minTime,QTime maxTime,double minLng,double maxLng,double minLat,double maxLat){
    return latFilter(lngFilter(timeFilter(dateFilter(tuples,minDate,maxDate),minTime,maxTime),minLng,maxLng),minLat,maxLat);
}

QString POI::timeInterval(QTime time){
    if (time<=QTime(5,59,59)){
        return "Before dawn";
    }else if(time <= QTime(10,59,59)){
        return "Morning";
    }else if(time <= QTime(12,59,59)){
        return "Noon";
    }else if(time <= QTime(17,59,59)){
        return "Afternoon";
    }else if(time <= QTime(20,59,59)){
        return "Evening";
    }else {
        return "Midnight";
    }
}

QList<POI*> POI::dateFilter(const QList<POI*>& tuples,QDate minDate,QDate maxDate){
    if (minDate==QDate(2009,2,1)&&maxDate==QDate(2010,10,31)){
        return tuples;
    }

    QList<POI*> filtered;
    QListIterator<POI*> it(tuples);
    while (it.hasNext()){
        POI* poi = it.next();
        if (poi->date >= minDate && poi->date <= maxDate){
            filtered << poi;
        }
    }

    return filtered;
}

QList<POI*> POI::timeFilter(const QList<POI*>& tuples,QTime minTime,QTime maxTime){
    if (minTime==QTime(0,0,0)&&maxTime==QTime(23,59,59)){
        return tuples;
    }

    QList<POI*> filtered;
    QListIterator<POI*> it(tuples);
    while (it.hasNext()){
        POI* poi = it.next();
        if (poi->time >= minTime && poi->time <= maxTime){
            filtered << poi;
        }
    }

    return filtered;
}

QList<POI*> POI::lngFilter(const QList<POI*>& tuples,double minLng,double maxLng){
    if (qFuzzyCompare(minLng,-180) && qFuzzyCompare(maxLng,180)){
        return tuples;
    }

    QList<POI*> filtered;
    QListIterator<POI*> it(tuples);
    while (it.hasNext()){
        POI* poi = it.next();
        if (poi->longitude >= minLng && poi->longitude <= maxLng){
            filtered << poi;
        }
    }

    return filtered;
}

QList<POI*> POI::latFilter(const QList<POI*>& tuples,double minLat,double maxLat){
    if (qFuzzyCompare(minLat,-90) && qFuzzyCompare(maxLat,90)){
        return tuples;
    }

    QList<POI*> filtered;
    QListIterator<POI*> it(tuples);
    while (it.hasNext()){
        POI* poi = it.next();
        if (poi->latitude >= minLat && poi->latitude <= maxLat){
            filtered << poi;
        }
    }

    return filtered;
}

QVector<QDate> POI::monthRange{
            QDate(2009,2,15),
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

QVector<QString> POI::timeIntervals{
    "Before dawn",
    "Morning",
    "Noon",
    "Afternoon",
    "Evening",
    "Midnight"
};
