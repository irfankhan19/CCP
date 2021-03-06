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

#ifndef SOLUTION_H
#define SOLUTION_H

#include "model_global.h"

/**
 * Namespace
 */
#include "Point.h"
#include <QList>
#include <QString>

#include "SolutionImprovement.h"


namespace CCP {
    class Point;
    class Instance;
    class Cluster;
    class History;



    /**
 * Class Solution
 */
 class Solution
           :public QObject {
           Q_OBJECT
        /**
 * Public stuff
 */
        //public slots:


    public:
        /**
     * Constructors
     */
        /**
     * Empty Constructor
     */
        Solution ( Instance * instance);

        ~Solution();
        /**
     * Accessor Methods
     */
        /**
    */
        void setInstance (Instance * inst);

        /**
    *
    */
        Instance * instance(){
            return _myInstance;
        }
        /**
     *
     */
        PointType pointType (unsigned short index);


        //     void setPointsType (PointType * value ) {
        //         _pointsType = value;
        //     }


        void constructSolution(HeuristicType type);



        void setAlgorithmToUse(HeuristicType type);


        void run();


        Cluster * cluster(unsigned short index){
            return _centers[index];
        }

        /** return name of algorithm used.*/
        QString algorithmName(){ return _myAlgorithmName;}

        /** Return time taken to perform selected algorithm (in seconds).*/
        double timeTaken(){return _myTime;}

        /** Return iterations taken to perform algorithm. */
        long iterations(){return _myIterations;}

        void setIterations(long iter) {_myIterations = iter;}

        /**
     * @brief Return the point thats represent the center of cluster at index.
     * Use this method is same that does Solution::cluster(index)->centerPoint();
     * @param index index of cluster in array. Shoud be less than number of centers.
     * @return Point considered as center os cluster.
    */
        Point * centerOfCluster(unsigned short index);
        Instance * getInstance(){       return _myInstance;
        }
        double getValue();
        void setPointType( Point* arg1, PointType arg2 );

        /** @brief Return if the Solution is valid or not.
	This method check if all points are assigned to only on cluster, all cluster have a center and the center is not an consumer point too.
	Is checked also the capacity of clusters.
	*/
        bool isValid() ;

        bool isImprovement() const { return toImprove;}

        Solution * improve();

        Solution * solutionParent() { return _parent;}

        void setImprovement(ImprovementHeuristic type);


        History * history();

        Solution * clone() const;

        /**
 * Private stuff
 */
    private:
        /**
     * Fields
     */
        long _myIterations;
        double _myTime;
        QString _myAlgorithmName;

        Instance * _myInstance;

        Cluster ** _centers;

        HeuristicType _type;

        bool toImprove;

        ImprovementHeuristic improveType;

        Solution * _parent;
            History* _history;
    };
}
#endif //SOLUTION_H

