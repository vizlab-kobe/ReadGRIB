#pragma once
#include <iostream>
#include <fstream>
#include <kvs/Indent>
#include <kvs/AnyValueArray>
#include "Section.h"


namespace ReadGRIB
{

namespace grib
{

class BinaryDataSection : public Section
{
private:

    int m_length; ///< Length of the binary data section (octet 1-3)
    int m_scale_factor; ///< binary scale factor E (octet 5-6)
    float m_ref_value; ///< reference value R (octet 7-10)
    int m_nbits; ///< number of bits into which datum point is packed (octet 11)
    kvs::AnyValueArray m_data;

public:

    BinaryDataSection();

    int length() const { return m_length; }
    int scaleFactor() const { return m_scale_factor; }
    float refValue() const { return m_ref_value; }
    int numberOfBits() const { return m_nbits; }
    const kvs::AnyValueArray& data() const { return m_data; }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( std::ifstream& ifs );
};

} // end of namespace grib

} // end of namespace ReadGRIB
