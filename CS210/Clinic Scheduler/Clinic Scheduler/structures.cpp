#pragma once
#include <iostream>
#include "structures.h"
#include <string>

using namespace std;

bool isSpecialty(string request)
{
	if(request == "PED" || request == "GP" || request == "INT" || request == "CAR" 
		|| request == "SUR" || request == "OBS" || request == "PSY" || request == "NEU" 
		|| request == "ORT" || request == "DET" || request == "OPT" || request == "ENT" || request == "NP")
		return true;
	else
		return false;
};

doctor::doctor()
{
	name = "Name";
	doctorSpecialty = "NP";
	roomNumber = -1;
};

string doctor::getSpecialty()
{
	return doctorSpecialty;
};

int doctor::getRoom()
{
	return roomNumber;
};

void doctor::setRoom(int number)
{
	roomNumber = number;
};

void doctor::doctorCheckin()		
{
	string specialty;
	bool valid = false;
	cout << "What is your name? ";
	cin >> name;
	cout << "And what is your specialty Doctor? ";
	do{													//allows program to keep asking for specialty until a valid choice is recieved
		cin >> specialty;
		if(isSpecialty(specialty) && specialty != "NP")		//doctor cannot have no preferance of his specialty.
		{
			doctorSpecialty = specialty;
			valid = true;
		}
		else
		{
			cout << "Invalid doctor specialty. Please try again: ";
		}
	}while(!valid);
	valid = false;
	cout << "Thank you Dr. " << name << ". One last question, which exam room would you like? ";
	do{
		cin >> roomNumber;
		if(0 <= roomNumber && roomNumber <= numberOfRooms)
		{
			valid = true;
		}
		else
		{
			cout << "Im sorry, that is not a valid room number. Please try again: ";
			cin >> roomNumber;
		}
	}while(!valid);				//more error checking, to make sure the doctor doesnt request a non existing exam room
};

patient::patient()
{
	name = "";
	age = 0;
	requestedSpecialty = "";
	isEmergency = false;
	roomNumber = -1;
};

string patient::getRequestedSpecialty()
{
	return requestedSpecialty;
};

int patient::getAge()
{
	return age;
};

bool patient::getEmergency()
{
	return isEmergency;
};

void patient::patientCheckin()
{
	string specialty;				//temp variables to help gather and error check input
	string input;
	bool valid = false;
	char emerg;	
	cout << "What is your name? ";
	cin >> name;
	cout << "And what is your age " << name << " ?";
	cin >> age;
	cout << "What type of doctor would you like to see? ";
	do{					//loop error checks doctor specialty request
		cin >> specialty;
		if(isSpecialty(specialty))
		{
			requestedSpecialty = specialty;
			valid = true;
		}
		else
			cout << "Invalid specialty. Please try again. ";
	}while(!valid);							
	valid = false;
	do{					//loop error checks emergency request
		cout << "Finally, is this an emergency(Y/N)? ";
		cin >> emerg;
		switch (emerg)
		{
		case 'Y':
		case 'y':
			isEmergency = true;
			valid = true;
			break;
		case 'N':
		case 'n':
			isEmergency = false;
			valid = true;
			break;
		default:
			cout << "Im sorry, I did not recieve a valid response. " << endl;
			break;
		}
	}while(!valid);
};

room::room()
{
	isFull = false;
	hasPatient = false;
};

void room::assignDoctor(doctor toAssign)
{
	isFull = true;
	residingDoctor = toAssign;
};

void room::assignPatient(patient toAssign)
{
	residingPatient = toAssign;
	hasPatient = true;
};

void room::addToQueue(patient add)
{
	patientQueue.enqueue(add);
};

void room::addToEmergency(patient add)
{
	emergencyQueue.enqueue(add);
};

bool room::getIsFull()
{
	return isFull;
};

doctor room::getDoctor()
{
	return residingDoctor;
};

int room::getQueueSize()
{
	return (patientQueue.getSize() + emergencyQueue.getSize());
};

bool room::getHasPatient()
{
	return hasPatient;
};

void patient::setRoom(int number)
{
	roomNumber = number;
};

int patient::getRoomNumber()
{
	return roomNumber;
};

void room::removePatient()
{
	hasPatient = false;
};

void room::removeDoctor()
{
	isFull = false;
};
