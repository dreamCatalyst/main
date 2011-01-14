#
#
#

require 'test/unit'
require 'cmake_parser'


FixtureDirectory = "unit-tests/fixtures/cmake_parser"

CMakeTestFiles = {
  :simple_cmake    => "#{FixtureDirectory}/simple_cmake.txt",
  :empty_cmake     => "#{FixtureDirectory}/empty_cmake.txt",
  :open_paren      => "#{FixtureDirectory}/open_paren.txt",
  :open_string     => "#{FixtureDirectory}/open_string.txt",
  :complex_string  => "#{FixtureDirectory}/complex_string.txt",
  :complex_string2 => "#{FixtureDirectory}/complex_string2.txt",
  :complex_string3 => "#{FixtureDirectory}/complex_string3.txt",
  :complex_comment => "#{FixtureDirectory}/complex_comment.txt",
  :simple_variables => "#{FixtureDirectory}/simple_variables.txt",
  :simple_targets   => "#{FixtureDirectory}/simple_targets.txt"
}
CMakeTestDirectory = "#{FixtureDirectory}/complex_dir"


class TestCMakeParser < Test::Unit::TestCase
  def setup
    check_fixtures unless @@fixtures_checked
    @parser = CMakeParser.new
  end

  @@fixtures_checked = false

  def check_fixtures
    check_cmake_files_exist
    check_cmake_directory_exists
    @@fixtures_checked = true
  end

  def check_cmake_files_exist
    CMakeTestFiles.values.each do |filename|
      assert( File.exist?( filename ),
             "Missing cmake fixture file '#{filename}'" )
    end
  end

  def check_cmake_directory_exists
    assert( File.directory?( CMakeTestDirectory ), 
           "Missing cmake fixture directory '#{CMakeTestDirectory}'" )
  end

  def verify_file_parses(file_sym)
    fn = CMakeTestFiles[ file_sym ]
    assert_not_nil( @parser.parse( fn ), "Expected '#{fn}' to parse")
    assert( !@parser.has_error() )
  end

  def verify_file_does_not_parse(file_sym)
    fn = CMakeTestFiles[ file_sym ];
    assert_nil( @parser.parse( fn ), "Expected '#{fn}' not to parse")
    assert( @parser.has_error() )
  end

  def test_parse_non_existing_file
    assert_nil( @parser.parse("non-existing-file") )
    assert( @parser.has_error() )
  end

  def test_parse_invalid_cmake_files
    verify_file_does_not_parse :open_paren
    verify_file_does_not_parse :open_string
  end

  def test_parse_simple_cmake_file
    verify_file_parses :simple_cmake
  end

  def test_parse_empty_file
    verify_file_parses :empty_cmake
  end

  def test_handling_comments
    verify_file_parses :complex_string
    verify_file_parses :complex_string2
    verify_file_parses :complex_string3
    verify_file_parses :complex_comment
  end

  def test_simple_variables
    verify_file_parses :simple_variables
    vars = @parser.result.variables

    assert( 3, vars.size, "Incorrect number of variables parsed")
    expected = {
      "Var1" => %w[ a b c ],
      "Var2" => %w[ D E F ],
      "Var3" => %w[ 1 2 3 ]
    }
    vars.each do |variable|
      assert( expected.has_key?(variable.name) )
      assert_equal( expected[variable.name], variable.values )
    end
  end

  def test_executable_targets
    verify_file_parses :executable_targets
    targets = @parser.result.targets
    assert( 2, targets.size, "Incorrect number of targets parsed")

    target = targets[0]
    assert_equal( "Target1", target.name )
    assert_equal( %w[ main.cpp ], target.sources )
    assert_equal( :executable, target.type )

    target = targets[1]
    assert_equal( "Target2", target.name )
    assert_equal( %w[ main.cpp ], target.sources )
    assert_equal( :executable, target.type )
  end

  def test_library_targets
    verify_file_parses :library_targets
    targets = @parser.result.targets
    assert( 2, targets.size, "Incorrect number of targets parsed")

    target = targets[0]
    assert_equal( "Target1", target.name )
    assert_equal( :library, target.type )
    assert_equal( %w[ source1.cpp source2.cpp ], target.sources )
    assert_equal( :shared, target.libtype )

    target = targets[1]
    assert_equal( "Target2", target.name )
    assert_equal( :plugin, target.type )
    assert_equal( %w[ source1.cpp source2.cpp ], target.sources )
    assert_equal( :shared, target.libtype )
  end
  end

  def test_parse_directory
    assert( false, "not yet implemented")
  end

end

