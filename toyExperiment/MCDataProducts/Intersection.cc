//
// Information about the MC truth for hits in the tracker.
//

#include "toyExperiment/MCDataProducts/Intersection.h"

tex::Intersection::Intersection():
  _shell(-1),
  _genTrack(),
  _position()
{
}

tex::Intersection::Intersection( int                            shell,
				 art::Ptr<GenParticle> const&   genTrack,
				 CLHEP::Hep3Vector const&       position
				 ):
  _shell(shell),
  _genTrack(genTrack),
  _position(position)
{
}
