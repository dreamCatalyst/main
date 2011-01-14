#
#
#

require 'test/unit'
require 'cmake_parser'


FixtureDirectory = "unit-tests/fixtures/cmake_parser"


class TestCMakeParser < Test::Unit::TestCase
  FilesThatShouldParse = [
    :simple_cmake, :empty_cmake,
    :complex_string, :complex_string2, :complex_string3,
    :complex_comment,
    :simple_variables, :complex_variables,
    :executable_targets, :library_targets,
    :kde_targets
  ]
  FilesThatShouldNotParse = [ :open_paren, :open_string ]

  @@init_done = false

  def setup
    delayed_initialize unless @@init_done
  end

  def delayed_initialize
    @@init_done = true
    @@parser_results = {}
    @@parser = CMakeParser.new
    parse_files
  end

  def parse_files
    FilesThatShouldParse.each do |s| parse_file(s, true) end
    FilesThatShouldNotParse.each do |s| parse_file(s, false) end
  end

  def parse_file(symbol, success_expected)
    filename = get_filename_for_symbol(symbol)
    if success_expected
      verify_file_parses(filename)
    else
      verify_file_does_not_parse(filename)
    end
    @@parser_results[ symbol ] = @@parser.result
  end

  def verify_file_parses(filename)
    assert_not_nil( @@parser.parse( filename ), "Expected '#{filename}' to parse")
    assert( !@@parser.has_error() )
  end

  def verify_file_does_not_parse(filename)
    assert_nil( @@parser.parse( filename ), "Expected '#{filename}' not to parse")
    assert( @@parser.has_error() )
  end

  def get_filename_for_symbol(file_sym)
    "#{FixtureDirectory}/#{file_sym}.txt"
  end

  # ---------------------------------------------- Testing the content

  def test_parse_non_existing_file
    assert_nil( @@parser.parse("non-existing-file") )
    assert( @@parser.has_error() )
  end

  def test_simple_variables
    vars = @@parser_results[:simple_variables].variables
    verify_variables( vars, {
      "Var1" => %w[ a b c ],
      "Var2" => %w[ D E F ],
      "Var3" => %w[ 1 2 3 ]
    })
  end

  def test_complex_variables
    vars = @@parser_results[:complex_variables].variables
    verify_variables( vars, {
      "Var1" => %w[ a b c ],
      "Var2" => %w[ d e f ],
      "Var3" => %w[ a b c d e f ]
    })
  end

  def verify_variables(variables, expected)
    variables.each do |variable|
      assert( expected.has_key?(variable.name) )
      assert_equal( expected[variable.name], variable.values )
    end
  end

  def test_executable_targets
    targets = @@parser_results[:executable_targets].targets
    assert_equal( 2, targets.size, "Incorrect number of targets parsed")

    verify_target( targets[0],
        "Target1", :executable, "", %w[ main.cpp some_file.cpp ] )
    verify_target( targets[1],
        "Target2", :executable, "", %w[ main.cpp some_file.cpp ] )
  end

  def test_library_targets
    targets = @@parser_results[:library_targets].targets
    assert_equal( 4, targets.size, "Incorrect number of targets parsed")

    verify_target( targets[0], 
        "Target1", :library, :shared, %w[ main.cpp some_file.cpp ] )
    verify_target( targets[1],
        "Target2", :library, :static, %w[ main.cpp some_file.cpp ] )
    verify_target( targets[2],
        "Target3", :library, :module, %w[ main.cpp some_file.cpp ] )
    verify_target( targets[3],
        "Target4", :library, :shared, %w[ main.cpp some_file.cpp ] )
  end

  def test_kde_targets
    targets = @@parser_results[:kde_targets].targets
    assert_equal( 3, targets.size, "Incorrect number of targets parsed")

    verify_target( targets[0], 
        "Target1", :library, :shared, %w[ main.cpp some_file.cpp ] )
    verify_target( targets[1],
        "Target2", :plugin, "", %w[ main.cpp some_file.cpp ] )
    verify_target( targets[2],
        "Target3", :executable, "", %w[ main.cpp some_file.cpp ] )
  end

  def verify_target(target, name, type, libtype, sources)
    assert_equal( name, target.name )
    assert_equal( type, target.type )
    assert_equal( libtype, target.libtype )
    assert_equal( sources, target.sources )
  end

  CMakeTestDirectory = "#{FixtureDirectory}/complex_dir"

  def test_parse_directory
    result = @@parser.parse(CMakeTestDirectory)
    assert_not_nil(result, "Did not parse directory")
    assert_equal(3, result.subdirectories.size, 
        "Incorrect number of subdirectories parsed")
    assert_equal( %w[ subdir1 subdir2 subdir3 ], result.subdirectories )
  end

end

