function MyGo
%функция MyGo.m обрабатывает нажатие кнопки GO

%выполняет следующие действиея:

% 1 - читает содержание полей рабочего окна figure(1)

% 2 - запусает функцию fWave1 для нахождения поля E = z(x,y)
%     в узлах сетки создаваемой в плоскости x,y

% 3 - используя массив x(i), i=1,...,N для координаты x
%     используя массив y(i), i=1,...,M для координаты y
%     используя массив z(i,j) для значений поля в узлах сетки
%     строит 3D распределения электрического поля в окне figure(2)

% 4 - линия сечения в плоскости x,y задается двумя точкам
%     (xs1,ys1) и (xs2,ys2), лежащими на этой линии
%     функция Section1 находит точки пересечения линии сечения
%     с границами области вывода (xr1,yr1) и (xr2,yr2)
%     линия сечения выводится в графическом окне hAxes1

% 5 - используя координаты сечения (xr1,yr1), (xr2,yr2)
%     используя массивы x(i), y(i), z(i,j) находим сечение
%     3D распределения электрического поля вдоль линии сечения
%     для этого создается массив координат точек xL(k) вдоль
%     линии сечения, для каждой точки xL(k) на линии сечения
%     находится значение электрического поля zL(k) по заданному алгоритму
%     массивы xL(k)и zL(k) вычисляются функцией Section1
%     (алгритм и функция Section1 создаются самостоятельно !!!!!!!)
%     распредление поля в сечении выводится в графическом окне hAxes2

%глобальные переменные, доступные из других функций
global hFig1 hAxes1 hAxes2;
global hEdxb hEdxe hEdN hEdyb hEdye hEdM;
global hEdx1 hEdy1 hEdI1 hEdf1;
global hEdx2 hEdy2 hEdI2 hEdf2;
global hEdxs1 hEdys1 hEdxs2 hEdys2;

%читаем содержимое полей редактирования
strxb = get(hEdxb,'String');
strxe = get(hEdxe,'String');
strN = get(hEdN,'String');
stryb = get(hEdyb,'String');
strye = get(hEdye,'String');
strM = get(hEdM,'String');

strx1 = get(hEdx1,'String');
stry1 = get(hEdy1,'String');
strI1 = get(hEdI1,'String');
strf1 = get(hEdf1,'String');
strx2 = get(hEdx2,'String');
stry2 = get(hEdy2,'String');
strI2 = get(hEdI2,'String');
strf2 = get(hEdf2,'String');

strxs1 = get(hEdxs1,'String');
strys1 = get(hEdys1,'String');
strxs2 = get(hEdxs2,'String');
strys2 = get(hEdys2,'String');


%переводим строки в числа
xb = str2num(strxb);
xe = str2num(strxe);
N  = str2num(strN);
yb = str2num(stryb);
ye = str2num(strye);
M  = str2num(strM);

x1 = str2num(strx1);
y1 = str2num(stry1);
I1 = str2num(strI1);
f1 = str2num(strf1);
x2 = str2num(strx2);
y2 = str2num(stry2);
I2 = str2num(strI2);
f2 = str2num(strf2);

xs1 = str2num(strxs1);
ys1 = str2num(strys1);
xs2 = str2num(strxs2);
ys2 = str2num(strys2);


%нахождим поле E = z(x,y)
%в узлах сетки в плоскости x,y
%[x,y,z] = fWave1(xb,xe,N,yb,ye,M,x1,y1,I1,f1);
[x,y,z] = fMex2(xb,xe,int32(N),yb,ye,int32(M),x1,y1,I1,f1,x2,y2,I2,f2);

%создаем окно 
hFig2 = figure(2);
%строим 3D распределение электрического поля в окне figure(2)
[X,Y] = meshgrid(x,y);
hPlot3 = mesh(X,Y,z');
xlabel('x');
ylabel('y');
zlabel('E');

%находим точки пересечения (xr1,yr1), (xr2,yr2) линии сечения
%с границами области вывода 
[xr1,yr1,xr2,yr2] = Section1(xb,xe,yb,ye,xs1,ys1,xs2,ys2);

%рисуем линию сечения в графическом окне hAxes1
axes(hAxes1);

axis([(5*xb-xe)/4,(5*xe-xb)/4,(5*yb-ye)/4,(5*ye-yb)/4]);
line([(5*xb-xe)/4,(5*xe-xb)/4],[yb,yb]);
line([(5*xb-xe)/4,(5*xe-xb)/4],[ye,ye]);
line([xb, xb],[(5*yb-ye)/4,(5*ye-yb)/4]);
line([xe, xe],[(5*yb-ye)/4,(5*ye-yb)/4]);

hLine = line([xr1, xr2],[yr1, yr2]);
set(hLine,'Color',[1.0 0.0 0.6],'LineWidth', 2);

hText = text(xr1, yr1, '1');
set(hText,'Color',[1 0 0.6],'FontSize',[11]);
hText = text(xr2, yr2, '2');
set(hText,'Color',[0.6 0 1],'FontSize',[11]);

xlabel('x');
ylabel('y');

%находим сечение 3D распределения электрического поля вдоль линии сечения
%для этого создается массивы xL(k)и zL(k)
[xL,zL] = Section2(xb,xe,N,yb,ye,M,xr1,xr2,yr1,yr2,x,y,z);

%рисуем сечение в графическом окне hAxes1
axes(hAxes2);

hold on
hPlot = plot(xL,zL,'m');
xlabel('xL');
ylabel('E');
grid on;
set(hPlot,'Color',[1.0 0.0 0.6],'LineWidth', 2);
K = length(xL);



