
/* Ubuntu needs it */

#define HAVE_STDINT_H 1
#define HAVE_MBSTATE_T 1
#define HAVE_NAMESPACES 1
#undef NOT_USING_DJVU_NAMESPACE
#define HAVE_STDINCLUDES 1
#define AUTOCONF 1

#ifdef WIN32
#include "autoconfigwin.h"
#else
#include "autoconfig.h"
#define HAVE_PTHREAD 1
#define CPP_SUPPORTS_EXCEPTIONS 1
#endif
