//
// Build a dictionary.
//

#include "toyExperiment/MCDataProducts/GenParticleCollection.h"
#include "toyExperiment/MCDataProducts/IntersectionCollection.h"
#include "toyExperiment/MCDataProducts/MCRunSummary.h"
#include "toyExperiment/MCDataProducts/TrkHitMatch.h"

#include "art/Persistency/Common/Wrapper.h"

#include <vector>
#include <string>

template class art::PtrVector<tex::GenParticle>;


template class art::Wrapper<tex::GenParticleCollection>;
template class art::Wrapper<tex::IntersectionCollection>;
template class art::Wrapper<tex::MCRunSummary>;

namespace {
  struct Instantiations {
    tex::TrkHitMatch junk00;
  };
}

template class art::Wrapper<tex::TrkHitMatch >;

