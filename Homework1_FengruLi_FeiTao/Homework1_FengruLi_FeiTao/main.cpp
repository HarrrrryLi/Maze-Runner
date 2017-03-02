#include "Move.h"
#include <Windows.h>

void main()
{
	srand(time(NULL));  //set random seed as time
	generatemaze();  
	displaymaze();
	cout << endl;
	Move m;

	//calculate runtime of forward A* with in favor smaller g-value
	SYSTEMTIME Fs_start_time;
	GetSystemTime(&Fs_start_time);
	m.AgentForward(0,1);
	SYSTEMTIME Fs_end_time;
	GetSystemTime(&Fs_end_time);
	cout << "Ties breaks with smaller g." << endl;
	cout << "Agent Gets Result with Forward A* algorithm needs " << ((Fs_end_time.wMinute - Fs_start_time.wMinute) * 60 * 1000 + (Fs_end_time.wSecond - Fs_start_time.wSecond) * 1000 + (Fs_end_time.wMilliseconds - Fs_start_time.wMilliseconds)) << " ms." << endl;
	cout << endl;

	m.reinitialize();
	//calculate runtime of forward A* with in favor larger g-value
	SYSTEMTIME Fl_start_time;
	GetSystemTime(&Fl_start_time);
	m.AgentForward(0, 0);
	SYSTEMTIME Fl_end_time;
	GetSystemTime(&Fl_end_time);
	cout << "Ties breaks with larger g." << endl;
	cout << "Agent Gets Result with Forward A* algorithm needs " << ((Fl_end_time.wMinute - Fl_start_time.wMinute) * 60 * 1000 + (Fl_end_time.wSecond - Fl_start_time.wSecond) * 1000 + (Fl_end_time.wMilliseconds - Fl_start_time.wMilliseconds)) << " ms." << endl;
	cout << endl;

	m.reinitialize();
	//calculate runtime of backward A* with in favor larger g-value
	SYSTEMTIME B_start_time;
	GetSystemTime(&B_start_time);
	m.AgentBackward();
	SYSTEMTIME B_end_time;
	GetSystemTime(&B_end_time);
	cout << "Agent Gets Result with Backward A* algorithm needs " << ((B_end_time.wMinute - B_start_time.wMinute) * 60 * 1000 + (B_end_time.wSecond - B_start_time.wSecond) * 1000 + (B_end_time.wMilliseconds - B_start_time.wMilliseconds)) << " ms." << endl;
	displaymaze();
	cout << endl;

	m.reinitialize();
	//calculate runtime of adaptive forward A* with in favor larger g-value
	SYSTEMTIME FA_start_time;
	GetSystemTime(&FA_start_time);
	m.AgentForward(1,0);
	SYSTEMTIME  FA_end_time;
	GetSystemTime(&FA_end_time);
	cout << "Agent Gets Result with Forward Adaptive A* algorithm needs " << ((FA_end_time.wMinute - FA_start_time.wMinute) * 60*1000+(FA_end_time.wSecond - FA_start_time.wSecond)*1000+(FA_end_time.wMilliseconds - FA_start_time.wMilliseconds)) << " ms." << endl;
	cout << endl;

	system("Pause");
}