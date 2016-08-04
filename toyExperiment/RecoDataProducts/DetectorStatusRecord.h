#ifndef RecoDataProducts_DetectorStatusRecord_h
#define RecoDataProducts_DetectorStatusRecord_h

//
// A minimal class to mock up status information that might be produced by the online system.
// It represents status information about one of the detector elements.
//

#include <ostream>

namespace tex {

  class DetectorStatusRecord {

  public:

    DetectorStatusRecord();

#ifndef __GCCXML__
    DetectorStatusRecord( bool isOn, double voltage );

    bool   isOn   ( ) const { return  _isOn;    }
    bool   isOff  ( ) const { return !_isOn;    }
    double voltage( ) const { return  _voltage; }
#endif  // __GCCXML__

  private:

    bool   _isOn;
    double _voltage;

  };

#ifndef __GCCXML__
  inline std::ostream& operator<<(std::ostream& ost,
                                  const tex::DetectorStatusRecord& d ){
    ost << d.isOn() << " " << d.voltage();
    return ost;
  }
#endif  // __GCCXML__

}

#endif /* RecoDataProducts_DetectorStatusRecord_h */
