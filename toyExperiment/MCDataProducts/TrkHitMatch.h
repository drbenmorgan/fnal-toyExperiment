#ifndef MCDataProducts_TrkHitMatch_h
#define MCDataProducts_TrkHitMatch_h

//
// Relationship between simulated TrkHits and their MC truth.
//

#include "toyExperiment/RecoDataProducts/TrkHit.h"
#include "toyExperiment/MCDataProducts/Intersection.h"

#include "art/Persistency/Common/Assns.h"

namespace tex {

  typedef art::Assns<TrkHit,Intersection> TrkHitMatch;

}

#endif /* MCDataProducts_TrkHitMatch_h */
