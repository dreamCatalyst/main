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

task :check_create_links => [] do
  if(!File.exists?("../lib"))
    create_lib_link
  end
  if(!File.exists?("../include"))
    create_include_link
  end
end

task :run_tests => [ ] do
  # I know the bash -c is ugly but couldn't get the LD_LIBRARY_PATH set otherwise
  sh %{ bash -c "LD_LIBRARY_PATH=../lib ruby -I unit-tests unit-tests/ts_all.rb" }
end


def create_lib_link
  # TODO check for windows and do something else here
  sh %{ cd ..; ln -s ../build lib }
end

def create_include_link
  # TODO check for windows and do something else here
  sh %{ cd ..; ln -s . include }
end

