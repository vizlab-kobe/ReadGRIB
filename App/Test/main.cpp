#include <iostream>
#include <string>
#include <kvs/Program>
#include "GRIB1Data.h"


class Program : public kvs::Program
{
    int exec( int argc, char** argv )
    {
        std::string filename( argv[1] );
        ReadGRIB::GRIB1Data data( filename );
        data.print( std::cout );
        return 0;
    }
};


int main( int argc, char** argv )
{
    Program program;
    return program.start( argc, argv );
}
