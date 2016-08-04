#ifndef RecoDataProducts_FittedHelixData_h
#define RecoDataProducts_FittedHelixData_h

//
// The persistent data for a fitted helix.
//


#include "toyExperiment/RecoDataProducts/Helix.h"
#include "toyExperiment/RecoDataProducts/TrkHit.h"

#include "art/Persistency/Common/Ptr.h"

#include "CLHEP/Matrix/SymMatrix.h"

#include <ostream>
#include <vector>

namespace tex {

  class FittedHelixData {

  public:

    // Genreflex still needs the space between > >.  C++11 does not.
    typedef std::vector<art::Ptr<TrkHit> >  hits_type;

    FittedHelixData();

#ifndef __GCCXML__
    FittedHelixData( Helix               const& helix,
                     CLHEP::HepSymMatrix const& cov,
                     hits_type           const& hits );

    Helix               const& helix() const { return helix_; }
    CLHEP::HepSymMatrix const& cov()   const { return cov_;   }
    hits_type           const& hits()  const { return hits_;  }

    art::Ptr<TrkHit>    const& hit ( size_t i ) const { return hits_.at(i); }
#endif  // __GCCXML__

  private:

    Helix               helix_;
    CLHEP::HepSymMatrix cov_;
    hits_type           hits_;

  };

#ifndef __GCCXML__
  std::ostream& operator<<(std::ostream& ost,
                           const tex::FittedHelixData& fit );
#endif  // __GCCXML__

}

#endif /* RecoDataProducts_FittedHelixData_h */
