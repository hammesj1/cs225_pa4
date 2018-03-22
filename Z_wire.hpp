///////////////////////////////////////////////////////////////////////////////////////////////////////////
// CS225 Spring 2016
// Evelyn Brown
// Wireless Router Class Definition
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef WIRELESSROUTER_HPP
#define WIRELESSROUTER_HPP


#include "packetswitch.hpp"

class WirelessRouter:public PacketSwitch
{
  private:
  static int numAlive;      //Used to track the number of objects alive
  int packetSize;           //The size of the packet in bytes
  std::string ieeeStd;      //The IEEE standard
  double dataRate;          //The data rate
  
  public:
  WirelessRouter();                               //Default Constructor
  WirelessRouter(const WirelessRouter& );         //Copy Constructor
  ~WirelessRouter();                              //Destructor
  
  static int getNumAlive() {return numAlive; }    //Method that returns numAlive
  int setPacketSize(int);                         //Mutator method for packetSize
  int getPacketSize() const {return packetSize; } //Accessor method for packetSize
  int setIeeeStd(std::string);                    //Mutator method for ieeeStd
  std::string getIeeeStd() const{return ieeeStd;} //Accessor method for ieeeStd
  int setDataRate(double);                        //Mutator method for dataRate
  double getDataRate() const {return dataRate; }  //Accessor method for dataRate
  virtual int computePacketsPerSecond();          //Virtual method for computing the packets per second
  int isEmptyWireless();                          //Boolean function that tells whether or not the object is empty
  static int getNumAliveWireless() {return numAlive;} //Returns the number of Wireless Routers alive
  int clearAll();                                     //Redefining the clearAll() function
  friend std::ostream& operator <<(std::ostream& outs, const WirelessRouter&);//friend function to overload the << operator
  
};

#endif