#pragma once

#if __cplusplus >= 2011
#define _BCLHASCXX11 1
#endif
#if __cplusplus >= 2014
#define _BCLHASCXX14 1
#endif
#if __cplusplus >= 2017
#define _BCLHASCXX17 1
#endif
#if __cplusplus >= 2020
#define _BCLHASCXX20 1
#endif
#if __cplusplus >= 2023
#define _BCLHASCXX23 1
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
#if __cplusplus >= 2011
#define _BKHASCXX11 1
#endif
#if __cplusplus >= 2014
#define _BKHASCXX14 1
#endif
#if __cplusplus >= 2017
#define _BKHASCXX17 1
#endif
#if __cplusplus >= 2020
#define _BKHASCXX20 1
#endif
#if __cplusplus >= 2023
#define _BKHASCXX23 1
#endif


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
#define _bk_empty_adress [[msvc::no_unique_address]]
#else
#define _bkemptyaddress [[no_unique_address]]
#endif

#else
#define _bkconstexpr20
#define _bk_empty_adress
#endif

#if _BKHASCXX23
#define _bkconsteval consteval
#else
#define _bkconsteval
#endif
