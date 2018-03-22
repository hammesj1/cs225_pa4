//////////////////////////////////////////////////////////////////
//
// Joshua Hammes
// Program File Name: component.hpp
// Homework Assignment 3
// CS225-01PC Spring 2016
//
// Program is complete with two other source files (packet_main.cpp 
// and packet_switch.cpp). This segment of the program contains
// all function declarations for the packetSwitch class.
//
//////////////////////////////////////////////////////////////////


// Function Declarations

#include <iostream>
#include <string>

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_


// Declaration of Component class

class Component
{

private:


  std::string compName;         // Component Name

  double compPowerRating;       // Component Power Rating
  double compPrice;             // Component Price

  static int alive_comp;        // Variable for tracking objects in memory


public:


  // Default Constructor
  Component();

  // Overload Constructor
  Component(std::string, double, double);

  // Destructor
  ~Component();

  // Predicate Function
  bool isCompEmpty() const;



  // Accessor Functions

  std::string get_compName()        const { return compName;        } // Returns Component Name

  double      get_compPowerRating() const { return compPowerRating; } // Returns Component Power Rating
  double      get_compPrice()       const { return compPrice;       } // Returns Component Price

  int         get_alive_comp()      const { return alive_comp;      } // Returns number of objects in memory



  // Mutator Functions

  int set_compName(std::string);    // Sets Component Name

  int set_compPowerRating(double);  // Sets Component Power Rating
  int set_compPrice(double);        // Sets Component Price

  int clearComponent();             // Clears all data members of an object
  
  
  
  // Friend Functions
  
  friend std::ostream & operator<<(std::ostream & os, const Component & cmpnt);
  
};

#endif

