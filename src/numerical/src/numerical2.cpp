#include "../inc/numerical.h"
#include <cstdio>
#include<bits/stdc++.h>
#include <iostream>
#include <Eigen/Dense>
#include <fstream>

using namespace Eigen;

/**
 * function to write the displacement (u) values for analytical solution
 * to a csv file called 'numerical2.csv'
**/
void write_csv(Matrix<double, Dynamic,Dynamic> vals)
{

    // Create an output filestream object
    std::fstream fout;
    fout.open("numerical2.csv", std::ios::out);

    // Send data to the stream
    for (int i = 0; i < vals.size(); ++i)
    {
        fout << vals(i) << "\n";
    }

    //for last u , it's displacement is 0
    fout << 0;

    // Close the file
    fout.close();
}

/**
 * function to remove last row from a given matrix (required for removing singularity whlie finding inverse) 
**/
void removeRow(Matrix<double, Dynamic,Dynamic>& matrix, unsigned int rowToRemove)
{
    unsigned int numRows = matrix.rows()-1;
    unsigned int numCols = matrix.cols();

    if( rowToRemove < numRows )
        matrix.block(rowToRemove,0,numRows-rowToRemove,numCols) = matrix.block(rowToRemove+1,0,numRows-rowToRemove,numCols);

    matrix.conservativeResize(numRows,numCols);
}

/**
 * function to remove last column from a given matrix (required for removing singularity whlie finding inverse) 
**/
void removeColumn(Matrix<double, Dynamic,Dynamic>& matrix, unsigned int colToRemove)
{
    unsigned int numRows = matrix.rows();
    unsigned int numCols = matrix.cols()-1;

    if( colToRemove < numCols )
        matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.block(0,colToRemove+1,numRows,numCols-colToRemove);

    matrix.conservativeResize(numRows,numCols);
}

// xA - i then xB - i+1
/**
 * Function to calculate the integral(I) for given parameters using Gauss Quadrature Method
 * For Numerical solution of Problem 2(variable area), we have used 1-point gauss quadrature
 * if xA = i then xB = i+1
**/
double gaussQuadrature(int diff1, int diff2, double E, double A0, int N, double L, double xA, double xB){
        // Initialise value of Integral of above function(phi(x)) with 0
        double I = 0;
        // 1-point gauss quadrature
        int n = 1;
        // lower limit of integral
        double a = xA*L/N;
        // upper limit of integral
        double b = xB*L/N;
        // defining phi(x), the function whose integral needs to be calculated
        double phi = (1+(a+b)/(2*L))*(diff1*diff2)*(E*A0*N*N)/(L*L);
        // alpha array is same as the weights array (w)
        // alpha1 = 2 for n=1
        int alpha[] = {2};
        // x1 = 0, so the formula for I reduces to the following
        for(int i=0; i<n; i++){
            I = I + alpha[i]*(((b-a)/2)*phi);
        }
        return I;
    }


/**
 * main function accepts command line arguments(P, A0, L, E, N)
 * Also, it calculates the value of displacement for all elements and write it to a csv file
 * 
**/
int main(int argc, char *argv[])
{
    //creating an object of template class Domain
    Domain<double> myDomain(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]));

    if (argc != 6)
    {
        std::cout<<"No. of arguments recieved does not match with that required by program"<<std::endl;
        return 1;
    }

    //print the arguments received
    std::cout<<"\n\n--------------Values received by numerical2.out--------------\n";
    myDomain.print();

   // For N elements, total no. of nodes will be N+1

    /* 
    Using the Eigen library (present at /nfs_home/nikhilh/eigen-3.3.9), we 
    create and calculate stiffness matrix, displacement vector and force vector
    */
    
   //creating a N+1 by N+1 global stiffness matrix called k_matrix , initiaised to 0
    Matrix<double, Dynamic,Dynamic> k_matrix=Matrix<double, Dynamic,Dynamic>::Zero(myDomain.getN() + 1, myDomain.getN() + 1);
    
    //creating a N by 4 elemental stiffness matrix called elemental_matrix , initiaised to 0
    Matrix<double, Dynamic,Dynamic> elemental_matrix=Matrix<double, Dynamic,Dynamic>::Zero(myDomain.getN(), 4);
    
    //creating a N+1 by 1 displacement vector(u) called u_vector , initiaised to 0
    Matrix<double, Dynamic,Dynamic> u_vector=Matrix<double, Dynamic,Dynamic>::Zero(myDomain.getN() + 1, 1);
    
    //creating a N+1 by 1 force vector called f_vector , initiaised to 0
    Matrix<double, Dynamic,Dynamic> f_vector=Matrix<double, Dynamic,Dynamic>::Zero(myDomain.getN() + 1, 1);
    

    //first element of the f -vector should be equal to P and rest all elements should be 0
    f_vector(0)=myDomain.getP();

     /*
    calculating the values for each element and storing it in it's elemental matrix
    here i denotes the ith element
    ith row contains 4 columns that corresponds to the ith's element 11,12,21 and 22 index K values
    if xA = i then xB = i+1
    */
    for(int i=0; i < myDomain.getN(); i++){
        elemental_matrix(i, 0) = gaussQuadrature(1, 1, myDomain.getE(), myDomain.getA0(), myDomain.getN(), myDomain.getL(), i, i+1);
        elemental_matrix(i, 1) = gaussQuadrature(-1, 1, myDomain.getE(), myDomain.getA0(), myDomain.getN(), myDomain.getL(), i, i+1);
        elemental_matrix(i, 2) = gaussQuadrature(1, -1, myDomain.getE(), myDomain.getA0(), myDomain.getN(), myDomain.getL(), i, i+1);
        elemental_matrix(i, 3) = gaussQuadrature(-1, -1, myDomain.getE(), myDomain.getA0(), myDomain.getN(), myDomain.getL(), i, i+1);
    }

     /*
    here i denotes the ith element
    we assemble the elemental stiffness matrices into a global stiffness matrix
    */
    for(int i = 0; i<myDomain.getN(); i++){
        k_matrix(i, i) += elemental_matrix(i, 0);
        k_matrix(i, i+1) += elemental_matrix(i, 1);
        k_matrix(i+1, i) += elemental_matrix(i, 2);
        k_matrix(i+1, i+1) += elemental_matrix(i, 3);
    }


    //print elemental_matrix
    //std::cout << elemental_matrix << std::endl<<std::endl<<std::endl;

    //print k_matrix
    //std::cout << k_matrix << std::endl<<std::endl<<std::endl;

    //print u_vector
    //std::cout << u_vector << std::endl<<std::endl<<std::endl;


    //print f_vector
    //std::cout << f_vector << std::endl<<std::endl<<std::endl;

    //removing last row and last column of k_matrix
    removeRow(k_matrix, myDomain.getN());
    removeColumn(k_matrix, myDomain.getN());

    //removing last row of u_vector
    removeRow(u_vector, myDomain.getN());

    //removing last row of f_vector
    removeRow(f_vector, myDomain.getN());

    /*
    calculating u_vector from KU=F matrix equation where K is global stiffness matrix,
    U is global displacement vector and F is global force vector
    */
    u_vector=k_matrix.inverse()*f_vector;

    //print u_vector
    //std::cout << u_vector << std::endl<<std::endl<<std::endl;

    //write the displacements calculated to 'numerical2.csv' file
    write_csv(u_vector);
    return 0;
}
