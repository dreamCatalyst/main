/* This file is part of the libjm project
 * Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
 *
 * jmdb.i - Defines the swig interface for the jmdb library
 */

%module jmdb_ruby
%{
  #include "jmdb_databasehandler.h"
  #include "jmdb_databasehandlerfactory.h"
  #include "jmdb_field.h"
  #include "jmdb_preparedstatement.h"
  #include "jmdb_columninformation.h"
  #include "jmdb_resultset.h"
  #include "jmdb_resultrow.h"
  
  /* ------- jmdb_sqlite headers ------ */
  #include "jmdb_sqlitedatabasehandler.h"
  
  /* ------- jmdb_mysql headers ------ */
  #include "jmdb_mysqldatabasehandler.h"
%}


/* -------------------------------------------- Typemaps ------------ */

%include "typemaps.i"

/* --------------------- Typemaps for int64_t ------------ */

%typemap(out) int64_t {
  $result = LL2NUM($1);
}

%typemap(in) int64_t const {
  $1 = NUM2LL($input);
}

%typemap(typecheck,precedence=SWIG_TYPECHECK_INTEGER) int64_t {
  $1 = (TYPE($input) == T_BIGNUM);
}


/* -------------------------------------------- Includes ------------ */

%include "jmdb_databasehandler.i"
%include "jmdb_databasehandlerfactory.i"
%include "jmdb_field.i"
%include "jmdb_preparedstatement.i"
%include "jmdb_columninformation.i"
%include "jmdb_resultset.i"
%include "jmdb_resultrow.i"

%include "jmdb_sqlitedatabasehandler.i"

%include "jmdb_mysqldatabasehandler.i"