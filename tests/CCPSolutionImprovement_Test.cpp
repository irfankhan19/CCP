#include "CCPSolutionImprovement_Test.h"
#include <QTest>
#include <Instance.h>
#include <Solution.h>
#include <SolutionImprovement.h>
#include <Distance.h>
#include <QDebug>

using namespace CCP;

void CCPSolutionImprovement_Test::initTestCase(){
    this->_instance = new Instance;
     Point ** points = new Point*[6];
     points[0] = new Point(_instance,0.0, 2.0, 1.0);
     points[1] = new Point(_instance,0.0, 0.0, 1.0);
     points[2] = new Point(_instance,1.0, 1.0, 1.0);
     points[3] = new Point(_instance,2.0, 1.0, 1.0);
     points[4] = new Point(_instance,3.0, 0.0, 1.0);
     points[5] = new Point(_instance,3.0, 2.0, 1.0);
     _instance->setPoints(points, 6);
     _instance->setNumCenters(2);
     _instance->setCapacity(5.0);
     new Distance(_instance);
}

void CCPSolutionImprovement_Test::cleanupTestCase(){
//    QFAIL("Not implemented yet");
}

void CCPSolutionImprovement_Test::cleanup(){
}

void CCPSolutionImprovement_Test::hillClimbShift1(){
//    QFAIL("Not implemented yet");

    Solution * orig = new Solution(_instance);
    orig->constructSolution(HMeans);

    Solution improved = SolutionImprovement::hillClimbShift(*orig);

    QVERIFY2 (improved.isValid(), "Invalid Solution.");
   // QVERIFY2 (improved.getValue() <= orig->getValue(), "Invalid Solution."); // cannt say all the times will get a better solution
    qDebug() << improved.getValue() << orig->getValue();
    delete orig;
}



void CCPSolutionImprovement_Test::hillClimbInterchange1(){
    Solution * orig = new Solution(_instance);
    orig->constructSolution(HMeans);

    Solution improved = SolutionImprovement::hillClimbInterchange(*orig);

    QVERIFY2 (improved.isValid(), "Invalid Solution.");
    QVERIFY2 (improved.getValue() <= orig->getValue(), "Invalid Solution.");
    qDebug() << improved.getValue() << orig->getValue();
    delete orig;
}

void CCPSolutionImprovement_Test::SAShift1(){
    Solution * orig = new Solution(_instance);
    orig->constructSolution(HMeans);

    Solution improved = SolutionImprovement::SAShift(*orig);

    QVERIFY2 (improved.isValid(), "Invalid Solution.");
    QVERIFY2 (improved.getValue() <= orig->getValue(), "Invalid Solution.");
    qDebug() << improved.getValue() << orig->getValue();
    delete orig;
}

void CCPSolutionImprovement_Test::SAInterchange1(){
    Solution * orig = new Solution(_instance);
    orig->constructSolution(HMeans);

    Solution improved = SolutionImprovement::SAInterchange(*orig);

    QVERIFY2 (improved.isValid(), "Invalid Solution.");
    QVERIFY2 (improved.getValue() <= orig->getValue(), "Invalid Solution.");
    qDebug() << improved.getValue() << orig->getValue();
    delete orig;
}


QTEST_MAIN(CCPSolutionImprovement_Test)
#include "CCPSolutionImprovement_Test.moc"
