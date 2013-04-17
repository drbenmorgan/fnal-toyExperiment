//
// A minimal class to mock up detector status information that might be
// produced by the online system.
//

#include "toyExperiment/RecoDataProducts/DetectorStatus.h"

tex::DetectorStatus::DetectorStatus( ):_records(){
}
  
tex::DetectorStatus::DetectorStatus( size_t n):_records(){
  _records.reserve(n);
}

void 
tex::DetectorStatus::addRecord( DetectorStatusRecord const& record ){
  _records.push_back(record);
}
