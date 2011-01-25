#
#
#

require 'imdb_model_classes'
require 'google_search_helper'
require 'nokogiri_helper'
require 'mm_cache'


module Imdb

class MovieBuilder

  def build_movie(movie_name, year = 0)
    movie = Movie.new(movie_name)
    movie.url = GoogleSearchHelper.get_first_url_for(
      "site: imdb.com #{movie_name} #{ (year==0)? '': year }")
    set_movie_data(movie)
    movie
  end

  private
  def set_movie_data(movie)
    doc = NokogiriHelper::create_doc_from_url(movie.url)

    title = doc.css("h1.header")[0].text
    movie.title = title[1..(title.index("\n\n"))]
    title =~ /\(([\d]+)\)/
    movie.year = $2

    movie.cover_url = doc.css("td#img_primary a img")[0].attributes["src"].value 
  end
end

end

