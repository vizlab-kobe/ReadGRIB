#include "EndSection.h"
#include <kvs/ValueArray>
#include <kvs/Type>


namespace ReadGRIB
{

namespace grib
{

EndSection::EndSection()
{
}

void EndSection::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Code : " << m_code << std::endl;
}

bool EndSection::read( std::ifstream& ifs )
{
    const size_t section_size = 4;
    kvs::ValueArray<kvs::UInt8> buffer( section_size );
    ifs.read( (char*)buffer.data(), buffer.size() );
    if ( ifs.fail() )
    {
        kvsMessageError( "Failed to read the end section." );
        return false;
    }

    m_code = packString( buffer[0], buffer[1], buffer[2], buffer[3] );
    if ( m_code != "7777" )
    {
        kvsMessageError( "Cannot find '7777' used to denote the end of GRIB message." );
        return false;
    }

    return true;
}

} // end of namespace grib

} // end of namespace ReadGRIB
