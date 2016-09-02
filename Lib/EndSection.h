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

    int m_length; ///< length of the end section (4)
    std::string m_code; ///< '7777'

public:

    EndSection();

    const std::string& code() const { return m_code; }
    int length() const { return m_length; }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( std::ifstream& ifs );
};

} // end of namespace grib

} // end of namespace ReadGRIB
