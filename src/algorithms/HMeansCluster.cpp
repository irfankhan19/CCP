/*
Wagner de Melo Reck (wagner.reck@gmail.com)

CCP

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

#include "HMeansCluster.h"
#include <QTime>


HMeansCluster::HMeansCluster(CCP::Instance* inst): AlgorithmStruct(inst)
{

}


HMeansCluster::~HMeansCluster()
{

}


CCP::Cluster** HMeansCluster::buildClusters()
{
    selectInitialCenters();
    bool changed = true;
    
    while (changed){
	//Remove all points
	unAssignAllConsumers();
	
	//re-assign points to nearst center...
	for (int i = 0; i < instance()->numPoints; ++i){
	    if (!isAssigned(i)){
	      int cen = -1;
	      QList<int> forbiden;
	      do{
		cen = findNearCenter(instance()->point(i), forbiden)
		if (cen = -1){
		    //Cant find any center. Do something
		    break;
		}
		if (_centers[cen]->remainCapacity() >= instance()->point(i)->demand() ){
		    assign(cen, i); 
		    break;
		}
		forbiden << cen;
	      }while(1);
	    }
	}
	
	//Try find bests centers
	changed = findBestCenters();
    }
    
    return _centers;
    
}


void HMeansCluster::selectInitialCenters(){
  qsrand(QTime::msec());
  int i;
  
  for (i = 0; i < instance()->numCenters(); ++i){
    int gen;
    do{
      gen = qrand() % instance()->numPoints();
    }while (isAssigned(gen));
    assign(gen,i,CCP::Center);
  }
}