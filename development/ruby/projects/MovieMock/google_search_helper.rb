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
#

require 'rubygems'
require 'googleajax'

GoogleAjax.referer = "somesite.com"


class GoogleSearchHelper

  def self.get_first_url_for(search_query)
    res = GoogleAjax::Search.web(search_query, { "rsz" => 1 } )
    res[:results][0][:unescaped_url]  # yes it's that simple!
  end

end

