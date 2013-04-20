#pragma once

//用模板匹配的方式实现static_assert功能。

namespace slib {
template <int> struct CompileTimeError;
template <> struct CompileTimeError<true> {
};
}

#define SLIB_STATIC_CHECK(expr, msg)
{
  slib::CompileTimeError<((expr) != 0)> ERROR_##msg;
  (void) ERROR_##msg;
}
