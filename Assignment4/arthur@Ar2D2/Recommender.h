#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "User.h"

#include <string>
#include <vector>
#include <set>
#include <unordered_map>

class UserDatabase;
class MovieDatabase;

struct MovieAndRank {
    MovieAndRank(const std::string& id, int score) : movie_id(id), compatibility_score(score) {
        
    }

    std::string movie_id;
    int compatibility_score;
};

class Recommender {
    public:
        Recommender(const UserDatabase& user_database, const MovieDatabase& movie_database);
        ~Recommender();
        std::vector<MovieAndRank> recommend_movies(const std::string& user_email, int movie_count) const;

    private:
        const UserDatabase* m_udb;
        const MovieDatabase* m_mdb;
};

#endif // RECOMMENDER_INCLUDED
