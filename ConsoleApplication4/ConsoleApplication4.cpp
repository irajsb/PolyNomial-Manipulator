// ConsoleApplication4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <stdlib.h>
bool replacer(std::string& str, const std::string& from, const std::string& to);
using namespace std;

//void welcome();
void manip(vector<vector<string>>xarray);
int main()
 {
	
a:
//	welcome();
	string input, inputbyp, changer = "", orginal = "", temps = "";
	bool havex = false;
	std::vector<string> ProccedP;
	
	system("cls");
	cout << "plz enter a polynomial for example : (+23x2-2x1+1x1-4x2)(+2x2-7x1+3x2)" << endl;
	
	cin >> input;
	system("cls");
	temps = input;
	input = "";
	//start of convert
	int missed = 0;
	for (std::string::iterator it = temps.begin(); it != temps.end();) {
		//if (it != temps.begin())
		//	it++;
		if (*it == '(') {
			it++;
			missed++;
		}
		if (*it == ')') {
			it++;
			missed++;
		}
			if (*it == '+' || *it == '-') {
				changer += *it;
				orginal += *it;
				it++;
				while (*it != '+'&& *it != '-'&&*it!=')'&&it!=temps.end()) {
					changer += *it; 
					orginal += *it;
					if (*it == 'x')
						havex = true;
					it++;
				}
				if (!(havex))
					changer += "x0";	
				else if (changer.find("x") && changer == "+x")
					changer = "+1x1";
				else if (changer == "-x")
					changer = "-1x1";
				replacer(temps, orginal, changer);
			
				int index = 0;
				for (std::string::iterator itz = temps.begin(); index<changer.size()+missed&&itz != temps.end(); ++itz,++index)
				{
					input.push_back(*itz);
				}temps.erase(0, changer.size()+missed);
				changer = ""; 
				orginal = "";
				havex = false;
				missed = 0;
				it = temps.begin();
				if (it + 1 == temps.end())
				{
					input.push_back(')');
					break;
				}
			}

		
	}

	//end of convert
	std::vector<std::vector<string>> xarray;
	vector<string> xtemp;
	string proccestemp = "";
	//process polynomial by ()
	for (std::string::iterator it = input.begin(); it != input.end(); ++it) {
		if (*it == '(') {
			while (*it != ')')
			{
				*it++;
				if (*it != ')')
					proccestemp += *it;

			}
			ProccedP.push_back(proccestemp);
			//cout << proccestemp;
			proccestemp = "";


		}
	}

	//end of process check:OK
	//
	//
	//process by +-
	string temp, output = "";
	int counter = 0;


	for (std::vector<string>::const_iterator its = ProccedP.begin(); its != ProccedP.end(); ++its) {
		temp = *its;


		for (std::string::iterator it = temp.begin(); it != temp.end(); ++it) {

			if ((*it == '+' || *it == '-') && counter == 0)
			{
				counter++;
				output += *it;
				it++;
				for (; *it != '+'&&*it != '-'&& it != temp.end(); ++it) {
					output += *it;
					if (it + 1 == temp.end()) {
						xtemp.push_back(output);
						output = "";
						counter--;

						break;
					}
				
				}
			}

			

			if ((*it == '+' || *it == '-') && counter == 1) {
				xtemp.push_back(output);
			   // cout << output;
				output = "";
				counter--;
				it--;
			}


		}

		xarray.push_back(xtemp);
		xtemp.clear();
	}
	//end of process check:OK
	//
	//
	//start of manipulating
	manip(xarray);
		///end of process check:tested with 2 poly
		////
		//printing  result
	cout << "THE RESULT IS:" << endl;
	for (std::vector<vector<string>>::const_iterator its1 = xarray.begin(); its1 != xarray.end(); ++its1)
		for (vector<string>::const_iterator its2 = its1->begin(); its2 != its1->end(); ++its2)
			cout << *its2;
	cout << endl;
	system("PAUSE");
	cout << "do u wish to continue????  1.yes 2.no" << endl;
	int n;
	cin >>n;
	if (n == 1) {
		xarray.clear();
		//solved.clear();
		ProccedP.clear();
		goto a;
	}
	
	


	

	
    return 0;
}





void manip(vector<vector<string>>xarray) {
	vector<string> solved;
	for (std::vector<vector<string>>::const_iterator its2 = xarray.begin(), its1 = xarray.begin(); its1 != xarray.end() && its2 != xarray.end(); its1 = xarray.begin()
		, its2 = xarray.begin(), its2++)
	{



		string a = "", b = "";
		float base1, base2;
		int pow1, pow2;
		for (vector<string>::const_iterator it1 = its1->begin(); it1 != its1->end(); ++it1) {
			for (vector<string>::const_iterator it2 = its2->begin(); it2 != its2->end(); ++it2) {
				for (std::string::const_iterator itr = it1->begin(); itr != it1->end(); ++itr) {
					while (*itr != 'x') {
						a = a + *itr;
						itr++;
					}
					if (*itr == 'x') {
						base1 = stof(a);
						itr++;
					}b += *itr;



				}pow1 = stoi(b);
				a = "", b = "";
				for (std::string::const_iterator itr = it2->begin(); itr != it2->end(); ++itr) {
					while (*itr != 'x') {

						a = a + *itr;
						itr++;
					}
					if (*itr == 'x') {
						base2 = stof(a);
						itr++;
					}b += *itr;


				}pow2 = stoi(b);
				a = "", b = "";
				base1 = base1 * base2;
				pow1 = pow1 + pow2;
				string result;
				if (base1 > 0)
					result = "+" + to_string(base1) + "x" + to_string(pow1);
				if (base1 < 0)
					result = to_string(base1) + "x" + to_string(pow1);

				solved.push_back(result);
				base1 = base2 = pow1 = pow2 = 0;
			}
		}

		xarray.erase(xarray.begin(), xarray.begin() + 2);
		xarray.push_back(solved);
		solved.clear();
		its1 = xarray.begin();


		if (xarray.size() == 1) {

			break;
		}


	}
}








void welcome() {
	Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||                                                  ||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||            W  E   L   C  O   M   E               ||||||||||||||||||||||||||||||||||||" << endl;
	cout << "|||||||||||||||||||||||||||||||||                                                  ||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100); cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100); cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100); cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100); cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100); cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100); cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100); cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; Sleep(100);
	system("PAUSE");
}
bool replacer(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}
