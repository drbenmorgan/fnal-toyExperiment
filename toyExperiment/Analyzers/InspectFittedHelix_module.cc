//
//  Look at the contents of the FittedHelixDataCollection; make both printout and histograms.
//

#include "toyExperiment/RecoDataProducts/FittedHelixDataCollection.h"


#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Services/Optional/TFileService.h"

#include "TH1F.h"
#include "TNtuple.h"

#include "CLHEP/Units/SystemOfUnits.h"

#include <iostream>
#include <string>

namespace tex {

  class InspectFittedHelix : public art::EDAnalyzer {

  public:

    explicit InspectFittedHelix(fhicl::ParameterSet const& pset);

    void beginJob();
    void analyze(const art::Event& event);

  private:

    std::string _fitterModuleLabel;
    int         _maxPrint;

    art::ServiceHandle<art::TFileService> _tfs;

    int _printCount;
  };

}

tex::InspectFittedHelix::InspectFittedHelix(fhicl::ParameterSet const& pset):
  _fitterModuleLabel( pset.get<std::string>("fitterModuleLabel") ),
  _maxPrint( pset.get<int>("maxPrint",0) ),
  _tfs( art::ServiceHandle<art::TFileService>() ),
  _printCount(0){
}

void tex::InspectFittedHelix::beginJob(){
}

void tex::InspectFittedHelix::analyze(const art::Event& event){

  // Get the generated particles from the event.
  art::Handle<FittedHelixDataCollection> fitsHandle;
  event.getByLabel( _fitterModuleLabel, fitsHandle);
  FittedHelixDataCollection const& fits(*fitsHandle);

  // Printout, if requested.
  bool doPrint = ( ++_printCount < _maxPrint );
  if ( doPrint ) {
    std::cout << "\nNumber of FittedHelices in event "
              << event.id().event() << " is: "
              << fits.size()
              << std::endl;
  }

  for ( auto const& fit : fits ){
    if ( doPrint ) {
      std::cout << fit << std::endl;
    }
  }

}

DEFINE_ART_MODULE(tex::InspectFittedHelix)
