#include "BinaryDataSection.h"
#include <kvs/ValueArray>
#include <kvs/Type>


namespace
{

float IBM2Float( const kvs::UInt8* n )
{
    long int mant = ( n[1] << 16 ) + ( n[2] << 8 ) + n[3];
    if ( mant == 0 ) { return 0.0; }

    int positive = ( n[0] & 0x80 ) == 0;
    int power = (int)( n[0] & 0x7f ) - 64;
    unsigned int abspower = power > 0 ? power : -power;

    double exp = 16.0;
    double value = 1.0;
    while ( abspower )
    {
        if ( abspower & 1 ) { value *= exp; }
        exp = exp * exp;
        abspower >>= 1;
    }

    if ( power < 0 ) { value = 1.0 / value; }
    value = value * mant / 16777216.0;
    if ( positive == 0 ) { value = -value; }

//    return float(value);
    return value;
}

} // end of namespace


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
    os << indent << "Binary Scale factor E : " << m_scale_factor << std::endl;
    os << indent << "Reference value R : " << m_ref_value << std::endl;
    os << indent << "Number of bits : " << m_nbits << std::endl;
}

bool BinaryDataSection::read( std::ifstream& ifs )
{
    const size_t section_size = peek( ifs, 3 );
    kvs::ValueArray<kvs::UInt8> buffer = load( ifs, section_size );
    if ( ifs.fail() )
    {
        kvsMessageError( "Failed to read the binary data section." );
        return false;
    }

    m_length = pack( buffer[0], buffer[1], buffer[2] );
    m_scale_factor = pack( buffer[4], buffer[5] );
    m_ref_value = ::IBM2Float( buffer.data() + 6 );
    m_nbits = pack( buffer[10] );

    const bool is_float = ( ( buffer[3] & 32 ) == 0 );
    const bool has_more_flags = ( ( buffer[3] & 16 ) == 0 );
    const int unused_bits = int( buffer[3] & 15 );
    const int starting_point = 11 + has_more_flags * 3;
    const int nvalues = ( m_nbits == 0 ) ? 0 : ( ( m_length - starting_point ) * 8 - unused_bits ) / m_nbits;

    return true;
}

} // end of namespace grib

} // end of namespace ReadGRIB
