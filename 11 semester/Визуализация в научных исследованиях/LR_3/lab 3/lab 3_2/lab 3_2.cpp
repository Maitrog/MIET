// WindowsProject1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab 3_2.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

struct ANGLS {
	double fi, teta;
};

static ANGLS angl, anglOld;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void LineCreate();
void LineDestroy();
void LinePaint(HWND);
void LineLButtonDown(HWND, int, int);
void LineMouseMove(HWND, int, int);
void DrawBox(HWND, HDC, ANGLS);
void LineLButtonUp(HWND);
void PointCorns();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LAB32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB32));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB32));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB32);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		100, 30, 700, 700, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int x, y;
	switch (message)
	{
	case WM_CREATE:
		LineCreate();
		break;

	case WM_PAINT:
		LinePaint(hWnd);
		break;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		LineLButtonDown(hWnd, x, y);
		break;

	case WM_LBUTTONUP:
		LineLButtonUp(hWnd);
		InvalidateRect(hWnd, NULL, TRUE);
		break;


	case WM_MOUSEMOVE:
		x = LOWORD(lParam);
		y = HIWORD(lParam);

		LineMouseMove(hWnd, x, y);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			angl.fi += 10;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case VK_RIGHT:
			angl.fi -= 10;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case VK_UP:
			angl.teta += 10;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case VK_DOWN:
			angl.teta -= 10;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		break;

	case WM_DESTROY:
		LineDestroy();
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0L;
}
double const M_PI = 3.141592654;

struct TDATA {
	BOOL ButtonDown;
	BOOL Drawing;
};

static TDATA Dat;


struct CORD {
	int x, y;
};

static CORD cor, corOld;

struct POINT3 {
	double x, y, z;
};

static POINT3 Point[8];
//static POINT3 Point[8], PointB[32];

struct VECTORS {
	double x, y, z;
	double dx, dy, dz;
};

static VECTORS vect[32];

struct VECMAG {
	double hx, hy, hz;
};



//координаты зарядов
POINT3 CoordCharge[4];
//величины зарядов
double qCharge[4];
//число зарядов
int NCharge;
//номер заряда
int iCharge;
//начальные точки линий поля
POINT3 PointB[26];
//массив начальных точек линий поля
POINT3 qPointB[26][4];



/*

//вершины магнитной пластинки
double Px[4], Py[4], Pz[4];
*/

//размеры поля вывода в мировых координатах и в пикселях
double xe1, xe2, ye1, ye2;
int    ne1, ne2, me1, me2;

//длины координатных осей (в мировых координатах)
double xmax, ymax, zmax;

//размеры магнитной пластинки
double ax, ay;



//радиус сферы вокруг заряда с которой начинаются линии поля
double R0;



//задаем различные параметры в начале работы приложения
void LineCreate()
{

	//размеры поля вывода в мировых координатах и в пикселях
	xe1 = -5;  xe2 = 5; ye1 = -5; ye2 = 5;
	//	ne1 = 100; ne2 = 500; me1 = 450; me2 = 50;

	//длины координатных осей (в мировых координатах)
	xmax = 3, ymax = 3, zmax = 3;

	//задаем вершины куба, связанного с подвижной системой координат
	PointCorns();


	//число зарядов
	NCharge = 4;

	//задаем параметры 3-х зарядов
	CoordCharge[0].x = 2;
	CoordCharge[0].y = 2;
	CoordCharge[0].z = 0;
	qCharge[0] = -1;

	CoordCharge[1].x = -2;
	CoordCharge[1].y = 2;
	CoordCharge[1].z = 0;
	qCharge[1] = 1;

	CoordCharge[2].x = -2;
	CoordCharge[2].y = -2;
	CoordCharge[2].z = 0;
	qCharge[2] = 1;

	CoordCharge[3].x = 2;
	CoordCharge[3].y = -2;
	CoordCharge[3].z = 0;
	qCharge[3] = -1;


	//радиус сферы вокруг заряда с которой начинаются линии поля
	R0 = 0.2;

	//начальные значения углов поворота системы координат
	angl.fi = 30; angl.teta = 60;
}


//задаем вершины куба, связанного с подвижной системой координат
void	PointCorns()
{
	Point[0].x = xmax; Point[0].y = ymax; Point[0].z = -zmax;
	Point[1].x = -xmax; Point[1].y = ymax; Point[1].z = -zmax;
	Point[2].x = -xmax; Point[2].y = -ymax; Point[2].z = -zmax;
	Point[3].x = xmax; Point[3].y = -ymax; Point[3].z = -zmax;
	Point[4].x = xmax; Point[4].y = ymax; Point[4].z = zmax;
	Point[5].x = -xmax; Point[5].y = ymax; Point[5].z = zmax;
	Point[6].x = -xmax; Point[6].y = -ymax; Point[6].z = zmax;
	Point[7].x = xmax; Point[7].y = -ymax; Point[7].z = zmax;
}


//вычисляем поле (hx,hy,hz) в заданной точке пространства (x,y,z)
VECMAG magn(double q, double x, double y, double z, double x0, double y0, double z0)
{
	VECMAG mag;

	double dx = x - x0, dy = y - y0, dz = z - z0;
	double r3 = pow(dx * dx + dy * dy + dz * dz, 1.5);

	mag.hx = q / r3 * dx; mag.hy = q / r3 * dy; mag.hz = q / r3 * dz;

	return mag;
}


void LineDestroy()
{
	PostQuitMessage(0);   //закрываем окно приложения
}



//угловые коэффициенты поворота системы координат
double sf, cf, st, ct;

//переход в видовую систему координат и ортографическое проецирование 
double Xe(double x, double y)
{
	return -sf * x + cf * y;
}

//переход в видовую систему координат и ортографическое проецирование 
double Ye(double x, double y, double z)
{
	return -ct * cf * x - ct * sf * y + st * z;
}


//переход от видовых координат к экранным координатам 

//переход от координты x к пикселю n
inline int xn(double x)
{
	return (int)((x - xe1) / (xe2 - xe1) * (ne2 - ne1)) + ne1;
}


//переход от координты y к пикселю m
inline int ym(double y)
{
	return (int)((y - ye1) / (ye2 - ye1) * (me2 - me1)) + me1;
}




//задаем начальные точки линий поля
void LineBeginPoints(double x0, double y0, double z0)
{
	double dfi = M_PI / 4, dtet = M_PI / 4;
	double fi, tet;
	int k = 0;

	PointB[0].x = x0; PointB[0].y = y0; PointB[0].z = z0 + R0;

	for (int i = 1; i <= 3; i++)
	{
		tet = i * dtet;
		for (int j = 0; j < 8; j++)
		{
			fi = j * dfi;
			k++;
			PointB[k].x = x0 + R0 * sin(tet) * cos(fi);
			PointB[k].y = y0 + R0 * sin(tet) * sin(fi);
			PointB[k].z = z0 + R0 * cos(tet);
		}
	}
	PointB[25].x = x0; PointB[25].y = y0; PointB[25].z = z0 - R0;

}


//рисуем 2D вектор-стрелку
void arrowVector(HDC hdc, int x1, int y1, int x2, int y2, COLORREF rgb)
{
	int k = 5; //размеры стрелки в пикселях
	double d = sqrt((double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
	double nx = (x2 - x1) / d, ny = (y2 - y1) / d;
	double mx = -ny, my = nx;

	int x3, y3, x4, y4, x0, y0;

	x0 = int(k * nx) + x1;
	y0 = int(k * ny) + y1;
	x3 = int(k * mx) + x1;
	y3 = int(k * my) + y1;
	x4 = -int(k * mx) + x1;
	y4 = -int(k * my) + y1;

	HPEN hPen = CreatePen(PS_SOLID, 2, rgb);
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, x3, y3, 0);
	LineTo(hdc, x0, y0);
	LineTo(hdc, x4, y4);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}





//"рисует" одну линию поля из начальной точки x0, y0,z0 
//учитывается направление линии с поиощью знака заряда q
void LineField(HDC hdc, double x0, double y0, double z0, double q, int iCh)
{
	COLORREF rgb;
	VECTORS vect;
	vect.x = x0;
	vect.y = y0;
	vect.z = z0;

	//видовые координаты проецируемой точки
//	double xe, ye, ze1, ze2;
	double xe, ye;
	//координаты пикселов
	int x1, y1, x2, y2;

	int Nstep = 100; //среднее число шагов в линии поля
	double dt = 2 * sqrt(xmax * xmax + ymax * ymax + zmax * zmax) / Nstep; //длина шага на линии поля

	//	double dt = 0.1; //длина шага на линии поля
	double x, y, z, Hx, Hy, Hz, Ha;
	int k = 0;

	VECMAG mag;

	HPEN hPen, hPenOld;


	//меняем знак шага и цвет линии в зависимости от знака заряда
	if (q < 0)
	{
		dt = -dt;
		rgb = RGB(0, 0, 255);
		hPen = CreatePen(PS_SOLID, 3, rgb);
		hPenOld = SelectPen(hdc, hPen);
	}
	else
	{
		rgb = RGB(255, 0, 0);
		hPen = CreatePen(PS_SOLID, 3, rgb);
		hPenOld = SelectPen(hdc, hPen);
	}
	int nbr = 0;
	double xt1, yt1, zt1, xt2, yt2, zt2;

	vect.dx = 0;
	vect.dy = 0;
	vect.dz = 0;

	//цикл дивижения по линии поля
	//прекражение движения в двух случаях
	// 1 - линия пересекла границу куба
	// 2 - линия подошла слишком близко к точечному заряду
	// 3 - линия подошла слишком близко к точке сингулярности поля
	do
	{

		x = vect.x;
		y = vect.y;
		z = vect.z;

		int jCh;

		//складываются поля от разных зарядов
		// NCharge - число зарядов
		double magx = 0, magy = 0, magz = 0;
		for (jCh = 0; jCh < NCharge; jCh++)
		{

			mag = magn(qCharge[jCh], x, y, z, CoordCharge[jCh].x,
				CoordCharge[jCh].y, CoordCharge[jCh].z);
			magx += mag.hx;
			magy += mag.hy;
			magz += mag.hz;

		}

		Hx = magx;
		Hy = magy;
		Hz = magz;

		//линия подошла к точке сингулярности, где Ha = 0 !!
		//резкое изменение направления линии > 90 градусов
		if (Hx * vect.dx + Hy * vect.dy + Hz * vect.dz < 0)
			break;

		//вычисляем направление вектора поля
		//проекции единичного вектора
		Ha = sqrt(Hx * Hx + Hy * Hy + Hz * Hz);


		vect.dx = Hx / Ha;
		vect.dy = Hy / Ha;
		vect.dz = Hz / Ha;


		//учитываем направление движения по линии поля
		//в зависимости от знака заряда
		if (q > 0)
		{
			xt1 = vect.x; yt1 = vect.y; zt1 = vect.z;
			xt2 = xt1 + vect.dx * dt;
			yt2 = yt1 + vect.dy * dt;
			zt2 = zt1 + vect.dz * dt;

		}
		else
		{
			xt2 = vect.x; yt2 = vect.y; zt2 = vect.z;
			xt1 = xt2 + vect.dx * dt;
			yt1 = yt2 + vect.dy * dt;
			zt1 = zt2 + vect.dz * dt;
		}

		double dd1, dd2, dx, dy, dz;


		//проверяем подошла ли линия поля слишко близко
		//к одному из точечных зарядов
		int flag;
		flag = 0;
		for (jCh = 0; jCh < NCharge; jCh++)
		{
			dx = xt1 - CoordCharge[jCh].x;
			dy = yt1 - CoordCharge[jCh].y;
			dz = zt1 - CoordCharge[jCh].z;
			dd1 = dx * dx + dy * dy + dz * dz;

			dx = xt2 - CoordCharge[jCh].x;
			dy = yt2 - CoordCharge[jCh].y;
			dz = zt2 - CoordCharge[jCh].z;
			dd2 = dx * dx + dy * dy + dz * dz;

			if ((dd1 < 0.1 * R0 * R0) || (dd2 < 0.1 * R0 * R0))
				flag = 1;
		}

		if (flag == 1)
			break;

		/*
				//перводим мировые координаты в видовые с центральным
				//проецированием, и переводим координаты видовой плоскости
				//в координаты пикселей
				xe=Xe(xt1,yt1,zt1);
				ye=Ye(xt1,yt1,zt1);
				ze1=Ze(xt1,yt1,zt1);
				x1=xn(xe);
				y1=ym(ye);

				xe=Xe(xt2,yt2,zt2);
				ye=Ye(xt2,yt2,zt2);
				ze2=Ze(xt2,yt2,zt2);
				x2=xn(xe);
				y2=ym(ye);

		*/			xe = Xe(xt1, yt1);
		ye = Ye(xt1, yt1, zt1);
		x1 = xn(xe);
		y1 = ym(ye);

		xe = Xe(xt2, yt2);
		ye = Ye(xt2, yt2, zt2);
		x2 = xn(xe);
		y2 = ym(ye);

		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);

		/*
				//"рисуем" отрезок линии поля заданной толщиной и цветом
				//с учетом Z-буфера
				ZbufLineWidth(hdc,x1,y1,x2,y2,ze1,ze2,3,rgb);
		*/
		if (q > 0)
		{
			vect.x = xt2;
			vect.y = yt2;
			vect.z = zt2;
		}
		else
		{
			vect.x = xt1;
			vect.y = yt1;
			vect.z = zt1;
		}

		//после 10-и шагов на лини поля "рисуем" стрелку
		k++;
		if(k == 10)
		{
			arrowVector(hdc,x1,y1,x2,y2,RGB(0,0,255));
			k = 0;
		}

	//прекращаем рисовать линию поля на границе куба
	} while ((x > -1.1 * xmax) && (x < 1.1 * xmax) &&
		(y > -1.1 * ymax) && (y < 1.1 * ymax) && (z > -1.1 * zmax) && (z < 1.1 * zmax));

	SelectPen(hdc, hPenOld);
	DeletePen(hPen);

}


/*


//рисует одну линию поля из начальной точки PointB
void LineField(HDC hdc,POINT3 PointB)
{

	VECTORS vect;
		vect.x = PointB.x;
		vect.y = PointB.y;
		vect.z = PointB.z;

	//видовые координаты проецируемой точки
	double xe, ye;
//координаты пикселов
	int x1,y1,x2,y2;

	double dt = 0.01;
	double x, y, z, Hx, Hy, Hz, Ha;

	VECMAG mag;
	double xt1,yt1,zt1,xt2,yt2,zt2;

	do
		{
			x = vect.x;
			y = vect.y;
			z = vect.z;

			mag = magn(x,y,z);

			Hx = mag.hx;
			Hy = mag.hy;
			Hz = mag.hz;

			Ha = sqrt(Hx*Hx + Hy*Hy + Hz*Hz);

			vect.dx = Hx/Ha;
			vect.dy = Hy/Ha;
			vect.dz = Hz/Ha;


			xt1 = vect.x; yt1 = vect.y; zt1 = vect.z;
			xt2 = xt1 + vect.dx*dt;
			yt2 = yt1 + vect.dy*dt;
			zt2 = zt1 + vect.dz*dt;

			xe=Xe(xt1,yt1);
			ye=Ye(xt1,yt1,zt1);
			x1=xn(xe);
			y1=ym(ye);

			xe=Xe(xt2,yt2);
			ye=Ye(xt2,yt2,zt2);
			x2=xn(xe);
			y2=ym(ye);

			MoveToEx(hdc,x1,y1,NULL);
			LineTo(hdc,x2,y2);

			vect.x = xt2;
			vect.y = yt2;
			vect.z = zt2;


		}while((x>-xmax)&&(x<xmax)&&(y>-ymax)&&(y<ymax)&&(z>-zmax)&&(z<zmax));
}

*/



//"рисует точечный заряд" в виде круга радиусом 5 пикселей,
// цветом rgb
//x0,y0,z0 - координаты точечного заряда в мировой системе координат
void Circle(HDC hdc, double x0, double y0, double z0, COLORREF rgb)
{
	int i, j;
	int  x, y, x1, y1;
	//	double xe,ye,zz;
	double xe, ye;
	//	unsigned long p;
	unsigned char r, g, b;


	xe = Xe(x0, y0);
	ye = Ye(x0, y0, z0);

	//	xe=Xe(x0,y0,z0);
	//	ye=Ye(x0,y0,z0);
	//	zz=Ze(x0,y0,z0);
	x = xn(xe);
	y = ym(ye);

	COLORREF crColor;

	r = (unsigned char)rgb;
	g = (unsigned char)(rgb >> 8);
	b = (unsigned char)(rgb >> 16);

	crColor = RGB(r, g, b);

	for (i = -5; i <= 5; i++)
		for (j = -5; j <= 5; j++)
		{
			if (i * i + j * j <= 25)
			{
				x1 = x + i; y1 = y + j;
				if ((x1 >= ne1) && (x1 <= ne2) && (y1 >= me2) && (y1 <= me1))
				{
					SetPixel(hdc, x1, y1, crColor);

				}
			}
		}

}





//рисуем картину линий поля, координтные оис, куб и т.д.
void LinePaint(HWND hwnd)
{

	//связываем размеры поля вывода с размерами клиентской области окна
	//--------------------------------------------------------------------
	RECT rct;
	GetClientRect(hwnd, &rct);

	ne1 = rct.left + 50; ne2 = rct.right - 50;
	me1 = rct.bottom - 50; me2 = rct.top + 50;
	//------------------------------------------------------------------

	PAINTSTRUCT ps;

	//получаем контест устройства для экрана
	HDC hdcWin = BeginPaint(hwnd, &ps);

	HDC hdc = CreateCompatibleDC(hdcWin); //создаем контекст
	//памяти связаный с контекстом экрана

//памяти надо придать вид экрана - подходт битовая карта с форматом
// как у экрана. В памяти будем рисовать на битовой карте
	HBITMAP hBitmap, hBitmapOld;
	hBitmap = CreateCompatibleBitmap(hdcWin, ne2, me1); //создаем
	//битовую карту совместмую с контекстом экрана
	hBitmapOld = (HBITMAP)SelectObject(hdc, hBitmap); //помещаем
	// битовую карту в контекст памяти


//создание прямоугольной области
	HRGN hrgn2 = CreateRectRgn(ne1, me2 - 30, ne2, me1);

	//заливаем выделенную область светлосерым цветом
	HBRUSH hBrush2 = CreateSolidBrush(RGB(0xC0, 0xC0, 0xC0));
	FillRgn(hdc, hrgn2, hBrush2);



	HPEN hPen, hPenOld;

	MoveToEx(hdc, ne1, me1 - 1, NULL);
	LineTo(hdc, ne2 - 1, me1 - 1);
	LineTo(hdc, ne2 - 1, me2);
	LineTo(hdc, ne1, me2);
	LineTo(hdc, ne1, me1);


	//вычисление угловых коэффициентов поворота системы координат
	sf = sin(M_PI * angl.fi / 180);
	cf = cos(M_PI * angl.fi / 180);
	st = sin(M_PI * angl.teta / 180);
	ct = cos(M_PI * angl.teta / 180);


	//информация об углах поворота системы координат
	TCHAR ss[20];
	SetBkColor(hdc, RGB(0xC0, 0xC0, 0xC0));
	SetTextColor(hdc, RGB(0, 0, 0x80));
	swprintf_s(ss, 20, L"fi = %4.0lf", angl.fi);
	TextOut(hdc, (ne1 + ne2) / 2 - 80, me2 - 25, ss, 9);
	swprintf_s(ss, 20, L"teta = %4.0lf", angl.teta);
	TextOut(hdc, (ne1 + ne2) / 2 + 20, me2 - 25, ss, 11);




	int iCh;

	/*
		//"рисуем" электрические заряды заданным цветом заполняя Z-буфер
	*/
	//"рисуем" электрические заряды заданным цветом	
	//-----------------------------------------------------------------------
	for (iCh = 0; iCh < NCharge; iCh++)
	{

		if (qCharge[iCh] < 0)
			Circle(hdc, CoordCharge[iCh].x, CoordCharge[iCh].y,
				CoordCharge[iCh].z, RGB(0, 0, 255));
		else
			Circle(hdc, CoordCharge[iCh].x, CoordCharge[iCh].y,
				CoordCharge[iCh].z, RGB(255, 0, 0));
	}
	//------------------------------------------------------------------




	//задаем начальные точки линий поля для всех зарядов
	//------------------------------------------------------
	for (iCh = 0; iCh < NCharge; iCh++)
	{
		LineBeginPoints(CoordCharge[iCh].x, CoordCharge[iCh].y, CoordCharge[iCh].z);
		for (int n = 0; n < 26; n++)
		{
			qPointB[n][iCh].x = PointB[n].x;
			qPointB[n][iCh].y = PointB[n].y;
			qPointB[n][iCh].z = PointB[n].z;
		}
	}
	//-------------------------------------------------------


/*
	//"рисуем" линии поля заполняя Z-буфер для всех зарядов
*/

//"рисуем" линии поля для всех зарядов
//----------------------------------------------------------------
	for (iCh = 0; iCh < NCharge; iCh++)
	{
		double x0, y0, z0;
		for (int i = 0; i < 26; i++)
		{
			x0 = qPointB[i][iCh].x; y0 = qPointB[i][iCh].y; z0 = qPointB[i][iCh].z;
			LineField(hdc, x0, y0, z0, qCharge[iCh], iCh);

		}
	}
	//-----------------------------------------------------------------------



//------------------------------------------------------------------------
//рисуем координтные оси
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	hPenOld = SelectPen(hdc, hPen);

	//видовые координаты проецируемой точки
	double xe, ye;
	//координаты пикселов
	int x1, y1, x2, y2;


	//ось Ox
	xe = Xe(-1.5 * xmax / 3, 0);
	ye = Ye(-1.5 * xmax / 3, 0, 0);
	x1 = xn(xe);
	y1 = ym(ye);
	xe = Xe(1.5 * xmax, 0);
	ye = Ye(1.5 * xmax, 0, 0);
	x2 = xn(xe);
	y2 = ym(ye);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	SetBkColor(hdc, RGB(0xC0, 0xC0, 0xC0));
	SetTextColor(hdc, RGB(120, 120, 120));
	TextOut(hdc, x2, y2, _T("X"), 1);

	//Ось Oy
	xe = Xe(0, -1.5 * ymax / 3);
	ye = Ye(0, -1.5 * ymax / 3, 0);
	x1 = xn(xe);
	y1 = ym(ye);
	xe = Xe(0, 1.5 * ymax);
	ye = Ye(0, 1.5 * ymax, 0);
	x2 = xn(xe);
	y2 = ym(ye);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	SetBkColor(hdc, RGB(0xC0, 0xC0, 0xC0));
	SetTextColor(hdc, RGB(120, 120, 120));
	TextOut(hdc, x2, y2, _T("Y"), 1);

	//Ось Oz
	xe = Xe(0, 0);
	ye = Ye(0, 0, -1.5 * zmax / 3);
	x1 = xn(xe);
	y1 = ym(ye);
	xe = Xe(0, 0);
	ye = Ye(0, 0, 1.5 * zmax);
	x2 = xn(xe);
	y2 = ym(ye);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	SetBkColor(hdc, RGB(0xC0, 0xC0, 0xC0));
	SetTextColor(hdc, RGB(120, 120, 120));
	TextOut(hdc, x2, y2, _T("Z"), 1);

	SelectPen(hdc, hPenOld);
	DeletePen(hPen);
	//-----------------------------------------------------------------------------

	/*
	//---------------------------------------------------------------------------
	//рисуем магнитную пластнику желтым цветом, толщиной 4 пикселя
		hPen = CreatePen(PS_SOLID,4,RGB(255,255,0));
		hPenOld = SelectPen(hdc,hPen);

		double xt1,yt1,zt1,xt2,yt2,zt2;
		int j;

		for(int i=0; i<4; i++)
		{
			j = i + 1;
			if(j==4)
				j = 0;
			xt1 = Px[i]; yt1 = Py[i]; zt1 = Pz[i];
			xt2 = Px[j]; yt2 = Py[j]; zt2 = Pz[j];

			xe=Xe(xt1,yt1);
			ye=Ye(xt1,yt1,zt1);
			x1=xn(xe);
			y1=ym(ye);

			xe=Xe(xt2,yt2);
			ye=Ye(xt2,yt2,zt2);
			x2=xn(xe);
			y2=ym(ye);

			MoveToEx(hdc,x1,y1,NULL);
			LineTo(hdc,x2,y2);
		}


		SelectPen(hdc,hPenOld);
		DeletePen(hPen);
	//------------------------------------------------------------------






	//----------------------------------------------------------------
	//рисуем линии поля

	//рисуем 16 линий поля красным цветом
		hPen = CreatePen(PS_SOLID,2,RGB(255,0,0));
		hPenOld = SelectPen(hdc,hPen);

		for(int i=0; i<16; i++)
		{
			LineField(hdc,PointB[i]);

		}

		SelectPen(hdc,hPenOld);
		DeletePen(hPen);


	//рисуем 16 линий поля синим цветом
		hPen = CreatePen(PS_SOLID,2,RGB(0,0,255));
		hPenOld = SelectPen(hdc,hPen);

		for(int i=16; i<32; i++)
		{
			LineField(hdc,PointB[i]);
		}

		SelectPen(hdc,hPenOld);
		DeletePen(hPen);
	//-----------------------------------------------------------------------
	*/

	//----------------------------------------------------------------------
	//рисуем куб
	hPen = CreatePen(PS_SOLID, 1, RGB(160, 160, 160));
	hPenOld = SelectPen(hdc, hPen);

	DrawBox(hwnd, hdc, angl);

	SelectPen(hdc, hPenOld);
	DeletePen(hPen);
	//------------------------------------------------------------------------

	BitBlt(hdcWin, ne1, me2 - 30, ne2, me1, hdc, ne1, me2 - 30, SRCCOPY); //копи-
	//руем контекст памяти в контекст экрана

	DeleteObject(hBrush2);
	DeleteObject(hrgn2);


	SelectObject(hdc, hBitmapOld); //востанавливаем контекст памяти
	DeleteObject(hBitmap); //убираем битовую карту
	DeleteDC(hdc);  //  освобождаем контекст памяти


	EndPaint(hwnd, &ps);
}



//обрабатывает нажатие левой клавиши мышки
void LineLButtonDown(HWND hwnd, int x, int y)
{
	Dat.ButtonDown = TRUE;
	Dat.Drawing = FALSE;

	anglOld.fi = angl.fi;
	anglOld.teta = angl.teta;
	corOld.x = x;
	corOld.y = y;

	//при нажатии клавиши мыши выделяется куб синим цветом
	HDC PaintDC = GetDC(hwnd);
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	hPenOld = SelectPen(PaintDC, hPen);

	SetROP2(PaintDC, R2_NOTXORPEN);

	DrawBox(hwnd, PaintDC, anglOld);

	SelectPen(PaintDC, hPenOld);
	DeletePen(hPen);

	ReleaseDC(hwnd, PaintDC);
}

//обрабатывает отпускание левой клавиши мышки
void LineLButtonUp(HWND hwnd)
{
	if (Dat.ButtonDown && Dat.Drawing)
		Dat.Drawing = FALSE;

	Dat.ButtonDown = FALSE;
}


//обрабатывает движение мыши при нажатой левой клавиши
void LineMouseMove(HWND hwnd, int x, int y)
{

	if (Dat.ButtonDown)
	{
		Dat.Drawing = TRUE;

		HDC PaintDC = GetDC(hwnd);

		//перерисовывает куб в новом положении в режиме NOTXOR
		HPEN hPen, hPenOld;
		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		hPenOld = SelectPen(PaintDC, hPen);

		SetROP2(PaintDC, R2_NOTXORPEN);

		DrawBox(hwnd, PaintDC, anglOld);

		angl.fi += corOld.x - x;
		angl.teta += corOld.y - y;

		corOld.x = x; corOld.y = y;

		anglOld.fi = angl.fi;
		anglOld.teta = angl.teta;

		DrawBox(hwnd, PaintDC, anglOld);

		SelectPen(PaintDC, hPenOld);
		DeletePen(hPen);


		//информация об углах поворота куба
		TCHAR ss[20];
		SetBkColor(PaintDC, RGB(0xC0, 0xC0, 0xC0));
		SetTextColor(PaintDC, RGB(0, 0, 0x80));
		swprintf_s(ss, 20, L"fi = %4.0lf", angl.fi);
		TextOut(PaintDC, (ne1 + ne2) / 2 - 80, me2 - 25, ss, 9);
		swprintf_s(ss, 20, L"teta = %4.0lf", angl.teta);
		TextOut(PaintDC, (ne1 + ne2) / 2 + 20, me2 - 25, ss, 11);

		ReleaseDC(hwnd, PaintDC);
	}

}


//рисуем куб, связанный с подвижной системой координат
void DrawBox(HWND hwnd, HDC hdc, ANGLS an)
{
	sf = sin(M_PI * an.fi / 180);
	cf = cos(M_PI * an.fi / 180);
	st = sin(M_PI * an.teta / 180);
	ct = cos(M_PI * an.teta / 180);

	double xe, ye;
	int x1, y1, x2, y2;
	double xt1, yt1, zt1, xt2, yt2, zt2;
	int j;

	for (int i = 0; i < 4; i++)
	{
		j = i + 1;
		if (j == 4)
			j = 0;
		xt1 = Point[i].x; yt1 = Point[i].y; zt1 = Point[i].z;
		xt2 = Point[j].x; yt2 = Point[j].y; zt2 = Point[j].z;

		xe = Xe(xt1, yt1);
		ye = Ye(xt1, yt1, zt1);
		x1 = xn(xe);
		y1 = ym(ye);

		xe = Xe(xt2, yt2);
		ye = Ye(xt2, yt2, zt2);
		x2 = xn(xe);
		y2 = ym(ye);

		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
	}



	for (int i = 4; i < 8; i++)
	{
		j = i + 1;
		if (j == 8)
			j = 4;
		xt1 = Point[i].x; yt1 = Point[i].y; zt1 = Point[i].z;
		xt2 = Point[j].x; yt2 = Point[j].y; zt2 = Point[j].z;

		xe = Xe(xt1, yt1);
		ye = Ye(xt1, yt1, zt1);
		x1 = xn(xe);
		y1 = ym(ye);

		xe = Xe(xt2, yt2);
		ye = Ye(xt2, yt2, zt2);
		x2 = xn(xe);
		y2 = ym(ye);

		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
	}

	for (int i = 0; i < 4; i++)
	{
		xt1 = Point[i].x; yt1 = Point[i].y; zt1 = Point[i].z;
		xt2 = Point[i + 4].x; yt2 = Point[i + 4].y; zt2 = Point[i + 4].z;

		xe = Xe(xt1, yt1);
		ye = Ye(xt1, yt1, zt1);
		x1 = xn(xe);
		y1 = ym(ye);

		xe = Xe(xt2, yt2);
		ye = Ye(xt2, yt2, zt2);
		x2 = xn(xe);
		y2 = ym(ye);

		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
	}


	for (int i = 0; i < 2; i++)
	{
		xt1 = Point[i].x; yt1 = Point[i].y; zt1 = Point[i].z;
		xt2 = Point[i + 2].x; yt2 = Point[i + 2].y; zt2 = Point[i + 2].z;

		xe = Xe(xt1, yt1);
		ye = Ye(xt1, yt1, zt1);
		x1 = xn(xe);
		y1 = ym(ye);

		xe = Xe(xt2, yt2);
		ye = Ye(xt2, yt2, zt2);
		x2 = xn(xe);
		y2 = ym(ye);

		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
	}


}