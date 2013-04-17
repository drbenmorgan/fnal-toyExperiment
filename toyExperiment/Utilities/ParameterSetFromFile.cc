//
//
// Read a .fcl file and form a parameter set object.
//

#include "toyExperiment/Utilities/ParameterSetFromFile.h"

#include "fhiclcpp/intermediate_table.h"
#include "fhiclcpp/parse.h"
#include "fhiclcpp/make_ParameterSet.h"

#include "cetlib/filepath_maker.h"

#include <iostream>
#include <iostream>

tex::ParameterSetFromFile::
ParameterSetFromFile( std::string const& fileName ):
  _fileName(fileName)
{

  cet::filepath_lookup policy("FHICL_FILE_PATH");

  fhicl::intermediate_table tbl;
  std::string in("test01.fcl");
  fhicl::parse_document(_fileName, policy, tbl);

  fhicl::make_ParameterSet(tbl, _pSet);

}


void
tex::ParameterSetFromFile::printKeys( std::ostream& out ) const {

  std::vector<std::string> const& keys = _pSet.get_keys();
  out << "\nParameter set read from file: " << _fileName << std::endl;
  out << "Number of keys: " << keys.size() << std::endl;
  for ( std::vector<std::string>::const_iterator i=keys.begin();
        i != keys.end(); ++i ){
    out << " " << i-keys.begin() << " " << *i << std::endl;
  }

}
