#ifndef RecoDataProducts_TrkHit_h
#define RecoDataProducts_TrkHit_h

//
// A data-like hit; contains no MCTruth information.
//

#include <ostream>

namespace tex {

  class TrkHit {

  public:

    TrkHit();
#ifndef __GCCXML__

    TrkHit( int    shell,
	    double z,
	    double phi,
	    double sz,
	    double zphi);

    int    shell()  const { return _shell; }
    double z()      const { return _z;     }
    double phi()    const { return _phi;   }
    double sigZ()   const { return _sz;    }
    double sigPhi() const { return _sphi;  }
#endif  // __GCCXML__

  private:

    int    _shell;
    double _z;
    double _phi;
    double _sz;
    double _sphi;

  };

#ifndef __GCCXML__
  std::ostream& operator<<(std::ostream& ost,
                           const tex::TrkHit& hit );
#endif  // __GCCXML__

}

#endif /* RecoDataProducts_TrkHit_h */

