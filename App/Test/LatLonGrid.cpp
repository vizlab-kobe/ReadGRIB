#include "LatLonGrid.h"


namespace ReadGRIB
{

namespace grib
{

void LatLonGrid::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Number of points along a latitude circle : " << m_ni << std::endl;
    os << indent << "Number of points along a longitude meridian : " << m_nj << std::endl;
    os << indent << "Latitude of first grid point : " << m_lat1 << std::endl;
    os << indent << "Longitude of first grid point : " << m_lon1 << std::endl;
    os << indent << "Latitude of last grid point : " << m_lat2 << std::endl;
    os << indent << "Longitude of last grid point : " << m_lon2 << std::endl;
    os << indent << "Longitudinal direction increment : " << m_di << std::endl;
    os << indent << "Latitudinal direction increment : " << m_dj << std::endl;
}

void LatLonGrid::read( kvs::ValueArray<kvs::UInt8>& buffer )
{
    m_ni = pack( buffer[6], buffer[7] );
    m_nj = pack( buffer[8], buffer[9] );
    m_lat1 = pack( buffer[10], buffer[11], buffer[12] );
    m_lon1 = pack( buffer[13], buffer[14], buffer[15] );
    m_lat2 = pack( buffer[17], buffer[18], buffer[19] );
    m_lon2 = pack( buffer[20], buffer[21], buffer[22] );
    m_di = ( buffer[16] & 128 ) ? pack( buffer[23], buffer[24] ) : 0;
    m_dj = ( buffer[16] & 128 ) ? pack( buffer[25], buffer[26] ) : 0;
}

} // end of namespace grib

} // end of namespace ReadGRIB
