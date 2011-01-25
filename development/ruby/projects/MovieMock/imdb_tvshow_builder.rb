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
require 'imdb_search_helper'
require 'nokogiri_helper'


module Imdb


class TVShowBuilder

  def build_tvshow(showname)
    show = create_new_tvshow(showname)
    doc = create_nokogiri_doc(
        SearchHelper.get_tvshow_episode_list_url(showname))
    set_show_data(show, doc)
    show
  end

  private
  def create_new_tvshow(showname)
    show = TVShow.new(showname)
    show.url = SearchHelper.get_tvshow_url(showname)
    show
  end

  def set_show_data(show, doc)
    set_show_year(show, doc)
    add_episodes(show, doc)
  end

  def set_show_year(show, doc)
    title = doc.xpath("//html/head/title")[0].to_str
    title =~ /.*\(([\d]*)\)/
    show.year = $1
  end

  def add_episodes(show, doc)
    doc.css("div.season-filter-all").each do |season_elem|
      puts "---Adding season"
      season_elem.xpath("div/table/tr/td[2]").each do |episode_elem|
        #puts "---Adding episode"
        add_episode_to_show(show, episode_elem)
      end
    end
  end

  def add_episode_to_show(show, elem)
    ep = TVShowEpisode.new
    set_episode_header_data(ep, elem)
    set_episode_airdate(ep, elem)
    set_episode_summary(ep, elem)
    set_episode_url(ep, elem)

    show.add_episode(ep)
  end

  def set_episode_header_data(episode, elem)
    get_episode_head_string(elem) =~ /Season ([\d]*), Episode ([\d]*): (.*)/
    episode.season = $1
    episode.episode = $2
    episode.title = $3
  end

  def get_episode_head_string(elem)
    elem.xpath("h3")[0].to_str
  end

  def set_episode_airdate(episode, elem)
    episode.airdate = elem.xpath("span/strong")[0].to_str
  end

  def set_episode_summary(episode, elem)
    str = elem.to_html
    str =~ /<\/strong>.*<\/span>.*<br> (.*)<\/td>/
    episode.summary = $1
  end

  def set_episode_url(episode, elem)
    elem.xpath("h3/a").to_html =~ /href="(.*)"/
    episode.url = "http://www.imdb.com" + $1
  end

  def create_nokogiri_doc(url)
    NokogiriHelper.create_doc_from_url(url)
  end

end


end  # module Imdb

