#include <iostream>
#include <conio.h>
#include <string>
#include <string.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <iomanip>

//so lieu may bay
#define MAXLIST 300
#define MAXTICKET 300
#define SOLUONGMOITRANG 15
#define SOLUONGMOITRANG2 6

// trang thai chuyen bay
#define TT_HUYCHUYEN 0
#define TT_CONVE 1
#define TT_HETVE 2
#define TT_HOANTAT 3

// tinh trang ve
#define TICHKET_DABAN 1
#define TICHKET_TRONG 0

// giao dien
#define X_a 110
#define Y_a 6

#define X_ThongBao 120
#define Y_ThongBao 40

#define X_DISPLAY 5
#define Y_DISPLAY 4

#define X_MENU_TICKET 20
#define Y_MENU_TICKET 4

#define X_PAGE 20
#define Y_PAGE 40

#define X_TITLE 60
#define Y_TITLE 1

#define Y_MENU2 10
#define Y_MAIN 15
// key
#define SPACE  32
#define ESC  27
#define ENTER 13
#define BACKSPACE 8
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_F2 60
#define KEY_F3 61
#define KEY_F4 62
#define KEY_F5 63
#define KEY_F10 68
#define PAGE_DOWN 81
#define PAGE_UP 73

#define MAX_LENGTH 15
#define MAX_CMND 12

//color
#define GREY 7
#define GREEN 6
#define PURPLE 5
using namespace std;

int currposAirplane = 0;
int currposPrecAirplane = 0;
int trangHienTaiMB = 1;
int tongsoTrangMB = 0;

int vitriHienTaiTK = 1;
int vitriTruocDoTK = 1;

int vitriHienTaiCB = 0;
int vitriTruocDoCB = 0;
int trangHientaiCB = 1;
int tongsoTrangCB = 0;

int vitriHienTaiCBDel = 0;
int vitriTruocDoCBDel = 0;
int trangHientaiCBDel = 1;
int tongsoTrangCBDel = 0;

int vitriHienTaiHK = 0;
int vitriTruocDoHK = 0;
int trangHientaiHK = 1;
int tongsoTrangHK = 0;

int vitriHienTaiMenu = 0;
int vitriTruocDoMenu = 0;

int SoHanhKhach;
unsigned int arrIdHanhKhach[200];
//========================================================
void gotoxy(short x, short y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void SetBGColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void TextColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
 
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;
 
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void Normal (){
	TextColor(11);
	SetBGColor(0);
}

void setColor(int textColor, int BackColor){
	// converts the textColor and BackColor to one
	int color = textColor + (BackColor * 16);

	// creates the handle we need to use
	HANDLE Console_Handle;

	// grab the handle so we can use it
	Console_Handle= GetStdHandle(STD_OUTPUT_HANDLE);

	// sets the color desired
	SetConsoleTextAttribute(Console_Handle, color);
}
//==========================Giao Dien=======================
// Hàm xóa màn hình.
void XoaManHinh()
{
	for (int i =3;i<29;i++)
	{
		gotoxy(2,i);
		cout<<"                                                           ";
	}
}

void XoamanhinhF()
{
	int toadoy=12;
	for (int i = 0; i < 15;i++)
	{
		gotoxy(16, toadoy); cout << "                ";
		gotoxy(34, toadoy); cout << "                     ";
		gotoxy(60, toadoy); cout << "                 ";
		gotoxy(81, toadoy); cout << "                ";
		gotoxy(105, toadoy);cout << "    ";
		toadoy++;
	}
}

void XoamanhinhH()
{
	int toadoy = 12;
	for (int i = 0; i < 15; i++)
	{
		gotoxy(25,toadoy); cout<<"        ";
		gotoxy(62,toadoy); cout<<"        ";
		toadoy++;
	}
}

void VeKhungCH(int x, int y, int width, int height, bool draw) 
{
	if (draw)
	{	
		TextColor(11);
		gotoxy(x, y);
		cout << char(218);
		gotoxy(x + width, y);
		cout << char(191);
		gotoxy(x, y + height);
		cout << char(192);
		gotoxy(x + width, y + height);
		cout << char(217);
		for (int i = y + 1; i < (y + height); i++)
		{
			gotoxy(x, i);
			cout << char(179);
			gotoxy(x+width, i);
			cout << char(179);
		}
		
		for (int i = x + 1; i < (x + width); i++)
		{
			gotoxy(i, y);
			cout << char(196);
			gotoxy(i, y+height);
			cout << char(196);
		}
		
	}
	else 
	{
		for (int i = x; i <= (x + width); i++)
		{
			gotoxy(i, y);
			cout << " ";
			gotoxy(i, y + height);
			cout << " ";
		}
		for (int i = y + 1; i < (y + height); i++)
		{
			gotoxy(x, i);
			cout << " ";
			gotoxy(x + width, i);
			cout << " ";
		}
	}
	Normal();
}

void KhungXuatMB()
{
	TextColor(6);
	gotoxy(8,1);
	cout<<"<============ DANH SACH MAY BAY ============>";
	TextColor(9);
	gotoxy(7,3);
	cout<<"STT";
	gotoxy(15,3);
	cout<<"LOAI MAY BAY";
	gotoxy(35,3);
	cout<<"SO HIEU";
	gotoxy(47,3);
	cout<<"SO CHO";
	
	VeKhungCH(5,2,49,23,1);
	for (int i = 3;i<26;i++)
	{
		gotoxy(11,i);
		cout<<char (179);
		gotoxy(31,i);
		cout<<char (179);
		gotoxy(45,i);
		cout<<char (179);
	}
	gotoxy(6,4);
	for (int i = 1; i< 49;i++)
	cout<<char(196);
	//nga ba huong xuong
	gotoxy(11,2);	cout<<char (194);
	gotoxy(31,2);	cout<<char (194);
	gotoxy(45,2);	cout<<char (194);
	//nga tu
	gotoxy(11,4);	cout<<char (197);
	gotoxy(31,4);	cout<<char (197);
	gotoxy(45,4);	cout<<char (197);
	//nga ba huong len
	gotoxy(11,25);	cout<<char (193);
	gotoxy(31,25);	cout<<char (193);
	gotoxy(45,25);	cout<<char (193);
	gotoxy(5,4);
	cout<<char (195);
	gotoxy(54,4);
	cout<<char (180); //nga ba sang trai
	Normal();
}

// Di chuyen khung chon
int KhungChon(int x,int y, int wide ,int numberchoices)
{
	//y=2
	int i=1;
	int n=y;
	int keyboard;
	
	do 
	{
		if ((i > numberchoices) || (i<1) ) 
			{
			n=y;
			i=1;
			}
		TextColor(4);
		VeKhungCH(x-1,n-1, wide,2,1);
			
		keyboard = getch();
		if (keyboard == 0) keyboard = getch();
			{
			if (keyboard == KEY_DOWN)
				{
					SetBGColor(0);
					VeKhungCH(x-1,n-1,wide,2,0);
					n+=2;
					i++;
				}
			if (keyboard == KEY_UP)
				{
					SetBGColor(0);
					VeKhungCH(x-1,n-1,wide,2,0);
					n-=2;
					i--;
				}
			}
		
	}
	while ((keyboard != ENTER) && (keyboard != ESC));
	if (keyboard == ENTER) 
	{ 
		
		VeKhungCH(x-1,n-1,wide,2,0);
		TextColor(11);
		return i;
	}
	if (keyboard == ESC) 
	{ 
		VeKhungCH(x-1,n-1,wide,2,0);
		TextColor(11);
		return 5;
	}
}
// Nen chay
void RunningColor(int x, int y)
{
	gotoxy(x,y);
	setColor(11, 0);
}

string tpMenuChinh[9] = { " MAY BAY " ," CHUYEN BAY "," HANH KHACH "," DAT VE "," HUY VE "," HANH KHACH 1 CHUYEN BAY "," CHUYEN BAY TRONG NGAY "," DANH SACH VE CHUYEN BAY "," CHUYEN BAY CUA MAY BAY "};
int taodoxMenuChinh[5];

void Intro(){
	string a;
	ifstream file("C:\\Users\\Admin\\Desktop\\chuyenbay\\lammau.txt");
	while(!file.eof()){
		getline(file, a);		
		cout << a << endl;
	}
}

void CreatBox(int x, int y, string text, int lenght){
	
	gotoxy(x - 2, y - 1);
	cout << char(218) << setw(lenght) << setfill(char(196)) << char(196) << char(191);
	if (lenght != 20){
		gotoxy(x - 2, y);
		TextColor(14);
		cout << char(179) << text << setw(lenght - text.length() + 1) << setfill(' ') << char(179);
		TextColor(11);
	}
	else {
		gotoxy(x - 2, y);
		cout << char(179);
		gotoxy(x + 4, y);
		cout << text << setw(lenght - text.length() - 4) << setfill(' ') << char(179);
	}
	gotoxy(x- 2, y + 1);
	cout << char(192) << setw(lenght) << setfill(char(196)) << char(196) << char(217);
}

void ChuyenMauMenu(string key[], int vitri)
{
	gotoxy(taodoxMenuChinh[vitri] - 3, Y_MAIN + vitri * 2); cout << char(175);
	gotoxy(taodoxMenuChinh[vitri] + 2 + tpMenuChinh[vitri].length(), Y_MAIN + vitri * 2); cout << char(174);
	gotoxy(taodoxMenuChinh[vitri], Y_MAIN + vitri * 2);
	setColor(0, 14);
	cout << key[vitri];

	gotoxy(taodoxMenuChinh[vitriTruocDoMenu], Y_MAIN + vitriTruocDoMenu * 2);
	setColor(11, 0);
	cout << key[vitriTruocDoMenu];
	//getch();
	//gotoxy(taodoxMenuChinh[vitriTruocDoMenu] - 3, Y_MAIN + vitri * 2); cout << char(0);
	//gotoxy(taodoxMenuChinh[vitriTruocDoMenu] + 2 + tpMenuChinh[vitri].length(), Y_MAIN + vitri * 2); cout << char(0);
	
	vitriTruocDoMenu = vitri;
}

void ChangeColorItemMainMenu(string key, int index, int newColor, int oldColor)
{
	gotoxy(taodoxMenuChinh[index] , Y_MAIN);
	setColor(0, newColor);
	cout << key;
	setColor(11, oldColor);
}
void MainMenu(string key[], int nKey)
{
	int center;
	system("color 0B");
	gotoxy(108 - 7, Y_MAIN); cout << char(175); // 2 dau lon hon
	gotoxy(108 + 7, Y_MAIN); cout << char(174); // 2 dau be hon
	for (int i = 0; i < nKey; i++)
	{
		center = 108 - (tpMenuChinh[i].length() / 2);
		taodoxMenuChinh[i] = center;
		gotoxy(center, Y_MAIN + i * 2);
		cout << " " << tpMenuChinh[i] << " ";
	}
	ChangeColorItemMainMenu(key[0], 3, 14, 0);
}

void BoxTicket(int x, int y, int  text, int stt)
{
	gotoxy(x - 2, y - 1);
	cout << char(218) << setw(3) << setfill(char(196)) << char(196) << char(191);
	cout << endl;
	
	gotoxy(x - 2, y);
	cout << char(179) << setw(3);
	if (stt == TICHKET_DABAN) SetBGColor(7);
	TextColor(14);
	cout << setfill('0') << text;
	TextColor(11);
	SetBGColor(0);
	cout << char(179);
	gotoxy(x - 2, y + 1);
	cout << char(192) << setw(3) << setfill(char(196)) << char(196) << char(217);
}

string tpGiaodienMB[3] = { "SO HIEU MAY BAY", "LOAI MAY BAY", "SO CHO" };
string tpGiaodienCB[6] = { "SO HIEU MB", "MA CHUYEN BAY", "NGAY GIO","SAN BAY DEN","TRANG THAI","SO VE" };
string tpGiaodienHK[4] = { "CMND", "HO", "TEN", "PHAI" };
string tpGiaodienThongTinVe[2] = { "CHUYEN BAY", "THONG TIN CHUYEN BAY"};
string tpGiaodienHK1CB[5] = { "STT", "SO VE", "SO CMND", "HO TEN", "PHAI"};
string tpMucLucCB[2] = { " F2:Them   F3:Huy   F4:Hieu Chinh   F5:Xoa   F 10:Save ", " QUAN LY CAC CHUYEN BAY " };
string tpMucLucHK[2] = { " F2:Them   F3:Xoa   F4:Hieu Chinh   F 10:Save ", " QUAN LY HANH KHACH " };

int toadoxGiaoDien[7] = { 11,31,56,77,96,111,121 }; // chuyen bay, hanh khach
int toadoxGiaoDien2[3] = { 20, 50, 94 }; // dung cho huy ve
int toadoxGiaoDien3[6] = { 40,48,58,72,90,99 }; // dung cho thong ke hanh khach 1 chuyen bay
void GiaoDienChinhSua(string key[], int nKey, int lenght){
	int yA = Y_a;
	for (int i = 0; i < nKey; i++){
		CreatBox(X_a + 20, yA, key[i], lenght);
		yA += 3;
	}
}

void TitleBangChon(string key[]){
	gotoxy(toadoxGiaoDien[0] + 20, Y_DISPLAY + 39);
	setColor(15, 6);
	cout <<  key[0];
	gotoxy(X_TITLE, Y_TITLE); cout << key[1];
	gotoxy(X_ThongBao + 30, Y_ThongBao + 3);
	cout << "ESC : thoat";
	setColor(11, 0);
}

void DeleteMenuAdd()
{
	//system("color 5A");
	for (int i = 0; i < 20; i++)
	{
		gotoxy(X_a + 18, Y_a + i - 1);
		cout << setw(60) << setfill(' ') << " ";
	}
}

void DeleteOldData(int nKey, int locate)
{
	for (int i = 0; i < nKey; i++)
	{
		gotoxy(toadoxGiaoDien[i] + 1, Y_DISPLAY + 3 + locate);
		cout << setw(toadoxGiaoDien[i] - toadoxGiaoDien[i]-2) << setfill(' ') << " ";		
	}
}

void DeleteNote(int nColumn)
{
	gotoxy(toadoxGiaoDien[0] + 1, Y_DISPLAY + 40);
	cout << setw(toadoxGiaoDien[nColumn] - toadoxGiaoDien[0] - 1) << " " << setfill(' ');
}

void DeleteNotify()
{
	gotoxy(X_ThongBao, Y_ThongBao);
	cout << setw(35) << setfill(' ') << " ";
	gotoxy(X_ThongBao - 5, Y_ThongBao + 1);
	cout << setw(40) << setfill(' ') << " ";
	gotoxy(X_ThongBao - 5, Y_ThongBao + 2);
	cout << setw(40) << setfill(' ') << " ";
	gotoxy(X_ThongBao - 5, Y_ThongBao + 3);
	cout << setw(33) << setfill(' ') << " ";
}

void Display(string key[], int nKey)
{
	int arrTemp[7];
	if (nKey != 5){
		for (int i = 0; i <= nKey; i++){
			arrTemp[i] = toadoxGiaoDien[i];
		}
	}
	else {
		for (int i = 0; i <= nKey; i++){
			arrTemp[i] = toadoxGiaoDien3[i];
		}
	}
	
	TextColor(14);
	for (int i = 0; i < nKey; i++)
	{
		gotoxy(arrTemp[i], Y_DISPLAY+ 1);
		cout << key[i];
	}
	TextColor(11);
	
	for (int j = Y_DISPLAY; j <= Y_DISPLAY + 32; j++)
	{
		for (int i = 0; i < nKey + 1; i++)
		{
			gotoxy(arrTemp[i] - 3, j);
			cout << char(179); // cot thang
		}
	}

	for (int i = arrTemp[0]; i <= arrTemp[nKey]; i++)
	{
		gotoxy(i - 3, Y_DISPLAY);
		if (i == arrTemp[1] || i == arrTemp[2] || i == arrTemp[3] || i == arrTemp[4] || i == arrTemp[5])
		{
			cout << char(194);
		}
		else if (i == arrTemp[0])
		{
			cout << char(218); //moc phai
		}	
		else if (i == arrTemp[nKey])
		{
			cout << char(191);//moc trai
		}  
		else
		{
			cout << char(196); //duong thang ngang
		}
		
		gotoxy(i - 3, Y_DISPLAY + 2);
		if (i == arrTemp[1] || i == arrTemp[2] || i == arrTemp[3] || i == arrTemp[4] || i == arrTemp[5])
			cout << char(197); //nga 4
		else if (i == arrTemp[0])
		{
			cout << char(195); //nga 3 sang phai
		}
		else if (i == arrTemp[nKey])
		{
			cout << char(180);//nga 3 sang trai
		}
		else
		{
			cout << char(196); //duong thang ngang
		}

		gotoxy(i -3, Y_DISPLAY + 33);
		if (i == arrTemp[nKey])
		{
			cout << char(217); //nga 3 sang trai
		}
		else if (i == arrTemp[1] || i == arrTemp[2] || i == arrTemp[3] || i == arrTemp[4] || i == arrTemp[5])
			cout << char(193);
		else if (i == arrTemp[0])
			cout << char(192); //nga 3 sang phai
		else
		{
			cout << char(196); //duong thang ngang
		}
	}
	
	if (nKey == 4)
	{
		gotoxy(arrTemp[4] - 3, Y_DISPLAY);
		cout << char(191);
		gotoxy(arrTemp[4] - 3, Y_DISPLAY + 2);
		cout << char(180);
	}
	
	if (nKey == 5)
	{
		gotoxy(arrTemp[5] - 3, Y_DISPLAY);
		cout << char(191);
		gotoxy(arrTemp[5] - 3, Y_DISPLAY + 2);
		cout << char(180);
	}
	
}


void Display2(string key[], string key2[], int nKey)
{
	TextColor(14);
	for (int i = 0; i < nKey; i++)
	{
		gotoxy(toadoxGiaoDien2[i], Y_DISPLAY + 6);
		cout << key[i];
	}
	TextColor(11);
	
	for (int j = Y_DISPLAY + 5; j <= Y_DISPLAY + 20; j++)
	{
		for (int i = 0; i < nKey + 1; i++)
		{
			gotoxy(toadoxGiaoDien2[i] - 3, j);
			cout << char(179); // cot thang
		}
	}
	
	TextColor(14);
	gotoxy(toadoxGiaoDien2[1], Y_DISPLAY + 8); cout << "SO HIEU MB";
	for (int i = 1; i < 6; i++)
	{
		gotoxy(toadoxGiaoDien2[1], Y_DISPLAY + 8 + i * 2);
		if (i == 5) 
			cout << "SO GHE TREN MB";
		else 
			cout << key2[i + 1];
	}
	TextColor(11);
	
	for (int i = toadoxGiaoDien2[0]; i <= toadoxGiaoDien2[nKey]; i++)
	{
		gotoxy(i - 3, Y_DISPLAY + 5);
		if (i == toadoxGiaoDien2[1])
			cout << char(194);//nga 3
		else if (i == toadoxGiaoDien2[0])
		{
			cout << char(218); //moc phai
		}
		else if (i == toadoxGiaoDien2[nKey])
		{
			cout << char(191);//moc trai
		}  
		else
		{
			cout << char(196); //duong thang ngang
		}

		gotoxy(i - 3, Y_DISPLAY + 7);
		if (i == toadoxGiaoDien2[1])
			cout << char(197); //nga 4
		else if (i == toadoxGiaoDien2[0])
		{
			cout << char(195); //nga 3 sang phai
		}
		else if (i == toadoxGiaoDien2[nKey])
		{
			cout << char(180);//nga 3 sang trai
		}
		else
		{
			cout << char(196); //duong thang ngang
		}

		gotoxy(i - 3, Y_DISPLAY + 20);
		if (i == toadoxGiaoDien2[0])
		{
			cout << char(192); //queo sang phai
		}
		else if (i == toadoxGiaoDien2[1])
		{
			cout << char(193);
		}
		else if (i == toadoxGiaoDien2[nKey])
		{
			cout << char(217); //queo sang trai
		}
		else
		{
			cout << char(196); //duong thang ngang
		}
	}
}

void Display3(){
	TextColor(11);
	gotoxy(25, 14); cout << char(218); // moc phai
	for (int i = 0; i < 15; i++){
		gotoxy(26 + i, 14); cout << char(196); // thang ngang
	}
	cout << "THONG TIN";
	for (int i = 24; i < 39; i++){
		gotoxy(26 + i, 14); cout << char(196);
	}
	cout << char(191); // moc trai
	
	for (int i = 1; i < 12; i++){
		gotoxy(25, 14 + i); cout << char(179); // cot thang
		gotoxy(65, 14 + i); cout << char(179); // cot thang
	}
	
	TextColor(14);
	gotoxy(32, 17); cout << "NGO QUANG HOA";
	gotoxy(32, 19); cout << "N17DCCN051";
	gotoxy(45, 19); cout << "D17CQCN01 - N";
	gotoxy(32, 21); cout << "LUONG QUANG HUY";
	gotoxy(32, 23); cout << "N17DCCN057";
	gotoxy(45, 23); cout << "D17CQCN01 - N";
	TextColor(11);

	gotoxy(25, 26); cout << char(192);
	for (int i = 1; i < 40; i++){
		gotoxy(25 + i, 26); cout << char(196);
	}
	cout << char(217);
	
	TextColor(14);
	SetBGColor(3);
	gotoxy(30, 38); cout << "         ";
	gotoxy(30, 39); cout << "  ENTER  ";
	gotoxy(30, 40); cout << "         ";
	gotoxy(132, 38); cout << "         ";
	gotoxy(132, 39); cout << "   ECS   ";
	gotoxy(132, 40); cout << "         ";
	TextColor(11);
	SetBGColor(0);
}

int ChooseMenu(string key[], int nKey)
{
	ShowCur(false);
	vitriHienTaiMenu = 0;
	vitriTruocDoMenu = 0;
	int keyboard = 0;
	while (true)
	{
		keyboard = getch();
		if (keyboard == 0)
			keyboard = getch();

		switch (keyboard)
		{
		case KEY_UP:
			gotoxy(taodoxMenuChinh[vitriTruocDoMenu] - 3, Y_MAIN + vitriHienTaiMenu * 2); cout << char(0);
			gotoxy(taodoxMenuChinh[vitriTruocDoMenu] + 2 + tpMenuChinh[vitriHienTaiMenu].length(), Y_MAIN + vitriHienTaiMenu * 2); cout << char(0);
			if (vitriHienTaiMenu > 0)
				vitriHienTaiMenu = vitriHienTaiMenu - 1;
			else
				vitriHienTaiMenu = nKey - 1;
			ChuyenMauMenu(key, vitriHienTaiMenu);
			break;
		case KEY_DOWN:
			gotoxy(taodoxMenuChinh[vitriTruocDoMenu] - 3, Y_MAIN + vitriHienTaiMenu * 2); cout << char(0);
			gotoxy(taodoxMenuChinh[vitriTruocDoMenu] + 2 + tpMenuChinh[vitriHienTaiMenu].length(), Y_MAIN + vitriHienTaiMenu * 2); cout << char(0);
			if (vitriHienTaiMenu < nKey - 1)
				vitriHienTaiMenu = vitriHienTaiMenu + 1;
			else
				vitriHienTaiMenu = 0;
			ChuyenMauMenu(key, vitriHienTaiMenu);
			break;
		case ESC:
			return -1;
			break;
		case ENTER:
			ShowCur(true);
			return vitriHienTaiMenu;
			break;
		}
	}
}
//=========================Ngay Thang===============================
int NgayTrongNam[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

struct DateTime {
	int ngay = 0;
	int  thang = 0;
	int  nam = 0;
	int gio = 0;
	int phut = 0;
};

bool KiemTraNgayThang(DateTime dt) {
	NgayTrongNam[2] = 28;
	if ((dt.nam % 4 == 0 && dt.nam % 100 != 0) || (dt.nam % 400 == 0)) // nam nhuan la nam chia het cho 400 hoac chia het cho 4 va khong chia het cho 100
		NgayTrongNam[2] = 29;
	if (dt.ngay > NgayTrongNam[dt.thang]) return false;
	return true;
}

bool KiemTraNgayThangCoHopLe(DateTime dt){
	if (!KiemTraNgayThang(dt)) return false;
	DateTime dtime;
	NgayTrongNam[2] = 28;
	time_t hienTai = time(0); // time_t la kieu du lieu thoi gian : có giá tri là so giây tính tu epoch (1970-01-01 00:00:00 UTC)
	tm *localT = localtime(&hienTai); // tm la mot struct, ham localtime dung de dinh dang ngay thang nam cho so giay ke tu epoch (1970-01-01 00:00:00 UTC)
	dtime.nam = 1900 + localT->tm_year;
	dtime.thang = 1 + localT->tm_mon;
	dtime.ngay = localT->tm_mday;
	dtime.gio = localT->tm_hour;
	dtime.phut = localT->tm_min;
	
	if (dt.nam < dtime.nam) return false;
	if ((dt.nam == dtime.nam) && (dt.thang < dtime.thang)) return false;
	if ((dt.nam % 4 == 0 && dt.nam % 100 != 0) || (dt.nam % 400 == 0))	NgayTrongNam[2] = 29;
	if ((dt.nam == dtime.nam) && (dt.thang == dtime.thang) && (dt.ngay < dtime.ngay)) return false;
	if ((dt.nam == dtime.nam) && (dt.thang == dtime.thang) && (dt.ngay == dtime.ngay) && (dt.gio < dtime.gio)) return false;
	if ((dt.nam == dtime.nam) && (dt.thang == dtime.thang) && (dt.ngay == dtime.ngay) && (dt.gio == dtime.gio) && (dt.phut < dtime.phut)) return false;
	return true;
}

void OutputDateTime(DateTime dt){
	if (dt.ngay / 10 == 0) cout << "0";
	cout << dt.ngay << "/";
	if (dt.thang / 10 == 0) cout << "0";
	cout << dt.thang << "/" << dt.nam << " " << dt.gio << ":" << dt.phut;
	if (dt.phut == 0) cout << "0";
}
//=========================================================
//void NhapHoacEditCMND(char &result[], bool &isMove, int &ordinal, bool &isSave, int doDaiChuoi)
//{
//	int lengh;
//	if (result != 0)
//		lengh = strlen(result);
//	else lengh = 0;
//	Gotoxy(X_a + doDaiChuoi, ordinal * 3 + Y_a);
//	if (result != 0)
//		cout << result;
//	int count = lengh;
//	while (true)
//	{
//		while (kbhit())
//		{
//			int key = getch();
//			if (key != 224 && key != SPACE && key != 0)
//			{
//				if (key >= 48 && key <= 57 && count < 12)
//				{
//					//int f = key - 48;
//					if (count == 0 && key == 48)
//						continue;
//					else
//					{
//						cout << (char)key;
//						result ++ (char)key;
//						count++;
//					}
//				}
//				else if (key == ENTER)
//					return;
//				else if (key == BACKSPACE && count >0)
//				{
//					cout << "\b" << " " << "\b";
//					count--;
//					result.
//				}
//			}
//			else if (key == 224)
//			{
//				key = getch();
//				if (key == KEY_UP)
//				{
//					isMove = true;
//					return;
//				}
//				else
//				{
//					isMove = false;
//					return;
//				}
//			}
//			else if (key == 0)
//			{
//				key = getch();
//				if (key == KEY_F10)
//				{
//					isSave = true;
//					return;
//				}
//			}
//		}
//	}
//}

void NhapHoacEditCMND(unsigned int &result, bool &isMove, int &ordinal, bool &isSave, int doDaiChuoi)
{
	int length;
	if (result != 0)
	length = (int)log10(result) + 1; // hieu don gian la log10 la ham toan hoc, chu yeu dung log10 de lay do dai cua result
	else length = 0;
	gotoxy(X_a + 20 + doDaiChuoi, ordinal * 3 + Y_a);
	if (result != 0) cout << result;
	int count = length;
	while (true)
	{
		while (kbhit())
		{
			int key = getch();
			if (key != 224 && key != SPACE && key != 0)
			{
				if (key >= 48 && key <= 57 && count < 9)
				{
					int f = key - 48;
					if (count == 0 && key == 48)
						continue;
					else
					{
						cout << f;
						result = result * 10 + (f);
						count++;
					}
				}
				else if (key == ENTER)
					return;
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					count--;
					result /= 10;
				}
			}
			else if (key == 224)
			{
				key = getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}
	}
}

void NhapHoacEditID(string &result, bool &isMove, int &ordinal, bool &isSave, int doDaiChuoi)
{
	int length = result.length();
	gotoxy(X_a + 20 + doDaiChuoi , ordinal * 3 + Y_a);
	cout << result;
	int count = length;
	while (true)
	{
		while (kbhit())
		{
			int key = getch();
			if (key != 224 && key != SPACE && key != 0)
			{
				if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122)  || (key >= 48 && key <= 57))
				{
					if (count < MAX_LENGTH)
					{
						count++;
						cout << (char)key;
						result += (char)key;
					}
				}
				else if (key == ENTER)
					return;
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					result.erase(result.length() - 1,1); // ham erase(x,y) xoa y phan tu sau vi tri x
					count--;
				}
			}
			else if (key == 224)
			{
				key = getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//kbhit
	}//while true
}

void NhapHoacEditNgayGio(int &result, bool &isMove, int &ordinal, bool &isSave, int condition, int doDaiChuoi)
{
	int length;
	if (result != 0)
	length = (int)log10(result) + 1; // hieu don gian la log10 la ham toan hoc, chu yeu dung log10 de lay do dai cua result
	else length = 0;
	gotoxy(X_a + 20 + doDaiChuoi + ordinal * 3, 6 + Y_a);
	if (result != 0)
	cout << result;
	int count = length;
	//bool isSpaced = false;
	while (true)
	{
		while (kbhit())
		{
			int key = getch();
			if (key != 224 && key != SPACE && key != 0)
			{
				if (key >= 48 && key <= 57)
				{
					int f = key - 48;
					if (count == 0 && key == SPACE)
						continue; //dang xem xet co nen can khong ?
					else
					{
						if (result * 10 + (f) <= condition)
						{
							cout << f;
							result = result * 10 + (f);
							count++;
						}
					}
				}
				else if (key == ENTER)
				{
					if (result > condition)
						continue;
					return;
				}
				else if (key == 8 && count >0)
				{
					cout << "\b" << " " << "\b";
					count--;
					result /= 10;

				}
			}
			else if (key == 224)
			{
				key = getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}
	}
}

void NhapHoacEditTen(string &result, bool &isMove, int &ordinal, bool &isSave, int doDaiChuoi)
{
	int length = result.length();
	gotoxy(X_a + 20 + doDaiChuoi, ordinal * 3 + Y_a);
	cout << result;
	int count = length;
	bool isSpaced = false;
	while (true)
	{
		while (kbhit())
		{
			int key = getch();	
			if (key != 224  && key != 0)
			{
				if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == SPACE )
				{
					if (count < MAX_LENGTH)
					{
						count++;
						//if (!isSpaced && key == SPACE)
						//{
						//	cout << (char)key;
						//	result += (char)key;
						//	isSpaced = true;
						//}
						//else
						//{
						cout << (char)key;
						result += (char)key;
						isSpaced = false;
						//}
					}
				}
				else if (key == ENTER)
					return;
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					result.erase(result.length() - 1, 1);
					count--;
				}
			}
			else if (key == 224)
			{
				key = getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//kbhit
	}//true
}

void NhapHoacEditSo(int &result, bool &isMove, int &ordinal, bool &isSave, int doDaiChuoi, int condition)
{
	int length;
	if (result != 0)
		length = (int)log10(result) + 1;
	else length = 0;
	gotoxy(X_a + 20 + doDaiChuoi, ordinal * 3 + Y_a);
	if (result != 0)
	cout << result;
	int count = length;
	while (true)
	{
		while (kbhit())
		{
			int key = getch();
			if (key != 224 && key != SPACE && key != 0 )
			{
				if (key >= 48 && key <= 57)
				{
					int f = key - 48;
					if (count == 0 && key == 48)
						continue;
					else
						if (result * 10 + (f) <= condition)
						{
							cout << f;
							result = result * 10 + (f);
							count++;
						}
				}
				else if (key == ENTER)
				{
					if (result > condition)
						continue;
					return;
					
				}
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					count--;
					result /= 10;
				}
			}
			else if (key == 224)
			{
				key = getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//kbhit
	}//while tru

}

void DinhDangSoHieu(char *a)
{
	int length = strlen(a);
	for (int i = 0; i < length; ++i)
		a[i] = toupper(a[i]);
}

void DinhDangTen(char *a)
{
	a[0] = toupper(a[0]); // ham toupper(x) in hoa x
	int length = strlen(a);
	for (int i = 1; i < length; ++i)
	{
		if (a[i - 1] == ' ' && a[i] != ' ') a[i] = toupper(a[i]);
		else a[i] = tolower(a[i]); // in thuong
	}
}

void Trim(char *s)
{
	int i = strlen(s) - 1;
	char *p = s;
	while (*p == ' ') p++;
	if (p != s) strcpy(s, p);
	while (s[i] == ' '  && i>0)
		i--;
	s[i + 1] = 0;
}


//======================MAY BAY=============================
struct PData {
	char SoHieu[15];
	char LoaiMayBay[40];
	int SoCho;
};

struct AirPlanes
{
	PData *data[MAXLIST] = {NULL};
	int n = -1;
};

void XuatMB(AirPlanes MB, int vitri, int toadoy)
{
	TextColor(11);
	gotoxy(7,toadoy) ; cout<<vitri+1;
	gotoxy(13,toadoy); cout<<MB.data[vitri]->LoaiMayBay;
	gotoxy(35,toadoy); cout<<MB.data[vitri]->SoHieu;
	gotoxy(47,toadoy); cout<<MB.data[vitri]->SoCho;
}

void XuatDSMBB(AirPlanes mb, int vitriDautien)
{
	int temp = -1, SOLUONGMOITRANGMB = 20;
	for (int i = vitriDautien; i < mb.n; i++)
	{
		temp++;
		if (temp < SOLUONGMOITRANGMB)
			XuatMB(mb, i, 5 + temp);
	}
}

// Tim kiem so hieu may bay
int SearchSH(AirPlanes DSMB, char SH[15])
{
	int vitri = -1;
	Trim(SH);
	for (int i = 0; i <= DSMB.n; i++)
		if (stricmp(DSMB.data[i]->SoHieu, SH) == 0) vitri = i;
	return vitri;
}

//Sinh So Hieu may bay tu dong
void SinhSH(AirPlanes &DSMB, int &vitri)
{
	int i = -1;
	int dem = -1;
	string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char a[15];
	do
	{
		strncpy(a, DSMB.data[vitri]->LoaiMayBay, 2);
		a[2] = '\0';
		strupr(a);
		char Temp[5];
		int b = DSMB.data[vitri]->SoCho;
		i++;
		/*for (int k=1; k<=DSMB.n;k++)
		{
		if ((stricmp(DSMB.data[k]->LoaiMayBay,a)==0) && (DSMB.data[k]->SoCho == b)) i++;
		}*/
		if (b < 100)
		{
			itoa(b, Temp, 10);
			for (int j = 3; j >= 1; j--)
			{
				Temp[j] = Temp[j - 1];
			}
			Temp[4] = '\0';
			Temp[0] = '0';
		}
		else itoa(b, Temp, 10);
		strcat(a, Temp);

		if (i == 25)
		{
			dem++;
			i = 0;
		}
		if (dem >= 0)
		{
			char r[2];
			r[0] = (char)s[dem];
			r[1] = '\0';
			strcat(a, r);
		}
		char k[2];
		k[0] = (char)s[i];
		k[1] = '\0';
		strcat(a, k);

	} while (SearchSH(DSMB, a) > 0);
	strcpy(DSMB.data[vitri]->SoHieu, a);
}

int PickMB(AirPlanes dsmb)
{
	system("cls");
	TextColor(11);
	int vitriHienTai = 0; // dieu kien de khoi bi sai moi khi UP hay DOWN
	int trangHienTai = 1;
	int keyboard;
	int choice = 0;
	int k = 0;
	int toadoy = 5;
	int SOLUONGMOITRANGMB = 20;
	int tongsoTrang;
	KhungXuatMB();
	TextColor(11);
	gotoxy(45,26); cout<<"ESC: exit";
	Normal();
	XuatDSMBB(dsmb, vitriHienTai);
	SetBGColor(8);
	XuatMB(dsmb,0,toadoy);
	SetBGColor(0);
	VeKhungCH(89,19,35,6,1);
	setColor(3,0);
	gotoxy(90,21); cout<<" RIGHT/LEFT to NEXT/PREVIOUS page ";
	gotoxy(90,22); cout<<" ENTER to choose                  ";
	gotoxy(90,23); cout<<" ESC to exit                      ";
	Normal();
	while (true) {
	//	while(kbhit()){
			tongsoTrang = ((dsmb.n - 1) / SOLUONGMOITRANGMB) + 1;
			keyboard = getch();
			if (keyboard == 0) keyboard = getch();
			switch (keyboard) 
			{
				case KEY_UP: 
				{
					if (vitriHienTai > 0)
					{
						SetBGColor(0);
				    	XuatMB(dsmb,choice,toadoy);
				    	vitriHienTai--; choice--; toadoy--;
						SetBGColor(8);
						XuatMB(dsmb,choice,toadoy);
				    	SetBGColor(0);
				    }
				    break;
			    }
			    case KEY_DOWN: 
				{
					if (vitriHienTai < SOLUONGMOITRANGMB - 1 && (choice < dsmb.n-1) ) // dieu kien thu 2 de ngan khong cho xuong hang
					{
						SetBGColor(0);																	
					    XuatMB(dsmb,choice,toadoy);
					    vitriHienTai++; choice++; toadoy++;
					    SetBGColor(8);
						XuatMB(dsmb,choice,toadoy);
						SetBGColor(0);
					}
					break;
				}
				case KEY_RIGHT:
				{
				if (trangHienTai < tongsoTrang)
					{
						XoaManHinh();
						KhungXuatMB();
						trangHienTai++;
						vitriHienTai = 0;
						toadoy = 5;
						choice = (trangHienTai - 1) * SOLUONGMOITRANGMB;
						XuatDSMBB(dsmb, choice);
						SetBGColor(8);
						XuatMB(dsmb,choice,toadoy);
						SetBGColor(0);
					}
					break;
				}
				case KEY_LEFT: 
				{
					if (trangHienTai > 1)
						{
							XoaManHinh();
							KhungXuatMB();
							trangHienTai--;
							vitriHienTai = 0;
							toadoy = 5;
							choice = (trangHienTai - 1) * SOLUONGMOITRANGMB;
							XuatDSMBB(dsmb, choice);
							SetBGColor(8);
							XuatMB(dsmb,choice,toadoy);
							SetBGColor(0);
						}
					break;
				}
				case ENTER: 
				{
					SetBGColor(0);
				    XuatMB(dsmb,choice,toadoy);
				    VeKhungCH(89,19,35,6,0);
					gotoxy(90,21); cout<<"                                  ";
					gotoxy(90,22); cout<<"                                  ";
					gotoxy(90,23); cout<<"                                  ";
					Normal();
					return choice;
					break;
				}
				
				case ESC: 
				{
				SetBGColor(0);
				XuatMB(dsmb,choice,toadoy);
				VeKhungCH(89,19,35,6,0);
				gotoxy(90,21); cout<<"                                  ";
				gotoxy(90,22); cout<<"                                  ";
				gotoxy(90,23); cout<<"                                  ";
				Normal();
				return -1;
				break;
				}
			}
		}
//	}
}

void XuatDSMB(AirPlanes dsmb)
{
	ShowCur(false);
	system("cls");
	TextColor(11);
	int vitriHienTai = 0; // dieu kien de khoi bi sai moi khi UP hay DOWN
	int trangHienTai = 1;
	int keyboard;
	int choice = 0;
	int SOLUONGMOITRANGMB = 20;
	int tongsoTrang;
	KhungXuatMB();
	TextColor(11);
	gotoxy(45,26); cout<<"ESC: exit";
	Normal();
	XuatDSMBB(dsmb, vitriHienTai);
	VeKhungCH(89,20,35,5,1);
	setColor(3,0);
	gotoxy(90,22); cout<<" RIGHT/LEFT to NEXT/PREVIOUS page ";
	gotoxy(90,23); cout<<" ESC to exit                      ";
	Normal();
	while (true) { // lap vo tan
		while(kbhit()){
			tongsoTrang = ((dsmb.n - 1) / SOLUONGMOITRANGMB) + 1;
			keyboard = getch();
			if (keyboard == 0) keyboard = getch();
			switch (keyboard) 
			{
				case KEY_RIGHT:
				{
				if (trangHienTai < tongsoTrang)
					{
						XoaManHinh();
						KhungXuatMB();
						trangHienTai++;
						vitriHienTai = 0;
						choice = (trangHienTai - 1) * SOLUONGMOITRANGMB;
						XuatDSMBB(dsmb, choice);
					}
					break;
				}
				case KEY_LEFT: 
				{
					if (trangHienTai > 1)
						{
							XoaManHinh();
							KhungXuatMB();
							trangHienTai--;
							vitriHienTai = 0;
							choice = (trangHienTai - 1) * SOLUONGMOITRANGMB;
							XuatDSMBB(dsmb, choice);
						}
					break;
				}
				case ESC: 
				{
				gotoxy(90,21); cout<<"                                  ";
				gotoxy(90,22); cout<<"                                  ";
				gotoxy(90,23); cout<<"                                  ";
				Normal();
				return ;
				break;
				}
			}
		}
	}
	ShowCur(true);
}



// Them may bay vao DSMB
void AddDSMB(AirPlanes &DSMB)
{	
	char keyboard;
	do
	{
		XoaManHinh();
		TextColor(11);
		gotoxy(2,3);
		cout<<"Nhap loai may bay: ";
		DSMB.data[DSMB.n] = new PData;
		fflush(stdin);
		char b[16];
		cin.getline(b,16,'\n');
		Trim(b);
		strcpy(DSMB.data[DSMB.n]->LoaiMayBay,b);
	
		int a ;
		gotoxy(2,4);
		cout<<"Nhap so cho: ";
		cin>>a;
		while (a<20)
		{
			gotoxy(17,27);
			cout<<"So cho phai lon hon 20";
			gotoxy(17,28);
			cout<<"Press any key to continue...";
			keyboard=getch();
			gotoxy(17,27);
			cout<<"                                        ";
			gotoxy(17,28);
			cout<<"                              ";
			gotoxy(15,4);
			cout<<"    ";
			gotoxy(15,4);
			cin>>a;
		}
		DSMB.data[DSMB.n]->SoCho=a;
		SinhSH(DSMB,DSMB.n);
//		gotoxy(2,5);
		DSMB.n++;
		gotoxy(20,27);
		cout<<"Success!!! Any key to continue";
		gotoxy(20,28);
		cout<<"Press ESC to exit...";
		keyboard=getch();
	}
	while (keyboard != ESC);
}

//=======================CHUYEN BAY==========================
struct Ticket {
	int tinhTrang = TICHKET_TRONG;
	char cmndHK[10];
};

struct Flight {
	char id[15];
	char SanBayden[100];
	DateTime Ngaykhoihanh;
	int TrangThai = TT_CONVE;
	int SoVeDaBan = 0;
	int SoVe = 0;
	char SoHieu[15];
	Ticket *DanhSachVe = new Ticket[MAXTICKET];
};

struct nodeFlight {
	Flight DataFlight;
	struct nodeFlight *Next;
};
typedef struct nodeFlight NODE_CHUYENBAY;

struct listFlight { // de cho viec thao tac tren danh sach cac chuyen bay tro nen de dang. (vd them, xoa,.. de dang hon)
	int n = 0;
	NODE_CHUYENBAY *Head, *Tail;
};

NODE_CHUYENBAY* taoNodeFlight(Flight data) {
	NODE_CHUYENBAY *p = new nodeFlight;
	if (p == NULL) return NULL;	
	p->DataFlight = data; // gan gia tri cho node
	p->Next = NULL; // cho next tro toi NULL (init danh sach lien ket)
	return p;
}

void InitListFlight(listFlight &cb) {
	cb.Head = cb.Tail = NULL;
}

bool ListFight_Empty(listFlight cb) { // kiem tra ds chuyen bay co rong hay khong
	return cb.Head == NULL;
}

void ThemVaoDauList(listFlight &cb, Flight data) {
	NODE_CHUYENBAY *p = taoNodeFlight(data);
	p->Next = cb.Head;
	cb.Head = p;
	++cb.n;
}

void ThemVaoCuoiList(listFlight &cb, Flight data) {
	NODE_CHUYENBAY *p = taoNodeFlight(data);
	if (cb.Head == NULL)
		cb.Head = cb.Tail = p; // nut dau cung la nut cuoi
	else {
		cb.Tail->Next = p;
		cb.Tail = p;
	}
	++cb.n;
}

NODE_CHUYENBAY* FindFlight(listFlight cb, char *id){
	if (cb.Head == NULL) return NULL;
	for (NODE_CHUYENBAY *p = cb.Head; p != NULL; p = p->Next)
		if (stricmp(p->DataFlight.id, id) == 0)
			return p;
	return NULL;
}

int arrSTTChuyenBay[20];
int arrSoVe[20];
int SoCB;
void FindFlightTheoCMND(listFlight cb, char *cmnd){
	//if (cb.Head == NULL) return;
	SoCB = 0;
	int SoTTCBayTrongDS = 0, i = 0;
	for (NODE_CHUYENBAY *p = cb.Head; p != NULL; p = p->Next){
		for (int j = 0; j < p->DataFlight.SoVe; j++){
			if (strcmp(p->DataFlight.DanhSachVe[j].cmndHK, cmnd) == 0){
				arrSTTChuyenBay[i] = SoTTCBayTrongDS;
				arrSoVe[i] = j + 1;
				SoCB++; i++;
				break; 
			}
		}
		SoTTCBayTrongDS++;
	}
}

NODE_CHUYENBAY* FindFlightTheoThuTu(listFlight cb, int ThuTu){
	if (cb.Head == NULL) return NULL;
	if (cb.n - 1 < ThuTu) return NULL;
	if (cb.n - 1 == ThuTu) return cb.Tail;
	if (ThuTu == 0) return cb.Head;
	NODE_CHUYENBAY *p = cb.Head;
	int count = 0;
	while (count != ThuTu){
		p = p->Next;
		count++;
	}
	return p;
}

void InputDateTime(DateTime &dt, bool &newIsSave)
{
	int newOrdinal = 0;
	bool newIsMoveUp = false;
	newIsSave = false;
	gotoxy(X_a + 20 + 12 + 2, 6 + Y_a);
	cout << ":";
	gotoxy(X_a + 20 + 12 + 8, 6 + Y_a);
	cout << "/";
	gotoxy(X_a + 20 + 12 + 11, 6 + Y_a);
	cout << "/";
	while (true)
	{
 		switch (newOrdinal)
		{
		case 0:
			NhapHoacEditNgayGio(dt.gio, newIsMoveUp, newOrdinal, newIsSave, 23, 12);
			break;
		case 1:
			NhapHoacEditNgayGio(dt.phut, newIsMoveUp, newOrdinal, newIsSave, 59, 12);
			break;
		case 2:
			NhapHoacEditNgayGio(dt.ngay, newIsMoveUp, newOrdinal, newIsSave, 31, 12);
			break;
		case 3:
			NhapHoacEditNgayGio(dt.thang, newIsMoveUp, newOrdinal, newIsSave, 12, 12);
			break;
		case 4:
			NhapHoacEditNgayGio(dt.nam, newIsMoveUp, newOrdinal, newIsSave, 10000, 12);
			break;
	
		} // end switch newordinal
		
		//check move
		if (newIsMoveUp)
		{
			if (newOrdinal == 0)
				newIsMoveUp = false;
			else
				newOrdinal--;
		}
		else
		{
			if (newOrdinal == 4)
			{
				newIsMoveUp = true;
				return;
			}
			else
				newOrdinal++;
		}
		//--end check move

		if (newIsSave)
			return;
		else
			newIsSave = false;
	} // end while
}

bool Delete_Head(listFlight &cb){
	if (ListFight_Empty(cb)) return false;
	NODE_CHUYENBAY* p = cb.Head;
	cb.Head = p->Next;
	delete p;
	--cb.n;
	return true;
}

bool Delete_Tail(listFlight &cb)
{
		if (ListFight_Empty(cb)) return false;
		//NODE_CHUYENBAY *beforeP = NULL;
		for (NODE_CHUYENBAY *p = cb.Head; p != NULL; p = p->Next)
		{
			if (p->Next == cb.Tail)
			{
				//cb.Tail = beforeP;
				//beforeP->Next = NULL;
				//delete p;
				delete cb.Tail;
				p->Next = NULL;
				cb.Tail = p;
				--cb.n;
				return true;
			}
			//beforeP = p;
		}
}

bool Delete_After(listFlight &cb, NODE_CHUYENBAY* p)
{
	if (p == NULL || p->Next == NULL) return false;
	NODE_CHUYENBAY* q = p->Next;
	p->Next = q->Next;
	delete q;
	--cb.n;
	return true;
}

bool DeleteFlight_Id(listFlight &cb, Flight data)
{
	NODE_CHUYENBAY* p = FindFlight(cb, data.id);
	if (p == NULL) return false;
	if (p == cb.Head) return Delete_Head(cb);
	if (p == cb.Tail) return Delete_Tail(cb);
	else
	{
		NODE_CHUYENBAY* q = cb.Head;
		while (q->Next != p)
			q = q->Next;
		return Delete_After(cb, q);
	}
}

void Display4(int x, int y, int sove, Flight cb, bool ThongKe){ // khung trang tri ve may bay
	int row = (sove - 1) / 20 + 1;
	int width = 6 * 20 + 3;
	int vertical = row * 3 + 4;
	int center = width / 2 - 3;
	TextColor(11);
	gotoxy(x, y); cout << char(201); // moc phai
	for (int i = 1; i < center; i++){
		gotoxy(x + i, y); cout << char(205); // duong thang ngang
	}
	cout << "AIRPLANE";
	for (int i = center + 8; i < width; i++){
		gotoxy(x + i, y); cout << char(205); // duong thang ngang
	}
	cout << char(187); // moc trai
	for (int i = 1; i < vertical; i ++){
		gotoxy(x, y + i); cout << char(186); // cot thang
		gotoxy(x + width, y + i); cout << char(186); // cot thang
	}
	gotoxy(x, y + vertical - 1); cout << char(200);
	for (int i = 1; i < width; i++){
		gotoxy(x + i, y + vertical - 1); cout << char(205); // duong thang ngang
	}
	cout << char(188);
	
	setColor(14, 3);
	if (ThongKe == false){
	gotoxy(x + 56, y + vertical + 2); cout << "   UP/DOWN  ";
	gotoxy(x + 56, y + vertical + 3); cout << " LEFT/RIGHT ";
	gotoxy(x + 56, y + vertical + 4); cout << "   is move  ";
	gotoxy(x + 84, y + vertical + 2); cout << "         ";
	gotoxy(x + 84, y + vertical + 3); cout << "  ENTER  ";
	gotoxy(x + 84, y + vertical + 4); cout << "         ";
	}
	gotoxy(x + 109, y + vertical + 2); cout << "         ";
	gotoxy(x + 109, y + vertical + 3); cout << "   ECS   ";
	gotoxy(x + 109, y + vertical + 4); cout << "         ";
	setColor(11, 0);
	BoxTicket(x + 5, y + vertical + 3, 0, 1); gotoxy(x + 8, y + vertical + 3); cout << " Co nguoi dat";
	gotoxy(42, y + vertical + 2); cout << "So Ghe Da Dat : " << cb.SoVeDaBan;
	gotoxy(42, y + vertical + 4); cout << "So Ghe Con Trong : " << cb.SoVe - cb.SoVeDaBan;
}

void GiaoDienDatVe(Flight cb, bool ThongKe)
{
	int x = X_MENU_TICKET;
	int y = Y_MENU_TICKET;
	int n = cb.SoVe;
	Display4(x - 3, y, n, cb, ThongKe);
	for (int i = 1; i <= n; i++)
	{
		BoxTicket(x + 1, y + 3, i, cb.DanhSachVe[i - 1].tinhTrang);
		x += 6;
		if (i % 20 == 0)
		{
			y += 3;
			x = X_MENU_TICKET;
		}
	}
}

void ChuyenKhungSoVe(int ThuTu, int preColor)
{
	int current = ThuTu;
	int column = (current - 1) % 20;
	int row = (current - 1) / 20;

	SetBGColor(7);
	gotoxy(14 + (column + 1) * 6, (row + 1) * 3 + 4);
	TextColor(14);
	cout << setw(3) << setfill('0') << current;
	//TextColor(11);

	column = (vitriTruocDoTK - 1) % 20;
	row = (vitriTruocDoTK - 1) / 20;

	if (preColor == 0) preColor = 0;
	else preColor = 7;
	SetBGColor(preColor);
	gotoxy(14 + (column + 1) * 6, (row + 1) * 3 + 4);
	cout << setw(3) << setfill('0') << vitriTruocDoTK;

	vitriTruocDoTK = current;
}

int ChooseTicket(Flight cb){
	ShowCur(false);
	setColor(15, 6);
	gotoxy(X_TITLE + 9, Y_TITLE); cout << " CHON GHE MUON DAT";
	setColor(11, 0);
	vitriHienTaiTK = vitriTruocDoTK = 1;
	GiaoDienDatVe(cb, false);
	int keyboard_read = 0;
	int PASS = 1;
	// danh dau ô màu vào vi tri dau tien
	SetBGColor(7);
	gotoxy(20, 7);
	TextColor(14);
	cout << setw(3) << setfill('0') << 1;
	TextColor(11);
	while (PASS)
	{
		keyboard_read = getch();
		if (keyboard_read == 0)
			keyboard_read = getch();
		switch (keyboard_read)
		{
		case KEY_DOWN: //key down
			if (vitriHienTaiTK + 20 <= cb.SoVe)
			{
				vitriHienTaiTK = vitriHienTaiTK + 20;
				ChuyenKhungSoVe(vitriHienTaiTK, cb.DanhSachVe[vitriTruocDoTK - 1].tinhTrang);
			}
			break;
		case KEY_UP: //key up
			if (vitriHienTaiTK - 20 >= 1)
			{
				vitriHienTaiTK = vitriHienTaiTK - 20;
				ChuyenKhungSoVe(vitriHienTaiTK, cb.DanhSachVe[vitriTruocDoTK - 1].tinhTrang);
			}
			break;
		case KEY_LEFT: //left
			if (vitriHienTaiTK > 1)
			{
				vitriHienTaiTK--;
				ChuyenKhungSoVe(vitriHienTaiTK, cb.DanhSachVe[vitriTruocDoTK - 1].tinhTrang);
			}
			break;
		case KEY_RIGHT: //right
			if (vitriHienTaiTK < cb.SoVe)
			{
				vitriHienTaiTK++;
				ChuyenKhungSoVe(vitriHienTaiTK, cb.DanhSachVe[vitriTruocDoTK - 1].tinhTrang);
			}
			break;
		case ESC: 
			SetBGColor(0);
			return -1;
			break;

		case ENTER: //enter
			ShowCur(true);
			SetBGColor(0);
			PASS = 0;
			return vitriHienTaiTK;
			break;
		}
	}
	return 0;
}

void ThayDoiTrangThaiChuyenBay(listFlight cb){
	for (NODE_CHUYENBAY* p = cb.Head; p != NULL; p = p->Next)
		if (!KiemTraNgayThangCoHopLe(p->DataFlight.Ngaykhoihanh)) p->DataFlight.TrangThai = TT_HOANTAT;
}

void XuatFlight(Flight fl, int locate){
	gotoxy(toadoxGiaoDien[0] + 1, Y_DISPLAY + 3 + locate); cout << fl.SoHieu;
	gotoxy(toadoxGiaoDien[1] + 1, Y_DISPLAY + 3 + locate); cout << fl.id;
	gotoxy(toadoxGiaoDien[2] , Y_DISPLAY + 3 + locate); OutputDateTime(fl.Ngaykhoihanh);
	gotoxy(toadoxGiaoDien[3] + 1, Y_DISPLAY + 3 + locate); cout << fl.SanBayden;
	gotoxy(toadoxGiaoDien[4] + 1, Y_DISPLAY + 3 + locate);
	switch(fl.TrangThai){
		case 0: cout << "Da huy";
			break;
		case 1: cout << "Con ve";
			break;
		case 2: cout << "Het ve";
			break;
		case 3: cout << "Hoan tat";
			break;
		default:
			break;
	}
	gotoxy(toadoxGiaoDien[5] + 1, Y_DISPLAY + 3 + locate); cout << fl.SoVe;
}

void XuatSoHieuCB(listFlight cb, int firstOrdinal){
	int temp = -1;
	for (int i = firstOrdinal; i < SoCB; i++){ // gia tri cua SoCB co duoc sau khi goi ham FindFlightTheoCMND
		temp++;
		if (temp < SOLUONGMOITRANG2) {
			NODE_CHUYENBAY* p = FindFlightTheoThuTu(cb, arrSTTChuyenBay[i]);
			gotoxy(toadoxGiaoDien2[0] + 1, Y_DISPLAY + 8 + temp * 2);
			cout << p->DataFlight.id;
		}
	}
}

void XuatThongTinCB(listFlight f, int SoTTChuyenBay, int SoTT){
	NODE_CHUYENBAY* p = FindFlightTheoThuTu(f, SoTTChuyenBay);
	
	gotoxy(toadoxGiaoDien2[1] + 18, Y_DISPLAY + 8 + 1 * 2); cout << "                      ";
	gotoxy(toadoxGiaoDien2[1] + 18, Y_DISPLAY + 8 + 2 * 2); cout << "                      ";
	gotoxy(toadoxGiaoDien2[1] + 18, Y_DISPLAY + 8 + 3 * 2); cout << "               ";
	gotoxy(toadoxGiaoDien2[1] + 18, Y_DISPLAY + 8 + 4 * 2); cout << "               ";
	gotoxy(toadoxGiaoDien2[1] + 18, Y_DISPLAY + 8 + 5 * 2); cout << "               ";
	gotoxy(toadoxGiaoDien2[1] + 18, Y_DISPLAY + 8 + 0 * 2); cout << p->DataFlight.SoHieu;
	gotoxy(toadoxGiaoDien2[1] + 18, Y_DISPLAY + 8 + 1 * 2); OutputDateTime(p->DataFlight.Ngaykhoihanh);
	gotoxy(toadoxGiaoDien2[1] + 18, Y_DISPLAY + 8 + 2 * 2); cout << p->DataFlight.SanBayden;
	gotoxy(toadoxGiaoDien2[1] + 18, Y_DISPLAY + 8 + 3 * 2);
	switch(p->DataFlight.TrangThai){
		case 0: cout << "Da huy";
			break;
		case 1: cout << "Con ve";
			break;
		case 2: cout << "Het ve"; 
			break;
		case 3: cout << "Hoan tat";
			break;
		default:
			break;
	}
	gotoxy(toadoxGiaoDien2[1] + 18, Y_DISPLAY + 8 + 4 * 2); cout << p->DataFlight.SoVe;
	gotoxy(toadoxGiaoDien2[1] + 18, Y_DISPLAY + 8 + 5 * 2); cout << arrSoVe[SoTT];
}

//void XuatListFlight(listFlight cb){
//	if (cb.Head == NULL && cb.Tail == NULL) return;
//	int temp = -1;
//	ThayDoiTrangThaiChuyenBay(cb);
//	for (NODE_CHUYENBAY* p = cb.Head; p != NULL; p = p->Next){
//		temp++;
//		XuatFlight(p->DataFlight, temp);
//		}
//}

void ThietLapMauSoHieuCB(Flight cb, int ThuTu){
	SetBGColor(7);
	gotoxy(toadoxGiaoDien2[0] + 1, Y_DISPLAY + 8 + (ThuTu % SOLUONGMOITRANG2 ) * 2); cout << cb.id;
	SetBGColor(0);
}

void ChuyenDoiMauSoHieuCB(listFlight cb, int ThuTu, Flight CBmoi, Flight CBCu){
	int current = ThuTu;
	XuatThongTinCB(cb, arrSTTChuyenBay[current], current);
	ThietLapMauSoHieuCB(CBmoi, current);
	gotoxy(toadoxGiaoDien2[0] + 1, Y_DISPLAY + 8 + (vitriTruocDoCBDel % SOLUONGMOITRANG2) * 2); cout << CBCu.id;
	vitriTruocDoCBDel = current;
}

void HuongDan(){
	setColor(14, 3);
	gotoxy(116, 10); cout << "  UP/DOWN  ";
	gotoxy(116, 13); cout << "   LEFT    ";
	gotoxy(116, 14); cout << "   RIGHT   ";
	gotoxy(116, 17); cout << "           ";
	gotoxy(116, 18); cout << "   ENTER   ";
	gotoxy(116, 19); cout << "           ";
	gotoxy(116, 22); cout << "           ";
	gotoxy(116, 23); cout << "    ESC    ";
	gotoxy(116, 24); cout << "           ";
	setColor(11, 0);
	gotoxy(129, 10); cout << "len/xuong";
	gotoxy(129, 13); cout << "chuyen trang";
	gotoxy(129, 18); cout << "chon ve de huy";
	gotoxy(129, 23); cout << "thoat";
}

void ChuyenTrangDelete(listFlight dscb)
{
	system("cls");
	setColor(14, 3);
	gotoxy(X_TITLE, Y_TITLE); cout << " CHUYEN BAY HANH KHACH DA DAT VE ";
	setColor(11, 0);
	HuongDan();
	Display2(tpGiaodienThongTinVe, tpGiaodienCB, sizeof(tpGiaodienThongTinVe) / sizeof(string));
	vitriHienTaiCBDel = (trangHientaiCBDel - 1) * SOLUONGMOITRANG2;
	vitriTruocDoCBDel = (trangHientaiCBDel - 1) * SOLUONGMOITRANG2;
}

int SoTTVe;
NODE_CHUYENBAY* ChooseFlightDelete(listFlight cb){
	int keyboard_read = 0;
	ShowCur(false);
	trangHientaiCBDel = 1;
	vitriHienTaiCBDel = (trangHientaiCBDel - 1) * SOLUONGMOITRANG2; // vi tri trong arr chuyen bay, arr so ve
	vitriTruocDoCBDel = (trangHientaiCBDel - 1) * SOLUONGMOITRANG2;
	tongsoTrangCBDel = ((SoCB - 1) / SOLUONGMOITRANG2) + 1;
	
	NODE_CHUYENBAY* newNodeFlightDel = FindFlightTheoThuTu(cb, arrSTTChuyenBay[vitriHienTaiCBDel]);
	NODE_CHUYENBAY* oldNodeFilghtDel = NULL;
	
	XuatSoHieuCB(cb, 0);
	XuatThongTinCB(cb, arrSTTChuyenBay[vitriHienTaiCBDel], vitriHienTaiCBDel);
	ThietLapMauSoHieuCB(newNodeFlightDel->DataFlight, vitriHienTaiCBDel);
	HuongDan();
	while (true)
	{
		keyboard_read = getch();
		if (keyboard_read == 0)
			keyboard_read = getch();
		switch (keyboard_read)
		{
		case KEY_UP:
			if (vitriHienTaiCBDel % SOLUONGMOITRANG2 > 0)
			{
				vitriHienTaiCBDel = vitriHienTaiCBDel - 1;
				oldNodeFilghtDel = newNodeFlightDel;
				newNodeFlightDel = FindFlightTheoThuTu(cb, arrSTTChuyenBay[vitriHienTaiCBDel]);
				ChuyenDoiMauSoHieuCB(cb, vitriHienTaiCBDel, newNodeFlightDel->DataFlight, oldNodeFilghtDel->DataFlight);
			}
			break;
		case KEY_DOWN:
			if (vitriHienTaiCBDel % SOLUONGMOITRANG2 < SOLUONGMOITRANG2 - 1 && vitriHienTaiCBDel != SoCB - 1) 
			{
				vitriHienTaiCBDel = vitriHienTaiCBDel + 1;
				oldNodeFilghtDel = newNodeFlightDel;
				newNodeFlightDel = FindFlightTheoThuTu(cb, arrSTTChuyenBay[vitriHienTaiCBDel]);
				ChuyenDoiMauSoHieuCB(cb, vitriHienTaiCBDel, newNodeFlightDel->DataFlight, oldNodeFilghtDel->DataFlight);
			}
			break;
		
		case KEY_RIGHT:
			if (trangHientaiCBDel < tongsoTrangCBDel)
			{
				trangHientaiCBDel++;
				ChuyenTrangDelete(cb);
				XuatSoHieuCB(cb, (trangHientaiCBDel - 1) * SOLUONGMOITRANG2);
				XuatThongTinCB(cb, arrSTTChuyenBay[vitriHienTaiCBDel], vitriHienTaiCBDel);
				newNodeFlightDel = FindFlightTheoThuTu(cb, arrSTTChuyenBay[vitriHienTaiCBDel]);
				ThietLapMauSoHieuCB(newNodeFlightDel->DataFlight, vitriHienTaiCBDel);
			}
			break;
		case KEY_LEFT:
			if (trangHientaiCBDel > 1)
			{
				trangHientaiCBDel--;
				ChuyenTrangDelete(cb);
				XuatSoHieuCB(cb, (trangHientaiCBDel - 1) * SOLUONGMOITRANG2);
				XuatThongTinCB(cb, arrSTTChuyenBay[vitriHienTaiCBDel], vitriHienTaiCBDel);
				newNodeFlightDel = FindFlightTheoThuTu(cb, arrSTTChuyenBay[vitriHienTaiCBDel]);
				ThietLapMauSoHieuCB(newNodeFlightDel->DataFlight, vitriHienTaiCBDel);
			}
			break;
		case ENTER:  //enter
			ShowCur(true);
			SoTTVe = vitriHienTaiCBDel;
			return newNodeFlightDel;
			break;
		case ESC:
			return NULL; 
			break;
		}//end switch  read key
	}
}

void XuatListFlightTheoTungTrang(listFlight cb, int firstOrdinal){
	if (cb.Head == NULL && cb.Tail == NULL) return;
	int count = -1;
	ThayDoiTrangThaiChuyenBay(cb);
	for (NODE_CHUYENBAY* p = cb.Head; p != NULL; p = p->Next){
		count++;
		if (count == firstOrdinal){
			int i = -1;
			while (p != NULL && i < SOLUONGMOITRANG - 1){
				XuatFlight(p->DataFlight, (++i) * 2);
				p = p->Next;
			}
			break;
		}
	}
	gotoxy(X_PAGE, Y_PAGE - 2);
	cout << "Trang" << trangHientaiCB << "/" << tongsoTrangCB;
	return;
}

bool KiemTraDuLieuChuyenBayCoRong(Flight fl){
	if (strlen(fl.SoHieu) == 0) return true;
	if (strlen(fl.id) == 0) return true;
	if (strlen(fl.SanBayden) == 0) return true;
	if (fl.SoVe <= 0) return true;
	return false;
}

bool KiemTraNgayThangCuaCB(Flight fl, listFlight cb) {
	if (cb.Head == NULL) return NULL;
	for (NODE_CHUYENBAY *p = cb.Head; p != NULL; p = p->Next) {
		if (stricmp(p->DataFlight.SoHieu, fl.SoHieu) == 0 && (stricmp(p->DataFlight.id, fl.id) > 0 || stricmp(p->DataFlight.id, fl.id) < 0))
			if (p->DataFlight.Ngaykhoihanh.ngay == fl.Ngaykhoihanh.ngay && p->DataFlight.Ngaykhoihanh.thang == fl.Ngaykhoihanh.thang && p->DataFlight.Ngaykhoihanh.nam == fl.Ngaykhoihanh.nam)
			{
				int a(0), b(0), temp(0);
				a = fl.Ngaykhoihanh.gio * 60 + fl.Ngaykhoihanh.phut;
				b = p->DataFlight.Ngaykhoihanh.gio * 60 + p->DataFlight.Ngaykhoihanh.phut;
				temp = a - b;
				if (abs(temp) <= 180) return true;
			}
	}
	return false;
}

void InputFlight(AirPlanes mb, listFlight &cb, Flight &fl, bool ChinhSua = false){
	ShowCur(true);
	int ordinal = 1;
	bool isMoveUp = false; // bien nay dung de xac dinh xem nguoi dung co bam phím key_up không?
	bool isSave = false;
	bool idIsExist = false; // xác dinh xem id có ton tai chua? neu co thì moi nguoi dung nhap lai
	//bool idMBIsExist = false;
	char idMB[15]; // id may bay
	string id; // so hieu
	DateTime dt;
	string destiny;
	int stt = TT_CONVE, nTicket = 0;
	
	if(!ChinhSua){
		// chon may bay
		int choice = PickMB(mb);
		strcpy(idMB, mb.data[choice]->SoHieu);

		GiaoDienChinhSua(tpGiaodienCB, sizeof(tpGiaodienCB) / sizeof(string), 35);
		gotoxy(X_a + 20 + 15 , Y_a); cout << idMB;
	}
	
	gotoxy(X_ThongBao, Y_ThongBao + 1);
	cout << "F10 : Luu Ngay Va Gio";
	gotoxy(X_ThongBao - 4, Y_ThongBao + 2);
	cout << "Trang Thai: 0.Huy Chuyen 1.Con Ve";
	gotoxy(X_ThongBao + 8, Y_ThongBao + 3);
	cout << "2.Het Ve 3.Hoan Tat";
	
	if (ChinhSua){ // Neu nguoi dung muon chinh sua thi chuong trinh se chay dong if nay, con them chuyen bay moi thi se tu dong bo qua
		ordinal = 2;
		
		strcpy(idMB, fl.SoHieu);
		id = fl.id;
		dt = fl.Ngaykhoihanh;
		destiny = fl.SanBayden;
		stt = fl.TrangThai;
		nTicket = fl.SoVe;
		
		gotoxy(X_a + 20 + 12 + 2, Y_a + 6);
		cout << ":";
		gotoxy(X_a + 20 + 12 + 8, Y_a + 6);
		cout << "/";
		gotoxy(X_a + 20 + 12 + 11, Y_a + 6);
		cout << "/";
		
		gotoxy(X_a + 20 + 12 + 0 * 3, Y_a + 6);
		cout << dt.gio;
		gotoxy(X_a + 20 + 12 + 1 * 3, Y_a + 6);
		cout << dt.phut;
		gotoxy(X_a + 20 + 12 + 2 * 3, Y_a + 6);
		cout << dt.ngay;
		gotoxy(X_a + 20 + 12 + 3 * 3, Y_a + 6);
		cout << dt.thang;
		gotoxy(X_a + 20 + 12 + 4 * 3, Y_a + 6);
		cout << dt.nam;
		
		gotoxy(X_a + 35, Y_a + 0 * 3);
		cout << idMB;
		gotoxy(X_a + 35, Y_a + 1 * 3);
		cout << id;
		gotoxy(X_a + 35, Y_a + 3 * 3);
		cout << destiny;
		gotoxy(X_a + 35, Y_a + 4 * 3);
		cout << stt;
		gotoxy(X_a + 35, Y_a + 5 * 3);
		cout << nTicket;
	}
	while(true){ 
		switch(ordinal){
			case 1:
			{
				NhapHoacEditID(id, isMoveUp, ordinal, isSave, 15);
				if (ChinhSua && stricmp(id.c_str(), fl.id) == 0) break; 
				if (FindFlight(cb, (char *)id.c_str()) == NULL){ // tim kiem xem co chuyen bay ton tai chua, c_str la ham chuyen string -> char*
					idIsExist = false;
					break;
				}
				idIsExist = true;
				break;
			}
			case 2:
			{
				InputDateTime(dt, isSave);
				break;
			}
			case 3:
			{
				NhapHoacEditTen(destiny, isMoveUp, ordinal, isSave, 15);
				break;
			}
			case 4:
			{
				NhapHoacEditSo(stt, isMoveUp, ordinal, isSave, 15, 4);
				break;
			}
			case 5:
			{
//				gotoxy(X_a + 20 + 15, ordinal * 3 + Y_a);
//				for (int i = 0; i < mb.n; i++)
//					if (stricmp(idMB.c_str(), mb.data[i]->SoHieu) == 0){
//						nTicket = mb.data[i]->SoCho;
//						cout << nTicket;
//						break;
//					}
//				gotoxy(X_a + 20 + 15, ordinal * 3 + Y_a);
//				cout << mb.data[0]->SoHieu;
//				int vitri = FindAirplane(mb, "fu312a");
//				cout << vitri;
				NhapHoacEditSo(nTicket, isMoveUp, ordinal, isSave, 15, 300);
				break;
			}
		}
		if(!ChinhSua){
		if (isMoveUp) // neu nguoi dung di chuyen con tro chuot len 
		{
			if (ordinal == 1) // neu con tro chuot dang o tren hang dau tien, thi khong di chuyen len chi co the di chuyen xuong
				isMoveUp = false; //block move up
			ordinal--;
		}
		else
		{
			if (ordinal == 5) // neu con tro chuot dang o duoi cung, thi khong the di xuong duoc nua, chi co the di len
				isMoveUp = true; //block move down
			ordinal++;
		}
		//--end move
		}
		
		if (isSave){ // F10
			strcpy(fl.SoHieu, idMB);
			strcpy(fl.id, id.c_str());
			fl.Ngaykhoihanh = dt;
			strcpy(fl.SanBayden, destiny.c_str());
			fl.TrangThai = stt;
			fl.SoVe = nTicket;
			int vitri = SearchSH(mb, fl.SoHieu);
			
			gotoxy(X_ThongBao, Y_ThongBao - 1);
			cout << setw(80) << setfill(' ') << " ";
			gotoxy(X_ThongBao, Y_ThongBao);
			cout << setw(50) << setfill(' ') << " ";
			if (!KiemTraNgayThangCoHopLe(fl.Ngaykhoihanh)){ // ngay thang phai bang hien tai hoac lon hon ngay thang cua qua khu
				gotoxy(X_ThongBao, Y_ThongBao);
				cout << "Ngay Gio Khong Hop Le !";
			}
			else if (KiemTraNgayThangCuaCB(fl, cb)){
				gotoxy(X_ThongBao, Y_ThongBao - 1);
				cout << "Cac chuyen bay cua 1 may bay";
				gotoxy(X_ThongBao, Y_ThongBao);
				cout << "phai cach nhau dung 3 tieng !";
			}
			else if (KiemTraDuLieuChuyenBayCoRong(fl)){
				gotoxy(X_ThongBao, Y_ThongBao);
				cout << "Phai Dien Day Du Thong Tin. Khong duoc de trong !";
			}
			//else if (!idMBIsExist){
			//	gotoxy(X_ThongBao, Y_ThongBao);
			//	cout << "Khong ton tai so hieu may bay !";
			//}
			else if (idIsExist){
				gotoxy(X_ThongBao, Y_ThongBao);
				cout << "Ma CB Khong Duoc Trung !";
			}
			else if (fl.SoVe > mb.data[vitri]->SoCho || fl.SoVe <= 20){
				gotoxy(X_ThongBao, Y_ThongBao);
			cout << "So Ve Khong Hop Le !";
			}
			else {
				DinhDangSoHieu(fl.id);
				//DinhDangSoHieu(fl.SoHieu);
				DinhDangTen(fl.SanBayden);
				if (ChinhSua){ 
					NODE_CHUYENBAY* p = FindFlight(cb, fl.id);
					p->DataFlight = fl;
				}
				else ThemVaoCuoiList(cb, fl);
				tongsoTrangCB = ((cb.n - 1) / SOLUONGMOITRANG) + 1;
				DeleteMenuAdd();
				return;
			}
		isSave = false;
	}
	else isSave = false;
	}
	ShowCur(false);
}

void ThietLapMauChoTungDong(Flight cb, int ThuTu) // thiet lap thanh sáng màu cho tung` dong` cua chuyen bay
{
	SetBGColor(7);
	XuatFlight(cb, (ThuTu % SOLUONGMOITRANG) * 2);
	SetBGColor(0);
}

void ChuyenDoiTungDongChuyenBay(int ThuTu, Flight CbMoi, Flight CbCu) // chuyen thanh sáng lên hay xuông' 
{
	int current = ThuTu;
	ThietLapMauChoTungDong(CbMoi, current);
	XuatFlight(CbCu, (vitriTruocDoCB % SOLUONGMOITRANG) * 2);
	vitriTruocDoCB = current;
}

void ChuyenTrangChonChuyenBay(listFlight dscb)
{
	system("cls");
	Display(tpGiaodienCB, sizeof(tpGiaodienCB) / sizeof(string));
	vitriHienTaiCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	vitriTruocDoCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	TitleBangChon(tpMucLucCB);
}

NODE_CHUYENBAY* ChooseFlight(listFlight cb)
{
	int keyboard_read = 0;
	ShowCur(false);
	trangHientaiCB = 1;
	vitriHienTaiCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	vitriTruocDoCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	tongsoTrangCB = ((cb.n - 1) / SOLUONGMOITRANG) + 1;
	
	NODE_CHUYENBAY* newNodeFlight = FindFlightTheoThuTu(cb, vitriHienTaiCB);
	NODE_CHUYENBAY* oldNodeFilght = NULL;
	
	XuatListFlightTheoTungTrang(cb, (trangHientaiCB - 1) * SOLUONGMOITRANG);
	ThietLapMauChoTungDong(newNodeFlight->DataFlight, vitriHienTaiCB);
	while (true)
	{
		keyboard_read = _getch();
		if (keyboard_read == 0)
			keyboard_read = _getch();
		switch (keyboard_read)
		{
		case KEY_UP:
			if (vitriHienTaiCB % SOLUONGMOITRANG > 0)
			{
				vitriHienTaiCB = vitriHienTaiCB - 1;
				oldNodeFilght = newNodeFlight;
				for (newNodeFlight = cb.Head; newNodeFlight->Next != oldNodeFilght; newNodeFlight = newNodeFlight->Next);
				ChuyenDoiTungDongChuyenBay(vitriHienTaiCB, newNodeFlight->DataFlight, oldNodeFilght->DataFlight);
			}
			break;
		case KEY_DOWN:
			if (vitriHienTaiCB % SOLUONGMOITRANG < SOLUONGMOITRANG - 1 && newNodeFlight->Next != NULL) 
			{
				vitriHienTaiCB = vitriHienTaiCB + 1;
				oldNodeFilght = newNodeFlight;
				newNodeFlight = newNodeFlight->Next;
				ChuyenDoiTungDongChuyenBay(vitriHienTaiCB, newNodeFlight->DataFlight, oldNodeFilght->DataFlight);
			}
			break;
		
		case KEY_RIGHT:
			if (trangHientaiCB < tongsoTrangCB)
			{
				trangHientaiCB++;
				ChuyenTrangChonChuyenBay(cb);
				XuatListFlightTheoTungTrang(cb, (trangHientaiCB - 1) * SOLUONGMOITRANG);
				newNodeFlight = FindFlightTheoThuTu(cb, vitriHienTaiCB);
				ThietLapMauChoTungDong(newNodeFlight->DataFlight, vitriHienTaiCB);
			}
			break;
		case KEY_LEFT:
			if (trangHientaiCB > 1)
			{
				trangHientaiCB--;	
				ChuyenTrangChonChuyenBay(cb);
				XuatListFlightTheoTungTrang(cb, (trangHientaiCB - 1) * SOLUONGMOITRANG);
				newNodeFlight = FindFlightTheoThuTu(cb, vitriHienTaiCB);
				ThietLapMauChoTungDong(newNodeFlight->DataFlight, vitriHienTaiCB);
			}
			break;
		case ENTER:  //enter
			ShowCur(true);
			return newNodeFlight;
			break;
		case ESC: 
			return NULL; 
			break;
		}//end switch  read key
	}
}

void ChuyenTrangQLyChuyenBay(listFlight cb){
	system("cls");
	setColor(15, 3);
	gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY CHUYEN BAY";
	setColor(11, 0);
	XuatListFlightTheoTungTrang(cb, (trangHientaiCB - 1) * SOLUONGMOITRANG);
	Display(tpGiaodienCB, sizeof(tpGiaodienCB) / sizeof(string));
	TitleBangChon(tpMucLucCB);
}

void MenuQlyChuyenBay(listFlight &cb, AirPlanes mb){
	ShowCur(false);
backMenu:
	system("cls");
	trangHientaiCB = 1;
	tongsoTrangCB = ((cb.n - 1) / SOLUONGMOITRANG) + 1;
	XuatListFlightTheoTungTrang(cb, 0);
	Display(tpGiaodienCB, sizeof(tpGiaodienCB) / sizeof(string));
	gotoxy(toadoxGiaoDien[0] + 20, Y_DISPLAY + 39);
	setColor(15, 6);
	cout <<  " F2: Them F3: Huy F4: Hieu Chinh F5: Xoa F10: Save ";
	gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY CAC CHUYEN BAY ";
	gotoxy(X_ThongBao + 30, Y_ThongBao + 3); cout << "ESC : thoat";
	setColor(11, 0);
	int key;
	while(true){
		while(kbhit()){
			key = getch();
			if (key == 0 || key == 224){
				key = getch();
				if (key == KEY_F2){  // F2
					Flight fl;
					gotoxy(24, Y_ThongBao + 3); cout << setw(65) << " ";
					gotoxy(X_ThongBao + 30, Y_ThongBao + 3); cout << "           ";
					InputFlight(mb, cb, fl, false);
					tongsoTrangCB = ((cb.n - 1) / SOLUONGMOITRANG) + 1;
					ChuyenTrangQLyChuyenBay(cb);
					DeleteNotify();
					gotoxy(X_ThongBao, Y_ThongBao); cout << "Them thanh cong !";
				}
				
				else if (key == KEY_F3){ // F3
					gotoxy(24, Y_ThongBao + 3); cout << setw(65) << " ";
					NODE_CHUYENBAY* fl = ChooseFlight(cb);
					if (fl == NULL) goto backMenu;
					gotoxy(X_ThongBao, Y_ThongBao); cout << "Enter neu chac chan huy !";
					key = getch();
					if (key == ENTER){
						if (fl->DataFlight.SoVeDaBan != 0){
							gotoxy(X_ThongBao, Y_ThongBao); cout << "Da co hanh khach dat ve. Khong huy duoc !";
							getch();
							goto backMenu;
						}
						else {
							fl->DataFlight.TrangThai = TT_HUYCHUYEN;
							system("cls");
							Display(tpGiaodienCB, sizeof(tpGiaodienCB) / sizeof(string));
							XuatListFlightTheoTungTrang(cb, (trangHientaiCB - 1) * SOLUONGMOITRANG);
							TitleBangChon(tpMucLucCB);
							gotoxy(X_ThongBao, Y_ThongBao); cout << "Huy thanh cong !";
						}
					}
					else goto backMenu;
				}
				
				else if (key == KEY_F4){
					gotoxy(24, Y_ThongBao + 3); cout << setw(65) << " ";
					NODE_CHUYENBAY* fl;
					do{
						fl = ChooseFlight(cb);
						if (fl == NULL) goto backMenu;
						if (fl->DataFlight.TrangThai == TT_HUYCHUYEN || fl->DataFlight.TrangThai == TT_HOANTAT){
							gotoxy(X_ThongBao, Y_ThongBao); cout << setw(41) << setfill(' ');
							gotoxy(X_ThongBao, Y_ThongBao);
							cout << "Vui long chon chuyen khac !";
							getch();
						}
						gotoxy(X_ThongBao, Y_ThongBao); cout << "                                             ";
					} while (fl->DataFlight.TrangThai == TT_HOANTAT || fl->DataFlight.TrangThai == TT_HUYCHUYEN);
					
					GiaoDienChinhSua(tpGiaodienCB, sizeof(tpGiaodienCB) / sizeof(string), 35);
					InputFlight(mb, cb, fl->DataFlight, true);
					system("cls");
					Display(tpGiaodienCB, sizeof(tpGiaodienCB) / sizeof(string));
					XuatListFlightTheoTungTrang(cb, (trangHientaiCB - 1) * SOLUONGMOITRANG);
					TitleBangChon(tpMucLucCB);
					DeleteNotify();
					gotoxy(X_ThongBao, Y_ThongBao); cout << "Sua thanh cong !";
				}
				
				else if (key == KEY_F5){ // F5
					gotoxy(24, Y_ThongBao + 3); cout << setw(65) << " ";
					NODE_CHUYENBAY* fl = ChooseFlight(cb);
					if (fl == NULL) goto backMenu;
					gotoxy(X_ThongBao, Y_ThongBao); cout << "Enter neu chac chan xoa !";
					key = getch();
					if (key == ENTER){
						//if (fl->DataFlight.SoVeDaBan != 0){
						//	gotoxy(X_ThongBao, Y_ThongBao); cout << "Da co hanh khach dat ve. Khong huy duoc !";
						//	getch();
						//	goto backMenu;
						//}
						if (DeleteFlight_Id(cb, fl->DataFlight)){
							tongsoTrangCB = ((cb.n - 1) / SOLUONGMOITRANG) + 1;
							if (cb.n % SOLUONGMOITRANG == 0) trangHientaiCB--;
							ChuyenTrangQLyChuyenBay(cb);
							TitleBangChon(tpMucLucCB);
							gotoxy(X_ThongBao, Y_ThongBao); cout << "Xoa thanh cong !";
						}
					}
					else goto backMenu;
				}
				
				else if (key == KEY_RIGHT && trangHientaiCB < tongsoTrangCB){
					trangHientaiCB++;
					ChuyenTrangQLyChuyenBay(cb);
				}
				
				else if (key == KEY_LEFT && trangHientaiCB > 1){
					trangHientaiCB--;
					ChuyenTrangQLyChuyenBay(cb);
				}
			}
			else if (key == ESC)
					return;
		}
	}
}


//========================HANH KHACH==========================
struct HanhKhach {
	char cmnd[10];
	char Ho[20], Ten[20];
	int phai = 1; // 1 la nam, 2 la nu
};

struct nodeHanhKhach {
	HanhKhach data;
	struct nodeHanhKhach *left;
	struct nodeHanhKhach *right;
};
typedef struct nodeHanhKhach NODE_HANHKHACH;
typedef NODE_HANHKHACH* treeHanhKhach; // su dung treeHanhKhach cho de nhin, thay vi phai NODE_HANHKHACH*

void Initialize(treeHanhKhach &root) { // khoi tao cay hanh khach
	SoHanhKhach = -1;
	root = NULL;
}

void Insert_HanhKhach(treeHanhKhach &t, HanhKhach hk) {
	if (t == NULL) { // cay rong
		NODE_HANHKHACH *point = new NODE_HANHKHACH; // khoi tao 1 node de them vao cay
		point->data = hk;
		point->left = NULL;
		point->right = NULL;
		t = point; // node point chinh la nut goc
		int temp;
		temp = atoi(hk.cmnd);
		arrIdHanhKhach[++SoHanhKhach] = temp;
	}
	else { // cay co ton tai phan tu
		if (strcmp(hk.cmnd, t->data.cmnd) < 0)
			Insert_HanhKhach(t->left, hk);
		else if (strcmp(hk.cmnd, t->data.cmnd) > 0)
			Insert_HanhKhach(t->right, hk);
	}
}

NODE_HANHKHACH* FindPassenger(treeHanhKhach root, unsigned int cmndHanhKhach)
{
	if (root != NULL)
	{
		NODE_HANHKHACH* p = root;
		char CharCMND[13];
		itoa(cmndHanhKhach, CharCMND, 10);
		while (p != NULL)
		{
			if (strcmp(p->data.cmnd, CharCMND) == 0)
				return p;
			else if (strcmp(p->data.cmnd, CharCMND) > 0)
				p = p->left;
			else
				p = p->right;
		}
	}
	return NULL;
}

void TimNodeTheMang(treeHanhKhach &x, treeHanhKhach &y){
	if (y->left != NULL)
		TimNodeTheMang(x, y->left);
	else {
		x->data = y->data;
		x = y; // cho node x tro den y de sau nay xoa
		y = y->right;
	}
}

bool Delete_Passenger(treeHanhKhach &t, HanhKhach hk){
	if (t == NULL) return false;
	else {
		if (strcmp(hk.cmnd, t->data.cmnd) > 0)	
			Delete_Passenger(t->right, hk);
		else if (strcmp(hk.cmnd, t->data.cmnd) < 0)
			Delete_Passenger(t->left, hk);
		else {
			NODE_HANHKHACH *temp = t;
			if (t->left == NULL)
				t = t->right;
			else if (t->right == NULL)
				t = t->left;
			else {
				TimNodeTheMang(temp, t->right);
			}
			delete temp;
			return true;
		}
	}
}

void Quick_Sort(int head, int tail, unsigned int a[]){
	int temp;
	int x = a[(head + tail) / 2];
	int i = head, j = tail;
	do {
		while (a[i] < x) i++;
		while (a[j] > x) j--;
		if(i <= j){
			if (i < j) {
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
			i++; j--;
		}
	} while(i <= j);
	if (head < j) Quick_Sort(head, j, a);
	if (tail > i) Quick_Sort(i, tail, a);
}

void XuatHanhKhach(HanhKhach hk, int locate){
	DeleteOldData(sizeof(tpGiaodienHK) / sizeof(string), locate);
	gotoxy(toadoxGiaoDien[0] + 1, Y_DISPLAY + 3 + locate); cout << hk.cmnd;
	gotoxy(toadoxGiaoDien[1] + 1, Y_DISPLAY + 3 + locate); cout << hk.Ho;
	gotoxy(toadoxGiaoDien[2] + 1, Y_DISPLAY + 3 + locate); cout << hk.Ten;
	gotoxy(toadoxGiaoDien[3] + 1, Y_DISPLAY + 3 + locate);
	if (hk.phai == 1)cout << "Nam";
	else cout << "Nu";
}

void XuatHanhKhach1ChuyenBay(HanhKhach hk, int SoTT){
	gotoxy(toadoxGiaoDien3[2], Y_DISPLAY + 3 + SoTT * 2); cout << hk.cmnd;
	gotoxy(toadoxGiaoDien3[3], Y_DISPLAY + 3 + SoTT * 2); cout << hk.Ho;
	gotoxy(toadoxGiaoDien3[3] + 7, Y_DISPLAY + 3 + SoTT * 2); cout << hk.Ten;
	gotoxy(toadoxGiaoDien3[4], Y_DISPLAY + 3 + SoTT * 2);
	if (hk.phai == 1)cout << "Nam";
	else cout << "Nu";
}

void XuatListPassengerTheoTungTrang(treeHanhKhach t, int thutuBatDau)
{
	for (int i = 0; i + thutuBatDau <= SoHanhKhach && i < SOLUONGMOITRANG; i++)
	{
		NODE_HANHKHACH* p = FindPassenger(t, arrIdHanhKhach[i + thutuBatDau]);
		XuatHanhKhach(p->data, i * 2);
	}
	gotoxy(X_PAGE, Y_PAGE - 2);
	cout << "Trang " << trangHientaiHK << "/" << tongsoTrangHK;
}

void ThietLapMauChoTungDongHK(HanhKhach hk, int ThuTu)
{
	SetBGColor(7);
	XuatHanhKhach(hk, ThuTu % SOLUONGMOITRANG);
	SetBGColor(0);
}

void ChuyenDoiTungDongHanhKhach(int ThuTu, HanhKhach HKmoi, HanhKhach HKcu)
{
	int current = ThuTu;
	SetBGColor(7);
	XuatHanhKhach(HKmoi, (current % SOLUONGMOITRANG) * 2);
	SetBGColor(0);
	XuatHanhKhach(HKcu, (vitriTruocDoHK % SOLUONGMOITRANG) * 2);
	vitriTruocDoHK = current;
}

void ChuyenTrangHanhKhach(treeHanhKhach t)
{
	vitriHienTaiHK = (trangHientaiHK - 1) * SOLUONGMOITRANG;
	vitriTruocDoHK = (trangHientaiHK - 1) * SOLUONGMOITRANG;
	system("cls");
	setColor(15, 6);
	gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY HANH KHACH ";
	gotoxy(X_ThongBao + 30, Y_ThongBao + 3); cout << "ESC : thoat";
	setColor(11, 0);
	Display(tpGiaodienHK, sizeof(tpGiaodienHK) / sizeof(string));
	DeleteNote(sizeof(tpGiaodienHK) / sizeof(string));
}

NODE_HANHKHACH* ChoosePassenger(treeHanhKhach &t)
{
	if (t == NULL) return NULL;
	ShowCur(false);
	int key;
	int keyboard_read = 0;
	int PASS = 1;
	Quick_Sort(0, SoHanhKhach, arrIdHanhKhach);
	Display(tpGiaodienHK, sizeof(tpGiaodienHK) / sizeof(string));
	trangHientaiHK = 1;
	vitriHienTaiHK = (trangHientaiHK - 1) * SOLUONGMOITRANG;
	vitriTruocDoHK = (trangHientaiHK - 1) * SOLUONGMOITRANG;
	NODE_HANHKHACH* newPassenger = FindPassenger(t, arrIdHanhKhach[0]);
	XuatListPassengerTheoTungTrang(t, 0);
	ThietLapMauChoTungDongHK(newPassenger->data, vitriHienTaiHK);
	NODE_HANHKHACH* oldPassenger = NULL;
	gotoxy(X_PAGE, Y_PAGE - 2);
	cout << "trang " << trangHientaiHK << "/" << tongsoTrangHK;
	setColor(15, 6); 
	gotoxy(X_ThongBao + 30, Y_ThongBao + 3); cout << "ESC : thoat";
	setColor(11, 0);
	while (PASS)
	{
		keyboard_read = getch();
		if (keyboard_read == 0)
			keyboard_read = getch();
		switch (keyboard_read){
		case KEY_UP:
			if (vitriHienTaiHK % SOLUONGMOITRANG > 0)
			{
				vitriHienTaiHK = vitriHienTaiHK - 1;
				oldPassenger = newPassenger;
				newPassenger = FindPassenger(t, arrIdHanhKhach[vitriHienTaiHK]);
				ChuyenDoiTungDongHanhKhach(vitriHienTaiHK, newPassenger->data, oldPassenger->data);
			}
			break;
		case KEY_DOWN:
			if (vitriHienTaiHK % SOLUONGMOITRANG < SOLUONGMOITRANG - 1 && vitriHienTaiHK < SoHanhKhach)
			{
				vitriHienTaiHK = vitriHienTaiHK + 1;
				oldPassenger = newPassenger;
				newPassenger = FindPassenger(t, arrIdHanhKhach[vitriHienTaiHK]);
				ChuyenDoiTungDongHanhKhach(vitriHienTaiHK, newPassenger->data, oldPassenger->data);
			}
			break;
		case KEY_RIGHT:
			if (trangHientaiHK < tongsoTrangHK)
			{
				trangHientaiHK++;
				ChuyenTrangHanhKhach(t);
				newPassenger = FindPassenger(t, arrIdHanhKhach[vitriHienTaiHK]);
				oldPassenger = newPassenger;
				XuatListPassengerTheoTungTrang(t, (trangHientaiHK - 1) * SOLUONGMOITRANG);
				ThietLapMauChoTungDongHK(newPassenger->data, vitriHienTaiHK);
			}
			break;
		case KEY_LEFT:
			if (trangHientaiHK > 1)
			{
				trangHientaiHK--;
				ChuyenTrangHanhKhach(t);
				newPassenger = FindPassenger(t, arrIdHanhKhach[vitriHienTaiHK]);
				oldPassenger = newPassenger;
				XuatListPassengerTheoTungTrang(t, (trangHientaiHK - 1) * SOLUONGMOITRANG);
				ThietLapMauChoTungDongHK(newPassenger->data, vitriHienTaiHK);
			}
			break;
		case ENTER:  //enter
			PASS = 0;
			ShowCur(true);
			return newPassenger;
			break;
		case ESC:
			ShowCur(true);
			return NULL;
			break;
		}
	}
}

void Create_Tree(treeHanhKhach &root) {
	HanhKhach hk;
	int temp;
	cout << "\nNhap so Hanh khach : ";
	cin >> temp;
	for (int i = 1; i <= temp; i++) {
		cout << "\nNhap cmnd cua Hanh Khach : ";
		cin >> hk.cmnd;
		while (strlen(hk.cmnd) != 9 && strlen(hk.cmnd) != 12) {
			cout << "\nMa cmnd khong hop le. Xin vui long nhap lai !";
			cout << "\nNhap cmnd cua Hanh Khach : ";
			cin >> hk.cmnd;
		}
		cout << "\nNhap Ho :";
		cin >> hk.Ho;
		cout << "\nNhap Ten : ";
		cin >> hk.Ten;
		cout << "\nPhai la : ";
		cin >> hk.phai;
		while (hk.phai != 2 && hk.phai != 1) {
			cout << "\nKhong hop le. Moi nhap lai !";
			cin >> hk.phai;
		}
		Insert_HanhKhach(root, hk);
	}
}

void InputPassenger(treeHanhKhach &t, HanhKhach &hk, bool daChinhSua = false){
	ShowCur(true);
	int TrinhTu = 0;
	bool isMoveUp = false;
	bool isSave = false;
	
	unsigned int cmnd;
	int IntCMND; // chuyen cmnd tu char sang int cho de dung
	string ho, ten;
	int phai = 0;
	bool DaCoCMND = false;
	gotoxy(X_ThongBao, Y_ThongBao + 1); cout << "1. Nam  2. Nu   F10. Luu";
	if (daChinhSua){
		IntCMND = atoi(hk.cmnd);
		cmnd = IntCMND;
		ho = hk.Ho;
		ten = hk.Ten;
		phai = hk.phai;
		
		gotoxy(X_a + 30, 0 * 3 + Y_a); cout << cmnd;
		gotoxy(X_a + 30, 1 * 3 + Y_a); cout << ho;
		gotoxy(X_a + 30, 2 * 3 + Y_a); cout << ten;
		gotoxy(X_a + 30, 3 * 3 + Y_a); cout << phai;
	}
	while(true){
		switch(TrinhTu){
			case 0: {
				if (daChinhSua) break;
				NhapHoacEditCMND(cmnd, isMoveUp, TrinhTu, isSave, 10);
				if(FindPassenger(t, cmnd) == NULL){
					DaCoCMND = false;
					break;
				}
				DaCoCMND = true;
				break;
			}
			case 1: {
				NhapHoacEditTen(ho, isMoveUp, TrinhTu, isSave, 10);
				break;
			}
			case 2: {
				NhapHoacEditTen(ten, isMoveUp, TrinhTu, isSave, 10);
				break;
			}
			case 3: {
				NhapHoacEditSo(phai, isMoveUp, TrinhTu, isSave, 10, 2);
				break;
			}
		}
			if (isMoveUp){
				if (TrinhTu == 0)
					isMoveUp = false;
				TrinhTu--;
			}
			else {
				if (TrinhTu == 4)
					isMoveUp = true;
				TrinhTu++;
			}
			if (isSave){
				gotoxy(X_ThongBao, Y_ThongBao); cout << setw(50) << setfill(' ') << " ";
				if (ho.empty() || ten.empty() || (int)log10(cmnd) + 1 == 0){
					gotoxy(X_ThongBao, Y_ThongBao);
					cout << "Phai Dien Day Du Thong Tin. Khong duoc de trong !";
				}
				else if ((int)log10(cmnd) + 1 != 9){
					gotoxy(X_ThongBao, Y_ThongBao);
					cout << "CMND khong hop le !";
				}
				else if (DaCoCMND){
					gotoxy(X_ThongBao, Y_ThongBao);
					cout << "CMND khong duoc trung !";
				}
				else {
					char CharCMND[13];
					itoa(cmnd, CharCMND, 10);
					strcpy(hk.cmnd, CharCMND);
					strcpy(hk.Ho, ho.c_str());
					strcpy(hk.Ten, ten.c_str());
					hk.phai = phai;
					
					DinhDangTen(hk.Ho);
					DinhDangTen(hk.Ten);
					if (daChinhSua) {
						NODE_HANHKHACH* p = FindPassenger(t, cmnd);
						p->data = hk;
					}
					else
						Insert_HanhKhach(t, hk);

					DeleteMenuAdd();
					gotoxy(X_ThongBao, Y_ThongBao + 1);
					cout << "						";
					return;
				}
				isSave = false;
		}
		else isSave = false;
	}
	ShowCur(false);
}

void MenuQlyHanhKhach(treeHanhKhach &t){
	ShowCur(false);
backMenu: 
	tongsoTrangHK = SoHanhKhach / SOLUONGMOITRANG + 1;
	trangHientaiHK = 1;
	Quick_Sort(0, SoHanhKhach, arrIdHanhKhach);
	
	XuatListPassengerTheoTungTrang(t, 0);
	Display(tpGiaodienHK, sizeof(tpGiaodienHK) / sizeof(string));
	setColor(15, 6);
	gotoxy(toadoxGiaoDien[0] + 20, Y_DISPLAY + 39);
	cout << " F2: Them F3: Huy F4: Hieu Chinh F10: Save ";
	gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY HANH KHACH ";
	gotoxy(X_ThongBao + 30, Y_ThongBao + 3); cout << "ESC : thoat";
	setColor(11, 0);
	int key;
	while(true){
		while(kbhit()){
			gotoxy(X_PAGE, Y_PAGE - 2);
			cout << "Trang " << trangHientaiHK << "/" << tongsoTrangHK;
			key = getch();
			if (key == 0 || key == 224)
			{
				key = getch();
				gotoxy(X_ThongBao, Y_ThongBao);
				cout << setw(35) << setfill(' ') << " ";
				if (key == KEY_F2) //f2
				{
					HanhKhach hk;
					gotoxy(20, Y_DISPLAY + 39); cout << setw(150) << " ";
					GiaoDienChinhSua(tpGiaodienHK, sizeof(tpGiaodienHK) / sizeof(string), 35);
					InputPassenger(t, hk, false);
					tongsoTrangHK = SoHanhKhach / SOLUONGMOITRANG + 1;
					trangHientaiHK = 1;
					system("cls");
					Display(tpGiaodienHK, sizeof(tpGiaodienHK) / sizeof(string));
					XuatListPassengerTheoTungTrang(t, (trangHientaiHK - 1) * SOLUONGMOITRANG);
					gotoxy(X_ThongBao, Y_ThongBao);
					cout << "Them thanh cong !";
					TitleBangChon(tpMucLucHK);
				}
				else if (key == KEY_F3) {// F3
					system("cls");
					setColor(15, 6);
					gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY HANH KHACH ";
					setColor(11, 0);
					NODE_HANHKHACH* b = ChoosePassenger(t);
					if (b == NULL) goto backMenu;
					//if (b->data.daDatVe)
					//{
					//	gotoxy(X_ThongBao, Y_ThongBao);
					//	cout << "Nguoi nay dang giu ve. K xoa duoc";
					//	key = getch();
					//	DeleteNotify();
					//	goto backMenu;
					//}
					gotoxy(X_ThongBao, Y_ThongBao); cout << "Enter neu chac chan xoa !";
					key = getch();
					if (key == ENTER){
						system("cls");
						Display(tpGiaodienHK, sizeof(tpGiaodienHK) / sizeof(string));
						int IntCMND;
						IntCMND = atoi(b->data.cmnd);
						for (int i = 0; i <= SoHanhKhach; i++)
						{
							if (arrIdHanhKhach[i] == IntCMND)
							{
								for (int j = i; j < SoHanhKhach; j++)
									arrIdHanhKhach[j] = arrIdHanhKhach[j + 1];
								SoHanhKhach--;
								break;
							}
						}
						if (Delete_Passenger(t, b->data)){
							XuatListPassengerTheoTungTrang(t, (trangHientaiHK - 1) * SOLUONGMOITRANG);
							gotoxy(X_ThongBao, Y_ThongBao);
							cout << "Xoa thanh cong !";
							TitleBangChon(tpMucLucHK);
						}
					}
					else goto backMenu;
				}
				else if (key == KEY_F4){
					gotoxy(20, Y_DISPLAY + 39); cout << setw(150) << " ";
					NODE_HANHKHACH* b = ChoosePassenger(t);
					if (b == NULL) goto backMenu;
					GiaoDienChinhSua(tpGiaodienHK, sizeof(tpGiaodienHK) / sizeof(string), 35);
					InputPassenger(t, b->data, true);
					system("cls");
					XuatListPassengerTheoTungTrang(t, (trangHientaiHK - 1) * SOLUONGMOITRANG);
					Display(tpGiaodienHK, sizeof(tpGiaodienHK) / sizeof(string));
					gotoxy(X_ThongBao, Y_ThongBao); cout << "Sua thanh cong !";
					TitleBangChon(tpMucLucHK);
				}
				else if (key == KEY_RIGHT && trangHientaiHK < tongsoTrangHK)
				{
					system("cls");
					trangHientaiHK++;
					XuatListPassengerTheoTungTrang(t, (trangHientaiHK - 1) * SOLUONGMOITRANG);
					Display(tpGiaodienHK, sizeof(tpGiaodienHK) / sizeof(string));
					TitleBangChon(tpMucLucHK);
				}
				else if (key == KEY_LEFT && trangHientaiHK > 1)
				{
					system("cls");
					trangHientaiHK--;
					XuatListPassengerTheoTungTrang(t, (trangHientaiHK - 1) * SOLUONGMOITRANG);
					Display(tpGiaodienHK, sizeof(tpGiaodienHK) / sizeof(string));
					TitleBangChon(tpMucLucHK);
				}
			}
			else if (key == ESC)
				return;
		}
	}
}

//=========================DOC/GHI FILE========================
void SaveMayBay(AirPlanes DSMB){
	fstream fileOut1("C:\\Users\\Admin\\Desktop\\chuyenbay\\maybay.txt", ios::out | ios::binary);
	for (int i = 0; i < DSMB.n; i++)
		fileOut1.write(reinterpret_cast<const char*>(DSMB.data[i]), sizeof(PData));

	fileOut1.close();
}

void LoadMayBay(AirPlanes &DSMB){
	fstream fileIn1("C:\\Users\\Admin\\Desktop\\chuyenbay\\maybay.txt", ios::in | ios::binary);
	while (!fileIn1.eof()) {
		DSMB.data[++DSMB.n] = new PData;
		fileIn1.read(reinterpret_cast<char*>(DSMB.data[DSMB.n]), sizeof(PData));
	}
	delete DSMB.data[DSMB.n];
	fileIn1.close();
}

void SaveChuyenBay(listFlight cb) {
	int sizeFlight = sizeof(Flight) - sizeof(Ticket*);
	fstream fileOut2("C:\\Users\\Admin\\Desktop\\chuyenbay\\chuyenbay.txt", ios::out | ios::binary);
	fileOut2.write(reinterpret_cast<const char*>(&cb.n), sizeof(int));
//	for (NODE_CHUYENBAY *q = cb.Head; q != NULL; q = q->Next) {
//		fileOut2.write(reinterpret_cast<const char*>(&q->DataFlight), sizeFlight);
//		int nTicket = q->DataFlight.SoVeDaBan;
//		for (int i = 0; i < nTicket; i++)
//			fileOut2.write(reinterpret_cast<const char*>(&q->DataFlight.DanhSachVe[i]), sizeof(Ticket));
//	}
	NODE_CHUYENBAY* p = cb.Head;
	while(p != NULL){
		fileOut2.write(reinterpret_cast<const char*>(&p->DataFlight), sizeFlight);
		int nTicket = p->DataFlight.SoVe;
		for (int i = 0; i < nTicket; i++)
			fileOut2.write(reinterpret_cast<const char*>(&p->DataFlight.DanhSachVe[i]), sizeof(Ticket));
		p = p->Next;
	}
	fileOut2.close();
}

void LoadChuyenBay(listFlight &cb) {
	int sizeFlight = sizeof(Flight) - sizeof(Ticket*);
	int SoChuyenBay;
	fstream fileIn2("C:\\Users\\Admin\\Desktop\\chuyenbay\\chuyenbay.txt", ios::in | ios::binary);
	InitListFlight(cb);
	fileIn2.read(reinterpret_cast<char*>(&SoChuyenBay), sizeof(int));
	Flight p;
	for (int i = 0; i < SoChuyenBay; ++i) {
		fileIn2.read(reinterpret_cast<char*>(&p), sizeFlight);
		int nTicket = p.SoVe;
		p.DanhSachVe = new Ticket[MAXTICKET];
		for (int j = 0; j < nTicket; j++)
			fileIn2.read(reinterpret_cast<char*>(&p.DanhSachVe[j]), sizeof(Ticket));

		ThemVaoCuoiList(cb, p);
	}
	fileIn2.close();
}

void GhiHanhKhachVaoFile(treeHanhKhach p, fstream &fileOut3, int size) {
	if (p != NULL) {
		fileOut3.write(reinterpret_cast<const char*>(&p->data), size);
		GhiHanhKhachVaoFile(p->left, fileOut3, size);
		GhiHanhKhachVaoFile(p->right, fileOut3, size);
	}
}

void SaveHanhKhach(treeHanhKhach point) {
	fstream fileOut3("C:\\Users\\Admin\\Desktop\\chuyenbay\\hanhkhach.txt", ios::out | ios::binary);
	fileOut3.write(reinterpret_cast<const char*>(&SoHanhKhach), sizeof(int));
	//fileOut3 << SoHanhKhach;
	int size = sizeof(HanhKhach);
	treeHanhKhach p = point;
	GhiHanhKhachVaoFile(p, fileOut3, size);
	fileOut3.close();
}

void LoadHanhKhach(treeHanhKhach &t) {
	fstream fileIn3("C:\\Users\\Admin\\Desktop\\chuyenbay\\hanhkhach.txt", ios::in | ios::binary);
	int SoHK;
	HanhKhach hk;
	fileIn3.read(reinterpret_cast<char*>(&SoHK), sizeof(int));
	//fileIn3 >> SoHanhKhach;
	int size = sizeof(HanhKhach);
	for (int i = 0; i <= SoHK; i++)
	{
		fileIn3.read(reinterpret_cast<char*>(&hk), size);
		Insert_HanhKhach(t, hk);
	}
}

//void Xuat(HanhKhach p) {
//	cout << "\n===============";
//	cout << "\ncmnd " << p.cmnd;
//	cout << "\nho " << p.Ho;
//	cout << "\nten " << p.Ten;
//	cout << "\nphai " << p.phai;
//}

//void Output(treeHanhKhach t) {
//	if (t != NULL) {
//		Output(t->left);
//		Xuat(t->data);
//		Output(t->right);
//	}
//}
//==============================================================================
// Xoa may bay trong DSMB 
void Del(AirPlanes &dsmb, listFlight &cb)
{
	int keyboard;
	int trangHienTai = 1;
	int SOLUONGMOITRANGMB = 20;
	do
	{
	fflush(stdin);
	int k = PickMB(dsmb);
	if (k != -1)
	{
		int flag = 1;
		for (NODE_CHUYENBAY* p = cb.Head; (p != NULL) && (flag != 0); p= p->Next)
		{
			if ((stricmp(dsmb.data[k]->SoHieu,p->DataFlight.SoHieu) == 0) && (((p->DataFlight.TrangThai == TT_CONVE) && (p->DataFlight.SoVeDaBan!=0)) || (p->DataFlight.TrangThai == TT_HETVE)))
				flag = 0;
		}
		if (flag == 1)
		{
			setColor(239,77);
			gotoxy(79,12); cout <<"Are you sure you want to permanently delete this Airplanes?"; 
			gotoxy(98,15); cout <<"Enter to confirm"; 
			setColor(3,0);
			int getkytu;
			getkytu = getch();
			gotoxy(79,12); cout <<"                                                           "; 
			gotoxy(98,15); cout <<"                "; 
			if (getkytu == ENTER)
			{ 
				for (int i = k; i < dsmb.n; i++)
				{
					dsmb.data[i]=dsmb.data[i+1];
				}
				dsmb.n--;
				
				system("cls");
				KhungXuatMB();
				XuatDSMBB(dsmb, (trangHienTai - 1) * SOLUONGMOITRANGMB);
				setColor(3,0);
				gotoxy(79,22); cout <<" Xoa thanh cong !!! ";
				gotoxy(79,23); cout <<" Any key to continue"; 
				gotoxy(79,24); cout <<" ESC to exit        ";  
				Normal();
				keyboard = getch();
			}
		}
		else 
		{
			gotoxy(79,22); cout <<"May bay dang co chuyen bay ";
			gotoxy(79,23); cout <<"      Khong the xoa"; 
			getch();
		}
	}
	else (keyboard = ESC);
	}
	while (keyboard != ESC);
	
}
// Sua DSMB
void EditDSMB (AirPlanes &dsmb, listFlight &cb) //
{	
	int keyboard,Temp;	
	int SOLUONGMOITRANGMB = 20;
	int tongsoTrang = ((dsmb.n - 1) / SOLUONGMOITRANGMB) + 1;
	int toadox[4] = {0,13,35,47};
	int toadoy;
	int k;
	do
	{
			int flag=0;
			int chonlua=1;
			k = PickMB(dsmb);
			if (k != -1)
			{
				TextColor(14);
				gotoxy(45,26); cout<<"ESC: exit";
				Normal();	
				int trangHienTai = (k/SOLUONGMOITRANGMB)+1;
				if (trangHienTai >=2) toadoy = (k - ((trangHienTai*2 - 2)*10)) + 5;
				else toadoy = k+5;
				SetBGColor(8);
				gotoxy(toadox[chonlua],toadoy);
				cout<<dsmb.data[k]->LoaiMayBay;
				SetBGColor(0);
				do
				{
					keyboard = getch();
					VeKhungCH(89,19,25,3,0);
					gotoxy(91,20); cout<<"                    ";	
					gotoxy(91,21); cout<<"                    ";
					if (keyboard == 0) keyboard = getch();
					switch (keyboard) 
					{
					case KEY_RIGHT:	if ( chonlua < 3)
					{
							if (chonlua == 1)
							{
								SetBGColor(0);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmb.data[k]->LoaiMayBay;
								chonlua++;
								SetBGColor(8);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmb.data[k]->SoHieu;
								Normal();
								
							}
							else if ( chonlua == 2)
							{
								SetBGColor(0);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmb.data[k]->SoHieu;
								chonlua++;
								SetBGColor(8);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmb.data[k]->SoCho;
								Normal();
							}
					}
					break;
					case KEY_LEFT:if ( chonlua > 1)
					{
							if ( chonlua == 2)
							{
								SetBGColor(0);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmb.data[k]->SoHieu;
								chonlua--;
								SetBGColor(8);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmb.data[k]->LoaiMayBay;
								Normal();
							}
							else if ( chonlua == 3)
							{
								SetBGColor(0);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmb.data[k]->SoCho;
								chonlua--;
								SetBGColor(8);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmb.data[k]->SoHieu;
								Normal();
							}
					}
					break;
					case ENTER:
					{	
						
						switch(chonlua)
						{
						case 1:
						{
							char b[15];
							fflush(stdin);
							gotoxy(toadox[chonlua],toadoy);
							cout<<"                 ";
							gotoxy(toadox[chonlua],toadoy);
							cin.getline(b,15);
							Trim(b);
							strcpy(dsmb.data[k]->LoaiMayBay,b);	
							VeKhungCH(89,19,25,3,1);
							gotoxy(90,20); cout<<" Chinh sua thanh cong   ";	
							gotoxy(90,21); cout<<" Any key to continue ";
							break;
						}
						case 2:
						{
							char Temp[15];
							char b[15];
							fflush(stdin);
							strcpy(Temp,dsmb.data[k]->SoHieu);
							gotoxy(toadox[chonlua],toadoy);
							cout<<"       ";
							gotoxy(toadox[chonlua],toadoy);
							cin.getline(b,15);
							Trim(b);
							int Check;
							do
							{
								Check = SearchSH(dsmb,b);
								if (Check != -1)
								{
									VeKhungCH(89,19,25,3,1);
									setColor(14,0);			
									gotoxy(90,20); cout<<"SO HIEU DA DUOC SU DUNG ";
									gotoxy(90,21); cout<<"       Moi dat lai      ";
									Normal();
									gotoxy(toadox[chonlua],toadoy);
									cout<<"       ";
									gotoxy(toadox[chonlua],toadoy);
									cin.getline(b,15);
									VeKhungCH(89,19,25,4,0);
									gotoxy(90,21); cout<<"                         ";
									gotoxy(90,22); cout<<"                         ";
									gotoxy(90,23); cout<<"                         ";
									Normal();
								}	
							}
							while (Check != -1);
							strcpy(dsmb.data[k]->SoHieu,b);
							for (NODE_CHUYENBAY* p = cb.Head; p != NULL; p= p->Next)
							{
								if (stricmp(Temp,p->DataFlight.SoHieu) == 0)
									strcpy(p->DataFlight.SoHieu,dsmb.data[k]->SoHieu); 
							}	
							VeKhungCH(89,19,25,3,1);
							gotoxy(90,20); cout<<" Chinh sua thanh cong   ";	
							gotoxy(90,21); cout<<" Any key to continue ";
							break;	
						}
						case 3:
						{
						int flag = 0;
						for (NODE_CHUYENBAY* p = cb.Head; (p != NULL) && (flag != 1); p= p->Next)
							{
								if ((stricmp(dsmb.data[k]->SoHieu,p->DataFlight.SoHieu) == 0) && (p->DataFlight.SoVeDaBan == 0) && (p->DataFlight.TrangThai != TT_HOANTAT) && (p->DataFlight.TrangThai != TT_HUYCHUYEN))
								flag = 1;
							}
						if (flag == 1)
						{
							int a;
						/*	char Temp[15];
							int Tam;
							Tam = dsmb.data[k]->SoCho;
							strcpy(Temp,dsmb.data[k]->SoHieu);*/
							gotoxy(toadox[chonlua],toadoy);
							cout<<"      ";
							gotoxy(toadox[chonlua],toadoy);
							cin>>a;
							while (a<20)
							{
								VeKhungCH(89,19,25,3,1);
								setColor(14,0);			
								gotoxy(90,20); cout<<" SO CHO PHAI LON HON 20 ";
								Normal();
								gotoxy(toadox[chonlua],toadoy);
								cout<<"     ";
								gotoxy(toadox[chonlua],toadoy);
								cin>>a;
								VeKhungCH(89,19,25,3,0);
								gotoxy(90,21); cout<<"                        ";
								Normal();
							}
							dsmb.data[k]->SoCho=a;
							for (NODE_CHUYENBAY* p = cb.Head; p != NULL; p= p->Next)
							{
								if ((stricmp(dsmb.data[k]->SoHieu,p->DataFlight.SoHieu) == 0) && ((p->DataFlight.SoVeDaBan == 0) && (p->DataFlight.TrangThai != TT_HOANTAT) ))
									p->DataFlight.SoVe = dsmb.data[k]->SoCho;
							}
							
							VeKhungCH(89,19,25,3,1);
							gotoxy(90,20); cout<<" Chinh sua thanh cong   ";	
							gotoxy(90,21); cout<<" Any key to continue ";
							break;
						}
						else
						{
							gotoxy(90,20); cout<<"May bay da co chuyen bay duoc dat ve hoac chuyen bay da hoan tat/huy chuyen";
							gotoxy(90,21); cout<<"                    Any key to continue ";
						}
						}
						break;
						}
					break;
			    	}
					case ESC: 
						flag=1;
						break;
					}
				}while (flag == 0);
		}
	}
	while (k != -1);
}

bool KiemTraHanhKhachTrenCB(NODE_CHUYENBAY* fl, NODE_HANHKHACH* hkhach){
	for (int i = 0; i < fl->DataFlight.SoVe; i++){
			if (strcmp(fl->DataFlight.DanhSachVe[i].cmndHK, hkhach->data.cmnd) == 0){
					return true;
			}
		}
	return false;
}

bool DatVe(treeHanhKhach &hk, listFlight &cb){
	system("cls");
	if (hk == NULL){
		gotoxy(10, 10); cout << "Chua co hanh khach nao ! Bam phim bat ky de nhap thong tin hanh khach";
		getch();
		gotoxy(10, 10); cout << "                                                                      ";
		HanhKhach a;
		GiaoDienChinhSua(tpGiaodienHK, sizeof(tpGiaodienHK) / sizeof(string), 35);
		InputPassenger(hk, a, false);
		SaveHanhKhach(hk);
	}
	setColor(15, 6);
	gotoxy(X_TITLE, Y_TITLE); cout << "CHON HANH KHACH MUON DAT VE";
	setColor(14, 0);
	NODE_HANHKHACH* hkhach = ChoosePassenger(hk);
	if (hkhach == NULL)
	{
		system("cls");
		return false;
	}
	system("cls");
	
	setColor(15, 6);
	gotoxy(X_TITLE, Y_TITLE); cout << "CHON CHUYEN BAY MUON DAT VE";
	gotoxy(X_ThongBao + 30, Y_ThongBao + 3); cout << "ESC : thoat";
	setColor(14, 0);
	Display(tpGiaodienCB, sizeof(tpGiaodienCB) / sizeof(string));
	gotoxy(toadoxGiaoDien[0] + 1, Y_DISPLAY + 40);
	cout << setw(toadoxGiaoDien[sizeof(tpGiaodienHK) / sizeof(string)] - toadoxGiaoDien[0] - 1) << " " << setfill(' ');
	XuatListFlightTheoTungTrang(cb, 0);
	NODE_CHUYENBAY* fl;
	int keyboard;
	do{
		fl = ChooseFlight(cb);
		if (fl == NULL){ // ESC
			system("cls");
			return false;
		}
		if (fl->DataFlight.TrangThai != TT_CONVE){
			gotoxy(X_ThongBao, Y_ThongBao);
			cout <<"Chon chuyen con ve. Xin cam on !";
			keyboard = getch();
		}
		if (KiemTraHanhKhachTrenCB(fl, hkhach)){
			gotoxy(X_ThongBao, Y_ThongBao); cout << setw(41) << setfill(' ');
			gotoxy(X_ThongBao, Y_ThongBao);
			cout << "Hanh Khach da dat ve tren chuyen bay nay !";
			keyboard = getch();
		}
		gotoxy(X_ThongBao, Y_ThongBao); cout << "                                           ";
	} while (fl->DataFlight.TrangThai != TT_CONVE || KiemTraHanhKhachTrenCB(fl, hkhach));
	
	int ve;
	system("cls");
	do {
		ve = ChooseTicket(fl->DataFlight);
		if (fl->DataFlight.DanhSachVe[ve - 1].tinhTrang == TICHKET_DABAN && ve != -1){
			gotoxy(X_ThongBao, Y_ThongBao); cout << "Ve da co nguoi dat";
			getch();
			DeleteNotify();
		}
	}while (fl->DataFlight.DanhSachVe[ve - 1].tinhTrang == TICHKET_DABAN && ve != -1);
	
	if (ve == -1){
		system("cls");
		return false;
	}
	
	fl->DataFlight.DanhSachVe[ve - 1].tinhTrang = TICHKET_DABAN;
	fl->DataFlight.SoVeDaBan++;
	strcpy(fl->DataFlight.DanhSachVe[ve - 1].cmndHK, hkhach->data.cmnd);
	//hkhach->data.daDatVe = true;
	if (fl->DataFlight.SoVe == fl->DataFlight.SoVeDaBan) fl->DataFlight.TrangThai = TT_HETVE;
	gotoxy(X_ThongBao, Y_ThongBao); cout << "Dat ve thanh cong !";
	getch();
	return true;
}

bool KiemTraSoVe(){
	for (int i = 0; i < SoCB; i++){
		if (arrSoVe[i] != 0) return false;
	}
	return true;
}

bool HuyVe(treeHanhKhach &hk, listFlight &cb){
	system("cls");
	setColor(15, 6);
	gotoxy(X_TITLE, Y_TITLE); cout << "CHON HANH KHACH MUON HUY VE";
	setColor(14, 0);
	Display(tpGiaodienHK, sizeof(tpGiaodienHK) / sizeof(string));
	DeleteNote(sizeof(toadoxGiaoDien) / sizeof(string));
	NODE_HANHKHACH* hkhach;
	do{
		hkhach = ChoosePassenger(hk);
		if (hkhach == NULL)
		{
			system("cls");
			return false;
		}
		FindFlightTheoCMND(cb, hkhach->data.cmnd);
		if (KiemTraSoVe()) 
		{
			gotoxy(X_ThongBao, Y_ThongBao); cout << "Hanh khach chua dat ve !";
		}
	}while(KiemTraSoVe());
	system("cls");
	setColor(15, 6);
	gotoxy(X_TITLE, Y_TITLE); cout << " CHUYEN BAY HANH KHACH DA DAT VE ";
	setColor(11, 0);
	Display2(tpGiaodienThongTinVe, tpGiaodienCB, sizeof(tpGiaodienThongTinVe) / sizeof(string));
	NODE_CHUYENBAY* f;
	do {
		f = ChooseFlightDelete(cb);
		if (f == NULL){
			system("cls");
			return false;
		}
		if (f->DataFlight.TrangThai == TT_HOANTAT || f->DataFlight.TrangThai == TT_HUYCHUYEN){
			gotoxy(X_ThongBao, Y_ThongBao); cout << "Chon chuyen chua khoi hanh. Xin cam on !";
			getch();
		}
		gotoxy(X_ThongBao, Y_ThongBao); cout << "                                               ";
	}while(f->DataFlight.TrangThai == TT_HOANTAT || f->DataFlight.TrangThai == TT_HUYCHUYEN);
	int temp = arrSoVe[SoTTVe];
	arrSoVe[SoTTVe] = 0;
	f->DataFlight.DanhSachVe[temp - 1].tinhTrang = TICHKET_TRONG;
	f->DataFlight.SoVeDaBan--;
	strcpy(f->DataFlight.DanhSachVe[temp - 1].cmndHK, "000000000");
	f->DataFlight.TrangThai = TT_CONVE;
	gotoxy(X_ThongBao, Y_ThongBao); cout << "Huy ve thanh cong !";
	getch();
	return true;
}

void ChuyenTrangCauE(Flight fl, HanhKhach arrHK[], int arrSoVe[], int firstOrdinal){
	ShowCur(false);
	system("cls");
	setColor(15, 6);
	gotoxy(X_TITLE, Y_TITLE);
	cout << "DANH SACH HANH KHACH THUOC CHUYEN BAY : " << fl.id;
	gotoxy(X_TITLE + 33, Y_TITLE + 1);
	cout << " NOI DEN: " << fl.SanBayden;
	gotoxy(X_TITLE - 3, Y_TITLE + 1);
	cout << "NGAY GIO KHOI HANH: "; OutputDateTime(fl.Ngaykhoihanh);
	setColor(14, 3);
	gotoxy(116, 13); cout << "   LEFT   ";
	gotoxy(116, 14); cout << "   RIGHT  ";
	gotoxy(116, 17); cout << "           ";
	gotoxy(116, 18); cout << "    ESC    ";
	gotoxy(116, 19); cout << "           ";
	setColor(11, 0);
	gotoxy(129, 13); cout << "chuyen trang";
	gotoxy(129, 18); cout << "thoat";
	Display(tpGiaodienHK1CB, sizeof(tpGiaodienHK1CB) / sizeof(string));
	int temp = 0;
	for (int i = firstOrdinal; i < fl.SoVeDaBan; i++){
		if (temp < SOLUONGMOITRANG){
			gotoxy(toadoxGiaoDien3[0] + 1, Y_DISPLAY + 3 + temp * 2); cout << i + 1;
			gotoxy(toadoxGiaoDien3[1] + 1, Y_DISPLAY + 3 + temp * 2); cout << arrSoVe[i];
			XuatHanhKhach1ChuyenBay(arrHK[i], temp);
		}
		temp++;
	}
}

bool HanhKhach1ChuyenBay(listFlight cb, treeHanhKhach hk){
	system("cls");
	setColor(15, 6);
	gotoxy(X_TITLE, Y_TITLE); cout << "CHON CHUYEN BAY MUON IN";
	setColor(14, 0);
	Display(tpGiaodienCB, sizeof(tpGiaodienCB) / sizeof(string));
	NODE_CHUYENBAY* fl;
	do{
		fl = ChooseFlight(cb);
		if (fl == NULL){
			system("cls");
			return false;
		}
		if (fl->DataFlight.TrangThai == TT_HUYCHUYEN){
			gotoxy(X_ThongBao, Y_ThongBao);
			cout <<"Vui long chon chuyen khac !";
			getch();
		}
		if (fl->DataFlight.SoVeDaBan == 0)
		{
			gotoxy(X_ThongBao, Y_ThongBao);
			cout << "Khong co hanh khach !";
		}
	} while (fl->DataFlight.TrangThai == TT_HUYCHUYEN && fl != NULL || fl->DataFlight.SoVeDaBan == 0);

	system("cls");
	setColor(15, 6);
	gotoxy(X_TITLE, Y_TITLE);
	cout << "DANH SACH HANH KHACH THUOC CHUYEN BAY : " << fl->DataFlight.id;
	gotoxy(X_TITLE + 33, Y_TITLE + 1);
	cout << " NOI DEN: " << fl->DataFlight.SanBayden;
	gotoxy(X_TITLE - 3, Y_TITLE + 1);
	cout << "NGAY GIO KHOI HANH: "; OutputDateTime(fl->DataFlight.Ngaykhoihanh);
	setColor(14, 3);
	gotoxy(116, 13); cout << "    LEFT   ";
	gotoxy(116, 14); cout << "    RIGHT  ";
	gotoxy(116, 22); cout << "           ";
	gotoxy(116, 23); cout << "    ESC    ";
	gotoxy(116, 24); cout << "           ";
	setColor(11, 0);
	gotoxy(129, 13); cout << "chuyen trang";
	gotoxy(129, 23); cout << "thoat";
	Display(tpGiaodienHK1CB, sizeof(tpGiaodienHK1CB) / sizeof(string));
	
	int tongsoTrangCauE = (fl->DataFlight.SoVeDaBan - 1) / SOLUONGMOITRANG + 1;
	int	trangHientaiCauE = 1; int IntCMND; int count = 0;
	HanhKhach arrHK[fl->DataFlight.SoVeDaBan]; // mang chua du lieu hanh khach, thuan tien cho viec chuyen doi qua lai giua cac trang hon
	int arrSoVe[fl->DataFlight.SoVeDaBan]; // mang chua so ghe tren chuyen bay
	
	for (int i = 0; i < fl->DataFlight.SoVe; i++){
		if(fl->DataFlight.DanhSachVe[i].tinhTrang == TICHKET_DABAN){
			IntCMND = atoi(fl->DataFlight.DanhSachVe[i].cmndHK);
			NODE_HANHKHACH* passenger = FindPassenger(hk, IntCMND);
			arrHK[count] = passenger->data;
			arrSoVe[count] = i + 1;
			count++;
		}
	}
	
	ChuyenTrangCauE(fl->DataFlight, arrHK, arrSoVe, 0);
	while (true)
	{
		int keyboard_read = getch();
		if (keyboard_read == 0)
			keyboard_read = getch();
		switch (keyboard_read)
		{
		case KEY_RIGHT:
			if (trangHientaiCauE < tongsoTrangCauE)
			{
				trangHientaiCauE++;
				ChuyenTrangCauE(fl->DataFlight, arrHK, arrSoVe, (trangHientaiCauE - 1) * SOLUONGMOITRANG);
			}
			break;
		case KEY_LEFT:
			if (trangHientaiCauE > 1)
			{
				trangHientaiCauE--;
				ChuyenTrangCauE(fl->DataFlight, arrHK, arrSoVe, (trangHientaiCauE - 1) * SOLUONGMOITRANG);
			}
			break;
		case ESC: 
			return true; 
			break;
		}//end switch  read key
	}
	getch();
	return true;
}

bool VeTrongCuaChuyenBay(listFlight cb){
	system("cls");
	setColor(15, 6);
	gotoxy(X_TITLE, Y_TITLE); cout << " CHON CHUYEN BAY MUON THONG KE ";
	setColor(14, 0);
	Display(tpGiaodienCB, sizeof(tpGiaodienCB) / sizeof(string));
	gotoxy(toadoxGiaoDien[0] + 1, Y_DISPLAY + 40);
	//cout << setw(toadoxGiaoDien[sizeof(tpGiaodienHK) / sizeof(string)] - toadoxGiaoDien[0] - 1) << " " << setfill(' ');
	XuatListFlightTheoTungTrang(cb, 0);
	NODE_CHUYENBAY* fl;
	do{
		fl = ChooseFlight(cb);
		if (fl == NULL){
			system("cls");
			return false;
		}
		if (fl->DataFlight.TrangThai == TT_HUYCHUYEN){
			gotoxy(X_ThongBao, Y_ThongBao); cout << setw(41) << setfill(' ');
			gotoxy(X_ThongBao, Y_ThongBao);
			cout << "Chuyen bay da huy. Chon chuyen khac !";
			getch();
		}
		gotoxy(X_ThongBao, Y_ThongBao); cout << "                                            ";
	} while (fl->DataFlight.TrangThai == TT_HUYCHUYEN && fl != NULL);
	
	system("cls");
	ShowCur(false);
	setColor(15, 6);
	gotoxy(X_TITLE, Y_TITLE); cout << " DANH SACH VE CUA CHUYEN BAY : " << fl->DataFlight.id;
	setColor(14, 0);
	GiaoDienDatVe(fl->DataFlight, true);
	getch();
	return true;
}

void CauF(listFlight cb)
{
	DateTime Temp;
	char Dich[100];
	int keyboard;
	int flag = 0;
	do
	{
		system("cls");
		gotoxy(55,1); cout<<"DANH SACH CAC CHUYEN BAY KHOI HANH";
		gotoxy(57,2); cout<<"  /  /    "; 
		gotoxy(72,2); cout<<"Noi den:";
		gotoxy(57,2); cin>>Temp.ngay;
		gotoxy(60,2); cin>>Temp.thang;
		gotoxy(63,2); cin>>Temp.nam;
		gotoxy(82,2); 
		fflush(stdin);
		cin.getline(Dich,100);
		Trim(Dich);
		if (cb.Head == NULL)	
		{
		gotoxy(20,5);	cout<<"Khong co Chuyen bay can tim";
		}
		else
		{
			
			int toadoy= 12;
			int soluongcbmax=0;
			
			for (NODE_CHUYENBAY *p = cb.Head; p != NULL; p = p->Next)
			{
				if ((p->DataFlight.Ngaykhoihanh.ngay == Temp.ngay) && (p->DataFlight.Ngaykhoihanh.ngay == Temp.ngay) 
				&& (p->DataFlight.Ngaykhoihanh.ngay == Temp.ngay) && (stricmp(p->DataFlight.SanBayden,Dich) == 0) 
				&& (p->DataFlight.TrangThai == TT_CONVE))
				soluongcbmax++;
			}
			if (soluongcbmax > 0)
			{
				VeKhungCH(12,9,104,18,1);
				//Thanh doc
				for (int i = 10;i <27;i++)
				{
					gotoxy(32,i);	cout<<char(179);
					gotoxy(57,i);	cout<<char(179);
					gotoxy(77,i);	cout<<char(179);
					gotoxy(97,i);	cout<<char(179);
				}
				//Thanh ngang
				for (int i = 13; i < 116;i++ )
				{
					gotoxy(i,11);	cout<<char(196);
				}
				//Nga tu
				gotoxy(32,11);	cout<<char (197);
				gotoxy(57,11);	cout<<char (197);
				gotoxy(77,11);	cout<<char (197);
				gotoxy(97,11);	cout<<char (197);
				//Nga ba huong xuong
				gotoxy(32,9);	cout<<char (194);
				gotoxy(57,9);	cout<<char (194);
				gotoxy(77,9);	cout<<char (194);
				gotoxy(97,9);	cout<<char (194);
				//Nga ba huong len
				gotoxy(32,27);	cout<<char (193);
				gotoxy(57,27);	cout<<char (193);
				gotoxy(77,27);	cout<<char (193);
				gotoxy(97,27);	cout<<char (193);
				//nga ba
				gotoxy(12,11);
				cout<<char (195); //phai
				gotoxy(116,11);
				cout<<char (180); //trai
				TextColor(14);
				gotoxy(17,10); cout<<"So Hieu MB";
				gotoxy(38,10); cout<<"Ma Chuyen Bay";
				gotoxy(64,10); cout<<"Ngay Gio";
				gotoxy(82,10); cout<<"San Bay Den";
				gotoxy(100,10); cout<<"So Ve Con Lai";
				TextColor(11);
				setColor(14, 3);
				gotoxy(125, 12); cout << "   LEFT   ";
				gotoxy(125, 13); cout << "   RIGHT  ";
				gotoxy(125, 17); cout << "           ";
				gotoxy(125, 18); cout << "    ESC    ";
				gotoxy(125, 19); cout << "           ";
				setColor(11, 0);
				gotoxy(144, 12); cout << "chuyen trang";
				gotoxy(144, 18); cout << "thoat";
				Flight CBdatyeucau[soluongcbmax];
				int countPhantu = -1;
				for (NODE_CHUYENBAY *p = cb.Head; (p != NULL) && (countPhantu < soluongcbmax) ;p = p->Next)
				{
					if ((p->DataFlight.Ngaykhoihanh.ngay == Temp.ngay) && (p->DataFlight.Ngaykhoihanh.ngay == Temp.ngay) 
					&& (p->DataFlight.Ngaykhoihanh.ngay == Temp.ngay) && (stricmp(p->DataFlight.SanBayden,Dich) == 0) 
					&& (p->DataFlight.TrangThai == TT_CONVE))
					{
						countPhantu++;
						CBdatyeucau[countPhantu] = p->DataFlight;
						
					}
				}
				for (int i = 0; ((i < soluongcbmax) && (i < 15)); i++)
				{
						gotoxy(19, toadoy); cout << CBdatyeucau[i].SoHieu;
						gotoxy(41, toadoy); cout << CBdatyeucau[i].id;
						gotoxy(60, toadoy); OutputDateTime(CBdatyeucau[i].Ngaykhoihanh);
						gotoxy(82, toadoy); cout << CBdatyeucau[i].SanBayden;
						gotoxy(105, toadoy);cout << CBdatyeucau[i].SoVe - CBdatyeucau[i].SoVeDaBan;
						toadoy++;
				}
				int tongsoTrang = ((soluongcbmax - 1) / SOLUONGMOITRANG) + 1;
				if (tongsoTrang > 1)
				{
					int trangHienTai = 1;
					int choice;
					while (true)	
					{
							fflush(stdin);
							keyboard = getch();
							if (keyboard == 0) keyboard = getch();
							switch (keyboard) 
							{
								case KEY_RIGHT:if (trangHienTai < tongsoTrang)
								{
									toadoy = 12;
									trangHienTai++;
									choice = (trangHienTai -1)* SOLUONGMOITRANG;
									XoamanhinhF();	
									for (int i = choice; (i <= choice + 14) && (i< soluongcbmax) ; i++)
									{
											gotoxy(16, toadoy); cout << CBdatyeucau[i].SoHieu;
											gotoxy(34, toadoy); cout << CBdatyeucau[i].id;
											gotoxy(60, toadoy); OutputDateTime(CBdatyeucau[i].Ngaykhoihanh);
											gotoxy(81, toadoy); cout << CBdatyeucau[i].SanBayden;
											gotoxy(105, toadoy);cout << CBdatyeucau[i].SoVe - CBdatyeucau[i].SoVeDaBan;
											toadoy++;
									}
								}
								break;
								case KEY_LEFT:	if (trangHienTai > 1)
								{
									toadoy = 12;
									trangHienTai--;
									choice = (trangHienTai -1)* SOLUONGMOITRANG;
									XoamanhinhF();	
									for (int i = choice; (i <= choice + 14) && (i< soluongcbmax) ; i++)
									{
											gotoxy(16, toadoy); cout << CBdatyeucau[i].SoHieu;
											gotoxy(34, toadoy); cout << CBdatyeucau[i].id;
											gotoxy(60, toadoy); OutputDateTime(CBdatyeucau[i].Ngaykhoihanh);
											gotoxy(81, toadoy); cout << CBdatyeucau[i].SanBayden;
											gotoxy(105, toadoy);cout << CBdatyeucau[i].SoVe - CBdatyeucau[i].SoVeDaBan;
											toadoy++;
									}
									
								}
								break;
								case ESC: 
								{
								flag = 1;
								return ;
								break;
								}
							}
					}
				}
				else
				{
					gotoxy(125,22); cout<<"Any key to continue ";	
					keyboard = getch();
					if (keyboard == ESC) flag = 1;
				}
		}
		else
		{
			gotoxy(10,toadoy);
			cout<<"Khong co chuyen bay can tim !!!";
			keyboard = getch();
		}
		if (keyboard == ESC) flag = 1;
		}
	} while (flag == 0);
}

bool CauH(listFlight cb)
{
	ShowCur(false);
	AirPlanes Counted;
	
	Counted.n = -1;	
	system("cls");
	if (cb.Head == NULL)	cout<<"Khong thong ke duoc vi khong co chuyen bay";
	else
	{	
		for (NODE_CHUYENBAY *p = cb.Head; p != NULL; p = p->Next)
		{
			if (Counted.n == -1)
			{
				Counted.n++;
				Counted.data[Counted.n] = new PData;
				strcpy(Counted.data[Counted.n]->SoHieu,p->DataFlight.SoHieu);
				Counted.data[Counted.n]->SoCho=1; //So cho = dem
			}
			else
			{
				int flag=0;
				for (int i = 0; i <= Counted.n; i++)
				{
					if (stricmp(Counted.data[i]->SoHieu, p->DataFlight.SoHieu) == 0) 
					{
						Counted.data[i]->SoCho++;
						flag = 1;
					}
				}
				if (flag != 1)
				{
					Counted.n++;
					Counted.data[Counted.n] = new PData;
					strcpy(Counted.data[Counted.n]->SoHieu,p->DataFlight.SoHieu);
					Counted.data[Counted.n]->SoCho=1;
				}
			}			
		}	
	
		
		for (int i = 0; i< Counted.n; i++)
		{
			int vitrimax = i;
			int max=Counted.data[i]->SoCho;
			for (int j=i+1;j<=Counted.n;j++)
			{
				if (Counted.data[j]->SoCho > max )	
				{
					max  = Counted.data[j]->SoCho;
					vitrimax = j;
				}
			}
			PData *Temp;
			Temp = Counted.data[vitrimax];
			Counted.data[vitrimax] = Counted.data[i];
			Counted.data[i]=Temp;
			
		}	
		VeKhungCH(17,9,70,18,1);
		for (int i = 10; i<=26; i++ ) 
		{
			gotoxy(40,i);	cout<<char (179);
		}
		for (int i = 18; i<= 86; i++)
		{
			gotoxy(i,11);	cout<<char (196);
		}
		gotoxy(40,27);	cout<<char (193);	//nga ba len
		gotoxy(40,9);	cout<<char (194);	//nga ba xuong
		gotoxy(40,11);	cout<<char (197);	//nga tu
		gotoxy(87,11);	cout<<char (180);	//nga ba trai
		gotoxy(17,11);	cout<<char (195);	//nga ba phai
		setColor(15, 6);
		gotoxy(55,1); cout<<"THONG KE SO LUOT THUC HIEN CHUYEN BAY CUA TUNG MAY BAY";
		setColor(14, 0);
		gotoxy(21,10); cout<<"SO HIEU MAY BAY";
		gotoxy(50,10);	cout<<"SO LUOT THUC HIEN CHUYEN BAY";
//		gotoxy(150,21);	cout<<"Press ESC to exit";
		setColor(14, 3);
		gotoxy(100, 12); cout << "   LEFT   ";
		gotoxy(100, 13); cout << "   RIGHT  ";
		gotoxy(100, 17); cout << "           ";
		gotoxy(100, 18); cout << "    ESC    ";
		gotoxy(100, 19); cout << "           ";
		setColor(11, 0);
		gotoxy(112, 12); cout << "chuyen trang";
		gotoxy(112, 18); cout << "thoat";
		
		int toadoy= 12;
		for (int i = 0; (i <= 14) && (i<=Counted.n); i++)
		{
			gotoxy(25,toadoy); cout<<Counted.data[i]->SoHieu;
			gotoxy(62,toadoy); cout<<Counted.data[i]->SoCho;
			toadoy++;
		}
		
		if (Counted.n > 14)
		{
			setColor(14, 3);
			gotoxy(100, 12); cout << "   LEFT   ";
			gotoxy(100, 13); cout << "   RIGHT  ";			// Có trang moi can sang trang
			setColor(3,0);
			int trangHienTai = 1;
			int tongsoTrang,keyboard;
			tongsoTrang = ((Counted.n - 1) / SOLUONGMOITRANG) + 1;
			int choice = 0;
			while (true)	
			{
				while (kbhit())
				{
					fflush(stdin);
					keyboard = getch();
					if (keyboard == 0) keyboard = getch();
					switch (keyboard) 
					{
						case KEY_RIGHT:if (trangHienTai < tongsoTrang)
						{
							toadoy = 12;
							XoamanhinhH();	
							trangHienTai++;
							choice = (trangHienTai -1)* SOLUONGMOITRANG;
							for (int i = choice; (i <= choice + 14) && (i<= Counted.n) ; i++)
							{
								gotoxy(25,toadoy); cout<<Counted.data[i]->SoHieu;
								gotoxy(62,toadoy); cout<<Counted.data[i]->SoCho;
								toadoy++;
							}
						
						}
						break;
						case KEY_LEFT:	if (trangHienTai > 1)
						{
							toadoy = 12;
							XoamanhinhH();	
							trangHienTai--;
							choice = (trangHienTai -1)* SOLUONGMOITRANG;
							for (int i = choice; (i <= choice + 14) ; i++)
							{
								gotoxy(25,toadoy); cout<<Counted.data[i]->SoHieu;
								gotoxy(62,toadoy); cout<<Counted.data[i]->SoCho;
								toadoy++;
							}
							
						}
						break;
						case ESC: 
						{
						return false;
						break;
						}
					}
				}
			}
		}
	}
	int c;
	c = getch();
	//	return true;
}

void MenuDSMB(AirPlanes &DSMB, listFlight &cb)
{
	ShowCur(false);
	int flag = 0;
	do
	{
	system("cls");
	VeKhungCH(0,0,61,29,1);
	gotoxy(10,1);
	setColor(6,0);
	cout<<"============ DANH SACH MAY BAY ===========";
	
	gotoxy (85,0);
	cout <<"MENU";
	gotoxy (70,2);
	setColor(2,0);
	cout<<"1. Them may bay vao danh sach";
	gotoxy(70,4);
	cout<<"2. Xoa may bay khoi danh sach";
	gotoxy(70,6);
	cout<<"3. Hieu chinh thong tin may bay";
	gotoxy(70,8);
	cout<<"4. Xem danh sach may bay";
	gotoxy(70,10);
	cout<<"5. Thoat";
	setColor(3,0);
		int a = KhungChon(70,2,35,5);
		switch (a)
		{
			case 1:
			{
				AddDSMB(DSMB);
				SaveMayBay(DSMB);
				break;
			}
			case 2:
			{
				Del(DSMB,cb);
				SaveMayBay(DSMB);
				break;
			}
			case 3:
			{
				EditDSMB(DSMB,cb);
				SaveMayBay(DSMB);
				break;	
			}
			case 4:
			{
				XuatDSMB(DSMB);
				TextColor(14);
				break;
			}
			case 5:
			{
				SaveMayBay(DSMB);
				flag = 1;
				break;
			}
		}
	}
	while (flag == 0);
	ShowCur(true);
}

void MenuFirst(AirPlanes &mb, listFlight &cb, treeHanhKhach &hk){
	ShowCur(false);
	while (true){
		Intro();
		MainMenu(tpMenuChinh, sizeof(tpMenuChinh) / sizeof(string));
		Display3();
		int choice = ChooseMenu(tpMenuChinh, sizeof(tpMenuChinh) / sizeof(string));
		tongsoTrangCB = cb.n / SOLUONGMOITRANG + 1;
		tongsoTrangHK = SoHanhKhach / SOLUONGMOITRANG + 1;
		switch (choice){
			case -1: return;
			case 0:
				{
					system("cls");
					MenuDSMB(mb,cb);
					//SaveMayBay(mb);
					break;
				}
			case 1:
				{
					system("cls");
					MenuQlyChuyenBay(cb, mb);
					//SaveChuyenBay(cb);
					break;
				}
			case 2:
				{
					system("cls");
					MenuQlyHanhKhach(hk);
					//SaveHanhKhach(hk);
					break;
				}
			case 3:
				{
					if (DatVe(hk, cb) == false) continue;
					//SaveChuyenBay(cb);
					break;
				}
			case 4:
				{
					if (HuyVe(hk, cb) == false) continue;
					//SaveChuyenBay(cb);
					break;
				}
			case 5:
				{
					if (HanhKhach1ChuyenBay(cb, hk) == false) continue;
					break;
				}
			case 6:
				{
					system("cls");
					CauF(cb);
					break;
				}
			case 7:
				{
					if (VeTrongCuaChuyenBay(cb) == false) continue;
					break;
				}
			case 8:
				{
					system("cls");
					CauH(cb);
					break;
				}
		}
		system("cls");
	}
}

//==============================================================================
int main() {
	resizeConsole(2000,1000);
	system("color 0B");
	
	treeHanhKhach r;
	listFlight cb;
	Flight data;
	AirPlanes dsmb;
	
	Initialize(r);
	
	LoadHanhKhach(r);
	LoadMayBay(dsmb);
	LoadChuyenBay(cb);

	MenuFirst(dsmb, cb, r);
	
	SaveMayBay(dsmb);
	SaveChuyenBay(cb);
	SaveHanhKhach(r);

	return 0;
}

