
#include<iostream>
#include"jCbc.hpp"
#include<string>

using namespace std;
int main ()


{
  
  CoinModel* modelObject = new  CoinModel();
        
        OsiClpSolverInterface * solver =  new OsiClpSolverInterface();
    const double MAXX=100000000;
        double objValue[] = {1.0, 2.0, 4.0};
        double upper[] = {1.0, 10.0, MAXX};
        double lower[] = {0.0,-MAXX, 2.0};
        
        
        //define variables:
      addCol(modelObject,lower[0],upper[0],objValue[0],"x1",true);
      addCol(modelObject,lower[1],upper[1],objValue[1],"x2",false);
      addCol(modelObject,lower[2],upper[2],objValue[2],"x3",true);
        
        // this defines an integer array of length 2
       int * row1Index =  new int[2];
        // set the values of this array
        row1Index[0]=0;
        row1Index[1]=2;
        
        
        double * row1Value  = new double[2];
        row1Value[0]=1.0;
        row1Value[1]=3.0;
        
        //add row to CoinModel
        addRow(modelObject,2, row1Index, row1Value, 1.0, MAXX,"r1");
        
        int * row2Index = new int[3];
        row2Index[0]=0;
        row2Index[1]=1;
        row2Index[2]=2;
        
        
        double * row2Value = new double[3];
        row2Value[0]=-1.0;
        row2Value[1]= 2.0;
        row2Value[2]=-0.5;
        
        addRow(modelObject,3, row2Index, row2Value, -MAXX, 3.0,"r2");
        
        int * row3Index = new int[3];
        row3Index[0]=0;
        row3Index[1]=1;
        row3Index[2]=2;
        
        double*  row3Value = new double[3];
        row3Value[0]=1.0;
        row3Value[1]=-1.0;
        row3Value[2]=2.0;
        
        addRow(modelObject,3,row3Index,row3Value,7/2.,7/2.,"r3");
        
        //add all rows to OsiClpSolverInterface at once
        addRows(solver, modelObject);
        
        // This defines a new empty CbcModel
       CbcModel *  Model = new CbcModel();
        // Assign the solver to CbcModel
        assignSolver(Model,solver);
        
        
       setModelName(solver, "test");
        
        
        solve(Model,solver,0);
    //Model->branchAndBound();
    
         // get the solution
         double * sol = new double[3];
         sol = (double *)getColSolution(Model);
         
         // print solution 
         cout<<"Solution:"<<endl;
    
    if (Model->isProvenInfeasible()!=1)
    {
         cout<<"Objective_Value="<<getObjValue(Model)<<endl;
         for (int j = 0; j < 3; j++){
         cout<<getColName(solver,j)<<"="<<sol[j]<<endl;
         }
    }
    else{
        cout<<"Change the Model: Infeasible Problem"<<endl;}
    delete modelObject;
        delete Model;

        return 0;
}