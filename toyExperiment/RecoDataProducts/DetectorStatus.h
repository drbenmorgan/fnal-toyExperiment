#ifndef RecoDataProducts_DetectorStatus_h
#define RecoDataProducts_DetectorStatus_h

//
// A minimal class to mock up detector status information that might be
// produced by the online system.
//
// In this case, the data product is a not a collection type, just to
// show that data products need not be collection types.
//

#include "toyExperiment/RecoDataProducts/DetectorStatusRecord.h"

#include <vector>
#include <ostream>

namespace tex {

  class DetectorStatus {

  public:

    DetectorStatus( );
    DetectorStatus( size_t n);

    void addRecord( DetectorStatusRecord const& record );

    DetectorStatusRecord const& record( size_t id ) const { return _records.at(id); }


  private:

    std::vector<DetectorStatusRecord> _records;

  };

  /*
    // Fixme: make this real
  inline
  std::ostream& operator<<(std::ostream& ost,
  const DetectorStatus& d ){
    ost << d.isOn() << " " << d.voltage();
    return ost;
  }
  */

}

#endif /* RecoDataProducts_DetectorStatus_h */
