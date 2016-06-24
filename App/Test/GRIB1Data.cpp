/*****************************************************************************/
/**
 *  @file   GRIB1Data.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "GRIB1Data.h"
#include <cstdio>
#include <kvs/ValueArray>
#include <kvs/Message>


namespace ReadGRIB
{

bool GRIB1Data::read( const std::string& filename )
{
    setFilename( filename );
    setSuccess( false );

    FILE* fp = fopen( filename.c_str(), "r" );
    if ( !fp )
    {
        kvsMessageError( "Cannot open %s.", filename.c_str() );
        return false;
    }

    // Indicator Section
    {
        std::string code;
        {
            size_t size = 4;
            kvs::ValueArray<char> values( size );
            if ( fread( values.data(), sizeof(char), size, fp ) < size )
            {
                kvsMessageError( "Failed to read the value." );
                return false;
            }

            code = std::string( values.data(), values.size() );
        }
        std::cout << "code: " << code << std::endl;

        int total_length = 0;
        {
            size_t size = 3;
            kvs::ValueArray<unsigned char> values( size );
            if ( fread( values.data(), sizeof(unsigned char), size, fp ) < size )
            {
                kvsMessageError( "Failed to read the value." );
                return false;
            }
            total_length = int( ( values[0] << 16 ) + ( values[1] << 8 ) + values[2] );
        }
        std::cout << "total length: " << total_length << std::endl;

        int edition_number = 0;
        {
            size_t size = 1;
            kvs::ValueArray<unsigned char> values( size );
            if ( fread( values.data(), sizeof(unsigned char), size, fp ) < size )
            {
                kvsMessageError( "Failed to read the value." );
                return false;
            }

            edition_number = int( values[0] );
        }
        std::cout << "edition number: " << edition_number << std::endl;
    }

    // Product Definition Section (PDS)
    {
        int length = 0;
        {
            size_t size = 3;
            kvs::ValueArray<unsigned char> values( size );
            if ( fread( values.data(), sizeof(unsigned char), size, fp ) < size )
            {
                kvsMessageError( "Failed to read the value." );
                return false;
            }
            length = int( ( values[0] << 16 ) + ( values[1] << 8 ) + values[2] );
        }
        std::cout << "length of PDS: " << length << std::endl;

        int version = 0;
        {
            size_t size = 1;
            kvs::ValueArray<unsigned char> values( size );
            if ( fread( values.data(), sizeof(unsigned char), size, fp ) < size )
            {
                kvsMessageError( "Failed to read the value." );
                return false;
            }
            version = int( values[0] );
        }
        std::cout << "parameter table version: " << version << std::endl;
    }

    fclose( fp );

    return false;
}

} // end of namespace ReadGRIB
