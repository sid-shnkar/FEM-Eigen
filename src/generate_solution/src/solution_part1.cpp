#include <cstdio>
#include<bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cmath>


/**
 * function to write the node numbers, analytical solution, numerical solution and error(analytical-numerical)
 * to a csv file called 'solution_part1.csv' for problem 1
**/
void write_csv(int size, std::vector<double> analytical, std::vector<double> numerical, std::vector<double> error_vals, double rms_error)
{

    // Create an output filestream object
    std::fstream fout;
    fout.open("solution_part1.csv", std::ios::out);

     fout<<"Node number, Analytical Solution, Numerical Solution, Error"<<"\n";
    // Send data to the stream
    for (int i = 0; i < size; ++i)
    {
        fout<<i<<","<<analytical[i]<<","<<numerical[i]<<","<<error_vals[i]<<"\n";
    }

    fout<<"\n"<<"RMS Error: "<<rms_error;
    // Close the file
    fout.close();
}


/**
 * function to find the root mean square error from the vector called error_vals
**/
double findRMS(std::vector<double> error_vals){
    double square = 0;
    double mean = 0.0, root = 0.0;
 
    // Calculate square.
    for (int i = 0; i < error_vals.size(); i++) {
        square += pow(error_vals[i], 2);
    }
 
    // Calculate Mean.
    mean = (square / (double)(error_vals.size()));
 
    // Calculate Root.
    root = sqrt(mean);
 
    return root;
}


/**
 * main function uses the fstream library to read and write to csv files
 * Also, it calculates the node wise error values and also the overall RMS error
**/
int main(int argc, char *argv[])
{

    std::fstream analytical1;
    std::fstream numerical1;

    analytical1.open("outputs_csv/analytical1.csv", std::ios::in);

    numerical1.open("outputs_csv/numerical1.csv", std::ios::in);

    std::vector<std::string> analytical1_rows_strings;
    std::vector<std::string> numerical1_rows_strings;
    std::string line, temp;

    //reading analytical solution (displacement values) for problem 1
    while(!analytical1.eof()){
        getline(analytical1, line);
        analytical1_rows_strings.push_back(line);
    }

    //reading numerical solution (displacement values) for problem 1
    while(!numerical1.eof()){
        getline(numerical1, line);
        numerical1_rows_strings.push_back(line);
    }

        analytical1.close();
        numerical1.close();

    // this will remove double quotes from the string if present
    for (auto &s : analytical1_rows_strings)
        s.erase(remove(s.begin(), s.end(), '\"'), s.end());

    // this will remove double quotes from the string if present
    for (auto &s : numerical1_rows_strings)
        s.erase(remove(s.begin(), s.end(), '\"'), s.end());
    

    std::vector<double> analytical1_rows_doubles;
    std::vector<double> numerical1_rows_doubles;

    //converting string values to double for error calculation
    for (auto it = analytical1_rows_strings.begin(); it != analytical1_rows_strings.end(); it++) {
        analytical1_rows_doubles.push_back(stod(*it));
     }

    //converting string values to double for error calculation
    for (auto it = numerical1_rows_strings.begin(); it != numerical1_rows_strings.end(); it++) {
        numerical1_rows_doubles.push_back(stod(*it));
     }

    //storing error values(numerical - analytical)
    // analytical_rows_doubles.size() == numerical1_rows_doubles.size()
    int size=analytical1_rows_doubles.size();
    std::vector<double> error_vals;

    for(int i=0; i < size; i++){
        error_vals.push_back(analytical1_rows_doubles[i]-numerical1_rows_doubles[i]);
    }

    //finding the Root Mean Square Error
   double rms_error=findRMS(error_vals);

    // write the final solution to 'solution_part1.csv' file
    write_csv(size, analytical1_rows_doubles, numerical1_rows_doubles, error_vals, rms_error);

    return 0;
}
