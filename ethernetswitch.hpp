//////////////////////////////////////////////////////////////////
//
// Joshua Hammes
// Program File Name: ethernetswitch.hpp
// Homework Assignment 4
// CS225-01PC Spring 2016
//
// Program is complete with two other source files (packet_main.cpp 
// and packet_switch.cpp). This segment of the program contains
// all function declarations for the packetSwitch class.
//
//////////////////////////////////////////////////////////////////


// Function Declarations
#include "packetswitch.hpp"

#ifndef ETHERNETSWITCH_HPP_
#define ETHERNETSWITCH_HPP_


// Declaration of ethernetSwitch class

class ethernetSwitch : public packetSwitch
{

private:


  int packet_size;                  // Size of packets transferred by the Ethernet Switch
  
  int rating;                       // Rating of the Ethernet Switch

  static int alive_ethernet;        // Variable for tracking objects in memory


public:


  // Default Constructor
  ethernetSwitch();

  // Overload Constructor
  ethernetSwitch(int, int);

  // Destructor
  ~ethernetSwitch();

  // Predicate Function
  bool isEthEmpty() const;



  // Accessor Functions

  int get_packet_size() const { return packet_size;    } // Returns Ethernet Switch's Packet Size
  int get_rating()      const { return rating;         } // Returns Ethernet Switch's Rating

  int get_alive_eth()   const { return alive_ethernet; } // Returns number of objects in memory



  // Mutator Functions

  int set_packet_size(int);  // Sets Ethernet Switch Packet Size
  int set_rating     (int);  // Sets Ethernet Switch Rating

  int clearEthernet();       // Clears all data members of an object
  
  
  
  // Friend Functions
  
  //friend std::ostream & operator<<(std::ostream & os, const Component & cmpnt);
  
  
  
  // Virtual Functions
  
  virtual int compute_packetspersec();      // Computes packets_per_sec
  
};

#endif

