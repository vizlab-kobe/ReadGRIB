/*****************************************************************************/
/**
 *  @file   GRIBData.h
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
/*----------------------------------------------------------------------------
 *
 * References:
 * [1] http://www.wmo.int/pages/prog/www/WDM/Guides/Guide-binary-2.html
 * [2] http://rda.ucar.edu/docs/formats/grib/gribdoc/
 * [3] http://weather.unisys.com/wxp/Appendices/Formats/GRIB.html
 * [4] http://www.seaspace.com/technical/protected/html/man1/expgrib.html
 *
 */
/*****************************************************************************/
#pragma once
#include <string>
#include <vector>
#include <kvs/FileFormatBase>
#include "Message.h"


namespace ReadGRIB
{

/*===========================================================================*/
/**
 *  @brief  GRIB (edition 1) data class
 */
/*===========================================================================*/
class GRIBData : public kvs::FileFormatBase
{
public:

    typedef grib::Message Message;
    typedef std::vector<Message> Messages;

private:
    Messages m_messages;

public:

    GRIBData( const std::string& filename );

    const Messages& messages() const { return m_messages; }
    const Message& message( const size_t index ) const { return m_messages[index]; }
    size_t numberOfMessages() const { return m_messages.size(); }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const std::string& filename );

private:
    bool write( const std::string& ) { return false; }
};

} // end of namespace ReadGRIB
