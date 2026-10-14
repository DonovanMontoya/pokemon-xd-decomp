#include <locale>
#include <cctype>
#include <wctype_api.h>
#include <mbstring.h>

#pragma options align=native
#pragma warn_padding off

struct lconv __lconv = {
    ".",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    0x7F,
    0x7F,
    0x7F,
    0x7F,
    0x7F,
    0x7F,
    0x7F,
    "",
    0x7F,
    0x7F,
    0x7F,
    0x7F,
    0x7F,
    0x7F,
    0x7F
};
#pragma warn_padding reset
#pragma options align=reset

/* The default locale name shares the read-only string pool with __lconv. */
static const char* default_locale_name = "C";
