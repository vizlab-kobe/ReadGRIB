#include "GRIB.h"
#include <kvs/Message>


namespace ReadGRIB
{

namespace grib
{

std::string GetErrorMessage( const int error )
{
    return grib_get_error_message( error );
}

bool HasError( const int error )
{
    if ( error == GRIB_SUCCESS ) { return true; }

    const std::string error_message = GetErrorMessage( error );
    kvsMessageError( "%s", error_message.c_str() );
    return false;
}

}

}
