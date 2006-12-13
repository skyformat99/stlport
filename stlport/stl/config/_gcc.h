/* STLport configuration file
 * It is internal STLport header - DO NOT include it directly
 */

#define _STLP_COMPILER "gcc"

#define _STLP_HAS_INCLUDE_NEXT 1

#if (__GNUC__ < 2) || ((__GNUC__ < 3) && ((__GNUC_MINOR__ < 95) || (__GNUC_MINOR__ == 96)))
#  error It's time to upgrage you compiler
#endif

/* Systems having GLIBC installed have different traits */
#if defined (__linux__)
#  ifndef _STLP_USE_GLIBC
#    define _STLP_USE_GLIBC 1
#  endif
#  if defined (__UCLIBC__) && !defined (_STLP_USE_UCLIBC)
#    define _STLP_USE_UCLIBC 1
#  endif
#endif

#if defined (__CYGWIN__) && \
     (__GNUC__ >= 3) && (__GNUC_MINOR__ >= 3) && !defined (_GLIBCPP_USE_C99)
#  define _STLP_NO_VENDOR_MATH_L
#  define _STLP_NO_VENDOR_STDLIB_L
#endif

#if (__GNUC__ < 3)
#  define _STLP_NO_VENDOR_STDLIB_L
#endif

#if (__GNUC__ < 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ < 4))
/* define for gcc versions before 3.4.0. */
#  define _STLP_NO_MEMBER_TEMPLATE_KEYWORD
#endif

/* Tru64 Unix, AIX, HP : gcc there by default uses native ld and hence cannot auto-instantiate
   static template data. If you are using GNU ld, please say so in stl_user_config.h header */
#if (__GNUC__ < 3) && !defined(_STLP_GCC_USES_GNU_LD) && \
   ((defined (__osf__) && defined (__alpha__)) || defined (_AIX) || defined (__hpux) || defined(__amigaos__) )
#  define _STLP_NO_STATIC_TEMPLATE_DATA
#endif

#if !defined (_REENTRANT) && (defined (_THREAD_SAFE) || \
                             (defined (__OpenBSD__) && defined (_POSIX_THREADS)) || \
                             (defined (__MINGW32__) && defined (_MT)))
#  define _REENTRANT
#endif

#if defined (__DJGPP)
#  define _STLP_RAND48    1
#  define _NOTHREADS    1
#  undef  _PTHREADS
#  define _STLP_LITTLE_ENDIAN
#endif

#if defined (__MINGW32__)
/* Mingw32, egcs compiler using the Microsoft C runtime */
#  undef  _STLP_NO_DRAND48
#  define _STLP_NO_DRAND48
#  define _STLP_CALL

#  if defined (_STLP_NEW_PLATFORM_SDK)
/* For the moment the Windows SDK coming with Mingw still mimik the old platform SDK. */
#    undef _STLP_NEW_PLATFORM_SDK
#  endif
#endif /* __MINGW32__ */

#if (__GNUC__ >= 4)
#  if !defined (_STLP_USE_STATIC_LIB)
#    if !defined (_STLP_USE_DYNAMIC_LIB)
#      define _STLP_USE_DYNAMIC_LIB
#    endif
#    define _STLP_USE_DECLSPEC 1
#    define _STLP_EXPORT_DECLSPEC __attribute__((visibility("default")))
#    define _STLP_IMPORT_DECLSPEC __attribute__((visibility("default")))
#    define _STLP_CLASS_EXPORT_DECLSPEC __attribute__((visibility("default")))
#    define _STLP_CLASS_IMPORT_DECLSPEC __attribute__((visibility("default")))
#  endif
#endif

#if defined (__CYGWIN__) || defined (__MINGW32__)
#  if !defined (_STLP_USE_STATIC_LIB)
#    define _STLP_USE_DECLSPEC 1
#    if !defined (_STLP_USE_DYNAMIC_LIB)
#      define _STLP_USE_DYNAMIC_LIB
#    endif
#    define _STLP_EXPORT_DECLSPEC __declspec(dllexport)
#    define _STLP_CLASS_EXPORT_DECLSPEC __declspec(dllexport)
#    define _STLP_CLASS_IMPORT_DECLSPEC __declspec(dllimport)
#  endif
/* The following is defined independently of _STLP_USE_STATIC_LIB because it is also
 * used to import symbols from PSDK under MinGW
 */
#  define _STLP_IMPORT_DECLSPEC __declspec(dllimport)
#endif

#if defined (__CYGWIN__) || defined (__MINGW32__) || !(defined (_STLP_USE_GLIBC) || defined (__sun) || defined(__APPLE__))
#  if !defined (__MINGW32__) && !defined (__CYGWIN__)
#    define _STLP_NO_NATIVE_MBSTATE_T    1
#  endif
#  if !defined (__MINGW32__) || (__GNUC__ < 3) || (__GNUC__ == 3) && (__GNUC_MINOR__ < 4)
#    define _STLP_NO_NATIVE_WIDE_FUNCTIONS 1
#  endif
#  define _STLP_NO_NATIVE_WIDE_STREAMS   1
#endif

#define _STLP_NORETURN_FUNCTION __attribute__((noreturn))

/* Mac OS X is a little different with namespaces and cannot instantiate
 * static data members in template classes */
#if defined (__APPLE__)
#  if ((__GNUC__ < 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ < 3)))
/* Mac OS X is missing a required typedef and standard macro */
typedef unsigned int wint_t;
#  endif

#  define __unix

#  if (__GNUC__ < 3)

 /* Mac OS X needs one and only one source file to initialize all static data
  * members in template classes. Only one source file in an executable or
  * library can declare instances for such data members, otherwise duplicate
  * symbols will be generated. */

#    define _STLP_NO_STATIC_TEMPLATE_DATA
#    define _STLP_STATIC_CONST_INIT_BUG 1
#    define _STLP_STATIC_TEMPLATE_DATA 0
#    define _STLP_WEAK_ATTRIBUTE 1
#  endif /* __GNUC__ < 3 */

#  define _STLP_NO_LONG_DOUBLE

/* Mac OS X needs all "::" scope references to be "std::" */
#  define _STLP_USE_NEW_C_HEADERS

#  define _STLP_NO_VENDOR_STDLIB_L

#endif /* __APPLE__ */


#if defined(__BEOS__) && defined(__INTEL__)
#  define _STLP_NO_NATIVE_WIDE_FUNCTIONS 1
#  define _STLP_NO_NATIVE_WIDE_STREAMS   1
/*
#  define _NOTHREADS 1
*/
#  ifdef _PTHREADS
#    undef  _PTHREADS
#  endif
#  ifdef _STLP_PTHREADS
#    undef _STLP_PTHREADS
#  endif
#  define _STLP_USE_STDIO_IO 1
#  define _STLP_USE_GLIBC 1
#endif

/* g++ 2.7.x and above */
#define _STLP_LONG_LONG long long

#ifdef _STLP_USE_UCLIBC
  /* No *f math fuctions variants (i.e. sqrtf, fabsf, etc.) */
#  define _STLP_NO_VENDOR_MATH_F
  /* No *l math fuctions variants (i.e. sqrtl, fabsl, etc.) */
#  define _STLP_NO_VENDOR_MATH_L
#  define _STLP_NO_LONG_DOUBLE
#endif

#if defined (__OpenBSD__) || defined (__FreeBSD__)
#  define _STLP_NO_VENDOR_MATH_L
#  define _STLP_NO_VENDOR_STDLIB_L /* no llabs */
#  ifndef __unix
#    define __unix
#  endif
#endif

#if defined (__alpha__)
#  define _STLP_NO_VENDOR_MATH_L
#  define _STLP_NO_IEC559_SUPPORT
#endif

#if defined (__hpux)
#  define _STLP_NO_VENDOR_STDLIB_L /* no llabs */
  /* No *f math fuctions variants (i.e. sqrtf, fabsf, etc.) */
#  define _STLP_NO_VENDOR_MATH_F
#endif

#if (__GNUC__ >= 3)
#  ifndef _STLP_HAS_NO_NEW_C_HEADERS
/*
#    ifndef _STLP_USE_UCLIBC
*/
#    define _STLP_HAS_NATIVE_FLOAT_ABS
/*
#    endif
*/
#  else
#    ifdef _STLP_USE_GLIBC
#      define _STLP_VENDOR_LONG_DOUBLE_MATH  1
#    endif
#  endif
#endif

#if (__GNUC__ < 3)
#  define _STLP_HAS_NO_NEW_C_HEADERS     1
#  define _STLP_VENDOR_GLOBAL_CSTD       1
#  define _STLP_DONT_USE_PTHREAD_SPINLOCK 1
#  ifndef __HONOR_STD
#    define _STLP_VENDOR_GLOBAL_EXCEPT_STD 1
#  endif
/* egcs fails to initialize builtin types in expr. like this : new(p) char();  */
#  define _STLP_DEF_CONST_PLCT_NEW_BUG 1
#endif

#  undef _STLP_NO_UNCAUGHT_EXCEPT_SUPPORT
#  undef _STLP_NO_UNEXPECTED_EXCEPT_SUPPORT

/* static template data members workaround strategy for gcc tries
 * to use weak symbols.
 * if you don't want to use that, #define _STLP_WEAK_ATTRIBUTE=0 ( you'll
 * have to put "#define __PUT_STATIC_DATA_MEMBERS_HERE" line in one of your
 * compilation unit ( or CFLAGS for it ) _before_ including any STL header ).
 */
#if defined (_STLP_NO_STATIC_TEMPLATE_DATA) && ! defined (_STLP_WEAK_ATTRIBUTE )
/* systems using GNU ld or format that supports weak symbols
   may use "weak" attribute
   Linux & Solaris ( x86 & SPARC ) are being auto-recognized here */
#  if defined(_STLP_GNU_LD) || defined(__ELF__) || defined (__CYGWIN__) || \
     (( defined (__SVR4) || defined ( __svr4__ )) && \
      ( defined (sun) || defined ( __sun__ )))
#    define _STLP_WEAK_ATTRIBUTE 1
#  endif
#endif /* _STLP_WEAK_ATTRIBUTE */


/* strict ANSI prohibits "long long" ( gcc) */
#if defined ( __STRICT_ANSI__ )
#  undef _STLP_LONG_LONG
#endif

#ifndef __EXCEPTIONS
#  undef  _STLP_DONT_USE_EXCEPTIONS
#  define _STLP_DONT_USE_EXCEPTIONS 1
#endif

#if (__GNUC__ >= 3)
/* Instantiation scheme that used (default) in gcc 3 made void of sense explicit
   instantiation within library: nothing except increased library size. - ptr
 */
#  define _STLP_NO_FORCE_INSTANTIATE
#endif

/* Tune settings for the case where static template data members are not
 * instaniated by default
 */
#if defined ( _STLP_NO_STATIC_TEMPLATE_DATA )
#  define _STLP_STATIC_TEMPLATE_DATA 0
#  if !defined ( _STLP_WEAK_ATTRIBUTE )
#    define _STLP_WEAK_ATTRIBUTE 0
#  endif
#  ifdef __PUT_STATIC_DATA_MEMBERS_HERE
#    define __DECLARE_INSTANCE(type,item,init) type item init
#  else
#    define __DECLARE_INSTANCE(type,item,init)
#  endif
#else
#  define _STLP_STATIC_TEMPLATE_DATA 1
#endif

