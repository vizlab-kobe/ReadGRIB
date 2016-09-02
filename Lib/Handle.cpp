#include "Handle.h"


namespace ReadGRIB
{

namespace grib
{

Handle::Handle( FILE* fp ): m_error( GRIB_SUCCESS )
{
    this->create( fp );
}

Handle::~Handle()
{
    this->destroy();
}

bool Handle::create( FILE* fp )
{
    m_handle = grib_handle_new_from_file( 0, fp, &m_error );
    return this->hasError();
}

bool Handle::destroy()
{
    m_error = grib_handle_delete( m_handle );
    return this->hasError();
}

size_t Handle::getOffset( const std::string& key )
{
    size_t offset = 0;
    m_error = grib_get_offset( m_handle, key.c_str(), &offset );
    return offset;
}

size_t Handle::getSize( const std::string& key )
{
    size_t size = 0;
    m_error = grib_get_size( m_handle, key.c_str(), &size );
    return size;
}

template <>
long Handle::getValue<long>( const std::string& key )
{
    long value = 0;
    m_error = grib_get_long( m_handle, key.c_str(), &value );
    return value;
}

template <>
double Handle::getValue<double>( const std::string& key )
{
    double value = 0;
    m_error = grib_get_double( m_handle, key.c_str(), &value );
    return value;
}

template <>
kvs::ValueArray<long> Handle::getValueArray<long>( const std::string& key )
{
    size_t size = this->getSize( key );
    kvs::ValueArray<long> values( size );
    m_error = grib_get_long_array( m_handle, key.c_str(), values.data(), &size );
    return values;
}

template <>
kvs::ValueArray<double> Handle::getValueArray<double>( const std::string& key )
{
    size_t size = this->getSize( key );
    kvs::ValueArray<double> values( size );
    m_error = grib_get_double_array( m_handle, key.c_str(), values.data(), &size );
    return values;
}

} // end of namespace grib

} // end of namespace ReadGRIB
