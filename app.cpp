#include<iostream>
#include<windows.h>
#include<stdio.h>
#include<atlhandler.h>
#include<string>
#include<fstream>
#include<iomanip>
#include<experimental\filesystem>
#include <direct.h>
#include<vector>
#include <filesystem>
#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS_GLOBALS
#define _ITERATOR_DEBUG_LEVEL 2
#pragma warning(disable : 4996)

using namespace std;
string mypath = "D:\\ali\\";

void DirCommand(string mypath)
{
	string PATH = mypath + "\\*";
	WIN32_FIND_DATA WFD;
	HANDLE HANDLE_FIND = (HANDLE)-1;

	if (PATH.length() + 3 > MAX_PATH)
	{
		cout << "  \nDirectory is too long.\n";
		return;
	}

	cout << "  Directory of " << PATH << " \n\n";

	// Find the first file in the directory.
	HANDLE_FIND = FindFirstFile((PATH).c_str(), &WFD);

	if ((HANDLE)-1 == HANDLE_FIND)
	{

		cout << "  File Not Found.\n";
		return;
	}

	do
	{

		FILETIME filetime;
		SYSTEMTIME systemtime;
		FileTimeToLocalFileTime(&WFD.ftCreationTime, &filetime);
		FileTimeToSystemTime(&filetime, &systemtime);
		cout << systemtime.wYear << "-" << setw(2) << setfill('0') << systemtime.wMonth << "-" << setw(2) << systemtime.wDay
			<< "  " << setw(2) << systemtime.wHour << ":" << setw(2) << systemtime.wMinute;
		//checks if File or Dir.
		if (WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			cout << "    <DIR>          " << WFD.cFileName << "\n";
		}
		else
		{
			unsigned long long FILE_SIZE = WFD.nFileSizeHigh*(MAXDWORD)+WFD.nFileSizeLow;
			cout << "    " << setw(14) << setfill(' ') << FILE_SIZE << " " << WFD.cFileName << "\n";
		}
		// gets all Files and Dirs in directory. 
	} while (FindNextFile(HANDLE_FIND, &WFD) != 0);

	FindClose(HANDLE_FIND);
}
void help() {

	cout << "CD" << "                  Displays the name of or changes the current directory.\n"
		<< "CLS" << "                 Clears the screen.\n"
		<< "COMP" << "                Compares the contents of two files or sets of files.\n"
		<< "DEL" << "                 Deletes one or more files.\n"
		<< "DIR" << "                 Displays a list of files and subdirectories in a directory. \n"
		<< "EXIT" << "                Quits the CMD.EXE program.\n"
		<< "FIND" << "                Searches for a text string in a file or files.\n"
		<< "HELP" << "                Provides Help information for Windows commands.\n"
		<< "MD" << "                  Creates a directory.\n"
		<< "PRINT" << "               Prints a text file.\n"
		<< "RD" << "                  Removes a directory.\n"
		<< "RENAME" << "              Renames a file or files.\n"
		<< "Sort" << "                Sorts input.\n"
		<< "TYPE" << "                Displays the contents of a text file.\n"
		<< "XCOPY" << "               Copies files and directory trees.\n";
}
void exit() {
	exit(0);
}
void cd(string p) {
	mypath = p;
}
void cls() {
	DWORD n;
	DWORD size;
	COORD coord = { 0 };
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &csbi);
	size = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(h, TEXT(' '), size, coord, &n);
	GetConsoleScreenBufferInfo(h, &csbi);
	FillConsoleOutputAttribute(h, csbi.wAttributes, size, coord, &n);
	SetConsoleCursorPosition(h, coord);
}
void del(string path) {


	int c = remove((path).c_str());
	if (c == 0)
	{
		return;
	}
	cout << "\nnot found \n";
	return;
}
void Find(string filename, string word)

{
	fstream file(mypath + filename);
	if (!file.is_open())
	{
		cout << "file not found \n";
		return;
	}
	int count = 0;
	string line;
	while (!file.eof())
	{

		std::getline(file, line);
		if (line.find(word) != -1)
		{
			cout << line << endl;
			count = 1;


		}

	}
	if (count == 0)
	{
		cout << "\n" << word << " not found   " << endl;
	}

}
void md(const char * path) {

	if (!CreateDirectory(path, NULL))
	{
		return;
	}

}
void type(const char*filename) {

	fstream file(mypath + filename);
	if (!file.is_open())
	{
		cout << "file not found \n";
		return;
	}
	string line;
	while (!file.eof())
	{
        std::getline(file, line);
		cout << line << endl;
   }
}
void Delet_director(char *token)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	DWORD Attributes;
	char str[MAX_PATH];

	strcpy(str, token);
	strcat(str, "\\*.*");


	//List files
	hFind = FindFirstFile(str, &FindFileData);
	if ((HANDLE)-1 == hFind)
	{

		cout << "  File Not Found.\n";
		return;
	}
	do {
		if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
		{
			try
			{
				//Str append Example
				strcpy(str, token);
				strcat(str, "\\");
				strcat(str, FindFileData.cFileName);
				//_tprintf (TEXT("File Found: %s\n"),str);
				Attributes = GetFileAttributes(str);
				if (Attributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					//is directory
					Delet_director(str);
				}
				else
				{
					remove(str);
					//not directory
				}
			}
			catch (exception e)
			{
				cout << "\nnot exist \n";
			}
		}
	} while (FindNextFile(hFind, &FindFileData));
	FindClose(hFind);

	RemoveDirectory(token);

}
void xcopy(char*exist,char*New)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	DWORD Attributes;
	char str[MAX_PATH];
	char str2[MAX_PATH];
	strcpy(str,exist);
	strcat(str, "\\*.*");
	strcpy(str2, New);
	//List files
	hFind = FindFirstFile(str, &FindFileData);
	if ((HANDLE)-1 == hFind)
	{

		cout << "  File Not Found.\n";
		return;
	}
	md(New);
	do {
		if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
		{
			
				//Str append Example
				strcpy(str,exist);
				strcat(str, "\\");
				strcat(str2,"\\");
				strcat(str, FindFileData.cFileName);
				strcat(str2, FindFileData.cFileName);
				cout << str << endl;
				cout << str2 << endl;
				//_tprintf (TEXT("File Found: %s\n"),str);
				    Attributes = GetFileAttributes(str);
				if (Attributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					//is directory
					xcopy(str, str2);
					md(str2);
				}
				else
				{
					strcat(str, "\\");
					//strcat(str2, "\\");
					CopyFile(str, str2, false);
				}
					
		}
	} while (FindNextFile(hFind, &FindFileData)!=0);
	FindClose(hFind);
}
void RENAMe(char*oldname,char*newname)
{
	//system("RENAME");
	int result;
	 result=rename(oldname, newname);
	if (result == 0)
		puts("File successfully renamed");
	else
		perror("Error renaming file");

}
void sort(char*fileread,char*filewrite) {
	vector<string> names;

	// Read names from file LineUp.txt
	ifstream in(fileread);
	ofstream out(filewrite);
	if (!in.is_open())
		cout << "Unable to open file\n";

	// this is wrong, by the way: while(in.good()){
	string word;
	while (getline(in, word))
		names.push_back(word);
	sort(names.begin(), names.end());
	if (!out.is_open())
		cout << "Unable to open file\n";
	// Loop to print names
	for (size_t i = 0; i < names.size(); i++)
		out << names[i] << '\n';
}
void sleep(unsigned int time)
{
	Sleep(time);
}
void print(char*path,char*printername) {

	fstream file(path, ios::in);
	if (!file)
	{
		cerr << "\n Cannot open file !\n";
		return;
	}

	ofstream printer(printername); // Open the printer stream.
	if (!printer) // Ensure the printer stream opened ok.
	{
		cout << "\a\n\tERROR: Unable to open " << printername << endl;
		cout << "\n\tPress the [ENTER] key to return ";
		return;
	}
}
void comp(char*file1, char*file2)
{
	fstream fil1;
	fil1.open(file1, ios::in);
	fstream fil2;
	fil2.open(file2, ios::in);
	char f1;
	char f2;
	while (fil1.good())
	{
		fil1 >> f1;
		fil2 >> f2;
		if (f1 != f2) {
			cout << "different char " << f1 << "  " << f2 << endl;
	   }
	}
	fil1.close();
	fil2.close();
	
}
int  main()
{
	cout << "  \n  ALi[Version 1]" << endl
		<< "  2017 ALi Corporation.All rights not reserved." << endl;
	string c;
	
	do{
		cout << mypath << ">";
		cin >> c;
		char* p = new char[MAX_PATH-3];
		string s;
		if (c=="dir") {
			DirCommand(mypath);	
		}
		else if(c=="help"){
			help();
		}
		else if (c == "exit") {
			exit();
		}
		else if (c == "cd" ) {
			cout << "enter new path" << endl;
			cin >> s;
			cd(s);
		}
		else if (c == "cls" ) {
			cls();
		}
		else if (c == "DEL" ) {
			cout << "enterfile path" << endl;
			cin >> s;
			del(s);
		}
		else if (c == "find" ) {
			cout << "file path" << endl;
			cin >> s;
			string d;
			cout << "enter word wanted" << endl;
			cin >> d;
			Find(s, d);
		}
		else if (c == "md" ) {
			cout << "enter path" << endl;
			cin >> p;
			md(p);
		}
		else if (c == "type") {
			cout << "enter path" << endl;
			cin >> p;
			type(p);
		}
		else if (c == "rd") {
			cout << "dpath" << endl;
			cin >> p;
			Delet_director(p);
		}
		else if (c =="xcopy") {
			cout << "enter path1" << endl;
			cin >> p;
			char* f=new char[MAX_PATH];
			cout << "enter path2" << endl;
			cin >> f;
			xcopy(p, f);
		}
		else if (c == "rename") {
			cout << "oldname withpath" << endl;
			cin >> p;
			char* d = new char[MAX_PATH];
			cout << "newname with path" << endl;
			cin >> d;
			RENAMe(p, d);
		}
		else if (c == "comp") {
			cout << "file1 withpath" << endl;
			cin >> p;
			char* d = new char[MAX_PATH];
			cout << "fil2 with path" << endl;
			cin >> d;
			comp(p, d);
		}
		else if (c == "sort") {
			cout << "file1 withpath" << endl;
			cin >> p;
			char* d = new char[MAX_PATH];
			cout << "file2 with path" << endl;
			cin >> d;
			sort(p, d);
		}
		else if (c == "print") {
			cout << "ppath" << endl;
			cin >> p;
			char* d = new char[MAX_PATH];
			cout << "name printer" << endl;
			cin >> d;
			print(p, d);
		}
		else if (c == "sleep") {
			unsigned int t;
			cout << "time" << endl;
			cin >> t;
			sleep(t);
		}
		char*c = new char[10];

	} while (true);
	return 0;

}