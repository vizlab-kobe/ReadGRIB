#pragma once
#include <iostream>
#include <fstream>
#include <kvs/Indent>
#include "Section.h"


namespace ReadGRIB
{

namespace grib
{

class GridDescriptionSection : public Section
{
private:

    int m_length; ///< Length of the grid description section
    int m_data_type; ///< Data representation type

public:

    GridDescriptionSection();

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( std::ifstream& ifs );
};

} // end of namespace grib

} // end of namespace ReadGRIB
