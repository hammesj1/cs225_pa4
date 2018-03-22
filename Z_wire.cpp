/////////////////////////////////////////////////////////////////////////////////////////
// CS225 Spring 2016
// Evelyn Brown
// Wireless Router Class Implementation
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef WIRELESSROUTER_CPP
#define WIRELESSROUTER_CPP

#include <string>
#include <iostream>
#include "wirelessrouter.hpp"

const int defaultPacketSize = 0;
const double defaultDataRate = 0;
const std::string defaultIeeeStd = "";

  
//Initializing numAlive
int WirelessRouter::numAlive = 0;

//Default Constructor
WirelessRouter::WirelessRouter()
{
  packetSize = defaultPacketSize;
  ieeeStd = defaultIeeeStd;
  dataRate = defaultDataRate;
  numAlive++;
}

//Copy Constructor
WirelessRouter::WirelessRouter(const WirelessRouter & wr)
{
  packetSize = wr.packetSize;
  ieeeStd = wr.ieeeStd;
  dataRate = wr.dataRate;
  numAlive++;
}

//Destructor
WirelessRouter::~WirelessRouter() { numAlive--; }

//Function to set packetSize
int WirelessRouter::setPacketSize(int ps)
{
  packetSize = ps;
  return 0;
}

//Function to set ieeeStd
int WirelessRouter::setIeeeStd(std::string iestd)
{
  ieeeStd = iestd;
  return 0;
}

//Function to set dataRate
int WirelessRouter::setDataRate(double dr)
{
  dataRate = dr;
  return 0;
}

//Virtual function for computing the packets per second
int WirelessRouter::computePacketsPerSecond()
{
  double packetsPerSecond;
  packetsPerSecond = dataRate / (8 * packetSize);
  std::cout << "The packets per second rate is: " << packetsPerSecond << " (bytes/sec)" << std::endl;
  return 0;
}

//Function to redefine the clear all packet switch function
int WirelessRouter::clearAll()
{
  PacketSwitch::clearAll();
  setPacketSize(defaultPacketSize);
  setDataRate(defaultDataRate);
  setIeeeStd(defaultIeeeStd);
  return 0;
}

//Function for checking if the object is empty
//Function to see if the ethernet object is empty
int WirelessRouter::isEmptyWireless()
{
  bool state = true;
  state = PacketSwitch::isEmpty();
  if(packetSize != defaultPacketSize)
    state = false;
  if(dataRate != defaultDataRate)
    state = false;
  if(ieeeStd != defaultIeeeStd)
    state = false;
  return state;
}

//Overloaded << operator function
std::ostream& operator <<(std::ostream& outs, const WirelessRouter& ws)
{
  outs << "Packet Switch Vendor             : " << ws.getVendor() << std::endl
       << "Packet Switch Model              : " << ws.getModel() << std::endl
       << "Number of Ports in Packet Switch : " << ws.getNumPorts() << std::endl
       << "Per-port Speed                   : " << ws.getPPS() << std::endl
       << "Power in Watts                   : " << ws.getPower() << std::endl
       << "Dimensions (HxWxD)               : " << ws.getHeight() << " x " << ws.getWidth() << " x " << ws.getDepth() << std::endl
       << "Packet Size                      : " << ws.getPacketSize() << std::endl
       << "IEEE Standard                    : " << ws.getIeeeStd() << std::endl
       << "Data Rate                        : " << ws.getDataRate() << std::endl << std::endl;
  
  // Network portion of print out
  outs << "Connected Network Details:" << std::endl
       << "--------------------------" << std::endl;
  
  if(((ws.getNetwork())) != NULL)
    outs << *(ws.getNetwork()) << std::endl;
    
  // Component details 
  outs << "Component Details: " << std::endl
       << "Component#     Name          Power (Watts)       Price ($) " << std::endl
       << "----------     --------      ---------------     ----------" << std::endl;
  
  //For loop for array of components belonging to each packet switch
  int i;
  for (i = 0; i < 20; i++)  //iterate through the loop of components
  {
    if(!(ws.getComponentPtr()+i)->isEmpty())
      outs << "    "  << i << "          " << *(ws.getComponentPtr() + i);
  } 
  
  ws.componentPowerConsumption();
    
  return outs;
}

#endif