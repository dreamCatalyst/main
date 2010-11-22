
%include "typemaps.i"
%apply int *OUTPUT { int* len };

%typemap(out) int64_t {
  $result = LL2NUM($1);
}

%typemap(in) int64_t const {
  $1 = NUM2LL($input);
}

%typemap(typecheck,precedence=SWIG_TYPECHECK_INTEGER) int64_t {
  $1 = (TYPE($input) == T_BIGNUM);
}

%include "jmdb_field.h"
