#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct sailordata
{
	int ID;
	double rank, age;
	string name;
};

struct boatdata
{
	int ID;
	string name, color;
};

struct resdata
{
	int SID, BID;
	string date;
};

struct list
{
	int SID, BID;
};

struct finaldata
{
	double age, rank;
	string date, sailorname, boatname, color;
};

bool CorrectFileName(string filename)
{
	ifstream input;

	input.open(filename.c_str());

	if (input.fail())
	{
		return false;
	}
	input.close();
	return true;
}

int SIZE(string filename)
{
	ifstream input;
	string s;
	int  numLines = 0;
	input.open(filename.c_str());
	while (getline(input, s)){
		numLines++;
	}
	input.close();
	return numLines;
}


void print(const vector<finaldata> &finall)
{
	for (int i = 0; i < finall.size(); i++)
	{
		cout << finall[i].date <<" -> "<< finall[i].sailorname <<"("<< finall[i].age <<","<< finall[i].rank <<") has reserved "
			<< finall[i].boatname <<"("<<finall[i].color << ")" << endl;
	}
}

void Sort(vector<finaldata> &a)
{
    int j, k, minIndex, numElts = a.size();
	vector<finaldata> temp(a.size());
	for(k = 0; k < numElts - 1; k++)
	{
		minIndex = k;
		for(j=k+1; j < numElts; j++)
		{
			if (a[j].date < a[minIndex].date)
			{
				minIndex = j;
			}
			else if (a[j].date == a[minIndex].date)
			{
				if (a[j].sailorname < a[minIndex].sailorname){
					minIndex = j;
				}
			}
		}
		temp[k] = a[k];
		a[k] = a[minIndex];
		a[minIndex] = temp[k];
	}
}


int main()
{
	string resfile, Sailors = "Sailors.txt", Boats = "Boats.txt";
	ifstream resinput, boatinput, sailorinput;

	vector<boatdata> boats(SIZE(Boats)-1);
	vector<sailordata> sailors(SIZE(Sailors)-1);

	cout << "Enter filename for reservation database: ";
	cin >> resfile;
	
	if (CorrectFileName(resfile) == false)
	{
		cout << "Cannot open the files. Exiting..." << endl;
	}
	else
	{
		vector<resdata> reserves(SIZE(resfile)-1);

		sailorinput.open(Sailors.c_str());
		string sailorline;
		int i = 0;
		while (getline(sailorinput, sailorline))
		{
			if ( i > 0 )
			{
				istringstream linestream(sailorline);
				int sailorID;
				double rank, age;
				string sailorname;
				linestream >> sailorID >> sailorname >> rank >> age;

				sailors[i-1].ID = sailorID;
				sailors[i-1].name = sailorname;
				sailors[i-1].rank = rank;
				sailors[i-1].age = age;
			}
			i ++;
		}
		sailorinput.close();

		boatinput.open(Boats.c_str());
		string boatline;
		int j = 0;
		while (getline(boatinput, boatline))
		{
			if ( j > 0 )
			{
				istringstream linestream(boatline);
				int boatID;
				string boatname, color;
				linestream >> boatID >> boatname >> color;

				boats[j-1].ID = boatID;
				boats[j-1].name = boatname;
				boats[j-1].color = color;
			}
			j ++;
		}
		boatinput.close();

		resinput.open(resfile.c_str());
		string resline;
		int k = 0;
		while (getline(resinput, resline))
		{
			if (k > 0)
			{
				istringstream linestream(resline);
				int SID, BID;
				string date;
				linestream >> SID >> BID >> date;

				reserves[k-1].SID = SID;
				reserves[k-1].BID = BID;
				reserves[k-1].date = date;
			}
			k++;
		}
		resinput.close();

		vector<list> indexes(SIZE(resfile)-1);
		for (int s = 0; s < indexes.size(); s++)
		{
			for ( int t = 0; t < sailors.size(); t++)
			{
				if (sailors[t].ID == reserves[s].SID)
				{
					indexes[s].SID = t;
				}
			}
			for (int l = 0; l < boats.size(); l++)
			{
				if (boats[l].ID == reserves[s].BID)
				{
					indexes[s].BID = l;
				}
			}
		}

		vector<finaldata> finallist(SIZE(resfile)-1);
		for (int n = 0; n < finallist.size(); n++)
		{
			finallist[n].date = reserves[n].date;

			finallist[n].sailorname = sailors[indexes[n].SID].name;

			finallist[n].age = sailors[indexes[n].SID].age;
				
			finallist[n].rank = sailors[indexes[n].SID].rank;
		
			finallist[n].boatname = boats[indexes[n].BID].name;
			
			finallist[n].color = boats[indexes[n].BID].color;
		}

		Sort(finallist);
		print(finallist);

	}
	return 0;
}