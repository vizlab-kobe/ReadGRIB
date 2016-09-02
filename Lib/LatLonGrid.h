#pragma once
#include <iostream>
#include <fstream>
#include <kvs/Indent>
#include <kvs/ValueArray>
#include "Section.h"


namespace ReadGRIB
{

namespace grib
{

/*===========================================================================*/
/**
 *  @brief  Latitude/Longitude grid class
 */
/*===========================================================================*/
class LatLonGrid : public Section
{
private:

    int m_ni; ///< number of points along a latitude circle (octet 7-8)
    int m_nj; ///< number of points along a longitude meridian (octet 9-10)
    int m_lat1; ///< latitude of first grid point in millidegrees (octet 11-13)
    int m_lon1; ///< longitude of first grid point in millidegrees (octet 14-16)
    int m_lat2; ///< latitude of last grid point in millidegrees (octet 18-20)
    int m_lon2; ///< longitude of last grid point in millidegrees (octet 21-23)
    int m_di; ///< longitudinal direction increment in millidegrees (octet 24-25)
    int m_dj; ///< latitudinal direction increment in millidegrees (octet 26-27)

public:

    int ni() const { return m_ni; }
    int nj() const { return m_nj; }
    int lat1() const { return m_lat1; }
    int lon1() const { return m_lon1; }
    int lat2() const { return m_lat2; }
    int lon2() const { return m_lon2; }
    int di() const { return m_di; }
    int dj() const { return m_dj; }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    void read( kvs::ValueArray<kvs::UInt8>& buffer );
};

} // end of namespace grib

} // end of namespace ReadGRIB
