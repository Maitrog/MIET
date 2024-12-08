#include "framework.h"
#include "lab 3_6.h"

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
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void LineCreate();
void LineDestroy();
void LinePicture(HWND, int);
void LineLButtonDown(HWND, int, int);
void LineMouseMove(HWND, int, int);
void DrawBox(HWND, HDC, ANGLS);
void LineLButtonUp(HWND);
void PointCorns();
void arrowVector(HDC hdc, int x1, int y1, int x2, int y2, double ze, COLORREF rgb);
void LineField(HDC hdc, double x0, double y0, double z0, double q, int iCh);
double ZPalet(double z);
void ZbufLineWidth(HDC hdc, int x1, int y1, int x2, int y2,
	double ze1, double ze2, int w, COLORREF rgb);
void ZbufParallelogram(HDC, int, int, double, int, int, double,
	int, int, double, int, int, double, COLORREF);

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
	LoadStringW(hInstance, IDC_LAB36, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB36));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB36));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
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

	HMENU hMenu = CreateMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)IDD_DIALOG1, TEXT("Data"));
	SetMenu(hWnd, hMenu);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//функция обработки сообщений (функция окна) 
LRESULT CALLBACK  WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{

	int x, y;
	INT_PTR result;
	switch (msg)
	{
	case WM_CREATE:
		LineCreate();
		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDD_DIALOG1:
			result = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, About);
			if (result == IDOK) {
				LinePicture(hwnd, 2);
				// Здесь можно использовать обновленные значения переменных, например xe1, xe2 и т.д.
			}
			//DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, About, (LPARAM)hwnd);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
		//			InvalidateRect(hwnd,NULL,TRUE);
		LinePicture(hwnd, 1);
		break;

	case WM_SIZE:
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		LineLButtonDown(hwnd, x, y);
		break;

	case WM_LBUTTONUP:
		LineLButtonUp(hwnd);
		LinePicture(hwnd, 2);
		break;


	case WM_MOUSEMOVE:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		LineMouseMove(hwnd, x, y);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			angl.fi += 10;
			LinePicture(hwnd, 2);
			break;

		case VK_RIGHT:
			angl.fi -= 10;
			LinePicture(hwnd, 2);
			break;

		case VK_UP:
			angl.teta += 10;
			LinePicture(hwnd, 2);
			break;

		case VK_DOWN:
			angl.teta -= 10;
			LinePicture(hwnd, 2);
			break;
		}
		break;

	case WM_DESTROY:
		LineDestroy();
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0L;
}


double const M_PI = 3.141592654;

//структура 3D-точки
struct POINT3 {
	double x, y, z;
};

//структура операций с мышкой
struct TDATA {
	BOOL ButtonDown;
	BOOL Drawing;
};

TDATA Dat;


//структура точки в пиксельной плоскости
struct CORD {
	int x, y;
};

CORD cor, corOld;

//вершины куба, связанного с подвижной системой координат
POINT3 Point[8];
//начальные точки линий поля
//POINT3 PointB[72];

//структура 3D-вектора
struct VECTORS {
	double x, y, z;
	double dx, dy, dz;
};


//структура вектора магнитного поля
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





//структура для трех цветов модели RGB
struct ColorS {
	unsigned char R, G, B;
};

//структура Z-буффер
struct ZbuffS {
	double z; //глубина буфера для данного пиксела
	ColorS c; //три цвета RGB для данного пиксела
};

ZbuffS* zb;


//число пикселей в окне вывода
unsigned long Np, Mp, NM;


//вершины магнитной пластинки
double Px[4], Py[4], Pz[4];

//размеры поля вывода в мировых координатах и в пикселях
double xe1, xe2, ye1, ye2;
int    ne1, ne2, me1, me2;

//длины координатных осей (в мировых координатах) (размер куба)
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



/*
//вычисляем магнитное поле (hx,hy,hz) в заданной точке пространства (x,y,z)
VECMAG magn(double x, double y, double z)
{
	VECMAG mag;
	double s11, s12, s21, s22;
	double u1, u2, v1, v2;

	u1 = x - ax; u2 = x + ax;
	v1 = y - ay; v2 = y + ay;

	s11 = sqrt(u1*u1 + v1*v1 + z*z);
	s12 = sqrt(u1*u1 + v2*v2 + z*z);
	s21 = sqrt(u2*u2 + v1*v1 + z*z);
	s22 = sqrt(u2*u2 + v2*v2 + z*z);


	mag.hx =
			 log(((v1 + s21)/(v1 + s11))*((v2 + s12)/(v2 + s22)));
	mag.hy =
			 log(((u1 + s12)/(u1 + s11))*((u2 + s21)/(u2 + s22)));
	mag.hz =
			 atan((u2*v2)/(z*s22)) - atan((u1*v2)/(z*s12)) -
			 atan((u2*v1)/(z*s21)) + atan((u1*v1)/(z*s11));

	return mag;
}
*/

//закрываем окно приложения
void LineDestroy()
{
	PostQuitMessage(0);
}


//угловые коэффициенты поворота системы координат
double sf, cf, st, ct;

//параметры центрального проектирования
double dCentral = 4, cCentral = 3;

//переход из мировой системы координат в видовую
//центральное проектирование
inline double Xe(double x, double y, double z)
{
	double u = (dCentral + cCentral - (st * cf * x + st * sf * y + ct * z)) / cCentral;
	return (-sf * x + cf * y) / u;
}

//переход из мировой системы координат в видовую
// центральное проектирование
inline double Ye(double x, double y, double z)
{
	double u = (dCentral + cCentral - (st * cf * x + st * sf * y + ct * z)) / cCentral;
	return (-ct * cf * x - ct * sf * y + st * z) / u;
}

//переход из мировой системы координат в видовую
//отрографическое проектирование
inline double Ze(double x, double y, double z)
{
	return st * cf * x + st * sf * y + ct * z - dCentral;
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




//"рисуем" 2D вектор-стрелку
//с помощью функций работающих с Z-буфером
void arrowVector(HDC hdc, int x1, int y1, int x2, int y2, double ze, COLORREF rgb)
{

	int k = 5; //размеры стрелки в пикселях
	double d = sqrt((double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
	double ax = (x1 - x2) / d, ay = (y1 - y2) / d;
	int x3, y3, x4, y4, x0, y0;

	x0 = int(k * ax) + x2;
	y0 = int(k * ay) + y2;
	x3 = -int(k * ay) + x0;
	y3 = int(k * ax) + y0;
	x4 = int(k * ay) + x0;
	y4 = -int(k * ax) + y0;


	ZbufLineWidth(hdc, x3, y3, x2, y2, ze, ze, 2, rgb);
	ZbufLineWidth(hdc, x2, y2, x4, y4, ze, ze, 2, rgb);
}




//"рисует" одну линию поля из начальной точки x0, y0,z0 
//учитывается направление линии с поиощью знака заряда q
//"рисует" одну линию поля из начальной точки PointB 
//с помощью функций работающих с Z-буфером
void LineField(HDC hdc, double x0, double y0, double z0, double q, int iCh)
{
	COLORREF rgb;
	VECTORS vect;
	vect.x = x0;
	vect.y = y0;
	vect.z = z0;

	//видовые координаты проецируемой точки
	double xe, ye, ze1, ze2;
	//	double xe, ye;
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


		//перводим мировые координаты в видовые с центральным
		//проецированием, и переводим координаты видовой плоскости
		//в координаты пикселей
		xe = Xe(xt1, yt1, zt1);
		ye = Ye(xt1, yt1, zt1);
		ze1 = Ze(xt1, yt1, zt1);
		x1 = xn(xe);
		y1 = ym(ye);

		xe = Xe(xt2, yt2, zt2);
		ye = Ye(xt2, yt2, zt2);
		ze2 = Ze(xt2, yt2, zt2);
		x2 = xn(xe);
		y2 = ym(ye);




		//"рисуем" отрезок линии поля заданной толщиной и цветом
		//с учетом Z-буфера
		ZbufLineWidth(hdc, x1, y1, x2, y2, ze1, ze2, 3, rgb);

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
		if (k == 10)
		{
			//			arrowVector(hdc,x1,y1,x2,y2,RGB(0,0,255));
			arrowVector(hdc, x1, y1, x2, y2, ze2, RGB(0, 0, 255));
			k = 0;
		}

		//прекращаем рисовать линию поля на границе куба
	} while ((x > -1.1 * xmax) && (x < 1.1 * xmax) &&
		(y > -1.1 * ymax) && (y < 1.1 * ymax) && (z > -1.1 * zmax) && (z < 1.1 * zmax));

	SelectPen(hdc, hPenOld);
	DeletePen(hPen);

}


//"рисует точечный заряд" в виде круга радиусом 5 пикселей,
// цветом rgb, заполняя Z-буфер
//x0,y0,z0 - координаты точечного заряда в мировой системе координат
void ZbufCircle(HDC hdc, double x0, double y0, double z0, COLORREF rgb)
{
	int i, j;
	int  x, y, x1, y1;
	double xe, ye, zz;
	unsigned long p;
	unsigned char r, g, b;


	xe = Xe(x0, y0, z0);
	ye = Ye(x0, y0, z0);
	zz = Ze(x0, y0, z0);
	x = xn(xe);
	y = ym(ye);


	for (i = -5; i <= 5; i++)
		for (j = -5; j <= 5; j++)
		{
			if (i * i + j * j <= 25)
			{
				x1 = x + i; y1 = y + j;
				if ((x1 >= ne1) && (x1 <= ne2) && (y1 >= me2) && (y1 <= me1))
				{
					p = (x1 - ne1) + (y1 - me2) * Np;
					if (zb[p].z < zz)
					{
						zb[p].z = zz;
						r = (unsigned char)rgb;
						g = (unsigned char)(rgb >> 8);
						b = (unsigned char)(rgb >> 16);
						zb[p].c.R = unsigned char(r * ZPalet(zz));
						zb[p].c.G = unsigned char(g * ZPalet(zz));
						zb[p].c.B = unsigned char(b * ZPalet(zz));
					}
				}
			}
		}


}



/*

//"рисует" одну линию поля из начальной точки PointB
//с помощью функций работающих с Z-буфером
void LineField(HDC hdc,POINT3 PointB,COLORREF rgb)
{

	VECTORS vect;
	vect.x = PointB.x;
	vect.y = PointB.y;
	vect.z = PointB.z;

	//видовые координаты проецируемой точки
	double xe, ye, ze1, ze2;
	//координаты пикселов
	int x1,y1,x2,y2;

	double dt = 0.1; //длина шага на линии поля
	double x, y, z, Hx, Hy, Hz, Ha;
	int k = 0;

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
		ze1=Ze(xt1,yt1,zt1);
		x1=xn(xe);
		y1=ym(ye);

		xe=Xe(xt2,yt2);
		ye=Ye(xt2,yt2,zt2);
		ze2=Ze(xt2,yt2,zt2);
		x2=xn(xe);
		y2=ym(ye);

		//"рисуем" отрезок линии поля
		ZbufLineWidth(hdc,x1,y1,x2,y2,ze1,ze2,3,rgb);

		vect.x = xt2;
		vect.y = yt2;
		vect.z = zt2;

		//после 10-и шагов на лини поля "рисуем" стрелку
		k++;
		if(k == 10)
		{
			arrowVector(hdc,x1,y1,x2,y2,ze2,RGB(0,0,255));
			k = 0;
		}

	//прекращаем рисовать линию поля на границе куба
	}while((x>-xmax)&&(x<xmax)&&(y>-ymax)&&(y<ymax)&&(z>-zmax)&&(z<zmax));
}
*/


//рисуем картину приложения
void LinePicture(HWND hwnd, int Context)
{
	//выбираем нужный контектс устройства для экрана
	//---------------------------------------------
	HDC hdcWin;
	PAINTSTRUCT ps;
	//получаем контест устройства для экрана
	if (Context == 1)
		hdcWin = BeginPaint(hwnd, &ps);
	else
		hdcWin = GetDC(hwnd);
	//-----------------------------------------------


	//связываем размеры поля вывода с размерами клиентской области окна
	//--------------------------------------------------------------------
	RECT rct;
	GetClientRect(hwnd, &rct);

	ne1 = rct.left + 50; ne2 = rct.right - 50;
	me1 = rct.bottom - 50; me2 = rct.top + 50;
	//------------------------------------------------------------------

	//создаем контекст экрана
	//------------------------------------------------------------
	HDC hdc = CreateCompatibleDC(hdcWin); //создаем контекст
	//памяти связаный с контекстом экрана

//памяти надо придать вид экрана - подходт битовая карта с форматом
// как у экрана. В памяти будем рисовать на битовой карте
	HBITMAP hBitmap, hBitmapOld;
	hBitmap = CreateCompatibleBitmap(hdcWin, ne2, me1); //создаем
	//битовую карту совместмую с контекстом экрана
	hBitmapOld = (HBITMAP)SelectObject(hdc, hBitmap); //помещаем
	// битовую карту в контекст памяти
//--------------------------------------------------------------


//выводи значения углов в верхней части поля вывода
//--------------------------------------------------------	
	//создание прямоугольной области для вывода углов поворота
	HRGN hrgn2 = CreateRectRgn(ne1, me2 - 30, ne2, me1);

	//заливаем выделенную область серым цветом
	HBRUSH hBrush2 = CreateSolidBrush(RGB(0x80, 0x80, 0x80));
	HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, hBrush2);
	FillRgn(hdc, hrgn2, hBrush2);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush2);
	DeleteObject(hrgn2);


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
	//------------------------------------------------





	//выделение памяти под Z-буфер и начальное его заполнение
	//-------------------------------------------------------------
		//вычисляем число пикселей в поле  вывода
	Np = ne2 - ne1 + 1, Mp = me1 - me2 + 1, NM = Np * Mp;

	//выделяем память под Z-буфер для каждого пикселя
	zb = new ZbuffS[NM];

	//начальное заполнение z-буфера для каждого пикселя
	for (long unsigned p = 0; p < NM; p++)
	{
		zb[p].z = -1000;
		zb[p].c.R = 0xC0; zb[p].c.G = 0xC0; zb[p].c.B = 0xC0;
	}
	//-----------------------------------------------------------




	int iCh;
	//"рисуем" электрические заряды заданным цветом заполняя Z-буфер	
	//-----------------------------------------------------------------------
	for (iCh = 0; iCh < NCharge; iCh++)
	{

		if (qCharge[iCh] < 0)
			ZbufCircle(hdc, CoordCharge[iCh].x, CoordCharge[iCh].y,
				CoordCharge[iCh].z, RGB(0, 0, 255));
		else
			ZbufCircle(hdc, CoordCharge[iCh].x, CoordCharge[iCh].y,
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


	//"рисуем" линии поля заполняя Z-буфер для всех зарядов
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


	int x1, y1;
	//	double xe,ye,ze1;
	double xe, ye;

	/*
	//"рисуем" магнитную пластинку заданным цветом заполняя Z-буфер
	//-----------------------------------------------------------------------
		//мировые координаты проецируемой точки
		double xt1,yt1,zt1;
		//видовые координаты проецируемой точки
		double xe,ye,ze1;
		//пиксельные координаты проецируемой точки
		int x1,y1;

		//пиксельные координаты 4-х углов пластинки
		int xp[4], yp[4];
		//видовые z-координаты 4-х углов пластинки
		double ze[4];

		for(int n=0; n<4; n++)
		{
			xt1 = Px[n]; yt1 = Py[n]; zt1 = Pz[n];
			xe=Xe(xt1,yt1);
			ye=Ye(xt1,yt1,zt1);
			ze1=Ze(xt1,yt1,zt1);
			x1=xn(xe);
			y1=ym(ye);
			xp[n] = x1; yp[n] = y1; ze[n] = ze1;
		}
		ZbufParallelogram(hdc,xp[0],yp[0],ze[0],xp[1],yp[1],ze[1],
			xp[2],yp[2],ze[2],xp[3],yp[3],ze[3],RGB(255,255,0));
	//------------------------------------------------------------------



	//"рисуем" линии поля заполняя Z-буфер
	//----------------------------------------------------------------
		for(int i=0; i<36; i++)
		{
			LineField(hdc,PointB[i],RGB(255,0,0));

		}
		for(int i=36; i<72; i++)
		{
			LineField(hdc,PointB[i],RGB(0,0,255));

		}
	//-----------------------------------------------------------------------
	*/

	//выводим содержимое Z-буфера в контекст памяти
	//--------------------------------------------------------------------
		//двигаемся по всем пикселям окна вывода
	for (unsigned long ij = 0; ij < NM; ij++)
	{
		x1 = ne1 + ij % Np;
		y1 = me2 + ij / Np;
		SetPixel(hdc, x1, y1, RGB(zb[ij].c.R, zb[ij].c.G, zb[ij].c.B));

	}

	delete[] zb; //очищаем память под Z-буфером
	//-------------------------------------------------------------



	//рисуем координтные оси
	//------------------------------------------------------------------------

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

	int x2, y2;

	//ось Ox
	xe = Xe(-xmax / 3, 0, 0);
	ye = Ye(-xmax / 3, 0, 0);
	x1 = xn(xe);
	y1 = ym(ye);
	xe = Xe(xmax, 0, 0);
	ye = Ye(xmax, 0, 0);
	x2 = xn(xe);
	y2 = ym(ye);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	SetBkColor(hdc, RGB(0xC0, 0xC0, 0xC0));
	SetTextColor(hdc, RGB(120, 120, 120));
	TextOut(hdc, x2, y2, _T("X"), 1);

	//Ось Oy
	xe = Xe(0, -ymax / 3, 0);
	ye = Ye(0, -ymax / 3, 0);
	x1 = xn(xe);
	y1 = ym(ye);
	xe = Xe(0, ymax, 0);
	ye = Ye(0, ymax, 0);
	x2 = xn(xe);
	y2 = ym(ye);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	SetBkColor(hdc, RGB(0xC0, 0xC0, 0xC0));
	SetTextColor(hdc, RGB(120, 120, 120));
	TextOut(hdc, x2, y2, _T("Y"), 1);

	//Ось Oz
	xe = Xe(0, 0, -zmax / 3);
	ye = Ye(0, 0, -zmax / 3);
	x1 = xn(xe);
	y1 = ym(ye);
	xe = Xe(0, 0, zmax);
	ye = Ye(0, 0, zmax);
	x2 = xn(xe);
	y2 = ym(ye);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	SetBkColor(hdc, RGB(0xC0, 0xC0, 0xC0));
	SetTextColor(hdc, RGB(120, 120, 120));
	TextOut(hdc, x2, y2, _T("Z"), 1);


	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	//-----------------------------------------------------------------------------


	//рисуем куб
	//----------------------------------------------------------------------
	hPen = CreatePen(PS_SOLID, 1, RGB(160, 160, 160));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	DrawBox(hwnd, hdc, angl);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	//------------------------------------------------------------------------


	//копируем контекст памяти в контекст экрана
	//-----------------------------------------------------------------------	
	BitBlt(hdcWin, ne1, me2 - 30, ne2, me1, hdc, ne1, me2 - 30, SRCCOPY);
	//----------------------------------------------------------------------


	//завершаем работу с контекстами и памятью
	//-------------------------------------------------------------------
	SelectObject(hdc, hBitmapOld); //востанавливаем контекст памяти
	DeleteObject(hBitmap); //убираем битовую карту
	DeleteDC(hdc);  //  освобождаем контекст памяти

	//освобождаем контекст экрана
	if (Context == 1)
		EndPaint(hwnd, &ps);
	else
		ReleaseDC(hwnd, hdcWin);
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

		xe = Xe(xt1, yt1, zt1);
		ye = Ye(xt1, yt1, zt1);
		x1 = xn(xe);
		y1 = ym(ye);

		xe = Xe(xt2, yt2, zt2);
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

		xe = Xe(xt1, yt1, zt1);
		ye = Ye(xt1, yt1, zt1);
		x1 = xn(xe);
		y1 = ym(ye);

		xe = Xe(xt2, yt2, zt2);
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

		xe = Xe(xt1, yt1, zt1);
		ye = Ye(xt1, yt1, zt1);
		x1 = xn(xe);
		y1 = ym(ye);

		xe = Xe(xt2, yt2, zt2);
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

		xe = Xe(xt1, yt1, zt1);
		ye = Ye(xt1, yt1, zt1);
		x1 = xn(xe);
		y1 = ym(ye);

		xe = Xe(xt2, yt2, zt2);
		ye = Ye(xt2, yt2, zt2);
		x2 = xn(xe);
		y2 = ym(ye);

		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
	}


}



//функция для создания палитры, которая уменьшает яркось в глубь Z-буфера  
double ZPalet(double z)
{
	double a, b, f;
	a = -2.0 * xmax - dCentral;
	b = 0.5 * xmax - dCentral;

	if (z < a)
		f = 0;
	if ((z >= a) && (z <= b))
		f = (z - a) / (b - a);
	if (z > b)
		f = 1;
	return f;
}



//"рисует" линию по пикселям, цветом rgb, заполняя Z-буфер zb 
//x1,y1,x2,y2 - координаты линии в пиксельной плоскости
//ze1, ze2 - z-координаты концов линии в видовой системе координат
//на цвет rgb накладывается палитра ZPalet, которая уменьшает яркось в глубь Z-буфера  
void ZbufLine(HDC hdc, int x1, int y1, int x2, int y2,
	double ze1, double ze2, COLORREF rgb)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = x2 >= x1 ? 1 : -1;
	int sy = y2 >= y1 ? 1 : -1;
	unsigned long p;
	double zz;

	unsigned char r, g, b;


	if (dy <= dx)
	{

		int d = (dy << 1) - dx;
		int d1 = dy << 1;
		int d2 = (dy - dx) << 1;

		if ((x1 >= ne1) && (x1 <= ne2) && (y1 >= me2) && (y1 <= me1))
		{
			p = (x1 - ne1) + (y1 - me2) * Np;
			zz = ze1;
			if (zb[p].z < zz)
			{
				zb[p].z = zz;
				r = unsigned char(rgb);
				g = unsigned char(rgb >> 8);
				b = unsigned char(rgb >> 16);
				zb[p].c.R = unsigned char(r * ZPalet(zz));
				zb[p].c.G = unsigned char(g * ZPalet(zz));
				zb[p].c.B = unsigned char(b * ZPalet(zz));
			}
		}

		for (int x = x1 + sx, y = y1, i = 1; i <= dx; i++, x += sx)
		{
			if (d > 0)
			{
				d += d2;
				y += sy;
			}
			else
				d += d1;

			if ((x >= ne1) && (x <= ne2) && (y >= me2) && (y <= me1))
			{
				p = (x - ne1) + (y - me2) * Np;
				zz = ze1 + (ze2 - ze1) * (x - x1) / (x2 - x1);
				if (zb[p].z < zz)
				{
					zb[p].z = zz;
					r = (unsigned char)rgb;
					g = (unsigned char)(rgb >> 8);
					b = (unsigned char)(rgb >> 16);
					zb[p].c.R = unsigned char(r * ZPalet(zz));
					zb[p].c.G = unsigned char(g * ZPalet(zz));
					zb[p].c.B = unsigned char(b * ZPalet(zz));
				}
			}
		}
	}
	else
	{

		int d = (dx << 1) - dy;
		int d1 = dx << 1;
		int d2 = (dx - dy) << 1;

		if ((x1 >= ne1) && (x1 <= ne2) && (y1 >= me2) && (y1 <= me1))
		{
			p = (x1 - ne1) + (y1 - me2) * Np;
			zz = ze1;
			if (zb[p].z < zz)
			{
				zb[p].z = zz;
				r = (unsigned char)rgb;
				g = (unsigned char)(rgb >> 8);
				b = (unsigned char)(rgb >> 16);
				zb[p].c.R = unsigned char(r * ZPalet(zz));
				zb[p].c.G = unsigned char(g * ZPalet(zz));
				zb[p].c.B = unsigned char(b * ZPalet(zz));
			}
		}
		for (int x = x1, y = y1 + sy, i = 1; i <= dy; i++, y += sy)
		{
			if (d > 0)
			{
				d += d2;
				x += sx;
			}
			else
				d += d1;

			if ((x >= ne1) && (x <= ne2) && (y >= me2) && (y <= me1))
			{
				p = (x - ne1) + (y - me2) * Np;
				zz = ze1 + (ze2 - ze1) * (y - y1) / (y2 - y1);
				if (zb[p].z < zz)
				{
					zb[p].z = zz;
					r = (unsigned char)rgb;
					g = (unsigned char)(rgb >> 8);
					b = (unsigned char)(rgb >> 16);
					zb[p].c.R = unsigned char(r * ZPalet(zz));
					zb[p].c.G = unsigned char(g * ZPalet(zz));
					zb[p].c.B = unsigned char(b * ZPalet(zz));
				}
			}

		}
	}
}


//"рисует" линию толщиной w - пикселей, цветом rgb, заполняя Z-буфер
//x1,y12,x2,y2 - координаты линии в пиксельной плоскости
//ze1, ze2 - z-координаты концов линии в видовой системе координат
void ZbufLineWidth(HDC hdc, int x1, int y1, int x2, int y2,
	double ze1, double ze2, int w, COLORREF rgb)
{

	int n, m;
	if (w == 1)
	{
		ZbufLine(hdc, x1, y1, x2, y2, ze1, ze2, rgb);
	}
	else
	{
		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);
		if (dx >= dy)
		{
			m = w / 2;
			if (w % 2 == 0)
				n = -m + 1;
			else
				n = -m;
			for (int i = n; i <= m; i++)
				ZbufLine(hdc, x1, y1 + i, x2, y2 + i, ze1, ze2, rgb);
		}
		else
		{
			m = w / 2;
			if (w % 2 == 0)
				n = -m + 1;
			else
				n = -m;
			for (int i = n; i <= m; i++)
				ZbufLine(hdc, x1 + i, y1, x2 + i, y2, ze1, ze2, rgb);
		}
	}


}




//"рисует" параллелограм, цветом rgb, заполняя Z-буфер
//x1,y12,x2,y2,x3,y3,x4,y4 - координаты вершин в пиксельной плоскости
//ze1,ze2,ze3,ze4 - z-координаты вершин в видовой системе координат
void ZbufParallelogram(HDC hdc, int x1, int y1, double ze1,
	int x2, int y2, double ze2,
	int x3, int y3, double ze3,
	int x4, int y4, double ze4, COLORREF rgb)
{

	double zz, zzb;

	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = x2 >= x1 ? 1 : -1;
	int sy = y2 >= y1 ? 1 : -1;


	if (dy <= dx)
	{

		int d = (dy << 1) - dx;
		int d1 = dy << 1;
		int d2 = (dy - dx) << 1;

		ZbufLine(hdc, x1, y1, x4, y4, ze1, ze4, rgb);
		for (int x = x1 + sx, y = y1, xb = x4 + sx, yb = y4, i = 1;
			i <= dx; i++, x += sx, xb += sx)
		{
			if (d > 0)
			{
				d += d2;
				y += sy;
				yb += sy;
			}
			else
				d += d1;

			zz = ze1 + (ze2 - ze1) * (x - x1) / (x2 - x1);
			zzb = ze4 + (ze3 - ze4) * (xb - x4) / (x3 - x4);
			ZbufLineWidth(hdc, x, y, xb, yb, zz, zzb, 2, rgb);
		}
	}
	else
	{

		int d = (dx << 1) - dy;
		int d1 = dx << 1;
		int d2 = (dx - dy) << 1;

		for (int x = x1, y = y1 + sy, xb = x4, yb = y4 + sy, i = 1;
			i <= dy; i++, y += sy, yb += sy)
		{
			if (d > 0)
			{
				d += d2;
				x += sx;
				xb += sx;
			}
			else
				d += d1;

			zz = ze1 + (ze2 - ze1) * (y - y1) / (y2 - y1);
			zzb = ze4 + (ze3 - ze4) * (yb - y4) / (y3 - y4);
			ZbufLineWidth(hdc, x, y, xb, yb, zz, zzb, 2, rgb);

		}
	}
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hMainWnd = (HWND)lParam;
	switch (message) {
	case WM_INITDIALOG:
		wchar_t buffer[20];

		swprintf_s(buffer, 20, L"%.2f", xe1);
		SetDlgItemText(hDlg, 100, buffer);

		swprintf_s(buffer, 20, L"%.2f", xe2);
		SetDlgItemText(hDlg, 101, buffer);

		swprintf_s(buffer, 20, L"%.2f", ye1);
		SetDlgItemText(hDlg, 102, buffer);

		swprintf_s(buffer, 20, L"%.2f", ye2);
		SetDlgItemText(hDlg, 103, buffer);

		swprintf_s(buffer, 20, L"%.2f", dCentral);
		SetDlgItemText(hDlg, 104, buffer);

		swprintf_s(buffer, 20, L"%.2f", cCentral);
		SetDlgItemText(hDlg, 105, buffer);

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) {
			// Сохраняем изменения в переменные при нажатии OK
			wchar_t buffer[20];

			GetDlgItemText(hDlg, 100, buffer, 20);
			xe1 = wcstod(buffer, NULL);

			GetDlgItemText(hDlg, 101, buffer, 20);
			xe2 = wcstod(buffer, NULL);

			GetDlgItemText(hDlg, 102, buffer, 20);
			ye1 = wcstod(buffer, NULL);

			GetDlgItemText(hDlg, 103, buffer, 20);
			ye2 = wcstod(buffer, NULL);

			GetDlgItemText(hDlg, 104, buffer, 20);
			dCentral = wcstod(buffer, NULL);

			GetDlgItemText(hDlg, 105, buffer, 20);
			cCentral = wcstod(buffer, NULL);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
