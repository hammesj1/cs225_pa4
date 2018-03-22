//////////////////////////////////////////////////////////////////
//
// Joshua Hammes
// Program File Name: packetswitch.cpp
// Homework Assignment 3
// CS225-01PC Spring 2016
//
// Program is complete with two other source files (packet_main.cpp 
// and packet_switch.hpp). This segment of the program contains
// all function definitions for the packetSwitch class.
//
//////////////////////////////////////////////////////////////////


#include "packetswitch.hpp"

int packetSwitch::num_alive = 0;    // Static int variable for tracking objects in memory


//////////////////////////////////////////////////////
//          Constructors and Destructor             //
//////////////////////////////////////////////////////

// Default Constructor
packetSwitch::packetSwitch()
{
  vendor     = "";
  model      = "";
  num_ports  = 0;
  pps        = 0;
  power      = 0;
  dimensions = {0.0, 0.0, 0.0};
  
  netPtr     = NULL;
  
  //compArr[maxComponents];
  
  packets_per_sec = 0;
  
  num_alive++;
}

// Overloaded Constructor
packetSwitch::packetSwitch(std::string new_vendor, std::string new_model, int new_num_ports, 
      double new_pps, double new_power, float height, float weight, float depth, 
      Network* new_netPtr, double new_packets) 
{
  vendor     = new_vendor;
  model      = new_model;
  num_ports  = new_num_ports;
  pps        = new_pps;
  power      = new_power;
  dimensions = {height, weight, depth};

  netPtr     = new_netPtr;

  //Component new_compArr[]
  //compArr    = new_compArr[0];
  
  packets_per_sec = new_packets;
  
  num_alive++;
}

//Destructor
packetSwitch::~packetSwitch() 
{
  num_alive--;
}


//////////////////////////////////////////////////////
//               Predicate Functions                //
//////////////////////////////////////////////////////

bool packetSwitch::isEmpty() const
{
  if( vendor == "" && model == "" && num_ports == 0 && pps == 0 && power == 0 && 
     dimensions.height == 0.0 && dimensions.width == 0.0 && dimensions.depth == 0.0 &&
     netPtr == NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}


//////////////////////////////////////////////////////
//               Accessor Functions                 //
//////////////////////////////////////////////////////
  
// Calculate Total Power Consumption
double packetSwitch::get_totalPower() const
{
  double totalPower = 0;
  
  for( int currComp = 0; currComp < maxComponents; currComp++ )
  {  
    if( !(compArr[currComp].isCompEmpty() ) )
    {
      totalPower = totalPower + compArr[currComp].get_compPowerRating();
    }
  }
  
  return totalPower;
}

// Calculate Minimum Cost
double packetSwitch::get_totalCost() const
{
  double totalCost = 0;
  
  for( int currComp = 0; currComp < maxComponents; currComp++ )
  {  
    if( !(compArr[currComp].isCompEmpty() ) )
    {
      totalCost = totalCost + compArr[currComp].get_compPrice();
    }
  }
  
  return totalCost;
}

// Calculate Power Dissipation
double packetSwitch::get_power_dissipation()
{
  double dissipation;
  
  dissipation = power * 3.41;
  
  return dissipation;
}


//////////////////////////////////////////////////////
//                Mutator Functions                 //
//////////////////////////////////////////////////////

int packetSwitch::set_vendor(std::string new_vendor)      // Vendor
{
  vendor = new_vendor;
  return 0;
}

int packetSwitch::set_model(std::string new_model)        // Model
{
  model = new_model;
  return 0;
}

int packetSwitch::set_ports(int new_num_ports)            // Number of Ports
{
  num_ports = new_num_ports;
  return 0;
}

int packetSwitch::set_pps(double new_pps)                 // Per Port Speed (MBPS)
{
  pps = new_pps;
  return 0;
}

int packetSwitch::set_power(double new_power)             // Power Consumption
{
  power = new_power;
  return 0;
}

int packetSwitch::set_packets(double new_packets)         // Packets Per Second
{
  packets_per_sec = new_packets;
  return 0;
}

int packetSwitch::set_dimensions(float height, float width, float depth)  // Dimensions (HxWxD)
{
  dimensions = {height, width, depth};
  return 0;
}

int packetSwitch::set_netPtr( Network * new_netPtr)        // Network Pointer
{
  netPtr = new_netPtr;
    
  return 0;
}

int packetSwitch::clearPacketSwitch()                      // Clear Packet Switch Data
{
  vendor     = "";
  model      = "";
  num_ports  = 0;
  pps        = 0;
  power      = 0;
  dimensions = {0.0, 0.0, 0.0};
  netPtr     = NULL;
 
  return 0;
}


//////////////////////////////////////////////////////
//                 Friend Functions                 //
//////////////////////////////////////////////////////

std::ostream & operator<<(std::ostream & os, const packetSwitch & ps)
{
  // Print Out of Packet Switch Details
  os << std::endl <<
  "  Packet Switch Vendor                 : " << ps.vendor     <<                 std::endl <<
  "  Packet Switch Model                  : " << ps.model      <<                 std::endl <<
  "  Number of Ports in Packet Switch     : " << ps.num_ports  <<                 std::endl <<
  "  Packet Switch Per Port Speed         : " << ps.pps        << " Mbps"      << std::endl <<
  "  Packet Switch Power Consumption      : " << ps.power      << " W"         << std::endl <<
  "  Packet Switch Dimensions (H x W x D) : " << ps.dimensions.height << " x " << ps.dimensions.width <<
  " x " << ps.dimensions.depth << " inches" << std::endl;
  
  // Print Out of Network Details
  if( ps.netPtr == NULL )
  {
    os << std::endl << "ERROR: NO NETWORK HAS BEEN ASSIGNED TO THIS PACKET SWITCH!" << std::endl;
  }
  else
  {
    os << *(ps.netPtr);
  }
  
  // Print Header of Component Details
  os << std::endl <<
  "  Component Details " << std::endl <<
  "  Component #    Name                Power (Watts)       Price ($) " << std::endl <<
  "  -----------    ----                -------------       --------- " << std::endl;

  // Print Out of Component Details
  for( int currComp = 0; currComp < maxComponents; currComp++ )
  {
    if( !(ps.compArr[currComp].isCompEmpty() ) )
    {
      os << "  ";
      os.setf(std::ios_base::left, std::ios_base::adjustfield);
      os.width(15);
      os << currComp;
      os.width(20);
      os << ps.compArr[currComp];
    }
  }
  
  // Print Out of Total Power Consumption
  if( ps.get_totalPower() <= ps.power )
  {
    os << std::endl <<
    "  Total power consumption of this component-based configuration is " <<
    ps.get_totalPower() << " W," << std::endl <<
    "  and is within the max power consumption rating of the Packet Switch (" <<
    ps.power << " W)." << std::endl;
  }
  
  else if( ps.get_totalPower() > ps.power )
  {
    os << std::endl <<
    "  WARNING!!! Total power consumption of this component-based configuration (" <<
    ps.get_totalPower() << " W)" << std::endl <<
    "             exceeds that of the Packet Switch (" <<
    ps.power << " W)." << std::endl;
  }
  
  // Print Out of Minimum Cost
  os << std::endl <<
  "  Minimum price of this Packet Switch based on this component-based configuration is $" <<
  ps.get_totalCost() << "." << std::endl;
  
  return os;
}
  
  
//////////////////////////////////////////////////////
//                 Virtual Functions                //
//////////////////////////////////////////////////////

int packetSwitch::compute_packetspersec()
{
  std::cout << std::endl <<
  "  ERROR: No sufficient data available in the object!" << std::endl;
  
  return 0;
}
















