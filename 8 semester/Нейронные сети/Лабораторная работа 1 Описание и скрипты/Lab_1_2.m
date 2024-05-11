% Нейронные сети 
% Лабораторная работа 1

% Программа вычисления ДПФ гармонического сигнала
close all; clear all;

disp('*** Программа вычислениЯ ДПФ гармонического сигнала ***');
A   = input('Введите амплитуду сигнала, ед.: ');
f0  = input('Введите частоту сигнала, Гц: ');

fdn = 2*f0;       % Частота дискретизации
                  % в соответствии с критерием Найквиста
mvis= 10;
fdv = mvis*fdn;   % Частота дискретизации длЯ визуализации
dt  = 1/fdv;      % Интервал дискретизации по времени
T   = 1/f0;       % Период сигнала
NT  = 6;
t   = 0:dt:NT*T;  % Вектор времени, с
y   = A*sin(2*pi*f0*t);
                  % Вектор сигнала
N   = length(y);
                  
% Дискретное преобразование Фурье
k   = 0:N-1;
Ex  = exp(-j*2*pi/N*k'*k);
Y   = y*Ex;

% Обратное дискретное преобразование Фурье
Ex  = exp(j*2*pi/N*k'*k);
ys  = Y/(N-1)*Ex;

Y2  = Y.*conj(Y);  % Квадрат модулЯ Фурье-образа
ff  = k*fdv/N; % Вектор частоты, Гц

figure(1);
plot(ff,Y2,'r');
xlabel('Frequency, Hz');
ylabel('Fourier-image modulus squared');
figure(2);
subplot(2,2,1);
plot(t,real(y),'r');
axis([0 NT*T -1.1*A 1.1*A]);
title('Real part');
xlabel('Time, s');
ylabel('Initial signal');
subplot(2,2,2);
plot(t,imag(y),'b');
axis([0 NT*T -1.1*A 1.1*A]);
title('Imaginary part');
xlabel('Time, s');
ylabel('Initial signal');
subplot(2,2,3);
plot(t,real(ys),'r');
axis([0 NT*T -1.1*A 1.1*A]);
xlabel('Time, s');
ylabel('Restored signal');
subplot(2,2,4);
plot(t,imag(ys),'b');
axis([0 NT*T -1.1*A 1.1*A]);
xlabel('Time, s');
ylabel('Restored signal');

disp('**********   Конец работы   **********');