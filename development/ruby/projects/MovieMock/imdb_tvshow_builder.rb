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


###################################################
#
#                       *
#                      / \
#                     /   \
#                    /  _  \
#           /\      /  (_)  \      /\
#          /  \    /         \    /  \
#          |  |   /           \   |  |
#       /\ |  |   |           |   |  | /\
#      /  \|  |   |           |   |  |/  \
#     /____\  |   |    ___    |   |  /____\
#     |    |__|___|   /   \   |___|__|    |
#     |    |         Y     Y         |    |
#     |    |         |     |         |    |
#     |____|_________|     |_________|____|
#                    /=====/
#                   /*****/
#                  /*****/
#                  \*****\
#                   \*****\
#                    \*****\
#                     \*****\
#                      |*****|
#                      |*****|
#                      |*****|
#                      |*****|
#
#                  Ah yes Dorothy,
#     you've finally arrived at the wizard's castle
#
#
###################################################


require 'imdb_model_classes'
require 'nokogiri_helper'


module Imdb


class TVShowBuilder

  def build_show_from_url(showname, url)
    show = create_new_show(showname, url)
    doc = create_nokogiri_doc(url)
    set_show_data(show, doc)
    show
  end

  private
  def set_show_data(show, doc)
    set_show_year(show, doc)
    add_episodes(show, doc)
  end

  def create_new_show(showname, url)
    show = TVShow.new(showname)
    show.url = url
    show
  end

  def set_show_year(show, doc)
    title = doc.xpath("//html/head/title")[0].to_str
    if !(title =~ /.*\(([\d]*)\)/)
      puts "\n--Parsing error: title doesn't match expectation"  # again log this instead
      return
    end

    show.year = $1
  end

  def add_episodes(show, doc)
    first = true
    doc.xpath("//div/div[2]/layer/div[2]/div/div/div[2]/div").each do |season_elem|
      (first = false ; next ) if first
      season_elem.xpath("div/table/tr/td[2]").each do |episode_elem|
        add_episode_to_show(show, episode_elem)
      end
    end
  end

  def add_episode_to_show(show, elem)
    get_episode_head_string(elem) =~ /Season ([\d]*), Episode ([\d]*): (.*)/
    ep = TVShowEpisode.new
    ep.season = $1
    ep.episode = $2
    ep.title = $3
    ep.airdate = get_airdate(elem)
    ep.summary = get_summary(elem)
    show.add_episode(ep)
  end

  def get_episode_head_string(elem)
    elem.xpath("h3")[0].to_str
  end

  def get_airdate(elem)
    elem.xpath("span/strong")[0].to_str
  end

  def get_summary(elem)
    str = elem.to_html
    str =~ /<\/strong>.*<\/span>.*<br> (.*)<\/td>/
    $1
  end

  def create_nokogiri_doc(url)
    NokogiriHelper.create_doc_from_url(url)
  end

end


end  # module Imdb

