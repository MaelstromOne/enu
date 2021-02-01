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

    Geodetic geoPoint = {55, 50, 100};

    Cartesian point = enu->convertGeodetic2Local(geoPoint);
    Geodetic newGeoPoint = enu->convertLocal2Geodetic(point);

    QCOMPARE(newGeoPoint.lat(), geoPoint.lat());
    QCOMPARE(newGeoPoint.lon(), geoPoint.lon());
    QCOMPARE(newGeoPoint.alt(), geoPoint.alt());
}

QTEST_APPLESS_MAIN(tst_Enu)

#include "tst_Enu.moc"
