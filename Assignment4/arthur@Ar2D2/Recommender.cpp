#include "Recommender.h"

#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database, const MovieDatabase& movie_database) {
    m_udb = &user_database;
    m_mdb = &movie_database;
}

Recommender::~Recommender() {
    
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const {
    if (movie_count <= 0) {
        vector<MovieAndRank> instaReturn;
        return instaReturn;
    }

    unordered_map<string, int> m_possibleMoviesToRecommend; //IDs and compatibility score
    User* u = m_udb->get_user_from_email(user_email);
    for (int i = 0; i < u->get_watch_history().size(); i++) {
        // cout << "curr watch history movieID: " << u->get_watch_history().at(i) << endl;

        Movie* currMovie = m_mdb->get_movie_from_id(u->get_watch_history().at(i));
        vector<Movie*> movieSameDir;
        vector<Movie*> movieSameActor;
        vector<Movie*> movieSameGenre;

        for (int d = 0; d < currMovie->get_directors().size(); d++) { //loop thru how many directors you have
            movieSameDir = m_mdb->get_movies_with_director((*currMovie).get_directors().at(d));

            for (int m = 0; m < movieSameDir.size(); m++) {
                m_possibleMoviesToRecommend[movieSameDir.at(m)->get_id()] += 20;
            }
        }

        for (int a = 0; a < currMovie->get_actors().size(); a++) {
            movieSameActor = m_mdb->get_movies_with_actor((*currMovie).get_actors().at(a));

            for (int m = 0; m < movieSameActor.size(); m++) {
                m_possibleMoviesToRecommend[movieSameActor.at(m)->get_id()] += 30;
            }
        } 

        for (int g = 0; g < currMovie->get_genres().size(); g++) {
            movieSameGenre = m_mdb->get_movies_with_genre((*currMovie).get_genres().at(g));

            for (int m = 0; m < movieSameGenre.size(); m++) {
                m_possibleMoviesToRecommend[movieSameGenre.at(m)->get_id()] += 1;
            }
        }
    }

    // for (unordered_map<string, int>:: iterator p = m_possibleMoviesToRecommend.begin(); p != m_possibleMoviesToRecommend.end(); p++) {
    //     cout << "ID: " << p->first << " | " << "score: " << p->second << endl;
    // }
    // cout << "unordered hashmap successfully populated" << endl;

    vector<MovieAndRank> allMovies; //descending order
    unordered_map<string, int>::iterator iter;
    for (iter = m_possibleMoviesToRecommend.begin(); iter != m_possibleMoviesToRecommend.end(); iter++) {
        string iterID = iter->first;
        // cout << "current iterID: " << iterID << endl;
        int iterScore = iter->second;
        MovieAndRank mAndR(iterID, iterScore);
        vector<string> tempWatchHistory = u->get_watch_history();

        if (find(tempWatchHistory.begin(), tempWatchHistory.end(), iterID) != tempWatchHistory.end()) { //alr in watch history
            // cout << iterID << " alr in watch history" << endl;
            continue;
        }

        if (allMovies.empty()) { //base case
            allMovies.push_back(mAndR);
            // cout << iterID << " first one in allMovies" << endl;
            // cout << "newAllmovies" << endl;
            // for (int gay = 0; gay < allMovies.size(); gay++) {
            //     cout << "ID: " << allMovies[gay].movie_id << " | " << "Score: " << allMovies[gay].compatibility_score << endl;
            // }
            continue;
        }
        // cout << "size of all possible movies: " << m_possibleMoviesToRecommend.size() << endl;
        for (int i = 0; i < allMovies.size(); i++) {
            // cout << "i: " << i << " | allMovies.size(): " << allMovies.size() << endl;

            if (i == allMovies.size() - 1) {
                allMovies.push_back(mAndR);
                // cout << "newAllmovies" << endl;
                // for (int gay = 0; gay < allMovies.size(); gay++) {
                //     cout << "ID: " << allMovies[gay].movie_id << " | " << "Score: " << allMovies[gay].compatibility_score << endl;
                // }
                break;
            }

            if (iterScore > allMovies[i].compatibility_score) {
                allMovies.insert(allMovies.begin() + i, mAndR);
                    // cout << "newAllmovies" << endl;
                    // for (int gay = 0; gay < allMovies.size(); gay++) {
                    //     cout << "ID: " << allMovies[gay].movie_id << " | " << "Score: " << allMovies[gay].compatibility_score << endl;
                    // }
                break;
            } else if (iterScore == allMovies[i].compatibility_score) { //we have tie
                string allMoviesID = allMovies[i].movie_id;
                Movie* iterMovie = m_mdb->get_movie_from_id(iterID);
                Movie* allMoviesMovie = m_mdb->get_movie_from_id(allMoviesID);
                // cout << "we got to this comparison" << endl;
                if (iterMovie->get_rating() > allMoviesMovie->get_rating()) {
                    // cout << "compare rating" << endl;
                    allMovies.insert(allMovies.begin() + i, mAndR);
                        // cout << "newAllmovies" << endl;
                        // for (int gay = 0; gay < allMovies.size(); gay++) {
                        //     cout << "ID: " << allMovies[gay].movie_id << " | " << "Score: " << allMovies[gay].compatibility_score << endl;
                        // }
                    break;
                } else if (iterMovie->get_rating() == allMoviesMovie->get_rating()) {
                    // cout << "compare alphabet IterID: " << iterID << " vs " << allMoviesID  << endl;
                    if (iterID.compare(allMoviesID) > 0) {
                        // cout << "trigger true vs " << allMoviesID << endl;
                        allMovies.insert(allMovies.begin() + i, mAndR);
                            // cout << "newAllmovies" << endl;
                            // for (int gay = 0; gay < allMovies.size(); gay++) {
                            //     cout << "ID: " << allMovies[gay].movie_id << " | " << "Score: " << allMovies[gay].compatibility_score << endl;
                            // }
                        break;
                    }
                }
            }
        }
        // cout << "done with currID: " << iterID << endl;
    }
    // cout << "we're done with allMovies vector bruh" << endl;
    // for (int gay = 0; gay < allMovies.size(); gay++) {
    //     cout << "ID: " << allMovies[gay].movie_id << " | " << "Score: " << allMovies[gay].compatibility_score << endl;
    // }
    // cout << "done printing" << endl;
    vector<MovieAndRank> recommendedMovies;
    for (int i = 0; i < movie_count; i++) {
        recommendedMovies.push_back(allMovies[i]);
    }
    // cout << "wait we literally returned too" << endl;
    return recommendedMovies;
}
