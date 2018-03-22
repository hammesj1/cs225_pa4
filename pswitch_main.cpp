////////////////////////////////////////////////////////////
//
// Joshua Hammes
// Program packet_main.cpp
// Homework Assignment 2
// CS225-01PC Spring 2016
//
// Program implements a class to store packet switch data
// based upon user input or file input. Input can set the
// member variables in an array of objects as well as view
// the data placed into the objects, delete the data, view
// a menu of options, and select other options. Program is
// complete with two other source files (packet_switch.cpp
// and packet_switch.hpp).
//
////////////////////////////////////////////////////////////


/////////////////////////////////////////////
//             Included files              //
/////////////////////////////////////////////

#include "packetswitch.hpp"
#include "ethernetswitch.hpp"
#include "wirelessrouter.hpp"

#include <unistd.h>
#include <sstream>


////////////////////////////////////////////
//                Globals                 //
////////////////////////////////////////////

const int maxPacketSwitch = 30;  // Maximum number of packet switches allowed
const int maxNetwork = 10;       // Maximum number of networks allowed

const int ARR_MAX = 60;          // Maximum size of the mixed array of objects
const int PER_GROUP = 20;        // Maximum number of objects of each class allowed

bool done        = false;
bool interactive = true;

int currObj = 0;                 // Global int to keep track of current object
packetSwitch *ps1;               // Global pointer to identify the current object

Network *net1;                   // Global pointer to keep track of the Network array


////////////////////////////////////////////
//          Function Prototypes           //
////////////////////////////////////////////

int process_menu_in(std::string);
int print_menu();


/////////////////////////////////////////////
//              Main Function              //
/////////////////////////////////////////////

int main() {

  packetSwitch ps_array[maxPacketSwitch];  // Declaration of an array of 30 packetSwitch objects
  ps1 = ps_array;                          // Assignment of global pointer to first object in array
  
  Network net_array[maxNetwork];           // Declaration of an array of 10 Network objects
  net1 = net_array;                        // Assignment of global pointer to first object in array
                   
  std::string menu_in;                     // Variable for storing user choice in menu options
  
  interactive = isatty(STDIN_FILENO);      // Check to see if input is from file or user input

  if(!interactive)
    std::cout << std::endl << "File Input!" << std::endl;

  else
  {
    std::cout<< std::endl << "Console Input!" << std::endl;

    print_menu();
  }
  
  while (!done)                             // Loops until user chooses to quit program
  {
    std::cout << std::endl << "Menu [" << currObj << "] : ";
    getline(std::cin, menu_in);
    process_menu_in(menu_in);
  }
 
  std::cout << "Toodles!" << std::endl;
}


///////////////////////////////////////////////////////////////
// Process Menu - executes certain code based on user choice //
///////////////////////////////////////////////////////////////

int process_menu_in(std::string menu_in)
{
  // Configuration for reading input buffer
  char inchar;
  
  std::istringstream in_string(menu_in);
  
  in_string >> inchar;
  
  std::istream *in_stream;
  

  if( isatty(STDIN_FILENO) )  // If Interactive is True
  {
    in_stream = &std::cin;
  }
  else                        // If Interactive is False
  {
    in_stream = &in_string;
  }
  
  // Switch/Case statement to process input
  switch(toupper(inchar))
  {
    case '*':  // Displays data for all currently live packet switch objects
    
      for (int loopCntr = 0; loopCntr < maxPacketSwitch; loopCntr++ )
      {
        if( !( ps1[loopCntr].isEmpty() ) )
        {
          std::cout << std::endl << "  Packet Switch # " << loopCntr << ps1[loopCntr] << std::endl;
        }
      }
      break;
      
    case 'B':  // Displays the program's memory usage
    {
      packetSwitch *currPS = &ps1[currObj];
    
      int alivePS, bytesPS, aliveNet, bytesNet, aliveComp, bytesComp, bytesTotal;
      
      // Usage of Packet Switch Objects
      alivePS    =  ps1[currObj].get_num_alive();
      bytesPS    = (ps1[currObj].get_num_alive() * sizeof(packetSwitch));

      // Usage of Network Objects
      aliveNet   =  net1[0].get_alive_net();
      bytesNet   = (net1[0].get_alive_net() * sizeof(Network));
      
      // Usage of Component Objects
      aliveComp  =   currPS -> get_comp(0) -> get_alive_comp();
      bytesComp  = ( currPS -> get_comp(0) -> get_alive_comp() ) * ( sizeof(Component) );
      
      // The total bytes calculation does not include the bytes allocated to Components
      // because they are already included in the bytes allocated to the Packet Switch's
      bytesTotal = bytesPS + bytesNet;

      std::cout << std::endl << " Total Alive Packet Switch's in Memory : " << alivePS
                << std::endl << " Bytes Allocated for Packet Switch's   : " << bytesPS
                << std::endl << " Total Alive Networks in Memory        : " << aliveNet
                << std::endl << " Bytes Allocated for Networks          : " << bytesNet
                << std::endl << " Total Alive Components in Memory      : " << aliveComp
                << std::endl << " Bytes Allocated for Components        : " << bytesComp
                << std::endl << " Total Number of Bytes Allocated       : " << bytesTotal
                << std::endl;
    }
      break;
      
    case '+':  // Increments the current object selected in the array
    {  
      if ( currObj == 19 )
      {
        std::cout << std::endl << "You are already at Packet Switch #19." << std::endl;
      }
      else
      {
        currObj++;
        std::cout << std::endl << "Packet Switch #" << currObj << " is now selected." << std::endl;
      }
    }  
      break;
      
    case '-':  // Decrements the current object selected in the array
    {  
        if ( currObj == 0 )
        {
          std::cout << std::endl << "You are already at Packet Switch #0." << std::endl;
        }
        else
        {
          currObj--;
          std::cout << std::endl << "Packet Switch #" << currObj << " is now selected." << std::endl;
        }
    }  
      break;
      
    case '#':  // Sets the current selected object in the array
    {
      int usrChoice;

      std::cout << std::endl << "Which Packet Switch would you like to jump to? (Enter 0-19): ";
      (*in_stream) >> usrChoice;
      
      if ( 0 <= usrChoice && usrChoice <= 19 )
      {
        currObj = usrChoice;
        std::cout << std::endl << "Packet Switch #" << currObj << " is now selected." << std::endl;
      }
      else
      {
        std::cout << std::endl << "The choice you entered is not valid!" << std::endl;
      }
    }
      break;
      
    case '0':  // Clears the data in the current object in the array
    
      ps1[currObj].clearPacketSwitch();
      
      break;
      
    case '>':  // Creates a new network object in the network array
      { 
        int currNet = 0;
      
        while( !( net1[currNet].isNetEmpty() ) && (currNet < maxNetwork) )
        {
          currNet++;
        }
          
        if( currNet == maxNetwork )
        {
          std::cout << std::endl << 
          " You have already reached your maximum number of Networks allowed!" << std::endl;
        }
        else
        {
          std::string usrString;
          int nodes;
          
          getline((*in_stream), usrString, ' ');
        
          std::cout << std::endl << " Enter the SSID of the network: ";
          getline((*in_stream), usrString, ' ');
          net1[currNet].set_ssid( usrString );
        
          std::cout << std::endl << " Enter the IP Address of the network: ";
          getline((*in_stream), usrString, ' ');
          net1[currNet].set_netIP( usrString );
          
          std::cout << std::endl << " Enter the number of nodes on the network: " << std::endl;
          (*in_stream) >> nodes;
          net1[currNet].set_nodes( nodes );
        }
      }
      break;
      
    case 'I':  // Sets the network index for the current packet switch object
    {
      int netIndex;
    
      std::cout << std::endl << " Enter the Network Index of the current Packet Switch: ";
      (*in_stream) >> netIndex;
      ps1[currObj].set_netPtr( &net1[netIndex] ); 
    }  
      break;
 
    case 'D':  // Displays data for the current Packet Switch object
    
      std::cout << std::endl << "  Packet Switch # " << currObj << ps1[currObj] << std::endl;   

      break;

    case 'V':  // Allows user to enter new switch vendor
      {      
        std::string vendor;
       
        getline((*in_stream), vendor, ' ');
       
        std::cout << "Enter Packet Switch Vendor : ";
        getline((*in_stream), vendor, ' ');
        ps1[currObj].set_vendor(vendor);
      }
      break;
     
    case 'M':  // Allows user to enter new switch model
      {      
        std::string model;
       
        getline((*in_stream), model, ' ');
       
        std::cout << "Enter Packet Switch Model : ";
        getline((*in_stream), model, ' ');
        ps1[currObj].set_model(model);
      }
      break;
     
    case 'N':  // Allows user to enter a new number of ports for the switch
      {
        int num_ports;
        std::cout << "Enter Number of Ports in Packet Switch : ";
        (*in_stream) >> num_ports;
        ps1[currObj].set_ports(num_ports);
      }
      break;
      
    case 'T':  // Allows user to enter new switch per port speed
      {
        int pps;
        std::cout << "Enter Per Port Speed of Packet Switch (in Mbps) : ";
        (*in_stream) >> pps;
        ps1[currObj].set_pps(pps);
      }
      break;
      
    case 'E':  // Allows user to enter new switch power consumption
      {
        int power;
        std::cout << "Enter Power Consumption of Packet Switch (in Watts) : ";
        (*in_stream) >> power;
        ps1[currObj].set_power(power);
      }
      break;
      
    case 'S':  // Allows user to enter new switch dimensions
      {
        float height, width, depth;
        std::cout << "Enter Dimensions - height, width, depth - of the Packet Switch (enter H W D) : ";

        (*in_stream) >> height;
        (*in_stream) >> width;
        (*in_stream) >> depth;

        ps1[currObj].set_dimensions(height, width, depth);
      }
      break;
      
    case 'C':  // Adds a component to the current packet switch object
      {
        packetSwitch *currPS = &ps1[currObj];
        int index = 0;
        std::string compName;
        double compPowerRating, compPrice;
        
        getline((*in_stream), compName, ' ');
        
        // Iterate through the components until an empty one is found
        while( !( currPS -> get_comp(index) -> isCompEmpty() ) )
        {
          index++;
        }
      
        std::cout << "Enter a name for the Component you would like to add : ";
        getline((*in_stream), compName, ' ');
        currPS->get_comp(index)->set_compName(compName);
      
        std::cout << std::endl << "Enter the Power Rating for the Component you would like to add : ";
        (*in_stream) >> compPowerRating;
        currPS->get_comp(index)->set_compPowerRating(compPowerRating);
      
        std::cout << std::endl << "Enter the Price of the Component you would like to add : ";
        (*in_stream) >> compPrice;
        currPS->get_comp(index)->set_compPrice(compPrice);

      }  
      break;
      
    case 'R':  // Sets Ethernet Switch Rating
    
      // NO CODE ADDED YET!!!
      break;
      
    case 'W':  // Sets Wireless Router IEEE Standard
    
      // NO CODE ADDED YET!!!
      break;
      
    case 'X':  // Sets Wireless Router Data Rate
    
      // NO CODE ADDED YET!!!
      break;
      
    case 'F':  // Sets Packet Size for Wireless or Ethernet
    
      // NO CODE ADDED YET!!!
      break;
      
    case 'A':  // Displays Ethernet Switches sorted by rating
    
      // NO CODE ADDED YET!!!
      break;

    case 'P':  // Prints the user choice menu

      print_menu();
      
      break;
    
    case 'Q':  // Quits the program

      done = true;
      
      break;

    default:  // Prints an error message if an invalid input is entered
   
      std::cout << "Invalid Syntax. Try Again." << std::endl;
      
      break;
  }
 
  return 0;
}


//////////////////////////////////////////////
// Print Menu - prints the user choice menu //
//////////////////////////////////////////////

int print_menu()
{
  std::cout << std::endl <<
    "/*************************************************************/" << std::endl <<
    "/*************************** MENU ****************************/" << std::endl <<
    "/*************************************************************/" << std::endl <<
    "/*                                                           */" << std::endl <<
    "/*              0 - 19: Ethernet Switch Objects              */" << std::endl <<
    "/*             20 - 39: Wireless Router Objects              */" << std::endl <<
    "/*             40 - 59: Packet Switch Objects                */" << std::endl <<
    "/*    --------------------------------------------------     */" << std::endl <<
    "/*     *  : Display Data For All Objects                     */" << std::endl <<
    "/*     B  : Display Program Memory Usage                     */" << std::endl <<
    "/*     +/-: Change The Current Object In The Array           */" << std::endl <<
    "/*     #  : Set The Selected Object                          */" << std::endl <<
    "/*     0  : Clear The Selected Object's Data                 */" << std::endl <<
    "/*     >  : Create A New Network                             */" << std::endl <<
    "/*     I  : Set The Network Index For The Current Obect      */" << std::endl <<
    "/*     D  : Display The Selected Object's Data               */" << std::endl <<
    "/*     V  : Set Packet Switch Vendor                         */" << std::endl <<
    "/*     M  : Set Packet Switch Model                          */" << std::endl <<
    "/*     N  : Set Packet Switch Number of Ports                */" << std::endl <<
    "/*     T  : Set Packet Switch Per Port Speed                 */" << std::endl <<
    "/*     E  : Set Packet Switch Power Consumption              */" << std::endl <<
    "/*     S  : Set Packet Switch Dimensions [H W D]             */" << std::endl <<
    "/*     C  : Add Packet Switch Component                      */" << std::endl <<
    "/*     R  : Set The Rating Of The Ethernet Switch            */" << std::endl <<
    "/*     W  : Set The IEEE Standard Of The Wireless Router     */" << std::endl <<
    "/*     X  : Set The Data Rate Of The Wireless Router         */" << std::endl <<
    "/*     F  : Set Packet Size For Ethernet Or Wireless         */" << std::endl <<
    "/*     A  : Display Ethernet Switches Sorted By Rating       */" << std::endl <<
    "/*     P  : Print This Menu                                  */" << std::endl <<
    "/*     Q  : Quit This Program                                */" << std::endl <<
    "/*                                                           */" << std::endl <<
    "/*************************************************************/" << std::endl;

  return 0;
}


//       END OF PROGRAM
// AND ALL THIS OTHER FUN STUFF