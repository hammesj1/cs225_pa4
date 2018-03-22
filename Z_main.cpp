////////////////////////////////////////////////////////////////////////////////////////////////
// CS225 Spring 2016
// Evelyn Brown
// Programming Assignment #4
////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CS225HW4_CPP
#define CS225HW4_CPP

#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h> // isatty header file

// Project Classes: class packetSwitch is defined in packetswitch.hpp
#include "packetswitch.hpp" 
#include "ethernetswitch.hpp"
#include "wirelessrouter.hpp"

using namespace std;

///////////////////////////////////////////////////////////
// Global variables
#define ARR_MAX 60
#define PER_GROUP 20

//Function Prototypes
int processMenuIn(string);
void printMenu();
int initMixedArray();
int memoryDisplay();

bool interactive = true;
bool done = false;
PacketSwitch  **mixedArrayPtr;      // Used to pass a reference to the array between functions
PacketSwitch  **curPSwitch;         // Used to keep track of the current position in the array
Network *networkArray;      
Network *curNetwork;                // Used to keep track of the current network object in the array

const int maxNetworkArray = 10;

PacketSwitch *mixedArray[ARR_MAX];   //Declaring the mixed array to a packet switch pointer



////////////////////////////////////////////////////////////////////////////////////////////////
//Main Function
int main()
{

  initMixedArray();                    //Initializing the mixed array to the different objects

  string inputLine;
  
  mixedArrayPtr = mixedArray;          // points to an array of pointers
  curPSwitch = mixedArray;             // current position is the first array element

  interactive = isatty(STDIN_FILENO);  // true: user entry mode. false: test script mode
  if (interactive) printMenu();        // if user entry mode, print the menu options
  
  //Creating an array of Network Objects
  Network localNetworkArray[maxNetworkArray];
  networkArray = localNetworkArray;
  curNetwork = localNetworkArray;
  
  
  // While loop that circles through the menu and does whatever the user asks
  // Loop will terminate after the user has pressed 'Q' 
  string menuIn;
  while (!done)
  {
    cout << endl << "Menu [" << (curPSwitch - mixedArray) << "] :";
    getline(cin, inputLine);
    processMenuIn(inputLine); //call a function to process user input
  }
  
  cout << "Goodbye!" << endl;
  return 0;
} //End of main() function

/////////////////////////////////////////////////////////////////////////////////////////////
// Process Menu Funtion Definition
int processMenuIn(string menuLine)
{

  char menuChar; 
  
  istringstream inString(menuLine);
  inString >> menuChar; // extract the first character in the inString, ie. the menu option 
  istream *inStream;    // a pointer to an istream class object
  
  if(interactive)
    inStream = &cin;    // points to the cin object to that the next user input can be read
  else
    inStream = &inString;  // points to the rest of the file contained in inString
  
  switch(toupper(menuChar)) //use switch statement to process the chosen menu option
  {
  //Case to display all objects with non-default data
  case '*':
    {
      int i; //iteration variable to loop through the for loop
      for(i = 0; i < ARR_MAX; i++)
        {
          if(!static_cast<EthernetSwitch*>(mixedArrayPtr[i])->isEmptyEthernet() && i <= 19)
            {
            cout << "Ethernet Switch " << i << " : " << endl;
            cout << *(static_cast<EthernetSwitch*> (mixedArrayPtr[i]));
            }
          
          if(i >=20 && i <= 39 && !static_cast<WirelessRouter*>(mixedArrayPtr[i])-> isEmptyWireless())
            {
            cout << "Wireless Router " << i << " : " << endl;
            cout << *(static_cast<WirelessRouter*> (mixedArrayPtr[i]));
            }
            
          if(i>=40 && !mixedArrayPtr[i]->isEmpty())
            {
            cout << "Packet Switch " << i << " : " << endl;
            cout << *(mixedArrayPtr[i]);
            }
        }
    }
    break;
  
  //Case to display memory usage
  case 'B':
    {
      memoryDisplay();
    }
    break;
  
  //Case to enable user to go to the next Packet Switch object in array
  case '+':
    {
      int curIndex;
      curIndex = curPSwitch - mixedArrayPtr;
        if((curPSwitch - mixedArrayPtr) < ARR_MAX)
          curPSwitch = &mixedArrayPtr[curIndex + 1];
        else 
          curPSwitch = mixedArrayPtr;
    }
    break;
    
  //Case to enable a user to got to the previous packet switch object in array
  case '-':
    {
      int curIndex;
      curIndex = curPSwitch - mixedArrayPtr;
        if((curPSwitch - mixedArrayPtr) >= 0)
          curPSwitch = &mixedArrayPtr[curIndex - 1];
        else 
          curPSwitch = &mixedArrayPtr[ARR_MAX - 1];
    }
    break;
  
  //Case to enable a user to go to a specific PacketSwitch object
  case '#':
    {
      int curIndex;
      cout << "Please enter a number between 0 and " << ARR_MAX - 1 << " :" << endl;
      (*inStream) >> curIndex;
//      cin.get();  // cin.get() functions are commented out for the file test cases
      if (curIndex < ARR_MAX && curIndex >= 0)
        curPSwitch = &mixedArrayPtr[curIndex];
      else 
        cout << "Please try again.";
    }
    break;
  
  
  //Case to clear the Packet Switch
  case '0':
    int curElement;  //The current element in the array
    curElement = curPSwitch - mixedArray; 
    if(curElement <= 19)
      static_cast<EthernetSwitch*> (*curPSwitch) -> clearAll();
    if(curElement >= 20 && curElement <= 39)
      static_cast<WirelessRouter*> (*curPSwitch) -> clearAll();
    if(curElement >= 40)
      (*curPSwitch)->clearAll();
    break;
    
  //Case to create a new network
  case '>':
    {
    int curNetworkIndex = curNetwork - networkArray;
    if((curNetwork - networkArray) < maxNetworkArray)
      {
      // Defining variables
      string networkLabel;
      string networkIPaddress;
      double networkSize;
      
      cout << "Please enter the new network label, IP address, and size : " << endl;
      (*inStream) >> networkLabel >> networkIPaddress >> networkSize;
//      cin.get();

      curNetwork->setNetwork(networkLabel, networkIPaddress, networkSize);
    
      //Incrementing the network so we don't overwrite the user's previous input
      curNetwork = &networkArray[curNetworkIndex + 1];
      }
    else
      cout << "WARNING: the array is full. Please clear a network and try again." << endl;

    }
    break;
    
  // Case to assign a network to a particular packet switch
  case 'I':
    {
      int assignedNetwork;
      
      cout << "Please indicate the network you wish to use: (0, 1, 2...) " << endl;
      (*inStream) >> assignedNetwork;
      (*curPSwitch)->setNetwork(networkArray + assignedNetwork);
    }
    break;
       
  //Case to display all of the Packet Switch Data
  case 'D':
    {
      int curPtr = curPSwitch - mixedArrayPtr;
      if(curPtr <= 19)
        cout << *(static_cast <EthernetSwitch*> (*curPSwitch));
      if(curPtr >= 20 && curPtr <= 39)
        cout << *(static_cast <WirelessRouter*> (*curPSwitch));
      if(curPtr >= 40)
        cout << **curPSwitch;
    }
    break;
  
  //Case to set the vendor name
  case 'V':
    {
      string newVendor;
      cout << "Enter Switch Vendor: ";
      getline((*inStream), newVendor);
//      cin.get();
      (*curPSwitch)->setVendor(newVendor); //use a PacketSwitch mutator method
    }
    break;
    
  //Case to set the model name  
  case 'M' :
    {
      string newModel;
      cout << "Enter Switch Model: ";
      getline((*inStream), newModel);
//      cin.get();
      (*curPSwitch)->setModel(newModel); 
    }
    break;
    
  //Case to set the number of ports the switch is using
  case 'N' :
    {
      int newNumOfPorts;
      cout << "Enter number of ports in the switch: ";
      (*inStream) >> newNumOfPorts;
//      cin.get();
      (*curPSwitch)->setNumPorts(newNumOfPorts);
    }
    break;
    
  // Case to set the PPS  
  case 'T':
    {
      int newPPS;
      cout << "Enter the new per-port-speed in Mbps: ";
      (*inStream) >> newPPS;
//      cin.get();
      (*curPSwitch)->setPPS(newPPS);
    }
    break;
    
  // Case to set the power in watts
  case 'E':
    {
      int newPower;
      cout << "Enter the new power consumption in Watts: ";
      (*inStream) >> newPower;
//      cin.get();
      (*curPSwitch)->setPower(newPower);
    }
    break;
    
  // Case to set the height, width, and depth of the object
  case 'S':
    {
      float newHeight, newWidth, newDepth;
      cout << "Enter Height, width, and depth of the Packet Switch: "; 
      (*inStream) >> newHeight >> newWidth >> newDepth;
//      cin.get(); 
      (*curPSwitch)->setDimensions(newHeight, newWidth, newDepth);
    }
    break;
    
  // Case to create a new component object
  case 'C':
    {  
    int compIndex = 0; //Variable to keep track of the current component
    
    while(compIndex < 20)
      {
        
        //retrieving the correct component in the array
        Component& psComp = (*curPSwitch)->getComponent(compIndex);
        
        if(psComp.isEmpty())
          {
            //Initializing Variables
            string compName;
            double compPower, compPrice;
        
            // Getting the input from the user.
            cout << "Please enter the component name, power rating, and price : ";
            (*inStream) >> compName >> compPower >> compPrice;
//            cin.get();
            psComp.setComponent(compName, compPower, compPrice);
            break;
          }
        
        compIndex++; //adding 1 to the iteration loop 
      }
    if(compIndex == 19)
      cout << "WARNING: You have reached the maximum amount of components you can enter!" << endl;
     
    }
    break;
    

  //Case to set the ethernet packet rating
  case 'R':
    {
      if((curPSwitch - mixedArray) <= 19)
        { 
          int r;
          cout << "Please enter the rating for the Ethernet Switch:  " << endl;
          (*inStream) >> r;
//          cin.get();
          (static_cast <EthernetSwitch*> (*curPSwitch))-> setRating(r);
        }
      else
        cout << "Please navigate to an Ethernet Switch and try again!" << endl;  
    }
    break;
    
  //Case to set the IEEE standard of the wireless router
  case 'W':
    {
      if((curPSwitch - mixedArray >= 20) && (curPSwitch - mixedArray <=39))
        {
          string ieee;
          cout << "Please enter the IEEE standard for the Wireless Router: " << endl;
          (*inStream)>> ieee;
//          cin.get();
          (static_cast <WirelessRouter*> (*curPSwitch)) -> setIeeeStd(ieee);
        }
      else
        cout << "Please navigate to a Wireless Router and try again!" << endl;
    }
    break;
    
  //Case to set the data rate of the wireless router
  case 'X':
    {
      if((curPSwitch - mixedArray >= 20) && (curPSwitch - mixedArray <= 39))
        {
          double dr;
          cout << "Please enter the data rate for the Wireles Router: " << endl;
          (*inStream) >> dr;
//          cin.get();
          (static_cast <WirelessRouter*> (*curPSwitch)) -> setDataRate(dr);
        }
      else
        cout << "Please navigate to a Wireless Router and try again!" << endl;
    }
    break;
    
  //Case to set the Packet Size for the Wireless Router or Ethernet Switch
  case 'F':
    { 
      if((curPSwitch - mixedArray >= 0) && (curPSwitch - mixedArray <= 39))
        {
          int ps;
          cout << "Please enter the packet size: " << endl;
          (*inStream) >> ps;
//          cin.get();
          if (curPSwitch - mixedArray <= 19)
            (static_cast <EthernetSwitch*> (*curPSwitch)) -> setPacketSize(ps);
          else
            (static_cast <WirelessRouter*> (*curPSwitch)) -> setPacketSize(ps);
        }
      else
        cout << "Please navigate to a Wireless Router or an Ethernet Switch!" << endl;
    }
    break;
    
  //Case to display Ethernet Switches according to their rating
  case 'A':
    {
      PacketSwitch** tempPtr;
      tempPtr = mixedArray;
      int i, j;
      EthernetSwitch tempArray[20];
      EthernetSwitch temp;
      // copy the mixed array into the temp array
      for(i = 0; i < 20; i++)
        tempArray[i] = *(static_cast<EthernetSwitch*> (*(tempPtr+i)));
        
      // Sorting the Array
      for(i = 0; i < 20; i++)
        {
          for (j = 0; j < 20; j++)
            {
              if(tempArray[i].getRating() > tempArray[j].getRating())
                { 
                  temp = tempArray[i];
                  tempArray[i] = tempArray[j];
                  tempArray[j] = temp;
                }
            }
        } 
      
      for(i = 0; i < 20; i++)
        if(!tempArray[i].isEmptyEthernet())
          {
            cout << "Ethernet Switch " << i << " : " << endl;
            cout << tempArray[i] << endl;
          }
    }
    break;
  
  //Case to print the menu again
  case 'P' :
    printMenu();
    break;

  //Case to quite the program
  case 'Q' :
    done = true;
    break;
    
  // Default case to catch any incorrect user input
  default:
    {
      cout << "Please input a valid entry!" << endl << endl;
      printMenu();
    }
    break;  
  }
  return 0;
}
  
////////////////////////////////////////////////////////////////////////
// Display Menu Function Definition
void printMenu(void)
{   
  cout << "////////////////////////////////////////////////////////////" << endl;
  cout << "00-19: Ethernet Switches" << endl;
  cout << "20-39: Wireless Routers" << endl;
  cout << "30-59: Packet Switches" << endl;
  cout << "*  : Display data for all Packet Switches" << endl;
  cout << "B  : Display program memory usage" << endl;
  cout << "+/-: Succeeding / Preceding packet Switch object within array" << endl;
  cout << "#  : Set the selected Packet Switch" << endl;
  cout << "0  : Clear Packet Switch data" << endl;
  cout << ">  : Create a new network" << endl;
  cout << "I  : Set the network index for Packet Switch" << endl; 
  cout << "D  : Display Packet Switch data" << endl;
  cout << "V  : Set Packet Switch Vendor" << endl;
  cout << "M  : Set Packet Switch Model" << endl;
  cout << "N  : Set the Number of Ports in Packet Switch $" << endl;
  cout << "T  : Set the Per-Port-Speed in Mbps " << endl;
  cout << "E  : Set the Power in Watts" << endl;
  cout << "S  : Set the size in inches of the Packet Switch" << endl;
  cout << "C  : Add Packet Switch component" << endl;
  cout << "R  : Set the Rating of the Ethernet Switch:" << endl;
  cout << "W  : Set the IEEE standard of the Wireless Router:" << endl;
  cout << "X  : Set the Data Rate of the Wireless Router:" << endl;
  cout << "F  : Set Packet Size for Ethernet switch or Wireless switch:" << endl;
  cout << "A  : Display Ethernet Switches sorted by their Rating" << endl;
  cout << "P  : Print this menu" << endl;
  cout << "Q  : Quit this program" << endl;
  cout << "///////////////////////////////////////////////////////////" << endl;
};


/////////////////////////////////////////////////////////////
// Global Mixed Array initialization loop
int initMixedArray()
{
  for (int i = 0; i < ARR_MAX; i++)  //global constant = 60
    {
      int type = (i / (PER_GROUP));  //global constant = 20
      
      switch(type)
      {
         case 0:
           mixedArray[i] = new EthernetSwitch();
           break;
           
         case 1:
           mixedArray[i] = new WirelessRouter();
           break;
           
         case 2:
           mixedArray[i] = new PacketSwitch();
           break;
         
         default:
           cout << "ERROR : in array initialize" << endl;
           return -1;
      }
    }
  return 0;
}

int memoryDisplay()
{
  int memory;
  //Finding an accurate count of base objects that are alive by subtracting the derived classes living packets from the base class
  int numAliveBase = ((PacketSwitch::getNumAlive() - EthernetSwitch::getNumAliveEthernet()) - WirelessRouter::getNumAliveWireless());
  cout << "There are " << numAliveBase  << " living Packet Switch objects" << endl;
  cout << "There are " << EthernetSwitch::getNumAliveEthernet() << " living Ethernet Switch objects" << endl;
  cout << "There are " << WirelessRouter::getNumAliveWireless() << " living Wireless Router objects" << endl;
  

  memory = ((numAliveBase * sizeof(PacketSwitch)) + (EthernetSwitch::getNumAliveEthernet() * sizeof(EthernetSwitch))
              + (WirelessRouter::getNumAliveWireless() * sizeof(WirelessRouter)));
  cout << "There are " << memory << " bytes of memory allocated";
  return 0;

}
         
#endif