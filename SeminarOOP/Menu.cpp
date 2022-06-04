#include "Menu.h"
void DisableSelection()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}
// in ra hướng dẫn để người dùng biết cách bắt đầu, tiếp tục, tạm dừng
void check(char& ch)
{
	TextColor(15);
	wcout << L"Press ""SPACEBAR"" to start\n";
	wcout << L"To cancel, please press ""ESC""\n";

	// chờ người dùng nhấn phím
	bool flag = true;
	while (flag) 
	{
		if (_kbhit())
		{
			ch = _getch();
			Sleep(500);
			if (ch == 32)
			{
				clrscr();
				PlaySound(TEXT("Building.wav"), NULL, SND_FILENAME | SND_ASYNC);
				wcout << L"Starting...\n";
				flag = !flag;
				Sleep(1500);
				return;
			}
			if (ch == 27)
			{
				clrscr();
				PlaySound(TEXT("cancel.wav"), NULL, SND_FILENAME | SND_ASYNC);
				wcout << L"Canceling...";
				Sleep(1500);
				return;
			}
		}
	}
	cin.ignore();
}
void ShowScrollbar(BOOL Show)
{
	HWND hWnd = GetConsoleWindow();
	ShowScrollBar(hWnd, SB_BOTH, Show);
}

// nhập các dữ liệu cần thiết để bắt đầu sắp xếp
void input(Sort* sort, int n)
{
	int x = 0, s = 0, dem = 0;
	char ch;
	// chọn cách nhập
	PlaySound(TEXT("selecttarget.wav"), NULL, SND_FILENAME | SND_ASYNC); 
	do
	{
		clrscr();
		TextColor(15);
		wcout << L"\nChoose insert way:"; wcout << L"\n------------------\n";
		if (dem == 0) TextColor(12);
		else TextColor(15);
		wcout << L"   =========================\n   =                       =\n   =  1. Insert directly   =\n   =                       =\n   =========================\n";
		if (dem == 1) TextColor(12);
		else TextColor(15);
		wcout << L"   ==============================\n   =                            =\n   =  2. Create randomly array  =\n   =                            =\n   ==============================\n";
		if (dem == 2) TextColor(12);
		else TextColor(15);
		wcout << L"   =====================\n   =                   =\n   =  3. Insert file   =\n   =                   =\n   =====================\n";
		ch = _getch();
		if (ch == 80) // xử lý thao tác nhấn nút down
		{
			dem++;
			if (dem > 2) dem = 0;
		} 
		else if (ch == 72) // xử lý thao tác nhấn nút up
		{
			dem--;
			if (dem < 0) dem = 2;
		}
	} while (ch != 13);

	// xử lý yêu cầu nhập
	if (dem == 0) cin >> sort;
	else if (dem == 1) sort->Random();
	else sort->inputFile();
	wcout << sort << endl;
	sort->complexity();
	TextColor(12);
	wcout << L"\nPress any key to continue...";
	ch = _getch();

	// chọn cách sắp xếp
	PlaySound(TEXT("selecttarget.wav"), NULL, SND_FILENAME | SND_ASYNC);
	do
	{
		clrscr();
		TextColor(15);
		wcout << L"Sort by:\n";	wcout << L"--------\n";
		
		if (x == 0) TextColor(12);
		else TextColor(15);
		wcout << L"   ======================\n   =                    =\n   =     Increment      =\n   =                    =\n   ======================\n";
		if (x == 1) TextColor(12);
		else TextColor(15);
		wcout << L"   ======================\n   =                    =\n   =     Decrement      =\n   =                    =\n   ======================\n";
		ch = _getch();
		if (ch == 80) // xử lý thao tác nhấn nút down
		{
			x++;
			if (x > 1) x = 0;
		}
		else if (ch == 72) // xử lý thao tác nhấn nút up
		{
			x--;
			if (x < 0) x = 1;
		}
	} while (ch != 13);

	
	// chọn tốc độ biểu diễn
	PlaySound(TEXT("selecttarget.wav"), NULL, SND_FILENAME | SND_ASYNC);
	do
	{
		clrscr();
		TextColor(15);
		wcout << L"Choose the speed:\n"; wcout << L"-----------------\n";
		if (s == 0) TextColor(12);
		else TextColor(15);
		wcout << L"   =================\n   =               =\n   =     Slow      =\n   =               =\n   =================\n";
		if (s == 1) TextColor(12);
		else TextColor(15);
		wcout << L"   =================\n   =               =\n   =    Normal     =\n   =               =\n   =================\n";
		if (s == 2) TextColor(12);
		else TextColor(15);
		wcout << L"   =================\n   =               =\n   =     Fast      =\n   =               =\n   =================\n";
		ch = _getch();
		if (ch == 80) // xử lý thao tác nhấn nút down
		{
			s++;
			if (s > 2) s = 0;
		}
		else if (ch == 72) // xử lý thao tác nhấn nút up
		{
			s--;
			if (s < 0) s = 2;
		}
	} while (ch != 13);

	// xử lý tốc độ biểu diễn
	if (s == 0) sort->setSpeed(500);
	else if (s == 1) sort->setSpeed(250);
	else sort->setSpeed(100);
	TextColor(15);
	clrscr();
	wcout << sort << endl;
	check(ch);
	if (ch == 27) return;

	// xử lý yêu cầu sắp xếp
	if (x == 0) sort->increase();
	else sort->decrease();
	if (n != 7 & dem != 2) clrscr();
	else if (dem == 2) wcout << sort;
	TextColor(15);
	if (dem == 2) sort->outputFile();
	PlaySound(TEXT("constructioncompleted.wav"), NULL, SND_FILENAME | SND_ASYNC);
	wcout << sort;
	wcout << L"\nSorting completed. Press any key to continue...\n";
	Sleep(100);
	ch = _getch();
}

// xử lý các lựa chọn của người dùng
void selection(int x)
{
	Sort* sort;
	TextColor(15);
	switch (x)
	{
	case 0: 
		sort = new SelectionSort;
		input(sort,x);
		delete sort;
		break; 
	case 1: 
		sort = new InterchangeSort;
		input(sort,x);
		delete sort;
		break; 
	case 2: 
		sort = new InsertionSort;
		input(sort,x);
		delete sort;
		break; 
	case 3: 
		sort = new BinaryInsertionSort;
		input(sort,x);
		delete sort;
		break; 
	case 4:
		sort = new BubbleSort;
		input(sort,x);
		delete sort;
		break;
	case 5:
		sort = new ShakerSort;
		input(sort,x);
		delete sort;
		break;
	case 6:
		clrscr();
		break;
	case 7:
		// xử lý khi người dùng thoát
		Sleep(400);
		infor();
		TextColor(12);
		gotoXY(95, 21);
		wcout << L"Exiting...\n";
		Sleep(1000);
		clrscr();
		gotoXY(95, 21);
		PlaySound(TEXT("quit.wav"), NULL, SND_FILENAME | SND_ASYNC);
		wcout << L"Cya";
		gotoXY(92, 40);
		Sleep(3000);
		break;
	case 8:
		sort = new ShellSort;
		input(sort,x);
		delete sort;
		break;
	case 9:
		sort = new CountingSort;
		input(sort,x);
		delete sort;
		break;
	case 10:
		sort = new RadixSort;
		input(sort,x);
		delete sort;
		break;
	case 11:
		sort = new HeapSort;
		input(sort,x);
		delete sort;
		break;
	case 12:
		sort = new QuickSort;
		input(sort,x);
		delete sort;
		break;
	case 13:
		sort = new MergeSort;
		input(sort,x);
		delete sort;
		break;
	case 14:
		clrscr();
		break;
	case 15:
		// xử lý khi người dùng thoát
		Sleep(400);
		infor();
		TextColor(12);
		gotoXY(95, 21);
		wcout << L"Exiting...\n";
		Sleep(1000);
		clrscr();
		gotoXY(95, 21);
		PlaySound(TEXT("quit.wav"), NULL, SND_FILENAME | SND_ASYNC);
		wcout << L"Cya";
		gotoXY(92, 40);
		Sleep(3000);
		break;

	}

}

// in ra thông tin của các bạn trong nhóm
void infor()
{
	PlaySound(TEXT("outro.wav"), NULL, SND_FILENAME | SND_ASYNC);
	ShowCur(0);
			clrscr();
			TextColor(7);
			gotoXY(100, 19);
			wcout << L"== Mentor ==\n";
			TextColor(15);
			gotoXY(97, 20);
			wcout << L"------------------\n";
			TextColor(3);
			gotoXY(100, 22);
			Sleep(1000);
			wcout << L"Bùi Văn Thành\n";
			TextColor(7);
			gotoXY(99, 24);
			Sleep(1000);
			wcout << L"== Created by ==\n";
			TextColor(15);
			gotoXY(96, 25);
			wcout << L"---------------------\n";
			TextColor(2);
			gotoXY(96, 27);
			Sleep(1000);
			wcout << L"Lê Đình Trí - 21521561\n";
			Sleep(1000);
			gotoXY(94, 28);
			wcout << L"Nguyễn Ngọc Nhung - 21521248\n";
			gotoXY(95, 29);
			Sleep(1000);
			wcout << L"Bùi Thành Đạt - 21520689\n";
			Sleep(2500);
	clrscr();
}

// in ra menu để người dùng lựa chọn
void firstMenu(int& dem) {
	clrscr();
	TextColor(15);
	wcout << L"\n\nCHOOSE ONE OPTION:\n------------------\n\n";
	if (dem == 0) TextColor(12);
	else TextColor(15);
	wcout << "   =====================\n   =                   =\n   = 1. Selection Sort =\n   =                   =\n   =====================\n";
	if (dem == 1) TextColor(12);
	else TextColor(15);
	wcout << "   ========================\n   =                      =\n   = 2. Interchange Sort  =\n   =                      =\n   ========================\n";
	if (dem == 2) TextColor(12);
	else TextColor(15);
	wcout << "   =====================\n   =                   =\n   = 3. Insertion Sort =\n   =                   =\n   =====================\n";
	if (dem == 3) TextColor(12);
	else TextColor(15);
	wcout << "   ============================\n   =                          =\n   = 4. Binary Insersion Sort =\n   =                          =\n   ============================\n";
	if (dem == 4) TextColor(12);
	else TextColor(15);
	wcout << "   =====================\n   =                   =\n   =  5. Bubble Sort   =\n   =                   =\n   =====================\n";
	if (dem == 5) TextColor(12);
	else TextColor(15);
	wcout << "   =====================\n   =                   =\n   = 6.  Shaker Sort   =\n   =                   =\n   =====================\n";
	if (dem == 6) TextColor(12);
	else TextColor(15);
	wcout << L"   ==================\n   =                =\n   =    More...     =\n   =                =\n   ==================\n";
	if (dem == 7) TextColor(12);
	else TextColor(15);
	wcout << L"   =================\n   =               =\n   =     Quit      =\n   =               =\n   =================\n";
}
void secondMenu(int& dem){
	clrscr();
	TextColor(15);
	wcout << L"\n\nCHOOSE ONE OPTION:\n------------------\n\n";
	if (dem == 8) TextColor(12);
	else TextColor(15);
	wcout << "   =====================\n   =                   =\n   = 7.   Shell Sort   =\n   =                   =\n   =====================\n";
	if (dem == 9) TextColor(12);
	else TextColor(15);
	wcout << "   =====================\n   =                   =\n   = 8. Counting Sort  =\n   =                   =\n   =====================\n";
	if (dem == 10) TextColor(12);
	else TextColor(15);
	wcout << "   =====================\n   =                   =\n   =   9. Radix Sort   =\n   =                   =\n   =====================\n";
	if (dem == 11) TextColor(12);
	else TextColor(15);
	wcout << "   =====================\n   =                   =\n   =   10. Heap Sort   =\n   =                   =\n   =====================\n";
	if (dem == 12) TextColor(12);
	else TextColor(15);
	wcout << "   =====================\n   =                   =\n   =  11. Quick Sort   =\n   =                   =\n   =====================\n";
	if (dem == 13) TextColor(12);
	else TextColor(15);
	wcout << "   =====================\n   =                   =\n   =  12. Merge Sort   =\n   =                   =\n   =====================\n";
	if (dem == 14) TextColor(12);
	else TextColor(15);
	wcout << L"   ==================\n   =                =\n   =    Back...     =\n   =                =\n   ==================\n";
	if (dem == 15) TextColor(12);
	else TextColor(15);
	wcout << L"   =================\n   =               =\n   =     Quit      =\n   =               =\n   =================\n";
}
void command()
{	
	char ch;
	int dem = 0;
	_setmode(_fileno(stdout), _O_U16TEXT);
	PlaySound(TEXT("begining.wav"), NULL, SND_FILENAME | SND_ASYNC);
	gotoXY(95, 18);
	TextColor(12);
	ShowCur(0);
	wcout << "== GROUP 12 IT002.M21 ==";
	gotoXY(92, 19);
	TextColor(15);
	wcout << "-----------------------------";
	Sleep(3600);
	gotoXY(84, 21);
	TextColor(10);
	ShowCur(0);
	ShowCur(0);
	wcout << "== NORTH TANK DIVISION Cooperation Present! ==";
	gotoXY(82, 22);
	TextColor(15);
	wcout << "---------------------------------------------------";
	Sleep(3600);
	TextColor(9);
	gotoXY(94, 24);
	ShowCur(0);
	wcout << "== SORTING PROGRAM 0.1a ==";
	gotoXY(92, 25);
	TextColor(15);
	wcout << "-------------------------------";
	Sleep(3000);
	clrscr();
	TextColor(15);
	ShowCur(1);
	PlaySound(TEXT("boot.wav"), NULL, SND_FILENAME | SND_ASYNC);
	wcout << "0> This is demo of Sorting Program. If you want the full version please DONATE...............";
	Sleep(300);
	wcout << "\n0> LAUNCHING PROGRAM.........................................................................";
	Sleep(300);
	wcout << "\n0> Copyright © 2022 NTD Cooperation, Inc.All rights reserved.................................";
	Sleep(300);
	wcout << "\n0> NTD PROPRIETARY / CONFIDENTIAL............................................................";
	Sleep(300);
	wcout << "\n0> Use is subject to license terms...........................................................";
	Sleep(300);
	wcout << "\n0> POST engaging.............................................................................";
	Sleep(300);
	wcout << "\n0> Executing TACTICAL ELECTRONIC VOICE AGENT ARTIFICIAL INTELLIGENCE.........................";
	Sleep(300);
	wcout << "\n0> Start VOLKNET.....";
	Sleep(3000);
	PlaySound(TEXT("Start.wav"), NULL, SND_FILENAME | SND_ASYNC);
	wcout << "\n0> "; wcout << "E"; Sleep(50); wcout << "s"; Sleep(50); wcout << "t"; Sleep(50); wcout << "a"; Sleep(50); wcout << "b"; Sleep(50); wcout << "l"; Sleep(50); wcout << "i"; Sleep(50); wcout << "s"; Sleep(50); wcout << "h"; Sleep(50); wcout << "i"; Sleep(50); wcout << "n"; Sleep(50); wcout << "g"; Sleep(50); wcout << " B"; Sleep(50); wcout << "a"; Sleep(50); wcout << "t"; Sleep(50); wcout << "t"; Sleep(50); wcout << "l"; Sleep(50); wcout << "e"; Sleep(50); wcout << "f"; Sleep(50); wcout << "i"; Sleep(50); wcout << "e"; Sleep(50); wcout << "l"; Sleep(50); wcout << "d"; Sleep(50); wcout << " C"; Sleep(50); wcout << "o"; Sleep(50); wcout << "n"; Sleep(50); wcout << "t"; Sleep(50); wcout << "r"; Sleep(50); wcout << "o"; Sleep(50); wcout << "l"; Sleep(50); wcout << " S"; Sleep(50); wcout << "t"; Sleep(50); wcout << "a"; Sleep(50); wcout << "n"; Sleep(50); wcout << "d"; Sleep(50); wcout << "b"; Sleep(50); wcout << "y"; Sleep(50); wcout << "."; Sleep(50); wcout << "."; Sleep(50); wcout << ".";
	Sleep(3000);
	PlaySound(TEXT("Welcome.wav"), NULL, SND_FILENAME | SND_ASYNC); 
	clrscr();
	TextColor(11);
	gotoXY(100, 20);
	ShowCur(0);
	wcout << "W"; Sleep(50); wcout << "E"; Sleep(50); wcout << "L"; Sleep(50); wcout << "C"; Sleep(50); wcout << "O"; Sleep(50); wcout << "M"; Sleep(50); wcout << "E"; Sleep(500);
	Sleep(2000);
	PlaySound(TEXT("newtechaquired(inputfile).wav"), NULL, SND_FILENAME | SND_ASYNC);
	do
	{	
		while (true) {
			firstMenu(dem);
			ch = _getch();
			if (ch == 13)
			{
				selection(dem);
				if (dem == 7 || dem == 6) break;
				dem = 0;
			}
			if (ch == 80) // xử lý thao tác nhấn nút down
			{
				dem++;
				if (dem > 7) dem = 0;
			}
			else if (ch == 72) // xử lý thao tác nhấn nút up
			{
				dem--;
				if (dem < 0) dem = 7;
			}
		}
		if (dem == 7) break;
		while (true) {
			dem == 8;
			secondMenu(dem);
			ch = _getch();
			if (ch == 13)
			{
				selection(dem);
				if (dem == 15 || dem == 14) break;
				dem = 8;
			}
			if (ch == 80) // xử lý thao tác nhấn nút down
			{
				dem++;
				if (dem > 15) dem = 8;
			}
			else if (ch == 72) // xử lý thao tác nhấn nút up
			{
				dem--;
				if (dem < 8) dem = 15;
			}
		}
		if (dem == 15) break;
	} while (true);
}