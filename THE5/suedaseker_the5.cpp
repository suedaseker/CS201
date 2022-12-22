#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "strutils.h"
#include "date.h"
#include "Reservation.h"
using namespace std;

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

int main()
{
	string resfile, sailorfile = "Sailors.txt", boatfile = "Boats.txt";
	ifstream resinput, sailorinput, boatinput;

	cout << "Enter filename for reservation database: ";
	cin >> resfile;
	if (CorrectFileName(resfile) == false || CorrectFileName(sailorfile) == false || CorrectFileName(boatfile) == false)
	{
		cout << "Cannot open the files. Exiting..." << endl << endl;
	}

	vector<Sailor> sailorData;

	sailorinput.open(sailorfile.c_str());
	string sailorline;
	int i = 0;
	while (getline(sailorinput, sailorline))
	{
		if (i > 0)
		{
			istringstream linestream(sailorline);
			int sailorID;
			double rank, age;
			string sailorname;
			linestream >> sailorID >> sailorname >> rank >> age;
			sailorData.push_back(Sailor(sailorID, sailorname, rank, age));
		}
		i++;
	}
	sailorinput.close();

	vector<Boat> boatData;

	boatinput.open(boatfile.c_str());
	string boatline;
	int j = 0;
	while (getline(boatinput, boatline))
	{
		if (j > 0)
		{
			istringstream linestream(boatline);
			int boatID;
			string boatname, color;
			linestream >> boatID >> boatname >> color;
			boatData.push_back(Boat(boatID, boatname, color));
		}
		j++;
	}
	boatinput.close();

	Reservations resData;

	resinput.open(resfile.c_str());
	string resline;
	int k = 0;
	while(getline(resinput, resline))
	{
		istringstream linestream(resline);
		string key, date, date2;
		int sailorID, boatID;
		linestream >> key >> sailorID >> boatID >> date >> date2;

		int Y = 0, M = 0, D = 0;
		istringstream datestream(date);
		string part;
		int l = 0;
		while(getline(datestream, part, '-'))
		{
			if (l == 0)
			{
				Y = atoi(part);
			}
			else if (l == 1)
			{
				M = atoi(part);
			}
			else if (l == 2)
			{
				D = atoi(part);
			}
			l++;
		}

		Sailor tempSailor;
		Boat tempBoat;
		Date tempDate = Date(M, D, Y);

		if (key == "A")
		{
			for (int i = 0; i < sailorData.size(); i++)
			{
				if (sailorID == sailorData[i].getSID())
				{
					tempSailor = sailorData[i];
				}
			}

			for (int i = 0; i < boatData.size(); i++)
			{
				if (boatID == boatData[i].getBID())
				{
					tempBoat = boatData[i];
				}
			}

			resData.Add(tempSailor, tempBoat, tempDate);
		}
		else if (key == "D")
		{
			if (sailorID == 0)
			{
				resData.DelBoat(boatID);
			}
			else if (boatID == 0)
			{
				resData.DelSailor(sailorID);
			}
			else 
			{
				resData.Del(sailorID, boatID, tempDate);
			}
		}
		else if (key == "F")
		{
			if (sailorID == 0 && boatID == 0)
			{
				int Y2 = 0, M2 = 0, D2 = 0;
				istringstream datestream(date2);
				string part;
				int l = 0;
				while(getline(datestream, part, '-'))
				{
					if (l == 0)
					{
						Y2 = atoi(part);
					}
					else if (l == 1)
					{
						M2 = atoi(part);
					}
					else if (l == 2)
					{
						D2 = atoi(part);
					}
					l++;
				}
				Date tempDate2 = Date(M2, D2, Y2);

				resData.Find(tempDate, tempDate2);
			}
			else if (sailorID == 0)
			{
				resData.FindBoat(boatID, tempDate);
			}
			else if (boatID == 0)
			{
				resData.FindSailor(sailorID, tempDate);
			}
		}
		k++;
	}
	return 0;
}

