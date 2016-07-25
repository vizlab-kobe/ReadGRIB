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
#include <vector>
#include <kvs/FileFormatBase>
#include "Message.h"


namespace ReadGRIB
{

class GRIB1Data : public kvs::FileFormatBase
{
private:
    std::vector<grib::Message> m_messages;

public:

    GRIB1Data( const std::string& filename );

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const std::string& filename );

private:
    bool write( const std::string& ) { return false; }
};

} // end of namespace ReadGRIB
