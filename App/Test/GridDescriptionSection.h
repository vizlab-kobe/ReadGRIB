#pragma once
#include <iostream>
#include <fstream>
#include <kvs/Indent>
#include "Section.h"
#include "LatLonGrid.h"


namespace ReadGRIB
{

namespace grib
{

class GridDescriptionSection : public Section
{
public:

    union Grid
    {
        LatLonGrid lat_lon; ///< latitude/longitude grid
    };

private:

    int m_length; ///< length of grid description section (octet 1-3)
    int m_nv; ///< number of vertical coordinate (octet 4)
    int m_pv; ///< location of vertical coordinate (octet 5)
    int m_grid_type; ///< data representation type (octet 6)
    Grid m_grid; ///< grid information (octet 7-32,42,44)

public:

    GridDescriptionSection();

    int length() const { return m_length; }
    int nv() const { return m_nv; }
    int pv() const { return m_pv; }
    int gridType() const { return m_grid_type; }
    const LatLonGrid& latLonGrid() const { return m_grid.lat_lon; }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( std::ifstream& ifs );
};

} // end of namespace grib

} // end of namespace ReadGRIB
