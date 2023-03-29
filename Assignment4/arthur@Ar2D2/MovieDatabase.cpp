#include "MovieDatabase.h"
#include "Movie.h"
#include "utility.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

MovieDatabase::MovieDatabase() {
    m_loadCalled = false;
}

MovieDatabase::~MovieDatabase() {
    
}

bool MovieDatabase::load(const string& filename) { //mlogm, it's fine we iterate thru m movies and then insert 4 things but 4mlogm is mlogm
    if (m_loadCalled) {
        return false;
    }

    m_loadCalled = true;
    ifstream movieFile(filename);

    string newLine;
    string movieID;
    string title;
    string releaseDate;
    vector<string> directors;
    vector<string> actors;
    vector<string> genres;
    float rating;

    while (getline(movieFile, newLine)) {
        movieID = newLine;
        // cout << "movieID: " << movieID << endl;

        if (!getline(movieFile, newLine)) {
            movieFile.close();
            return false;
        }
        title = newLine;
        // cout << "title: " << title << endl;

        if (!getline(movieFile, newLine)) {
            movieFile.close();
            return false;
        }
        releaseDate = newLine;
        // cout << "releaseDate: " << releaseDate << endl;


        if (!getline(movieFile, newLine)) {
            movieFile.close();
            return false;
        }
        // cout << "newLine: " << newLine << endl;
        string newDirector = "";
        for (int i = 0; i < newLine.length(); i++) {
            if (newLine[i] == ',' || i == newLine.length() - 1) {
                if (i == newLine.length() - 1) 
                    newDirector += newLine[i];
                // cout << "newDirector: " << newDirector << endl;
                directors.push_back(newDirector);
                newDirector = "";
                continue;
            }

            newDirector += newLine[i];
        }
        // cout << "directors: " << endl;
        // utility::printStringVector(directors);


        if (!getline(movieFile, newLine)) {
            movieFile.close();
            return false;
        }
        string newActor = "";
        for (int i = 0; i < newLine.length(); i++) {
            if (newLine[i] == ',' || i == newLine.length() - 1) {
                if (i == newLine.length() - 1) 
                    newActor += newLine[i];
                actors.push_back(newActor);
                newActor = "";
                continue;
            }

            newActor += newLine[i];
        }
        // cout << "actors: " << endl;
        // utility::printStringVector(actors);
        // cout << endl;


        if (!getline(movieFile, newLine)) {
            movieFile.close();
            return false;
        }
        string newGenre = "";
        for (int i = 0; i < newLine.length(); i++) {
            if (newLine[i] == ',' || i == newLine.length() - 1) {
                if (i == newLine.length() - 1) 
                    newGenre += newLine[i];
                genres.push_back(newGenre);
                newGenre = "";
                continue;
            }

            newGenre += newLine[i];
        }
        // cout << "genres: " << endl;
        // utility::printStringVector(genres);
        // cout << endl;


        if (!getline(movieFile, newLine)) {
            movieFile.close();
            return false;
        }
        rating = stof(newLine);
        // cout << "rating: " << rating << endl;

        // cout << "NEW MOVIE:" << endl;
        Movie newMovie(movieID, title, releaseDate, directors, actors, genres, rating);
        // utility::printMovie(newMovie);
        tmmIDMovie.insert(movieID, newMovie);
        for (int i = 0; i < directors.size(); i++) {
            tmmDirectorMovie.insert(directors.at(i), newMovie);
        }
        for (int i = 0; i < actors.size(); i++) {
            tmmActorMovie.insert(actors.at(i), newMovie);
        }
        for (int i = 0; i < genres.size(); i++) {
            tmmGenreMovie.insert(genres.at(i), newMovie);
        }
        directors.clear();
        actors.clear();
        genres.clear();
        getline(movieFile, newLine);
    }

    movieFile.close();
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const { //logn run time, we are chilling
    if (tmmIDMovie.find(id).is_valid()) {
        return &(tmmIDMovie.find(id).get_value());
    } else {
        return nullptr;
    }
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const { //m + logd run time, search every movie 
    vector<Movie*> moviesFromDirector;
    TreeMultimap<string, Movie>::Iterator it = tmmDirectorMovie.find(director);

    while (it.is_valid()) {
        moviesFromDirector.push_back(&(it.get_value()));
        it.advance();
    }
    
    return moviesFromDirector;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const { //m + loga run time, 
    vector<Movie*> moviesWithActor;
    TreeMultimap<string, Movie>::Iterator it = tmmActorMovie.find(actor);

    while (it.is_valid()) {
        moviesWithActor.push_back(&(it.get_value()));
        it.advance();
    }
    
    return moviesWithActor;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const { //m + logg run time, 
    vector<Movie*> movieGenre;
    TreeMultimap<string, Movie>::Iterator it = tmmGenreMovie.find(genre);

    while (it.is_valid()) {
        movieGenre.push_back(&(it.get_value()));
        it.advance();
    }
    
    return movieGenre;
}
