%волна H - типа (TE - волна)
%волновод прямоугольного сечения

% 1) дисперсионные кривые волноводных мод 

% 2) линии электрического и магнитного поля моды

% 3) распределение электрического и магнитного поля
%    по контуру волновода

% 4) распределение поверхностного заряда и поверхностного тока
%    по контуру волновода



clc
clear

format short g


%в сечении z = 0
%в момент времени t0
t0 = 1/8; % в единичах периода T



%мощность, переносимая модой
P = 800; % (Вт)


%размеры волновода
a = 3; % (cm)
b = 1; % (cm)

fm = 50; %максимальная частота (GHz)
eGHz = 1.e+9; %один гигаГерц
c = 3.e+8; %скорость света (cm/m)
eps0 = 8.8542e-12; %электрическая постоянная (Ф/м)
mu0 = 4*pi*1.e-7; %магнитная постоянная (Гн/м)

%индексы волноводной моды H_nm
n=1;
m=1;  

%частота отсечки
f_nm = c/2*sqrt((n/a)^2 + (m/b)^2)*100/eGHz; % (GHz)
fc = f_nm;
disp('fc=')
disp(fc)


%   1) ///////////////////////////////////////////////////
%рисуем дисперсионную кривую

%находим постоянную распространения 'bet' для моды E_11
f1=f_nm:0.01:fm;
bet1 = 2*pi/c/100*eGHz*sqrt(f1.^2 - f_nm^2);

%находим асимптотику bet = 2*pi/c*f
f0=0:0.01:fm;
bet0 = 2*pi/c/100*eGHz*f0;

figure(10)
hPl=plot(f1,bet1,f0,bet0,'--');
set(hPl,'LineWidth',4);
grid on


%функция gca возвращает дескриптор текущих осей координат (гарафический объект axis)  
hAxes = gca;
%функция set устанавливает метки вдоль оси 'x' координатных осей hAxes
%set(hAxes,'xtick',[1.5 1.75 2.0 2.25 2.5])
set(hAxes,'FontSize',26,'FontWeight','bold');


%устанавливаем метку на оси 'x' текущих осей координат
xlabel('f     (GHz)')
%устанавливаем метку на оси 'y' текущих осей координат
ylabel('\beta     (1/cm)')

%text(11.0, 0.5,'E_{11}','Color',[0 0 0],'FontSize',[14])
%text(26.0, 0.5,'E_{12}','Color',[0 0 0],'FontSize',[14])
%text(23.0, 0.5,'H_{31}','Color',[0 0 0],'FontSize',26,'FontWeight','bold')
%text(33.0, 0.5,'E_{22}','Color',[0 0 0],'FontSize',[14])
%title('Dispersion Relation     \beta  =  \beta (f)')

strn = num2str(n);
strm = num2str(m);
string = ['Dispersion Relation.   TE - mode,  H_',strn,'_',strm];
title(string);


% ///////////////////////////////////////////////////



%   2) ///////////////////////////////////////////////////
%рисуем линии поля

%задаем сетку в области [0 a 0 b]
%для рисования линий уровня
dx = a/500;
dy = b/250;
[x,y] = meshgrid(0:dx:a, 0:dy:b);


z = cos(pi*n*x/a).*cos(pi*m*y/b)*sin(-2*pi*t0);    %Магнитный потенциал Герца  


figure(11)
%рисует эквипотенциальные линии (линии электрического поля)
[C,hc] = contour(x,y,z);       
set(hc,'LineWidth',2,'Color',[0.8 0.3 0.3]);
axis([0 a 0 b]);


%задаем сетку в области [0 a 0 b]
%для рисования линий градиента
dx = a/100;
dy = b/50;
[x,y] = meshgrid(0:dx:a, 0:dy:b);

z = cos(pi*n*x/a).*cos(pi*m*y/b)*sin(-2*pi*t0);    %Магнитный потенциал Герца  

%находим минус градиент поля z(x,y)
[px,py] = gradient(-z);                  


hold on;
%рисует векторы градиента (магнитное поле)
h = quiver(x,y,px,py,1.5);     
set(h,'LineWidth',2,'Color',[0.0 0.3 0.8]);


%функция gca возвращает дескриптор текущих осей координат (гарафический объект axis)  
hAxes = gca;
%функция set устанавливает метки вдоль оси 'x' координатных осей hAxes

ticX = 0:0.5:a;
ticY = 0:0.5:b;
%set(hAxes,'xtick',[0.0 0.5 1.0  1.5 2.0 2.5 3.0]);
%set(hAxes,'ytick',[0.0 0.5 1.0]);
set(hAxes,'xtick',ticX);
set(hAxes,'ytick',ticY);

%set(hAxes,'xtick',[0.0 0.5 1.0  1.5 2.0 2.5 3.0]);
%set(hAxes,'ytick',[0.0 0.5 1.0]);
set(hAxes,'FontSize',20,'FontWeight','bold');

%устанавливаем метку на оси 'x' текущих осей координат
xlabel('x     (cm)')
%устанавливаем метку на оси 'y' текущих осей координат
ylabel('y     (cm)')

%title('Lines E and B fields')

strn = num2str(n);
strm = num2str(m);
string = ['Lines E and B fields.   TE - mode,  H_',strn,'_',strm];
title(string);



% ///////////////////////////////////////////////////










%выбираем частоту f = 1.5*fc
f = 1.5*fc;  % (GHz)   
disp('f=')
disp(f)



%находим постоянную распространения 'bet' для моды H_nm
%на частоте f
bet = 2*pi/c*eGHz*sqrt(f.^2 - f_nm^2)/100;  % (1/cm)
disp('bet=')
disp(bet)


%находим длину волны моды H_nm
lamb = 2*pi/bet; % (cm)
disp('lamb=')
disp(lamb)

%находим фазовую скорость волны
vp = 2*pi*f*eGHz/bet; % (cm/c)
disp('vp=')
disp(vp)


%находим групповую скорость моды
vg = c*(c/vp)*10^4; % (cm/c)
disp('vg=')
disp(vg)



%Амплитуда моды
kA = bet*100*2*pi*f*eGHz/mu0/2*((pi*n/a)^2 + (pi*m/b)^2)*a*b/4; % (1/(Гн*с))
A2 = sqrt(P/kA)*10^4; % (Тл*см^2)
disp('A2=')
disp(A2)
A=sqrt(A2)

%находим наибольшее значение электрического и магнитного полей
%на контуре волновода
g2 = (pi*n/a)^2 + (pi*m/b)^2;
A2m = pi*m/b*A2/sqrt(2); % (Тл*см) = (10^{-4} с*В/см)   
A2n = pi*n/a*A2/sqrt(2); % (Тл*см) = (10^{-4} с*В/см)
B2z = g2*A2/sqrt(2);     % (Тл)

%нижняя часть конутра
Ed = 2*pi*f*eGHz*A2n/10^4;  % (В/см)
Btd = bet*A2n;              % (Тл)
Htd = Btd/mu0/100;          % (А/см)   
Bzd = B2z;                  % (Тл)
Hzd = Bzd/mu0/100;          % (А/см)   


%правая часть конутра
Er = 2*pi*f*eGHz*A2m/10^4;  % (В/см)
Btr = bet*A2m;              % (Тл)
Htr = Btr/mu0/100;          % (А/см)   
Bzr = B2z;                  % (Тл)
Hzr = Bzr/mu0/100;          % (А/см)   


%верхняя часть конутра
Et = 2*pi*f*eGHz*A2n/10^4;  % (В/см)
Btt = bet*A2n;              % (Тл)
Htt = Btt/mu0/100;          % (А/см)   
Bzt = B2z;                  % (Тл)
Hzt = Bzt/mu0/100;          % (А/см)   



%левая часть конутра
El = 2*pi*f*eGHz*A2m/10^4;  % (В/см)
Btl = bet*A2m;              % (Тл)
Htl = Btl/mu0/100;          % (А/см)   
Bzl = B2z;                  % (Тл)
Hzl = Bzl/mu0/100;          % (А/см)   



Emax = max([Ed, Er, Et, El]);
Btmax = max([Btd, Btr, Btt, Btl]);
Htmax = max([Htd, Htr, Htt, Htl]);
Bzmax = max([Bzd, Bzr, Bzt, Bzl]);
Hzmax = max([Hzd, Hzr, Hzt, Hzl]);

disp('       Emax,      Btmax,        Htmax')
disp([Emax   Btmax   Htmax])
disp('                  Bzmax,        Hzmax')
disp([0   Bzmax   Hzmax])


%находим наибольшее значение поверхностной плотности электрического заряда
%поверхностной плотности электрического тока
%на контуре волновода

%нижняя часть конутра
roSd = Ed*100*eps0/10^4*10^9;   % (нКл/см^2)
jSzd = Btd/mu0/100;             % (А/см)
jStd = Bzd/mu0/100;             % (А/см)

%правая часть конутра
roSr = Er*100*eps0/10^4*10^9;   % (нКл/см^2)
jSzr = Btr/mu0/100;             % (А/см)
jStr = Bzr/mu0/100;             % (А/см)

%верхняя часть конутра
roSt = Et*100*eps0/10^4*10^9;   % (нКл/см^2)
jSzt = Btt/mu0/100;             % (А/см)
jStt = Bzt/mu0/100;             % (А/см)

%левая часть конутра
roSl = El*100*eps0/10^4*10^9;   % (нКл/см^2)
jSzl = Btl/mu0/100;             % (А/см)
jStl = Bzl/mu0/100;             % (А/см)


roSmax = max([roSd, roSr, roSt, roSl]);
jSzmax  = max([jSzd, jSzr, jSzt, jSzl]);
jStmax  = max([jStd, jStr, jStt, jStl]);

disp('      roSmax,       jSzmax,       jStmax')
disp([roSmax   jSzmax   jStmax])



% ///////////////////////////////////////////////////
%находим поля, заряды и токи по контуру волновода

%нижняя часть конутра
s1 = 0:0.001:a;
x = s1;
E1 = Ed*sin(pi*n/a*x);           % (В/см)
Bt1 = Btd*sin(pi*n/a*x);         % (Тл)
Bz1 = Bzd*cos(pi*n/a*x);          % (Тл)
roS1 = E1*100*eps0/10^4*10^9;     % (нКл/см^2)
jSz1  = Bt1/mu0/100;              % (А/см)
jSt1  = -Bz1/mu0/100;             % (А/см)


%правая часть конутра
s2 = a:0.001:a+b;
y = s2 - a;
E2 = Er*(-1)^n*sin(pi*m/b*y);    % (В/см)
Bt2 = Btr*(-1)^n*sin(pi*m/b*y);  % (Тл)
Bz2 = Bzr*(-1)^n*cos(pi*m/b*y);      % (Тл)
roS2 = E2*100*eps0/10^4*10^9;     % (нКл/см^2)
jSz2  = Bt2/mu0/100;              % (А/см)
jSt2  = -Bz2/mu0/100;             % (А/см)


%верхняя часть конутра
s3 = a+b:0.001:2*a+b;
x = -s3 + 2*a + b;
E3 = Et*(-1)^(m+1)*sin(pi*n/a*x);           % (В/см)
Bt3 = Btt*(-1)^(m+1)*sin(pi*n/a*x);         % (Тл)
Bz3 = Bzt*(-1)^m*cos(pi*n/a*x);          % (Тл)
roS3 = E3*100*eps0/10^4*10^9;     % (нКл/см^2)
jSz3  = Bt3/mu0/100;              % (А/см)
jSt3  = -Bz3/mu0/100;             % (А/см)


%левая часть конутра
s4 = 2*a+b:0.001:2*a+2*b;
y = -s4 + 2*a + 2*b;
E4 = -El*sin(pi*m/b*y);           % (В/см)
Bt4 = -Btl*sin(pi*m/b*y);         % (Тл)
Bz4 = Bzl*cos(pi*m/b*y);          % (Тл)
roS4 = E4*100*eps0/10^4*10^9;     % (нКл/см^2)
jSz4  = Bt4/mu0/100;              % (А/см)
jSt4  = -Bz4/mu0/100;             % (А/см)




s = cat(2,s1,s2,s3,s4);
E = cat(2,E1,E2,E3,E4);
Bt = cat(2,Bt1,Bt2,Bt3,Bt4);
Bz = cat(2,Bz1,Bz2,Bz3,Bz4);
roS = cat(2,roS1,roS2,roS3,roS4);
jSz  = cat(2,jSz1,jSz2,jSz3,jSz4);
jSt  = cat(2,jSt1,jSt2,jSt3,jSt4);


Bt = Bt*10^6;
Bz = Bz*10^6;
roS = roS*10^2;

Btmax = Btmax*10^6;
Bzmax = Bzmax*10^6;
roSmax = roSmax*10^2;

EBmax = max([Emax,Btmax,Bzmax]);
roSjSmax = max([roSmax,jSzmax,jStmax]);

% ///////////////////////////////////////////////////



%   3) ///////////////////////////////////////////////////
%рисуем распредление поля по контуру волновода

figure(12)
hPl = plot(s,E,s,Bt,'--',s,Bz,'-.');
set(hPl,'LineWidth',2);
axis([0 2*a+2*b -1.1*EBmax 1.1*EBmax]);
%функция gca возвращает дескриптор текущих осей координат (гарафический объект axis)  
hAxes = gca;
%функция set устанавливает метки вдоль оси 'x' координатных осей hAxes
%set(hAxes,'xtick',[1.5 1.75 2.0 2.25 2.5])
set(hAxes,'FontSize',16);
%устанавливаем метку на оси 'x' текущих осей координат
xlabel('s     (cm)')
%устанавливаем метку на оси 'y' текущих осей координат
legend('E  (V/cm)','B_{\tau} (10^{-6} T)','B_{z} (10^{-6} T)')
%title('E  (V/cm),          B (10^{-6} T)')

grid on

strn = int2str(n);
strm = int2str(m);
string = ['E   and   B   fields on countour.  TE - mode, H_',strn,'_',strm];
title(string)

% ///////////////////////////////////////////////////




%   4) ///////////////////////////////////////////////////
%рисуем распредление заряда и тока по контуру волновода

figure(13)
hPl = plot(s,roS,s,jSz,'--',s,jSt,'-.');
set(hPl,'LineWidth',2);
axis([0 2*a+2*b -1.1*roSjSmax 1.1*roSjSmax]);
%функция gca возвращает дескриптор текущих осей координат (гарафический объект axis)  
hAxes = gca;
%функция set устанавливает метки вдоль оси 'x' координатных осей hAxes
%set(hAxes,'xtick',[1.5 1.75 2.0 2.25 2.5])
set(hAxes,'FontSize',14,'FontWeight','bold');
%устанавливаем метку на оси 'x' текущих осей координат
xlabel('s     (cm)')
%устанавливаем метку на оси 'y' текущих осей координат
legend('\rho_{S}  (10^{-2} nQ/cm^{2})','j_{S z} (A/cm)','j_{S \tau} (A/cm)')
%title('\rho_{S}  (10^{-2} nQ/cm^{2}),        j_{S} (A/cm)')

grid on


grid on
strn = int2str(n);
strm = int2str(m);
string = ['\rho_{S}    and    j_{S}    on countour.  TE - mode, H_',strn,'_',strm];
title(string)


% ///////////////////////////////////////////////////


format short

