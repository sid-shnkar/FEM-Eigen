#include "../inc/analytical.h"
#include <cstdio>
#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <fstream>

/**
 * function to write the displacement (u) values for analytical solution
 * to a csv file called 'analytical2.csv'
**/
void write_csv(std::vector<double> vals)
{

    // Create an output filestream object
    std::fstream fout;
    fout.open("analytical2.csv", std::ios::out);


    // Send data to the stream
    //std::cout<<"vals size: "<<vals.size()<<"\n";

    for (int i = 0; i < vals.size(); ++i)
    {
        if(i==vals.size()-1){
            fout<<0;
        }else{
            fout << vals.at(i) << "\n";
        }
    }

    // Close the file
    fout.close();
}

/**
 * main function accepts command line arguments(P, A0, L, E, N)
 * Also, it calculates the value of displacement for all elements and write it to a csv file
**/
int main(int argc, char *argv[])
{
     //creating an object of template class Domain
    Domain<double> myDomain(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]));

    if (argc != 6)
    {
        std::cout << "No. of arguments recieved does not match with that required by program" << std::endl;
        return 1;
    }

    // print the arguments received
    std::cout<<"\n\n--------------Values received by analytical2.out--------------\n";
    myDomain.print();

    // For N elements, total no. of nodes will be N+1

    //creating a N+1 by 1 u values array
    std::vector<double> u_array(myDomain.getN() + 1);

    //using the formula derived for displacement i.e. u(x) as mentioned in report, we find displacements
    for (int i = 0; i <= myDomain.getN(); i++)
    {
        u_array[i] = ((myDomain.getP() * myDomain.getL()) / (myDomain.getE() * myDomain.getA0())) * (log((2 * myDomain.getL()) / (myDomain.getL() + (i * myDomain.getL() / myDomain.getN()))));
    }

    //print the displacements(u_array)
    // for (int i = 0; i <= myDomain.getN(); i++)
    // {
    //     std::cout << u_array[i] << std::endl;
    // }

    // write the displacements calculated to 'analytical2.csv' file
    write_csv(u_array);

    return 0;
}
