require 'test/unit'
require 'jmutil_ruby'

include Jmutil_ruby;


class TestFileUtils < Test::Unit::TestCase
  def setup
    @@dir = "/tmp/test_file_utils"
    @@fn = "aFile.txt"
    @@fn_path = "#{@@dir}/#{@@fn}"

    `mkdir #{@@dir}`
    `touch #{@@fn_path}`
  end

  def teardown
    `rm -rf #{@@dir}`
  end

  def test_fileExists
    assert(FileUtils::exists(@@fn_path), "exists() returns true for an existing file");
    assert(FileUtils::exists(@@dir), "exists() returns true for an existing directory");
    assert(!FileUtils::exists(""), "exists() returns false for an empty string");
    assert(!FileUtils::exists("#{@@dir}/no_file.txt"), "exists() returns false for a non existing file");
  end
end

