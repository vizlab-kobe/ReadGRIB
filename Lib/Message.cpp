#include "Message.h"

#include <kvs/ValueArray>
#include <kvs/Type>


namespace ReadGRIB
{

namespace grib
{

Message::Message()
{
}

void Message::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Indicator Section" << std::endl;
    m_indicator_section.print( os, indent.nextIndent() );
    os << indent << "Product Definition Section" << std::endl;
    m_product_definition_section.print( os, indent.nextIndent() );
    if ( m_product_definition_section.hasGDS() )
    {
        os << indent << "Grid Description Section" << std::endl;
        m_grid_description_section.print( os, indent.nextIndent() );
    }
    if ( m_product_definition_section.hasBMS() )
    {
        os << indent << "Bit Map Section" << std::endl;
        m_bit_map_section.print( os, indent.nextIndent() );
    }
    os << indent << "Binary Data Section" << std::endl;
    m_binary_data_section.print( os, indent.nextIndent() );
    os << indent << "End Section" << std::endl;
    m_end_section.print( os, indent.nextIndent() );
}

bool Message::read( std::ifstream& ifs )
{
    if ( !m_indicator_section.read( ifs ) ) { return false; }
    if ( !m_product_definition_section.read( ifs ) ) { return false; }
    if ( m_product_definition_section.hasGDS() ) { if ( !m_grid_description_section.read( ifs ) ) { return false; } }
    if ( m_product_definition_section.hasBMS() ) { if ( !m_bit_map_section.read( ifs ) ) { return false; } }
    if ( !m_binary_data_section.read( ifs ) ) { return false; }
    if ( !m_end_section.read( ifs ) ) { return false; }
    return true;
}

} // end of namespace grib

} // end of namespace ReadGRIB
