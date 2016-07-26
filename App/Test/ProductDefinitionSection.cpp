#include "ProductDefinitionSection.h"
#include <kvs/ValueArray>
#include <kvs/Type>
#include <map>


namespace ReadGRIB
{

namespace grib
{

ProductDefinitionSection::ProductDefinitionSection()
{
}

void ProductDefinitionSection::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Length : " << m_length << std::endl;
    os << indent << "Parameter table version number : " << m_version << std::endl;
    os << indent << "Originating center ID : " << m_center_id << std::endl;
    os << indent << "Generating process ID : " << m_process_id << std::endl;
    os << indent << "Grid ID : " << m_grid_id << std::endl;
    os << indent << "Indicator of parameter and units : " << m_parameter_id << std::endl;
    os << indent << "Indicator of type of layer/level : " << m_layer_id << std::endl;
    os << indent << "Layer value : " << m_layer_value << std::endl;
    os << indent << "Layer value 1 : " << m_layer_value_1 << std::endl;
    os << indent << "Layer value 2 : " << m_layer_value_2 << std::endl;
    os << indent << "Year : " << m_year << std::endl;
    os << indent << "Month : " << m_month << std::endl;
    os << indent << "Day : " << m_day << std::endl;
    os << indent << "Hour : " << m_hour << std::endl;
    os << indent << "Minute : " << m_minute << std::endl;
    os << indent << "Forecast time unit : " << m_time_unit << std::endl;
    os << indent << "Period of time P1 : " << m_time_period_1 << std::endl;
    os << indent << "Period of time P2 : " << m_time_period_2 << std::endl;
    os << indent << "Time range indicator : " << m_time_range_indicator << std::endl;
    os << indent << "Number included in average : " << m_average << std::endl;
    os << indent << "Number missing in averages or accumulations : " << m_missing << std::endl;
    os << indent << "Century of year : " << m_century << std::endl;
    os << indent << "Sub-center ID : " << m_sub_center_id << std::endl;
    os << indent << "Decimal scale factor D : " << m_scale_factor << std::endl;
}

bool ProductDefinitionSection::read( std::ifstream& ifs )
{
    const size_t section_size = peek( ifs, 3 );
    kvs::ValueArray<kvs::UInt8> buffer = load( ifs, section_size );
    if ( ifs.fail() )
    {
        kvsMessageError( "Failed to read the product definition section." );
        return false;
    }

    m_length = pack( buffer[0], buffer[1], buffer[2] );
    m_version = pack( buffer[3] );
    m_center_id = pack( buffer[4] );
    m_process_id = pack( buffer[5] );
    m_grid_id = pack( buffer[6] );
    m_parameter_id = pack( buffer[8] );
    m_layer_id = pack( buffer[9] );
    m_layer_value = pack( buffer[10], buffer[11] );
    m_layer_value_1 = pack( buffer[10] );
    m_layer_value_2 = pack( buffer[11] );
    m_year = pack( buffer[12] );
    m_month = pack( buffer[13] );
    m_day = pack( buffer[14] );
    m_hour = pack( buffer[15] );
    m_minute = pack( buffer[16] );
    m_time_unit = pack( buffer[17] );
    m_time_period_1 = pack( buffer[18] );
    m_time_period_2 = pack( buffer[19] );
    m_time_range_indicator = pack( buffer[20] );
    m_average = pack( buffer[21], buffer[22] );
    m_missing = pack( buffer[23] );
    m_century = pack( buffer[24] );
    m_sub_center_id = pack( buffer[25] );;
    m_scale_factor = pack( buffer[26], buffer[27] );
    m_has_gds = ( ( buffer[7] & 128 ) != 0 );
    m_has_bms = ( ( buffer[7] &  64 ) != 0 );

    return true;
}

} // end of namespace grib

} // end of namespace ReadGRIB
