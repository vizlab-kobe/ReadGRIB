/*****************************************************************************/
/**
 *  @file   GRIB1Data.h
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
#pragma once

#include <string>
#include <kvs/FileFormatBase>


namespace ReadGRIB
{

class GRIB1Data : public kvs::FileFormatBase
{
public:

    GRIB1Data( const std::string& filename )
    {
        this->read( filename );
    }

    bool read( const std::string& filename );

private:
    bool write( const std::string& ) { return false; }
};

} // end of namespace ReadGRIB
