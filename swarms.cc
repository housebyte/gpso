#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <ctime>
#include "particle.h"

using namespace std;


void particle::init(int dimsize){

velocity = new double[dimsize];
position = new double[dimsize];
localg   = new double[dimsize];

         }


swarm::swarm(int number,int dimsize){
popsize = number;
dim = dimsize;

globalg = new double[dimsize];

p = new particle[number];

for(int i=0;i<number;i++){
p[i].init(dim);
         		  }
					}

void swarm::initialise(double w_,double deltag_,double deltap_,double 
lrt_,double upper_,double lower_,double (*evalfunc_) (double* 
pos,int dim))
{
upper=upper_;
lower=lower_;
lrt=lrt_;
deltag=deltag_;
deltap=deltap_;
w=w_;
evalfunc=evalfunc_;

srand(time(NULL));

for(int j=0;j<dim;j++){
globalg[j] = getlrand(lower,upper);
}


for(int i=0;i<popsize;i++){

for(int j=0;j<dim;j++){

p[i].position[j] = getlrand(lower,upper);
p[i].velocity[j] = getlrand(lower,upper);
p[i].localg[j] = p[i].position[j]; 

}				


if(evalfunc(p[i].localg,3)<evalfunc(globalg,3)){

for(int k=0;k<dim;k++)
globalg[k] = p[i].localg[k];

						}


			}


				}
            
void swarm::printout(){

if(0){
for(int i=0;i<popsize;i++){

cout << "partical" <<i<<" ";

for(int j=0;j<dim;j++){
cout << p[i].position[j] << ",";
			}
cout<<"\n";
				  }
      }

cout << "Global Best = " <<evalfunc(globalg,3) << "," <<globalg[0]<<" "<<globalg[1]<< "\n";
		

}

void swarm::mainloop(int iter_){

double rp[dim],rg[dim];

for(int iter=0;iter<iter_;iter++){

cout << "Global Best = " <<evalfunc(globalg,3) << "," <<globalg[0]<<" "<<globalg[1]<< "\n";
			
for(int i=0;i<popsize;i++){

for(int j=0;j<dim;j++){

rp[j] = getlrand(-1,1);
rg[j] = getlrand(-1,1);

//Update velocity
p[i].velocity[j] = w*p[i].velocity[j] + deltap * rp[j] * (p[i].localg[j]-p[i].position[j]) + deltag*rg[j]*(globalg[j]-p[i].position[j]);

//Update position
p[i].position[j] = p[i].position[j] + lrt * p[i].velocity[j];

//Restrict to bounded
if(p[i].position[j]>=upper){
p[i].position[j]=0;
			}

if(p[i].position[j]<=lower){
p[i].position[j]=0;
				}

				

//cout<<p[i].position[0]<<"************\n";

			}

			
if(evalfunc(p[i].position,3)<evalfunc(p[i].localg,3)){

for(int k=0;k<dim;k++)
p[i].localg[k] = p[i].position[k];
						}			

if(evalfunc(p[i].localg,3)<evalfunc(globalg,3)){

for(int k=0;k<dim;k++)
globalg[k] = p[i].localg[k];
						}

				}
		}
}

int swarm::inbounds(double* pos){

int count=0;
int ret;

for(int i=0;i<dim;i++){

if(lower<pos[i]<upper){
count++;
}
				}
if(count==dim){ret=1;}else{ret=0;}

return ret;
}


double func1(double* pos,int dim){

/*dim=3 DeJongs Sphere*/

return pow(pos[0],2) + pow(pos[1],2) + pow(pos[3],2);

}

double func2(double* pos,int dim){

/*dim=2 Schaefer n2*/
double t1,t2;

t1 = sin(sqrt(pow(pos[0],2)+pow(pos[1],2)));
t2 = 1 + 0.001*(pow(pos[0],2)+pow(pos[1],2));

return 0.5+(t1*t1-0.5)/pow(t2,2);

}

double func3(double* pos,int dim){

/*dim=2 Schaffer n4*/
double t0,t1,t2,t3,t4;

t0 = pow(pos[0],2)-pow(pos[1],2);
t1 = pow(pos[0],2)+pow(pos[1],2);
t2 = sqrt(pow(t0,2)); 
t3 = pow(cos(sin(t2)),2)-0.5;
t4 = pow((1+0.001*t1),2);

return 0.5 + t3/t4;

}

/*
double func4(double* pos,int dim){

//dim=2 Holder table
double t0,t1,t2,t3,t4;

t0 = 1-(sqrt(pow(pos[0],2)+pow(pos[1],2))/M_PI);
t1 = abs(t0);
t2 = sin(pos[0])*cos(pos[1])*exp(t1);
return -abs(t2);
}

*/

double func4(double* pos,int dim){

/*dim=2 Holder Table*/

double t0,t1;

t0 = sin(pos[0])*cos(pos[1]);
t1 = exp(abs(1-sqrt(pow(pos[0],2)+pow(pos[1],2))/M_PI));

return -abs(t0*t1)+5.5;

}


double func5(double* pos,int dim){

/*dim=2 Ackley*/
double t0,t1,t2,t3,t4;

t0 = -0.2*sqrt(0.5*(pow(pos[0],2)+pow(pos[1],2)));
t1 = -20*exp(t0);
t2 = exp(0.5*(  cos(2*M_PI*pos[0]) + cos(2*M_PI*pos[1]) ));
t3 = exp(1)+20;

return t1 - t2 + t3;

}

double getlrand(double lower,double upper){

return ((double) rand()/ RAND_MAX) * (upper-lower) + lower;

}

double func6(double* pos,int dim){

/*Egg Holder - Note:too big for graph -now fits!!*/
double t0,t1,t2,t3,t4;
t3 = pos[0]*50;
t4 = pos[1]*10;

t0 = -t3*sin(sqrt(abs(t3-(t4+47))));
t1 = -(t4+47)*sin(sqrt(abs((t3/2)+(t4+47))));

return 5.5+(t0 + t1)/70;
}

double func7(double* pos,int dim){

/*X in tray*/
double t0,t1,t2,t3,t4;

t0 = abs(100- ( sqrt (pow(pos[0],2)+pow(pos[1],2))/M_PI) );
t1 = sin(pos[0])*sin(pos[1])*exp(t0);
t2 = -0.0001*pow(abs(t1)+1,0.1);

return t2;
}


double func8(double* pos,int dim){

/*Booth*/
double t0,t1,t2,t3,t4;

t0 = pow((pos[0]+2*pos[1]-7),2) + pow((2*pos[0]+pos[1]-5),2);
return t0;
}

double func9(double* pos,int dim){

/*Levi function */
double t0,t1,t2,t3,t4;

t0 = pow(sin(3*M_PI*pos[0]),2);
t1 = pow((pos[0]-1),2)*(1+pow(sin(3*M_PI*pos[1]),2));
t2 = pow((pos[1]-1),2)*(1+pow(sin(2*M_PI*pos[1]),2));
return t0+t1+t2;
}

double func11(double* pos,int dim){

/*Goldstein-Price*/
double t0,t1,t2,t3;
t2 = pos[0]/20;
t3 = pos[1]/40;

t0 = 1+pow((t2+t3+1),2)*(19-14*t2+3*pow(t2,2)-14*t3+6*t2*t3+3*pow(t3,2));
t1 = 30+pow((2*t2-3*t3),2)*(18-32*t2+12*pow(t2,2)+48*t3-36*t2*t3+27*pow(t3,2));

return -17.5+(t0*t1)/70;
}

