#include<fstream>
#include<iostream>
#include<time.h>
#include<sstream>
#include <string>
#include<cmath>
#include "memory.h"
#include <map>
#include <vector>
#include <algorithm>
using namespace std;


class Pengfei_DIY_Func
{
	public:
		double StringToDouble(string d_str);
		int StringToInt(string d_str);
		string DoubleToString(double d_num);
		string IntToString(int d_num);
		string RepStrInit(string d_str1,string d_str2,int d_num);
		string ReplaceAllTender(string d_str,string d_old_value,string d_new_value);
		string ReplaceAllRude(string d_str,string d_old_value,string d_new_value);
		string Trim(string d_str);
		string Split(string d_str,const char * d_split,string d_each[],int &d_num);
		double Var_Wei_jack(double d_fx[],double d_fx_all,int d_chunks,int d_each_num[],int d_marker_num);
		double Ave(double d_data[],int d_num);
		double Var(double d_data[],int d_num);
		int Allele_adjust(string d_ori_snp,string d_ref_snp);
		string Allele_convert(string d_snp);

};

class Distance
{ 	
	private: 
 		double distance; 
 		string ident; 
	public: 
		Distance(double distance,string ident)
		{
			this->distance=distance;
			this->ident=ident;
		}
		double get_distance() 
 		{ 
			return distance; 
		}
		string get_ident() 
		{ 
			return ident; 
		}
};


bool comparer(Distance m_a, Distance m_b)  
{ 
        return (m_a.get_distance() < m_b.get_distance());  
}
bool comparer2(double a, double b)  
{ 
        return (a < b);  
}


//*****************************************
//*****************************************
//*****************************************

int main(int argc,char *argv[])
{
	int sp_rep_num=1000;//repeats
	int sp_cell_num=100;//spl cell num
	int sp;
	vector<Distance> vec;
	int i=0,g=0,j=0,k=0,m=0,n,l,c,pop;
		ofstream outfile;
		ifstream infile;
		string str_line;
		string infilename,outfilename;
		string str_temp[50000];
		int locus_num=0;
		string str_swap;
		char * p;
		const char * split = "\t";
		map<string,string> map_rsid;


	string samplestr=argv[1];
	int k1,k2;
	srand((unsigned)time(NULL));
	int rndnum1;

	Pengfei_DIY_Func myfunc;
	int cell_num;
	int gene_num;

	double sum=0;
	double sum_all=0;
	int count1=0;		
	int count2=0;		
        string gene_id[5000];
        string gene_name[5000];
	int count_all;
        string ident_ref[1000];
        string ident_obj[1000];
        int ident_num_ref;
        int ident_num_obj;
        string ident_list_ref[100];
        string ident_list_obj[100];
        int sample_num;
	int cell_num_ref;
	int cell_num_obj;
	double dis_ref[50];
	double prob[50][50];
       
	j=0;
        infilename="temp_out/s6_"+samplestr+".txt";
        infile.open(&infilename[0],ios::in);
        while(!infile.eof())
        {
                str_line="";
                getline(infile,str_line);
                if(str_line.length()<1)continue;
                j++;
		k=0;
		p = strtok(&str_line[0],split);
		while(p!=NULL)
		{
			str_temp[k++]=p;
			p = strtok(NULL,split);
		}
                dis_ref[j-1]=myfunc.StringToDouble(str_temp[0]);
//              ident_list_ref[j-1]=str_temp[1];
        }
        infile.close();infile.clear();
//      ident_num_ref=j;
//	cout<<j<<endl;

        j=0;
        infilename="data_ref/cell_type_list.txt";
        infile.open(&infilename[0],ios::in);
        while(!infile.eof())
        {
                str_line="";
                getline(infile,str_line);
                if(str_line.length()<1)continue;
                j++;
                ident_list_ref[j-1]=str_line;
        }
        infile.close();infile.clear();
        ident_num_ref=j;
//        cout<<j<<endl;
/*
	
        string drop_ref[100];
        j=0;
        infilename="data_ref/drop_list_ref.txt";
        infile.open(&infilename[0],ios::in);
        while(!infile.eof())
        {
                str_line="";
                getline(infile,str_line);
                if(str_line.length()<1)continue;
                j++;
                k=0;
                p = strtok(&str_line[0],split);
                while(p!=NULL)
                {
                        str_temp[k++]=p;
                        p = strtok(NULL,split);
                }
                drop_ref[j-1]=str_temp[1];
        }
        infile.close();infile.clear();
*/



double dis_sp[30][10000];
for(i=0;i<ident_num_ref;i++)
{

	j=0;
	infilename="temp_out/s6_distri_"+samplestr+"_"+myfunc.IntToString(i+1)+".txt";
	infile.open(&infilename[0],ios::in);
	while(!infile.eof())
	{
		str_line="";
		getline(infile,str_line);
		if(str_line.length()<1)continue;
		j++;
		dis_sp[i][j-1]=myfunc.StringToDouble(str_line);
	}
	infile.close();infile.clear();

}
//cout<<"read in sampling dis-results "<<endl;

        double bf[50];
        sum=0;
for(i=0;i<ident_num_ref;i++)
{
	bf[i]=0;
//        if(drop_ref[i]=="0")continue;

	for(j=0;j<ident_num_ref;j++)
	{
//        	if(drop_ref[j]=="0")continue;
		count1=0;
		for(k=0;k<sp_rep_num;k++)
		{
			if(dis_ref[i]>dis_sp[j][k])count1++;
		}
		prob[i][j]=double(count1)/sp_rep_num;
	}
        sum=0;
	for(j=0;j<ident_num_ref;j++)
        {
                sum=sum+prob[i][j];
        }
        bf[i]=prob[i][i]/sum;
        if(sum==0)bf[i]=0;
}
        cout<<"cal Bayes Factor ... done."<<endl;


	outfilename="temp_out/s7_bf_"+samplestr+".txt";
	outfile.open(&outfilename[0],ios::out);
	for(i=0;i<ident_num_ref;i++)
	{
		outfile<<ident_list_ref[i]<<"\t"<<bf[i]<<endl;	
	}
	outfile.close();outfile.clear();

cout<<"output "<<outfilename<<endl;




}
//*****************************************
//*****************************************
//*****************************************

double Pengfei_DIY_Func::StringToDouble(string d_str)
{
	double d_num;
	stringstream d_sstr;
	d_sstr<<d_str;
	d_sstr>>d_num;
	return d_num;
}

int Pengfei_DIY_Func::StringToInt(string d_str)
{
	int d_num;
	stringstream d_sstr;
	d_sstr<<d_str;
	d_sstr>>d_num;
	return d_num;
}

string Pengfei_DIY_Func::DoubleToString(double d_num)
{
	string d_str;
	stringstream d_sstr;
	d_sstr<<d_num;
	d_sstr>>d_str;
	return d_str;	
}

string Pengfei_DIY_Func::IntToString(int d_num)
{
	string d_str;
	stringstream d_sstr;
	d_sstr<<d_num;
	d_sstr>>d_str;
	return d_str;	
}

string Pengfei_DIY_Func::RepStrInit(string d_str1,string d_str2,int d_num)
{
	for(int d_i=0;d_i<d_num;d_i++)
	{
		d_str1+=d_str2;
	}
	return d_str1;
}

string Pengfei_DIY_Func::ReplaceAllTender(string d_str,string d_old_value,string d_new_value)
{   
    for(string::size_type d_pos(0);d_pos!= string::npos;d_pos+= d_new_value.length())
	{
		if((d_pos=d_str.find(d_old_value,d_pos))!= string::npos)d_str.replace(d_pos,d_old_value.length(),d_new_value);
		else break;
	}
	return d_str;
}

string Pengfei_DIY_Func::ReplaceAllRude(string d_str,string d_old_value,string d_new_value)
{   
	while(true)
	{
		string::size_type d_pos(0);
		if((d_pos=d_str.find(d_old_value))!=string::npos)
			d_str.replace(d_pos,d_old_value.length(),d_new_value);
		else break;
	}
	return d_str;
}

string Pengfei_DIY_Func::Trim(string d_str)
{
	int d_len=d_str.length();
	int d_i=0,d_j=0;
	string d_str2;
	for(d_i=0;d_i<d_len;d_i++)
	{
		if(d_str[d_i]!=' ')break;
	}
	for(d_j=d_len-1;d_j>=0;d_j--)
	{
		if(d_str[d_j]!=' ')break;
	}
	d_str2.assign(d_str,d_i,d_j-d_i+1);
	return d_str2;
}

string Pengfei_DIY_Func::Split(string d_str,const char * d_split,string d_each[],int &d_num)
{   
	char * d_p;
	int d_k=0;
    d_p = strtok(&d_str[0],d_split); 
	while(d_p!=NULL)
	{ 
		d_each[d_k++]=d_p;
		d_p = strtok(NULL,d_split); 
	}
	return d_str;
}
double Pengfei_DIY_Func::Ave(double d_data[],int d_num)
{
	double d_sum1=0;
	int d_i=0;
	for(int d_i=0;d_i<d_num;d_i++)
	{	
		d_sum1+=d_data[d_i];
	}
	return d_sum1/d_num;
}

double Pengfei_DIY_Func::Var(double d_data[],int d_num)
{
	double d_sum1=0;
	double d_sum2=0;
	double d_mean=0;
	int d_i=0;
	for(int d_i=0;d_i<d_num;d_i++)
	{	
		d_sum1+=d_data[d_i];
	}
	d_mean=d_sum1/d_num;
	for(d_i=0;d_i<d_num;d_i++)
	{	
		d_sum2+=pow(d_data[d_i]-d_mean,2);
	}
	return d_sum2/(d_num-1);
}

double Pengfei_DIY_Func::Var_Wei_jack(double d_fx[],double d_fx_all,int d_chunks,int d_each_num[],int d_marker_num)
{
	double d_sum1=0;
	double d_sum2=0;
	int d_i=0;
	double d_h=0;
	int d_chunks_valid=0;
	for(int d_i=0;d_i<d_chunks;d_i++)
	{		
		if(d_each_num[d_i]!=0)d_chunks_valid++;
	}
	for(int d_i=0;d_i<d_chunks;d_i++)
	{	
		if(d_each_num[d_i]==0)continue;
		d_sum2+=(1-(double)d_each_num[d_i]/d_marker_num)*d_fx[d_i];
	}
	for(int d_i=0;d_i<d_chunks;d_i++)
	{
		if(d_each_num[d_i]==0)continue;
		d_h=(double)d_marker_num/d_each_num[d_i];
		d_sum1+=pow(d_h*d_fx_all-(d_h-1)*d_fx[d_i]-d_chunks_valid*d_fx_all+d_sum2,2)/(d_h-1);
	}
	return pow(d_sum1/d_chunks_valid,0.5);
}

string Pengfei_DIY_Func::Allele_convert(string d_snp)
{
	if(d_snp=="A")return "T";
	else if(d_snp=="T")return "A";
	else if(d_snp=="G")return "C";
	else if(d_snp=="C")return "G";
	else return "N";
}
	
int Pengfei_DIY_Func::Allele_adjust(string d_ori_snp,string d_ref_snp)
{
	if(d_ori_snp[0]==d_ref_snp[0]&&d_ori_snp[1]==d_ref_snp[1])return 1;//ok
	else if(d_ori_snp[0]==d_ref_snp[1]&&d_ori_snp[1]==d_ref_snp[0])
	{
		if(d_ori_snp[0]=='A'&&d_ori_snp[1]=='T')return -9;//unsure, need to be deleted
		else if(d_ori_snp[0]=='T'&&d_ori_snp[1]=='A')return -9;
		else if(d_ori_snp[0]=='C'&&d_ori_snp[1]=='G')return -9;
		else if(d_ori_snp[0]=='G'&&d_ori_snp[1]=='C')return -9;
		else return 2;//be ref strand, but disordered 
	}	
	else if(d_ori_snp=="AG")
	{
		if(d_ref_snp=="TC")return -1;
		else if(d_ref_snp=="CT")return -2;
		else return -9;
	}
	else if(d_ori_snp=="AC")
	{
		if(d_ref_snp=="TG")return -1;
		else if(d_ref_snp=="GT")return -2;
		else return -9;
	}
	else if(d_ori_snp=="TC")
	{
		if(d_ref_snp=="AG")return -1;//not ref strand,change to opposite allele
		else if(d_ref_snp=="GA")return -2;//not ref strand, change to opposite allele, also disordered.
		else return -9;
	}	
	else if(d_ori_snp=="TG")
	{
		if(d_ref_snp=="AC")return -1;
		else if(d_ref_snp=="CA")return -2;
		else return -9;
	}
	else if(d_ori_snp=="CA")
	{
		if(d_ref_snp=="GT")return -1;
		else if(d_ref_snp=="TG")return -2;
		else return -9;
	}
	else if(d_ori_snp=="CT")
	{
		if(d_ref_snp=="GA")return -1;
		else if(d_ref_snp=="AG")return -2;
		else return -9;
	}
	else if(d_ori_snp=="GA")
	{
		if(d_ref_snp=="CT")return -1;
		else if(d_ref_snp=="TC")return -2;
		else return -9;
	}
	else if(d_ori_snp=="GT")
	{
		if(d_ref_snp=="CA")return -1;
		else if(d_ref_snp=="AC")return -2;
		else return -9;
	}
	else return -10;//absolutely wrong
}



