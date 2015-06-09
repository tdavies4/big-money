#ifndef SKYSCRAPER_H
#define SKYSCRAPER_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Skyscraper {
private: 
	string name;
	string city;
	string country;
	int height; //using feet
	int floors;
	int year;
	string latitude;
	string longitude;

public: 
	Skyscraper();
	~Skyscraper();

	void readDataFromFile(ifstream& input);

	void readStringFromFile(ifstream& input, string& data) {
		char letter = ' ';
		while (letter != ';') {
			input >> letter;
			data += letter;
		}
	}

	void display(ofstream& output) {
		output << name << "\t" << city << ", " << country << "\t" << height << " ft" << endl;
		output << floors << " floors" << "\tBuilt: " << year << endl;
		output << "Lat: " << latitude << "\tLong: " << longitude << endl << endl;
	}

	void displayConsole() {
		cout << name << "\t" << city << ", " << country << "\t" << height << " ft" << endl;
		cout << floors << " floors" << "\tBuilt: " << year << endl;
		cout << "Lat: " << latitude << "\tLong: " << longitude << endl << endl;
	}
};
#endif

void Skyscraper::readDataFromFile(ifstream& input) {
	string unimportantData; //used to input unimportant data

	readStringFromFile(input, name);
	readStringFromFile(input, city);
	readStringFromFile(input, country);
	readStringFromFile(input, unimportantData); //reads height in meters, probably won't be used
	input >> height; //height in feet
	input >> unimportantData;
	input >> floors;
	input >> year;
	readStringFromFile(input, latitude);
	readStringFromFile(input, longitude);
}
