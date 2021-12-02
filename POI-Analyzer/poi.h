#ifndef POI_H
#define POI_H

#include <QString>

class POI
{
public:
    POI(int user_id,int loc_id,QString time,double latitude,double longitude);

    int _user_id;
    int _loc_id;
    QString _time;
    double _latitude;
    double _longitude;
};

#endif // POI_H
