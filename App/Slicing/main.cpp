#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <kvs/Program>
#include <kvs/ColorImage>
#include <kvs/RGBFormulae>
#include <Lib/GRIBData.h>


namespace
{

typedef ReadGRIB::GRIBData Data;
typedef kvs::ColorImage Image;

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

inline Image Slice( const Data& data, const size_t index, const kvs::ColorMap& cmap )
{
    KVS_ASSERT( data.numberOfMessages() != 0 );

    const size_t dimx = data.message(0).ni();
    const size_t dimy = data.message(0).nj();
    Image image( dimx, dimy );

    const Data::Message& message = data.message( index );
    for ( size_t i = 0; i < image.numberOfPixels(); i++ )
    {
        const double value = message.values().at(i);
        const kvs::RGBColor color = cmap.at( value );
        image.setPixel( i, color );
    }

    return image;
}

}

class Program : public kvs::Program
{
    int exec( int argc, char** argv )
    {
        std::string filename( argv[1] );
        FILE* fp = fopen( filename.c_str(), "r" );
        if ( !fp ) { return 0; }

        ::Data data;
        data.parse( fp );

        data = ::Data::Find( data, 2, kvs::Time( 0, 0, 0 ) );
        data.load();
        ::Print( data );

        double min_value = data.message(0).minValue();
        double max_value = data.message(0).maxValue();
        for ( size_t i = 0; i < data.numberOfMessages(); i++ )
        {
            min_value = kvs::Math::Min( min_value, data.message(i).minValue() );
            max_value = kvs::Math::Max( max_value, data.message(i).maxValue() );
        }

        kvs::ColorMap cmap = kvs::RGBFormulae::Rainbow( 256 );
        cmap.setRange( min_value, max_value );

        for ( size_t i = 0; i < data.numberOfMessages(); i++ )
        {
            size_t id = data.message(i).parameterID();
            std::string date = data.message(i).date().toString("");
            std::string time = data.message(i).time().toString("");
            std::ostringstream n; n << std::setfill('0') << std::setw(2) << id;
            std::string name = "image_" + n.str() + "_" + date + "_" + time + ".bmp";

            Image image = ::Slice( data, i, cmap );
            image.write( name );
            std::cout << "Output image > " << name << std::endl;
        }

        fclose( fp );

        return 0;
    }
};

int main( int argc, char** argv )
{
    Program program;
    return program.start( argc, argv );
}
