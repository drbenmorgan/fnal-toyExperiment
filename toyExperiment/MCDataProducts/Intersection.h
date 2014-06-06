#ifndef MCDataProducts_Intersection_h
#define MCDataProducts_Intersection_h

//
// Information about the MC truth for hits in the tracker.
//

#include "toyExperiment/MCDataProducts/GenParticle.h"

#include "art/Persistency/Common/Ptr.h"

#include "CLHEP/Vector/ThreeVector.h"

#include <ostream>

namespace tex {

  class Intersection {

  public:

    Intersection();

#ifndef __GCCXML__
    Intersection( int                            shell,
		 art::Ptr<GenParticle> const&   genTrack,
                 CLHEP::Hep3Vector const&       position
               );

    int                          shell()    const { return _shell;    }
    art::Ptr<GenParticle> const& genTrack() const { return _genTrack; }
    CLHEP::Hep3Vector const&     position() const { return _position; }
#endif // __GCCXML__

    private:

    int                   _shell;
    art::Ptr<GenParticle> _genTrack;
    CLHEP::Hep3Vector     _position;

  };

#ifndef __GCCXML__
  std::ostream& operator<<(std::ostream& ost,
			   const Intersection& hit );
#endif // __GCCXML__

}

#endif /* MCDataProducts_Intersection_h */
