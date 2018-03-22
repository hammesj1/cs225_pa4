//////////////////////////////////////////////////////////////////
//
// Joshua Hammes
// Program File Name: packetswitch.hpp
// Homework Assignment 3
// CS225-01PC Spring 2016
//
// Program is complete with two other source files (packet_main.cpp 
// and packet_switch.cpp). This segment of the program contains
// all function declarations for the packetSwitch class.
//
//////////////////////////////////////////////////////////////////


// Function Declarations
#include "network.hpp"
#include "component.hpp"

#include <iostream>
#include <string>

#ifndef PACKETSWITCH_HPP_
#define PACKETSWITCH_HPP_

const int maxComponents = 20;  // Maximum array size for member variable compArr


// Declaration of packetSwitch class

class packetSwitch 
{

private:


  std::string vendor;
  std::string model;
  int num_ports;

  double pps;                       // Per port speed in Mbps
  double power;                     // Power consumption in Watts;

  static int num_alive;             // Variable for tracking objects in memory

  struct SizeInInches               // Structure that holds packet switch dimensions
  {
    float height, width, depth;
  } dimensions;
  
  Network * netPtr;                 // Pointer to a network object stored in program memory
  
  Component compArr[maxComponents]; // Array of size 20 that stores component cbjects
  
  double packets_per_sec;           // Packets Per Second
  
  
protected:


  double get_power_dissipation();   // Compute and Print switch's Power Dissipation value


public:


  // Default Constructor
  packetSwitch();

  // Overload Constructor
  packetSwitch(std::string, std::string, int, double, double, float, float, float, Network*, double);

  // Destructor
  virtual ~packetSwitch();

  // Predicate Function
  bool isEmpty() const;



  // Accessor Functions

  std::string  get_vendor()        const { return vendor;          }   // Returns switch vendor
  std::string  get_model()         const { return model;           }   // Returns switch model
  int          get_ports()         const { return num_ports;       }   // Returns switch's number of ports

  double       get_pps()           const { return pps;             }   // Returns switch's per port speed in Mbps
  double       get_power()         const { return power;           }   // Returns switch's power consumption in Watts
  double       get_packets()       const { return packets_per_sec; }   // Returns switch's packets per second

  SizeInInches get_dimensions()    const { return dimensions;      }   // Returns switch's dimensions

  int          get_num_alive()     const { return num_alive;       }   // Returns number of objects in memory
  
  Network&     get_network()       const { return *netPtr;         }   // Returns the address of a network object
  
  Component*   get_comp(int index)       { return &compArr[index]; }   // Returns a pointer to a component object
  
  double       get_totalPower()    const;                              // Returns the total power consumtion of a component configuration
  double       get_totalCost()     const;                              // Returns the total cost of a component configuration
  


  // Mutator Functions

  int set_vendor    ( std::string );          // Sets switch vendor
  int set_model     ( std::string );          // Sets switch model
  int set_ports     ( int );                  // Sets switch's number of ports

  int set_pps       ( double );               // Sets switch's per port speed in Mbps
  int set_power     ( double );               // Sets switch's power consumption in Watts
  int set_packets   ( double );               // Sets switch's packets per second

  int set_dimensions( float, float, float );  // Sets switch's dimensions
  
  int set_netPtr    ( Network * );            // Sets switch's network pointer to a network object

  int clearPacketSwitch();                    // Clears all data members of an object
  
  
  
  // Friend Functions

  friend std::ostream & operator<<(std::ostream & os, const packetSwitch & ps);
  
  
  
  // Virtual Functions
  
  virtual int compute_packetspersec();      // Computes packets_per_sec

};

#endif