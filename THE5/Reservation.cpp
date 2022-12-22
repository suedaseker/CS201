#include <iostream>
#include <vector>
#include <string>
#include "date.h"
#include "Reservation.h"
#include "strutils.h"

//Sailor
Sailor::Sailor(int sailorid, string sailorname, double sailorrank, double sailorage)
{
	id = sailorid;
	name = sailorname;
	rank = sailorrank;
	age = sailorage;
}

int Sailor::getSID()
{
	return id;
}

string Sailor::getSailorName()
{
	return name;
}

double Sailor::getAge()
{
	return age;
}

double Sailor::getRank()
{
	return rank;
}

//Boat
Boat::Boat(int boatid, string boatname, string boatcolor)
{
	id = boatid;
	name = boatname;
	color = boatcolor;
}

int Boat::getBID()
{
	return id;
}

string Boat::getBoatName()
{
	return name;
}

string Boat::getColor()
{
	return color;
}

//Reservation
Reservation::Reservation(Sailor s, Boat b, Date d)
{
	sailor = s;
	boat = b;
	resDate = d;
}

int Reservation::getSailorID()
{
	return sailor.getSID();
}

int Reservation::getBoatID()
{
	return boat.getBID();
} 

Date Reservation::getResDate()
{
	return resDate;
}

Sailor Reservation::getSailor()
{
	return sailor;
}

Boat Reservation::getBoat()
{
	return boat;
}

string Reservation::getSName()
{
	return sailor.getSailorName();
}

void Reservation::Print()
{
	cout << resDate.MonthName() << " " << resDate.Day() << " " << resDate.Year() << " -> " << sailor.getSailorName() 
		<< "(" << sailor.getAge() << "," << sailor.getRank() << ") has reserved " 
		<< boat.getBoatName() << "(" << boat.getColor() << ")" << endl;
}


//Reservations
void Reservations::Sort()
{
	int j, k, minIndex, numElts = reservations.size();
	vector<Reservation> temp(reservations.size());
	for(k = 0; k < numElts - 1; k++)
	{
		minIndex = k;
		for(j=k+1; j < numElts; j++)
		{
			if (reservations[j].getResDate() < reservations[minIndex].getResDate())
			{
				minIndex = j;
			}
			else if (reservations[j].getResDate() == reservations[minIndex].getResDate())
			{
				if (reservations[j].getSName() < reservations[minIndex].getSName()){
					minIndex = j;
				}
			}
		}
		temp[k] = reservations[k];
		reservations[k] = reservations[minIndex];
		reservations[minIndex] = temp[k];
	}
}

void Reservations::Remove(vector<Reservation> & a, int pos)
{
	int k, lastIndex = a.size()-1;
	for (k=pos; k < lastIndex; k++)
	{
		a[k] = a[k+1];
	}
	a.pop_back();
}

void Reservations::Add(Sailor sailorid, Boat boatid, Date date)
{
	reservations.push_back(Reservation(sailorid, boatid, date));
	Sort();
}


void Reservations::DelBoat(int boatid)
{
	//eşleşiyorsa sil, eşleşmiyorsa hata mesajı yaz
	int count = 0;
	for (int i = 0; i < reservations.size(); i++)
	{
		if (boatid == reservations[i].getBoatID())
		{
			Remove(reservations, i);
			count ++;
		}
	}
	if (count == 0)
	{
		cout << "Error: Could not delete reservation for boat id " << boatid << endl << endl;
	}
}

void Reservations::DelSailor(int sailorid)
{
	//eşleşiyorsa sil, eşleşmiyorsa hata mesajı yaz
	int count = 0;
	for (int i = 0; i < reservations.size(); i++)
	{
		if (sailorid == reservations[i].getSailorID())
		{
			Remove(reservations, i);
			count ++;
		}
	}
	if (count == 0)
	{
		cout << "Error: Could not delete reservation for sailor id " << sailorid << endl << endl;
	}
}

void Reservations::Del(int sailorid, int boatid, Date date)
{
	//eşleşiyorsa sil, eşleşmiyorsa hata mesajı yaz
	int count = 0;
	for (int i = 0; i < reservations.size(); i++)
	{
		if (sailorid == reservations[i].getSailorID() && boatid == reservations[i].getBoatID() && 
			date == reservations[i].getResDate())
		{
			Remove(reservations, i);
			count ++;
		}
	}
	if (count == 0)
	{
		string rMonth = tostring(date.Month());
		if (date.Month() >= 0 && date.Month() < 10)
		{
			rMonth = "0" + rMonth;
		}
		string rDay = tostring(date.Day());
		if (date.Day() >= 0 && date.Day() < 10)
		{
			rDay = "0" + rDay;
		}
		cout << "Error: Could not delete reservation \"" << sailorid << " " << boatid << " "
			<< date.Year() << "-" << rMonth << "-" << rDay << "\"" << endl << endl;
	}
}


vector<Reservation> Reservations::Find(Date date1, Date date2)
{
	int count = 0;
	vector<Reservation> founds;
	cout << "Find Results:" << endl;
	for (int i = 0; i < reservations.size(); i++)
	{
		if (reservations[i].getResDate() >= date1 && reservations[i].getResDate() <= date2)
		{
			//reservations[i].Print();
			founds.push_back(Reservation(reservations[i].getSailor(), reservations[i].getBoat(), reservations[i].getResDate()));
			count++;
		}
	}
	if (count == 0)
	{
		string rStartMonth = tostring(date1.Month()), rStartDay = tostring(date1.Day());
		string rEndMonth = tostring(date2.Month()), rEndDay = tostring(date2.Day());

		if (date1.Month() >= 0 && date1.Month() < 10)
		{
			rStartMonth = "0" + rStartMonth;
		}
		if (date1.Day() >= 0 && date1.Day() < 10)
		{
			rStartDay = "0" + rStartDay;
		}
		if (date2.Month() >= 0 && date2.Month() <  10)
		{
			rEndMonth = "0" + rEndMonth;
		}
		if (date2.Day() >= 0 && date2.Day() < 10)
		{
			rEndDay = "0" + rEndDay;
		}

		cout << "Error: No matching reservation found between dates " << date1.Year() << "-" << rStartMonth << "-" 
			<< rStartDay << " & " << date2.Year() << "-" << rEndMonth << "-" << rEndDay << endl;
	}
	if (count != 0)
	{
		for (int i = 0; i < founds.size(); i++)
		{
			founds[i].Print();
		}
	}
	cout << endl;
	return founds;
}

vector<Reservation> Reservations::FindBoat(int boatid, Date date)
{
	vector<Reservation> founds;
	int count = 0;
	cout << "Find Results:" << endl;
	for (int i = 0; i < reservations.size(); i++)
	{
		if (boatid == reservations[i].getBoatID() && date == reservations[i].getResDate())
		{
			founds.push_back(Reservation(reservations[i].getSailor(), reservations[i].getBoat(), reservations[i].getResDate()));
			reservations[i].Print();
			count ++;
		}
	}
	if (count == 0)
	{
		string rMonth = tostring(date.Month());
		if (date.Month() >= 0 && date.Month() < 10)
		{
			rMonth = "0" + rMonth;
		}
		string rDay = tostring(date.Day());
		if (date.Day() >= 0 && date.Day() < 10)
		{
			rDay = "0" + rDay;
		}
		cout << "Error: No matching reservation found for boat id " << boatid << " on " << date.Year() << "-" << rMonth << "-" 
			<< rDay << endl;
	}
	cout << endl;
	return founds;
}

vector<Reservation> Reservations::FindSailor(int sailorid, Date date)
{
	vector<Reservation> founds;
	int count = 0;
	cout << "Find Results:" << endl;
	for (int i = 0; i < reservations.size(); i++)
	{
		if (sailorid == reservations[i].getSailorID() && date == reservations[i].getResDate())
		{
			founds.push_back(Reservation(reservations[i].getSailor(), reservations[i].getBoat(), reservations[i].getResDate()));
			reservations[i].Print();
			count ++;
		}
	}
	if (count == 0)
	{
		string rMonth = tostring(date.Month());
		if (date.Month() >= 0 && date.Month() < 10)
		{
			rMonth = "0" + rMonth;
		}
		string rDay = tostring(date.Day());
		if (date.Day() >= 0 && date.Day() < 10)
		{
			rDay = "0" + rDay;
		}
		cout << "Error: No matching reservation found for sailor id " << sailorid << " on " << date.Year() << "-" << rMonth << "-" 
			<< rDay << endl;
	}
	cout << endl;
	return founds;
}
