#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <kvs/Program>
#include <kvs/StructuredVolumeObject>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#include <kvs/RayCastingRenderer>
#include <kvs/Bounds>
#include <kvs/TransferFunction>
#include <kvs/RGBFormulae>
#include <Lib/GRIBData.h>


namespace
{

typedef ReadGRIB::GRIBData Data;
typedef kvs::StructuredVolumeObject Volume;

inline void Print( const Data& data )
{
    for ( size_t i = 0; i < data.numberOfMessages(); i++ )
    {
        const Data::Message& message = data.message(i);
        std::cout << std::setfill('0') << std::setw(5)
                  << i << ", "
                  << "("
                  << std::setfill('0') << std::setw(2)
                  << message.parameterID() << ") "
                  << message.date().toString("/") << " - "
                  << message.time().toString(":") << std::endl;
    }
}

inline Volume* Import( const Data& data )
{
    KVS_ASSERT( data.numberOfMessages() != 0 );

    const size_t dimx = data.message(0).ni();
    const size_t dimy = data.message(0).nj();
    const size_t dimz = data.numberOfMessages();

    kvs::ValueArray<double> values( dimx * dimy * dimz );
    values.fill(0);
    for ( size_t i = 0; i < dimz; i++ )
    {
        std::copy( data.message(i).values().begin(),
                   data.message(i).values().end(),
                   values.begin() + dimx * dimy * i );
    }

    Volume* volume = new Volume();
    volume->setVeclen( 1 );
    volume->setResolution( kvs::Vec3u( dimx, dimy, dimz ) );
    volume->setGridTypeToUniform();
    volume->setValues( kvs::AnyValueArray( values ) );
    volume->updateMinMaxValues();
    volume->updateMinMaxCoords();
    return volume;
}

}

class Program : public kvs::Program
{
    int exec( int argc, char** argv )
    {
        kvs::glut::Application app( argc, argv );
        kvs::glut::Screen screen( &app );

        ::Volume* volume = this->import( argv[1] );
        const float zscale = 10;
        const kvs::Vec3 min_coord = volume->minExternalCoord();
        const kvs::Vec3 max_coord = volume->maxExternalCoord() * kvs::Vec3( 1, 1, zscale );
        volume->setMinMaxExternalCoords( min_coord, max_coord );
        volume->print( std::cout );

        kvs::Bounds* bounds = new kvs::Bounds();
        bounds->setLineWidth( 2.0 );

        kvs::glsl::RayCastingRenderer* renderer = new kvs::glsl::RayCastingRenderer();
        renderer->setTransferFunction( kvs::TransferFunction( kvs::RGBFormulae::Rainbow( 256 ) ) );
        renderer->disableShading();

        screen.registerObject( volume, bounds );
        screen.registerObject( volume, renderer );
        screen.show();

        return app.run();
    }

    ::Volume* import( const std::string& filename )
    {
        FILE* fp = fopen( filename.c_str(), "r" );
        if ( !fp ) { return NULL; }

        ::Data data;
        data.parse( fp );

        data = ::Data::Find( data, 2, kvs::Time( 0, 0, 0 ) );
        data.load();
        ::Print( data );

        ::Volume* volume = ::Import( data );

        fclose( fp );

        return volume;
    }
};

int main( int argc, char** argv )
{
    Program program;
    return program.start( argc, argv );
}
