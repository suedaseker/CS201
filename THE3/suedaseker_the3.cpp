#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

bool CorrectInput(string filename)
{
	ifstream input;

	input.open(filename.c_str());

	if (input.fail())
	{
		cout << "Error: Cannot open file " << filename << endl;
		return false;
	}
	input.close();
	return true;
}

int grading(string &question, string &answer)
{
	int point = 1;
	string word;
	istringstream lineStream(question);
	
	while (lineStream >> word)
	{
		if (word == answer)
		{
			return point;
		}else {
			point ++;
		}
	}
	return point;
}

bool isempty(string answer)
{
	istringstream input(answer);
	string word;
	while (input >> word)
	{
		for (int i = 0; i < word.length(); i ++)
		{
			if (word[i] >= 'a' && word[i] <= 'z')
			{
				return false;
			}else if (word[i] >= 'A' && word[i] <= 'Z')
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	cout << "Hello and welcome to the Hogwarts house sorting hat program!" << endl;
	cout << "When I call your name, you'll come forth, I shall place the sorting hat on your head, and you will be sorted into your houses." << endl;

	string keyfile, answerfile, answers;
	ifstream ansinput, keyinput;

	cout << "Enter the name of the key file: ";
	cin >> keyfile;
	while (CorrectInput(keyfile) == false)
	{
		cout << "Enter the name of the key file: ";
		cin >> keyfile;
	}
	cout << "Enter the name of the answer file: ";
	cin >> answerfile;
	while (CorrectInput(answerfile) == false)
	{
		cout << "Enter the name of the answer file: ";
		cin >> answerfile;
	}

	ansinput.open(answerfile.c_str());
	keyinput.open(keyfile.c_str());

	string q1, q2, q3, q4, q5, q6;
	getline(keyinput, q1);
	getline(keyinput, q2);
	getline(keyinput, q3);
	getline(keyinput, q4);
	getline(keyinput, q5);
	getline(keyinput, q6);

	while (getline(ansinput, answers))
	{
		if (isempty(answers) == false)
		{
			istringstream lineStream(answers);
			string name, surname, ans1, ans2, ans3, ans4, ans5, ans6, house;
			int grade;

			lineStream >> name >> surname >> ans1 >> ans2 >> ans3 >> ans4 >> ans5 >> ans6;

			grade = grading(q1, ans1)+grading(q2, ans2)+grading(q3, ans3)+grading(q4, ans4)+grading(q5, ans5)+grading(q6, ans6);

			if (grade < 10){
				house = "Hufflepuff";
			}else if (10 <= grade && grade < 15){
				house = "Ravenclaw";
			}else if (15 <= grade && grade < 21){
				house = "Gryffindor";
			}else if (21 <= grade){
				house = "Slytherin";
			}

			cout << "Oh! we have " << name << " " << surname << " under the sorting hat. " << name << 
				", you scored " << grade << " points, you are a " << house << "!" << endl;


		}
	}
	ansinput.close();
	keyinput.close();
	return 0;
}