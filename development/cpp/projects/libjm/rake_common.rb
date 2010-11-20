# This file is part of the libjm project 
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl

# rake_common.rb - Common tasks for each subprojects' Rakefile

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
