#pragma once

//TODO: fix MSVC compilation. MSVC Does not auto emit __cplusplus


#if __cplusplus >= 201103L
#define _BKHASCXX11 1
#endif
#if __cplusplus >= 201402L
#define _BKHASCXX14 1
#endif
#if __cplusplus >= 201703L
#define _BKHASCXX17 1
#endif
#if __cplusplus >= 202002L
#define _BKHASCXX20 1
#endif
#if __cplusplus >= 202302L
#define _BKHASCXX23 1
#endif


#if _BCLHASCXX11
#define  _BCLCONSTEXPR11 constexpr
#else
#define _BCLCONSTEXPR11
#endif


#if _BCLHASCXX14
#define  _BCLCONSTEXPR14 constexpr
#else
#define _BCLCONSTEXPR11
#endif


#if _BCLHASCXX17
#define  _BCLCONSTEXPR17 constexpr
#define  _BCLNODISCARD [[nodiscard]]
#else
#define _BCLCONSTEXPR17
#define _BCLNODISCARD
#endif

#if _BCLHASCXX20
#define  _BCLCONSTEXPR20 constexpr

#ifdef _MSC_VER
#define _BCL_EMPTY_ADRESS [[msvc::no_unique_address]]
#else
#define _BCLEMPTYADRESS [[no_unique_address]]
#endif

#else
#define _BCLCONSTEXPR
#define _BCL_EMPTY_ADRESS
#endif

#if _BCLHASCXX23
#define _BCLCONSTEVAL consteval
#else
#define _BCLCONSTEVAL
#endif

//---------------------------------

#if _BKHASCXX11
#define  _bkconstexpr11 constexpr
#else
#define _bkconstexpr11
#endif


#if _BKHASCXX14
#define  _bkconstexpr14 constexpr
#else
#define _bkconstexpr14
#endif


#if _BKHASCXX17
#define  _bkconstexpr17 constexpr
#define  _bknodiscard [[nodiscard]]
#else
#define _bkconstexpr17
#define _bknodiscard
#endif

#if _BKHASCXX20
#define  _bkconstexpr20 constexpr

#ifdef _MSC_VER
#define _bkemptyaddress
#else
#define _bkemptyaddress [[no_unique_address]]
#endif

#else
#define _bkconstexpr20
#define _bkemptyaddress
#endif

#if _BKHASCXX23
#define _bkconsteval consteval
#else
#define _bkconsteval
#endif
