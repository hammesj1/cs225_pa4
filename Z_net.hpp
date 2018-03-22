////////////////////////////////////////////////////////
// CS225 Spring 2016
// Evelyn Brown
// Network Class Definition
/////////////////////////////////////////////////////////
#ifndef NETWORK_HPP
#define NETWORK_HPP

class Network
{
private:
    std::string label;      // Network label
    std::string IPaddress;  // Network IP Address
    int size;               // Network size (number of nodes)
    static int numAlive;    // number of Network objects alive

public:
    Network();              //Default Constructor
    ~Network();             //Destructor 

    int setLabel(std::string);                          //mutator method for label
    std::string getLabel() const {return label;}              //accessor method for label
    int setIPaddress(std::string);                      //mutator method for IP address
    std::string getIPaddress() const {return IPaddress;}      //accessor method for IP address
    int setSize(int);                                   //mutator method for size
    int getSize() const {return size;}                        //accessor method for size
    int setNetwork(std::string, std::string, int);      //mutator method for entire Network
    static int getNumAlive() {return numAlive;};        //accessor method for Num Alive
    int displayAllNetworks();                           //displays all the variables
    int clearAllNetworks();                             //clears all the variables
    bool isEmpty();                                     //predicate function that checks if the componenent is empty
    friend std::ostream& operator <<(std::ostream& outs, const Network& n);
};

#endif