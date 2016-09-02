#include <kvs/Math>
#include "Message.h"
#include "GRIB.h"


namespace ReadGRIB
{

namespace grib
{

void Message::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Number of points along a latitude circle (Ni) : " << m_ni << std::endl;
    os << indent << "Number of points along a longitude meridian (Nj) : " << m_nj << std::endl;
    os << indent << "Indicator of parameter and unit : " << m_parameter_id << std::endl;
    os << indent << "Year : " << m_date.year() << std::endl;
    os << indent << "Month : " << m_date.month() << std::endl;
    os << indent << "Day : " << m_date.day() << std::endl;
    os << indent << "Hour : " << m_time.hour() << std::endl;
    os << indent << "Minute : " << m_time.minute() << std::endl;
    os << indent << "Min. value : " << m_min_value << std::endl;
    os << indent << "Max. value : " << m_max_value << std::endl;
    os << indent << "Ave. value : " << m_average_value << std::endl;

    if ( m_values.size() > 0 )
    {
        double min_value = m_values[0];
        double max_value = m_values[0];
        double average_value = 0.0;
        for ( size_t i = 0; i < m_values.size(); i++ )
        {
            average_value += m_values[i];
            min_value = kvs::Math::Min( min_value, m_values[i] );
            max_value = kvs::Math::Max( max_value, m_values[i] );
        }
        average_value /= m_values.size();

        os << indent << "Min. value (actual) : " << min_value << std::endl;
        os << indent << "Max. value (actual) : " << max_value << std::endl;
        os << indent << "Ave. value (actual) : " << average_value << std::endl;
    }
}

bool Message::read( FILE* fp )
{
    if ( !this->parse( fp ) ) { return false; }
    return this->load();
}

bool Message::parse( FILE* fp )
{
    m_handle = kvs::SharedPointer<Handle>( new Handle(fp) );
    if ( !m_handle->isValid() ) { return false; }

    m_ni = static_cast<int>( m_handle->getValue<long>("Ni") );
    m_nj = static_cast<int>( m_handle->getValue<long>("Nj") );
    m_parameter_id = static_cast<int>( m_handle->getValue<long>("indicatorOfParameter") );

    int year = static_cast<int>( m_handle->getValue<long>("year") );
    int month = static_cast<int>( m_handle->getValue<long>("month") );
    int day = static_cast<int>( m_handle->getValue<long>("day") );
    m_date = kvs::Date( year, month, day );

    int hour = static_cast<int>( m_handle->getValue<long>("hour") );
    int minute = static_cast<int>( m_handle->getValue<long>("minute") );
    m_time = kvs::Time( hour, minute, 0 );

    m_min_value = m_handle->getValue<double>("min");
    m_max_value = m_handle->getValue<double>("max");
    m_average_value = m_handle->getValue<double>("average");

    return true;
}

bool Message::load()
{
    if ( !m_handle->isValid() ) { return false; }

    m_values = m_handle->getValueArray<double>("values");
    return true;
}

} // end of namespace grib

} // end of namespace ReadGRIB
