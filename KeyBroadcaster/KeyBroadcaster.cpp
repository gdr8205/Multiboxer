// KeyBroadcaster.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



#include "configs.h"

#pragma comment(lib, "User32.lib") // link lib file

bool pressed = false;
bool paused = false;
using namespace std;
//static bool keys[256];

void borderless(HWND hWnd, int winNum, int move);
//void addBorders(HWND hWnd, int winNum, int move);
float resizeWindow(float w, float h, float w2);
//void key(wstring key1, wstring key2);
void resetAll(int init);

//void inputReader();

bool incomming = false;

void keyActions(HWND hWnd, int action);

//bool someFuckerTookMyKeys(int keys);

void keyCombo();


//!====!===!!////////////////////
HHOOK _hook;
KBDLLHOOKSTRUCT kbdStruct;
int counterz = 0;
// This is the callback function. Consider it the event that is raised when, in this case, 
// a key is pressed.
LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	
	HWND hWnd = FindWindow(NULL, TEXT("Multiboxer v2.0 By: Lessaid"));
	if (nCode >= 0) {
		bool found = false;
		switch (wParam)
		{
			// the action is valid: HC_ACTION.
		case WM_SYSKEYDOWN:
			if (kbdStruct.vkCode == VK_SHIFT) {
				cout << "FUCKER IS WORKING" << endl;
			}
			//DefWindowProc(windows[0].hWnd, WM_SYSKEYUP, wParam, lParam);
			kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
			//cout << "FUCKSYSKEY DOWN" << endl;
			if (configs.keysPressed[0] == 0) {
				counterz = 0;
				configs.keysPressed[1] = { 0 };
				configs.keysPressed[2] = { 0 };
			}

			if (configs.keysPressed[2] > 0) {
				if (configs.keysPressed[1] == 0) {
					counterz = 0;
					configs.keysPressed[0] = { 0 };

					configs.keysPressed[2] = { 0 };
				}
			}
			if (incomming == false) {
				for (int x = 0; x < 3; x++) {
					if (kbdStruct.vkCode == configs.keysPressed[x]) {
						found = true;
					}
				}

				if (counterz < 3) {
					if (found == false) {
						configs.keysPressed[counterz] = kbdStruct.vkCode;
						//cout << counterz << " Key pressed..." << endl;
						counterz++;
					}
				}
			}

			return 0;
		case WM_SYSKEYUP:
			//DefWindowProc(windows[0].hWnd, WM_SYSKEYUP, wParam, lParam);
			//cout << "FUCKSYSKEYUP " << configs.keysPressed[0] << "+" << configs.keysPressed[1] << endl;
			if (incomming == false) {
				kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
				for (int x = 0; x < counterz; x++) {
					if (kbdStruct.vkCode == configs.keysPressed[x]) {
						//cout << configs.keysPressed[0] << "+" << configs.keysPressed[1] << "+" << configs.keysPressed[2] << " Hotkey found" << endl;
						keyCombo();
						configs.keysPressed[x] = { 0 };
						counterz--;
					}
				}
			}
			return 0;
		case WM_KEYDOWN:

			// lParam is the pointer to the struct containing the data needed, so cast and assign it to kdbStruct.
			kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
			
			if (kbdStruct.vkCode == VK_SHIFT) {
				cout << "FUCKER IS WORKING" << endl;
			}
			
				if (configs.keysPressed[0] == 0) {
					counterz = 0;
					configs.keysPressed[1] = { 0 };
					configs.keysPressed[2] = { 0 };
				}

				if (configs.keysPressed[2] > 0) {
					if (configs.keysPressed[1] == 0) {
						counterz = 0;
						configs.keysPressed[0] = { 0 };

						configs.keysPressed[2] = { 0 };
					}
				}
			if (incomming == false) {
				for (int x = 0; x < 3; x++) {
					if (kbdStruct.vkCode == configs.keysPressed[x]) {
						found = true;
					}
				}

				if (counterz < 3) {
					if (found == false) {
						configs.keysPressed[counterz] = kbdStruct.vkCode;
						//cout << counterz << " Key pressed..." << endl;
						counterz++;
					}
				}
			}

			return 0;
		case WM_KEYUP:
			//cout << "FOOK ME SOOOO" << endl;
			if (incomming == false) {
				kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
				for (int x = 0; x < counterz; x++) {
					if (kbdStruct.vkCode == configs.keysPressed[x]) {
						//cout << configs.keysPressed[0] << "+" << configs.keysPressed[1] << "+" << configs.keysPressed[2] << " Hotkey found" << endl;
						keyCombo();
						configs.keysPressed[x] = { 0 };
						counterz--;
					}
				}
			}
				
				//pressed = false;
			//}
			//InvalidateRect(hWnd, NULL, TRUE);
			// lParam is the pointer to the struct containing the data needed, so cast and assign it to kdbStruct.
			//kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
			// a key (non-system) is pressed.
			
			return 0;
		}
	}
	// call the next hook in the hook chain. This is nessecary or your hook chain will break and the hook stops
	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook()
{
	// Set the hook and set it to use the callback function above
	// WH_KEYBOARD_LL means it will set a low level keyboard hook. More information about it at MSDN.
	// The last 2 parameters are NULL, 0 because the callback function is in the same thread and window as the
	// function that sets and releases the hook. If you create a hack you will not need the callback function 
	// in another place then your own code file anyway. Read more about it at MSDN.
	if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0)))
	{
		MessageBox(NULL, L"Failed to install hook!", L"Error", MB_ICONERROR);
	}
}

void ReleaseHook()
{
	UnhookWindowsHookEx(_hook);
}
//!====!===!!////////////////////

int suspendCounter = 0;


int lastKeyCombo[3] = {NULL,NULL,NULL};

void resizeWindowCycle(){

	int winNum;

	HWND activeWindow = GetForegroundWindow();

	for (int x = 0; x < configs.windowCounter; x++) {
		if (activeWindow == windows[x].hWnd) {
			winNum = x;
			//cout << "Found Winder..." << endl;
			break;
		}
	}
	if (windows[configs.currentWindowMaxed].hWnd != activeWindow) {
		if (configs.currentWindowMaxed == NULL) {
			cout << "0" << endl;
			SetWindowPos(activeWindow, 0, 0, 0, configs.defaultWidth, configs.defaultHeight, SWP_NOZORDER | SWP_NOACTIVATE);
			configs.currentWindowMaxed = winNum;
		}
		else {
			cout << "1" << endl;
			SetWindowPos(windows[configs.currentWindowMaxed].hWnd, 0, windows[configs.currentWindowMaxed].xpos, windows[configs.currentWindowMaxed].ypos, windows[configs.currentWindowMaxed].width, windows[configs.currentWindowMaxed].height, SWP_NOZORDER | SWP_NOACTIVATE);

			SetWindowPos(activeWindow, 0, 0, 0, configs.defaultWidth, configs.defaultHeight, SWP_NOZORDER | SWP_NOACTIVATE);

			configs.currentWindowMaxed = winNum;
		}
	}
	else {
		cout << "2" << endl;
		SetWindowPos(windows[configs.currentWindowMaxed].hWnd, 0, windows[configs.currentWindowMaxed].xpos, windows[configs.currentWindowMaxed].ypos, windows[configs.currentWindowMaxed].width, windows[configs.currentWindowMaxed].height, SWP_NOZORDER | SWP_NOACTIVATE);
		configs.currentWindowMaxed = NULL;
	}
}

void keyCombo() {
	//cout << "hotkey" << endl;
	
	int clickedWindows[10];
	int clickCounter = 0;
	pressed = false;

	bool active = false;

	for (int x = 0; x <= configs.windowCounter; x++) {
		if (windows[x].hWnd == GetForegroundWindow()) {
			active = true;
			suspendCounter = 0;
			break;
		}
		else {
			//suspendCounter++;
			active = false;
		}
	}
	//suspendCounter++;
	if (active == false) {
		suspendCounter++;
		if (suspendCounter == 1) {
			cout << "\n\nBroadcast suspended due to focus.\n";
		}
	}

	if (configs.keysPressed[0] == VK_RCONTROL && configs.keysPressed[1] == VK_RSHIFT && configs.keysPressed[2] == 'R') {
		//cout << "\nSUM\n";
		//reset = true;
		paused = true;
		resetAll(0);
		paused = false;
	}
	else if (configs.keysPressed[0] == VK_RETURN && configs.keysPressed[1] == 0 && configs.keysPressed[2] == 0 && active == true) {
		if (paused == false) {
			cout << "\nBroadcasting Paused!\n";
			paused = true;
		}
		else {
			cout << "\nBroadcasting Resumed!\n";
			paused = false;
		}
	}
	else if (configs.keysPressed[0] == VK_ESCAPE && configs.keysPressed[1] == 0 && configs.keysPressed[2] == 0 && active == true && paused == true) {
		if (paused == false) {
			cout << "\nBroadcasting Paused!\n";
			paused = true;
		}
		else {
			cout << "\nBroadcasting Resumed!\n";
			paused = false;
		}
	}
	else if (configs.keysPressed[0] == 'R' && configs.keysPressed[1] == 0 && configs.keysPressed[2] == 0 && active == true && paused == false) {
		if (paused == false) {
			cout << "\nBroadcasting Paused!\n";
			paused = true;
		}
		else {
			cout << "\nBroadcasting Resumed!\n";
			paused = false;
		}
	}
	else if (configs.keysPressed[0] == VK_OEM_2 && configs.keysPressed[1] == 0 && configs.keysPressed[2] == 0 && paused == false) {
		if (paused == false) {
			cout << "\nBroadcasting Paused!\n";
			paused = true;
		}
		else {
			cout << "\nBroadcasting Resumed!\n";
			paused = false;
		}
	}
	else if (configs.keysPressed[0] == VK_RSHIFT && configs.keysPressed[1] == 'P' && configs.keysPressed[2] == 0 && active == true) {
		if (paused == false) {
			cout << "\nBroadcasting Paused!\n";
			paused = true;
		}
		else {
			cout << "\nBroadcasting Resumed!\n";
			paused = false;
		}
	}
	else if (configs.keysPressed[0] == VK_F1 && active == true) {
		resizeWindowCycle();
	}

	if (paused == false && active == true) {
		wstring keyCombo;
		for (int x = 0; x < configs.totalHotkeys; x++) {
			
			keyCombo.assign(configs.hotkey[x].begin(), configs.hotkey[x].end());

			if (configs.keys[x][0] == configs.keysPressed[0]) {
				if (configs.keys[x][1] == NULL) {
					//cout << "Hotkey 1 tier" << endl;
					//ReleaseHook();
					//////////////////////////////////////////////////

					if (pressed == false) {
						wcout << "\n" << keyCombo << " pressed on " << windows[configs.screen[x]].title;
						//clickedWindows[clickCounter] = config.screen[x];
						//clickCounter++;
						//keyActions(windows[configs.screen[x]].hWnd, configs.actions[x]);
						keyActions(windows[configs.screen[x]].hWnd, x);
					}
					else {
						wcout << ", " << windows[configs.screen[x]].title;
						//clickedWindows[clickCounter] = config.screen[x];
						//clickCounter++;
						//keyActions(windows[configs.screen[x]].hWnd, configs.actions[x]);
						keyActions(windows[configs.screen[x]].hWnd, x);

					}

					pressed = true;

					//////////////////////////
					//SetHook();
				}
				else if (configs.keys[x][1] == configs.keysPressed[1]) {
					if (configs.keys[x][2] == NULL) {
						//cout << "Hotkey 2 tier" << endl;
						//incomming = true;
						//ReleaseHook();
						//////////////////////////////////////////////////
						
							if (pressed == false) {
								wcout << "\n" << keyCombo << " pressed on " << windows[configs.screen[x]].title;
								//keyActions(windows[configs.screen[x]].hWnd, configs.actions[x]);
								keyActions(windows[configs.screen[x]].hWnd, x);
							}
							else {
								wcout << ", " << windows[configs.screen[x]].title;
								//keyActions(windows[configs.screen[x]].hWnd, configs.actions[x]);
								keyActions(windows[configs.screen[x]].hWnd, x);

							}

							pressed = true;
						
						//////////////////////////
						//SetHook();
						//incomming = false;
					}
					else if (configs.keys[x][2] == configs.keysPressed[2]) {
						//cout << "Hotkey 3 tier" << endl;
						//ReleaseHook();
						//////////////////////////////////////////////////

						if (pressed == false) {
							wcout << "\n" << keyCombo << " pressed on " << windows[configs.screen[x]].title;
							//keyActions(windows[configs.screen[x]].hWnd, configs.actions[x]);
							keyActions(windows[configs.screen[x]].hWnd, x);
						}
						else {
							wcout << ", " << windows[configs.screen[x]].title;
							//keyActions(windows[configs.screen[x]].hWnd, configs.actions[x]);
							keyActions(windows[configs.screen[x]].hWnd, x);

						}

						pressed = true;

						//////////////////////////
						//SetHook();
					}
				}
			}
		}
		/////// Enter New output segs here... ///////
		//wcout << keyCombo << " pressed on: ";
		//for (int x = 0; x < clickCounter; x++) {
		//	wcout << windows[clickedWindows[x]].title;
		//}
		//cout << "\n";
	}
	
}

/*int getkey(){
	for (int i = 0; i < 256; i++) {
		keys[i] = GetAsyncKeyState(i);

	}
	return 0;
}*/

//wstring WoWs[5];

//extern wows windows[5];

void keyMaker();
//bool broadcastPaused();


int main()
{
	int hang = -0;
	bool running = true;
	
	SetConsoleTitle(L"Multiboxer By: Lessaid");

	resetAll(0);

	
	bool reset = false;
	
	//LoadIcon(NULL, IDI_INFORMATION);
	
	//keyMaker();
	SetHook();
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{

	}

	/*
	while (running) {
		pressed = false;
		inputReader();
		//}
		//Sleep(100);
	}
	*/
	return 0;
}

void keyMaker() {
	for (int x = 0; x < configs.totalHotkeys; x++) {
		stringstream stream(configs.hotkey[x]);
		string keyString;
		int counter = 0;
		//int keys[3] = { NULL, NULL, NULL };

		configs.keys[x][0] = NULL;
		configs.keys[x][1] = NULL;
		configs.keys[x][2] = NULL;

		while (getline(stream, keyString, '+')) {

			configs.keys[x][counter] = convertStringToAction(keyString);

			counter++;
		}



	}
	Sleep(100);
}
void keyActions(HWND hWnd, int action) {
	
	HWND activeWindow = GetForegroundWindow();
		SetForegroundWindow(windows[0].hWnd);
	//SetFocus(windows[0].hWnd);
		ReleaseHook();
		

		if (configs.actions[action][0] != NULL) {
			PostMessage(hWnd, WM_KEYDOWN, configs.actions[action][0], 0) && PostMessage(hWnd, WM_KEYDOWN, configs.actions[action][1], 0);
			//PostMessage(hWnd, WM_KEYDOWN, configs.actions[action][1], 0);

			PostMessage(hWnd, WM_KEYUP, configs.actions[action][1], 0) && PostMessage(hWnd, WM_KEYUP, configs.actions[action][0], 0);
			//PostMessage(hWnd, WM_KEYUP, configs.actions[action][0], 0);
		}
		else {
			PostMessage(hWnd, WM_KEYDOWN, configs.actions[action][1], 0);
			PostMessage(hWnd, WM_KEYUP, configs.actions[action][1], 0);
		}

	/*	INPUT ip;

		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0;
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;
		ip.ki.dwFlags = 0;

		ip.ki.wVk = action;

		SetForegroundWindow(hWnd);
		//SetFocus(hWnd);
		SendInput(1, &ip, sizeof(INPUT));

		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		 
		//active = false;
		SetForegroundWindow(activeWindow);
		//SetFocus(activeWindow);
	*/	
	SetHook();

}

void borderless(HWND hWnd, int winNum,int move) {

	//HWND hWnd = FindWindow(NULL, windowName.c_str());
	if (hWnd) {
		//Use next two lines to get ride of window borders
		SetWindowLong(hWnd, GWL_STYLE, ::GetWindowLong(hWnd, GWL_STYLE) & ~(WS_BORDER | WS_DLGFRAME | WS_THICKFRAME));
		SetWindowLong(hWnd, GWL_EXSTYLE, ::GetWindowLong(hWnd, GWL_EXSTYLE) & ~WS_EX_DLGMODALFRAME);

		//SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		//SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_DLGMODALFRAME);

	
		
		if (move == 1) {
			SetWindowPos(hWnd, 0, windows[winNum].xpos, windows[winNum].ypos, windows[winNum].width, resizeWindow(configs.defaultWidth, configs.defaultHeight, windows[winNum].width), /*SWP_NOZORDER | SWP_NOACTIVATE*/ 0);
			ShowWindow(hWnd, SW_RESTORE);
		}
		else
			SetWindowPos(hWnd, 0, windows[winNum].xpos, windows[winNum].ypos, windows[winNum].width, resizeWindow(configs.defaultWidth, configs.defaultHeight, windows[winNum].width), /*SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE*/ 0);
		//1680x1050
	}
	else {
		wcout << "Couldn't find window: xyz." << endl;
	}

}



float resizeWindow(float w, float h, float w2){
	float h2;

	h2 = (h / w) * w2;

	return h2;
}

void resetAll(int init = 0) {
	bool running = TRUE;
	char check = NULL;

	//int instance_counter = 0;
	configs.windowCounter = 0;

	configs.totalHotkeys = 0;
	configs.keysPressed[0] = { NULL };
	configs.keysPressed[1] = { NULL };
	configs.keysPressed[2] = { NULL };

	cout << "--------------------------- Multiboxer  By: Lessaid ---------------------------" << endl;
	cout << " Waiting for Game instances. See config file to make changes to fit your needs!" << endl;
	cout << "::First WoW renamed will be considered the Master while the others are Slaves::" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;


	read();

	//configs.windowCounter;

	if (configs.windowCounter > 0) {

	}
	else {
		cout << "Couldnt find suitable config file. (Error also fires if no slaves are named.)" << endl;
	}

	configs.windowCounter = renameWindows(configs.windowCounter, 0);

	running = true;

	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "WoW windows under control: " << endl;
	for (int x = 0; x != configs.windowCounter; x++) {
		wcout << windows[x].title << endl;
	}
	cout << "-------------------------------------------------------------------------------" << endl;


	RECT info;
	// enter window size tests here
	cout << "== Window info before resizing. ==" << endl;
	for (int x = 0; x < configs.windowCounter; x++) {
		wcout << " == " << windows[x].title << " == " << endl;
		GetWindowRect(windows[x].hWnd, &info);
		//cout << "   Right: " << info.right << " | Left: " << info.left << " | Top: " << info.top << " | Bottom: " << info.bottom << endl;
		//cout << "   " << info.right - info.left << " = W | " << info.bottom - info.top << " = H" << endl;
		cout << "\n" << endl;
		cout << "   (" << info.left << "," << info.top << ")" << "                 " << info.right - info.left << "                 " << "(" << info.right << "," << info.top << ")" << endl;
		cout << "   +-------------------------------------------+" << endl;
		cout << "   |                                           |" << endl;
		cout << "   |                                           |" << endl;
		cout << "   |                                           |" << endl;
		cout << "   |                                           |" << " " << info.bottom - info.top << endl;
		cout << "   |                                           |" << endl;
		cout << "   |                                           |" << endl;
		cout << "   |                                           |" << endl;
		cout << "   +-------------------------------------------+" << endl;
		cout << "   (" << info.left << "," << info.bottom << ")" << "                                  " << "(" << info.right << "," << info.bottom << ")" << endl;
		cout << "\n" << endl;
	}
	//SetWindowPos(windows[0].hWnd, 0, windows[0].xpos, windows[0].ypos, windows[0].width, windows[0].height, SWP_NOZORDER | SWP_NOACTIVATE);

	//GetWindowRect(windows[1].hWnd, &info);
	//cout << "Right: " << -info.right << " | Left: " << -info.left << " | Top: " << info.top << " | Bottom: " << info.bottom << endl;
	//cout << info.right - info.left << " = Window width." << endl;


	for (int x = 0; x < configs.windowCounter; x++){
		SetWindowPos(windows[x].hWnd, 0, windows[x].xpos, windows[x].ypos, windows[x].width, windows[x].height, SWP_NOZORDER | SWP_NOACTIVATE);
	}

	

	//Sleep(100);

	cout << "Remove window borders? y/n" << endl;
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	FlushConsoleInputBuffer(hstdin);
	cin >> check;

	if (check == 'y') {
		for (int x = 0; x < configs.windowCounter; x++) {
			borderless(windows[x].hWnd, x, 1);
		}

		cout << "Borders removed." << endl;
	}
	else if (check == 'n') 
		cout << "Borders kept." << endl;

	cout << "\n-----------------------------------------------------\n";
	cout << "Broadcasting Started..." << endl;
	cout << "Press RSHIFT+P at anytime to Pause/Resume broadcasting." << endl;
	cout << "Press RCTRL+RSHIFT+R at anytime to reload configs." << endl;
	cout << "-------------------------------------------------------\n";
	SetForegroundWindow(windows[0].hWnd);
	keyMaker();

}