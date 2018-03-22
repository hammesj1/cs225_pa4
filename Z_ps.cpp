////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CS225 Spring 2016
// Evelyn Brown
// Packet Switch Class Implementation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PACKETSWITCH_CPP
#define PACKETSWITCH_CPP

#define DEF_VENDOR ""
#define DEF_MODEL ""
#define DEF_NUMPORTS 0
#define DEF_PPS 0
#define DEF_POWER 0
#define DEF_HEIGHT 0
#define DEF_WIDTH 0
#define DEF_DEPTH 0

#include <string>
#include <iostream>
#include "packetswitch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Packet switch methods

//Initialize NumAlive
//This is placed first for the implementation because I wasn't sure 
//what the program would do if constructors and destructors were 
//trying to add and subtract to a number that hadn't been initialized yet.
int PacketSwitch::numAlive = 0;        

//Default Constructor
PacketSwitch::PacketSwitch()
{
  vendor = DEF_VENDOR;
  model = DEF_MODEL;
  numPorts = DEF_NUMPORTS;
  pps = DEF_PPS;
  power = DEF_POWER;
  sizeInInches.height = DEF_HEIGHT;
  sizeInInches.width = DEF_WIDTH;
  sizeInInches.depth = DEF_DEPTH;
  numAlive++ ;
}

//Overloaded Constructor
PacketSwitch::PacketSwitch(std::string V, std::string M = DEF_MODEL, int N = DEF_NUMPORTS, double T = DEF_PPS,
    double E = DEF_POWER, float H = DEF_HEIGHT, float W = DEF_WIDTH, float D = DEF_DEPTH, Network* n = NULL, Component c1 = Component())
{
  vendor = V;
  model = M;
  numPorts = N;
  pps = T;
  power = E;
  sizeInInches.height = H;
  sizeInInches.width = W;
  sizeInInches.depth = D;
  numAlive++ ;
  n1 = n;
//  int iter = 0;
//  for (Component i : c1) //range-based for loop
//    {
//      c[iter++] = i;   //memberwise assignment
//    }
}

//Destructor
PacketSwitch::~PacketSwitch() { numAlive-- ; }

// Function to set vendor variable
int PacketSwitch::setVendor(std::string V)
{
  this->vendor = V;          //Use of the "this" pointer
  return 0;
}

// Function to set the model data
int PacketSwitch::setModel(std::string M) 
{
  this->model = M;
  return 0;
}

//Function to set the number of ports data
int PacketSwitch::setNumPorts(int N)
{
  this->numPorts = N;
  return 0;
}

//Mutator Method for PPS
int PacketSwitch::setPPS(double T)
{
  this->pps = T;
  return 0;
} 

//Mutator Method for Power
int PacketSwitch::setPower(double E)
{
  this->power = E;
  return 0;
}

//Mutator method for Size in Inches
int PacketSwitch::setDimensions(float inputHeight = 0, float inputWidth = 0, float inputDepth = 0) //Using Default Variables
{
  sizeInInches.height = inputHeight;
  sizeInInches.width = inputWidth;
  sizeInInches.depth = inputDepth;
  return 0;
}
  
//Function to display all data
int PacketSwitch::displayAll()
{
  std::cout << "Packet Switch Vendor             : " << getVendor() << std::endl;
  std::cout << "Packet Switch Model              : " << getModel() << std::endl;
  std::cout << "Number of Ports in Packet Switch : " << getNumPorts() << std::endl;
  std::cout << "Per-port Speed                   : " << getPPS() << std::endl;
  std::cout << "Power in Watts                   : " << getPower() << std::endl; 
  std::cout << "Dimentions (HxWxD)               : " << getHeight() << " x " << getWidth() << " x " << getDepth() << " inches " << std::endl;
  
  return 0;
}

//Function to clear all data
int PacketSwitch::clearAll()
{
  setVendor(DEF_VENDOR);
  setModel(DEF_MODEL);
  setNumPorts(DEF_NUMPORTS);
  setPPS(DEF_PPS);
  setPower(DEF_POWER);
  setDimensions(DEF_HEIGHT, DEF_WIDTH, DEF_DEPTH);
  return 0;
}


//isEmpty Function
bool PacketSwitch::isEmpty()
{
  bool state = true;
  if(vendor != DEF_VENDOR)
    state = false;
  if(model != DEF_MODEL)
    state = false;
  if(numPorts != DEF_NUMPORTS)
    state = false;
  if(pps != DEF_PPS)
    state = false;
  if(power != DEF_POWER)
    state = false;
  if(sizeInInches.height != DEF_HEIGHT)
    state = false;
  if(sizeInInches.width != DEF_WIDTH)
    state = false;
  if(sizeInInches.depth != DEF_DEPTH)
    state = false;
      
  return state;
}
      
// Get Component access method
Component& PacketSwitch::getComponent(int index)
{
  return c[index];
}

// Total power consumption and price computation
int PacketSwitch::componentPowerConsumption() const
{
  int powerSum = 0;    //Sum of component power
  float priceSum = 0;  //Sum or component prices
  
  for (Component currentComp:c)	
    {
      if (currentComp.isEmpty() == false)
        {
          powerSum += currentComp.getPowerRating();
          priceSum += currentComp.getPrice();
        }
    }

  if(powerSum > power)
    std::cout << "WARNING: component power consumption greater than packet switch power!" << std::endl;
    
  std::cout << "Price of all components is  : " << priceSum << std::endl << std::endl;
  return 0;
}
      
//Overloaded << operator function
std::ostream& operator <<(std::ostream& outs, const PacketSwitch& ps)
{
  outs << "Packet Switch Vendor             : " << ps.getVendor() << std::endl
       << "Packet Switch Model              : " << ps.getModel() << std::endl
       << "Number of Ports in Packet Switch : " << ps.getNumPorts() << std::endl
       << "Per-port Speed                   : " << ps.getPPS() << std::endl
       << "Power in Watts                   : " << ps.getPower() << std::endl
       << "Dimensions (HxWxD)               : " << ps.getHeight() << " x " << ps.getWidth() << " x " << ps.getDepth() << std::endl; 
  
  // Network portion of print out
  outs << "Connected Network Details:" << std::endl
       << "--------------------------" << std::endl;
  
  if(ps.n1 != NULL)
    outs << *(ps.n1) << std::endl;
    
  // Component details 
  outs << "Component Details: " << std::endl
       << "Component#     Name          Power (Watts)       Price ($) " << std::endl
       << "----------     --------      ---------------     ----------" << std::endl;
  
  //For loop for array of components belonging to each packet switch
  int i;
  for (i = 0; i < 20; i++)  //iterate through the loop of components
  {
    if(!(ps.c[i]).isEmpty())
      outs << "    "  << i << "          " << ps.c[i];
  } 

  ps.componentPowerConsumption();
  
  return outs;
}  

//Setting the associate netowrk object
int PacketSwitch::setNetwork(Network* n) 
{
  n1 = n;
  return 0;
}

// Thermal Output Protected Function
double PacketSwitch::thermalOutput()
{
  double thermalOutput;
  thermalOutput = power * 3.41;
  std::cout << "The thermal output of the packet switch is:  " << thermalOutput << " (BTU's/hour)" << std::endl;
  return 0;
}

//Computing the Packets Per Second
int PacketSwitch::computePacketsPerSecond()
{
  std::cout << "There is no sufficient data available in the object! " << std::endl;
  return 0;
}
  
 #endif