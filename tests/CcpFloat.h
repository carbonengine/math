// Copyright (c) 2026 CCP Games

#pragma once
#ifndef CcpMathTest_CcpFloat_h
#define CcpMathTest_CcpFloat_h

#include <cmath>
#include <cfloat>

inline bool CcpIsNaN( float x )
{
#ifdef _MSC_VER
    return _isnan( x ) != 0;
#else
    return std::isnan( x );
#endif
}

inline bool CcpIsFinite( float x )
{
#ifdef _MSC_VER
    return _finite( x ) != 0;
#else
    return std::isfinite( x );
#endif
}

#endif
