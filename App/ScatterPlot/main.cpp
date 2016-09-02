#include <iostream>
#include <string>
#include <vector>
#include <kvs/Program>
#include <kvs/TableObject>
#include <kvs/ScatterPlotRenderer>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#include <kvs/glut/Axis2D>
#include <Lib/GRIBData.h>


class Program : public kvs::Program
{
    typedef ReadGRIB::GRIBData Data;

    int exec( int argc, char** argv )
    {
        kvs::glut::Application app( argc, argv );
        kvs::glut::Screen screen( &app );

        std::string filename( argv[1] );
        FILE* fp = fopen( filename.c_str(), "r" );
        if ( !fp ) { return 1; }

        Data data;
        data.parse( fp );

        int parameter_id1 = 2; // Pressure
        Data data1 = Data::Find( data, parameter_id1, kvs::Time( 0, 0, 0 ) );
        data1.load();

        int parameter_id2 = 11; // Temperature
        Data data2 = Data::Find( data, parameter_id2, kvs::Time( 0, 0, 0 ) );
        data2.load();

        kvs::TableObject* table = new kvs::TableObject();
        table->addColumn( kvs::AnyValueArray( data1.message(0).values() ), "Pressure" );
        table->addColumn( kvs::AnyValueArray( data2.message(0).values() ), "Temperature" );

        kvs::ScatterPlotRenderer* renderer = new kvs::ScatterPlotRenderer();
        renderer->setPointColor( kvs::RGBColor( 220, 20, 60 ) );
        renderer->setPointOpacity( 50 );
        renderer->setPointSize( 5.0 );
        renderer->setBackgroundColor( kvs::RGBAColor( 255, 255, 255, 128 ) );

        kvs::glut::Axis2D* axis = new kvs::glut::Axis2D();

        screen.registerObject( table, renderer );
        screen.registerObject( table, axis );
        screen.show();

        fclose( fp );

        return app.run();
    }
};

int main( int argc, char** argv )
{
    Program program;
    return program.start( argc, argv );
}
