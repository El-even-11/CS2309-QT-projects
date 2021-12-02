#include "poi.h"

POI::POI(int user_id,int loc_id,QString time,double latitude,double longitude):
    _user_id(user_id),
    _loc_id(loc_id),
    _time(time),
    _latitude(latitude),
    _longitude(longitude)
{

}
