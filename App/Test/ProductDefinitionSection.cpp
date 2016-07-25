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
    os << indent << "Parameter table version number : " << m_parameter_table_version << std::endl;
    os << indent << "Originating center ID : " << m_originating_center_id << std::endl;
    os << indent << "Generating process ID : " << m_generating_process_id << std::endl;
    os << indent << "Grid ID : " << m_grid_id << std::endl;
    os << indent << "Flag specifying the presence or absence : " << m_flag_presence << std::endl;
    os << indent << "Indicator of parameter : " << m_indicator_of_parameter << std::endl;
    os << indent << "Indicator of type of level : " << m_indicator_of_type_of_level << std::endl;
    os << indent << "Level : " << m_level << std::endl;
    os << indent << "Year : " << m_year << std::endl;
    os << indent << "Month : " << m_month << std::endl;
    os << indent << "Day : " << m_day << std::endl;
    os << indent << "Hour : " << m_hour << std::endl;
    os << indent << "Minute : " << m_minute << std::endl;
    os << indent << "Forecast time unit : " << m_forecast_time_unit << std::endl;
    os << indent << "Period of time 1 : " << m_period_of_time_1 << std::endl;
    os << indent << "Period of time 2 : " << m_period_of_time_2 << std::endl;
    os << indent << "Time range indicator : " << m_time_range_indicator << std::endl;
    os << indent << "Number included in average : " << m_number_average << std::endl;
    os << indent << "Number Missing from averages or accumulations : " << m_number_missing << std::endl;
    os << indent << "Century of Initial (Reference) time : " << m_century << std::endl;
    os << indent << "Sub-center ID : " << m_sub_center_id << std::endl;
    os << indent << "Decimal scale factor : " << m_decima_scale << std::endl;
}

bool ProductDefinitionSection::read( std::ifstream& ifs )
{
    const size_t section_size = peekOct( ifs );
    kvs::ValueArray<kvs::UInt8> buffer( section_size );
    ifs.read( (char*)buffer.data(), buffer.size() );
    if ( ifs.fail() )
    {
        kvsMessageError( "Failed to read the product definition section." );
        return false;
    }

    m_length = packOct( buffer[0], buffer[1], buffer[2] );
    m_parameter_table_version = packOct( buffer[3] );
    m_originating_center_id = packOct( buffer[4] );
    m_generating_process_id = packOct( buffer[5] );
    m_grid_id = packOct( buffer[6] );
    m_flag_presence = packOct( buffer[7] );
    m_indicator_of_parameter = packOct( buffer[8] );
    m_indicator_of_type_of_level = packOct( buffer[9] );
    m_level = packOct( buffer[10], buffer[11] );
    m_year = packOct( buffer[12] );
    m_month = packOct( buffer[13] );
    m_day = packOct( buffer[14] );
    m_hour = packOct( buffer[15] );
    m_minute = packOct( buffer[16] );
    m_forecast_time_unit = packOct( buffer[17] );
    m_period_of_time_1 = packOct( buffer[18] );
    m_period_of_time_2 = packOct( buffer[19] );
    m_time_range_indicator = packOct( buffer[20] );
    m_number_average = packOct( buffer[21], buffer[22] );
    m_number_missing = packOct( buffer[23] );
    m_century = packOct( buffer[24] );
    m_sub_center_id = packOct( buffer[25] );;
    m_decima_scale = packOct( buffer[26], buffer[27] );

    m_has_gds = ( ( buffer[7] & 128 ) != 0 );
    m_has_bms = ( ( buffer[7] &  64 ) != 0 );

    return true;
}

} // end of namespace grib

} // end of namespace ReadGRIB
