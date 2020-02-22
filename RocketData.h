#ifndef ROCKETDATA_H
#define ROCKETDATA_H

#endif // ROCKETDATA_H

#include "HelperStructs.h"

struct RocketData {
    char startMarker[3];
    GeoLocation location;
    Vector3 acceleration;
    Quaternion rotation;
    double airbrakesAngle;
    double tempAV;
    double tempAmbient;
    bool parachuteDeployed;
    double batteryAV;
    double batteryAirbrakes;
    unsigned long int timeSent;
    char endMarker[3];
};
