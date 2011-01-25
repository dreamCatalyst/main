#
#
#

require 'yaml'
require 'http_helper'

class CacheEntry
  attr_accessor :url, :filename, :creation_date, :expiration_date
end

class UrlDiskCache
  def initialize(directory)
    @directory = directory
    Dir.mkdir(@directory) unless File.directory?(@directory)
    @cache = {}
    read_cache_from_disk
  end

  def write_cache_to_disk
    open( cache_file(), "w" ) do |file|
      file << @cache.to_yaml
    end
  end

  def get_file_for_url(url)
    return @cache[url].filename if @cache.has_key?(url)
    fn = @directory + "/" + generate_random_filename
    begin
      exp_date = HttpHelper::perform_download( url, fn )
      cache_entry = CacheEntry.new
      cache_entry.url = url
      cache_entry.filename = fn
      cache_entry.creation_date = Time.now
      #cache_entry.expiration_date = exp_date
      @cache[url] = cache_entry
      return fn

    rescue Exception => e
      puts "An error occurred while retrieving '#{url}'"
      puts "Exception message: '#{e.message}'"
    end
    return nil
  end
  
  private
  def cache_file
    "#{@directory}/image_url_cache.yaml"
  end

  def read_cache_from_disk
    @cache = YAML::load_file( cache_file() ) if File.exist?(cache_file())
  end

  def generate_random_filename
    fn = (0...8).map{65.+(rand(25)).chr}.join
    return generate_random_filename if File.exist?( "#{@directory}/#{fn}" )  # unlikely, but just to be sure
    return fn
  end
end

