========================================================================
    CONSOLE APPLICATION : KeyBroadcaster Project Overview
========================================================================

AppWizard has created this KeyBroadcaster application for you.

This file contains a summary of what you will find in each of the files that
make up your KeyBroadcaster application.


KeyBroadcaster.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

KeyBroadcaster.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

KeyBroadcaster.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named KeyBroadcaster.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////


int main()
{
	int hang = -0;
	bool running = true;
	
	SetConsoleTitle(L"Multiboxer By: Lessaid");

	resetAll();

	bool pause = false;
	bool reset = false;

	//int button1[6] = { VK_LCONTROL, VK_MENU, VK_LSHIFT, VK_TAB, VK_RCONTROL, VK_RSHIFT };
	//int button2[6] = { 'Q', 'W', 'A', 'S', 'Z', VK_TAB };
	//cout << button[0] << endl;
	//cout << button[1] << endl;
	
	while (running) {
		if (reset == true) {
			//break;
		}

		bool reset = false;
		bool pressed = false;
		//bool paused = false;
		if (GetAsyncKeyState(VK_RCONTROL) & 0x8000 && GetAsyncKeyState(VK_RSHIFT) & 0x8000 && GetAsyncKeyState('R') & 0x8000) {
			cout << "\nSUM\n";
			reset = true;
		}
		if (GetAsyncKeyState(VK_RSHIFT) & 0x8000 && GetAsyncKeyState('P') & 0x8000) {
			if (pause == false) {
				cout << "\nBroadcasting Paused!";
				pause = true;
			}
			else {
				cout << "\nBroadcasting Resumed!";
				pause = false;
			}
		}
		if (reset == true) {
			pressed == false;
			resetAll();
			//break;
		}
		else {
			if (pause == false) {

				for (int x = 0; x < configs.totalHotkeys; x++) {  // hotkeys
					stringstream stream(configs.hotkey[x]);
					string keyString;
					int keys[3] = { NULL, NULL, NULL };
					int counter = 0;
					//keys[0] = NULL;
					//hotkey[x]

					if (reset == true) {
						break;
					}

					while (getline(stream, keyString, '+')) {
						//cout << some << " | " << counter<< endl;
						if (keyString.find("RCTRL") != string::npos) {
							keys[counter] = VK_RCONTROL;
						}
						else if (keyString.find("LCTRL") != string::npos) {
							keys[counter] = VK_LCONTROL;
						}
						else if (keyString.find("CTRL") != string::npos) {
							keys[counter] = VK_CONTROL;
						}
						else if (keyString.find("RALT") != string::npos) {
							keys[counter] = VK_RMENU;
						}
						else if (keyString.find("LALT") != string::npos) {
							keys[counter] = VK_LMENU;
						}
						else if (keyString.find("ALT") != string::npos) {
							keys[counter] = VK_MENU;
						}
						else if (keyString.find("RSHIFT") != string::npos) {
							keys[counter] = VK_RSHIFT;
						}
						else if (keyString.find("LSHIFT") != string::npos) {
							keys[counter] = VK_LSHIFT;
						}
						else if (keyString.find("SHIFT") != string::npos) {
							keys[counter] = VK_SHIFT;
						}
						else if (keyString.find("TAB") != string::npos) {
							keys[counter] = VK_TAB;
						}
						else if (keyString.find("SPACE") != string::npos) {
							keys[counter] = VK_SPACE;
						}
						else if (keyString.find("UP") != string::npos) {
							keys[counter] = VK_UP;
						}
						else if (keyString.find("DOWN") != string::npos) {
							keys[counter] = VK_DOWN;
						}
						else if (keyString.find("RIGHT") != string::npos) {
							keys[counter] = VK_RIGHT;
						}
						else if (keyString.find("LEFT") != string::npos) {
							keys[counter] = VK_LEFT;
						}
						else {

							char info[1] = {};
							//for (int x = 0; x < keyString.length(); x++) {

							info[0] = keyString[0];

							//}
							keys[counter] = info[0];
						}
						//if (GetAsyncKeyState(keys[0]) & 0x8000){
						//}


						counter++;
					}

					wstring keyCombo;
					keyCombo.assign(configs.hotkey[x].begin(), configs.hotkey[x].end());

					//if (someFuckerTookMyKeys(keys[0])) {
					//	cout << "NIGGER DOWN" << endl;
					//}


					if (GetAsyncKeyState(keys[0]) & 0x8000) {



						if (keys[1] == NULL) {
							//////////////////////////////////////////////////

							if (pressed == false) {
								wcout << "\n" << keyCombo << " pressed on " << windows[configs.screen[x]].title;
								keyActions(windows[configs.screen[x]].hWnd, configs.actions[x]);
							}
							else {
								wcout << ", " << windows[configs.screen[x]].title;
								keyActions(windows[configs.screen[x]].hWnd, configs.actions[x]);

							}

							pressed = true;

							//////////////////////////
						}
						else if (GetAsyncKeyState(keys[1]) & 0x8000){


							//wcout << keyCombo << " pressed on " << windows[screen[x]].title << endl;
							if (keys[2] == NULL) {
								//////////////////////////////////////////////////


								if (pressed == false) {
									wcout << "\n" << keyCombo << " pressed on " << windows[configs.screen[x]].title;
									keyActions(windows[configs.screen[x]].hWnd, configs.actions[x]);

									INPUT ip;

									ip.type = INPUT_KEYBOARD;
									ip.ki.wScan = 0;
									ip.ki.time = 0;
									ip.ki.dwExtraInfo = 0;
									ip.ki.dwFlags = 0;


									ip.ki.wVk = configs.actions[x];

									//SetForegroundWindow(hWnd);
									//SendInput(1, &ip, sizeof(INPUT));

									//Sleep(100);

									//if (action != VK_SPACE && action != VK_UP && action != VK_DOWN && action != VK_LEFT && action != VK_RIGHT) {
										ip.ki.dwFlags = KEYEVENTF_KEYUP;
										SendInput(1, &ip, sizeof(INPUT));

										ip.ki.dwFlags = 0;
									//}

								}
								else {
									wcout << ", " << windows[configs.screen[x]].title;
									keyActions(windows[configs.screen[x]].hWnd, configs.actions[x]);
									

								}

								

								pressed = true;

								//////////////////////////
							}
							else if (GetAsyncKeyState(keys[2]) & 0x8000){
								//////////////////////////////////////////////////

								if (pressed == false) {
									wcout << "\n" << keyCombo << " pressed on " << windows[configs.screen[x]].title;
									keyActions(windows[configs.screen[x]].hWnd, configs.actions[x]);
								}
								else {
									wcout << ", " << windows[configs.screen[x]].title;
									keyActions(windows[configs.screen[x]].hWnd, configs.actions[x]);

								}

								pressed = true;

								//////////////////////////
							}


						}

						
					}



					//if ()

					/*if (GetAsyncKeyState(keys[0]) & 0x8000){
						//for (int y = 0; y < 6; y++) {
						//cout << "SOMETHING WORKD!" << endl;
						if (GetAsyncKeyState(keys[1]) & 0x8000){
						cout << "IT WORKED" << endl;
						//key(L"ALT", L"A");
						}
						//}
						}*/
					
				}
				
			}
			
			
		}
		Sleep(100);
	}
	return 0;
}