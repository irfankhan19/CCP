#include "Distance.h"
#include "Point.h"
#include "Instance.h"


/**
 * Constructors/Destructors
 */
CCP::Distance::Distance (Instance * inst):
  _numPoints(inst->numPoints()),
  _instance(inst)
{
  _instance->setDistances(this);
  unsigned short count, count2;
  this->_values = new double*[_numPoints];
  this->_ordered = new short*[_numPoints];
  for (count = 0; count < _numPoints; ++count){
      this->_values[count] = new double[count];
      this->_ordered[count] = new short[_numPoints];
      for (count2 = 0; count2 < _numPoints; ++count2){
	 if (count2 < count){
	    _values[count][count2] = -1;
	 }
	 this->_ordered[count][count2] = -1;
      }
  }
}

CCP::Distance::~Distance(){
    unsigned short count;
    for (count = 0; count < _numPoints; ++count){
      delete []_values;
      delete []_ordered;
    }
    delete [] _values;
    delete [] _ordered;
    
}

double CCP::Distance::distanceBetween(unsigned short int point1, unsigned short int point2 ){
  CCP::Point * p1 = _instance->point(point1);
  CCP::Point * p2 = _instance->point(point2);
  
  if (p1 == 0 || p2 == 0){
      return -1;
  }else{
      return p1->position().distance(p2->position());
  }
}
