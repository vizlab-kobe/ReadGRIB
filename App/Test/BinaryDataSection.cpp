#include "BinaryDataSection.h"
#include <kvs/ValueArray>
#include <kvs/Type>


namespace ReadGRIB
{

namespace grib
{

BinaryDataSection::BinaryDataSection()
{
}

void BinaryDataSection::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Length : " << m_length << std::endl;
}

bool BinaryDataSection::read( std::ifstream& ifs )
{
    const size_t section_size = peekOct( ifs );
    kvs::ValueArray<kvs::UInt8> buffer( section_size );
    ifs.read( (char*)buffer.data(), buffer.size() );
    if ( ifs.fail() )
    {
        kvsMessageError( "Failed to read the binary data section." );
        return false;
    }

    m_length = packOct( buffer[0], buffer[1], buffer[2] );

    return true;
}

} // end of namespace grib

} // end of namespace ReadGRIB
