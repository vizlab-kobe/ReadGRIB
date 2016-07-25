#pragma once
#include <iostream>
#include <fstream>
#include <kvs/Indent>
#include "Section.h"


namespace ReadGRIB
{

namespace grib
{

class ProductDefinitionSection : public Section
{
private:

    int m_length; ///< Length of the product definition section
    int m_parameter_table_version; ///< Parameter table version number
    int m_originating_center_id; ///< Originating center ID
    int m_generating_process_id; ///< Generating process ID
    int m_grid_id; ///< Grid ID
    int m_flag_presence; ///< Flag specifying the presence or absence
    int m_indicator_of_parameter; ///< Indicator of parameter and units
    int m_indicator_of_type_of_level; ///< Indicator of type of level
    int m_level; ///< Height, pressure, etc. of the level or layer
    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    int m_minute;
    int m_forecast_time_unit;
    int m_period_of_time_1;
    int m_period_of_time_2;
    int m_time_range_indicator;
    int m_number_average;
    int m_number_missing;
    int m_century;
    int m_sub_center_id;
    int m_decima_scale;
    bool m_has_gds;
    bool m_has_bms;

public:

    ProductDefinitionSection();

    int length() const { return m_length; }
    int parameterTableVersion() const { return m_parameter_table_version; }
    int originatingCenterID() const { return m_originating_center_id; }
    int generatingProcessID() const { return m_generating_process_id; }
    int gridID() const { return m_grid_id; }
    bool hasGDS() const { return m_has_gds; }
    bool hasBMS() const { return m_has_bms; }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( std::ifstream& ifs );
};

} // end of namespace grib

} // end of namespace ReadGRIB
