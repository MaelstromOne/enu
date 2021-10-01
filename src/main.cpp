#include <Enu.h>

#include <iostream>
#include <iomanip>
#include <vector>

int main(int argc, char *argv[])
{
    Enu *enu = new Enu({55, 49});

    std::vector<Geodetic> geoPoints = {
        {55, 49},
        {55, 49, 100},
        {54, 48},
        {54, 48, 100},
        {30, 27, 100},
    };

            std::cout << std::setprecision(17);

    for(Geodetic &geoPoint : geoPoints) {
        Cartesian point = enu->convertGeodetic2Local(geoPoint);
        Geodetic newGeoPoint = enu->convertLocal2Geodetic(point);

        std::cout << point.x() << " " << point.y() << std::endl;
        std::cout << geoPoint.lat() << " " << geoPoint.lon() << std::endl;
        std::cout << newGeoPoint.lat() << " " << newGeoPoint.lon() << std::endl;
        std::cout << std::endl;
    }

    delete enu;
}
