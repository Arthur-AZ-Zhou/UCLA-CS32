#include "utility.h"

void utility::printStringVector(const vector<string>& printVector) {
    for (int i = 0; i < printVector.size(); i++) {
		cout << printVector[i] << endl;
	}
}

void utility::printUser(const User& user) {
    cout << "USERNAME: " << user.get_full_name() << " | EMAIL: " << user.get_email() << endl;
    cout << "WATCH HISTORY: " << endl;
    printStringVector(user.get_watch_history());
    cout << "\n";
}

void utility::printMovie(const Movie& movie) {
    cout << "ID: " << movie.get_id() << " | TITLE: " << movie.get_title() 
        << " | RELEASE DATE: " << movie.get_release_year() << " | RATING: " << movie.get_rating() << endl;
    cout << "DIRECTORS: " << endl;
    printStringVector(movie.get_directors());
    cout << "ACTORS: " << endl;
    printStringVector(movie.get_actors());
    // cout << "WHY DO I OH BABY WHY DO I" << endl;
    cout << "GENRES: " << endl;
    printStringVector(movie.get_genres());
    cout << "\n";
}

/*void utility::printTreeIntUser(TreeMultimap<int, User>::BTNODE *cur) {
    if (cur == nullptr) {
        return;
    }

    cout << cur->kt << " ";
    printTreeIntUser(cur->left);
    printTreeIntUser(cur->right);
}*/

void utility::printIterForIntUser(TreeMultimap<int, User>::Iterator& it) {
    while (it.is_valid()) {
        cout << it.get_value().get_full_name() << endl;
        it.advance();
    }
}