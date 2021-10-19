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
  string index = " 153   ";
  int indexSize = 0;


  indexSize = 0;
  for(int i = 1; i <= 101; i++){
    auto str = to_string(i);
    str.insert(0, 3 - str.size(), '0');

    string filename = "MDlanMLuc_" + str + ".pdb";
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

        string temp; 
        if(found!=string::npos && found1!=string::npos && found2!=string::npos){
          
          x = stod(line.substr(31,38));
          y = stod(line.substr(39,46));    
          z = stod(line.substr(47,54)); 
          //cout << line <<  endl;   
        }if(found2!=string::npos){
          indexSize++;
        }
      }
      myfile.close(); 
      line = "";
      ifstream myfile1 (filename); 
      
      while (! myfile1.eof() )                
      {
        getline (myfile1,line);    
        string index1 = " 292   ";   
        // string index1 = " " + to_string(indexSize-5) + "   ";
        size_t found = line.find(index1);
        size_t found1 = line.find("ATOM");
        size_t found2 = line.find("CA");
        if(found!=string::npos && found1!=string::npos && found2!=string::npos){
          x1 = stod(line.substr(31,38));
          y1 = stod(line.substr(39,46));    
          z1 = stod(line.substr(47,54)); 
          //cout << line <<  endl;  
        }
      }
      
      myfile1.close(); 
      //cout << last << endl;
      length = sqrt(pow(x1-x,2)+pow(y1-y,2)+pow(z1-z,2));
      cout << length << endl; 
      line = "";
    }
    else cout << "Unable to open file";  
  
  }
  
   
}
