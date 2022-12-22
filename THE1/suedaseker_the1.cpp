#include <iostream>
#include <string>

using namespace std;

void getInput(string exercise, int & mins, int & reps, double & liftedWeight)
{
	cout << exercise << ": ";
	if (exercise == "Weight Lifting"){
		cin >> mins >> reps >> liftedWeight;
	}else{
		liftedWeight = 1;
		cin >> mins >> reps;
	}
}

bool inputCheck(int reps, double weight, int mins, double liftedWeight)
{
	if (weight < 30){
		cout << "Weight out of range!" << endl;
		return false;
		
	}else if (liftedWeight <= 0 || liftedWeight > 35){
		cout << "Lifted weight out of range!" << endl;
		return false;

	}else if (reps < 0 ||  reps > 50){
		cout << "Reps out of range!" << endl;
		return false;
	}else if (mins < 0 || mins > 2000){
		cout << "Minute out of range!" << endl;
		return false;
	}else{
		return true;
	}
}

void calculateMET(int & reps, const string & exercise, double & MET)
{
	if (exercise == "Lunges"){
		if (reps < 15){
			MET = 3;
		}else if (reps >= 15 && reps < 30){
			MET = 6.5;
		}else if (reps >= 30){
			MET = 10.5;
		}
	}if (exercise == "Push Ups"){
		if (reps < 15){
			MET = 4;
		}else if (reps >= 15){
			MET = 7.5;
		}
	}if (exercise == "Pull Ups"){
		if (reps < 25){
			MET = 5;
		}else if (reps >= 25){
			MET = 9;
		}
	}
}

void calculateWeightLiftMET(int & reps, double & liftedWeight, double & MET)
{
	if (liftedWeight < 5){
		if (reps < 20){
			MET = 3;
		}else if (reps >= 20 && reps < 40){
			MET = 5.5;
		}else if (reps >= 40){
			MET = 10;
		}
	}else if (liftedWeight >= 5 && liftedWeight < 15){
		if (reps < 20){
			MET = 4;
		}else if (reps >= 20 && reps < 40){
			MET = 7.5;
		}else if (reps >= 40){
			MET = 12;
		}
	}else if (liftedWeight >= 15){
		if (reps < 20){
			MET = 5;
		}else if (reps >= 20 && reps < 40){
			MET = 9;
		}else if (reps >= 40){
			MET = 13.5;
		}
	}
}

void displayResults(double caldiff, double calsum, double weight, double metlunge, double metpush, 
					double metpull, double metlift, double callunge, double calpush, double calpull, double callift)
{

	cout << "From lunges, you burned " << callunge << " calories." << endl;
	cout << "From push ups, you burned " << calpush << " calories." << endl;
	cout << "From pull ups, you burned " << calpull << " calories." << endl;
	cout << "From weight lifting, you burned " << callift << " calories." << endl;
	cout << "You burned " << calsum << " calories." << endl << endl;

	if (caldiff == 0){
		cout << "Congratulations! You have reached your goal!" << endl;
	}
	else if (caldiff < 0){
		cout << "You have surpassed your goal! You can eat something worth " << abs(caldiff) << " calories :)" << endl;
	}
	
	else if (caldiff > 0){
		double lungemin, pushmin, pullmin, liftmin;

		lungemin = (200 * caldiff) / (metlunge * 3.5 * weight);
		pushmin = (200 * caldiff) / (metpush * 3.5 * weight);
		pullmin = (200 * caldiff) / (metpull * 3.5 * weight);
		liftmin = (200 * caldiff) / (metlift * 3.5 * weight);

		cout << "You did not reach your goal by " << caldiff << " calories." << endl
			<< "You need to do lunges " << lungemin << " minutes more to reach your goal or," << endl
			<< "You need to do push ups " << pushmin << " minutes more to reach your goal or," << endl
			<< "You need to do pull ups " << pullmin << " minutes more to reach your goal or," << endl
			<< "You need to do weight lifting " << liftmin << " minutes more to reach your goal." << endl;
	}
	
}

void computeResults(double weight, double calgoal, int replunge, int reppush, int reppull, int replift, 
					int minlunge, int minpush, int minpull, int minlift, double liftedWeight)
{
	double callunge, calpush, calpull, callift, calsum, caldiff, metlunge, metpush, metpull, metlift;

	calculateMET(replunge, "Lunges", metlunge);
	calculateMET(reppush, "Push Ups", metpush);
	calculateMET(reppull, "Pull Ups", metpull);

	calculateWeightLiftMET(replift, liftedWeight, metlift);

	callunge = minlunge * (metlunge * 3.5 * weight) / 200;
	calpush = minpush * (metpush * 3.5 * weight) / 200;
	calpull = minpull * (metpull * 3.5 * weight) / 200;
	callift = minlift * (metlift * 3.5 * weight) / 200;

	calsum = callunge + calpush + calpull + callift;

	caldiff = calgoal - calsum;

	displayResults(caldiff, calsum, weight, metlunge, metpush, metpull, metlift, callunge, calpush, calpull, callift);
}

int main()
{
	string name;
	double weight, calgoal, metlunge, metpush, metpull, metlift, liftedWeight;
	int minlunge, replunge, minpush, reppush, minpull, reppull, minlift, replift;

	cout << "Please enter your name: ";
	cin >> name;
	cout << "Welcome " << name << ", please enter your weight(kg): ";
	cin >> weight;

	cout << name << ", please enter minutes and repetitions in a week for the activities below." << endl;
	getInput("Lunges", minlunge, replunge, liftedWeight);
	getInput("Push Ups", minpush, reppush, liftedWeight);
	getInput("Pull Ups", minpull, reppull, liftedWeight);
	cout << name << ", please enter minutes, repetitions and lifted weight in a week for the activities below." << endl;
	getInput("Weight Lifting", minlift, replift, liftedWeight);

	cout << name << ", please enter your weekly calorie burn goal: ";
	cin >> calgoal;

	if (inputCheck(replunge, weight, minlunge, liftedWeight) && inputCheck(reppush, weight, minpush, liftedWeight) && 
		inputCheck(reppull, weight, minpull, liftedWeight) && inputCheck(replift, weight, minlunge, liftedWeight)){
		
		calculateMET(replunge, "Lunges", metlunge);
		calculateMET(reppush, "Push Ups", metpush);
		calculateMET(reppull, "Pull Ups", metpull);


		calculateWeightLiftMET(replift, liftedWeight, metlift);

		computeResults(weight, calgoal, replunge, reppush, reppull, replift, minlunge, minpush, minpull, minlift, liftedWeight);
	}
	else{

		return 0;
	}


	return 0;
}