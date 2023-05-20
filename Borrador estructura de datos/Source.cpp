#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <locale.h>
#include <Windows.h>
#include <CommDlg.h>
#include <Commctrl.h>
#include <ctime>
#include "resource.h"
using namespace std;

HWND ghDlg = 0;
HWND h_edit;
HWND h_boton;
HWND h_radio;
HWND h_listbox;
HWND h_combo;
HWND h_PicControl;
//HWND calendario;
//SYSTEMTIME st;
//HINSTANCE regis;
HMENU h_menu;
HBITMAP bmp;
HINSTANCE INSTANCIA;
OPENFILENAME ofn;
BOOL numOK;

char zFile[MAX_PATH];
char FileTitle[MAX_PATH];

struct Persona {
	char a_ma[15];
	char a_pa[15];
	char name[15];
	char ID[15];
	char estadocivil[15];
	char fecha_nac[15];
	char direccion[200];
	char genero[15];
	char curp[20];
	char tel[15];
	char trabajo[15];
	char nomC[52];
	char path[MAX_PATH];
	Persona* anterior = nullptr;
	Persona* siguiente = nullptr;
};
Persona *primero = nullptr;
Persona* ultimo = nullptr;
Persona* temporal = nullptr;

struct Vacuna {
	char tipo[15];
	char marca[15];
	char num_dosis[15];
	char clave_v[15];
	char desc[MAX_PATH];
	float precio;
	Vacuna* anterior = nullptr;
	Vacuna* siguiente = nullptr;
};
Vacuna* primer = nullptr;
Vacuna* ultim = nullptr;
Vacuna* tempora = nullptr;

struct User {
	int clave_u;
	char contraseña[15];
	char a_materno[15];
	char a_paterno[15];
	char nombres[15];
	char namecom[52];
	User* anterior = nullptr;
	User* siguiente = nullptr;
};
User* prime = nullptr;
User* ulti = nullptr;
User* tempor = nullptr;

struct Carnet {
	char Curp[20];
	char vacuna[15];
	char No_dosis[15];
	char date[15];
	char lote[15];
	char lugar[15];
	int ID_carnet;
	Carnet* anterior = nullptr;
	Carnet* siguiente = nullptr;
	Persona datos;
};
Carnet* prim = nullptr;
Carnet* ult = nullptr;
Carnet* tempo = nullptr;


void guardarPertxt();
void guardarVtxt();
void guardarUtxt();
void guardarCartxt();
void guardarPer();
void guardarV();
void guardarU();
void guardarCar();
void leer_Per();
void leer_Vac();
void leer_User();
void leer_Carnet();
void dvacio(char datop[70]);
Carnet* getMid(Carnet* first, Carnet* last);
bool buscarlistaBinaria(Carnet* first, Carnet* last, int n);
void swap(Carnet* a, Carnet* b);
Carnet* particion(Carnet* primero, Carnet* ultimo);
void quickSort(Carnet* primero, Carnet* ultimo);
void imprimirLista(Carnet* cabeza, HWND hwnd);
void swapNodes(Carnet* a, Carnet* b);
void heapifyDown(Carnet* start, Carnet* end);
void heapSort(Carnet* start, Carnet* end);
void printList(Carnet* start, Carnet* end, HWND hwnd);
void reporte();

char gender[3][9] = { "Mujer","Hombre","Otro" };
char estcivil[4][15] = { "Soltero(a)","Casado(a)","Divorciado(a)","Viudo(a)" };
char dosisop[4][4] = { "1","2","3","4+" };
char datos[12][21] = {};
char INFO_U[14][100] = {};
char direcc[200] = {};
char de[MAX_PATH] = {};
char nuevo[100], conteiner[52], dummy[15],datop[70],iniciarse[52],textolistcorto[100],IDCHAR, curp[20];
int datonum1, datonum2,ID_CARNET,numeroID,c_user,prueba=0,tamaño,k,deno;
bool e = false;
char temp[52],pivote [52];
int tempnum;
string n = "Reporte",PATHE="";
int u;
const char* charStr;

//Contadores
float dno1;
int i,a,cur,detonante= 0;
fstream Archivo;
ofstream archivo;
ifstream txt;

BOOL CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Menu(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK RegistroU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK RegistroV(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK RegistroP(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK RegistroC(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ListadoU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK CambioU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK ListadoV(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK CambioV(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ListadoP(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK CambioP(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ListadoC(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK CambioC(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Reporte(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	ghDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)WindowProc);
	ShowWindow(ghDlg, nCmdShow);
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (GetMessage(&msg, 0, 0, 0))
	{
		if (ghDlg == 0 || !IsDialogMessage(ghDlg, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}
BOOL CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_INITDIALOG:
		h_boton = GetDlgItem(hwnd, iniciarsesion);
		h_boton = GetDlgItem(hwnd, regis);
		h_edit = GetDlgItem(hwnd, nameuser);
		h_edit = GetDlgItem(hwnd, contra);
		setlocale(LC_CTYPE, "Spanish");
		leer_Per();
		leer_Vac();
		leer_User();
		leer_Carnet();
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case iniciarsesion:

			GetDlgItemText(hwnd, nameuser, iniciarse, 52);
			GetDlgItemText(hwnd, contra, datos[2], 15);

			if (prime == nullptr) {
			MessageBox(hwnd, "No hay usuarios registrados aun", "MENSAJE", MB_ICONERROR);
			}

			else {
				ulti = prime;
				while (ulti) {
					if (strcmp(ulti->namecom, iniciarse) == 0 && strcmp(ulti->contraseña, datos[2]) == 0) {
						strcpy_s(iniciarse, 52, ulti->namecom);
						DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG2), 0, (DLGPROC)Menu);
					}
					else {
						ulti = ulti->siguiente;
					}
				}

				if (ulti == nullptr) {
					MessageBox(hwnd, "El usuario es incorrecto", "MENSAJE", MB_ICONERROR);
				}
			}

			break;

		case regis:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG3), 0, (DLGPROC)RegistroU);
			break;
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return FALSE;
}
BOOL CALLBACK Menu(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_menu = LoadMenu(INSTANCIA, MAKEINTRESOURCE(IDR_MENU1));
		h_edit = GetDlgItem(hwnd, nombreuser);
		SetMenu(hwnd, h_menu);
		SetDlgItemText(hwnd, nombreuser, iniciarse);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_USUARIO_REGISTRODEUSUARIO:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG3), 0, (DLGPROC)RegistroU);
			break;

		case ID_USUARIO_LISTADODEUSUARIO:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG7), 0, (DLGPROC)ListadoU);
			break;

		case ID_USUARIO_EDICIONDEUSUARIO:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG7), 0, (DLGPROC)ListadoU);
			break;

		case  ID_USUARIO_BAJADEUSUARIO:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG7), 0, (DLGPROC)ListadoU);
			break;

		case ID_VACUNA_REGISTRODEVACUNA:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG4), 0, (DLGPROC)RegistroV);
			break;

		case ID_VACUNA_LISTADODEVACUNA:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG9), 0, (DLGPROC)ListadoV);
			break;

		case ID_VACUNA_EDICIONDEVACUNA:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG9), 0, (DLGPROC)ListadoV);
			break;

		case ID_VACUNA_BAJADEVACUNA:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG9), 0, (DLGPROC)ListadoV);
			break;

		case ID_PERSONA_REGISTRODEPERSONA:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG5), 0, (DLGPROC)RegistroP);
			break;

		case ID_PERSONA_LISTADODEPERSONA:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG11), 0, (DLGPROC)ListadoP);
			break;

		case ID_PERSONA_EDICIONDEPERSONA:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG11), 0, (DLGPROC)ListadoP);
			break;

		case ID_PERSONA_BAJADEPERSONA:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG11), 0, (DLGPROC)ListadoP);
			break;

		case ID_CARNET_REGISTRODECARNETDEVACUNACION:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG6), 0, (DLGPROC)RegistroC);
			break;

		case ID_CARNET_LISTADODECARNETDEVACUNACION:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG13), 0, (DLGPROC)ListadoC);
			break;

		case ID_CARNET_EDICIONDECARNETDEVACUNACION:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG13), 0, (DLGPROC)ListadoC);
			break;
		case ID_CARNET_BAJADECA:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG13), 0, (DLGPROC)ListadoC);
			break;
		case ID_SALIR_SALIR40018:
			DestroyWindow(hwnd);
			PostQuitMessage(0);
			break;
		}
		break;

		break;
	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK RegistroU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, nameu);
		h_edit = GetDlgItem(hwnd, ap);
		h_edit = GetDlgItem(hwnd, am);
		h_edit = GetDlgItem(hwnd, contras);
		h_edit = GetDlgItem(hwnd, nombreuser2);
		h_boton = GetDlgItem(hwnd, G_RU);
		h_boton = GetDlgItem(hwnd, R_RU);
		SetDlgItemText(hwnd, nombreuser2, iniciarse);
		//ESTO ES DE LA FOTO
		//h_PicControl = GetDlgItem(hwnd, FOTON4);
		//bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		//SendDlgItemMessage(hwnd, FOTON4, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		//SetDlgItemText(hwnd, NOM4, Unom);

		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case G_RU:
			prueba = 0;
			detonante = 0;
			GetDlgItemText(hwnd,nameu, datos[1], 15);
			GetDlgItemText(hwnd,ap, datos[2], 15);
			GetDlgItemText(hwnd,am, datos[3], 15);
			GetDlgItemText(hwnd,contras, datos[4], 15);
			datonum1 = GetDlgItemInt(hwnd, contras2, &numOK, FALSE);
			if (prime != nullptr) {
				while (detonante == 0) {
					if (prime) {
						tempor = prime;
						while (tempor) {
							if (tempor->clave_u == datonum1)
							{
								prueba=1;
							}
							tempor = tempor->siguiente;
						}
						detonante = 1;
					}
				}
			}
			dvacio(datos[1]);
			dvacio(datos[2]);
			dvacio(datos[3]);
			dvacio(datos[4]);

			if (prueba == 0) {
				if (prime == nullptr) {
					prime = new User;
					strcpy_s(prime->nombres, 15, datos[1]);
					strcpy_s(prime->a_paterno, 15, datos[2]);
					strcpy_s(prime->a_materno, 15, datos[3]);
					strcpy_s(prime->contraseña, 15, datos[4]);
					prime->clave_u = datonum1;
					strcpy_s(conteiner, 15, "");
					strcat_s(conteiner, prime->nombres);
					strcat_s(conteiner, " ");
					strcat_s(conteiner, prime->a_paterno);
					strcat_s(conteiner, " ");
					strcat_s(conteiner, prime->a_materno);
					strcpy_s(prime->namecom, 52, conteiner);
					prime->siguiente = nullptr;
					prime->anterior = nullptr;
					ulti = prime;
				}
				else {
					ulti = prime;
					while (ulti->siguiente != nullptr) {
						ulti = ulti->siguiente;
					}
					ulti->siguiente = new User;
					ulti->siguiente->siguiente = nullptr;
					ulti->siguiente->anterior = ulti;
					ulti = ulti->siguiente;
					strcpy_s(ulti->nombres, 15, datos[1]);
					strcpy_s(ulti->a_paterno, 15, datos[2]);
					strcpy_s(ulti->a_materno, 15, datos[3]);
					strcpy_s(ulti->contraseña, 15, datos[4]);
					ulti->clave_u = datonum1;
					strcpy_s(conteiner, 15, "");
					strcat_s(conteiner, ulti->nombres);
					strcat_s(conteiner, " ");
					strcat_s(conteiner, ulti->a_paterno);
					strcat_s(conteiner, " ");
					strcat_s(conteiner, ulti->a_materno);
					strcpy_s(ulti->namecom, 52, conteiner);
				}
				MessageBox(hwnd, "El registro se ha realizado", "MENSAJE", MB_ICONINFORMATION);
				guardarUtxt();
				guardarU();
			}
			else {
				MessageBox(hwnd, "Ha dejado espacios en blanco o la clave de usuario se ha repetido", "MENSAJE", MB_ICONINFORMATION);

			}
			EndDialog(hwnd, wParam);
			break;

		case R_RU:
			EndDialog(hwnd, wParam);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK RegistroV(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, tv);
		h_edit = GetDlgItem(hwnd, m);
		h_edit = GetDlgItem(hwnd, cv);
		h_edit = GetDlgItem(hwnd, d);
		h_edit = GetDlgItem(hwnd, ninero);
		h_edit = GetDlgItem(hwnd, nombreuser3);
		h_boton = GetDlgItem(hwnd, G_VA);
		h_boton = GetDlgItem(hwnd, R_VA);
		h_combo = GetDlgItem(hwnd, IDC_COMBO1);
		SetDlgItemText(hwnd, nombreuser3, iniciarse);
		//ESTO ES DE LA FOTO
		//h_PicControl = GetDlgItem(hwnd, FOTON4);
		//bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		//SendDlgItemMessage(hwnd, FOTON4, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		//SetDlgItemText(hwnd, NOM4, Unom);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case G_VA:
			prueba = 0;
			detonante = 0;
			GetDlgItemText(hwnd, tv, datos[1], 15);
			GetDlgItemText(hwnd, m, datos[2], 15);
			GetDlgItemText(hwnd, d, de, MAX_PATH);
			GetDlgItemText(hwnd, cv, datos[4], 15);
			dno1 = GetDlgItemInt(hwnd, ninero, &numOK, FALSE);
			if (primer != nullptr) {
				while (detonante == 0) {
					if (primer) {
						tempora = primer;
						while (tempora) {
							if (strcmp(tempora->marca,datos[2])==0)
							{
								prueba = 2;
							}
							tempora = tempora->siguiente;
						}
						detonante = 1;
					}
				}
			}
			dvacio(datos[1]);
			dvacio(datos[2]);
			dvacio(datos[3]);
			dvacio(datos[3]);
			dvacio(de);

			if (prueba == 0 && dno1 > 0) {
				if (primer == nullptr) {
					primer = new Vacuna;
					strcpy_s(primer->tipo, 15, datos[1]);
					strcpy_s(primer->marca, 15, datos[2]);
					strcpy_s(primer->num_dosis, 15, datos[3]);
					strcpy_s(primer->desc, MAX_PATH, de);
					primer->precio = dno1;
					//Validar que sea mayor a 0
					//---------------------
					strcpy_s(primer->clave_v,15, datos[4]);
					//Se debe checar que no se repita con ninguna ya registrada
					primer->siguiente = nullptr;
					primer->anterior = nullptr;
					ultim = primer;
				}
				else {
					ultim = primer;
					while (ultim->siguiente != nullptr) {
						ultim = ultim->siguiente;
					}
					ultim->siguiente = new Vacuna;
					ultim->siguiente->siguiente = nullptr;
					ultim->siguiente->anterior = ultim;
					ultim = ultim->siguiente;
					strcpy_s(ultim->tipo, 15, datos[1]);
					strcpy_s(ultim->marca, 15, datos[2]);
					strcpy_s(ultim->num_dosis, 15, datos[3]);
					strcpy_s(ultim->desc, MAX_PATH, de);
					ultim->precio = dno1;
					//validar que sea mayor a 0
					//---------------------
					strcpy_s(ultim->clave_v,15,datos[4]);
					//Se debe checar que no se repita con ninguna ya registrada
				}
				MessageBox(hwnd, "El registro se ha realizado", "MENSAJE", MB_ICONINFORMATION);
				guardarVtxt();
				guardarV();
			}

			else {
				MessageBox(hwnd, "Ha dejado espacios en blanco o se ha repetido la clave de  marca de vacuna", "MENSAJE", MB_ICONERROR);
			}

			EndDialog(hwnd, wParam);
			break;

		case R_VA:
			EndDialog(hwnd, wParam);
			break;

		case IDC_COMBO1:
			for (a = 0; a < 4; a++) {
				SendDlgItemMessage(hwnd, IDC_COMBO1, CB_INSERTSTRING, (WPARAM)a, (LPARAM)dosisop[a]);
			}
			
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IDC_COMBO1, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_COMBO1, CB_GETLBTEXT, cur, (LPARAM)datos[3]);
			}
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK RegistroP(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, np);
		h_edit = GetDlgItem(hwnd, app);
		h_edit = GetDlgItem(hwnd, ampersona);
		h_edit = GetDlgItem(hwnd, curpi);
		h_edit = GetDlgItem(hwnd, fnp);
		h_edit = GetDlgItem(hwnd, dp);
		h_edit = GetDlgItem(hwnd, telp);
		h_edit = GetDlgItem(hwnd, ine);
		h_edit = GetDlgItem(hwnd, work);
		h_edit = GetDlgItem(hwnd, nombreuser4);
		h_combo = GetDlgItem(hwnd, ec);
		h_combo = GetDlgItem(hwnd, gene);
		h_boton = GetDlgItem(hwnd, G_RP);
		h_boton = GetDlgItem(hwnd, R_RP);
		h_boton = GetDlgItem(hwnd, INGRESAFOTO1);
		h_PicControl = GetDlgItem(hwnd, FOTO1);
		SetDlgItemText(hwnd, nombreuser4, iniciarse);

		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case G_RP:
			prueba = 0;
			detonante = 0;
			GetDlgItemText(hwnd, np, datos[1], 15);
			GetDlgItemText(hwnd, app, datos[2], 15);
			GetDlgItemText(hwnd, ampersona, datos[3], 15);
			GetDlgItemText(hwnd, curpi, datos[4], 20);
			GetDlgItemText(hwnd, fnp, datos[11], 15);
			GetDlgItemText(hwnd, dp, direcc, 200);
			GetDlgItemText(hwnd, telp, datos[7], 15);
			GetDlgItemText(hwnd, ine, datos[8], 15);
			GetDlgItemText(hwnd, work, datos[10], 15);
			if (primero != nullptr) {
				while (detonante == 0) {
					if (primero) {
						temporal = primero;
						while (temporal) {
							if (strcmp(temporal->curp,datos[4]) == 0)
							{
								prueba = 1;
							}
							temporal = temporal->siguiente;
						}
						detonante = 1;
					}
				}
			}
			dvacio(datos[1]);
			dvacio(datos[2]);
			dvacio(datos[3]);
			dvacio(datos[4]);
			dvacio(direcc);
			dvacio(datos[6]);
			dvacio(datos[7]);
			dvacio(datos[8]);
			dvacio(datos[9]);
			dvacio(datos[10]);
			dvacio(datos[11]);
			if (prueba == 0) {
				if (primero == nullptr) {
					primero = new Persona;
					strcpy_s(primero->name, 15, datos[1]);
					strcpy_s(primero->a_pa, 15, datos[2]);
					strcpy_s(primero->a_ma, 15, datos[3]);
					strcpy_s(primero->curp, 20, datos[4]);
					//Revisar que no se repita el curp
					strcpy_s(primero->fecha_nac, 15, datos[11]);
					strcpy_s(primero->direccion, 200, direcc);
					strcpy_s(primero->estadocivil, 15, datos[6]);
					strcpy_s(primero->tel, 15, datos[7]);
					strcpy_s(primero->ID, 15, datos[8]);
					strcpy_s(primero->genero, 15, datos[9]);
					strcpy_s(primero->trabajo, 15, datos[10]);
					strcpy_s(conteiner, 50, "");
					strcat_s(conteiner, primero->name);
					strcat_s(conteiner, " ");
					strcat_s(conteiner, primero->a_pa);
					strcat_s(conteiner, " ");
					strcat_s(conteiner, primero->a_ma);
					strcpy_s(primero->nomC, 52, conteiner);
					strcpy_s(primero->path, 258, zFile);
					primero->siguiente = nullptr;
					primero->anterior = nullptr;
					ultimo = primero;
				}
				else {
					ultimo = primero;
					while (ultimo->siguiente != nullptr) {
						ultimo = ultimo->siguiente;
					}
					ultimo->siguiente = new Persona;
					ultimo->siguiente->siguiente = nullptr;
					ultimo->siguiente->anterior = ultimo;
					ultimo = ultimo->siguiente;
					strcpy_s(ultimo->name, 15, datos[1]);
					strcpy_s(ultimo->a_pa, 15, datos[2]);
					strcpy_s(ultimo->a_ma, 15, datos[3]);
					strcpy_s(ultimo->curp, 20, datos[4]);
					//revisar que no se repita el curp
					strcpy_s(ultimo->fecha_nac, 15, datos[11]);
					strcpy_s(ultimo->direccion, 200, direcc);
					strcpy_s(ultimo->estadocivil, 15, datos[6]);
					strcpy_s(ultimo->tel, 15, datos[7]);
					strcpy_s(ultimo->ID, 15, datos[8]);
					strcpy_s(ultimo->genero, 15, datos[9]);
					strcpy_s(ultimo->trabajo, 15, datos[10]);
					strcpy_s(conteiner, 50, "");
					strcat_s(conteiner, ultimo->name);
					strcat_s(conteiner, " ");
					strcat_s(conteiner, ultimo->a_pa);
					strcat_s(conteiner, " ");
					strcat_s(conteiner, ultimo->a_ma);
					strcpy_s(ultimo->nomC, 52, conteiner);
					strcpy_s(ultimo->path, 258, zFile);
				}
				MessageBox(hwnd, "El registro se ha realizado", "MENSAJE", MB_ICONINFORMATION);
				guardarPertxt();
				guardarPer();
			}
			else {
				MessageBox(hwnd, "Ha dejado espacios en blanco o hay un curp ya registrado coincidente", "MENSAJE", MB_ICONERROR);
			}
			EndDialog(hwnd, wParam);
			break;

		case R_RP:
			EndDialog(hwnd, wParam);
			break;

		case INGRESAFOTO1:
			OPENFILENAME ofn;
			ZeroMemory(zFile, sizeof(zFile));
			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "All\0*.*\0Bitmaps\0*.bmp\0";;
			ofn.lpstrFile = zFile;
			ofn.lpstrFile[0] = '\ 0';
			ofn.nMaxFile = sizeof(zFile);
			ofn.lpstrFileTitle = FileTitle;
			ofn.nMaxFileTitle = sizeof(FileTitle);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.nFilterIndex = 1;

			if (GetOpenFileName(&ofn)) {
				prueba = 0;
				bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 180, 130, LR_LOADFROMFILE);
				SendDlgItemMessage(hwnd, FOTO1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
			}
			else {
				MessageBox(hwnd, "No selecciono ningun archivo", "AVISO", MB_OK);
				prueba++;
			}
			break;

		case ec:
			for (a = 0; a < 4; a++) {
				SendDlgItemMessage(hwnd, ec, CB_INSERTSTRING, (WPARAM)a, (LPARAM)estcivil[a]);
			}

			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = 0;
				cur = SendDlgItemMessage(hwnd, ec, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, ec, CB_GETLBTEXT, cur, (LPARAM)datos[6]);
			}
			break;


		case gene:
			for (a = 0; a < 3; a++) {
				SendDlgItemMessage(hwnd, gene, CB_INSERTSTRING, (WPARAM)a, (LPARAM)gender[a]);
			}

			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = 0;
				cur = SendDlgItemMessage(hwnd,gene, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, gene, CB_GETLBTEXT, cur, (LPARAM)datos[9]);
			}
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK RegistroC(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, IP_N4);
		h_edit = GetDlgItem(hwnd, IP_AP4);
		h_edit = GetDlgItem(hwnd, IP_AM4);
		h_edit = GetDlgItem(hwnd, IP_C4);
		h_edit = GetDlgItem(hwnd, IP_F4);
		h_edit = GetDlgItem(hwnd, IP_D4);
		h_edit = GetDlgItem(hwnd, IP_EC4);
		h_edit = GetDlgItem(hwnd, IP_T4);
		h_edit = GetDlgItem(hwnd, IP_DOC4);
		h_edit = GetDlgItem(hwnd, IP_G4);
		h_edit = GetDlgItem(hwnd, IP_GO4);
		h_edit = GetDlgItem(hwnd, datee);
		h_edit = GetDlgItem(hwnd, datee2);
		h_edit = GetDlgItem(hwnd, centro);
		h_edit = GetDlgItem(hwnd, nombreuser5);
		h_combo = GetDlgItem(hwnd, C_Personas);
		h_combo = GetDlgItem(hwnd, C_Vacunas);
		h_combo = GetDlgItem(hwnd, C_NumDosis);
		h_boton = GetDlgItem(hwnd, G_RC);
		h_boton = GetDlgItem(hwnd, R_RC);
		SetDlgItemText(hwnd, nombreuser5, iniciarse);
		h_PicControl = GetDlgItem(hwnd, FOTOP14);

		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case G_RC:
			prueba = 0;
			detonante = 0;
			GetDlgItemText(hwnd, datee, datos[3], 15);
			GetDlgItemText(hwnd, centro, datos[5], 15);
			GetDlgItemText(hwnd, datee2, datos[4], 15);
			ID_CARNET++;
			if (prim != nullptr) {
				while (detonante == 0) {
					if (prim) {
						tempo = prim;
						while (tempo) {
							if (tempo->ID_carnet == ID_CARNET)
							{
								ID_CARNET++;
							}
							else {
								datonum2 = ID_CARNET;
								detonante = 1;
							}
							tempo = tempo->siguiente;
						}
					}
				}
			}
			else {
				datonum2 = ID_CARNET;
			}
			dvacio(datos[1]);
			dvacio(datos[2]);
			dvacio(datos[3]);
			dvacio(datos[4]);
			dvacio(datos[5]);
			dvacio(datos[6]);
			if (prueba == 0) {
				if (prim == nullptr) {

					prim = new Carnet;
					strcpy_s(prim->Curp, 20, datos[1]);
					strcpy_s(prim->vacuna, 15, datos[2]);
					strcpy_s(prim->No_dosis, 15, datos[6]);
					strcpy_s(prim->date, 15, datos[3]);
					strcpy_s(prim->lote, 15, datos[4]);
					strcpy_s(prim->lugar, 15, datos[5]);
					temporal = primero;
					while (strcmp(temporal->curp, prim->Curp) != 0) {
						temporal = temporal->siguiente;
					}
					strcpy_s(prim->datos.nomC,temporal->nomC);
					strcpy_s(prim->datos.ID, temporal->ID);
					strcpy_s(prim->datos.tel, temporal->tel);
					strcpy_s(prim->datos.direccion, temporal->direccion);
					strcpy_s(prim->datos.fecha_nac, temporal->fecha_nac);
					strcpy_s(prim->datos.genero, temporal->genero);
					strcpy_s(prim->datos.trabajo, temporal->trabajo);
					prim->ID_carnet = datonum2;
					prim->siguiente = nullptr;
					prim->anterior = nullptr;
					ult = prim;


				}
				else {
					ult = prim;
					while (ult->siguiente != nullptr) {
						ult = ult->siguiente;
					}
					ult->siguiente = new Carnet;
					ult->siguiente->siguiente = nullptr;
					ult->siguiente->anterior = ult;
					ult = ult->siguiente;
					strcpy_s(ult->Curp, 20, datos[1]);
					strcpy_s(ult->vacuna, 15, datos[2]);
					strcpy_s(ult->No_dosis, 15, datos[6]);
					strcpy_s(ult->date, 15, datos[3]);
					strcpy_s(ult->lote, 15, datos[4]);
					strcpy_s(ult->lugar, 15, datos[5]);
					temporal = primero;
					while (strcmp(temporal->curp, ult->Curp) != 0) {
						temporal = temporal->siguiente;
					}
					strcpy_s(ult->datos.nomC, temporal->nomC);
					strcpy_s(ult->datos.ID, temporal->ID);
					strcpy_s(ult->datos.tel, temporal->tel);
					strcpy_s(ult->datos.direccion, temporal->direccion);
					strcpy_s(ult->datos.fecha_nac, temporal->fecha_nac);
					strcpy_s(ult->datos.genero, temporal->genero);
					strcpy_s(ult->datos.trabajo, temporal->trabajo);
					ult->ID_carnet = datonum2;

				}
				MessageBox(hwnd, "El registro se ha realizado", "MENSAJE", MB_ICONINFORMATION);
				if (primer) {
					tempora = primer;
					while (tempora) {
						if (strcmp(tempora->marca,datos[2])==0){
							if (strcmp(tempora->num_dosis, datos[6])==0) {
								MessageBox(hwnd, "Has acabado tu esquema de vacunacion", "INFO", MB_ICONINFORMATION);
							}
							else {
								MessageBox(hwnd, "Tienes dosis pendientes", "INFO", MB_ICONINFORMATION);
							}
						}
						tempora = tempora->siguiente;
					}
				}
				guardarCartxt();
				guardarCar();
			}
			else {
				MessageBox(hwnd, "Ha dejado espacios en blanco", "MENSAJE", MB_ICONERROR);
			}
			EndDialog(hwnd, wParam);
			break;

		case R_RC:
			EndDialog(hwnd, wParam);
			break;

		case C_Personas:
			if (primero) {
				temporal = primero;
				while (temporal) {
					SendDlgItemMessage(hwnd, C_Personas, CB_INSERTSTRING, 0, (LPARAM)temporal->curp);
					temporal = temporal->siguiente;
				}
			}
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, C_Personas, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, C_Personas, CB_GETLBTEXT, cur, (LPARAM)datos[1]);
			}

			if (primero) {
				temporal = primero;
				while (temporal) {
					if (strcmp(temporal->curp, datos[1]) == 0) {
						SetDlgItemText(hwnd, IP_N4, temporal->name);
						SetDlgItemText(hwnd, IP_AP4, temporal->a_pa);
						SetDlgItemText(hwnd, IP_AM4, temporal->a_ma);
						SetDlgItemText(hwnd, IP_C4, temporal->curp);
						SetDlgItemText(hwnd, IP_F4, temporal->fecha_nac);
						SetDlgItemText(hwnd, IP_D4, temporal->direccion);
						SetDlgItemText(hwnd, IP_EC4, temporal->estadocivil);
						SetDlgItemText(hwnd, IP_T4, temporal->tel);
						SetDlgItemText(hwnd, IP_DOC4, temporal->ID);
						SetDlgItemText(hwnd, IP_G4, temporal->genero);
						SetDlgItemText(hwnd, IP_GO4, temporal->trabajo);
						bmp = (HBITMAP)LoadImage(NULL, temporal->path, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
						SendDlgItemMessage(hwnd, FOTOP14, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
						temporal = temporal->siguiente;
					}
					else {
						temporal = temporal->siguiente;
					}
				}
			}
				break;

		case C_Vacunas:
			if (primer) {
				tempora = primer;
				while (tempora) {
					SendDlgItemMessage(hwnd, C_Vacunas, CB_INSERTSTRING, 0, (LPARAM)tempora->marca);
					tempora = tempora->siguiente;
				}
			}
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, C_Vacunas, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, C_Vacunas, CB_GETLBTEXT, cur, (LPARAM)datos[2]);
			}

			break;

		case C_NumDosis:
			for (a = 0; a < 4; a++) {
				SendDlgItemMessage(hwnd, C_NumDosis, CB_INSERTSTRING, (WPARAM)a, (LPARAM)dosisop[a]);
			}

			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, C_NumDosis, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, C_NumDosis, CB_GETLBTEXT, cur, (LPARAM)datos[6]);
			}
			break;

			}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;

	}

	return FALSE;
}
BOOL CALLBACK ListadoU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, ncomu);
		h_edit = GetDlgItem(hwnd, IUN);
		h_edit = GetDlgItem(hwnd, IUAP);
		h_edit = GetDlgItem(hwnd, IUAM);
		h_edit = GetDlgItem(hwnd, IUC);
		h_edit = GetDlgItem(hwnd, IUCL);
		h_boton = GetDlgItem(hwnd, ListadoELI);
		h_boton = GetDlgItem(hwnd, ListadoEDI);
		h_boton = GetDlgItem(hwnd, ListadoREG);
		h_listbox = GetDlgItem(hwnd, IDC_LIST1);
		SetDlgItemText(hwnd, ncomu, iniciarse);
		if (prime) {
			tempor = prime;
			while (tempor) {
				SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)tempor->namecom);
				tempor = tempor->siguiente;
			}
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_LIST1:
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, cur, (LPARAM)textolistcorto);
				if (prime) {
					tempor = prime;
					while (tempor) {
						if (strcmp(tempor->namecom, textolistcorto) == 0) {
							SetDlgItemText(hwnd,IUN , tempor->nombres);
							SetDlgItemText(hwnd,IUAP ,tempor->a_paterno);
							SetDlgItemText(hwnd,IUAM ,tempor->a_materno);
							SetDlgItemText(hwnd,IUC ,tempor->contraseña);
							SetDlgItemInt(hwnd, IUCL, (UINT)tempor->clave_u, FALSE);
							strcpy_s(INFO_U[0],15, tempor->nombres);
							strcpy_s(INFO_U[1],15, tempor->a_paterno);
							strcpy_s(INFO_U[2],15, tempor->a_materno);
							strcpy_s(INFO_U[3], 15, tempor->contraseña);
							strcpy_s(INFO_U[4], 52, tempor->namecom);
							datonum1 = tempor->clave_u;
							tempor = tempor->siguiente;
						}
						else {
							tempor = tempor->siguiente;
						}
					}
				}
			}
			break;
		case ListadoELI:
			MessageBox(hwnd, "Esta seguro de que dessea eliminar la informacion seleccionada?", "AVISO IMPORTANTE", MB_YESNO);
			if (IDNO != TRUE) {
				ulti = prime;
				if (strcmp(ulti->namecom, INFO_U[4]) == 0) {
					prime->anterior = nullptr;
					prime = prime->siguiente;
					ulti = tempor;
					delete tempor;
					MessageBox(hwnd, "La cuenta con la que ingreso ya no existe, cree una nueva", "SESION INEXISTENTE", MB_ICONINFORMATION | MB_OK);
					EndDialog(hwnd, wParam);
					PostQuitMessage(0);
				}
				else {
					while (ulti != nullptr && strcmp(ulti->namecom, INFO_U[4]) != 0) {
						ulti = ulti->siguiente;
					}
					if (ulti != nullptr) {
						if (strcmp(ulti->namecom, INFO_U[4]) == 0) {
							tempor = ulti;
							tempor->anterior->siguiente = tempor->siguiente;
							if (tempor->siguiente != nullptr) {
								tempor->siguiente->anterior = tempor->anterior;
							}
							delete tempor;
						}
					}
				}
				MessageBox(hwnd, "El Usuario Ha Sido Eliminado", "AVISO IMPORTANTE", MB_OK);
				SendDlgItemMessage(hwnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);
				if (prime) {
					tempor = prime;
					while (tempor) {
						SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)tempor->namecom);
						tempor = tempor->siguiente;
					}
				}
				SetDlgItemText(hwnd, IUN, "");
				SetDlgItemText(hwnd, IUAP, "");
				SetDlgItemText(hwnd, IUAM, "");
				SetDlgItemText(hwnd, IUC, "");
				SetDlgItemText(hwnd, IUCL, "");
				guardarU();
				guardarUtxt();
				}
			break;
		case ListadoEDI:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG8), 0, (DLGPROC)CambioU);
			SendDlgItemMessage(hwnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);
			if (prime) {
				tempor = prime;
				while (tempor) {
					SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)tempor->namecom);
					tempor = tempor->siguiente;
				}
			}
			SetDlgItemText(hwnd, IUN, "");
			SetDlgItemText(hwnd, IUAP, "");
			SetDlgItemText(hwnd, IUAM, "");
			SetDlgItemText(hwnd, IUC, "");
			SetDlgItemText(hwnd, IUCL, "");
			break;
		case ListadoREG:
			EndDialog(hwnd, wParam);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK CambioU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, ncomu2);
		h_edit = GetDlgItem(hwnd, IUN2);
		h_edit = GetDlgItem(hwnd, IUAP2);
		h_edit = GetDlgItem(hwnd, IUAM2);
		h_edit = GetDlgItem(hwnd, IUC2);
		h_edit = GetDlgItem(hwnd, IUCL2);
		h_boton = GetDlgItem(hwnd, B_ACTU);
		h_boton = GetDlgItem(hwnd, B_CU);
		SetDlgItemText(hwnd, ncomu2, iniciarse);
		SetDlgItemText(hwnd, IUN2, INFO_U[0]);
		SetDlgItemText(hwnd, IUAP2,INFO_U[1]);
		SetDlgItemText(hwnd, IUAM2,INFO_U[2]);
		SetDlgItemText(hwnd, IUC2, INFO_U[3]);
		SetDlgItemInt(hwnd, IUCL2,(UINT)datonum1,FALSE);
		break;


	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case B_ACTU:
			prueba = 0;
			detonante = 0;
			strcpy_s(nuevo, 52, INFO_U[4]);
			GetDlgItemText(hwnd, IUN2, INFO_U[0], 15);
			GetDlgItemText(hwnd, IUAP2, INFO_U[1], 15);
			GetDlgItemText(hwnd, IUAM2, INFO_U[2], 15);
			GetDlgItemText(hwnd, IUC2, INFO_U[3], 15);
			datonum1 = GetDlgItemInt(hwnd, IUCL2, &numOK, FALSE);
			if (prime != nullptr) {
				while (detonante == 0) {
					if (prime) {
						tempor = prime;
						while (tempor) {
							if (tempor->clave_u == datonum1)
							{
								prueba = 1;
							}
							tempor = tempor->siguiente;
						}
						detonante = 1;
					}
				}
			}
			dvacio(INFO_U[0]);
			dvacio(INFO_U[1]);
			dvacio(INFO_U[2]);
			dvacio(INFO_U[3]);
			
			if (prueba == 0) {
			tempor = prime;
			while (strcmp(tempor->namecom, nuevo)!= 0) {
				tempor = tempor->siguiente;
			}

				if (strcmp(tempor->nombres, INFO_U[0]) != 0) {
					strcpy_s(tempor->nombres, INFO_U[0]);
				
				}
				if (strcmp(tempor->a_paterno, INFO_U[1]) != 0) {
					strcpy_s(tempor->a_paterno, INFO_U[1]);

				}
				if (strcmp(tempor->a_materno, INFO_U[2]) != 0) {
					strcpy_s(tempor->a_materno, INFO_U[2]);

				}
				if (strcmp(tempor->contraseña, INFO_U[3]) != 0) {
					strcpy_s(tempor->contraseña, INFO_U[3]);

				}
				if (tempor->clave_u != datonum1) {
					tempor->clave_u = datonum1;
				}
				strcpy_s(conteiner, 15, "");
				strcat_s(conteiner, tempor->nombres);
				strcat_s(conteiner, " ");
				strcat_s(conteiner, tempor->a_paterno);
				strcat_s(conteiner, " ");
				strcat_s(conteiner, tempor->a_materno);
				strcpy_s(tempor->namecom, 52, conteiner);

			MessageBox(hwnd, "La informacion se ha actualizado", "MENSAJE", MB_ICONINFORMATION);
			guardarU();
			guardarUtxt();
			EndDialog(hwnd, wParam);
			}
			else {
			MessageBox(hwnd, "Ha dejado espacios en blanco o la clave de usuario se ha repetido", "MENSAJE", MB_ICONINFORMATION);
			}
			break;


		case B_CU:
			EndDialog(hwnd, wParam);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK ListadoV(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, ncomu3);
		h_edit = GetDlgItem(hwnd, IV_TV);
		h_edit = GetDlgItem(hwnd, IV_M);
		h_edit = GetDlgItem(hwnd, IV_CV);
		h_edit = GetDlgItem(hwnd, IV_D);
		h_edit = GetDlgItem(hwnd, IV_ND);
		h_edit = GetDlgItem(hwnd, IV_NINERO);
		h_boton = GetDlgItem(hwnd, ListadoELIV);
		h_boton = GetDlgItem(hwnd, ListadoEDIV);
		h_boton = GetDlgItem(hwnd, ListadoREGV);
		h_listbox = GetDlgItem(hwnd, IDC_LIST2);
		SetDlgItemText(hwnd, ncomu3, iniciarse);
		if (primer) {
			tempora = primer;
			while (tempora) {
				SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_ADDSTRING, 0, (LPARAM)tempora->marca);
				tempora = tempora->siguiente;
			}
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_LIST2:
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IDC_LIST2, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST2, LB_GETTEXT, cur, (LPARAM)textolistcorto);
				if (primer) {
					tempora = primer;
					while (tempora) {
						if (strcmp(tempora->marca, textolistcorto) == 0) {
							SetDlgItemText(hwnd, IV_TV, tempora->tipo);
							SetDlgItemText(hwnd, IV_M, tempora->marca);
							SetDlgItemText(hwnd, IV_CV, tempora->clave_v);
							SetDlgItemText(hwnd, IV_D, tempora->desc);
							SetDlgItemText(hwnd, IV_ND, tempora->num_dosis);
							SetDlgItemInt(hwnd, IV_NINERO, (UINT)tempora->precio, FALSE);
							strcpy_s(INFO_U[0], 15, tempora->tipo);
							strcpy_s(INFO_U[1], 15, tempora->marca);
							strcpy_s(INFO_U[2], 15, tempora->clave_v);
							strcpy_s(INFO_U[3], 15, tempora->num_dosis);
							strcpy_s(de, 260, tempora->desc);
							datonum1 = tempora->precio;
							tempora = tempora->siguiente;
						}
						else {
							tempora = tempora->siguiente;
						}
					}
				}
			}
			break;

		case ListadoELIV:
			MessageBox(hwnd, "Esta seguro de que dessea eliminar la informacion seleccionada?", "AVISO IMPORTANTE", MB_YESNO);
			if (IDNO != TRUE) {
				ultim = primer;
				if (strcmp(ultim->marca, INFO_U[1]) == 0) {
					primer->anterior = nullptr;
					primer = primer->siguiente;
					ultim = tempora;
					delete tempora;
				}
				else {
					while (ultim != nullptr && strcmp(ultim->marca, INFO_U[1]) != 0) {
						ultim = ultim->siguiente;
					}
					if (ultim != nullptr) {
						if (strcmp(ultim->marca, INFO_U[1]) == 0) {
							tempora = ultim;
							tempora->anterior->siguiente = tempora->siguiente;
							if (tempora->siguiente != nullptr) {
								tempora->siguiente->anterior = tempora->anterior;
							}
							delete tempora;
						}
					}
				}
				MessageBox(hwnd, "El Usuario Ha Sido Eliminado", "AVISO IMPORTANTE", MB_OK);
				SendDlgItemMessage(hwnd, IDC_LIST2, LB_RESETCONTENT, 0, 0);
				if (primer) {
					tempora = primer;
					while (tempora) {
						SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)tempora->marca);
						tempora = tempora->siguiente;
					}
				}
				SetDlgItemText(hwnd, IV_TV, "");
				SetDlgItemText(hwnd, IV_M , "");
				SetDlgItemText(hwnd, IV_CV, "");
				SetDlgItemText(hwnd, IV_D , "");
				SetDlgItemText(hwnd, IV_ND, "");
				SetDlgItemText(hwnd, IV_NINERO, "");
				guardarV();
				guardarVtxt();
			}
			break;


		case ListadoEDIV:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG10), 0, (DLGPROC)CambioV);
			SendDlgItemMessage(hwnd, IDC_LIST2, LB_RESETCONTENT, 0, 0);
			if (primer) {
				tempora = primer;
				while (tempora) {
					SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_ADDSTRING, 0, (LPARAM)tempora->marca);
					tempora = tempora->siguiente;
				}
			}
			SetDlgItemText(hwnd, IV_TV, "");
			SetDlgItemText(hwnd, IV_M, "");
			SetDlgItemText(hwnd, IV_CV, "");
			SetDlgItemText(hwnd, IV_D, "");
			SetDlgItemText(hwnd, IV_ND, "");
			SetDlgItemText(hwnd, IV_NINERO, "");
			break;
		
		case ListadoREGV:
			EndDialog(hwnd, wParam);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK CambioV(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, ncomu4);
		h_edit = GetDlgItem(hwnd, IV_TV2);
		h_edit = GetDlgItem(hwnd, IV_M2);
		h_edit = GetDlgItem(hwnd, IV_CV2);
		h_edit = GetDlgItem(hwnd, IV_D2);
		h_edit = GetDlgItem(hwnd, IV_NINERO2);
		h_combo = GetDlgItem(hwnd, IDC_COMBO2);
		SetDlgItemText(hwnd, ncomu4, iniciarse);
		SetDlgItemText(hwnd, IV_TV2, INFO_U[0]);
		SetDlgItemText(hwnd, IV_M2, INFO_U[1]);
		SetDlgItemText(hwnd, IV_CV2, INFO_U[2]);
		SetDlgItemText(hwnd, IV_D2, de);
		SetDlgItemInt(hwnd, IV_NINERO2, (UINT)datonum1, FALSE);
		break;


	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case B_ACTV:
			prueba = 0;
			detonante = 0;
			strcpy_s(nuevo, 15, INFO_U[1]);//AQUI GUARDE A MARCA
			GetDlgItemText(hwnd, IV_TV2, INFO_U[0],15);
			GetDlgItemText(hwnd, IV_M2, INFO_U[1],15);
			GetDlgItemText(hwnd, IV_CV2, INFO_U[2],15);
			GetDlgItemText(hwnd, IV_D2,de,259);
			datonum1=GetDlgItemInt(hwnd, IV_NINERO2,&numOK, FALSE);
			if (primer != nullptr) {
				while (detonante == 0) {
					if (primer) {
						tempora = primer;
						while (tempora) {
							if (strcmp(tempora->marca, INFO_U[1]) == 0)
							{
								prueba = 2;
							}
							tempora = tempora->siguiente;
						}
						detonante = 1;
					}
				}
			}
			dvacio(INFO_U[0]);
			dvacio(INFO_U[1]);
			dvacio(INFO_U[2]);
			dvacio(INFO_U[3]);

			if (prueba == 0) {
				tempora = primer;
				while (strcmp(tempora->marca, nuevo) != 0) {
					tempora = tempora->siguiente;
				}

				if (strcmp(tempora->tipo, INFO_U[0]) != 0) {
					strcpy_s(tempora->tipo, INFO_U[0]);

				}
				if (strcmp(tempora->marca, INFO_U[1]) != 0) {
					strcpy_s(tempora->marca, INFO_U[1]);

				}
				if (strcmp(tempora->clave_v, INFO_U[2]) != 0) {
					strcpy_s(tempora->clave_v, INFO_U[2]);

				}
				if (strcmp(tempora->num_dosis, INFO_U[3]) != 0) {
					strcpy_s(tempora->num_dosis, INFO_U[3]);

				}
				if (strcmp(tempora->desc, de) != 0) {
					strcpy_s(tempora->desc, de);

				}
				if (tempora->precio != datonum1) {
					tempora->precio = datonum1;
				}
				MessageBox(hwnd, "La informacion se ha actualizado", "MENSAJE", MB_ICONINFORMATION);
				guardarV();
				guardarVtxt();
				EndDialog(hwnd, wParam);
			}
			else {
				MessageBox(hwnd, "Ha dejado espacios en blanco o se ha repetido la clave de  marca de vacuna", "MENSAJE", MB_ICONERROR);
			}
			break;


		case IDC_COMBO2:
			for (a = 0; a < 4; a++) {
				SendDlgItemMessage(hwnd, IDC_COMBO2, CB_INSERTSTRING, (WPARAM)a, (LPARAM)dosisop[a]);
			}

			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IDC_COMBO2, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_COMBO2, CB_GETLBTEXT, cur, (LPARAM)INFO_U[3]);
			}
			break;

		case B_CV:
			EndDialog(hwnd, wParam);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK ListadoP(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, ncomu5);
		h_edit = GetDlgItem(hwnd, IP_N);
		h_edit = GetDlgItem(hwnd, IP_AP);
		h_edit = GetDlgItem(hwnd, IP_AM);
		h_edit = GetDlgItem(hwnd, IP_C);
		h_edit = GetDlgItem(hwnd, IP_F);
		h_edit = GetDlgItem(hwnd, IP_D);
		h_edit = GetDlgItem(hwnd, IP_EC);
		h_edit = GetDlgItem(hwnd, IP_T);
		h_edit = GetDlgItem(hwnd, IP_DOC);
		h_edit = GetDlgItem(hwnd, IP_G);
		h_edit = GetDlgItem(hwnd, IP_GO);
		h_boton = GetDlgItem(hwnd, ListadoELIP);
		h_boton = GetDlgItem(hwnd, ListadoEDIP);
		h_boton = GetDlgItem(hwnd, ListadoREGP);
		h_listbox = GetDlgItem(hwnd, IDC_LIST3);
		h_PicControl = GetDlgItem(hwnd, FOTOP1);
		SetDlgItemText(hwnd, ncomu5, iniciarse);
		if (primero) {
			temporal = primero;
			while (temporal) {
				SendMessage(GetDlgItem(hwnd, IDC_LIST3), LB_ADDSTRING, 0, (LPARAM)temporal->nomC);
				temporal = temporal->siguiente;
			}
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_LIST3:
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETTEXT, cur, (LPARAM)textolistcorto);
				if (primero) {
					temporal = primero;
					while (temporal) {
						if (strcmp(temporal->nomC, textolistcorto) == 0) {
							SetDlgItemText(hwnd, IP_N, temporal->name);
							SetDlgItemText(hwnd, IP_AP, temporal->a_pa);
							SetDlgItemText(hwnd, IP_AM, temporal->a_ma);
							SetDlgItemText(hwnd, IP_C, temporal->curp);
							SetDlgItemText(hwnd, IP_F, temporal->fecha_nac);
							SetDlgItemText(hwnd, IP_D, temporal->direccion);
							SetDlgItemText(hwnd, IP_EC, temporal->estadocivil);
							SetDlgItemText(hwnd, IP_T, temporal->tel);
							SetDlgItemText(hwnd, IP_DOC, temporal->ID);
							SetDlgItemText(hwnd, IP_G, temporal->genero);
							SetDlgItemText(hwnd, IP_GO, temporal->trabajo);
							bmp = (HBITMAP)LoadImage(NULL, temporal->path, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
							SendDlgItemMessage(hwnd, FOTOP1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
							strcpy_s(INFO_U[0],15, temporal->name);
							strcpy_s(INFO_U[1],15, temporal->a_pa);
							strcpy_s(INFO_U[2],15, temporal->a_ma);
							strcpy_s(INFO_U[3],20, temporal->curp);
							strcpy_s(INFO_U[4],15, temporal->fecha_nac);
							strcpy_s(direcc,200, temporal->direccion);
							strcpy_s(INFO_U[5],15, temporal->estadocivil);
							strcpy_s(INFO_U[6],15, temporal->tel);
							strcpy_s(INFO_U[7],15, temporal->ID);
							strcpy_s(INFO_U[8],15, temporal->genero);
							strcpy_s(INFO_U[9],15, temporal->trabajo);
							temporal = temporal->siguiente;
						}
						else {
							temporal = temporal->siguiente;
						}
					}
				}
			}
			break;
		case ListadoELIP:
			MessageBox(hwnd, "Esta seguro de que dessea eliminar la informacion seleccionada?", "AVISO IMPORTANTE", MB_YESNO);
			if (IDNO != TRUE) {
				ultimo = primero;
				if (strcmp(ultimo->nomC, textolistcorto) == 0) {
					primero->anterior = nullptr;
					primero = primero->siguiente;
					ultimo = temporal;
					delete temporal;
				}
				else {
					while (ultimo != nullptr && strcmp(ultimo->nomC, textolistcorto) != 0) {
						ultimo = ultimo->siguiente;
					}
					if (ultimo != nullptr) {
						if (strcmp(ultimo->nomC, textolistcorto) == 0) {
							temporal = ultimo;
							temporal->anterior->siguiente = temporal->siguiente;
							if (temporal->siguiente != nullptr) {
								temporal->siguiente->anterior = temporal->anterior;
							}
							delete temporal;
						}
					}
				}
				MessageBox(hwnd, "El Usuario Ha Sido Eliminado", "AVISO IMPORTANTE", MB_OK);
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_RESETCONTENT, 0, 0);
				if (primero) {
					temporal = primero;
					while (temporal) {
						SendMessage(GetDlgItem(hwnd, IDC_LIST3), LB_ADDSTRING, 0, (LPARAM)temporal->nomC);
						temporal = temporal->siguiente;
					}
				}
				SetDlgItemText(hwnd, IP_N,  "");
				SetDlgItemText(hwnd, IP_AP, "");
				SetDlgItemText(hwnd, IP_AM, "");
				SetDlgItemText(hwnd, IP_C,  "");
				SetDlgItemText(hwnd, IP_F,  "");
				SetDlgItemText(hwnd, IP_D,  "");
				SetDlgItemText(hwnd, IP_EC, "");
				SetDlgItemText(hwnd, IP_T,  "");
				SetDlgItemText(hwnd, IP_DOC, "");
				SetDlgItemText(hwnd, IP_G,  "");
				SetDlgItemText(hwnd, IP_GO, "");
				guardarPer();
				guardarPertxt();
			}
			break;
		case ListadoEDIP:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG12), 0, (DLGPROC)CambioP);
			SendDlgItemMessage(hwnd, IDC_LIST3, LB_RESETCONTENT, 0, 0);
			if (primero) {
				temporal = primero;
				while (temporal) {
					SendMessage(GetDlgItem(hwnd, IDC_LIST3), LB_ADDSTRING, 0, (LPARAM)temporal->nomC);
					temporal = temporal->siguiente;
				}
			}

			SetDlgItemText(hwnd, IP_N, "");
			SetDlgItemText(hwnd, IP_AP, "");
			SetDlgItemText(hwnd, IP_AM, "");
			SetDlgItemText(hwnd, IP_C, "");
			SetDlgItemText(hwnd, IP_F, "");
			SetDlgItemText(hwnd, IP_D, "");
			SetDlgItemText(hwnd, IP_EC, "");
			SetDlgItemText(hwnd, IP_T, "");
			SetDlgItemText(hwnd, IP_DOC, "");
			SetDlgItemText(hwnd, IP_G, "");
			SetDlgItemText(hwnd, IP_GO, "");
			break;
		case ListadoREGP:
			EndDialog(hwnd, wParam);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK CambioP(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, ncomu6);
		h_edit = GetDlgItem(hwnd, IP_N2);
		h_edit = GetDlgItem(hwnd, IP_AP2);
		h_edit = GetDlgItem(hwnd, IP_AM2);
		h_edit = GetDlgItem(hwnd, IP_C2);
		h_edit = GetDlgItem(hwnd, IP_F2);
		h_edit = GetDlgItem(hwnd, IP_D2);
		h_edit = GetDlgItem(hwnd, IP_T2);
		h_edit = GetDlgItem(hwnd, IP_DOC2);
		h_edit = GetDlgItem(hwnd, IP_GO2);
		h_combo = GetDlgItem(hwnd, IP_EC2);
		h_combo = GetDlgItem(hwnd, IP_G2);
		h_boton = GetDlgItem(hwnd, B_ACTP);
		h_boton = GetDlgItem(hwnd, B_CP);
		h_boton = GetDlgItem(hwnd, INGRESAFOTO2);
		h_PicControl = GetDlgItem(hwnd, FOTO2);
		SetDlgItemText(hwnd, ncomu6, iniciarse);
		SetDlgItemText(hwnd, IP_N2, INFO_U[0]);
		SetDlgItemText(hwnd, IP_AP2, INFO_U[1]);
		SetDlgItemText(hwnd, IP_AM2, INFO_U[2]);
		SetDlgItemText(hwnd, IP_C2, INFO_U[3]);
		SetDlgItemText(hwnd, IP_F2, INFO_U[4]);
		SetDlgItemText(hwnd, IP_D2, direcc);
		SetDlgItemText(hwnd, IP_EC2, INFO_U[5]);
		SetDlgItemText(hwnd, IP_T2, INFO_U[6]);
		SetDlgItemText(hwnd, IP_DOC2, INFO_U[7]);
		SetDlgItemText(hwnd, IP_G2, INFO_U[8]);
		SetDlgItemText(hwnd, IP_GO2, INFO_U[9]);
		break;


	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case B_ACTP:
			prueba = 0;
			detonante = 0;
			strcpy_s(nuevo, 52, textolistcorto);
			GetDlgItemText(hwnd, IP_N2, INFO_U[0],15);
			GetDlgItemText(hwnd, IP_AP2, INFO_U[1],15);
			GetDlgItemText(hwnd, IP_AM2, INFO_U[2],15);
			GetDlgItemText(hwnd, IP_C2, INFO_U[3],20);
			GetDlgItemText(hwnd, IP_F2, INFO_U[4],15);
			GetDlgItemText(hwnd, IP_D2, direcc,200);
			GetDlgItemText(hwnd, IP_T2, INFO_U[6],15);
			GetDlgItemText(hwnd, IP_DOC2, INFO_U[7],15);
			GetDlgItemText(hwnd, IP_GO2, INFO_U[9],15);
			if (primero != nullptr) {
				while (detonante == 0) {
					if (primero) {
						temporal = primero;
						while (temporal) {
							if (strcmp(temporal->curp, INFO_U[3]) == 0)
							{
								prueba = 1;
							}
							temporal = temporal->siguiente;
						}
						detonante = 1;
					}
				}
			}
			dvacio(INFO_U[0]);
			dvacio(INFO_U[1]);
			dvacio(INFO_U[2]);
			dvacio(INFO_U[3]);
			dvacio(INFO_U[4]);
			dvacio(INFO_U[5]);
			dvacio(INFO_U[6]);
			dvacio(INFO_U[7]);
			dvacio(INFO_U[8]);
			dvacio(INFO_U[9]);
			dvacio(direcc);

			if (prueba == 0) {
				temporal = primero;
				while (strcmp(temporal->nomC, nuevo) != 0) {
					temporal = temporal->siguiente;
				}

				if (strcmp(temporal->name, INFO_U[0]) != 0) {
					strcpy_s(temporal->name, INFO_U[0]);

				}
				if (strcmp(temporal->a_pa, INFO_U[1]) != 0) {
					strcpy_s(temporal->a_pa, INFO_U[1]);

				}
				if (strcmp(temporal->a_ma, INFO_U[2]) != 0) {
					strcpy_s(temporal->a_ma, INFO_U[2]);

				}
				if (strcmp(temporal->curp, INFO_U[3]) != 0) {
					strcpy_s(temporal->curp, INFO_U[3]);

				}

				if (strcmp(temporal->fecha_nac, INFO_U[4]) != 0) {
					strcpy_s(temporal->fecha_nac, INFO_U[4]);

				}
				if (strcmp(temporal->direccion, direcc) != 0) {
					strcpy_s(temporal->direccion, direcc);

				}
				if (strcmp(temporal->estadocivil, INFO_U[5]) != 0) {
					strcpy_s(temporal->estadocivil, INFO_U[5]);

				}
				if (strcmp(temporal->tel, INFO_U[6]) != 0) {
					strcpy_s(temporal->tel, INFO_U[6]);

				}

				if (strcmp(temporal->ID, INFO_U[7]) != 0) {
					strcpy_s(temporal->ID, INFO_U[7]);

				}
				if (strcmp(temporal->genero, INFO_U[8]) != 0) {
					strcpy_s(temporal->genero, INFO_U[8]);

				}
				if (strcmp(temporal->trabajo, INFO_U[9]) != 0) {
					strcpy_s(temporal->trabajo, INFO_U[9]);

				}
				if (strcmp(temporal->path, zFile) != 0) {
					strcpy_s(temporal->path, zFile);

				}
				strcpy_s(conteiner, 50, "");
				strcat_s(conteiner, temporal->name);
				strcat_s(conteiner, " ");
				strcat_s(conteiner, temporal->a_pa);
				strcat_s(conteiner, " ");
				strcat_s(conteiner, temporal->a_ma);
				strcpy_s(temporal->nomC, 52, conteiner);
				MessageBox(hwnd, "La informacion se ha actualizado", "MENSAJE", MB_ICONINFORMATION);
				guardarPer();
				guardarPertxt();
				EndDialog(hwnd, wParam);
			}
			else {
				MessageBox(hwnd, "Ha dejado espacios en blanco o hay un curp coincidente al registrado", "MENSAJE", MB_ICONINFORMATION);
			}
			break;

		case IP_EC2:
			for (a = 0; a < 4; a++) {
				SendDlgItemMessage(hwnd, IP_EC2, CB_INSERTSTRING, (WPARAM)a, (LPARAM)estcivil[a]);
			}

			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = 0;
				cur = SendDlgItemMessage(hwnd, IP_EC2, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IP_EC2, CB_GETLBTEXT, cur, (LPARAM)INFO_U[5]);
			}
			break;


		case IP_G2:
			for (a = 0; a < 3; a++) {
				SendDlgItemMessage(hwnd, IP_G2, CB_INSERTSTRING, (WPARAM)a, (LPARAM)gender[a]);
			}

			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = 0;
				cur = SendDlgItemMessage(hwnd, IP_G2, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IP_G2, CB_GETLBTEXT, cur, (LPARAM)INFO_U[8]);
			}
			break;

		case INGRESAFOTO2:
			OPENFILENAME ofn;
			ZeroMemory(zFile, sizeof(zFile));
			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "All\0*.*\0Bitmaps\0*.bmp\0";;
			ofn.lpstrFile = zFile;
			ofn.lpstrFile[0] = '\ 0';
			ofn.nMaxFile = sizeof(zFile);
			ofn.lpstrFileTitle = FileTitle;
			ofn.nMaxFileTitle = sizeof(FileTitle);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.nFilterIndex = 1;

			if (GetOpenFileName(&ofn)) {
				prueba = 0;
				h_PicControl = GetDlgItem(hwnd, FOTO2);
				bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 180, 130, LR_LOADFROMFILE);
				SendDlgItemMessage(hwnd, FOTO2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
			}
			else {
				MessageBox(hwnd, "No selecciono ningun archivo", "AVISO", MB_OK);
				prueba++;
			}
			break;

		case B_CP:
			EndDialog(hwnd, wParam);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK ListadoC(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_radio = GetDlgItem(hwnd, IDC_RADIO1);
		h_radio = GetDlgItem(hwnd, IDC_RADIO2);
		h_edit = GetDlgItem(hwnd, ncomu7);
		h_edit = GetDlgItem(hwnd, IC_C);
		h_edit = GetDlgItem(hwnd, IC_U);
		h_edit = GetDlgItem(hwnd, IC_ND);
		h_edit = GetDlgItem(hwnd, IC_L);
		h_edit = GetDlgItem(hwnd, IC_F);
		h_edit = GetDlgItem(hwnd, IC_CDA);
		h_edit = GetDlgItem(hwnd, Name_R);
		h_edit = GetDlgItem(hwnd, Doc_R);
		h_edit = GetDlgItem(hwnd, Name_R);
		h_edit = GetDlgItem(hwnd, Tel_R);
		h_edit = GetDlgItem(hwnd, Dire_R);
		h_edit = GetDlgItem(hwnd, Fecha_R);
		h_edit = GetDlgItem(hwnd, Genero_R);
		h_edit = GetDlgItem(hwnd, Work_R);
		h_boton = GetDlgItem(hwnd, ListadoELIC);
		h_boton = GetDlgItem(hwnd, ListadoEDIC);
		h_boton = GetDlgItem(hwnd, ListadoREGC);
		h_boton = GetDlgItem(hwnd, boton_reporte);
		h_listbox = GetDlgItem(hwnd, IDC_LIST4);
		SetDlgItemText(hwnd, ncomu7, iniciarse);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_LIST4:
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IDC_LIST4, LB_GETCURSEL, 0, 0);
				if (deno == 1) {
					SendDlgItemMessage(hwnd, IDC_LIST4, LB_GETTEXT, cur, (LPARAM)textolistcorto);
					if (prim) {
						tempo = prim;
						while (tempo) {
							if (strcmp(tempo->datos.nomC, textolistcorto) == 0) {
								SetDlgItemText(hwnd, IC_C, tempo->Curp);
								SetDlgItemText(hwnd, IC_U, tempo->vacuna);
								SetDlgItemText(hwnd, IC_ND, tempo->No_dosis);
								SetDlgItemText(hwnd, IC_L, tempo->lote);
								SetDlgItemText(hwnd, IC_F, tempo->date);
								SetDlgItemText(hwnd, IC_CDA, tempo->lugar);
								SetDlgItemText(hwnd,Name_R,tempo->datos.nomC);
								SetDlgItemText(hwnd,Doc_R,tempo->datos.ID);
								SetDlgItemText(hwnd,Tel_R,tempo->datos.tel);
								SetDlgItemText(hwnd,Dire_R,tempo->datos.direccion);
								SetDlgItemText(hwnd,Fecha_R,tempo->datos.fecha_nac);
								SetDlgItemText(hwnd,Genero_R,tempo->datos.genero);
								SetDlgItemText(hwnd,Work_R,tempo->datos.trabajo);
								strcpy_s(INFO_U[0], 20, tempo->Curp);
								strcpy_s(INFO_U[1], 15, tempo->vacuna);
								strcpy_s(INFO_U[2], 15, tempo->No_dosis);
								strcpy_s(INFO_U[3], 15, tempo->lote);
								strcpy_s(INFO_U[4], 52, tempo->date);
								strcpy_s(INFO_U[5], 52, tempo->lugar);
								tempo = tempo->siguiente;
							}
							else {
								tempo = tempo->siguiente;
							}
						}
					}
				}
				if (deno == 2) {
					SendDlgItemMessage(hwnd, IDC_LIST4, LB_GETTEXT, cur, (LPARAM)textolistcorto);
					buscarlistaBinaria(prim,NULL,atoi(textolistcorto));
					if (e == true) {
						SetDlgItemText(hwnd, IC_C, INFO_U[0]);
						SetDlgItemText(hwnd, IC_U, INFO_U[1]);
						SetDlgItemText(hwnd, IC_ND, INFO_U[2]);
						SetDlgItemText(hwnd, IC_L, INFO_U[3]);
						SetDlgItemText(hwnd, IC_F, INFO_U[4]);
						SetDlgItemText(hwnd, IC_CDA, INFO_U[5]);
						SetDlgItemText(hwnd, Name_R, INFO_U[6]);
						SetDlgItemText(hwnd, Doc_R,  INFO_U[7]);
						SetDlgItemText(hwnd, Tel_R,  INFO_U[8]);
						SetDlgItemText(hwnd, Dire_R,  INFO_U[9]);
						SetDlgItemText(hwnd, Fecha_R,  INFO_U[10]);
						SetDlgItemText(hwnd, Genero_R, INFO_U[11]);
						SetDlgItemText(hwnd, Work_R,  INFO_U[12]);
					}

				}
				break;
			}
		break;
		case IDC_RADIO1:
			deno = 1;
			SendDlgItemMessage(hwnd, IDC_LIST4, LB_RESETCONTENT, 0, 0);
			quickSort(prim,ult);
			imprimirLista(prim, hwnd);
			break;

		case IDC_RADIO2:
			deno = 2;
			SendDlgItemMessage(hwnd, IDC_LIST4, LB_RESETCONTENT, 0, 0);
			heapSort(prim, ult);
			printList(prim, ult,h_listbox);
			break;

		case ListadoELIC: 
			MessageBox(hwnd, "Esta seguro de que dessea eliminar la informacion seleccionada?", "AVISO IMPORTANTE", MB_YESNO);
			if (IDNO != TRUE) {
				if (deno == 1) {
					ult = prim;
					if (strcmp(ult->datos.nomC, textolistcorto) == 0) {
						prim->anterior = nullptr;
						prim = prim->siguiente;
						ult = tempo;
						delete tempo;
					}
					else {
						while (ult != nullptr && strcmp(ult->datos.nomC, textolistcorto) != 0) {
							ult = ult->siguiente;
						}
						if (ult != nullptr) {
							if (strcmp(ult->datos.nomC, textolistcorto) == 0) {
								tempo = ult;
								tempo->anterior->siguiente = tempo->siguiente;
								if (tempo->siguiente != nullptr) {
									tempo->siguiente->anterior = tempo->anterior;
								}
								delete tempo;
							}
						}
					}
				}
				if (deno == 2) {
					ult = prim;
					if (ult->ID_carnet == stoi(textolistcorto)) {
						prim->anterior = nullptr;
						prim = prim->siguiente;
						ult = tempo;
						delete tempo;
					}
					else {
						while (ult != nullptr && ult->ID_carnet != stoi(textolistcorto)) {
							ult = ult->siguiente;
						}
						if (ult != nullptr) {
							if (ult->ID_carnet == stoi(textolistcorto)) {
								tempo = ult;
								tempo->anterior->siguiente = tempo->siguiente;
								if (tempo->siguiente != nullptr) {
									tempo->siguiente->anterior = tempo->anterior;
								}
								delete tempo;
							}
						}
					}
				}
				MessageBox(hwnd, "El Usuario Ha Sido Eliminado", "AVISO IMPORTANTE", MB_OK);
				SendDlgItemMessage(hwnd, IDC_LIST4, LB_RESETCONTENT, 0, 0);
				SetDlgItemText(hwnd, IC_C, "");
				SetDlgItemText(hwnd, IC_U, "");
				SetDlgItemText(hwnd, IC_ND, "");
				SetDlgItemText(hwnd, IC_L, "");
				SetDlgItemText(hwnd, IC_F, "");
				SetDlgItemText(hwnd, IC_CDA, "");
				guardarCar();
				guardarCartxt();
			}
		break;

		case ListadoEDIC:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG14), 0, (DLGPROC)CambioC);
			SendDlgItemMessage(hwnd, IDC_LIST4, LB_RESETCONTENT, 0, 0);
			SetDlgItemText(hwnd, IC_C, "");
			SetDlgItemText(hwnd, IC_U, "");
			SetDlgItemText(hwnd, IC_ND, "");
			SetDlgItemText(hwnd, IC_L, "");
			SetDlgItemText(hwnd, IC_F, "");
			SetDlgItemText(hwnd, IC_CDA, "");
		break;
		
		case boton_reporte:
			reporte();
			MessageBox(hwnd, "Se ha generado un txt", "AVISO", MB_OK);
			PATHE = "C:\\Users\\dpere\\source\\repos\\Borrador estructura de datos\\Borrador estructura de datos\\";
			PATHE += n;
			charStr = PATHE.c_str();
			ShellExecute(NULL, "open", charStr, NULL, NULL, SW_SHOWNORMAL);
		break;
		
		case ListadoREGC:
			EndDialog(hwnd, wParam);
		break;

		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK CambioC(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, ncomu8);
		h_combo = GetDlgItem(hwnd, IC_C2);
		h_combo = GetDlgItem(hwnd, IC_U2);
		h_combo = GetDlgItem(hwnd, IC_ND2);
		h_edit = GetDlgItem(hwnd, IC_L2);
		h_edit = GetDlgItem(hwnd, IC_F2);
		h_edit = GetDlgItem(hwnd, IC_CDA2);
		h_boton = GetDlgItem(hwnd, B_ACTC);
		h_boton = GetDlgItem(hwnd, B_CC);
		SetDlgItemText(hwnd, ncomu8, iniciarse);
		SetDlgItemText(hwnd, IC_L2,  INFO_U[3]);//LOTE
		SetDlgItemText(hwnd, IC_F2,  INFO_U[4]);//FECHA
		SetDlgItemText(hwnd, IC_CDA2, INFO_U[5]);//CENTRO
		strcpy_s(curp, 20, INFO_U[0]);
		break;


	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case B_ACTC: {
			prueba = 0;
			detonante = 0;
			GetDlgItemText(hwnd, IC_L2, INFO_U[3], 15);
			GetDlgItemText(hwnd, IC_F2, INFO_U[4], 15);
			GetDlgItemText(hwnd, IC_CDA2, INFO_U[5], 15);
			if (prim != nullptr) {
				while (detonante == 0) {
					if (prim) {
						tempo = prim;
						while (tempo) {
							if (strcmp(tempo->Curp,INFO_U[0])==0)
							{
								prueba = 1;
							}
							tempo = tempo->siguiente;
						}
						detonante = 1;
					}
				}
			}
			dvacio(INFO_U[0]);
			dvacio(INFO_U[1]);
			dvacio(INFO_U[2]);
			dvacio(INFO_U[3]);
			dvacio(INFO_U[4]);
			dvacio(INFO_U[5]);

			if (prueba == 0) {
				tempo = prim;
				while (strcmp(tempo->Curp, curp) != 0) {
					tempo = tempo->siguiente;
				}

				if (strcmp(tempo->Curp, INFO_U[0]) != 0) {
					strcpy_s(tempo->Curp, INFO_U[0]);

				}
				if (strcmp(tempo->vacuna, INFO_U[1]) != 0) {
					strcpy_s(tempo->vacuna, INFO_U[1]);

				}
				if (strcmp(tempo->No_dosis, INFO_U[2]) != 0) {
					strcpy_s(tempo->No_dosis, INFO_U[2]);

				}
				if (strcmp(tempo->lote, INFO_U[3]) != 0) {
					strcpy_s(tempo->lote, INFO_U[3]);

				}
				if (strcmp(tempo->date, INFO_U[4]) != 0) {
					strcpy_s(tempo->date, INFO_U[4]);

				}
				if (strcmp(tempo->lugar, INFO_U[5]) != 0) {
					strcpy_s(tempo->lugar, INFO_U[5]);

				}
				MessageBox(hwnd, "La informacion se ha actualizado", "MENSAJE", MB_ICONINFORMATION);
				guardarCar();
				guardarCartxt();
				EndDialog(hwnd, wParam);
			}
			else {
				MessageBox(hwnd, "Ha dejado espacios en blanco o ha registrado un curp coincidente", "MENSAJE", MB_ICONINFORMATION);
			}
		}
			break;

		case IC_C2:
			if (primero) {
				temporal = primero;
				while (temporal) {
					SendDlgItemMessage(hwnd, IC_C2, CB_INSERTSTRING, 0, (LPARAM)temporal->curp);
					temporal = temporal->siguiente;
				}
			}
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IC_C2, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IC_C2, CB_GETLBTEXT, cur, (LPARAM)INFO_U[0]);
			}
			break;

		case IC_U2:
			if (primer) {
				tempora = primer;
				while (tempora) {
					SendDlgItemMessage(hwnd,IC_U2, CB_INSERTSTRING, 0, (LPARAM)tempora->marca);
					tempora = tempora->siguiente;
				}
			}
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IC_U2, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IC_U2, CB_GETLBTEXT, cur, (LPARAM)INFO_U[1]);
			}

			break;

		case IC_ND2:
			for (a = 0; a < 4; a++) {
				SendDlgItemMessage(hwnd, IC_ND2, CB_INSERTSTRING, (WPARAM)a, (LPARAM)dosisop[a]);
			}

			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IC_ND2, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IC_ND2, CB_GETLBTEXT, cur, (LPARAM)INFO_U[2]);
			}
			break;

		case B_CC:
			EndDialog(hwnd, wParam);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK Reporte(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, reg_fum);
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return FALSE;
}



void guardarPertxt() {
archivo.open("Personatexto.txt",ios::out);
	if (primero) {
	ultimo = primero;
		while (ultimo) {
			archivo << ultimo->a_ma << endl;
			archivo << ultimo->a_pa << endl;
			archivo << ultimo->name<< endl;
			archivo << ultimo->ID << endl;
			archivo << ultimo->estadocivil << endl;
			archivo<<ultimo->fecha_nac<<endl;
			archivo<<ultimo->direccion<<endl;
			archivo<<ultimo->genero<<endl;
			archivo<<ultimo->curp<<endl;
			archivo<<ultimo->tel<<endl;
			archivo<<ultimo->trabajo<<endl;
			archivo << ultimo->nomC << endl;
			archivo << ultimo->path << endl;
			ultimo = ultimo->siguiente;
		}
	}
archivo.close();

}
void guardarVtxt() {
	archivo.open("Vacunatexto.txt", ios::out);
	if (primer) {
		ultim = primer;
		while (ultim) {
			archivo << ultim->tipo<<endl;
			archivo << ultim->marca<<endl;
			archivo << ultim->num_dosis<<endl;
			archivo << ultim->clave_v<<endl;
			archivo << ultim->desc<<endl;
			archivo << ultim->precio<<endl;
			ultim = ultim->siguiente;
		}
	}
	archivo.close();
}
void guardarUtxt() {
	archivo.open("Usuariotexto.txt", ios::out);
	if (prime) {
		ulti = prime;
		while (ulti) {
			archivo << ulti->clave_u<<endl;
			archivo << ulti->contraseña<<endl;
			archivo << ulti->a_materno<<endl;
			archivo << ulti->a_paterno<<endl;
			archivo << ulti->nombres<<endl;
			archivo << ulti->namecom<<endl;
			ulti = ulti->siguiente;
		}
	}
	archivo.close();
}
void guardarCartxt() {
	archivo.open("Carnettexto.txt", ios::out);
	if (prim) {
		ult = prim;
		while (ult) {
			archivo << ult->Curp<<endl;
			archivo << ult->vacuna << endl;
			archivo << ult->No_dosis << endl;
			archivo << ult->date<<endl;
			archivo << ult->lote<<endl;
			archivo << ult->lugar<<endl;
			archivo << ult->ID_carnet << endl;
			archivo << ult->datos.nomC << endl;
			archivo << ult->datos.ID << endl;
			archivo << ult->datos.tel << endl;
			archivo << ult->datos.direccion << endl;
			archivo << ult->datos.fecha_nac <<endl;
			archivo << ult->datos.genero <<endl;
			archivo << ult->datos.trabajo <<endl;
			ult = ult->siguiente;
		}
	}
	archivo.close();
}
void guardarPer() {
	Archivo.open("Persona.bin", ios::out | ios::binary);

	if (Archivo.is_open()) {

		ultimo = primero;

		while (ultimo != nullptr) {

			Archivo.write(reinterpret_cast<char*>(ultimo), sizeof(Persona));
			ultimo = ultimo->siguiente;
		}

	}

	Archivo.close();

}
void guardarV() {
	Archivo.open("Vacuna.bin", ios::out | ios::binary);

	if (Archivo.is_open()) {

		ultim = primer;

		while (ultim != nullptr) {

			Archivo.write(reinterpret_cast<char*>(ultim), sizeof(Vacuna));
			ultim = ultim->siguiente;
		}

	}
	Archivo.close();
}
void guardarU() {
	Archivo.open("Usuario.bin", ios::out | ios::binary);

	if (Archivo.is_open()) {

		ulti = prime;

		while (ulti != nullptr) {

			Archivo.write(reinterpret_cast<char*>(ulti), sizeof(User));
			ulti = ulti->siguiente;
		}

	}
	Archivo.close();

}
void guardarCar() {
	Archivo.open("Carnet.bin", ios::out | ios::binary);

	if (Archivo.is_open()) {

		ult = prim;

		while (ult != nullptr) {

			Archivo.write(reinterpret_cast<char*>(ult), sizeof(Carnet));
			ult = ult->siguiente;
		}

	}
	Archivo.close();

}
void leer_Per() {
	Archivo.open("Persona.bin", ios::in | ios::binary);
	if (Archivo.is_open()) {
		Archivo.seekg(0, ios::end);
		tamaño = Archivo.tellg();
		if (tamaño != 0) {
			Persona* l = new Persona;
			while (!Archivo.eof()) {
				Archivo.seekg(k * sizeof(Persona));
				Archivo.read(reinterpret_cast<char*>(l), sizeof(Persona));
				if (primero == nullptr) {
					primero = new Persona;
					strcpy_s(primero->a_ma,15,l->a_ma);
					strcpy_s(primero->a_pa,15,l->a_pa);
					strcpy_s(primero->name,15,l->name);
					strcpy_s(primero->ID,15,l->ID);
					strcpy_s(primero->estadocivil,15,l->estadocivil);
					strcpy_s(primero->fecha_nac ,15,l->fecha_nac);
					strcpy_s(primero->direccion,200, l->direccion);
					strcpy_s(primero->genero,15,l->genero);
					strcpy_s(primero->curp,20,l->curp);
					strcpy_s(primero->tel,15,l->tel);
					strcpy_s(primero->trabajo,15,l->trabajo);
					strcpy_s(primero->nomC, 52, l->nomC);
					strcpy_s(primero->path, 258, l->path);
					primero->siguiente = nullptr;
					primero->anterior = nullptr;
					ultimo = primero;
					k++;
				}
				else {
					ultimo = primero;
					while (ultimo->siguiente != nullptr) {
						ultimo = ultimo->siguiente;
					}
					ultimo->siguiente = new Persona;
					ultimo->siguiente->siguiente = nullptr;
					ultimo->siguiente->anterior = ultimo;
					ultimo = ultimo->siguiente;
					strcpy_s(ultimo->a_ma, 15, l->a_ma);
					strcpy_s(ultimo->a_pa, 15, l->a_pa);
					strcpy_s(ultimo->name, 15, l->name);
					strcpy_s(ultimo->ID, 15, l->ID);
					strcpy_s(ultimo->estadocivil, 15, l->estadocivil);
					strcpy_s(ultimo->fecha_nac, 15, l->fecha_nac);
					strcpy_s(ultimo->direccion, 200, l->direccion);
					strcpy_s(ultimo->genero, 15, l->genero);
					strcpy_s(ultimo->curp, 20, l->curp);
					strcpy_s(ultimo->tel, 15, l->tel);
					strcpy_s(ultimo->trabajo, 15, l->trabajo);
					strcpy_s(ultimo->nomC, 52, l->nomC);
					strcpy_s(ultimo->path, 258, l->path);
					k++;
				}
			}
			k = 0;

			if (primero->a_ma == "") {
				primero->siguiente = nullptr;
				primero = nullptr;
			}
			else {
				temporal = ultimo;
				if (temporal->siguiente == nullptr) {
					temporal->anterior->siguiente = temporal->siguiente;
					if (temporal->siguiente != nullptr) {
						temporal->siguiente->anterior = temporal->anterior;
					}
					delete temporal;
				}
			}
		}
	}

	Archivo.close();
}
void leer_Vac() {
	Archivo.open("Vacuna.bin", ios::in | ios::binary);
	if (Archivo.is_open()) {
		Archivo.seekg(0, ios::end);
		tamaño = Archivo.tellg();
		if (tamaño != 0) {
			Vacuna* le = new Vacuna;
			while (!Archivo.eof()) {
				Archivo.seekg(k * sizeof(Vacuna));
				Archivo.read(reinterpret_cast<char*>(le), sizeof(Vacuna));
				if (primer == nullptr) {
					primer = new Vacuna;
					strcpy_s(primer->tipo,15,le->tipo);
					strcpy_s(primer->marca ,15,le->marca);
					strcpy_s(primer->num_dosis,15,le->num_dosis);
					strcpy_s(primer->clave_v,15,le->clave_v);
					strcpy_s(primer->desc,259, le->desc);
					primer->precio = le->precio;
					primer->siguiente = nullptr;
					primer->anterior = nullptr;
					ultim = primer;
					k++;
				}
				else {
					ultim = primer;
					while (ultim->siguiente != nullptr) {
						ultim = ultim->siguiente;
					}
					ultim->siguiente = new Vacuna;
					ultim->siguiente->siguiente = nullptr;
					ultim->siguiente->anterior = ultim;
					ultim = ultim->siguiente;
					strcpy_s(ultim->tipo,15,le->tipo);
					strcpy_s(ultim->marca,15,le->marca);
					strcpy_s(ultim->num_dosis,15,le->num_dosis);
					strcpy_s(ultim->clave_v,15,le->clave_v);
					strcpy_s(ultim->desc,259, le->desc);
					ultim->precio = le->precio;
					k++;
				}
			}
			k = 0;

			if (primer->tipo == "") {
				primer->siguiente = nullptr;
				primer = nullptr;
			}
			else {
				tempora = ultim;
				if (tempora->siguiente == nullptr) {
					tempora->anterior->siguiente = tempora->siguiente;
					if (tempora->siguiente != nullptr) {
						tempora->siguiente->anterior = tempora->anterior;
					}
					delete tempora;
				}
			}
		}
	}

	Archivo.close();
}
void leer_User() {
	Archivo.open("Usuario.bin", ios::in | ios::binary);
	if (Archivo.is_open()) {
		Archivo.seekg(0, ios::end);
		tamaño = Archivo.tellg();
		if (tamaño != 0) {
			User* lec = new User;
			while (!Archivo.eof()) {
				Archivo.seekg(k * sizeof(User));
				Archivo.read(reinterpret_cast<char*>(lec), sizeof(User));
				if (prime == nullptr) {
					prime = new User;
					prime->clave_u = lec->clave_u;
					strcpy_s(prime->contraseña,15,lec->contraseña);
					strcpy_s(prime->a_materno,15,lec->a_materno);
					strcpy_s(prime->a_paterno,15,lec->a_paterno);
					strcpy_s(prime->nombres,15,lec->nombres);
					strcpy_s(conteiner ,52,"");
					strcat_s(conteiner,prime->nombres);
					strcat_s(conteiner," ");
					strcat_s(conteiner,prime->a_paterno);
					strcat_s(conteiner," ");
					strcat_s(conteiner,prime->a_materno);
					strcpy_s(prime->namecom,52,conteiner);
					prime->siguiente = nullptr;
					prime->anterior = nullptr;
					ulti = prime;
					k++;
				}
				else {
					ulti = prime;
					while (ulti->siguiente != nullptr) {
						ulti = ulti->siguiente;
					}
					ulti->siguiente = new User;
					ulti->siguiente->siguiente = nullptr;
					ulti->siguiente->anterior = ulti;
					ulti = ulti->siguiente;
					ulti->clave_u = lec->clave_u;
					strcpy_s(ulti->contraseña,15,lec->contraseña);
					strcpy_s(ulti->a_materno,15,lec->a_materno);
					strcpy_s(ulti->a_paterno,15,lec->a_paterno);
					strcpy_s(ulti->nombres,15,lec->nombres);
					strcpy_s(conteiner,52,"");
					strcat_s(conteiner, ulti->nombres);
					strcat_s(conteiner, " ");
					strcat_s(conteiner, ulti->a_paterno);
					strcat_s(conteiner, " ");
					strcat_s(conteiner,ulti->a_materno);
					strcpy_s(ulti->namecom,52,conteiner);
					k++;
				}
			}
			k = 0;

			if (prime->contraseña == "") {
				prime->siguiente = nullptr;
				prime = nullptr;
			}
			else {
				tempor = ulti;
				if (tempor->siguiente == nullptr) {
					tempor->anterior->siguiente = tempor->siguiente;
					if (tempor->siguiente != nullptr) {
						tempor->siguiente->anterior = tempor->anterior;
					}
					delete tempor;
				}
			}
		}
	}

	Archivo.close();
}
void leer_Carnet() {
	Archivo.open("Carnet.bin", ios::in | ios::binary);
	if (Archivo.is_open()) {
		Archivo.seekg(0, ios::end);
		tamaño = Archivo.tellg();
		if (tamaño != 0) {
			Carnet* lect = new Carnet;
			while (!Archivo.eof()) {
				Archivo.seekg(k * sizeof(Carnet));
				Archivo.read(reinterpret_cast<char*>(lect), sizeof(Carnet));
				if (prim == nullptr) {
					prim = new Carnet;
					strcpy_s(prim->Curp,20,lect->Curp);
					strcpy_s(prim->vacuna ,15,lect->vacuna);
					strcpy_s(prim->No_dosis ,15,lect->No_dosis);
					strcpy_s(prim->date,15,lect->date);
					strcpy_s(prim->lote,15,lect->lote);
					strcpy_s(prim->lugar,15,lect->lugar);
					strcpy_s(prim->datos.nomC, lect->datos.nomC);
					strcpy_s(prim->datos.ID, lect->datos.ID);
					strcpy_s(prim->datos.tel, lect->datos.tel);
					strcpy_s(prim->datos.direccion, lect->datos.direccion);
					strcpy_s(prim->datos.fecha_nac, lect->datos.fecha_nac);
					strcpy_s(prim->datos.genero, lect->datos.genero);
					strcpy_s(prim->datos.trabajo, lect->datos.trabajo);
					prim->ID_carnet = lect->ID_carnet;
					prim->siguiente = nullptr;
					prim->anterior = nullptr;
					ult = prim;
					k++;
				}
				else {
					ult = prim;
					while (ult->siguiente != nullptr) {
						ult = ult->siguiente;
					}
					ult->siguiente = new Carnet;
					ult->siguiente->siguiente = nullptr;
					ult->siguiente->anterior = ult;
					ult = ult->siguiente;
					strcpy_s(ult->Curp, 20, lect->Curp);
					strcpy_s(ult->vacuna, 15, lect->vacuna);
					strcpy_s(ult->No_dosis, 15, lect->No_dosis);
					strcpy_s(ult->date, 15, lect->date);
					strcpy_s(ult->lote, 15, lect->lote);
					strcpy_s(ult->lugar, 15, lect->lugar);
					strcpy_s(ult->datos.nomC, lect->datos.nomC);
					strcpy_s(ult->datos.ID, lect->datos.ID);
					strcpy_s(ult->datos.tel, lect->datos.tel);
					strcpy_s(ult->datos.direccion, lect->datos.direccion);
					strcpy_s(ult->datos.fecha_nac, lect->datos.fecha_nac);
					strcpy_s(ult->datos.genero, lect->datos.genero);
					strcpy_s(ult->datos.trabajo, lect->datos.trabajo);
					ult->ID_carnet = lect->ID_carnet;
					k++;
				}
			}
			k = 0;

			if (prim->Curp == "") {
				prim->siguiente = nullptr;
				prim = nullptr;
			}
			else {
				tempo = ult;
				if (tempo->siguiente == nullptr) {
					tempo->anterior->siguiente = tempo->siguiente;
					if (tempo->siguiente != nullptr) {
						tempo->siguiente->anterior = tempo->anterior;
					}
					delete tempo;
				}
			}
		}
	}

	Archivo.close();
}
void dvacio(char datop[70]) {
	if (strcmp(datop, "") == 0) {
		prueba++;
	}
}
Carnet* getMid(Carnet* first, Carnet* last)
{
	if (first == NULL) return NULL;
	Carnet* slow = first;
	Carnet* fast = first->siguiente;

	while (fast != last)
	{
		fast = fast->siguiente;
		if (fast != last) {
			fast = fast->siguiente;
			slow = slow->siguiente;
		}
	}

	return slow;
}
bool buscarlistaBinaria(Carnet* first, Carnet* last, int n) {
	if (first == last) {
		//cout << "Dato NO encontrado.";
		return false;
	}

	Carnet* mid = getMid(first, last);

	if (mid != NULL) {
		if (mid->ID_carnet == n) {
			strcpy_s(INFO_U[0], 20, mid->Curp);
			strcpy_s(INFO_U[1], 15, mid->vacuna);
			strcpy_s(INFO_U[2], 15, mid->No_dosis);
			strcpy_s(INFO_U[3], 15, mid->lote);
			strcpy_s(INFO_U[4], 52, mid->date);
			strcpy_s(INFO_U[5], 52, mid->lugar);
			strcpy_s(INFO_U[6], mid->datos.nomC);
			strcpy_s(INFO_U[7], mid->datos.ID);
			strcpy_s(INFO_U[8], mid->datos.tel);
			strcpy_s(INFO_U[9], mid->datos.direccion);
			strcpy_s(INFO_U[10], mid->datos.fecha_nac);
			strcpy_s(INFO_U[11], mid->datos.genero);
			strcpy_s(INFO_U[12], mid->datos.trabajo);
			e = true;
			//cout << "Dato encontrado.";
			return true;
		}

		if (mid->ID_carnet > n) {
			return buscarlistaBinaria(first, mid, n);
		}
		return buscarlistaBinaria(mid->siguiente, last, n);
	}
	//cout << "Dato NO encontrado.";
	return false;
}
void swap(Carnet* a, Carnet* b) {
	strcpy_s(temp,50, a->datos.nomC);
	strcpy_s(a->datos.nomC,50,b->datos.nomC);
	strcpy_s(b->datos.nomC,50, temp);
}
Carnet* particion(Carnet* primero, Carnet* ultimo) {
	strcpy_s(pivote ,50, ultimo->datos.nomC); // Selecciona el último elemento como pivote
	Carnet* i = primero->anterior;

	for (Carnet* j = primero; j != ultimo; j = j->siguiente) {
		if (j->datos.nomC <= pivote) {
			i = (i == nullptr) ? primero : i->siguiente; // Avanza el índice del nodo menor
			swap(i, j);
		}
	}

	i = (i == nullptr) ? primero : i->siguiente; // Avanza el índice del nodo menor
	swap(i, ultimo);

	return i;
}
void quickSort(Carnet* primero, Carnet* ultimo) {
	if (primero != nullptr&& ultimo==nullptr) {
		if (ultimo != nullptr && primero != ultimo && primero != ultimo->siguiente) {
			Carnet* pivot = particion(primero, ultimo);

			quickSort(primero, pivot->anterior);
			quickSort(pivot->siguiente, ultimo);
		}
	}
}
void imprimirLista(Carnet* cabeza,HWND hwnd) {
	while (cabeza != nullptr) {
		SendMessage(GetDlgItem(hwnd, IDC_LIST4), LB_ADDSTRING, 0, (LPARAM)cabeza->datos.nomC);
		cabeza = cabeza->siguiente;
	}
}
void swapNodes(Carnet* a, Carnet* b) {
	tempnum = a->ID_carnet;
	a->ID_carnet = b->ID_carnet;
	b->ID_carnet = tempnum;
}
void heapifyDown(Carnet* start, Carnet* end) {
	Carnet* root = start;

	while (root->siguiente != end) {
		Carnet* child = root->siguiente;

		if (root->ID_carnet < child->ID_carnet) {
			swapNodes(root, child);
		}

		root = child;
	}
}
void heapSort(Carnet* start, Carnet* end) {
	if (start != nullptr && end == nullptr) {
		// Construir el heap
		Carnet* lastParent = start;
		while (lastParent->siguiente != end) {
			lastParent = lastParent->siguiente;
		}

		while (lastParent != start) {
			heapifyDown(lastParent, end);
			lastParent = lastParent->anterior;
		}

		// Extraer los elementos uno por uno
		Carnet* last = end->anterior;
		while (last != start) {
			swapNodes(start, last);
			heapifyDown(start, last);
			last = last->anterior;
		}
	}
}
void printList(Carnet* start, Carnet* end,HWND hwnd) {
	Carnet* temp = start;
	while (temp != nullptr) {
		SendMessage(h_listbox, LB_ADDSTRING, 0, (LPARAM)std::to_string(temp->ID_carnet).c_str());
		temp = temp->siguiente;
	}
}
void reporte() {
	srand(time(NULL));
	u = rand() % 10;
	n += to_string(u);
	archivo.open(n, ios::out);
	if (prim) {
		ult = prim;
		while (ult) {
			archivo << "CURP:" << ult->Curp << endl;
			archivo <<"VACUNA: " << ult->vacuna << endl;
			archivo <<"NUMERO DE DOSIS: " << ult->No_dosis << endl;
			archivo <<"FECHA: " << ult->date << endl;
			archivo <<"NUMERO DE LOTE" << ult->lote << endl;
			archivo <<"LUGAR DE APLICACION: " << ult->lugar << endl;
			archivo <<"NUMERO DE CARNET: " << ult->ID_carnet << endl;
			archivo <<"NOMBRE COMPLETO: " << ult->datos.nomC << endl;
			archivo <<"DOCUMENTO DE IDENTIFICACION: " << ult->datos.ID << endl;
			archivo <<"TELEFONO: " << ult->datos.tel << endl;
			archivo <<"DIRECCION: " << ult->datos.direccion << endl;
			archivo <<"FECHA DE NACIMIENTO: " << ult->datos.fecha_nac << endl;
			archivo <<"GENERO: " << ult->datos.genero << endl;
			archivo <<"OCUPACION: " << ult->datos.trabajo << endl;
			archivo << endl;
			ult = ult->siguiente;
		}
	}
	archivo.close();
}
