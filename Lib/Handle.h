#pragma once
#include "GRIB.h"
#include <kvs/ValueArray>


namespace ReadGRIB
{

namespace grib
{

class Handle
{
private:
    grib_handle* m_handle;
    int m_error;

public:
    Handle( FILE* fp );
    ~Handle();

    bool hasError() const { return m_error != GRIB_SUCCESS; }
    bool isValid() const { return m_handle != NULL; }

    bool create( FILE* fp );
    bool destroy();

    size_t getOffset( const std::string& key );
    size_t getSize( const std::string& key );

    template <typename T>
    T getValue( const std::string& ) { return T(0); }

    template <typename T>
    kvs::ValueArray<T> getValueArray( const std::string& ) { return kvs::ValueArray<T>(); }
};

template <> long Handle::getValue<long>( const std::string& key );
template <> double Handle::getValue<double>( const std::string& key );
template <> kvs::ValueArray<long> Handle::getValueArray<long>( const std::string& key );
template <> kvs::ValueArray<double> Handle::getValueArray<double>( const std::string& key );

} // end of namespace glib

} // end of namespace ReadGRIB
