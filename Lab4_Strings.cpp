// Lab4_strings.cpp
// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
//                 OR: -std=c++0x
// Example:  g++ Lab4_strings.cpp -o Lab4_strings -std=c++11
//      or:  g++ Lab4_strings.cpp -o Lab4_strings -std=c++0x
// Some initialization methods and other things are not supported by the old standard. 

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Complete the assignments stated in the comments.
int main()
{
// ****************************************************************************
// Declare and initialize four or five strings. Use different ways of
// initializing, as shown in Table 7.1 (Lecture 7). 
// Try all the operations in Table 7.2 (Lecture 7) using the strings that
// you declared.
// ****************************************************************************



	//different type of initialization.
	string s1;
	string s1_new;
	string s1_copy;
	string s2(s1);
	string s3=s1;
	string s4("Test");
	string s6 = "Test";
	string s5(4,'c');
	istringstream is("Hello");
	ostringstream os;

	//output the result of different initializations.
	cout<<"Original output of s1: "<<s1<<endl<<endl;
	//test is>>s.
	is>>s1_new;
	cout<< "Contents in s1_new: " << s1_new<<endl<<endl;
	//test getline(is, s).
	getline(cin, s1_copy);
	//test os<<s.
	os<<s1_copy;
	cout<<"The output of 'is' is : "<<s1_new<<endl;
	cout<<"After 'is' and 'os', the output of s1_copy: "<<os.str()<<endl;

	//test s.empty().
	if(s1.empty())
		cout<<"Empty"<<endl;
	//test s.size().
	cout<<"Size of s4:"<<s4.size()<<endl;
	//test s[].
	cout<<"Charactor at position 2 in s4:"<<s4[2]<<endl;
	//test s=s2+s1.
	s1=s4+s5;
	cout<<"s4+s5="<<s1<<endl;
	//test s1=s2.
	s4=s5;
	cout<<"Replace s4 with copy of s5:"<<s4<<endl;
	//test s1==s2,s1!=s2,s1<s2.
	if(s4==s5)
		cout<<"Equal"<<endl;

	if(s4!=s5)
		cout<<"Not Equal"<<endl;

	if(s1>s5)
		cout<<"s1>s5"<<endl;
	else
		cout<<"s1<s5"<<endl;


// -----------------------------------------------------------------------
	string line;
	cout << "\nEnter some text:" << endl;
	getline(cin, line);
	cout << line << endl << endl;

// ****************************************************************************
// Use "Range for" loops (L7_Ex6_Strings.cpp) and operations in table 7.3 to:
// 1) Count the number of letters in your input line above;
// 2) Count the number of digits;
// 3) Count the number of words (may be separated by white spaces, dots, etc.);

// 4) change the case of the letters (upper to lowercase and vice-versa).
// 5) Replace any whitespace with a dot ('.').
// Print the converted text in 4) and 5)
// ****************************************************************************

	int letter=0,digit=0,word=1;

	for(auto i:line)

	{
		//count the number of letters.
		if(isalpha(i)){
			letter++;
		}
		//count the number of digits.
		if(isdigit(i)){
			digit++;
		}
		//change letters to upper.
		i = toupper(i);
		//replace space to dot.
		if(isspace(i)){
			i = '.';
			//count the number of words.
			word++;
}

		cout<<i;

	}
	//output results.
	cout<<endl<<"Number of letters: "<<letter<<endl;
	cout<<"Number of digits: "<<digit<<endl;
	cout<<"Number of words: "<<word<<endl;

	return 0;
	}




