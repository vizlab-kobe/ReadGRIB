#pragma once
#include <string>
#include <kvs/Type>
#include <kvs/ValueArray>


namespace ReadGRIB
{

namespace grib
{

class Section
{
protected:

    int pack( kvs::UInt8 a )
    {
        return int( a );
    }

    int pack( kvs::UInt8 a, kvs::UInt8 b )
    {
        return ( a & 0x80 ) ? this->pack_int(a,b) : this->pack_uint(a,b);
    }

    int pack( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c )
    {
        return ( a & 0x80 ) ? this->pack_int(a,b,c) : this->pack_uint(a,b,c);
    }

    int pack( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c, kvs::UInt8 d )
    {
        return ( a & 0x80 ) ? this->pack_int(a,b,c,d) : this->pack_uint(a,b,c,d);
    }

    int peek( std::ifstream& ifs, size_t n )
    {
        kvs::ValueArray<kvs::UInt8> buffer = load( ifs, n );
        ifs.seekg( -n, std::ios_base::cur );
        kvs::UInt8* p = buffer.data();
        return ( *p & 0x80 ) ? this->pack_int( p, n ) : this->pack_uint( p, n );
    }

    kvs::ValueArray<kvs::UInt8> load( std::ifstream& ifs, size_t size )
    {
        kvs::ValueArray<kvs::UInt8> buffer( size );
        ifs.read( reinterpret_cast<char*>( buffer.data() ), buffer.size() );
        return buffer;
    }

private:

    int pack_int( kvs::UInt8 a, kvs::UInt8 b )
    {
        const int sign = ( 1 - (int)( (unsigned)( a & 0x80 ) >> 6 ) );
        return sign * (int)( ( ( a & 0x7f ) << 8 ) + b );
    }

    int pack_int( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c )
    {
        const int sign = ( 1 - (int)( (unsigned)( a & 0x80 ) >> 6 ) );
        return sign * (int)( ( ( a & 0x7f ) << 16 ) + ( b << 8 ) + c );
    }

    int pack_int( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c, kvs::UInt8 d )
    {
        const int sign = ( 1 - (int)( (unsigned)( a & 0x80 ) >> 6 ) );
        return sign * (int)( ( ( a & 0x7f ) << 24 ) + ( b << 16 ) + ( c << 8 ) + d );
    }

    int pack_int( kvs::UInt8* p, size_t n )
    {
        if ( n == 0 ) { return 0; }
        const int sign = 1 - (int)( (unsigned)( *p & 0x80 ) >> 6 );
        int i = *p++ & 127; while ( n-- > 1 ) { i = i * 256 + (int)(*p++); }
        return sign * i;
    }

    int pack_uint( kvs::UInt8 a, kvs::UInt8 b )
    {
        return int( ( a << 8 ) + b );
    }

    int pack_uint( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c )
    {
        return int( ( a << 16 ) + ( b << 8 ) + c );
    }

    int pack_uint( kvs::UInt8 a, kvs::UInt8 b, kvs::UInt8 c, kvs::UInt8 d )
    {
        return int( ( a << 24 ) + ( b << 16 ) + ( c << 8 ) + d );
    }

    int pack_uint( kvs::UInt8* p, size_t n )
    {
        if ( n == 0 ) { return 0; }
        int i = 0; while ( n-- > 0 ) { i = ( i << 8 ) + *p++; }
        return i;
    }
};

} // end of namespace grib

} // end of namespace ReadGRIB
