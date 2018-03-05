#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <cassert>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>

using namespace std;


//The function create new file and write values
void Write(double * data, double mode, char* f_name, int num)
{
	int i;
	//open file
	FILE* fp;
	fp = fopen(f_name,"w");
	//judge if it is NULL
	if(fp==NULL)
		cout<<"Error Message!"<<endl;
	else
	{
		//get the file name
		fprintf(fp, "%d %.4f\n",num, mode);
		for(i=0;i<num;i++)	//write contents into.
			fprintf(fp, "%.4f\n",data[i]);
		//close file.
		fclose(fp);
	}
	
}

//The function do the scale operation
double * scale_F(int * data, float scale, int num, int n_file){
	char sc_name[30];
	int i=0;
	double buf;
	double result[1024];
	//get the file name.
	sprintf(sc_name, "Scaled_data_%02d.txt",n_file);
	cout<<endl<<"Scaled file created!!"<<endl;
	//calculate the result array.
	while(i<num)
	{
		buf=(double)data[i]*scale;
		result[i]=buf;
		i++;
	}
	//call the write function to create new file.
	Write(result, scale, sc_name, num);
	return result;
}

//The function do the offset operation
double * offset_F(int * data, float offset, int num, int n_file)
{
	char sc_name[30];
	int i=0;
	double buf;
	double result[1024];
	//get the file name.
	sprintf(sc_name, "Offset_data_%02d.txt",n_file);
	cout<<endl<<"Offset file created!!"<<endl;
	//calculate the result array.
	while(i<num)
	{
		buf=(double)data[i]+offset;
		result[i]=buf;
		i++;
	}
	//call the write function to create new file.
	Write(result, offset, sc_name, num);
	return result;
}

//The function do the rename.
void rename_F(int * data, int num, int max, char* new_name)
{
	int i;
	
	FILE* fp;
	char sc_name[30];
	//get the file name and open the file.
	sprintf(sc_name,"%s.txt",new_name);
	fp = fopen(sc_name,"w");
	cout<<"New file created name "<<sc_name<<endl;
	//judge if it is NULL.
	if(fp==NULL)
		cout<<"Error Message!"<<endl;
	else
	{
		//get the first two values.
		fprintf(fp,"%d %d\n",num,max);
		
		//write contents into.
		for(i=0;i<num;i++)
			fprintf(fp,"%d\n",data[i]);
		//close file.
		fclose(fp);
	}
}

//The function do the average.
double Average(int * data, int num)
{
	double sum=0,ave;
	int i;
	//calculate.
	for(i=0;i<num;i++)
		sum+=data[i];
	ave = sum/num;
	return ave;
}

//The function get the max value.
double Max(int * data, int num)
{
	int Max,i;
	Max=data[0];
	//calculate.
	for(i=1;i<num;i++)
	{
		if(Max<data[i])
			Max=data[i];
	}
	return Max;
}

//The function do the statistic operation.
void Statistic(int * data, int num, int n_file)
{
	char sc_name[30];
	FILE* fp;
	int max;
	double ave;
	//get the file name and open the file.
	sprintf(sc_name, "Statistic_data_%02d.txt", n_file);
	cout<<endl<<"Statistic file created name "<<sc_name<<endl;
	//get the max and average value.
	max=Max(data, num);
	ave=Average(data, num);
	//open file.
	fp = fopen(sc_name,"w");
	//judge if it is NULL.
	if(fp==NULL)
		cout<<"Error Message!"<<endl;
	else
	{
		//write into and close file.
        fprintf(fp,"%.4f %d\n",ave,max);
        fclose(fp);		
	}
}

//The function do the normalize operation.
void Normalize(int * data, int num, int n_file)
{
	char sc_name[30];
	double scale;
	double result[1024];
	int max,min,i;
	//get the file name 
	sprintf(sc_name, "Normalized_data_%02d.txt", n_file);
	cout<<endl<<"Normalized file created name "<<sc_name<<endl;
	
	//looping for the min and max.
	max=data[0];
	min=data[0];
	
	for(i=0;i<num;)
	{
		i++;
		if(data[i]>max)
		{max=data[i];}
		if(data[i]<min)
		{min=data[i];}
	}
	i=0;
    while(i < num){
        if (min == max){
            // if min and max are equal, the scale is 0.5
            result[i] = data[i] * 0.5;
            scale = 0.5;
        }
        else{
            // find scale so i can print it to the file
            result[i] = ((double)(data[i] - min)/(double)(max - min));
            if (data[i]!= 0){
                scale = result[i] / data[i];
            }
            
        }
        i++;
    }	
	//call the function write.
	Write(result, scale, sc_name, num);
}

//The function do the Center operation.
void Center(int * data, int num, int n_file)
{
	char sc_name[30];
	double ave;
	double result[1024];
	int i;
	
	//get the file name.
	sprintf(sc_name, "Centered_data_%02d.txt", n_file);
	cout<<"Centered file created "<<sc_name<<endl;
	//get the average value.
	ave=Average(data, num);
	
	//do the center operation.
	for(i=0;i<num;i++)
		result[i]=data[i] - ave;
	
	ave = ave * -1;
	Write(result, ave, sc_name, num);
}







int main(int argc, char * argv[])

{
	int i=1,j=0;
	int stat=0,center=0,normal=0;
	int num, max;
	int data[100];
	int n_file=0;
	float scale=1, offset=0;
	char* rename=NULL;
	double* Result;
	//string filename="Raw_data_";
	char filename[15];
	
	//looping to get the user's mind from calling program arguments.
	while(i<argc)
	{
		//using switch to fit different situations.
		switch (argv[i][1]){

			//case of number of file.
			case 'n':{	//judge if it is valuable
				if(argv[i+1] == NULL){
                        printf("Please enter a file number!!\n");
                        return EXIT_FAILURE; // I found this way to terminate early
                    }
				n_file = atoi(argv[++i]);
				i++;
				break;
			}
			
			//case of offset.
			case 'o':{	//judge if it is valuable
					if(argv[i+1] == NULL){
                        printf("Please enter offset value!!\n");
                        return EXIT_FAILURE; // I found this way to terminate early
                    }
					//update offset value.
					offset = atof(argv[++i]);
					i++;
					break;
					}
				
			//case of scale.	
			case 's':{	//judge if it is valuable
					if(argv[i+1] == NULL){
                        printf("Please enter scale value!!\n");
                        return EXIT_FAILURE; // I found this way to terminate early
                    }
					//update scale value.
					scale = atof(argv[++i]);
					i++;
					break;
			}
			
			//case of rename.
			case 'r':{	//judge if it is valuable
					if(argv[i+1] == NULL){
                        printf("Please enter the new name!!\n");
                        return EXIT_FAILURE; // I found this way to terminate early
                    }
					//update new name.
					rename = argv[++i];
					i++;
					break;
			}
			
			//case of help.
			case 'h':{
				cout<<endl<<"The arguments should be:"<<endl
				<<"For example: ./My_Lab4_program –s 1.7 –S –N –n 9 –o -2.4 –r NewName –C"<<endl;
				return EXIT_FAILURE;
				break;
			}
			
			//case of statistic.
			case 'S':{
				stat=1;	//set flag
				i++;
				break;
			}
			
			//case of normalize.
			case 'N':{
				normal=1;	//set flag
				i++;
				break;
			}
			
			//case of center.
			case 'C':{
				center=1;	//set flag
				i++;
				break;
			}
			
			
			
			//default.
			default: {
				cout<<"Error Message!!"<<endl;
				i++;
				return EXIT_FAILURE;
				break;}
				
				
			
		}
		
	}
	
		//judge if there is the number of file.
	if(n_file==0)
	{
		cout<<"Error Message!! value of -n needed!!"<<endl;
		return EXIT_FAILURE;
	}

	//stream of file to print the contents of the file.
	ifstream infile;
	
	sprintf(filename, "Raw_data_%02d.txt",n_file);
	cout<< filename<<endl;
	
	infile.open(filename);
	string c;
	while(getline(infile,c)){
		cout<<c<<endl;
	}
	infile.close();
	
	int buffer;
	//open the file.
	FILE* fp;
	fp = fopen(filename, "r");
	//get the first two values about elements numbers and max value.
	fscanf(fp, "%d %d", &num,&max);
	cout<<"The numbers of the file is "<<num<<". And the max of numbers is "<<max<<endl;
	
	//reading the file.
	while(!feof(fp)){
		fscanf(fp,"%d",&buffer);
		data[j]=buffer;
		j++;
	}
	//close the file.
	fclose(fp);
	
	
	//judge if the value of scale changed.
	if(scale!=1)
	{
	Result=scale_F(data, scale, num, n_file);
	}
	//judge if the value of offset changed. 
	if(offset!=0)
	{
	Result=offset_F(data, offset, num, n_file);
	}
	//judge if the content of new name changed.
	if(rename!=NULL)
	{
	rename_F(data, num, max, rename);
	}

	//judge the flag of statistic.
	if(stat==1)
	{
	Statistic(data, num, n_file);
	}	
	//judge the flag of normalize.
	if(normal==1)
	{
	Normalize(data, num, n_file);
	}	
	//judge the flag of center.
	if(center==1)
	{
	Center(data, num, n_file);
	}		

	return 0;
}
