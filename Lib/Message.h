#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <kvs/Indent>
#include <kvs/SharedPointer>
#include <kvs/Date>
#include <kvs/Time>
#include <kvs/ValueArray>
#include "GRIB.h"
#include "Handle.h"


namespace grib
{

class Message
{
private:
    kvs::SharedPointer<Handle> m_handle;
    int m_ni;
    int m_nj;
    int m_parameter_id;
    kvs::Date m_date;
    kvs::Time m_time;
    double m_min_value;
    double m_max_value;
    double m_average_value;
    kvs::ValueArray<double> m_values;

public:
    Message(){}

    bool hasError() const { return m_handle->hasError(); }
    bool isValid() const { return m_handle->isValid(); }

    int ni() const { return m_ni; }
    int nj() const { return m_nj; }
    int parameterID() const { return m_parameter_id; }
    const kvs::Date& date() const { return m_date; }
    const kvs::Time& time() const { return m_time; }
    double minValue() const { return m_min_value; }
    double maxValue() const { return m_max_value; }
    double averageValue() const { return m_average_value; }
    const kvs::ValueArray<double>& values() const { return m_values; }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( FILE* fp );
    bool parse( FILE* fp );
    bool load();
};

}
