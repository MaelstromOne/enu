#pragma once

#include <mutex>

#include "Matrix.h"

class Cartesian : public Vector3D
{
public:
    Cartesian() {}
    Cartesian(Vector3D vector) : Vector3D(vector) {}
    Cartesian(double x, double y, double z = 0) : Vector3D({x, y, z}) {}

    double x() { return this->at(0); }
    double y() { return this->at(1); }
    double z() { return this->at(2); }

    const double &x() const { return this->at(0); }
    const double &y() const { return this->at(1); }
    const double &z() const { return this->at(2); }
};

class Geodetic : public Vector3D
{
public:
    Geodetic() {}
    Geodetic(Vector3D vector) : Vector3D(vector) {}
    Geodetic(double lat, double lon, double alt = 0) : Vector3D({lat, lon, alt}) {}

    double lat() { return this->at(0); }
    double lon() { return this->at(1); }
    double alt() { return this->at(2); }

    const double &lat() const { return this->at(0); }
    const double &lon() const { return this->at(1); }
    const double &alt() const { return this->at(2); }
};

class Enu
{
public:
    Enu(const Geodetic &geodetic);
    Cartesian convertGeodetic2Local(const Geodetic &geodetic) const;
    Geodetic convertLocal2Geodetic(const Cartesian &local) const;

protected:
    void setReference(const Geodetic &geodetic);
    void initMatrix(const Geodetic &geodetic);
    Cartesian convertGeodetic2Cartesian(const Geodetic &geodetic) const;
    Cartesian convertCartesian2Local(const Cartesian &cartesian) const;
    Cartesian convertLocal2Cartesian(const Cartesian &local) const;
    Geodetic convertCartesian2Geodetic(const Cartesian &cartesian) const;

private:
    Cartesian referCartesian;
    Matrix3x3D matrix;
    Matrix3x3D matrixInv;

private:
    static constexpr double pi = M_PI;
    static constexpr double a = 6378137;
    static constexpr double e = 0.081819218;
};

class EnuSingletone {

public:
    EnuSingletone() = delete;
    static void initInstance(const Geodetic &geodetic);
    static std::shared_ptr<Enu> getInstance();

private:
    static std::shared_ptr<Enu> instance;
    static std::mutex mutex;
};
