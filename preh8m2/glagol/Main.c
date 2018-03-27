/*
����������-8�

������� �� ��������� �� ����� ����� ������-82/8� (� ����� �� ���������) � IBM-PC ��� ������� ������.
����� ������: 6.2001; Pascal (MS DOS) � BASIC (Apple DOS 3.3)
����� ���������: 1.0, 12.2002 (MS Windows-32, BASIC)
��������: 1.1, 1.2004 (MS Windows-32, BASIC)

9.8.2002 - �������� �� ���������� ������.
22.12.2002 - ����� ������ ��������, �� �� �� ������ ����������
������ ������ �����. ���� �� �� �� ������� �� ��������.

26.12.2002 - ����� �������� �� ����������� ������

10.1.2004 - ������ 1.1; ��������� ������ ��� ���������� ��� ����� ����; �������� �������

*/

#include <windows.h>
#include <string.h>
#include <io.h>
#include <process.h> //_spawn_..., _exec...
#include <winuser.h> //setwindowtext
//#include <mmsystem.h> //����

#pragma hdrstop

#include "Main.h"

#define IDC_MAIN_TEXT   1001
#define ID_BUTTON1      1   //���������_1
#define RAZSHIRENIE     ".d"    //����������
#define FALSE 0
#define TRUE  1
#define DA    1
#define NE    0
#define OS   128        //��������� �� ������� ������ ����
#define maxa 2000000	//�� �� ���� ������ �� ������


#define ZAGLAVIE         "����������-8�"
#define ZAGLAVIE_ENG_N   "Transferrer-8M"
#define GRESHKA_N        "������"
#define VUOB_N           "����������-8� � ������� �� ����������� ��������� �� ����� �� ������-82 � 8M ��� IBM-PC, ��������� �� ����� �������� (���).\n����� �������� ������: ��� 2001.\n����� �������: 1.0 �� 26-�� �������� 2002\n1.1 �� 10.1.2004"
#define ZA_PREH_N        "��������"
#define VUOB_ENG_N       "TRANSFERRER - a programme that allows diskettes from Apple\\ to be transferred to a PC"
#define ZA_PREH_ENG_N    "About"
#define OBEDINI          "#" //���� �� ������� �� ���������� �������
#define IZPULNEN         " - ��������."

#define NEPISHI 1

static char g_szClassName[] = "MyWindowClass";
static HINSTANCE g_hInst = NULL;
HWND bmp, bmp2;   //���� �� "������"
HWND nadpis;     //"����������-8�"
HWND natis;
HWND pole;
HMENU h_menu;    //�������
char put[255];
char dada[16000]; //�������� � ��������� ����
bool ezik = 1; //1 - ���������, 0 - ���������
int broi;
HDROP drop;


//��������
#define PRAZNO        5

#define PREH_X        PRAZNO
#define PREH_Y        PRAZNO
#define PREH_SHIR     243
#define PREH_VIS      32

#define NATIS_X      POLE_X + POLE_SHIR + PRAZNO
#define NATIS_Y      (POLE_Y + POLE_VIS)/2
#define NATIS_SHIR   40
#define NATIS_VIS    20

#define PROZ_X       20
#define PROZ_Y       20
#define PROZ_SHIR    PREH_X + PREH_SHIR + PRAZNO
#define PROZ_VIS     210    //POLE_Y + POLE_VIS + PRAZNO
#define ZNAK_X       1
#define ZNAK_Y       50

#define POLE_X        40
#define POLE_Y        PREH_Y + PREH_VIS + PRAZNO
#define POLE_SHIR     160//230
#define POLE_VIS      110

#define CR 13             //"������� �� ���������"
#define LF 10             //��� ���
char novredm[2];

//8M
typedef unsigned char uchar;

uchar dve_na[] = {1,2,4,8,16,32,64,128};
uchar os     = OS;
uchar nula   = 127;
uchar nul    = 48;
uchar edn    = 49;
uchar tonnac = 50;
uchar nad; // ��� �������� ����
uchar pod; // ��� �������� ����
uchar biti; //����� ��� �������
uchar bitove;
uchar bait; //��� ����
uchar broo,pro;
uchar ff=255;
uchar tek;

uchar* poin; 	//����� []
uchar* dekod;  //������� ������

char nov[255];
char pyt[255];

int masauk,proba;
long tekbyte;
long siz;
long m, poi;
long i;

unsigned bai, poinuk;
bool podd, poddpred;

FILE *poif;
FILE *vun;

void chetipoi();
void zapylbait();
void iztrii();
int vurti();
int otvorif();

void poch()
{
novredm[0]=CR;       //��� ���
novredm[1]=LF;
}


//�� �� ������� ����������� �� ������� � �����������, �� ����
//����� ����������� �� �������� ���������
void vurti_windows(char *im)
{

strcpy(&pyt[0], im);
vurti();            //������� ���������������
}

int osnova_cheti(char* ime)	//���� �������� ������ � ������ ��� �����
{
FILE *f;
char c[255];
short p;        //�������
short int pr = 0, zp =0;

f = fopen(&ime[0], "rt");

   do{
if (!fscanf(f, "%s", &c[0])) return(DA);  //��� ���� ����� ������ �� ����

if (strcmp(&c[0], OBEDINI) == 0)	//��� �� ������, ����� �� �� �������� �� �������
   {
   return(DA);
   }

if (strcmp(&c[0], "0") == 0)	//����
   {
   return(DA);
   }

vurti_windows(&c[0]);

}while (p < 1000);// �� ��� �� �� �����

}
//--���� �� ����_������--//

void mahniraz(char *c)    //������ ������� � ����, 22.12.2002, ���� ����������
{
short m = 0;

while (c[m] != 0) (c[m] != 46) ? m++ : c[m] = 0;

//46 == '.'
}

void izchisti()
{
 broi=0;
 poin = new unsigned char[maxa];
 dekod = new unsigned char[145000];//������� ����
}

unsigned char stepen(unsigned char stp)
{
 return(dve_na[stp]);
}

void zapishi()
{
 FILE *zap;
 char *greshnoli = new char [20];
 long fsz;
 int  razi;

zap = fopen(nov,"wb");		//������� ������ � ����������� ����������
fwrite(dekod,1,broi-1,zap);	//���������� ���� � �� ������ �� ������ - �������� ��
fclose(zap);

 _finddata_t fi2;

_findfirst(nov, &fi2);
char gaga[255];
wsprintf(&gaga[0],"%s, %d %s",fi2.name, fi2.size, /*greshnoli,*/ &novredm[0]);
strcat(&dada[0], gaga);
SetWindowText(pole, &dada[0]);	//������� � �������� ���� �������
}

void usili()		//�������� �� �����
{
int m;
uchar max = os, min = os;

for (m = 300; m<siz; m+= 3)	//���������� ����� �� ��������
{
if (poin[m]>max) max = poin[m];
}

if (max<140) os = 130;
if (max>140) os = 133;

FILE *f;
f = fopen ("_i.txt", "a");
fprintf(f, "\n%d",max);
fclose(f);

}

void chetipoi()
{
 long sss = siz-m;

 fseek(poif,m,0);

 if (sss >= maxa)
                 {
                  fread(poin,1,maxa,poif);
                  poi=m+maxa;
                 };
 if (sss < maxa)
                 {
                  fread(poin,1,(siz-m),poif);
                  poi = m + (siz-m);
                };

 poinuk=0;
 usili();

}

void zapylbait()	//��������� �� ���� �������������� ���� � �� ������� ����
{
 dekod[broi] = bait;
 broi++;

  pro = pro + bait;
  bitove = 0;
  bait = 0;
}

/*
int zapkude(char* c, int a, int stop)
{
if (NEPISHI) return 0;
FILE* fff;
fff = fopen("_zapis.txt", "at");
fprintf(fff, "\n %s, %d",c,  a);
fclose(fff);
if(stop) exit(0);
}
*/

int otvorif() //���� ������ ����� ��������
{
uchar edn,nul;
bool bobo=0;
bool pryv=1;
char ch;
long bibi;	//�����
char *niz[255];


 izchisti();
 pro=255;
 bibi=0;
 pryv=true;
 edn=1;
 nul=0;
 m=44;		//�������� ��� �������� �����
 poinuk=0;
 bait=0;
 bitove=0;
 broo=0;

  _finddata_t fi;
  int dali;

if (!_findfirst(pyt, &fi))
       {
		printf("File not found!");
		exit(0);
       }
 else	
 _findclose(dali);
 poif = fopen(pyt,"rb");        //���� �������
 siz = fi.size;
 chetipoi();			//������� ����� ������

 i = 44; // �������� ���������� �� �����������
 podd = 0; //false
 poddpred = podd;


 while (poin[poinuk]>127)
 {
 poinuk++;
 i++;
 };


//������ �� �������� ��� "1"

while(i<siz)
 {
  tek = poin[poinuk];
  podd = (tek > os);				        //��� ����?
  if ((podd) && (!poddpred)) broo=0;		//��� �������� �� �, ����� ��� ����
  if (podd) broo++;				//������� ���� �� ������� �� �����
  if ((!podd) && (poddpred))			//���� �� ���
    if ((broo>0) &&  (broo<3)) break; //{zapkude("BEGIN!",i,0); break;}
  poddpred = podd;
  i++;
  poinuk++;
 }

 poddpred = 0;
 broo = 0;

 while(i<siz)	//�������������
  {
   i++;
   m++;
   poinuk++;
   tek = poin[poinuk];
   podd = (tek > os);				        //��� ����?
   if ((podd) && (!poddpred)) broo=0;		//��� �������� �� �, ����� ��� ����

   if (podd) broo++;				//���� ������� �� ������� ����
   if ((!podd) && (poddpred))	    //���� �� ���� (���)
      {
       //zapkude("BROO", broo, 0);
         if ((broo>2) && (broo<5))
                                           {
                                            //zapkude("I", i, 0);
                                            bait+=stepen(7-bitove);			//��� � 2 -> 0, ��� � 5 -> ���������
                                            bitove++;
                                           }
      else
      if ((broo<3) && (broo>0)) bitove++;	//������ ���� "0"

      if (bitove==8) {
                      //zapkude("BYTE", bait, 0); //��������� ������ ������
                      zapylbait();
                     }
  }
  poddpred = podd;

  if (m==poi) chetipoi();					//���� ���� ����� �� ������� - �� �� �������� �� ��������

 }//���� �� _while_

fclose(poif);
zapishi();						//������ ��������������� �����
}

int vurti() //������ �������
{
 char zna=0;
  strcpy(nov, pyt);
  mahniraz(nov);   //������� ������ ���� ".'
  strcat(nov, RAZSHIRENIE);   //������ ���� ����������
 masauk = 0;
 otvorif();
}

void osvobodi()           //�������� �������
{
delete[] poin;
delete[] dekod;
}


BOOL LoadFile(HWND hEdit, LPSTR pszFileName)	//��������� �� Win32; �������� �� ������� � �� "Dev C++"
{
   HANDLE hFile;
   BOOL bSuccess = NE;

   hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
      OPEN_EXISTING, 0, 0);

   if(hFile != INVALID_HANDLE_VALUE)
   {
      DWORD dwFileSize;
      dwFileSize = GetFileSize(hFile, NULL);

      if (dwFileSize != 0xFFFFFFFF)
      {
         strcpy(&pyt[0],pszFileName);     //����
         vurti();                        //��������� ������
         bSuccess = DA;
      }
      CloseHandle(hFile);
   }
  return bSuccess;
}

BOOL DoFileOpenSave(HWND hwnd, BOOL bSave, int kazba)     //����� - ���������. 0 - ������� ���� ����������; 1 - ������
{
   OPENFILENAME ofn;
   char szFileName[MAX_PATH];

   ZeroMemory(&ofn, sizeof(ofn));
   szFileName[0] = 0;

   ofn.lStructSize = sizeof(ofn);
   ofn.hwndOwner = hwnd;

if (ezik)		//������������� ���������� �� ������ � �������� ��������
   ofn.lpstrFilter = "������� ������ (*.wav)\0*.wav\0������ ������� (*.*)\0*.*\0\0";
else
  ofn.lpstrFilter = "Wave records (*.wav)\0*.wav\0All files (*.*)\0*.*\0\0";
if (kazba)
   ofn.lpstrFilter = "�������� ������� (*.txt)\0*.txt\0������ �������\0*.*\0\0";

   ofn.lpstrFile = szFileName;
   ofn.nMaxFile = MAX_PATH;
   ofn.lpstrDefExt = "wav";

   if(bSave)
   {
   ofn.lpstrDefExt = "txt";

if (ezik)
   ofn.lpstrFilter = "�������� ������� (*.txt)\0*.txt\0������ �������\0*.*\0\0";
else
   ofn.lpstrFilter = "Text files (*.txt)\0*.txt\0All files\0*.*\0\0";

      ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY |
         OFN_OVERWRITEPROMPT;
   }
   else
   {
      ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
      if(GetOpenFileName(&ofn))
      {
      if (kazba == 1) osnova_cheti(szFileName);    //������ ���������� �� ���� �����
      else
         {
         if(!LoadFile(GetDlgItem(hwnd, IDC_MAIN_TEXT), szFileName))
          {
         if (ezik) MessageBox(hwnd, "��������� ������!", GRESHKA_N, MB_OK | MB_ICONEXCLAMATION);
         else      MessageBox(hwnd, "Load of file failed.", "Error", MB_OK | MB_ICONEXCLAMATION);
         return FALSE;
          }
        }
      }
   }
   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
   switch(Message)
   {
      case WM_CREATE:

     poch();
     pole = CreateWindowEx(WS_EX_ACCEPTFILES, "EDIT", "",	//������ ���������� ������� �������
            WS_VISIBLE | WS_CHILD | WS_BORDER  |WS_CLIPSIBLINGS| WS_TABSTOP
            |ES_MULTILINE| WS_VSCROLL,
            POLE_X, POLE_Y, POLE_SHIR, POLE_VIS,
            hwnd, (HMENU)IDC_MAIN_TEXT, g_hInst, NULL);
            DragAcceptFiles(hwnd, TRUE);

     nadpis = CreateWindow("STATIC", "ID_BMP2",
         WS_VISIBLE | SS_BITMAP | WS_CHILD,
          PREH_X, PREH_Y , PREH_SHIR, PREH_VIS,
          hwnd, (HMENU)ID_BMP2, g_hInst, NULL);

/*          //����������
    natis = CreateWindow("BUTTON", "����",
    WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON |WS_TABSTOP,
    NATIS_X, NATIS_Y, NATIS_SHIR, NATIS_VIS, hwnd, (HMENU) ID_NATIS, g_hInst, NULL);
*/

      bmp = CreateWindow("STATIC", "ID_BMP",
         WS_VISIBLE | SS_BITMAP | WS_CHILD,
          ZNAK_X, ZNAK_Y, CW_USEDEFAULT, CW_USEDEFAULT, //BMP_SHIR, BMP_VIS,
          hwnd, (HMENU)ID_BMP, g_hInst, NULL);

      bmp2 = CreateWindow("STATIC", "ID_BMP3",
         WS_VISIBLE | SS_BITMAP | WS_CHILD,
          203, ZNAK_Y, CW_USEDEFAULT, CW_USEDEFAULT, //BMP_SHIR, BMP_VIS,
          hwnd, (HMENU)ID_BMP3, g_hInst, NULL);


         SendDlgItemMessage(hwnd, IDC_MAIN_TEXT, WM_SETFONT,
            (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));


      break;

	case WM_DROPFILES:	//��������� ������
	{
             UINT ifi = 0xFFFFFFFF;     //���� �� ������� �������
             UINT buf = 0;
             UINT resu = 0;
             char ime[255];
             LPTSTR imel;
             
	ifi  = DragQueryFile((HDROP) wParam, 0xFFFFFFFF, &ime[0], buf); //���� �������
	buf  = DragQueryFile((HDROP) wParam, resu, NULL, buf);           // (������ �� ���������-1)
	resu = DragQueryFile((HDROP) wParam, ifi-1, &ime[0], buf+1);
	strcpy(&pyt[0], &ime[0]);
	vurti();
	}

      break;

      case WM_COMMAND:
         switch(LOWORD(wParam))
         {

         case CM_CHETI_EDIN:
               DoFileOpenSave(hwnd, FALSE,0);
            break;

         case CM_CHETI_ZARUKI:
               DoFileOpenSave(hwnd, FALSE, 1);
            break;

            case CM_FILE_EXIT:
               PostMessage(hwnd, WM_CLOSE, 0, 0);
            break;

            case CM_KRATKO:
MessageBox(0, VUOB_N, ZA_PREH_N, 0);

/*����������� ������ � ������, ���� ��
if (ezik) MessageBox(NULL, VUOB_N, ZA_PREH_N, 0); else
              MessageBox(NULL, VUOB_ENG_N, ZA_PREH_ENG_N, 0);
//���� - ���� PlaySound("n.wav", 0, SND_FILENAME | SND_ASYNC);
*/              break;

            case CM_MREJ:
            ShellExecute(hwnd, "open", "http://tosh.data.bg/preh8m", NULL, NULL, SW_MAXIMIZE);//);
            break;

            case CM_DULGO:
            ShellExecute(hwnd, "open", "8m-dulgo.htm", NULL, NULL, SW_MAXIMIZE);
            break;

            case CM_EZIK:
            ezik = !ezik;
            char izbir[50];
            if (ezik) strcpy(&izbir[0], "MAINMENU");
            else strcpy(&izbir[0],"MAINMENU2");

              DestroyMenu(h_menu);             //����������� ��������
              h_menu = CreateMenu();           //��������� ���
             h_menu = LoadMenu(g_hInst, &izbir[0]);  //��������� �� � �����
             SetMenu(hwnd, h_menu);     //� �� �������� ��� ������� ��������
            break;

            }
      break;
      case WM_CLOSE:
         osvobodi();
         DestroyWindow(hwnd);
      break;
      case WM_DESTROY:
         PostQuitMessage(0);
      break;
      default:
         return DefWindowProc(hwnd, Message, wParam, lParam);
   }
   return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
   LPSTR lpCmdLine, int nCmdShow)
{
   WNDCLASSEX WndClass;
   HWND hwnd;
   MSG Msg;

   g_hInst = hInstance;

   WndClass.cbSize        = sizeof(WNDCLASSEX);
   WndClass.style         = 0;
   WndClass.lpfnWndProc   = WndProc;
   WndClass.cbClsExtra    = 0;
   WndClass.cbWndExtra    = 0;
   WndClass.hInstance     = g_hInst;
   WndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
   WndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
   WndClass.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
   WndClass.lpszMenuName  = NULL; //"MAINMENU2";
   WndClass.lpszClassName = g_szClassName;
   WndClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

   if(!RegisterClassEx(&WndClass))
   {
      MessageBox(0, "Window Registration Failed!", "Error!",
         MB_ICONEXCLAMATION | MB_OK | MB_SYSTEMMODAL);
      return 0;
   }

  h_menu = CreateMenu();
  h_menu = LoadMenu(g_hInst, "MAINMENU");

   hwnd = CreateWindowEx(
      0,
      g_szClassName,
      ZAGLAVIE,
      WS_OVERLAPPEDWINDOW| WS_BORDER | WS_CLIPCHILDREN | WS_TABSTOP,
      PROZ_X, PROZ_Y, PROZ_SHIR, PROZ_VIS,
      NULL, h_menu, g_hInst, NULL);

   if(hwnd == NULL)
   {
      MessageBox(0, "Window Creation Failed!", "Error!",
         MB_ICONEXCLAMATION | MB_OK | MB_SYSTEMMODAL);
      return 0;
   }

   ShowWindow(hwnd, nCmdShow);
   UpdateWindow(hwnd);

   while(GetMessage(&Msg, NULL, 0, 0))
   {
      TranslateMessage(&Msg);
      DispatchMessage(&Msg);
   }
   return Msg.wParam;
}

