#pragma once

namespace slib
{
////////////////////////////////////////////////////////////////////////////////
// Helper structure for the STATIC_CHECK macro
////////////////////////////////////////////////////////////////////////////////

    template<int> struct CompileTimeError;
    template<> struct CompileTimeError<true> {};
}

#define SLIB_STATIC_CHECK(expr, msg) \
    { slib::CompileTimeError<((expr) != 0)> ERROR_##msg; (void)ERROR_##msg; } 

