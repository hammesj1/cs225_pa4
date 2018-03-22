//////////////////////////////////////////////////////////////////
//
// Joshua Hammes
// Program File Name: network.hpp
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

#ifndef NETWORK_HPP_
#define NETWORK_HPP_


// Declaration of Network class

class Network
{

private:


  std::string ssid;                 // Network label (SSID)
  std::string netIP;                // Network IP address
  
  int num_nodes;                    // Variable for storing the number of nodes in the network
  
  static int alive_net;             // Variable for tracking network objects in memory


public:


  // Default Constructor
  Network();

  // Overload Constructor
  Network(std::string, std::string, int);

  // Destructor
  ~Network();

  // Predicate Function
  bool isNetEmpty() const;



  // Accessor Functions

  std::string get_ssid()      const { return ssid;      }  // Returns network label
  std::string get_netIP()     const { return netIP;     }  // Returns network IP address

  int         get_nodes()     const { return num_nodes; }  // Returns network number of nodes

  int         get_alive_net() const { return alive_net; }  // Returns number of objects in memory



  // Mutator Functions

  int set_ssid(std::string);      // Sets network label
  int set_netIP(std::string);     // Sets network IP address
  int set_nodes(int);             // Sets network number of nodes

  int clearNetwork();             // Clears all data members of an object
  
  
  
  // Friend Functions
  
  friend std::ostream & operator<<(std::ostream & os, const Network & ntwk);

};

#endif