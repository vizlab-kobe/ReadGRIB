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

    int m_length; ///< length of the product definition section (octet 1-3)
    int m_version; ///< parameter table version (octet 4)
    int m_center_id; ///< originating center ID (octet 5)
    int m_process_id; ///< generating process ID (octet 6)
    int m_grid_id; ///< grid ID (octet 7)
    int m_parameter_id; ///< indicator of parameter and units (octet 9)
    int m_layer_id; ///< indicator of type of layer/level (octet 10)
    int m_layer_value; ///< layer/level value (octet 11 + octet 12)
    int m_layer_value_1; ///< layer value 1 (octet 11)
    int m_layer_value_2; ///< layer value 2 (octet 12)
    int m_year; ///< year of century (octet 13)
    int m_month; ///< month of year (octet 14)
    int m_day; ///< day of month (octet 15)
    int m_hour; ///< hour of day (octet 16)
    int m_minute; ///< minute of hour (octet 17)
    int m_time_unit; ///< forecast time unit (octet 18)
    int m_time_period_1; ///< period of time P1 (octet 19)
    int m_time_period_2; ///< period of time P2 (octet 20)
    int m_time_range_indicator; ///< time range indicator (octet 21)
    int m_average; ///< number included in average (octet 22-23)
    int m_missing; ///< number missing in averages or accumulations (octet 24)
    int m_century; ///< century of year (octet 25)
    int m_sub_center_id; ///< identification of sub-center (octet 26)
    int m_scale_factor; ///< decimal scale factor D (octet 27-28)
    bool m_has_gds; ///< flag for GDS presence
    bool m_has_bms; ///< flag for BMS presence

public:

    ProductDefinitionSection();

    int length() const { return m_length; }
    int version() const { return m_version; }
    int centerID() const { return m_center_id; }
    int processID() const { return m_process_id; }
    int gridID() const { return m_grid_id; }
    int parameterID() const { return m_parameter_id; }
    int layerID() const { return m_layer_id; }
    int layerValue() const { return m_layer_value; }
    int layerValue1() const { return m_layer_value_1; }
    int layerValue2() const { return m_layer_value_2; }
    int year() const { return m_year; }
    int month() const { return m_month; }
    int day() const { return m_day; }
    int hour() const { return m_hour; }
    int minute() const { return m_minute; }
    int timeUnit() const { return m_time_unit; }
    int timePeriod1() const { return m_time_period_1; }
    int timePeriod2() const { return m_time_period_2; }
    int timeRangeIndicator() const { return m_time_range_indicator; }
    int average() const { return m_average; }
    int missing() const { return m_missing; }
    int century() const { return m_century; }
    int subCenterID() const { return m_sub_center_id; }
    int scaleFactor() const { return m_scale_factor; }
    bool hasGDS() const { return m_has_gds; }
    bool hasBMS() const { return m_has_bms; }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( std::ifstream& ifs );
};

} // end of namespace grib

} // end of namespace ReadGRIB
