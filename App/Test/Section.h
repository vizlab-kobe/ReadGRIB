#pragma once
#include <string>
#include <kvs/Type>


namespace ReadGRIB
{

namespace grib
{

class Section
{
protected:

    int packOct( kvs::UInt8 a )
    {
        return ( a & 0x80 ) ? this->pack_as_int(a) : this->pack_as_uint(a);
    }

    int packOct( kvs::UInt8 a, kvs::UInt8 b )
    {
        return ( a & 0x80 ) ? this->pack_as_int(a,b) : this->pack_as_uint(a,b);
    }

    int packOct( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c )
    {
        return ( a & 0x80 ) ? this->pack_as_int(a,b,c) : this->pack_as_uint(a,b,c);
    }

    int packOct( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c, kvs::UInt8 d )
    {
        return ( a & 0x80 ) ? this->pack_as_int(a,b,c,d) : this->pack_as_uint(a,b,c,d);
    }

    std::string packString( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c, kvs::UInt8 d )
    {
        return this->pack_as_string( a, b, c, d );
    }

    int peekOct( std::ifstream& ifs )
    {
        const char a = ifs.get();
        const char b = ifs.get();
        const char c = ifs.get();
        ifs.seekg( -3, std::ios_base::cur );
        return this->packOct( a, b, c );
    }

private:

    int pack_as_int( kvs::UInt8 a )
    {
        return ( 1 - (int)( (unsigned)( a & 0x80 ) >> 6 ) ) * (int)( a & 0x7f );
    }

    int pack_as_int( kvs::UInt8 a, kvs::UInt8 b )
    {
        return ( 1 - (int)( (unsigned)( a & 0x80 ) >> 6 ) ) * (int)( ( ( a & 0x7f ) << 8 ) + b );
    }

    int pack_as_int( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c )
    {
        return ( 1 - (int)( (unsigned)( a & 0x80 ) >> 6 ) ) * (int)( ( ( a & 127 ) << 16 ) + ( b << 8 ) + c );
    }

    int pack_as_int( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c, kvs::UInt8 d )
    {
        return ( 1 - (int)( (unsigned)( a & 0x80 ) >> 6 ) ) * (int)( ( ( a & 0x7f ) << 24 ) + ( b << 16 ) + ( c << 8 ) + d );
    }

    int pack_as_uint( kvs::UInt8 a )
    {
        return int( a );
    }

    int pack_as_uint( kvs::UInt8 a, kvs::UInt8 b )
    {
        return int( ( a << 8 ) + b );
    }

    int pack_as_uint( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c )
    {
        return int( ( a << 16 ) + ( b << 8 ) + c );
    }

    int pack_as_uint( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c, kvs::UInt8 d )
    {
        return int( ( a << 24 ) + ( b << 16 ) + ( c << 8 ) + d );
    }

    std::string pack_as_string( kvs::UInt8 a )
    {
        return std::string(1,a);
    }

    std::string pack_as_string( kvs::UInt8 a, kvs::UInt8 b )
    {
        return std::string(1,a) + std::string(1,b);
    }

    std::string pack_as_string( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c )
    {
        return std::string(1,a) + std::string(1,b) + std::string(1,c);
    }

    std::string pack_as_string( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c, kvs::UInt8 d )
    {
        return std::string(1,a) + std::string(1,b) + std::string(1,c) + std::string(1,d);
    }
};

} // end of namespace grib

} // end of namespace ReadGRIB
