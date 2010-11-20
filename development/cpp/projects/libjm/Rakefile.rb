require 'rake/clean'
CLEAN.include('build')

task :default => [ :build ] 
task :all [ :build, :test_all ]
tast :test => [ :test_all ]

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
