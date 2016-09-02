#include "Data.h"
#include <cstdio>
#include <kvs/ValueArray>
#include <kvs/Message>


namespace grib
{

Data Data::Find( const Data& data, const int parameter_id )
{
    Data output;
    for ( size_t i = 0; i < data.numberOfMessages(); i++ )
    {
        const Message& message = data.message(i);
        if ( parameter_id == message.parameterID() )
        {
            output.add( message );
        }
    }
    return output;
}

Data Data::Find( const Data& data, const int parameter_id, const kvs::Date& date )
{
    Data output;
    for ( size_t i = 0; i < data.numberOfMessages(); i++ )
    {
        const Message& message = data.message(i);
        if ( parameter_id == message.parameterID() )
        {
            if ( date == message.date() )
            {
                output.add( message );
            }
        }
    }
    return output;
}

Data Data::Find( const Data& data, const int parameter_id, const kvs::Time& time )
{
    Data output;
    for ( size_t i = 0; i < data.numberOfMessages(); i++ )
    {
        const Message& message = data.message(i);
        if ( parameter_id == message.parameterID() )
        {
            if ( time == message.time() )
            {
                output.add( message );
            }
        }
    }
    return output;
}

Data::Data( FILE* fp )
{
    this->read( fp );
}

void Data::print( std::ostream& os, const kvs::Indent& indent ) const
{
    for ( size_t i = 0; i < m_messages.size(); i++ )
    {
        os << indent << "Message (" << i << ")" << std::endl;
        m_messages[i].print( os, indent.nextIndent() );
    }
}

bool Data::read( FILE* fp )
{
    KVS_ASSERT( fp );

    if ( !this->parse( fp ) ) { return false; }
    if ( !this->load() ) { return false; }
    return true;
}

bool Data::parse( FILE* fp )
{
    KVS_ASSERT( fp );

    for ( size_t i = 0; ; i++ )
    {
        Message message;
        if ( !message.parse( fp ) )
        {
            if ( message.hasError() ) { return false; }
            if ( !message.isValid() ) { break; }
        }

        m_messages.push_back( message );
    }

    return true;
}

bool Data::load()
{
    for ( size_t i = 0; i < m_messages.size(); i++ )
    {
        if ( !m_messages[i].load() ) { return false; }
    }

    return true;
}

}
