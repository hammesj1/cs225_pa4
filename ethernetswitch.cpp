//////////////////////////////////////////////////////////////////
//
// Joshua Hammes
// Program File Name: component.cpp
// Homework Assignment 3
// CS225-01PC Spring 2016
//
// Program is complete with two other source files (packet_main.cpp 
// and packet_switch.hpp). This segment of the program contains
// all function definitions for the packetSwitch class.
//
//////////////////////////////////////////////////////////////////


#include "ethernetswitch.hpp"

int ethernetSwitch::alive_ethernet = 0;    // Static int variable for tracking objects in memory


//////////////////////////////////////////////////////
//          Constructors and Destructor             //
//////////////////////////////////////////////////////

// Default Constructor
ethernetSwitch::ethernetSwitch()
{
  packet_size = 0;
  rating      = 0;
  
  alive_ethernet++;
}

// Overloaded Constructor
ethernetSwitch::ethernetSwitch(int new_packet_size, int new_rating) 
{
  packet_size = new_packet_size;
  rating      = new_rating;
  
  alive_ethernet++;
}

//Destructor
ethernetSwitch::~ethernetSwitch() 
{
  alive_ethernet--;
}


//////////////////////////////////////////////////////
//               Predicate Functions                //
//////////////////////////////////////////////////////

bool ethernetSwitch::isEthEmpty() const
{
  if( packet_size == 0 && rating == 0 )
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

int ethernetSwitch::set_packet_size(int new_size)  // Ethernet Packet Size
{
  packet_size = new_size;
  return 0;
}

int ethernetSwitch::set_rating(int new_rating)     // Ethernet Rating
{
  rating = new_rating;
  return 0;
}

int ethernetSwitch::clearEthernet()                // Clear Ethernet Data
{
  packet_size = 0;
  rating      = 0;
 
  return 0;
}


//////////////////////////////////////////////////////
//                 Friend Functions                 //
//////////////////////////////////////////////////////

//std::ostream & operator<<(std::ostream & os, const Component & cmpnt)
//{
//  os.width(20);
//  os << cmpnt.compName;
//  os.width(20);
//  os << cmpnt.compPowerRating;
//  os.width(20);
//  os << cmpnt.compPrice << std::endl;
//
//  return os;
//}


//////////////////////////////////////////////////////
//                 Virtual Functions                //
//////////////////////////////////////////////////////

int ethernetSwitch::compute_packetspersec()
{
  double pps_mbps = get_pps();
  int    ports    = get_ports();
  
  double per_sec_rate;
  
  per_sec_rate = (pps_mbps * ports) / (8 * packet_size);
  
  set_packets( per_sec_rate );
  
  //std::cout << "The packets per second rate is: " << packetsPerSecond << " (bytes/sec)" << std::endl;
  return 0;
}












