#include <QtTest>

#include "../src/Enu.h"

class tst_Enu : public QObject
{
    Q_OBJECT

public:
    tst_Enu();
    ~tst_Enu();

private slots:
    void test_case1();

};

tst_Enu::tst_Enu()
{

}

tst_Enu::~tst_Enu()
{

}

void tst_Enu::test_case1()
{
    Enu *enu = new Enu({55, 49});

    std::vector<Geodetic> geoPoints = {
        {55, 49},
//        {55, 49, 100},
        {54, 48},
        {54, 48, 100},
        {30, 27, 100},
    };

    for(Geodetic &geoPoint : geoPoints) {
        Cartesian point = enu->convertGeodetic2Local(geoPoint);
        Geodetic newGeoPoint = enu->convertLocal2Geodetic(point);

        QCOMPARE(newGeoPoint.lat(), geoPoint.lat());
        QCOMPARE(newGeoPoint.lon(), geoPoint.lon());
        QCOMPARE(newGeoPoint.alt(), geoPoint.alt());
    }

    delete enu;
}

QTEST_APPLESS_MAIN(tst_Enu)

#include "tst_Enu.moc"
