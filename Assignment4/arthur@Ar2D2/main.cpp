#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include "utility.h"
#include "treemm.h"
#include "Recommender.h"

#include <iostream>
#include <string>
using namespace std;

/*
//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.
*/

const string USER_DATAFILE  = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";
const string TESTUSER_DATAFILE = "usersTest.txt";
const string TESTMOVIE_DATAFILE = "moviesTest.txt";
const string CAREYUSER_DATAFILE = "careyUserTest.txt";
const string CAREYMOVIE_DATAFILE = "careyMovieTest.txt";

void findMatches(const Recommender& r, const MovieDatabase& md, const string& user_email, int num_recommendations) {
	// get up to ten movie recommendations for the user
	vector<MovieAndRank> recommendations = r.recommend_movies(user_email, num_recommendations);
	if (recommendations.empty())
		cout << "We found no movies to recommend :(.\n";
	else {
		for (int i = 0; i < recommendations.size(); i++) {
			const MovieAndRank& mr = recommendations[i]; 
			Movie* m = md.get_movie_from_id(mr.movie_id);
			cout << i + 1 << ". " << m->get_title() << " (" << m->get_release_year() << ")\n Rating: " << m->get_rating() << "\n Compatibility Score: " << mr.compatibility_score << "\n";
		}
 	}
}

int main() {
	//Make sure User works============================================================
	vector<string> sussyWatchHistory;
	sussyWatchHistory.push_back("ornnhub");
	sussyWatchHistory.push_back("cornhub");
	sussyWatchHistory.push_back("hornpub");
	User arturoZhou("Arthur Zhou", "arthuracct@gmail.com", sussyWatchHistory);
	utility::printUser(arturoZhou);

	//Make sure Movie works========================================================
	vector<string> directors;
	directors.push_back("osama bin laden");
	directors.push_back("barack obama");
	vector<string> actors;
	actors.push_back("niles elevens");
	actors.push_back("heroic worker 1");
	actors.push_back("bruhemoji123");
	vector<string> genres;
	genres.push_back("gay porn");
	genres.push_back("comedy");
	Movie tiltedTowers("42069", "Harry Potter and the Toppling Towers", "1999", directors, actors, genres, 3.69);
	utility::printMovie(tiltedTowers);

	//Make sure TreeMultiMap works====================================================
	// cout << "can you even make the class?" << endl;
	TreeMultimap<int, User> tmm;
	// cout << "TreeMultimap<int, User> made" << endl;
	User arturoZhou1("Arthur Zhou1", "arthuracct@gmail.com", sussyWatchHistory);
	User arturoZhou2("Arthur Zhou2", "arthuracct@gmail.com", sussyWatchHistory);
	User arturoZhou3("Arthur Zhou3", "arthuracct@gmail.com", sussyWatchHistory);
	User arturoZhou4("Arthur Zhou4", "arthuracct@gmail.com", sussyWatchHistory);
	User arturoZhou5("Arthur Zhou5", "arthuracct@gmail.com", sussyWatchHistory);
	User arturoZhou6("Arthur Zhou6", "arthuracct@gmail.com", sussyWatchHistory);
	User arturoZhou7("Arthur Zhou7", "arthuracct@gmail.com", sussyWatchHistory);
	User arturoZhou8("Arthur Zhou1 clone", "arthuracct@gmail.com", sussyWatchHistory);
	User arturoZhou9("Arthur Zhou1 another clone", "arthuracct@gmail.com", sussyWatchHistory);
	// cout << "Users made" << endl;
	tmm.insert(5, arturoZhou5);
	tmm.insert(3, arturoZhou3);
	tmm.insert(1, arturoZhou1);
	tmm.insert(2, arturoZhou2);
	tmm.insert(7, arturoZhou7);
	tmm.insert(4, arturoZhou4);
	tmm.insert(6, arturoZhou6);
	tmm.insert(1, arturoZhou8);
	tmm.insert(1, arturoZhou9);
	// cout << "Users inserted" << endl;
	TreeMultimap<int, User>::Iterator iter = tmm.find(1);
	TreeMultimap<int, User>::Iterator iter1 = tmm.find(7);
	TreeMultimap<int, User>::Iterator iter2 = tmm.find(9);
	// cout << "iterator made" << endl;
	cout << "ITER WITH MULTIPLE ITEMS: " << endl;
	utility::printIterForIntUser(iter);
	cout << "ITER WITH ONE ITEM: " << endl;
	utility::printIterForIntUser(iter1);
	cout << "ITER THAT DOESN'T EXIST" << endl;
	utility::printIterForIntUser(iter2);
	cout << "\n";
	/* PRINT TREE
	cout << "tmm in pre-order traversal: " << endl;
	utility::printTreeIntUser(tmm.m_rootPtr);
	*/

	//Make sure UserDatabase works====================================================
	UserDatabase udb;
	cout << "Did file successsfully load? " << (udb.load(TESTUSER_DATAFILE)? "Yes" : "No") << endl;
	for (;;)
	{
		cout << "Enter user email address (or quit): ";
		string email;
		getline(cin, email);
		if (email == "quit")
			break;
		User* u = udb.get_user_from_email(email);
		if (u == nullptr) {
			cout << "No user in the database has that email address." << endl;
		} else {
			utility::printUser(*u);
		}
	}

	//Make sure MovieDatabase works====================================================
	MovieDatabase mdb;
	cout << "Did file successsfully load? " << (mdb.load(TESTMOVIE_DATAFILE)? "Yes" : "No") << endl;
	for (;;) {
		cout << "Enter movie ID (or quit): ";
		string movieID;
		getline(cin, movieID);
		if (movieID == "quit") 
			break;
		Movie* movieFromID = mdb.get_movie_from_id(movieID);
		if (movieFromID == nullptr) {
			cout << "No movie in the database has that ID." << endl;
		} else {
			utility::printMovie(*movieFromID);
		}
	}
	for (;;) {
		cout << "Enter director name (or quit): ";
		string movieDir;
		getline(cin, movieDir);
		if (movieDir == "quit") 
			break;
		vector<Movie*> movieFromDir = mdb.get_movies_with_director(movieDir);
		if (movieFromDir.size() == 0) {
			cout << "No movie in the database has that director." << endl;
		} else {
			for (int i = 0; i < movieFromDir.size(); i++) {
				utility::printMovie(*movieFromDir[i]);
			}
		}
	}
	for (;;) {
		cout << "Enter actor name (or quit): ";
		string movieActor;
		getline(cin, movieActor);
		if (movieActor == "quit") 
			break;
		vector<Movie*> movieWithActor = mdb.get_movies_with_actor(movieActor);
		if (movieWithActor.size() == 0) {
			cout << "No movie in the database has that actor." << endl;
		} else {
			for (int i = 0; i < movieWithActor.size(); i++) {
				utility::printMovie(*movieWithActor[i]);
			}
		}
	}
	for (;;) {
		cout << "Enter genre (or quit): ";
		string movieGenre;
		getline(cin, movieGenre);
		if (movieGenre == "quit") 
			break;
		vector<Movie*> movieWithGenre = mdb.get_movies_with_genre(movieGenre);
		if (movieWithGenre.size() == 0) {
			cout << "No movie in the database has that genre." << endl;
		} else {
			for (int i = 0; i < movieWithGenre.size(); i++) {
				utility::printMovie(*movieWithGenre[i]);
			}
		}
	}

	//Make sure Recommender works====================================================
	UserDatabase careyPleaseWork;
	MovieDatabase careyPleaseWorkMovies;
	cout << "Did file successsfully load? " << (careyPleaseWork.load(CAREYUSER_DATAFILE)? "Yes" : "No") << endl;
	cout << "Did file successsfully load? " << (careyPleaseWorkMovies.load(CAREYMOVIE_DATAFILE)? "Yes" : "No") << endl;

	Recommender r(careyPleaseWork, careyPleaseWorkMovies);
	findMatches(r, careyPleaseWorkMovies, "climberkip@gmail.com", 5);
	cout << "WERE FUCKIGN DONE!!!!" << endl;
}
