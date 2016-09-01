#include <iostream>
#include <string>
#include <kvs/Program>
#include <kvs/StructuredVolumeObject>
#include "GRIBData.h"


namespace
{

typedef ReadGRIB::GRIBData DataSet;
typedef kvs::StructuredVolumeObject Object;


struct DataDate
{
    int century;
    int year;
    int month;
    int day;

    int number() const
    {
        return ( century - 1 ) * 1000000 + year * 10000 + month * 100 + day;
    }
};

struct DataTime
{
    int hour;
    int minute;

    int number() const
    {
        return hour * 1000 + minute;
    }
};

inline DataSet::Messages Find( const DataSet::Messages& messages, const int parameter_id )
{
    DataSet::Messages output;
    for ( size_t i = 0; i < messages.size(); i++ )
    {
        const DataSet::Message& message = messages[i];
        if ( parameter_id == message.productDefinitionSection().parameterID() )
        {
            output.push_back( message );
        }
    }
    return output;
}

inline DataSet::Messages Find( const DataSet::Messages& messages, const int parameter_id, const DataTime& time )
{
    DataSet::Messages output;
    for ( size_t i = 0; i < messages.size(); i++ )
    {
        const DataSet::Message& message = messages[i];
        if ( parameter_id == message.productDefinitionSection().parameterID() )
        {
            const int hour = message.productDefinitionSection().hour();
            const int minute = message.productDefinitionSection().minute();
            if ( hour == time.hour && minute == time.minute )
            {
                output.push_back( message );
            }
        }
    }
    return output;
}

inline DataSet::Messages Find( const DataSet::Messages& messages, const int parameter_id, const DataDate& date )
{
    DataSet::Messages output;
    for ( size_t i = 0; i < messages.size(); i++ )
    {
        const DataSet::Message& message = messages[i];
        if ( parameter_id == message.productDefinitionSection().parameterID() )
        {
            const int century = message.productDefinitionSection().century();
            const int year = message.productDefinitionSection().year();
            const int month = message.productDefinitionSection().month();
            const int day = message.productDefinitionSection().day();
            if ( century == date.century && year == date.year && month == date.month && day == date.day )
            {
                output.push_back( message );
            }
        }
    }
    return output;
}

inline void Print( const DataSet::Messages& messages )
{
    for ( size_t i = 0; i < messages.size(); i++ )
    {
        ::DataDate date;
        date.century = messages[i].productDefinitionSection().century();
        date.year = messages[i].productDefinitionSection().year();
        date.month = messages[i].productDefinitionSection().month();
        date.day = messages[i].productDefinitionSection().day();

        ::DataTime time;
        time.hour = messages[i].productDefinitionSection().hour();
        time.minute = messages[i].productDefinitionSection().minute();

        std::cout << i << "," << date.number() << "," << time.number() << std::endl;
    }
}

Object Import( const DataSet::Messages& messages )
{
    KVS_ASSERT( messages.size() != 0 );
    KVS_ASSERT( messages.gridDescriptionSection().gridType() == 0 );

    const size_t dimx = messages[0].gridDescriptionSection().latLonGrid().ni();
    const size_t dimy = messages[0].gridDescriptionSection().latLonGrid().nj();
    const size_t dimz = messages.size();

    std::cout << "dimx = " << dimx << std::endl;
    std::cout << "dimy = " << dimy << std::endl;
    std::cout << "dimz = " << dimz << std::endl;

    Object object;
    object.setResolution( kvs::Vec3u( dimx, dimy, dimz ) );
    return object;
}

}

class Program : public kvs::Program
{
    int exec( int argc, char** argv )
    {
        std::string filename( argv[1] );
        ::DataSet data( filename );
//        data.print( std::cout );

        int parameter_id = 2;
        ::DataTime time;
        time.hour = 12;
        time.minute = 0;
        ::DataSet::Messages messages = ::Find( data.messages(), parameter_id, time );
        ::Print( messages );

        ::Object object = ::Import( messages );

        return 0;
    }
};

int main( int argc, char** argv )
{
    Program program;
    return program.start( argc, argv );
}
