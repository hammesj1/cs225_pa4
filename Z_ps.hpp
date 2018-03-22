///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CS225 Spring 2016
// Evelyn Brown
// Packet Switch Class Definition
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PACKETSWITCH_HPP
#define PACKETSWITCH_HPP

#include "network.hpp"
#include "component.hpp"

class PacketSwitch
{
private:
    std::string vendor;
    std::string model;
    int numPorts;
    double pps;              // per port speed in Mbps
    double power;            // power consumption in Watts
    static int numAlive;     // number of PacketSwitch objects alive
    double packetsPerSecond; //to store the packets per second
    struct dimentions        // physical dimentions of the packetswitch
    {
       float height;
       float width;
       float depth;
    } sizeInInches;
    
    Network* n1 = NULL;
    Component c[20];
        
public:
    PacketSwitch();              //Default Constructor
    PacketSwitch(std::string, std::string, int, double, double, float, float, float, Network*, Component); // Overloaded Constructor
    virtual ~PacketSwitch();             //Destructor 

    //Mutatator Methods 
    int setVendor(std::string);                                      //mutator method for vendor
    int setModel(std::string);                                       //mutator method for model
    int setNumPorts(int);                                            //mutator method for numPorts
    int setPPS(double);                                              //mutator method for PPS
    int setPower(double);                                            //mutator method for Power
    int setDimensions(float, float, float);                          //mutator method for Size in Inches
    int setNetwork(Network*);                                        //mutator method for Network
 
    //Accessor Methods
    std::string getVendor() const { return vendor; };                //accessor method for vendor
    std::string getModel() const { return model; };                  //accessor method for model
    int getNumPorts() const  { return numPorts; };                   //accessor method for numPorts
    int getPPS() const { return pps; };                              //accessor method for PPS
    int getPower() const { return power; };                          //accessor method for Power
    float getHeight() const { return sizeInInches.height;};          //accessor method for height
    float getWidth() const { return sizeInInches.width;};            //accessor method for width
    float getDepth() const { return sizeInInches.depth;};            //accessor method for depth
    Network* getNetwork() const {return n1;};                        //accessor method for network pointer
    const Component* getComponentPtr() const {return c;};            //accessor method for component pointer
    static int getNumAlive() { return numAlive;};                    //accessor method for Num Alive
    std::string getNetworkLabel(){return n1->getLabel();}            //accessor method for Network Label
    std::string getNetworkIPAddress(){return n1->getIPaddress();}    //accessor method for Network IP address
    double getNetworkSize() {return n1->getSize();}                  //accessor method for Network Size
    Component& getComponent(int);                                    //accessor method for component specified by parameter

    //Other Methods
    int displayAll();                                                //method that displays all the class variables
    int clearAll();                                                  //method that sets all class variables back to default
    int componentPowerConsumption() const;                           //power consumption of components
    friend std::ostream& operator <<(std::ostream& outs, const PacketSwitch& ps);//friend function to overload the << operator
    bool isEmpty();                                                  //method that returns true if the object is empty
    virtual int computePacketsPerSecond();                           //method that computes the packets per second
    
protected:
    double thermalOutput();                                          //Protected method that computes the thermal output  
    
};

#endif