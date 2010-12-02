# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
# ts_all.rb - Test suite for the jmdb library

require 'test/unit'

require '00_test_loading_extension'

# Generic tests (non-db specific)
require '01_test_string_field'
require '02_test_int_field'
require '03_test_real_field'
require '04_test_binary_data_field'
require '05_test_dbhfactory'

# sqlite tests
require '11_test_sqlite_connstr'
require '12_test_sqlite_dbh'

# mysql tests
