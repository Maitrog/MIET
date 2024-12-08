function MyGo
%������� MyGo.m ������������ ������� ������ GO

%��������� ��������� ���������:

% 1 - ������ ���������� ����� �������� ���� figure(1)

% 2 - �������� ������� fWave1 ��� ���������� ���� E = z(x,y)
%     � ����� ����� ����������� � ��������� x,y

% 3 - ��������� ������ x(i), i=1,...,N ��� ���������� x
%     ��������� ������ y(i), i=1,...,M ��� ���������� y
%     ��������� ������ z(i,j) ��� �������� ���� � ����� �����
%     ������ 3D ������������� �������������� ���� � ���� figure(2)

% 4 - ����� ������� � ��������� x,y �������� ����� ������
%     (xs1,ys1) � (xs2,ys2), �������� �� ���� �����
%     ������� Section1 ������� ����� ����������� ����� �������
%     � ��������� ������� ������ (xr1,yr1) � (xr2,yr2)
%     ����� ������� ��������� � ����������� ���� hAxes1

% 5 - ��������� ���������� ������� (xr1,yr1), (xr2,yr2)
%     ��������� ������� x(i), y(i), z(i,j) ������� �������
%     3D ������������� �������������� ���� ����� ����� �������
%     ��� ����� ��������� ������ ��������� ����� xL(k) �����
%     ����� �������, ��� ������ ����� xL(k) �� ����� �������
%     ��������� �������� �������������� ���� zL(k) �� ��������� ���������
%     ������� xL(k)� zL(k) ����������� �������� Section1
%     (������� � ������� Section1 ��������� �������������� !!!!!!!)
%     ������������ ���� � ������� ��������� � ����������� ���� hAxes2

%���������� ����������, ��������� �� ������ �������
global hFig1 hAxes1 hAxes2;
global hEdxb hEdxe hEdN hEdyb hEdye hEdM;
global hEdx1 hEdy1 hEdI1 hEdf1;
global hEdx2 hEdy2 hEdI2 hEdf2;
global hEdxs1 hEdys1 hEdxs2 hEdys2;

%������ ���������� ����� ��������������
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


%��������� ������ � �����
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


%�������� ���� E = z(x,y)
%� ����� ����� � ��������� x,y
%[x,y,z] = fWave1(xb,xe,N,yb,ye,M,x1,y1,I1,f1);
[x,y,z] = fMex2(xb,xe,int32(N),yb,ye,int32(M),x1,y1,I1,f1,x2,y2,I2,f2);

%������� ���� 
hFig2 = figure(2);
%������ 3D ������������� �������������� ���� � ���� figure(2)
[X,Y] = meshgrid(x,y);
hPlot3 = mesh(X,Y,z');
xlabel('x');
ylabel('y');
zlabel('E');

%������� ����� ����������� (xr1,yr1), (xr2,yr2) ����� �������
%� ��������� ������� ������ 
[xr1,yr1,xr2,yr2] = Section1(xb,xe,yb,ye,xs1,ys1,xs2,ys2);

%������ ����� ������� � ����������� ���� hAxes1
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

%������� ������� 3D ������������� �������������� ���� ����� ����� �������
%��� ����� ��������� ������� xL(k)� zL(k)
[xL,zL] = Section2(xb,xe,N,yb,ye,M,xr1,xr2,yr1,yr2,x,y,z);

%������ ������� � ����������� ���� hAxes1
axes(hAxes2);

hold on
hPlot = plot(xL,zL,'m');
xlabel('xL');
ylabel('E');
grid on;
set(hPlot,'Color',[1.0 0.0 0.6],'LineWidth', 2);
K = length(xL);



