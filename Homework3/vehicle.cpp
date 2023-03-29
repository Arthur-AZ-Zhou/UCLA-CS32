#include <iostream>
#include <string>
using namespace std;

class Vehicle {
    public: 
        //constructor
        Vehicle(string id) {
            m_id = id;
        }

        //destructor
        virtual ~Vehicle() = 0;

        //getters
        string id() const {
            return m_id;  
        }

        virtual string description() const = 0;

        virtual bool canHover() const {
            return true;
        }

    private:
        string m_id;
};

Vehicle::~Vehicle() {}; //gay piece of shit

class Drone: public Vehicle {
    public:
        Drone(string id) : Vehicle(id) {
            
        }

        virtual ~Drone() {
            cout << "Destroying " + id() + ", a drone" << endl;
        }

        virtual string description() const {
            return "a drone";
        }

    private: 

};

class Balloon: public Vehicle {
    public:
        Balloon(string id, int diameter) : Vehicle(id) {
            m_diameter = diameter;
        }

        virtual ~Balloon() {
            cout << "Destroying the balloon " << id() << endl; 
        }

        virtual string description() const {
            string balloonSize = (m_diameter < 8)? "small balloon" : "large balloon";
            return "a " + balloonSize;
        }

    private:
        int m_diameter;
};

class Satellite: public Vehicle {
    public:
        Satellite(string id) : Vehicle(id) {
            
        }

        virtual ~Satellite() {
            cout << "Destroying the satellite " << id();
        }

        virtual string description() const {
            return "a satellite";
        }

        virtual bool canHover() const {
            return false;
        }

    private:

};

// void display(const Vehicle* v) {
//     cout << v->id() << " is " << v->description();
//     if (v->canHover()) {
//         cout << ", so it can hover";
//     }
//     cout << endl;
// }

// int main() {
//     Vehicle* fleet[4];
//     fleet[0] = new Drone("CB4UP");
//       // Balloons have an id and a diameter in meters  Balloons with a
//       // diameter under 8 meters are small balloons; those with a diameter
//       // 8 meters or more are large balloons
//     fleet[1] = new Balloon("99LB", 6.3);
//     fleet[2] = new Balloon("CN20230201", 30.2);
//     fleet[3] = new Satellite("EB8675309");

//     for (int k = 0; k < 4; k++) {
//         display(fleet[k]);
//     }

//       // Clean up the vehicles before exiting
//     cout << "Cleaning up" << endl;
//     for (int k = 0; k < 4; k++) {
//         delete fleet[k];
//     }
// }