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
  string index = " 72   ";
  int indexSize = 0;
  string numbers[4] =  {"6","8","10","15"};       
  string letters[2] = {"P","O"};

  for(string number:numbers){
    for(string number1:numbers){
      for(string letter:letters){
        indexSize = 0;
        x= 0, y = 0, z = 0, x1 = 0, y1 = 0, z1 = 0;
        string filename = "BRET" + number + "_" + number1 + "_" + letter +".pdb";
        //cout << filename << endl; 
        ifstream myfile (filename);        
        if (myfile.is_open())                  
        {
          while (! myfile.eof() )                
          {
            getline (myfile,line);            
            size_t found = line.find(index);
            size_t found1 = line.find("ATOM");
            size_t found2 = line.find("CA");
            size_t found3 = line.find("TYR");
            string temp; 
            if(found!=string::npos && found1!=string::npos && found2!=string::npos && found3!=string::npos){
              
              x = stod(line.substr(31,38));
              y = stod(line.substr(39,46));    
              z = stod(line.substr(47,54)); 
            // cout << x << " " << y << " " << z  <<  endl;
            //cout << line <<  endl;   
            }if(found2!=string::npos){
              last = line;
              indexSize++;
            }
          }
          myfile.close(); 
          ifstream myfile1 (filename); 
          while (! myfile1.eof() )                
          {
            getline (myfile1,line);            
            string index1 = " " + to_string(indexSize-144) + " ";
            size_t found = line.find(index1);
            size_t found1 = line.find("ATOM");
            size_t found2 = line.find("CA");
            size_t found3 = line.find("GLY");
            if(found!=string::npos && found1!=string::npos && found2!=string::npos && found3!=string::npos){
              x1 = stod(line.substr(31,38));
              y1 = stod(line.substr(39,46));    
              z1 = stod(line.substr(47,54)); 
            // cout << x << " " << y << " " << z  <<  endl;
           // cout << line <<  endl;  

            }
          }
          myfile1.close(); 
          //cout << last << endl;
          length = sqrt(pow(x1-x,2)+pow(y1-y,2)+pow(z1-z,2));
          cout << length << endl; 

        }
        else cout << "Unable to open file";  
      }
      //cout << endl;
    }
  }
}