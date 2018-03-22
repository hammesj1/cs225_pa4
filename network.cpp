//////////////////////////////////////////////////////////////////
//
// Joshua Hammes
// Program File Name: network.cpp
// Homework Assignment 3
// CS225-01PC Spring 2016
//
// Program is complete with two other source files (packet_main.cpp 
// and packet_switch.hpp). This segment of the program contains
// all function definitions for the packetSwitch class.
//
//////////////////////////////////////////////////////////////////


#include "network.hpp"

int Network::alive_net = 0;    // Static int variable for tracking objects in memory


//////////////////////////////////////////////////////
//          Constructors and Destructor             //
//////////////////////////////////////////////////////

// Default Constructor
Network::Network()
{
  ssid       = "";
  netIP      = "";
  num_nodes  = 0;
  
  alive_net++;
}

// Overloaded Constructor
Network::Network(std::string new_ssid, std::string new_netIP, int new_num_nodes)
{
  ssid       = new_ssid;
  netIP      = new_netIP;
  num_nodes  = new_num_nodes;

  alive_net++;
}

//Destructor
Network::~Network() 
{
  alive_net--;
}


//////////////////////////////////////////////////////
//               Predicate Functions                //
//////////////////////////////////////////////////////

bool Network::isNetEmpty() const
{
  if( ssid == "" && netIP == "" && num_nodes == 0 )
  {
    return true;
  }
  else
  {
    return false;
  }
}


//////////////////////////////////////////////////////
//                Mutator Functions                 //
//////////////////////////////////////////////////////

int Network::set_ssid(std::string new_ssid)      // Network SSID
{
  ssid = new_ssid;
  return 0;
}

int Network::set_netIP(std::string new_netIP)    // Network IP Address
{
  netIP = new_netIP;
  return 0;
}

int Network::set_nodes(int new_num_nodes)        // Network Number of Nodes
{
  num_nodes = new_num_nodes;
  return 0;
}

int Network::clearNetwork()                      // Clear Network Data
{
  ssid       = "";
  netIP      = "";
  num_nodes  = 0;

  return 0;
}


//////////////////////////////////////////////////////
//                 Friend Functions                 //
//////////////////////////////////////////////////////

std::ostream & operator<<(std::ostream & os, const Network & ntwk)
{
  os << std::endl <<
  "  Connected Network Details " << std::endl <<
  "  ------------------------- " << std::endl <<
  "  Label      : " << ntwk.ssid       << std::endl <<
  "  IP Address : " << ntwk.netIP      << std::endl <<
  "  Size       : " << ntwk.num_nodes  << " nodes " << std::endl;

  return os;
}