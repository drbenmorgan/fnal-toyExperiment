#ifndef Analyzers_WaitFor_h
#define Analyzers_WaitFor_h
//
// Tell the event display where to look for authorization to
// continue to the event, either input from the keyboard
// or from the mouse.
//

#include "toyExperiment/DataProducts/EnumToStringSparse.h"

namespace tex {

  class WaitForDetail{
  public:

    enum enum_type { unknown=-1, keyboard, mouse };

    static std::string const& typeName();

    static std::map<enum_type,std::string> const& names();

  };

  typedef EnumToStringSparse<WaitForDetail> WaitFor;
}

#endif
