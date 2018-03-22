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


#include "component.hpp"

int Component::alive_comp = 0;    // Static int variable for tracking objects in memory


//////////////////////////////////////////////////////
//          Constructors and Destructor             //
//////////////////////////////////////////////////////

// Default Constructor
Component::Component()
{
  compName        = "";
  compPowerRating = 0;
  compPrice       = 0;
  
  alive_comp++;
}

// Overloaded Constructor
Component::Component(std::string new_compName, double new_compPowerRating, double new_compPrice) 
{
  compName        = new_compName;
  compPowerRating = new_compPowerRating;
  compPrice       = new_compPrice;
  
  alive_comp++;
}

//Destructor
Component::~Component() 
{
  alive_comp--;
}


//////////////////////////////////////////////////////
//               Predicate Functions                //
//////////////////////////////////////////////////////

bool Component::isCompEmpty() const
{
  if( compName == "" && compPowerRating == 0 && compPrice == 0 )
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

int Component::set_compName(std::string new_compName)           // Component Name
{
  compName = new_compName;
  return 0;
}

int Component::set_compPowerRating(double new_compPowerRating)  // Component Power Rating
{
  compPowerRating = new_compPowerRating;
  return 0;
}

int Component::set_compPrice(double new_compPrice)              // Component Price
{
  compPrice = new_compPrice;
  return 0;
}

int Component::clearComponent()                                 // Clear Network Data
{
  compName        = "";
  compPowerRating = 0;
  compPrice       = 0;
 
  return 0;
}


//////////////////////////////////////////////////////
//                 Friend Functions                 //
//////////////////////////////////////////////////////

std::ostream & operator<<(std::ostream & os, const Component & cmpnt)
{
  os.width(20);
  os << cmpnt.compName;
  os.width(20);
  os << cmpnt.compPowerRating;
  os.width(20);
  os << cmpnt.compPrice << std::endl;

  return os;
}