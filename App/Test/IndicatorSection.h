#pragma once
#include <iostream>
#include <fstream>
#include <kvs/Indent>
#include "Section.h"


namespace ReadGRIB
{

namespace grib
{

class IndicatorSection : public Section
{
private:

    std::string m_code; ///< 'GRIB' coded CCITT-ITA No.5
    int m_total_length; ///< Total length of GRIB message
    int m_edition_number; ///< Edition number (currently 1)

public:

    IndicatorSection();

    const std::string& code() const { return m_code; }
    int totalLength() const { return m_total_length; }
    int editionNumber() const { return m_edition_number; }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( std::ifstream& ifs );
};

} // end of namespace grib

} // end of namespace ReadGRIB