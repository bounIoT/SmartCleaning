# SmartCleaning
CmpE 490 IoT Course Final Project, 2018 Spring, Bogazici University Computer Engineering Department
# Description of the project

Problem: cleaning is done regularly, not optimized  
Solution:
-Counting the numbers of the door activity
-Showing these data in UI.
-Showing red warning for high activity
-Button to reset the counters for user

# Team Members

Enes Bekereci  
N. Totikos  
Emir Gökdemir  

# Repository Structure 
* Node: Code for embedded processing and connectivity
* Cloud: Code for nodered and ui
* Figures
   * Screenshot of UI 
   * Screenshot of nodes

### Technology
Arduino, Wifi Module, Switch, Bluemix IOT Platform Starter

### Hardware setup
Arduino is used with Wifi Module. Three switch is connected to digital inputs of Arduino.

### Flow of data 
-Arduino sends the digital inputs to Bluemix IOT Platform. Arduino code is used. Takes input from switches, sen it to cloud.
-Data is read with nodered. Digital data is taken from node.
-It is compared with old data. It is done by cloud code.
-Send result to counter.  It is done in bluemix.
-UI takes data from counter. Displays on the web.

### Development Environment
Node Red v0.18.5  
Google Chrome v66.0.3359.181  
Arduino v1.8.5

