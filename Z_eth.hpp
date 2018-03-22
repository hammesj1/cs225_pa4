////////////////////////////////////////////////////////
// CS225 Spring 2016
// Evelyn Brown
// Ethernet Switch Class Definition
/////////////////////////////////////////////////////////
#ifndef ETHERNETSWITCH_HPP
#define ETHERNETSWITCH_HPP

#include "packetswitch.hpp"

class EthernetSwitch:public PacketSwitch
{
  private:
  static int numAlive; //Used to track the number of objects alive
  int packetSize;      //The size of the packet in bytes
  int rating;          //The rating of the packet
  
  public:
  EthernetSwitch();                               //Default Constructor
  EthernetSwitch(const EthernetSwitch& );         //Copy Constructor
  ~EthernetSwitch();                              //Destructor
  
  static int getNumAlive() {return numAlive; }    //Method that returns numAlive
  int setPacketSize(int);                         //Mutator method for packetSize
  int getPacketSize() const {return packetSize; } //Accessor method for packetSize
  int setRating(int);                             //Mutator method for rating
  int getRating() const {return rating; }         //Accessor method for rating
  virtual int computePacketsPerSecond();          //Virtual method for computing the packets per second
  int isEmptyEthernet();                          //bool method that returns true if the object is empty
  int clearAll();                                 //redefining the clearAll function
  static int getNumAliveEthernet() {return numAlive;} //getting the number of Ethernet Switches that are alive
  friend std::ostream& operator <<(std::ostream& outs, const EthernetSwitch&); //Overloaded insertion operator
  
};

#endif