//the program will have a test file with periods, dates, questions, and answers. 
//Thesaurus file will have a word or category with multiple different ways of writing it.
//period to next test, date last tested, question, answer.

// Test file example:
//2 days, 6/02/2026, How do i create a window and context?, 
// glfwWindow* window = glfwCreateWindow(width, height, name, null, null); 
// if (!window)
// {failure}
// returns null when failing

// Thesaurus file example
//howTo, How do i, what is the process required to
//glfwWin, create a window and context using c++, create something for triangles to be drawn on using c++, create a box that can display renders with c++
//glfwAdd, starting from base computer with no programs, starting from empty text file with no boilerplate,  
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

string getTimeTxt()
{
	struct tm newtime;
	time_t timeStamp = time(NULL);
	struct tm dateTime = *localtime(&timeStamp);
	char output[50];
	strftime(output, 50, "%d/%m/%y", &dateTime);
	return(output);
}

vector<vector<string>> getThesaurusLines()
{
	//get file
	ifstream file("thesaurus.csv");
	

	vector<vector<string>> output;

	string line;
	while (getline(file, line))
	{

		string scentence;
		vector<string> row;

		stringstream sLine(line);

		while (getline(sLine, scentence, ','))
		{
			row.push_back(scentence);
		}
		output.push_back(row);
	}
	file.close();
	
	return output;
}




//vector<vector<string>> findRowsDue()
//{
//	//get time
//	string time = getTimeTxt();
//}

void update()
{

}

//void test()
//{
//	std::cout << "beginning test...\n";
//	//loop through questions and make temporary list of overdue questions
//	vector<vector<string>> dueRows= findRowsDue();
//	//loop through due questions and display only the question, then keep answers in a seperate array
//	vector<string> answers;
//	string answer;
//	for (size_t i = 0; i < (sizeof(dueRows)/sizeof(dueRows[0])); i++)
//	{
//		std::cout << dueRows[3][i]<<"\n";
//		std::cin >> answer;
//		answers[i] = answer;
//	}
//	//loop through new list
//	bool correct;
//	for (size_t i = 0; i < (sizeof(dueRows) / sizeof(dueRows[0])); i++)
//	{
//		string answer;
//		std::cout << dueRows[3][i] << "\n";
//		std::cout << answers[i];
//		//ask user if they match and update CSV accordingly
//		std::cin >> correct;
//
//	}
//}

void notes()
{
	std::cout << "record questions then answers, type end to begin answers.\n";
	string grass = "Green";
	//continously loop, recording notes with thesaurus codes
	string question;
	vector<string> questions;
	int count = 0;
	getline(std::cin, question);
	while (true)
	{
		getline(std::cin, question);
		if (question == "end")
		{
			break;
		}
		cout << "Count: " << count << " question: " << question << "\n";
		questions.push_back(question);
		count++;
	}
	vector<string> answers;
	string answer;
	
	for (size_t i = 0; i < count; i++)
	{
		std::cout << questions[i]<<": \n";
		getline(std::cin,answer);
		answers.push_back(answer);
	}

//for each question and answer pair record a note in the CSV for each thesaurus definition
	//count the ammount of thesaurus words in the question or answer and use that to loop through them
	//each thesaurus item is an axis the length of it's row

	//put finished notes here
	vector<vector<string>> notes;

	//get thesaurus lines
	vector<vector<string>> thesaurusLines = getThesaurusLines();

	//loop through thesaurus lines to extract the code word and pair it with all of it's definitions
	vector<string> thesaurusCodes;
	vector<vector<string>> thesaurusDefs;

	int countx = 0;
	for (vector<string> thesaurusRows : thesaurusLines)
	{
		thesaurusCodes.push_back(thesaurusLines[countx][0]);
		vector<string> thesaurusDefLine;
		int county = 0;
			for (string thesaurusLine : thesaurusRows)
			{
				if (county != 0)
				{
					thesaurusDefLine.push_back(thesaurusLines[countx][county]);
				}
				county++;
			}
			thesaurusDefs.push_back(thesaurusDefLine);
			countx++;
	}
	
	//for every question answer pair
	cout << "Count: " << count << "\n";
	ofstream file("self tests.csv");
	for (size_t i = 0; i < count; i++)
	{
		//count every thesaurus word in the combined string 
		//create a list of the relevant thesaurus codes in order
		vector<string> thesCodesRel;
		vector<vector<string>> thesDefsRel;
		//create a list the length of how many thesaurus terms the q/a pair has, with integers showing how many definitions each term has
		vector<int> thesItems;
		// create a second list to be compared with the first, when a list 2 item reaches the number on list 1 it rolls over into the next item
		vector<int> thesItemCounter;
		//combine into a comma seperated string
		string pair = (questions[i] + "," + answers[i]);
		cout << "pair: " << pair << "\n";
		//count thesaurus codes and create both lists
		//count a single thesaurus code every loop
		int codenum = 0;
		for (string code : thesaurusCodes)
		{
			int result = pair.find(thesaurusCodes[codenum]);
			if (result != string::npos)
			{
				cout << "Found"<<"\n";
				//count definitions
				int defnum = thesaurusDefs[codenum].size();
				thesCodesRel.push_back(thesaurusCodes[codenum]);
				thesDefsRel.push_back(thesaurusDefs[codenum]);
				std::cout << "Thesnum: " << to_string(defnum) << "\n";
				thesItems.push_back(defnum);
				thesItemCounter.push_back(0);
			}
			codenum++;
		}
		//if this overflow slot with a 0 in itemcounter is triggered, the code is done
		thesItemCounter.push_back(0);

		//loop thesItemCounter and for every iteration it creates a unique test file item
		
			//loop thesItemCounter throigh all thesItems, incrementing the first item by 1 and overflowing it when it reaches the thesItem number
			cout << "counterEnd:" << to_string(thesItemCounter[thesItemCounter.size() - 1]) << "\n";
			cout << "counterSize" << to_string(thesItemCounter.size()) << "\n";
			cout << "itemsSize" << to_string(thesItems.size()) << "\n";
			if (thesItems.size() > 0)
			{
				while ((thesItemCounter[thesItemCounter.size() - 1]) == 0)
				{
					cout << "begin count\n";
					//add finalized item to self tests file
					//loop through thesAurus codes and replace all instances with the thesaurusDefinition that corresponds to the current thesItem number
					//string to be added to final test:
					string finalString = pair;

					//show thesitemcounter current numbere
					cout << "thesitemcounter code: ";
					for (size_t codeNum = 0; codeNum < thesItemCounter.size(); codeNum++)
					{
						cout << ", " << to_string(thesItemCounter[codeNum]);
					}
					cout << "\n";

					//loop through thescodes and print current definitions
					cout << "Current defs: \n";
					//remember the final value, so thesItemCounter is 1 more than needed
					for (size_t codeNum = 0; codeNum < thesCodesRel.size(); codeNum++)
					{
						//get current thesaurus code for current decimal space in thesitemcounter
						//then get current line in thesDefsRel from decimal space in Thesitem counter,
						//from which get current definition using the number placed in the current decimal space of thesitemcounter
						cout << thesCodesRel[codeNum] << ": " << thesDefsRel[codeNum][(thesItemCounter[codeNum])] << "\n";
					}

					//go through every relevant thesaurus code for this pair and replace it with the current definition based on
					//the current thesItemCounter number
					for (size_t i = 0; i < thesCodesRel.size(); i++)
					{
						int result = finalString.find((thesCodesRel[i]));
						if (result != string::npos)
						{
							cout << "result\n";
							//replace current code with current definition for current thesaurusDef for current thesaurusCode for current thesitem

							//set string values
							string 
								needle(thesCodesRel[i]),
								//get definition using thessaurus items counter
								newval(thesDefsRel[i][thesItemCounter[i]]);

							//set index to the place the item is
							
								
								cout << "index: " << result << " needle length: " << needle.length() << "\n";
								finalString.replace(result, needle.length(), newval);
								cout <<"Finalstring: " << finalString << " :finalstring \n";
								
						}
					}

					file<<(getTimeTxt() + "," + finalString + "\n");
					
					//add 1 to the first decimal space in thesitemcounter
					thesItemCounter[0]++;
					//if it carries over carry the 1 and loop through decimal spaces untill it stops carrying
					int decSpace = 0;
					while (thesItemCounter[decSpace] > thesItems[decSpace])
					{
						thesItemCounter[decSpace] = 0;
						decSpace++;
						thesItemCounter[decSpace]++;
					}

				}
			}
			//no thesaurus items in pair
			else
			{
				file<<(getTimeTxt() + "," + pair+"\n");
			}
		
	}
	file.close();
}

int main()
{
	string sky = "blue";

	while (sky == "blue")
	{
		int bin;
		//Begin testing,or take notes
		std::cout << "Press 1 to answer pending questions, 2 to take notes, or else to quit: \n";
		std::cin >> bin;

		if (bin == 1)
		{
			//test();
		}
		else if (bin == 2)
		{
			notes();
		}
		else
		{
			sky = "red";
		}
	}
	std::cout << "goodbye!";
	return(0);
}


