#pragma once
#include <kvs/Macro>
#include <kvs/Breakpoint>
#include <kvs/Platform>
#include <grib_api.h>
#include <string>


namespace grib
{

std::string GetErrorMessage( const int error );
bool HasError( const int error );

}
