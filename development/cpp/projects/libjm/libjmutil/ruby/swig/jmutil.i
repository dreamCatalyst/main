/* This file is part of the libjm project
 * Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
 *
 * jmutil.i - Defines the swig interface for the jmutil library
 */

%module jmutil_ruby
%{
  #include "jmutil_fileutils.h"
  #include "jmutil_stringutils.h"
%}

%include "jmutil_fileutils.i"
%include "jmutil_stringutils.i"
