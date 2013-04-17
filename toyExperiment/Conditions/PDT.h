#ifndef Conditions_PDT_h
#define Conditions_PDT_h
//
// A mockup of a very minimal Particle Data Table class.
// HEPPDT uses the wrong set of units for use in this example.
// Fixing that would introduce needless complexity.
//

#include "toyExperiment/Conditions/ParticleInfo.h"

#include <map>
#include <string>
#include <ostream>

namespace tex {

  class PDT{

  public:

    PDT();

    void print( std::ostream& ) const;

    ParticleInfo const& getById( PDGCode::type ) const;

  private:

    typedef std::map<PDGCode::type,ParticleInfo> map_type;
    map_type _pdt;


  };

  inline std::ostream& operator<<(std::ostream& ost,
                                  const PDT& t ){
    t.print(ost);
    return ost;
  }



}  // namespace tex

#endif /* Conditions_PDT_h */
