
require 'test/unit'

class TestLoadingExtension < Test::Unit::TestCase

  def test_load_extension
    begin
      require 'jmdb_ruby'
      assert(true, 'Extension loaded successfully')
    rescue LoadError
      assert(false, 'Extension could not be loaded')
    end
  end

  def test_module_is_defined
    assert(Module.constants.include?("Jmdb_ruby"), "module Jmdb_ruby is defined");
  end

  def test_module_has_all_classes
    assert(Jmdb_ruby.constants.include?("Field"), "the Field class is defined");
    assert(Jmdb_ruby.constants.include?("StringField"), "the StringField class is defined");
    assert(Jmdb_ruby.constants.include?("IntField"), "the IntField class is defined");
    assert(Jmdb_ruby.constants.include?("RealField"), "the RealField class is defined");
    assert(Jmdb_ruby.constants.include?("BinaryDataField"), "the BinaryDataField class is defined");
  end

end

