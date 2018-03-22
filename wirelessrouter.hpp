//////////////////////////////////////////////////////////////////
//
// Joshua Hammes
// Program File Name: wirelessrouter.hpp
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

#ifndef WIRELESSROUTER_HPP_
#define WIRELESSROUTER_HPP_


// Declaration of wirelessRouter class

class wirelessRouter : public packetSwitch
{

private:


  std::string ieee_std;             // IEEE 802.11 Standard
  int packet_size;                  // Size of packets transferred by the Wireless Router
  double data_rate;                 // Rate of Data Transfer supported by the Wireless Router

  static int alive_wireless;        // Variable for tracking objects in memory


public:


  // Default Constructor
  wirelessRouter();

  // Overload Constructor
  wirelessRouter(std::string, int, double);

  // Destructor
  ~wirelessRouter();

  // Predicate Function
  bool isWireEmpty() const;



  // Accessor Functions

  std::string get_ieee_std()    const { return ieee_std;       } // Returns Wireless Router's 802.11 Standard
  int         get_packet_size() const { return packet_size;    } // Returns Wireless Router's Packet Size
  double      get_data_rate()   const { return data_rate;      } // Returns Wireless Router's Data Rate

  int         get_alive_wire()  const { return alive_wireless; } // Returns number of objects in memory



  // Mutator Functions

  int set_ieee_std   (std::string); // Sets Wireless Router 802.11 Standard
  int set_packet_size(int);         // Sets Wireless Router Packet Size
  int set_data_rate  (double);      // Sets Wireless Router Data Rate

  int clearWireless();              // Clears all data members of an object
  
  
  
  // Friend Functions
  
  //friend std::ostream & operator<<(std::ostream & os, const Component & cmpnt);
  
  
  
  // Virtual Functions
  
  virtual int compute_packetspersec();      // Computes packets_per_sec
  
};

#endif

