#ifndef POI_H
#define POI_H

#include <QString>
#include <QTime>

class POI
{
public:
    POI(int userID,int locID,QString time,double latitude,double longitude);

    static

    int userID;
    int locID;
    QString time;
    double latitude;
    double longitude;
};

#endif // POI_H
