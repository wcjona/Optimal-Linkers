#include <iostream> 
#include <fstream>
#include <string>
#include <math.h>
#include <cmath>


int main(){
  using namespace std;                   
  short loop;                              
  short loop2;                           
  string line, last;
  double x,y,z,x1,y1,z1, length;
  string index = " 23 ";
  string lastIndex = " 139 ";
  ifstream myfile("6mi5_default.pdb");    
  int count = 0;    
  bool firstCA = true; 
  if (myfile.is_open())                  
  {
    while (! myfile.eof() )                
    {
      getline (myfile,line);            
      size_t found = line.find(index);
      size_t found1 = line.find("ATOM");
      size_t found2 = line.find("CA");
      size_t found3 = line.find(lastIndex);
      string temp; 
      if( found2!=string::npos && firstCA && found1!=string::npos){
        x = stod(line.substr(31,38));
        y = stod(line.substr(39,46));    
        z = stod(line.substr(47,54)); 
        firstCA = false; 
        //cout << line <<  endl;   
      }if(found3!=string::npos && found1!=string::npos && found2!=string::npos){
        x1 = stod(line.substr(31,38));
        y1 = stod(line.substr(39,46));    
        z1 = stod(line.substr(47,54)); 
        //cout << line <<  endl;   
        length = sqrt(pow(x1-x,2)+pow(y1-y,2)+pow(z1-z,2));
        cout << length << endl;
        firstCA = true; 
      }
    }
    myfile.close(); 

  }
  else cout << "Unable to open file";  
      
}