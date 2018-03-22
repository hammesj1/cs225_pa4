////////////////////////////////////////////////////////////////////////////////////////////////////
// CS225 Spring 2016
// Evelyn Brown
// Component Class Implementation
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef NETWORK_CPP
#define NETWORK_CPP

#define DEF_LABEL ""
#define DEF_IPADDRESS ""
#define DEF_SIZE 0

#include <iostream>
#include "network.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Network methods

//Initialize NumAlive
int Network::numAlive = 0;        

//Default Constructor
Network::Network()
{
  label = DEF_LABEL;
  IPaddress = DEF_IPADDRESS;
  size = DEF_SIZE;
  numAlive++ ;
}

//Destructor
Network::~Network() { numAlive-- ; }

// Function to set label variable
int Network::setLabel(std::string l)
{
  label = l;
  return 0;
}

//Function to set IP address
int Network::setIPaddress(std::string ip)
{
  IPaddress = ip;
  return 0;
}

//Function to set the network size
int Network::setSize(int s)
{
  size = s;
  return 0;
}

//Function to set the entire network
int Network::setNetwork(std::string l, std::string ip, int s)
{
  label = l;
  IPaddress = ip;
  size = s;
  return 0;
} 

//Function to display all data
int Network::displayAllNetworks()
{
  std::cout << "Label                            : " << getLabel() << std::endl;
  std::cout << "IP Address                       : " << getIPaddress() << std::endl;
  std::cout << "Size                             : " << getSize() << std::endl;
  return 0;
}

//Function to clear all data
int Network::clearAllNetworks()
{
  setLabel(DEF_LABEL);
  setIPaddress(DEF_IPADDRESS);
  setSize(DEF_SIZE);
  return 0;
}

//isEmpty Function
bool Network::isEmpty()
{
  bool state = true;
  if(label != DEF_LABEL)
    state = false;
  if(IPaddress != DEF_IPADDRESS)
    state = false;
  if(size != DEF_SIZE)
    state = false;
  return state;
}
    
std::ostream& operator <<(std::ostream& outs, const Network& n)
{  
  outs << "Network Label:        " << n.getLabel() << std::endl;
  outs << "Network IP address    " << n.getIPaddress() << std::endl;
  outs << "Network Size          " << n.getSize() << std::endl;
  return outs;
}  

#endif