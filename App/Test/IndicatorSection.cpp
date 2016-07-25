#include "IndicatorSection.h"
#include <kvs/ValueArray>
#include <kvs/Type>


namespace ReadGRIB
{

namespace grib
{

IndicatorSection::IndicatorSection()
{

}

void IndicatorSection::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Code : " << m_code << std::endl;
    os << indent << "Total length of GRIB message : " << m_total_length << std::endl;
    os << indent << "Edition number : " << m_edition_number << std::endl;
}

bool IndicatorSection::read( std::ifstream& ifs )
{
    const size_t section_size = 8;
    kvs::ValueArray<kvs::UInt8> buffer( section_size );
    ifs.read( (char*)buffer.data(), buffer.size() );
    if ( ifs.fail() )
    {
        kvsMessageError( "Failed to read the indicator section." );
        return false;
    }

    m_code = packString( buffer[0], buffer[1], buffer[2], buffer[3] );
    m_total_length = packOct( buffer[4], buffer[5], buffer[6] );
    m_edition_number = packOct( buffer[7] );

    return true;
}

} // end of namespace grib

} // end of namespace ReadGRIB
