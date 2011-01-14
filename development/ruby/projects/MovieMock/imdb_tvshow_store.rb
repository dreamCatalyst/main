# Copyright 2011 Jonathan Maasland <nochoice AT xs4all DOT nl>
#
# This file is part of MovieMock.
#
# MovieMock is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# MovieMock is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with MovieMock.  If not, see <http://www.gnu.org/licenses/>

module Imdb


class TVShowStore
  def initialize
    @backend = TVShowStoreBackend.instance
  end

  def get_tvshow(showname)
    @backend.get_tvshow(showname)
  end
end


class TVShowStoreBackend
  def self.instance
    @@instance ||= new
  end

  def get_tvshow(showname)
  end

  def save_to_disk
  end

  protected
  def initialize
    @storage = { }
    load_from_disk
  end

  def load_from_disk
    return unless storage_file_exists?()
    @storage = YAML::load_file( storage_file() )
  end

end


end

