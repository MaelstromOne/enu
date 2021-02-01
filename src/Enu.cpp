#include "Enu.h"

#include <functional>

Enu::Enu(const Geodetic &geodetic)
{
    setReference(geodetic);
    initMatrix(geodetic);
}

Cartesian Enu::convertGeodetic2Local(const Geodetic &geodetic) const
{
    Cartesian cartesian = convertGeodetic2Cartesian(geodetic);
    return convertCartesian2Local(cartesian);
}

Geodetic Enu::convertLocal2Geodetic(const Cartesian &local) const
{
    Cartesian cartesian = convertLocal2Cartesian(local);
    return convertCartesian2Geodetic(cartesian);
}

void Enu::setReference(const Geodetic &geodetic) {
    referCartesian = convertGeodetic2Cartesian(geodetic);
}

void Enu::initMatrix(const Geodetic &geodetic)
{
    double lat = geodetic.lat() * pi / 180;
    double lon = geodetic.lon() * pi / 180;

    matrix = {
        {-std::sin(lon),                std::cos(lon),               0.,          },
        {-std::sin(lat)*std::cos(lon), -std::sin(lat)*std::sin(lon), std::cos(lat)},
        { std::cos(lat)*std::cos(lon),  std::cos(lat)*std::sin(lon), std::sin(lat)}
    };

    matrixInv = {
        {-std::sin(lon), -std::sin(lat)*std::cos(lon),         std::cos(lat)*std::cos(lon)},
        { std::cos(lon), -std::sin(lat)*std::sin(lon),         std::cos(lat)*std::sin(lon)},
        { 0.,             std::cos(lat),                       std::sin(lat)}
    };
}

Cartesian Enu::convertGeodetic2Cartesian(const Geodetic &geodetic) const {
    double lat = geodetic.lat() * pi / 180;
    double lon = geodetic.lon() * pi / 180;
    double h   = geodetic.alt();

    double N = a / std::sqrt(1 - e*e * std::sin(lat) * std::sin(lat));

    double x = (N + h) * std::cos(lat) * std::cos(lon);
    double y = (N + h) * std::cos(lat) * std::sin(lon);
    double z = (N * (1 - e*e) + h)  * std::sin(lat);

    return Cartesian(x, y, z);
}

Cartesian Enu::convertCartesian2Local(const Cartesian &cartesian) const
{
    return matrix * (cartesian - referCartesian);
}

Cartesian Enu::convertLocal2Cartesian(const Cartesian &local) const
{
    return matrixInv * local + referCartesian;
}

Geodetic Enu::convertCartesian2Geodetic(const Cartesian &cartesian) const
{
    double x = cartesian.x();
    double y = cartesian.y();
    double z = cartesian.z();

/// link to algorithm
/// https://www.mathworks.com/help/aeroblks/ecefpositiontolla.html

    double lon = atan2(y, x);

    double s = sqrt(x*x + y*y);
    double c = sqrt(1 - e*e);
    double b = atan2(z, c*s);
    double lat = atan2(z + e*e*a*pow(sin(b), 3)/c, s - e*e*a*pow(cos(b), 3));

    double N = a / sqrt(1 - e*e*sin(lat)*sin(lat));
    double alt = s*cos(lat) + (z + e*e*N*sin(lat))*sin(lat) - N;

    return Geodetic(lat * 180 / pi, lon * 180 / pi, alt);
}

void EnuSingletone::initInstance(const Geodetic &geodetic)
{
    std::lock_guard<std::mutex> locker(mutex);
    instance = std::shared_ptr<Enu>(new Enu(geodetic));
}

std::shared_ptr<Enu> EnuSingletone::getInstance()
{
    std::lock_guard<std::mutex> locker(mutex);
    if (!instance) {
        throw std::logic_error("The reference geodetic coordinate is not initialized");
    }
    return instance;
}

std::shared_ptr<Enu> EnuSingletone::instance = nullptr;
std::mutex EnuSingletone::mutex;
