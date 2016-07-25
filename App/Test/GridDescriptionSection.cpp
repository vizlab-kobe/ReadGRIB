#include "GridDescriptionSection.h"
#include <kvs/ValueArray>
#include <kvs/Type>


namespace ReadGRIB
{

namespace grib
{

GridDescriptionSection::GridDescriptionSection()
{
}

void GridDescriptionSection::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Length : " << m_length << std::endl;
    os << indent << "Data type : " << m_data_type << std::endl;
}

bool GridDescriptionSection::read( std::ifstream& ifs )
{
    const size_t section_size = peekOct( ifs );
    kvs::ValueArray<kvs::UInt8> buffer( section_size );
    ifs.read( (char*)buffer.data(), buffer.size() );
    if ( ifs.fail() )
    {
        kvsMessageError( "Failed to read the grid description section." );
        return false;
    }

    m_length = packOct( buffer[0], buffer[1], buffer[2] );

    const int nv = packOct( buffer[3] );
    const int pv = packOct( buffer[4] );

    m_data_type = packOct( buffer[5] );

    if ( m_data_type == 0 ) // Lon/Lat grid
    {
        const int Ni = packOct( buffer[6], buffer[7] );
        const int Nj = packOct( buffer[8], buffer[9] );
//        std::cout << "Ni : " << Ni << std::endl;
//        std::cout << "Nj : " << Nj << std::endl;

        const int La1 = packOct( buffer[10], buffer[11], buffer[12] );
        const int Lo1 = packOct( buffer[13], buffer[14], buffer[15] );
//        std::cout << "La1 : " << La1 << std::endl;
//        std::cout << "Lo1 : " << Lo1 << std::endl;

        const int res_flag = packOct( buffer[16] );
//        std::cout << "Res. flag : " << res_flag << std::endl;

        const int La2 = packOct( buffer[17], buffer[18], buffer[19] );
        const int Lo2 = packOct( buffer[20], buffer[21], buffer[22] );
//        std::cout << "La2 : " << La2 << std::endl;
//        std::cout << "Lo2 : " << Lo2 << std::endl;

        const int Di = ( buffer[16] & 128 ) ? packOct( buffer[23], buffer[24] ) : 0;
        const int Dj = ( buffer[16] & 128 ) ? packOct( buffer[25], buffer[26] ) : 0;
//        std::cout << "Di : " << Di << std::endl;
//        std::cout << "Dj : " << Dj << std::endl;

        const int scan_flag = packOct( buffer[27] );
//        std::cout << "Scan flag : " << scan_flag << std::endl;
    }

    return true;
}

} // end of namespace grib

} // end of namespace ReadGRIB
