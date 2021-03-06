#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <iomanip>//only for testing
#include <fstream>
#include <ctype.h>
#include <math.h>



using namespace std;
int step_number=1;


void print_vector(vector<vector<float>> &current_step);
void add_one_neuron(vector<float> &neuron, vector<vector<float>> &current_step);
void read_line_and_parse(vector<float> &current_neuron, vector<vector<float>> &current_step, string line);
void open_dynamics(vector<float> &current_neuron, vector<vector<float>> &current_step, string filename);
void standart_deviation(vector<vector<float>> &current_step);
void write_result(float result1, float result2);




//void parse_string(vector< float > & inVect)
void print_vector(vector<vector<float>> &current_step)
{   
    for(int y=0;y<current_step.size();++y)
     {
         for(int x=0;x<current_step[y].size();++x)
         {
    	    	cout << fixed << setprecision(3) << current_step[y][x]<<" ";
         }
         cout<<'\n';
     }
}



void add_one_neuron(vector<float> &neuron, vector<vector<float>> &current_step)
{
		current_step.push_back(neuron);
		neuron.clear();
}
void read_line_and_parse(vector<float> &current_neuron, vector<vector<float>> &current_step, string line)
{
	//cout<<"parsing string"<<'\n';
	float s_float;
	istringstream buf(line);
	istream_iterator<string> beg(buf), end;
	vector<string> tokens(beg, end); // string to vector
	for(auto& s: tokens)
	{
		//cout << fixed << setprecision(3) << current_step[y][x] << '\n';
		s_float=strtof((s).c_str(),0);
		current_neuron.push_back(s_float);
	}
	add_one_neuron(current_neuron,current_step);

}
void open_dynamics(vector<float> &current_neuron, vector<vector<float>> &current_step, string filename)
{
	string line;
  	ifstream myfile (filename);
  	if (myfile.is_open())
  	{   
	    while ( getline (myfile,line) )
	    {   //cout<<line.front()<<'\n';
			if (line.front()==' '||line.empty()||line.front()=='\t')
			{
				cout<<"step"<<"\n";
				standart_deviation(current_step);
				current_step.clear();
				
			}
			else
			{
				read_line_and_parse(current_neuron,current_step,line);
			}
			
	    }
    myfile.close();
  	}
	else 
	{cout << "Unable to open file"; }

}
void standart_deviation(vector<vector<float>> &current_step)
{
	//average
	float sum1=0;
	float sum2=0;
	for(int y=0;y<current_step.size();++y)
    {
         
         	sum1=current_step[y][1]+sum1;
         	sum2=current_step[y][3]+sum2;
         
        
    }
    cout<<"sum1="<<sum1<<'\n';
    cout<<"sum2="<<sum2<<'\n';
    float average1=sum1/current_step.size();
    float average2=sum2/current_step.size();

    float dif_sum1=0;
    float dif_sum2=0;

    for(int y=0;y<current_step.size();++y)
    {
         
         		dif_sum1=pow((current_step[y][1]-average1),2);
         		dif_sum2=pow((current_step[y][3]-average1),2);

    }
    float result1=sqrt(dif_sum1/current_step.size());
    float result2=sqrt(dif_sum2/current_step.size());
    cout<<"result1="<<result1<<'\n';
    cout<<"result2="<<result2<<'\n';
	if(isnan(result1)||isnan(result2))
	{cout<<"error bad data detected"<<'\n';}
	else
	{
	//write result to file
	write_result(result1,result2);
	step_number++;
	}
}
void write_result(float result1, float result2)
{
  ofstream myfile;
  myfile.open ("result.txt",ios::app);
  myfile<< step_number <<" "<< result1<<" "<<result2<<"\n";
  myfile.close();
}
//void string(string s)
int main()
{	
	vector<vector<float>> current_step;
	vector<float> current_neuron;
	string filein="phase.txt";
    open_dynamics(current_neuron,current_step,filein);
	//print_vector(current_step);
    

}

