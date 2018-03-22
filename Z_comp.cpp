/////////////////////////////////////////////////////////////////////////////////////////////
// CS225 Spring 2016
// Evelyn Brown
// Component Class Implementation
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef COMPONENT_CPP
#define COMPONENT_CPP

#define DEF_NAME ""
#define DEF_POWERRATING 0
#define DEF_PRICE 0

#include <iostream>
#include "component.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
// Component methods

//Initialize NumAlive
int Component::numAlive = 0;        

//Default Constructor
Component::Component()
{
  name = DEF_NAME;
  powerRating = DEF_POWERRATING;
  price = DEF_PRICE;
  numAlive++ ;
}

//Destructor
Component::~Component() { numAlive-- ; }

// Function to set name variable
int Component::setName(std::string n)
{
  name = n;
  return 0;
}

//Function to set Power Rating
int Component::setPowerRating(double pr)
{
  powerRating = pr;
  return 0;
}

//Function to set the number of ports data
int Component::setPrice(double p)
{
  price = p;
  return 0;
}

//Function to set all data
int Component::setComponent(std::string n, double pr = 0, double p = 0) //Using Default Variables
{
  name = n;
  powerRating = pr;
  price = p;
  return 0;
}

//Function to display all data
int Component::displayAllComponents()
{
  std::cout << "Name                             : " << getName() << std::endl;
  std::cout << "Power Rating                     : " << getPowerRating() << std::endl;
  std::cout << "Price                            : " << getPrice() << std::endl;
  return 0;
}

//Function to clear all data
int Component::clearAllComponents()
{
  setName(DEF_NAME);
  setPowerRating(DEF_POWERRATING);
  setPrice(DEF_PRICE);
  return 0;
}

//isEmpty Function
bool Component::isEmpty() const
{
  bool state = true;
  if(name != DEF_NAME)
    state = false;
  if(powerRating != DEF_POWERRATING)
    state = false;
  if(price != DEF_PRICE)
    state = false;
  return state;
}
  
//Component overloaded operator function <<
std::ostream& operator <<(std::ostream& outs, const Component& c)
{
  outs << c.getName() << "           "  << c.getPowerRating() << "                "  << c.getPrice() << std::endl;
  return outs;
}
     
#endif