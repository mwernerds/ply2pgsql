/*
ply2pgsql
Copyright (C) 2017 M. Werner

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <iostream>
#include <pqxx/pqxx> 
#include<sstream>
#include "ikg_pc.hpp"
#include<limits>


using namespace std;
using namespace pqxx;

void _progress(double progress,int barWidth = 70)
{
    progress  = std::min(1.0, progress);
    std::cout<< "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
    }


   std::string format_insert(double x, double y, double z)
   {
     std::stringstream ss;
        ss.precision(std::numeric_limits<double>::max_digits10);

     ss << "INSERT INTO points(X,Y,Z) VALUES (" << x <<"," << y << "," << z <<");" << endl;
     
     return ss.str();
   }


int main(int argc, char* argv[]) {
   connection C("dbname = points user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");

    try {
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }
      C.disconnect ();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }
  // DB open.
  
   std::string sql;
   ikg::ScanReader sr;
   sr.read(argv[1],false);
   
   
   
      /* Create a transactional object. */
      work W(C);
  try{    
      /* Execute SQL query */
      for (size_t i=0; i < sr.vertices.size() / 2; i++)
      {
	double x = sr.vertices[2*i], y = sr.vertices[2*i+1], z = sr.z[i];
        W.exec( format_insert(x,y,z) );
        if (i%100 == 0) {cout << argv[1] <<":"; _progress( (double) i / (sr.vertices.size()/2), 50);};
      }
      W.commit();
      cout << "Records created successfully" << endl;
      C.disconnect ();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;

  
   
}


