#include "IndicatorSection.h"
#include <kvs/ValueArray>
#include <kvs/Type>


namespace ReadGRIB
{

namespace grib
{

IndicatorSection::IndicatorSection():
    m_length( 8 )
{
}

void IndicatorSection::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Length : " << m_length << std::endl;
    os << indent << "Code : " << m_code << std::endl;
    os << indent << "Total length of GRIB message : " << m_total_length << std::endl;
    os << indent << "Edition number : " << m_edition_number << std::endl;
}

bool IndicatorSection::read( std::ifstream& ifs )
{
    const size_t section_size = m_length;
    kvs::ValueArray<kvs::UInt8> buffer = load( ifs, section_size );
    if ( ifs.fail() )
    {
        kvsMessageError( "Failed to read the indicator section." );
        return false;
    }

    m_code = std::string( reinterpret_cast<const char*>( buffer.data() ), 4 );
    if ( m_code != "GRIB" )
    {
        kvsMessageError( "Cannot find 'GRIB' used to denote the begin of GRIB message." );
        return false;
    }

    m_total_length = pack( buffer[4], buffer[5], buffer[6] );
    m_edition_number = pack( buffer[7] );

    return true;
}

} // end of namespace grib

} // end of namespace ReadGRIB
