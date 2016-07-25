#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <kvs/Indent>
#include "IndicatorSection.h"
#include "ProductDefinitionSection.h"
#include "GridDescriptionSection.h"
#include "BitMapSection.h"
#include "BinaryDataSection.h"
#include "EndSection.h"


namespace ReadGRIB
{

namespace grib
{

class Message
{
private:
    grib::IndicatorSection m_indicator_section;
    grib::ProductDefinitionSection m_product_definition_section;
    grib::GridDescriptionSection m_grid_description_section;
    grib::BitMapSection m_bit_map_section;
    grib::BinaryDataSection m_binary_data_section;
    grib::EndSection m_end_section;

public:

    Message();

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( std::ifstream& ifs );
};

} // end of namespace grib

} // end of namespace ReadGRIB
