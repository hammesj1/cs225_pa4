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


#include "wirelessrouter.hpp"

int wirelessRouter::alive_wireless = 0;    // Static int variable for tracking objects in memory


//////////////////////////////////////////////////////
//          Constructors and Destructor             //
//////////////////////////////////////////////////////

// Default Constructor
wirelessRouter::wirelessRouter()
{
  ieee_std    = "";
  packet_size = 0;
  data_rate   = 0;
  
  alive_wireless++;
}

// Overloaded Constructor
wirelessRouter::wirelessRouter(std::string new_std, int new_size, double new_rate) 
{
  ieee_std    = new_std;
  packet_size = new_size;
  data_rate   = new_rate;
  
  alive_wireless++;
}

//Destructor
wirelessRouter::~wirelessRouter() 
{
  alive_wireless--;
}


//////////////////////////////////////////////////////
//               Predicate Functions                //
//////////////////////////////////////////////////////

bool wirelessRouter::isWireEmpty() const
{
  if( ieee_std == "" && packet_size == 0 && data_rate == 0 )
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

int wirelessRouter::set_ieee_std(std::string new_std)  // 802.11 Standard
{
  ieee_std = new_std;
  return 0;
}

int wirelessRouter::set_packet_size(int new_size)      // Packet Size
{
  packet_size = new_size;
  return 0;
}

int wirelessRouter::set_data_rate(double new_rate)     // Data Rate
{
  data_rate = new_rate;
  return 0;
}

int wirelessRouter::clearWireless()                    // Clear Wireless Data
{
  ieee_std    = "";
  packet_size = 0;
  data_rate   = 0;
 
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

int wirelessRouter::compute_packetspersec()
{
  double per_sec_rate;
  
  per_sec_rate = data_rate / (8 * packet_size);
  
  set_packets( per_sec_rate );
  
  //std::cout << "The packets per second rate is: " << packetsPerSecond << " (bytes/sec)" << std::endl;
  return 0;
}












