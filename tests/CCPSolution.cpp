/*
    CCP - Capacited Clustering Problem.
    Copyright (C) 2009  Wagner Reck (wagner.reck@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "CCPSolution.h"
#include "Instance.h"
#include "Point.h"
#include "Distance.h"
#include "Solution.h"
#include "Cluster.h"
#include "readccp.h"
#include <QtTest/QTest>

#include "../src/algorithms/densitycluster.h"

using namespace CCP;

void CCPSolution::initTestCase()
{
    this->instance = new Instance;
    Point ** points = new Point*[6];
    points[0] = new Point(0.0, 2.0, 1.0);
    points[1] = new Point(0.0, 0.0, 1.0);
    points[2] = new Point(1.0, 1.0, 1.0);
    points[3] = new Point(2.0, 1.0, 1.0);
    points[4] = new Point(3.0, 0.0, 1.0);
    points[5] = new Point(3.0, 2.0, 1.0);
    instance->setPoints(points, 6);
    instance->setNumCenters(2);
    instance->setCapacity(3.5);
    new Distance(instance);
}

void CCPSolution::init()
{
  
}

void CCPSolution::cleanup()
{}

void CCPSolution::cleanupTestCase()
{
}

void CCPSolution::buildInitial()
{
    Solution * sol = new Solution(this->instance);
    Cluster * cluster;
    sol->constructSolution(CCP::Farthest);
    
    cluster = sol->cluster(0);
    QCOMPARE(cluster->numPoints(), (unsigned short) 2);
    QCOMPARE(cluster->getPoint(0), instance->point(0));
    QCOMPARE(cluster->getPoint(1), instance->point(1));
    QCOMPARE(cluster->totalDistance(), instance->distance(2,1) + instance->distance(0,2));
    
    cluster = sol->cluster(1);
    QCOMPARE(cluster->numPoints(), (unsigned short) 2);
    QCOMPARE(cluster->getPoint(0), instance->point(4));
    QCOMPARE(cluster->getPoint(1), instance->point(5));
    QCOMPARE(cluster->totalDistance(), instance->distance(4,3) + instance->distance(3,5));    
    
    QCOMPARE(sol->pointType(0), CCP::Consumer);
    
    QCOMPARE(sol->pointType(1), CCP::Consumer);
    QCOMPARE(sol->pointType(2), CCP::Center);
    
    QCOMPARE(sol->pointType(3), CCP::Center);
    QCOMPARE(sol->pointType(4), CCP::Consumer);
    QCOMPARE(sol->pointType(5), CCP::Consumer);
    
    QVERIFY((sol->getValue() - 5.65685) < 0.00001);
    
}
void CCPSolution::buildDensity(){
    
    DensityCluster  density(instance);
    density.buildClusters();
    
//     QFAIL("Not implemented yet");
     QVERIFY(qAbs(density.pointDensity(0)-(double)0.878683) < 0.00001); 
     QVERIFY(qAbs(density.pointDensity(1)-(double)0.878683) < 0.00001); 
    QVERIFY(qAbs(density.pointDensity(2)-(double)1.242647) < 0.00001); 
    QVERIFY(qAbs(density.pointDensity(3)-(double)1.242647) < 0.00001); 
    QVERIFY(qAbs(density.pointDensity(4)-(double)0.878683) < 0.00001);
    QVERIFY(qAbs(density.pointDensity(5)-(double)0.878683) < 0.00001);
    
    
    QCOMPARE(density.greatDensity(), (unsigned short)2);
    QCOMPARE(density.greatDensity(1),(unsigned short) 3);
    QCOMPARE(density.greatDensity(2),(unsigned short) 0);
    
    QCOMPARE(density.greatRegret(), (unsigned short) 2);
    QCOMPARE(density.greatRegret(1), (unsigned short) 3);
    QCOMPARE(density.greatRegret(2), (unsigned short) 0);
    QCOMPARE(density.greatRegret(3), (unsigned short) 1);
    QCOMPARE(density.greatRegret(4), (unsigned short) 4);
    QCOMPARE(density.greatRegret(5), (unsigned short) 5);
    
    
}

void CCPSolution::buildFile(){
  Instance * fileInst = readCCP::readLorenaEuclidian("../../instances/lorenaEuclidian.dat");
  Distance * dist = new Distance(fileInst);
  DensityCluster  density(fileInst);
  density.buildClusters();
  
  
}

QTEST_MAIN(CCPSolution)
#include "CCPSolution.moc"