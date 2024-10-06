%волна H - типа (TE - волна)
%волновод круглого сечения

% 1) дисперсионные кривые волноводных мод 

% 2) линии электрического и магнитного поля моды

% 3) распределение электрического и магнитного поля
%    по контуру волновода

% 4) распределение поверхностного заряда и поверхностного тока
%    по контуру волновода



clc
clear

format short g

%нули mu_nm производной функции Бесселя J'_n(mu_nm) = 0
muB(1,2) = 3.832; muB(1,3) = 7.016; muB(1,4) = 10.173; muB(1,5) = 13.324;
muB(2,2) = 1.841; muB(2,3) = 5.331; muB(2,4) =  8.836; muB(2,5) = 11.706;
muB(3,2) = 3.054; muB(3,3) = 6.706; muB(3,4) =  9.970; muB(3,5) = 13.170;
muB(4,2) = 4.201; muB(4,3) = 8.015; muB(4,4) = 11.346; muB(4,5) = 14.586;

%в сечении z = 0
%в момент времени t0
t0 = 1/8; % в единичах периода T


%мощность, переносимая модой
P = 800; % (Вт)


%радиус волновода
a = 3; % (cm)

fm = 50; %максимальная частота (GHz)
eGHz = 1.e+9; %один гигаГерц
c = 3.e+8; %скорость света (cm/m)
eps0 = 8.8542e-12; %электрическая постоянная (Ф/м)
mu0 = 4*pi*1.e-7; %магнитная постоянная (Гн/м)

%индексы волноводной моды H_nm
n=1; 
m=1;  

%нуль производной функции Бесселя
mu_nm = muB(n+1,m+1);
%частота отсечки
f_nm = c/2/pi*mu_nm/a*100/eGHz; % (GHz)

fc = f_nm;
disp('fc=')
disp(fc)


%   1) ///////////////////////////////////////////////////
%рисуем дисперсионную кривую

%находим постоянную распространения 'bet' для моды H_nm
f1=f_nm:0.01:fm;
bet1 = 2*pi/c/100*eGHz*sqrt(f1.^2 - f_nm^2);

%находим асимптотику bet = 2*pi/c*f
f0=0:0.01:fm;
bet0 = 2*pi/c/100*eGHz*f0;

figure(10)
hPl=plot(f1,bet1,f0,bet0,'--');
set(hPl,'LineWidth',2);
grid on


%функция gca возвращает дескриптор текущих осей координат (гарафический объект axis)  
hAxes = gca;
%функция set устанавливает метки вдоль оси 'x' координатных осей hAxes
%set(hAxes,'xtick',[1.5 1.75 2.0 2.25 2.5])
set(hAxes,'FontSize',14,'FontWeight','bold');


%устанавливаем метку на оси 'x' текущих осей координат
xlabel('f     (GHz)')
%устанавливаем метку на оси 'y' текущих осей координат
ylabel('\beta     (1/cm)')

%text(11.0, 0.5,'E_{11}','Color',[0 0 0],'FontSize',[14])
%text(26.0, 0.5,'E_{12}','Color',[0 0 0],'FontSize',[14])
%text(23.0, 0.5,'E_{31}','Color',[0 0 0],'FontSize',14,'FontWeight','bold')
%text(33.0, 0.5,'E_{22}','Color',[0 0 0],'FontSize',[14])
%title('Dispersion Relation     \beta  =  \beta (f)')


strn = int2str(n);
strm = int2str(m);
string = ['Dispersion Relation.  TE - mode, H_',strn,'_',strm,...
     '\newline        Cylindrical waveguide'];
title(string)





% ///////////////////////////////////////////////////



%   2) ///////////////////////////////////////////////////
%рисуем линии поля

b = a;

%задаем сетку в области [-a a -b b]
%для рисования линий уровня
dx = a/300;
dy = b/300;
[x,y] = meshgrid(-a:dx:a, -b:dy:b);


%нуль производной функции Бесселя
mu_nm = muB(n+1,m+1);

%Магнитный потенциал Герца на сетке  
r = sqrt(x.^2+y.^2);
psi = atan2(y,x);
z = besselj(n,mu_nm*r/a).*sin(n*psi - 2*pi*t0);

figure(11)
%рисует эквипотенциальные линии (линии электрического поля)
[C,hc] = contour(x,y,z);       
set(hc,'LineWidth',2,'Color',[0.3 0.3 0.8]);
axis([-a a -b b]);


%задаем сетку в области [0 a 0 b]
%для рисования линий градиента
dx = a/10;
dy = b/10;
[x,y] = meshgrid(-a:dx:a, -a:dy:b);

%Магнитный потенциал Герца на сетке  
r = sqrt(x.^2+y.^2);
psi = atan2(y,x);
z = besselj(n,mu_nm*r/a).*sin(n*psi - 2*pi*t0);


%находим минус градиент поля z(x,y)
[px,py] = gradient(-z);                  


hold on;
%рисует векторы градиента (электрическое поле)
h = quiver(x,y,px,py,1.5);     
set(h,'LineWidth',2,'Color',[0.8 0.3 0.3]);


fi=0:0.01:2*pi;
xc = a*cos(fi);
yc = a*sin(fi);
hy=line(xc, yc); 
set(hy,'color',[0.5 0.5 0.5],'LineWidth',10);

%заливаем белым цветом область вокруг круга
xp = [xc a a -a -a a a ];
yp = [yc 0 -b -b b b 0 ];

fill(xp,yp,'w')

%функция gca возвращает дескриптор текущих осей координат (гарафический объект axis)  
hAxes = gca;
%функция set устанавливает метки вдоль оси 'x' координатных осей hAxes
ticX = -a:0.5:a;
ticY = -b:0.5:b;
%set(hAxes,'xtick',[0.0 0.5 1.0  1.5 2.0 2.5 3.0]);
%set(hAxes,'ytick',[0.0 0.5 1.0]);
set(hAxes,'xtick',ticX);
set(hAxes,'ytick',ticY);
set(hAxes,'FontSize',14,'FontWeight','bold');

%устанавливаем метку на оси 'x' текущих осей координат
xlabel('x     (cm)')
%устанавливаем метку на оси 'y' текущих осей координат
ylabel('y     (cm)')

%title('Lines E and B fields')

strn = int2str(n);
strm = int2str(m);
string = ['Lines of E and B fields.  TE - mode, H_',strn,'_',strm];
title(string)

%делаем квадратной область рисования
axis square



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
kA = bet*100*2*pi*f*eGHz*pi/mu0/2*(mu_nm^2-n^2)*(besselj(n,mu_nm))^2; % (1/(Гн*с))
A2 = sqrt(P/kA)*10^4; % (Тл*см^2)
disp('A2=')
disp(A2)
A=sqrt(A2)

%находим наибольшее значение электрического и магнитного полей
%на контуре волновода

g2 = (mu_nm/a)^2;
A2n = n/a*A2*besselj(n,mu_nm); % (Тл*см) = (10^{-4} с*В/см))
B2z = g2*A2*besselj(n,mu_nm);  % (Тл)

Eampl = 2*pi*f*eGHz*A2n/10^4;  % (В/см)
Btampl = bet*A2n;              % (Тл)
Bzampl = B2z;                  % (Тл)

Emax = abs(Eampl);              % (В/см)
Btmax = abs(Btampl);              % (Тл)
Bzmax = abs(Bzampl);              % (Тл)
Htmax = Btmax/mu0/100;           % (А/см)   
Hzmax = Bzmax/mu0/100;           % (А/см)   


disp('       Emax,      Btmax,        Htmax')
disp([Emax   Btmax   Htmax])
disp('                  Bzmax,        Hzmax')
disp([0   Bzmax   Hzmax])



%находим наибольшее значение поверхностной плотности электрического заряда
%поверхностной плотности электрического тока
%на контуре волновода

roSampl = Eampl*100*eps0/10^4*10^9;
jSzampl  = Btampl/mu0/100;          
jStampl  = -Bzampl/mu0/100;          

roSmax = abs(roSampl);        % (нКл/см^2)
jSzmax  = abs(jSzampl);          % (А/см)
jStmax  = abs(jStampl);          % (А/см)

disp('      roSmax,       jSzmax,       jStmax')
disp([roSmax   jSzmax   jStmax])




% ///////////////////////////////////////////////////
%находим поля, заряды и токи по контуру волновода


s1 = 0:0.01:2*pi*a;
psi1 = s1/a;
E1 = Eampl*cos(n*psi1 - 2*pi*t0);          % (В/см)
Bt1 = Bzampl*cos(n*psi1 - 2*pi*t0);          % (Тл)
Bz1 = Btampl*cos(n*psi1 - 2*pi*t0);          % (Тл)
roS1 = roSampl*cos(n*psi1 - 2*pi*t0);   % (нКл/см^2)
jSz1  = jSzampl*cos(n*psi1 - 2*pi*t0);              % (А/см)
jSt1  = jStampl*cos(n*psi1 - 2*pi*t0);              % (А/см)



Bt1 = Bt1*10^6;
Bz1 = Bz1*10^6;
roS1 = roS1*10^2;

Btmax = Btmax*10^6;
Bzmax = Bzmax*10^6;
roSmax = roSmax*10^2;

EBmax = max([Emax,Btmax,Bzmax]);
roSjSmax = max([roSmax,jSzmax,jStmax]);


% ///////////////////////////////////////////////////



%   3) ///////////////////////////////////////////////////
%рисуем распредление поля по контуру волновода

figure(12)
hPl = plot(s1,E1,s1,Bt1,'--',s1,Bz1,'-.');
set(hPl,'LineWidth',2);
axis([0 2*pi*a -1.1*EBmax 1.1*EBmax]);
%функция gca возвращает дескриптор текущих осей координат (гарафический объект axis)  
hAxes = gca;
%функция set устанавливает метки вдоль оси 'x' координатных осей hAxes
%set(hAxes,'xtick',[1.5 1.75 2.0 2.25 2.5])
set(hAxes,'FontSize',14,'FontWeight','bold');
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
hPl = plot(s1,roS1,s1,jSz1,'--',s1,jSt1,'-.');
set(hPl,'LineWidth',2);
axis([0 2*pi*a -1.1*roSjSmax 1.1*roSjSmax]);
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
strn = int2str(n);
strm = int2str(m);
string = ['\rho_{S}    and    j_{S}    on countour.  TE - mode, H_',strn,'_',strm];
title(string)

% ///////////////////////////////////////////////////


format short

