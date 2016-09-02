#include "GridDescriptionSection.h"
#include <kvs/ValueArray>
#include <kvs/Type>


namespace ReadGRIB
{

namespace grib
{

GridDescriptionSection::GridDescriptionSection()
{
}

void GridDescriptionSection::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Length : " << m_length << std::endl;
    os << indent << "Number of vertical coordinate : " << m_nv << std::endl;
    os << indent << "Location of vertical coordinate : " << m_pv << std::endl;
    os << indent << "Data representation type : " << m_grid_type << std::endl;
    if ( m_grid_type == 0 ) { m_grid.lat_lon.print( os, indent.nextIndent() ); }
}

bool GridDescriptionSection::read( std::ifstream& ifs )
{
    const size_t section_size = peek( ifs, 3 );
    kvs::ValueArray<kvs::UInt8> buffer = load( ifs, section_size );
    if ( ifs.fail() )
    {
        kvsMessageError( "Failed to read the grid description section." );
        return false;
    }

    m_length = pack( buffer[0], buffer[1], buffer[2] );
    m_nv = pack( buffer[3] );
    m_pv = pack( buffer[4] );
    m_grid_type = pack( buffer[5] );

    if ( m_grid_type == 0 ) // Lon/Lat grid
    {
        m_grid.lat_lon.read( buffer );
    }

    return true;
}

} // end of namespace grib

} // end of namespace ReadGRIB
