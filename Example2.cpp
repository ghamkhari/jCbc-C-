#include<iostream>
#include"jCbc.hpp"
#include<string>

using namespace std;
int main (int argc, char** argv)
{

//cout<<argv[1]<<endl;

OsiClpSolverInterface* solver =  new OsiClpSolverInterface(); 
CbcModel* Model = new CbcModel;

assignSolver(Model,solver); 

readLp(solver, argv[1]);

solve(Model,solver);

int nCols=getNumCols(Model);
const double* sol = new double[nCols]; 
sol = getColSolution(solver); 

cout<<"Solution:"; 

cout<<"Objective_Value="<<getObjValue(Model)<<endl; 

for (int j = 0; j < nCols; j++){
if ( isInteger(Model,j)==1) 

cout<<"x["<<j<<"]="<<sol[j]<<endl; 
}

delete Model;
     
     
	return 0;
}