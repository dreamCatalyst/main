#
#
#

require 'singleton'
require 'url_disk_cache'
require 'directory_helper'


class MovieMockUrlDiskCache
  include Singleton

  def initialize
    data_dir = DirectoryHelper.get_user_home() + "/.moviemock/cache"
    @backend = UrlDiskCache.new(data_dir)
  end

  def get_url_content(url)
    @backend.get_url_content(url)
  end

  def get_url_file(url)
    @backend.get_url_file(url)
  end
end

