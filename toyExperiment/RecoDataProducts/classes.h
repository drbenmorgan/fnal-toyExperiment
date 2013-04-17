//
// Build a dictionary.
//

#include "toyExperiment/RecoDataProducts/DetectorStatus.h"
#include "toyExperiment/RecoDataProducts/TrkHitCollection.h"
#include "toyExperiment/RecoDataProducts/RecoTrkCollection.h"
#include "toyExperiment/RecoDataProducts/FittedHelixDataCollection.h"

#include "art/Persistency/Common/Wrapper.h"

template class art::Ptr<tex::TrkHit>;
template class std::vector<art::Ptr<tex::TrkHit> >;

template class art::Wrapper<tex::DetectorStatus>;
template class art::Wrapper<tex::TrkHitCollection>;
template class art::Wrapper<tex::RecoTrkCollection>;
template class art::Wrapper<tex::FittedHelixDataCollection>;
