#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <kvs/Indent>
#include "Section.h"


namespace ReadGRIB
{

namespace grib
{

class EndSection : public Section
{
private:

    std::string m_code; ///< '7777'

public:

    EndSection();

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( std::ifstream& ifs );
};

} // end of namespace grib

} // end of namespace ReadGRIB
