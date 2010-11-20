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
  #include "jmdb_resultset.h"
%}

%include "jmdb_databasehandler.i"
%include "jmdb_databasehandlerfactory.i"
%include "jmdb_field.i"
%include "jmdb_preparedstatement.i"
%include "jmdb_resultset.i"