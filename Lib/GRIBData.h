#pragma once
#include <string>
#include <vector>
#include <kvs/Date>
#include <kvs/Time>
#include "Message.h"


namespace grib
{

class Data
{
public:

    typedef grib::Message Message;
    typedef std::vector<Message> Messages;

public:
    static Data Find( const Data& data, const int parameter_id );
    static Data Find( const Data& data, const int parameter_id, const kvs::Date& date );
    static Data Find( const Data& data, const int parameter_id, const kvs::Time& time );

private:
    Messages m_messages;

public:
    Data(){}
    Data( FILE* fp );

    const Messages& messages() const { return m_messages; }
    const Message& message( const size_t index ) const { return m_messages[index]; }
    size_t numberOfMessages() const { return m_messages.size(); }

    void add( const Message& message ) { m_messages.push_back( message ); }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( FILE* fp );
    bool parse( FILE* fp );
    bool load();

private:
    bool write( const std::string& ) { return false; }
};

}
