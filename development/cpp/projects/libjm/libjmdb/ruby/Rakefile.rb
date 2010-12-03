# This file is part of the libjm project 
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl

# Rakefile.rb - Defines task to build and run the tests for the jmdb library
require '../../rake_common'
require 'rake/clean'
CLEAN.include('*_wrapper.cpp', '*.o', '*.so', 'Makefile', 'mkmf.log');

task :default => [ :all ]
task :all => [ :compile_sources, :run_tests ]
task :test => [ :run_tests ]

task :compile_sources => [ :create_makefile ] do
  sh %{ make }
end

task :create_makefile => [ :check_create_links, :generate_wrappers ] do
  sh %{ ruby extconf.rb --with-jmdb-dir=.. }
end

task :generate_wrappers => [] do
  sh %{ swig -c++ -ruby -Wall -Wextra -I.. -o jmdb_ruby_wrapper.cpp swig/jmdb.i }
end

task :create_sqlite_testdb do
  puts "Creating sqlite fixture database"
  require 'rakehelpers/create_sqlite_testdb'
  create_sqlite_testdb
end