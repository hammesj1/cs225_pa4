/////////////////////////////////////////////////////////////////////////////////////////
// CS225 Spring 2016
// Evelyn Brown
// Ethernet Switch Class Implementation
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef ETHERNETSWITCH_CPP
#define ETHERNETSWITCH_CPP

#include <string>
#include <iostream>
#include "ethernetswitch.hpp"

const int defaultPacketSize = 0;
const int defaultRating = 0;

//Initializing numAlive
int EthernetSwitch::numAlive = 0;

//Default Constructor
EthernetSwitch::EthernetSwitch()
{
  packetSize = defaultPacketSize;
  rating = defaultRating;
  numAlive++;
}

//Copy Constructor
EthernetSwitch::EthernetSwitch(const EthernetSwitch& es)
{
  packetSize = es.packetSize;
  rating = es.rating;
  numAlive++;
}

//Destructor
EthernetSwitch::~EthernetSwitch() { numAlive--; }

//Virtual function for computing the packets per second
int EthernetSwitch::computePacketsPerSecond()
{
  int portSpeed = getPPS();
  int numPorts = getNumPorts();
  int packetsPerSecond;
  packetsPerSecond = (portSpeed * numPorts) / (8 * packetSize);
  std::cout << "The packets per second rate is: " << packetsPerSecond << " (bytes/sec)" << std::endl;
  return 0;
}
  
//Function to set packetSize
int EthernetSwitch::setPacketSize(int ps)
{
  packetSize = ps;
  return 0;
}

//Function to set rating
int EthernetSwitch::setRating(int r)
{
  rating = r;
  return 0;
}

//Function to see if the ethernet object is empty
int EthernetSwitch::isEmptyEthernet()
{
  bool state = true;
  state = PacketSwitch::isEmpty();
  if(packetSize != defaultPacketSize)
    state = false;
  if(rating != defaultRating)
    state = false;
  return state;
}

//Function to redefine the clear all packet switch function
int EthernetSwitch::clearAll()
{
  PacketSwitch::isEmpty();
  setPacketSize(defaultPacketSize);
  setRating(defaultRating);
  return 0;
}

//Overloaded << operator function
std::ostream& operator <<(std::ostream& outs, const EthernetSwitch& es)
{
  outs << "Packet Switch Vendor             : " << es.getVendor() << std::endl
       << "Packet Switch Model              : " << es.getModel() << std::endl
       << "Number of Ports in Packet Switch : " << es.getNumPorts() << std::endl
       << "Per-port Speed                   : " << es.getPPS() << std::endl
       << "Power in Watts                   : " << es.getPower() << std::endl
       << "Dimensions (HxWxD)               : " << es.getHeight() << " x " << es.getWidth() << " x " << es.getDepth() << std::endl
       << "Packet Size                      : " << es.getPacketSize() << std::endl
       << "Rating                           : " << es.getRating() << std::endl;

  // Network portion of print out
  outs << "Connected Network Details:" << std::endl
       << "--------------------------" << std::endl;
  
  if(((es.getNetwork())) != NULL)
    outs << *(es.getNetwork()) << std::endl;
    
  // Component details 
  outs << "Component Details: " << std::endl
       << "Component#     Name          Power (Watts)       Price ($) " << std::endl
       << "----------     --------      ---------------     ----------" << std::endl;
  
  //For loop for array of components belonging to each packet switch
  int i;
  for (i = 0; i < 20; i++)  //iterate through the loop of components
  {
    if(!(es.getComponentPtr()+i)->isEmpty())
      outs << "    "  << i << "          " << *(es.getComponentPtr() + i);
  } 
  
  es.componentPowerConsumption();
  
  
  return outs;
}


#endif