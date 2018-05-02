#include<iostream>
#include<vector>
#include<cstdlib>
#include<chrono>
#include<random>
#include<fstream>
#include<string>
#include<math.h>
#include<ctime>

using namespace std;

// Seed initialisation
//unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
random_device rd;
double dl = 0.001;
// Marsene Twister initialisation
mt19937 gen(rd());

// Print Vectors
void print_vec(vector<double>& x)
{
	for(int i=0;i<x.size();i++)
	{
		cout<<x[i]<<endl;
	}
}
/*
// Function to evalute the value of integral
double trapezoidal(vector<double> x, vector<double> y)
{
    // Grid spacing
    double a = x.front(), b =x.back();
    double h = x[1]-x[0];
 
    // Computing sum of first and last terms
    double s = y.front()+y.back();
 
    // Adding middle terms
    for (int i = 1; i < n; i++)
        s += 2*y(a+i*h);
 
    // h/2 indicates (b-a)/2n. Multiplying h/2
    // with s.
    return (h/2)*s;
}
*/

vector<double> definite_integral(vector<double> x, vector<double> y, vector<double> tau_list)
{
	vector<double> integral_list;
	integral_list.resize(tau_list.size());
	double integral = 0;
	int k=0;
	for(int i=0;i<(x.size()-1);i++)
	{
		integral += ((y[i] + y[i+1]) / 2 * (x[i+1] - x[i]));
		if(x[i+1]==tau_list[k])
		{
			//cout<<"tau="<<tau_list[k]<<endl;
			integral_list[k]=integral/tau_list[k];
			k++;
		}
	}
	return(integral_list);
}

double V(double x,double y)
{
	return(5*(cos(x)+cos(y)));
	//return(0);
}

vector<double> gradV(double x,double y)
{
	double DxV,DyV;
	DxV = (V(x+(dl/2),y)-V(x-(dl/2),y))/dl;
	DyV = (V(x,y+(dl/2))-V(x,y-(dl/2)))/dl;
	vector<double> grad{DxV,DyV};
	return(grad);
}

const string currentDateTime() 
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return(buf);
}

int main()
{
	double start_time = clock();
	normal_distribution<double> normal_dist(0.0,1.0);
	uniform_real_distribution<double> uniform_dist(0.0,2*M_PI);
	//double random_number;
	//random_number = distribution(gen);
	
	double dt = 0.001;
	double D,Dr,Fa,tau;
	double X,Y,theta,power,vel_x,vel_y;
	double x_noise,y_noise,theta_noise;
	unsigned int N;
	int i, j, k, t_max;
	vector<double> Fext,tau_list,work;
	
	tau_list = {1.0,2.0,3.0,4.0,5.0};
	int tau_list_length = tau_list.size();
	
	Dr = 1.0;
	cout<<"Enter Fa: ";
	cin>>Fa;
	cout<<"Enter D: ";
	cin>>D;
	tau = 5.0;
	N = 1000000;
	
	t_max = tau / dt;
	
	vector<double> work_list;
	work_list.resize(N);
	vector<double> power_list;
	power_list.resize(t_max);
	
	vector<double> time_list;
	time_list.resize(t_max+1);
	for(i=0;i<=t_max;i++)
	{
		time_list[i] = i*dt;
	}
	//print_vec(time_list);
	string date_and_time(currentDateTime());
	string folder_name ("Output/Power_Output/");
	string file_name=folder_name+date_and_time+"-power-D="+to_string(D)+"_Dr="+to_string(Dr)+"_Fa="+to_string(Fa)+"_N="+to_string(N)+"_tau="+to_string(tau)+".csv";
	//cout<<"Data being written into "<<file_name<<endl;
	ofstream fp;
	//fp.open(file_name.c_str());
	cout<<"D="<<D<<" Dr="<<Dr<<" Fa="<<Fa<<endl;
	
	folder_name = "Output/";
	file_name = folder_name+date_and_time+"-entropy-production-D="+to_string(D)+"_Dr="+to_string(Dr)+"_Fa="+to_string(Fa)+"_N="+to_string(N)+"_tau="+to_string(tau)+"-with-Potential.csv";
	cout<<"Data being written into "<<file_name<<endl;
	
	//ofstream fp;
	fp.open(file_name.c_str());
	
	for(k=0;k<tau_list_length;k++)
	{
		fp<<tau_list[k]<<",";
	}
	fp<<"\n";
	
	for(i=0;i<N;i++)
	{
		//cout<<"Calculating Trajectory #"<<i<<endl; 
		if(i%(N/100)==0)
		{
			cout<<i<<endl;
		}
		
		X = 0;
		Y = 0;
		theta = uniform_dist(gen);
		//cout<<theta<<endl;
		for(j=0;j<=t_max;j++)
		{
			x_noise = normal_dist(gen);
			y_noise = normal_dist(gen);
			theta_noise = normal_dist(gen);
			
			Fext = gradV(X,Y);
			vel_x = Fa * cos(theta) - Fext[0];
			vel_y = Fa * sin(theta) - Fext[1];
			//cout<<Fext[0]<<","<<Fext[1]<<endl;
			//X = X + Fa * cos(theta) * dt + sqrt(2 * D * dt) * x_noise;
			//Y = Y + Fa * sin(theta) * dt + sqrt(2 * D * dt) * y_noise;
			//power = (Fa * cos(theta) + sqrt(2 * D) * x_noise) * (Fa * cos(theta)) + (Fa * sin(theta) + sqrt(2 * D) * y_noise) * (Fa * sin(theta));
			
			X = X + vel_x * dt + sqrt(2 * D * dt) * x_noise;
			Y = Y + vel_y * dt + sqrt(2 * D * dt) * y_noise;
			power = (vel_x + sqrt(2 * D / dt) * x_noise) * vel_x + (vel_y + sqrt(2 * D / dt) * y_noise) * vel_y;
			
			power_list[j] = power;
			theta = theta + sqrt(2 * Dr * dt) * theta_noise;
			//cout<<X<<","<<Y<<","<<theta<<endl;
			//fp<<power<<",";
		}
		work = definite_integral(time_list,power_list,tau_list);
		//work_list[i] = work;
		//fp<<"\n";
		for(k=0;k<tau_list_length;k++)
		{
			fp<<work[k]<<",";
		}
		fp<<"\n";
	}
	//fp.close();
	/*
	for(i=0;i<t_max;i++)
	{
		power_list[i]=time_list[i]*time_list[i]*time_list[i];
	}
	*/
	//cout<<definite_integral(time_list,power_list);
	//print_vec(time_list);
	//print_vec(work_list);
	
	//string date_and_time(currentDateTime());
	/*
	for(i=0;i<N;i++)
	{
		fp<<work_list[i]<<"\n";
	}
	*/
	fp.close();
	cout<<"Time elapsed: "<<(clock()-start_time)/CLOCKS_PER_SEC<<" seconds"<<endl;
	return(0);
} 
