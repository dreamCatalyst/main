# This file is part of the libjm project 
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl

# Rakefile.rb - Defines task to build and run the tests for the jmutil library
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
  sh %{ ruby extconf.rb --with-jmutil-dir=.. }
end

task :generate_wrappers => [] do
   sh %{ swig -c++ -ruby -Wall -Wextra -I.. -o jmutil_ruby_wrapper.cpp swig/jmutil.i }
end

