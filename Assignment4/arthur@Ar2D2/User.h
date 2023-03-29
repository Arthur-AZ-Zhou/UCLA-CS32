#ifndef USER_INCLUDED
#define USER_INCLUDED

#include <string>
#include <vector>

class User {
    public:
        //constructor and destructor
        User(const std::string& full_name, const std::string& email, const std::vector<std::string>& watch_history);
        ~User();
        std::string get_full_name() const;
        std::string get_email() const;  
        std::vector<std::string> get_watch_history() const; //RETURNS VECTOR OF IDS

    private:
        std::string m_full_name;
        std::string m_email;
        std::vector<std::string> m_watch_history;
};

#endif // USER_INCLUDED
