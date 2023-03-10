
double func1(double* pos,int dim);
double func2(double* pos,int dim);
double func3(double* pos,int dim);
double func4(double* pos,int dim);
double func5(double* pos,int dim);
double func6(double* pos,int dim);
double func7(double* pos,int dim);
double func8(double* pos,int dim);
double func9(double* pos,int dim);

double getlrand(double upper,double lower);

class particle{
public:
double *velocity;
double *position;
double *localg;

void init(int dimsize);

		};
		
class swarm{
public:
particle *p;
double *globalg;
int popsize,dim;
double upper,lower,lrt,deltag,deltap,w;
double (*evalfunc)(double *pos,int dim);

swarm(int number,int dimsize);
void initialise(double w_,double deltag_,double deltap_,double 
lrt_,double upper_,double lower_,double (*evalfunc_) (double* 
pos,int dim));
void printout();
void mainloop(int iter_);
int inbounds(double* pos);		
		};





