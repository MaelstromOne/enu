#include <Enu.h>

#include <iostream>

int main(int argc, char *argv[])
{
    Enu *enu = new Enu({55, 49});

    Geodetic geoPoint = {55, 55};

    Cartesian point = enu->convertGeodetic2Local(geoPoint);
    Geodetic newGeoPoint = enu->convertLocal2Geodetic(point);

    std::cout << newGeoPoint.lat() << " " << newGeoPoint.lon() << std::endl;
}
