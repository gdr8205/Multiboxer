#include "stdafx.h"

#include "configs.h"

#include <fstream>

using namespace std;

const int maxWows = 10;

WOWS windows[maxWows];
CONFIG configs;





int read() {

	string fileName = "config.txt";
	ifstream configFile;
	string line;
	wstring convertedLine;
	int screenCounter = 0;

	//configs.hotkey[6] = { "CTRL+SHIFT+W", "CTRL+SHIFT+W", "SHIFT+A", "SHIFT+A", "ALT", "ALT" };
	//int actions[6] = { '1', '2', '3', '4', '5', '6' };
	//int screen[6] = { 2, 1, 1, 2, 1, 2 };
	//configs.hotkey[0] = "CTRL+SHIFT+W";

	configFile.open(fileName);

	if (configFile.is_open()) {

		HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hstdout, &csbi);

		cout << "----------------------" << endl;
		cout << "Loading config file..." << endl;
		cout << "----------------------" << endl;

		while (getline(configFile, line)) {
			if (line.find("//") != string::npos) {
				if (line[0] == '/') {
					// ignores lines with comments
				}
			}
			else if (line.find("defaultGameWindowTitle=") != string::npos) {
				string info;
				
				for (int x = 23; x < line.length(); x++) {

					info = info + line[x];

				}
				if (!info[0]) {
					configs.defaultGameWindowTitle = L"World of Warcraft";
				}
				else {
					configs.defaultGameWindowTitle.assign(info.begin(), info.end());
				}
				SetConsoleTextAttribute(hstdout, 0x0A);
				wcout << "Default Game Name Window: \t" << configs.defaultGameWindowTitle << endl;
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);

			}
			else if (line.find("defaultResolution=") != string::npos) {
				string info;
				for (int x = 18; x < line.length(); x++) {

					info = info + line[x];

				}
				SetConsoleTextAttribute(hstdout, 0x09);
				cout << "\tDefault res: \t" << info << endl;
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
			}
			/*else if (line.find("PAUSE=") != string::npos) {
				string info;
				for (int x = 6; x < line.length(); x++) {

					info = info + line[x];

				}
				cout << "PAUSE: " << info << endl;

				configs.screen[configs.totalHotkeys] = screenCounter;
				configs.hotkey[configs.totalHotkeys] = info;
				configs.actions[configs.totalHotkeys] = 1337;

				configs.totalHotkeys = configs.totalHotkeys + 1;
			}

			else if (line.find("RELOAD=") != string::npos) {
				string info;
				for (int x = 7; x < line.length(); x++) {

					info = info + line[x];

				}
				cout << "RELOAD: " << info << endl;
				
				configs.screen[configs.totalHotkeys] = screenCounter;
				configs.hotkey[configs.totalHotkeys] = info;
				configs.actions[configs.totalHotkeys] = 80085;
				
				configs.totalHotkeys = configs.totalHotkeys + 1;
			}
			*/
			else if (line.find("Master=") != string::npos) {
				//convertedLine.assign(line.begin(), line.end());
				string info;
				for (int x = 7; x < line.length(); x++) {

					info = info + line[x];

				}
				
				windows[screenCounter].title.assign(info.begin(), info.end());
				SetConsoleTextAttribute(hstdout, 0x0A);
				wcout << "Found Master: \t" << windows[0].title << endl;
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
			}
			else if (line.find("Slave=") != string::npos) {
				screenCounter++;
				string info;
				for (int x = 6; x < line.length(); x++) {

					info = info + line[x];

				}
				windows[screenCounter].title.assign(info.begin(), info.end());
				SetConsoleTextAttribute(hstdout, 0x0A);
				wcout << "Found Slave: \t" << windows[screenCounter].title << endl;
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);

			}
			else if (line.find("width=") != string::npos) {
				string info;
				for (int x = 6; x < line.length(); x++) {

					info = info + line[x];

				}
				SetConsoleTextAttribute(hstdout, 0x09);
				cout << "\tFound width: \t" << info << endl;
				windows[screenCounter].width = atoi(info.c_str());
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
			}
			else if (line.find("height=") != string::npos) {
				string info;
				for (int x = 7; x < line.length(); x++) {

					info = info + line[x];

					SetConsoleTextAttribute(hstdout, 0x09);
				}
				cout << "\tFound height: \t" << info << endl;
				windows[screenCounter].height = atoi(info.c_str());
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
			}
			else if (line.find("xpos=") != string::npos) {
				string info;
				for (int x = 5; x < line.length(); x++) {

					info = info + line[x];

				}
				SetConsoleTextAttribute(hstdout, 0x09);
				cout << "\tFound xpos: \t" << info << endl;
				windows[screenCounter].xpos = atoi(info.c_str());
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
			}
			else if (line.find("ypos=") != string::npos) {
				string info;
				for (int x = 5; x < line.length(); x++) {

					info = info + line[x];

				}
				SetConsoleTextAttribute(hstdout, 0x09);
				cout << "\tFound ypos: \t" << info << endl;
				windows[screenCounter].ypos = atoi(info.c_str());
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
			}
			else if (line.find("$") != string::npos && line.find("|") != string::npos) {
				

				string info;
				int spacer = 0;

				for (int x = 1; x < line.length(); x++) {
					if (line[x] == '|') {
						spacer = x;
						break;
					}
					else {
						info = info + line[x];
					}
				}
				configs.hotkey[configs.totalHotkeys] = info;

				string info2;

				for (int x = spacer+1; x < line.length(); x++) {
					
						info2 = info2 + line[x];
					
				}

				if (info2.find("RCTRL") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_RCONTROL;
				}
				else if (info2.find("LCTRL") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_LCONTROL;
				}
				else if (info2.find("CTRL") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_CONTROL;
				}
				else if (info2.find("RALT") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_RMENU;
				}
				else if (info2.find("LALT") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_LMENU;
				}
				else if (info2.find("ALT") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_MENU;
				}
				else if (info2.find("RSHIFT") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_RSHIFT;
				}
				else if (info2.find("LSHIFT") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_LSHIFT;
				}
				else if (info2.find("SHIFT") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_SHIFT;
				}
				else if (info2.find("TAB") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_TAB;
				}
				else if (info2.find("SPACE") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_SPACE;
				}
				else if (info2.find("UP") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_UP;
				}
				else if (info2.find("DOWN") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_DOWN;
				}
				else if (info2.find("RIGHT") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_RIGHT;
				}
				else if (info2.find("LEFT") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_LEFT;
				}
				else if (info2.find("-") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_OEM_MINUS;
				}
				else if (info2.find("=") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_OEM_PLUS;
				}
				else if (info2.find(",") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_OEM_COMMA;
				}
				else if (info2.find(".") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_OEM_PERIOD;
				}
				else if (info2.find(";") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_OEM_1;
				}
				else if (info2.find("/") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_OEM_2;
				}
				else if (info2.find("`") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_OEM_3;
				}
				else if (info2.find("[") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_OEM_4;
				}
				else if (info2.find("]") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_OEM_6;
				}
				else if (info2.find("'") != string::npos) {
					configs.actions[configs.totalHotkeys] = VK_OEM_7;
				}
				else {

					char info3;
					//for (int x = 0; x < keyString.length(); x++) {

					info3 = info2[0];


					configs.actions[configs.totalHotkeys] = info3;
					//}
					//keys[counter] = info[0];
				}

				
				//configs.actions[configs.totalHotkeys] = line[line.length() - 1];
				configs.screen[configs.totalHotkeys] = screenCounter;

				SetConsoleTextAttribute(hstdout, 0x09);
				cout << "\tHotkey found: \t";
				cout << configs.hotkey[configs.totalHotkeys] << " " << info2 << " "  <<  endl;
				configs.totalHotkeys = configs.totalHotkeys+1;
				SetConsoleTextAttribute(hstdout, csbi.wAttributes);
			}
		}

		cout << "--------------------------" << endl;
		cout << "Finished loading config..." << endl;
		cout << "--------------------------" << endl;
		
	}
	return configs.windowCounter = screenCounter;
}

void addBorders(HWND hWnd, int winNum, int move) {

	//HWND hWnd = FindWindow(NULL, windowName.c_str());
	if (hWnd) {
		//Use next two lines to get ride of window borders
		//SetWindowLong(hWnd, GWL_STYLE, ::GetWindowLong(hWnd, GWL_STYLE) & ~(WS_BORDER | WS_DLGFRAME | WS_THICKFRAME));
		//SetWindowLong(hWnd, GWL_EXSTYLE, ::GetWindowLong(hWnd, GWL_EXSTYLE) & ~WS_EX_DLGMODALFRAME);

		SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_DLGMODALFRAME);



		if (move == 1) {
			GetWindowRect(hWnd, &windows[winNum].oldRect);
			SetWindowPos(hWnd, 0, windows[winNum].xpos, windows[winNum].ypos, windows[winNum].width, windows[winNum].height, SWP_NOZORDER | SWP_NOACTIVATE);
			ShowWindow(hWnd, SW_RESTORE);
		}
		else
			SetWindowPos(hWnd, 0, windows[winNum].xpos, windows[winNum].ypos, windows[winNum].width, windows[winNum].height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
		//1680x1050
	}
	else {
		wcout << "Couldn't find window: xyz." << endl;
	}

}

int renameWindows(int configdInstancesNumber, int redo) {

	int instance_counter = 0;
	HWND hWnd, hWnd2;

	cout << "Renaming " << configdInstancesNumber + 1 << " WoWs as you load them..." << endl;

	if (redo == 0) {
		// rename windows during startup
		bool running = true;

		while (running == true) {
			
			hWnd2 = FindWindow(NULL, configs.defaultGameWindowTitle.c_str());
			//hWnd2 = FindWindow(NULL, TEXT("World of Warcraft"));

			hWnd = FindWindow(NULL, windows[instance_counter].title.c_str());
			
			if (instance_counter > configdInstancesNumber) {
				running = false;
			}
			else if (hWnd) {
				//getWindowInfo(instance_counter);
				addBorders(hWnd, instance_counter, 1);
				windows[instance_counter].hWnd = hWnd;
				wcout << "Found pre-existing renamed wow window: " << windows[instance_counter].title << endl;
				instance_counter++;
			}
			else if (hWnd2) {
				SetWindowText(hWnd2, windows[instance_counter].title.c_str());

				//hWnd = FindWindow(NULL, windows[instance_counter].title.c_str());
				windows[instance_counter].hWnd = hWnd2;

				
				wcout << "A WoW window has been renamed to: " << windows[instance_counter].title << endl;
				instance_counter++;
				
			}
			Sleep(1000);
			

		}

	}
	else {
		// rename windows after startup

	}

	return instance_counter;
}

void getWindowInfo(int winNumber){
	//RECT info;
	wcout << " == " << windows[winNumber].title << " == " << endl;
	GetWindowRect(windows[winNumber].hWnd, &windows[winNumber].oldRect);
	//cout << "   Right: " << info.right << " | Left: " << info.left << " | Top: " << info.top << " | Bottom: " << info.bottom << endl;
	//cout << "   " << info.right - info.left << " = W | " << info.bottom - info.top << " = H" << endl;
	cout << "\n" << endl;
	cout << "   (" << windows[winNumber].oldRect.left << "," << windows[winNumber].oldRect.top << ")" << "                 " << windows[winNumber].oldRect.right - windows[winNumber].oldRect.left << "                 " << "(" << windows[winNumber].oldRect.right << "," << windows[winNumber].oldRect.top << ")" << endl;
	cout << "   +-------------------------------------------+" << endl;
	cout << "   |                                           |" << endl;
	cout << "   |                                           |" << endl;
	cout << "   |                                           |" << endl;
	cout << "   |                                           |" << " " << windows[winNumber].oldRect.bottom - windows[winNumber].oldRect.top << endl;
	cout << "   |                                           |" << endl;
	cout << "   |                                           |" << endl;
	cout << "   |                                           |" << endl;
	cout << "   +-------------------------------------------+" << endl;
	cout << "   (" << windows[winNumber].oldRect.left << "," << windows[winNumber].oldRect.bottom << ")" << "                                  " << "(" << windows[winNumber].oldRect.right << "," << windows[winNumber].oldRect.bottom << ")" << endl;
	cout << "\n" << endl;
}