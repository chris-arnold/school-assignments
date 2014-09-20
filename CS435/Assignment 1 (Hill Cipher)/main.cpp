/*
CS 435 Assignment 1 Question 3. Implement Hill Cipher encryption and decryption.
By: Chris Arnold
SID: 200276366
Input Limitations: Any string of letters (a-z)
Output Notes: White space will be stripped from the input string.

Compile Instructions: 
At least gcc version 4.6.3 REQUIRED:
	g++ -std=c++0x main.cpp
This requirement is NOT met by hercules
This requirement is met by CL115 linux machines	
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> MatrixMult(vector<int>, vector<int>);
string DoCipher(string, vector<int>);

int main()
{	
	string input, output;
	vector<int> cipher(9), inverse(9);
	cipher = {17,17,5,21,18,21,2,2,19};
	inverse = {4,9,15,15,17,6,24,0,17};
	
	cout << "Enter Text: ";
	getline(cin, input);

	//since we seemingly ignore spaces, lets remove them from our input string. Also, make everything lowercase so our alphabet is 26 characters
	input.erase( remove_if( input.begin(), input.end(), ::isspace), input.end() );	
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	
	while( (input.size()%3) != 0 )			//normalize length to mult of 3
		input+='x';
	cout << "Processed Text: " << input << endl;
	output = DoCipher(input, cipher);
	cout << "Encrypted Text: " << output << endl;
	
	cout << "Decrypted Text: " << DoCipher(output, inverse) << endl;
	return 0;
}

string DoCipher(string input, vector<int> cipher)
{
	vector<int> text, outtext;
	int k = 0;
	string output;
	for(int i = 0; i <= input.size(); i++)
	{	
		if(k < 3)
			text.push_back(int(input[i]-97));
		else
		{
			outtext=MatrixMult(cipher, text);
			for(int l = 0; l < 3; l++)
				output+=(char(outtext[l]+97));
				
			k=0;
			text.clear();
			text.push_back(int(input[i]-97));
		}
		k++;
	}
	return output;
}

vector<int> MatrixMult(vector<int> cipher, vector<int> text)
{	
	vector<int> out(3);
	out[0] = ((cipher[0]*text[0]) + (cipher[1]*text[1]) + (cipher[2]*text[2]))%26;
	out[1] = ((cipher[3]*text[0]) + (cipher[4]*text[1]) + (cipher[5]*text[2]))%26;
	out[2] = ((cipher[6]*text[0]) + (cipher[7]*text[1]) + (cipher[8]*text[2]))%26;
	return out;
}
