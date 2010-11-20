# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
# 00_test_loading_extension - Tests to check if the compiled extension loads

require 'test/unit'

class TestLoadingExtension < Test::Unit::TestCase

  def test_load_extension
    begin
      require 'jmutil_ruby'
      assert(true, 'Extension loaded successfully')
    rescue LoadError
      assert(false, 'Extension could not be loaded')
    end
  end

  def test_module_is_defined
    assert(Module.constants.include?("Jmutil_ruby"), "module Jmutil_ruby is defined");
  end

  def test_module_has_all_classes
    assert(Jmutil_ruby.constants.include?("FileUtils"), "the FileUtils class is defined");
  end

end
