//
// Draw two 2D views of the event.
//
// Notes
// 1) This example leaks the TApplication object at the end of the job.
//    This is deliberate; if I delete it at the end of the job it causes a core dump,
//    probably because some objects managed by ROOT presume that the TApplication
//    lives longer than they do.
//

#include "toyExperiment/Analyzers/PlotOrientation.h"
#include "toyExperiment/Geometry/Geometry.h"
#include "toyExperiment/MCDataProducts/IntersectionCollection.h"
#include "toyExperiment/MCDataProducts/GenParticleCollection.h"
#include "toyExperiment/PDT/PDT.h"
#include "toyExperiment/RecoDataProducts/Helix.h"
#include "toyExperiment/Utilities/eventIDToString.h"

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Services/Optional/TFileService.h"

#include "Rtypes.h"
#include "TApplication.h"
#include "TArc.h"
#include "TArrow.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TLine.h"
#include "TString.h"

#include <iostream>
#include <cmath>

// Anonymous namespace for helpers.
namespace {

  // A helper class to manage the TGraph objects and the information needed to create them.
  struct Helper{

    Helper(size_t n,
           int acolor,
           std::string const& opt,
           tex::GenParticle const* agen = 0):
      color(acolor), drawingOption(opt), gen(agen), xyp(), rzp(){
      x.reserve(n);
      y.reserve(n);
      z.reserve(n);
      r.reserve(n);
    }

    void addPoint( CLHEP::Hep3Vector const& p ){
      x.push_back(p.x());
      y.push_back(p.y());
      z.push_back(p.z());
      r.push_back(p.perp());
    }

    bool empty() const{
      return x.empty();
    }

    size_t size() const{
      return x.size();
    }

    CLHEP::Hep3Vector back() const{
      if ( x.empty() ){
        return CLHEP::Hep3Vector();
      }
      return CLHEP::Hep3Vector( x.back(), y.back(), z.back() );
    }

    TGraph* drawXY(){

      if ( empty() ) return xyp.get();

      xyp = std::unique_ptr<TGraph>(new TGraph(size(), &x.front(), &y.front() ) );
      xyp->SetMarkerColor(color);
      xyp->SetLineColor(color);
      xyp->SetMarkerStyle(kFullDotLarge);
      xyp->Draw(drawingOption.c_str());

      return xyp.get();
    }

    TGraph* drawRZ(){

      if ( empty() ) return rzp.get();

      rzp = std::unique_ptr<TGraph>(new TGraph(size(), &z.front(), &r.front() ));
      rzp->SetMarkerColor(color);
      rzp->SetLineColor(color);
      rzp->SetMarkerStyle(kFullDotLarge);
      rzp->Draw(drawingOption.c_str());

      return rzp.get();
    }

    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> z;
    std::vector<double> r;

    int color;
    std::string drawingOption;
    tex::GenParticle const* gen;

    std::unique_ptr<TGraph> xyp;
    std::unique_ptr<TGraph> rzp;
  };

}

namespace tex {

  class EventDisplay : public art::EDAnalyzer {

  public:

    explicit EventDisplay(fhicl::ParameterSet const& pset);

    void beginJob();
    void endJob();
    void analyze(const art::Event& event);

  private:

    art::InputTag   _gensTag;
    bool            _drawGenTracks;
    bool            _drawHits;
    bool            _prompt;
    bool            _multipage;
    std::string     _plotFileName;
    PlotOrientation _orientation;
    int             _maxDisplay;
    int             _verbosity;

    std::string     _plotFileBase;
    std::string     _plotFileType;

    art::ServiceHandle<art::TFileService> _tfs;
    art::ServiceHandle<Geometry>          _geom;
    art::ServiceHandle<PDT>               _pdt;
    TApplication*                         _application;
    TCanvas*                              _canvas;

    TH1F* _hFrame;
    int _displayCount;

    // Various in-class helper methods.
    void parsePlotFileName();

    int  selectColor( PDGCode::type id );

    void fillHits ( std::vector<art::Handle<IntersectionCollection>> const& handles,
                    Helper& h1, Helper& h2, Helper& h3);

    void fillTracks ( GenParticleCollection const& gens, std::vector<Helper>& h );
    void fillTrack  ( GenParticle const& gen, Helper& h );

    void print( TCanvas*, int );

  };

}

tex::EventDisplay::EventDisplay(fhicl::ParameterSet const& pset):
  art::EDAnalyzer(pset),
  _gensTag        ( pset.get<std::string>("genParticleTag") ),
  _drawGenTracks  ( pset.get<bool>       ("drawGenTracks",true) ),
  _drawHits       ( pset.get<bool>       ("drawHits",true) ),
  _prompt         ( pset.get<bool>       ("prompt",true) ),
  _multipage      ( pset.get<bool>       ("multipage",false) ),
  _plotFileName   ( pset.get<std::string>("plotFileName","") ),
  _orientation    ( pset.get<std::string>("orientation", "portrait" ) ),
  _maxDisplay     ( pset.get<int>        ("maxDisplay", 0  ) ),
  _verbosity      ( pset.get<int>        ("verbosity",  0  ) ),
  _plotFileBase(),
  _plotFileType(),
  _tfs( art::ServiceHandle<art::TFileService>() ),
  _geom(art::ServiceHandle<Geometry>()),
  _pdt(),
  _application(0),
  _displayCount(0){

  // Split the plot file name into a base and a type.
  parsePlotFileName();

}

void tex::EventDisplay::beginJob(){

  // If needed, create the ROOT interactive environment. See note 1.
  if ( !gApplication ){
    int    tmp_argc(0);
    char** tmp_argv(0);
    _application = new TApplication( "noapplication", &tmp_argc, tmp_argv );
  }

  int windowSizeShort(600);
  int windowSizeLong(1200);
  if ( _orientation == PlotOrientation::portrait ){
    _canvas = new TCanvas("canvas_Test","Event Display", windowSizeShort, windowSizeLong );
  } else {
    _canvas = new TCanvas("canvas_Test","Event Display", windowSizeLong, windowSizeShort );
  }
  _canvas->Modified();
  _canvas->Update();

  // Open a multipage plot file.
  if ( _multipage ){
    if ( _verbosity > 1 ){
      std::cout << "Opening multipage plot file: " << _plotFileName << std::endl;
    }
    _canvas->Print( std::string( _plotFileName + "[").c_str() );
  }

}

void tex::EventDisplay::endJob(){

  // Close multipage plot file.
  if ( _multipage ){
    if ( _verbosity > 1 ){
      std::cout << "Closing multipage plot file: " << _plotFileName << std::endl;
    }
    _canvas->Print( std::string( _plotFileName + "]").c_str() );
  }

}

void tex::EventDisplay::analyze(const art::Event& event ){

  if ( _displayCount > _maxDisplay ) return;
  int pageCount = _displayCount++;

  // Fetch the input data products.
  auto gens = event.getValidHandle<GenParticleCollection>(_gensTag);

  // There may be more than 1 of this type of data product.
  std::vector<art::Handle<IntersectionCollection>> hitsHandles;
  event.getManyByType(hitsHandles);

  // Guess at how much space to reserve inside the Helpers;
  // This computation will usually reserve a little too much but the wasted space
  // is small enough that this is OK.
  int nReserve = 0;
  for ( auto const& handle: hitsHandles ){
    nReserve += handle->size();
  }

  // Populate the helper objects describing the generated trajectories.
  std::vector<Helper> chargedTracks;
  fillTracks ( *gens, chargedTracks );

  // Populate the helper objects holding the hits.
  Helper h1(nReserve, kRed, "P"), h2(nReserve, kBlue, "P"), h3( nReserve, kGreen, "P");
  fillHits ( hitsHandles, h1, h2, h3 );

  Tracker const& tracker( _geom->tracker() ) ;

  // Size of the frames is set by the geometry's world size.
  std::vector<double> const& world = _geom->worldHalfLengths();

  // ROOT shape drawing objects.
  TArc arc;
  arc.SetFillStyle(0);
  TLine line;

  // Clear page.
  _canvas->cd(0);
  _canvas->Clear();

  // Split the canvas into two pads
  if ( _orientation == PlotOrientation::portrait ) {
    _canvas->Divide(1,2);
  } else{
    _canvas->Divide(2,1);
  }

  std::string eventID = eventIDToString( event.id() );

  // Draw first plot.
  _canvas->cd(1);

  // Draw the geometry.
  std::string titleXY = "( " + eventID +  ")  Y vs X;[mm];[mm]";
  _hFrame = gPad->DrawFrame( -world[0], -world[1], world[0], world[1], titleXY.c_str() );
  for ( auto const& shell : tracker.shells() ){
   arc.DrawArc( 0., 0., shell.radius() );
  }

  if ( _drawHits ) {
    h1.drawXY();
    h2.drawXY();
    h3.drawXY();
  }

  if ( _drawGenTracks ){
    for ( auto& track : chargedTracks ){
      track.drawXY();
    }
  }

  // Draw second plot.
  _canvas->cd(2);

  // Draw the geometry.
  std::string titleRZ = "( " + eventID +  ")  R vs Z;[mm];[mm]";
  _hFrame = gPad->DrawFrame( -world[2], 0., world[2], world[0], titleRZ.c_str() );
  for ( auto const& shell : tracker.shells() ){
    line.DrawLine( -shell.halfLength(), shell.radius(), shell.halfLength(), shell.radius() );
  }

  if ( _drawHits ){
    h1.drawRZ();
    h2.drawRZ();
    h3.drawRZ();
  }

  if ( _drawGenTracks ){
    for ( auto& track : chargedTracks ){
      track.drawRZ();
    }
  }

  // Flush contents to the screen.
  _canvas->Modified();
  _canvas->Update();

  // Print the canvas, if requested.
  print( _canvas, pageCount );

  // Wait for user input.
  if ( _prompt ) {
    std::cout << "Type any character and hit return to continue: ";
    char junk;
    std::cin >> junk;
    std::cout << junk << std::endl;
    if ( junk == 'q' || junk == 'Q' ){
      throw cet::exception("USERSHUTDOWN") << "User requested shutdown in EventDisplay module.\n";
    }
  }

} // end tex::EventDisplay::analyze

int tex::EventDisplay::selectColor( PDGCode::type id ){
  if ( id == PDGCode::K_plus  ) return kRed;
  if ( id == PDGCode::K_minus ) return kBlue;
  return kGreen;
}

void
tex::EventDisplay::fillHits ( std::vector<art::Handle<IntersectionCollection>> const& handles,
                                Helper& h1,
                                Helper& h2,
                                Helper& h3){

  for ( auto const& handle: handles ){
    for ( auto const& hit: *handle ){
      if ( hit.genTrack()->pdgId() == PDGCode::K_plus ){
        h1.addPoint( hit.position() );
      } else if ( hit.genTrack()->pdgId() == PDGCode::K_minus ){
        h2.addPoint( hit.position() );
      } else{
        h3.addPoint( hit.position() );
      }
    }
  }

}


void tex::EventDisplay::fillTracks ( GenParticleCollection const& gens , std::vector<Helper>& tracks ){

  tracks.reserve(gens.size());

  for ( auto const& gen: gens){

    // Skip neutral tracks
    if ( gen.status() != GenParticle::alive ) continue;

    int color = selectColor(gen.pdgId());
    tracks.push_back( Helper( 100, color, "L", &gen ) );

    fillTrack ( gen, tracks.back() );

  }

} // end tex::EventDisplay::fillTracks.

void  tex::EventDisplay::fillTrack( GenParticle const& gen, Helper& h ){

  double q = _pdt->getById(gen.pdgId()).charge();
  double bz(_geom->bz());

  Helix trk(gen.position(), gen.momentum().vect(), q, bz);

  // 3d path length to the end of the first outgoing arc.
  double smax = M_PI*trk.rho()/trk.sinTheta();

  // Add points along the trajectory.
  int nSteps(100);
  double ds = smax/nSteps;
  for ( int i=0; i<nSteps; ++i){
    double s = ds*i;
    CLHEP::Hep3Vector position = trk.position( s );
    if ( _geom->tracker().insideTracker( position ) ){
      h.addPoint( position );
    }
  }

}

// Split name of the plot file into its base and type components.
// Supply a default type if requested.
// Force a file type of .pdf if multipage is selected.
void tex::EventDisplay::parsePlotFileName(){

  if ( _plotFileName.empty() ) return;

  size_t dotPosition = _plotFileName.rfind('.');
  if ( dotPosition != std::string::npos ){
    _plotFileBase = _plotFileName.substr(0,dotPosition);
    _plotFileType = _plotFileName.substr(dotPosition);
  } else {
    _plotFileBase = _plotFileName;
    _plotFileType = ( _multipage ) ? ".pdf" : ".png";
  }

  if ( _multipage ) {
    if ( _plotFileType != ".pdf" ){
      std::cout << "Warning: multipage has been chosen and file type for the plot file is not .pdf\n"
                << "         Forcing file type to pdf."
                << std::endl;
      _plotFileType = ".pdf";
      _plotFileName = _plotFileBase + _plotFileType;
    }
  }

}

void tex::EventDisplay::print( TCanvas*, int count ){

  if ( _plotFileName.empty() ) return;

  if ( _multipage ){
    if ( _verbosity > 1 ){
      std::cout << "Printing canvas to multipage plot file: " << _plotFileName << std::endl;
    }
    _canvas->Print( _plotFileName.c_str() );
  } else{
    std::string version = std::to_string( count );
    std::string name = _plotFileBase;
    name += "_";
    name += version;
    name += _plotFileType;
    if ( _verbosity > 1 ){
      std::cout << "Printing canvas to plot file: " << name << std::endl;
    }
    _canvas->Print( name.c_str() );
  }
}

DEFINE_ART_MODULE(tex::EventDisplay)
