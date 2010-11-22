%include "typemaps.i"

%typemap(in) const int64_t v {
  $1 = NUM2LL($input);
}

%typemap(typecheck,precedence=SWIG_TYPECHECK_INTEGER) int64_t {
  $1 = (TYPE($input) == T_BIGNUM);
}

%include "jmutil_stringutils.h"