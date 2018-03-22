////////////////////////////////////////////////////////
// CS225 Spring 2016
// Evelyn Brown
// Component Class Definition
/////////////////////////////////////////////////////////
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class Component
{
private:
    std::string name;
    double powerRating;  // power rating 
    double price;        // price of component
    static int numAlive; // number of PacketSwitch objects alive

public:
    Component();              //Default Constructor
    ~Component();             //Destructor 

    int setName(std::string);                                //mutator method for name
    std::string getName() const {return name;}               //accessor method for name
    int setPowerRating(double);                              //mutator method for powerRating
    double getPowerRating() const {return powerRating;}      //accessor method for powerRating
    int setPrice(double);                                    //mutator method for price
    double getPrice() const {return price;}                  //accessor method for price
    int setComponent(std::string, double, double);           //mutator method for entire component
    static int getNumAlive() {return numAlive;};             //accessor method for Num Alive
    int displayAllComponents();
    int clearAllComponents();
    bool isEmpty() const;                                    //predicate function that checks if the componenent is empty
    friend std::ostream& operator <<(std::ostream& outs, const Component& c);  //Overloaded operator << function
};

#endif