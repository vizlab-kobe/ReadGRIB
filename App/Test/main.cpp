#include <iostream>
#include <string>
#include <vector>
#include <kvs/Program>
#include <Lib/GRIBData.h>


class Program : public kvs::Program
{
    typedef ReadGRIB::GRIBData Data;

    int exec( int argc, char** argv )
    {
        std::string filename( argv[1] );
        FILE* fp = fopen( filename.c_str(), "r" );
        if ( !fp ) { return 1; }

        Data data;
        data.parse( fp );
        data.print( std::cout );

        fclose( fp );

        return 0;
    }
};

int main( int argc, char** argv )
{
    Program program;
    return program.start( argc, argv );
}
