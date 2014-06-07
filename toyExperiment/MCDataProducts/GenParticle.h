#ifndef MCDataProducts_GenParticle_h
#define MCDataProducts_GenParticle_h

//
// A minimal class to hold information about generated particles.
//

#include "toyExperiment/DataProducts/PDGCode.h"

#include "art/Persistency/Common/Ptr.h"
#include "art/Persistency/Common/PtrVector.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ThreeVector.h"

#include <ostream>

namespace tex {

  class GenParticle {

  public:

    enum status_type { undefined=-1, alive, decayed};

    typedef art::PtrVector<GenParticle> children_type;

    GenParticle();

#ifndef __GCCXML__
    GenParticle( PDGCode::type                  pdgId,
		 art::Ptr<GenParticle> const&   parent,
                 CLHEP::Hep3Vector const&       position,
                 CLHEP::HepLorentzVector const& momentum,
                 status_type                    status);

    PDGCode::type                  pdgId()           const { return  _pdgId;              }
    bool                           hasParent()       const { return  _parent.isNonnull(); }
    bool                           hasChildren()     const { return !_children.empty();   }
    art::Ptr<GenParticle> const&   parent()          const { return  _parent;             }
    children_type const&           children()        const { return  _children;           }
    art::Ptr<GenParticle> const&   child( size_t i ) const { return  _children.at(i);     }
    CLHEP::Hep3Vector const&       position()        const { return  _position;           }
    CLHEP::HepLorentzVector const& momentum()        const { return  _momentum;           }
    status_type                    status()          const { return  _status;             }

    void addChild( art::Ptr<GenParticle> const& child );

    // There is source in art::PtrVector that should be protected from gccxml trying to instantiate
    // it.  Until that is fixed, we need to provide a an operator< so or else the dictionary
    // generation fails ...  So we provide a bogus version here. This is never actually used but,if
    // gccxml cannot find the method, it quits.
    bool operator<( GenParticle const&) const{
      return true;
    }

#endif  // __GCCXML__

  private:

    // PDG particle ID code.
    PDGCode::type _pdgId;

    // Ancestry navigation.
    art::Ptr<GenParticle> _parent;
    children_type         _children;

    // Position, momentum at creation.
    CLHEP::Hep3Vector       _position;
    CLHEP::HepLorentzVector _momentum;

    status_type _status;

  };

#ifndef __GCCXML__
  std::ostream& operator<<(std::ostream& ost,
			   const tex::GenParticle& genp );
#endif  // __GCCXML__

}

#endif /* MCDataProducts_GenParticle_h */
