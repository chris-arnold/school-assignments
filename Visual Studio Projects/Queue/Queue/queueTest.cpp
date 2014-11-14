#include "queue.h"
typedef int qtype;

int main()
{
	queue<qtype> mine;
	qtype input;
	char wtd;
	do
	{
		cout << "Enqueue(e) or dequeue(d) or quit(q) or print(p) or size(s): ";
		cin >> wtd;
		switch (wtd)
		{
		case 'e':
			cout << "What value would you like to input?";
			cin >> input;
			mine.enqueue(input);
			break;
		case 'd':
			cout << "Dequeueing item" << endl;
			mine.dequeue();
			break;
		case 'q':
			cout << "Exiting program: " << endl;
			return 1;
			break;
		case 'p':
			mine.print();
			cout << endl << mine.getFrontData() << " is at the front of the queue. " << endl;
			break;
		case 's':
			cout << mine.getSize() << " is the size of the queue: " << endl;
			break;
		}
	}while(wtd != 'q');
	return 0;
}