#include "scheduler.h"
#include <fstream>
void welcome();

int main()
{
	scheduler myClinic;			//the clinic
	patient tempPatient;		//temporary patient to gather information to pass into clinic
	doctor tempDoctor;
	char wtd;					//what the user wants to do
	char checkin;				//checkin or check out
	bool success = false;		//error checking variable
	int roomNum;				//gets the room a patient is in
	int docRoom;
	ofstream log;
	log.open("trans.out", ios::out | ios::trunc);		//opening trans.out as an output only file. If any data is in it, its deleted and writing starts as a clean file
	welcome();
	do
	{
		cout << endl
			<< "First are you a patient(p) a doctor(d) or would you like to quit(q)?";
		cin >> wtd;
		switch (wtd)		//nested switches to call appropriate functions
		{
		case 'p':
		case 'P':
			cout << "Thank you. Would you like to check in(i) or out(o)? ";
			cin >> checkin;
			switch (checkin)	//patient checkin/checkout
			{
			case 'i':
			case 'I':
				log << "Patient request a checkin: ";
				tempPatient.patientCheckin();			//gather patient information
				if(tempPatient.getEmergency())
					log << "Emergency!! ";
				else
					log << "Regular: ";
				roomNum = myClinic.placePatient(tempPatient);		//place patient into room.
				if(roomNum == -1)
				{
					cout << "------Schedulers message------" << endl
						<< "I'm sorry that you could not be placed. There must not be any doctors checked in. " << endl
						<< "Please try again later. " << endl;
					log << "This request was denied. Reason-No doctors checked in. " << endl;
					break;
				}
				else{}
				success = myClinic.fillRoom(roomNum);		//try to fill the room from the queue.
				if(success)
				{
					cout << "Patient is now in the exam room with the doctor " << endl;
					log << "Request successful. Patient is now seeing the doctor in exam room " << roomNum << endl;
				}
				else
				{
					cout << "Patient is in the queue wating for the doctor. " << endl;
					log << "Request successful. Patient is now in the queue for exam room " << roomNum << " waiting for the doctor. " << endl;
				}
				//patient checkin here
				break;
			case 'o':
			case 'O':
				cout << "What room is the patient checking out of? ";
				cin >> roomNum;
				log << "Patient has requested to check out room " << roomNum << ": ";
				if(roomNum < 0 || roomNum > numberOfRooms)
				{
					cout << "No such room exits. Please try again. " << endl;
					log << "This request has been rejected. Reason - Room out of range. " << endl;
					break;
				}
				log << "Request is successful. " << endl;
				myClinic.patientCheckout(roomNum);
				success = myClinic.fillRoom(roomNum);			//since a patient checked out, attempt to re-fill the room with another patient.
				if(!success)
				{
					cout << "Room is empty. Doctor has no patients! " << endl;
					log << "No new patients to assign to the room. Waiting room and exam room are empty. " << endl;
				}
				else
				{
					cout << "New patient is currently seeing the doctor in room " << roomNum << endl;
					log << "New patient has been moved into the exam room. " << endl;
				}
				//patient checkout here
				break;
			default:
				cout << "I'm sorry, I did not understand your response. Please try again. " << endl;
				break;
			}
			break;
		case 'd':
		case 'D':
			cout << "Thank you. Would you like to check in(i) or out(o)? ";
			cin >> checkin;
			switch (checkin)	//doctor checkin/checkout
			{
			case 'i':
			case 'I':
				log << "Doctor is attempting to check in: ";
				tempDoctor.doctorCheckin();				//gather doctors information
				docRoom = myClinic.placeDoctor(tempDoctor);		//place the doctor.
				if(docRoom == -1)
				{
					cout << "-----Schedulers message-----" << endl
						<<"No available rooms to place the doctor in. " << endl
						<< "Please try again later. " << endl;
					log << "Request denied. Reason - No available exam room. " << endl;
					break;
				}
				log << "Request successful. Doctor has been assigned to exam room " << docRoom << endl;
				//doctor checkin here
				break;
			case 'o':
			case 'O':
				cout << "What room were you checking out of doctor? ";
				cin >> roomNum;
				log << "Doctor has requested to checkout of exam room " << roomNum << ": ";
				if(roomNum < 0 || roomNum > numberOfRooms)
				{
					cout << "No such room exits. Please try again. " << endl;
					log << "This request has been rejected. Reason - Room out of range. " << endl;
					break;
				}
				log << "Request successful. " << endl;
				success = myClinic.doctorCheckout(roomNum);			//clear doctor out of room, as well as the waiting patients.
				myClinic.patientCheckout(roomNum);					//if a patient was in the room, they will be removed as well.
				if(!success)
				{
					cout << "Doctor has left room " << roomNum << " but the waiting patients have no where to go... " << endl;
					log << "The waiting patients have no doctor to be re-assigned too. " << endl;
				}
				else
				{
					cout << "Checkout was successfull. All waiting patients were re-assigned waiting rooms. " << endl;
					log << "All queue'd patients were successfully diverted. " << endl;
				}
				//doctor checkout here
				break;
			default:
				cout << "I'm sorry, I could not understand your input. Please try again. " << endl;
				//error message here
				break;
			}
			break;
		case 'q':
		case 'Q':			//user quitting program
			wtd = 'q';
			break;
		default:
			cout << "I'm sorry, I could not understand what you want to do. Please try again. " << endl;
			break;
		}
	}while(wtd != 'q');
	//good bye message here
	cout << "Thank you for using the automated scheduling service. Have a nice day " << endl << endl;
	log << "Program is closing. Thank you. " << endl;
	log.close();					//close output stream.
	return 0;
};

void welcome()
{
	cout << "Welcome to the automated clinic scheduler. This program will allow doctors and patients to check "
		<< "in and out of the clinic and will handle these requests. " << endl 
		<< "Please follow the on screen instructions. "
		<< endl;
};

