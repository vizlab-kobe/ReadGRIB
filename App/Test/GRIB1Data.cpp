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

GRIB1Data::GRIB1Data( const std::string& filename )
{
    this->read( filename );
}

void GRIB1Data::print( std::ostream& os, const kvs::Indent& indent ) const
{
    for ( size_t i = 0; i < m_messages.size(); i++ )
    {
        os << indent << "Message (" << i << ")" << std::endl;
        m_messages[i].print( os, indent.nextIndent() );
    }
}

bool GRIB1Data::read( const std::string& filename )
{
    setFilename( filename );
    setSuccess( true );

    std::ifstream ifs( filename.c_str(), std::ios::binary | std::ios::in );
    if ( !ifs.is_open() )
    {
        kvsMessageError( "Cannot open %s.", filename.c_str() );
        ifs.close();
        setSuccess( false );
        return false;
    }

    while ( !ifs.eof() )
    {
        grib::Message message;
        if ( !message.read( ifs ) )
        {
            setSuccess( false );
            return false;
        }

        m_messages.push_back( message );
    }

    return true;
}

} // end of namespace ReadGRIB
