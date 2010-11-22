# This file is part of the libjm project
# Copyright (C) 2010  Jonathan Maasland
#
# Rakefile.rb - Defines tasks to build, clean and test libjm
# Use this to build with default settings

task :default => [ :build ] 
task :all => [ :build, :test_all ]
task :test => [ :test_all ]
task :rebuild => [ :clean, :build ]

task :clean do
  rm_rf "build"
  sh %{ cd libjmdb/ruby && rake clean }
  sh %{ cd libjmutil/ruby && rake clean }
end

task :build => [] do
  Dir.mkdir("build") if(!File.exists?("build"))
  sh %{ cd build && cmake .. && make }
end

task :test_all => [ :test_jmdb, :test_jmutil ]

task :test_jmdb do
  sh %{ cd libjmdb/ruby && rake }
end

task :test_jmutil do
  sh %{ cd libjmutil/ruby && rake }
end

# ------ Some tasks to help ease development

task :cpplint do
  fl = FileList.new("**/*.cpp", "**/*.h")
  fl.exclude(/_wrapper.cpp/).exclude(/^build/).sort
  quotedFns = fl.collect do |fn| '"' + fn + '"' end

  lintFilter = "-readability/todo," +
               "-readability/parens," +
               "-build/header_guard," +
               "-build/include," +
               "-whitespace/blank_lines," +
               "-whitespace/end_of_line," +
               "-whitespace/parens"

  `cpplint.py "--filter=#{lintFilter}" #{quotedFns.join(" ")}`
end

