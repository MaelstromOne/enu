# Library convert from Geodetic coordinate to ENU system coordinate and back

## How to use library

Before start convert coordinate, you need setup reference point

`Enu *enu = new Enu({55, 49});`

After you can make convert geodetic to enu

`Geodetic geoPoint = {55, 55};
Cartesian point = enu->convertGeodetic2Local(geoPoint);`

Or enu to geodetic

`Geodetic newGeoPoint = enu->convertLocal2Geodetic(point);`
