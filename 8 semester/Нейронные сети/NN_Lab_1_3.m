close all; clear all;

f0  = 2000;

disp(strcat('*** Программа визуализации функций синуса и косинуса с частотой ', num2str(f0), ' Гц ***'));
Tnab= input('Введите интервал наблюдения, мс.: ');
Tnab= Tnab / 1000;
pnt = input('Введите количество точек наблюдения: ');

fdn = 2*f0;       % Частота дискретизации
                  % в соответствии с критерием Найквиста
mvis= 8;
fdv = mvis*fdn;   % Частота дискретизации длЯ визуализации
dt  = 1/fdv;      % Интервал дискретизации по времени
T   = 1/f0;       % Период сигнала
NT  = f0 * Tnab;  % Количество периодов наблюдения
t   = 0:dt:NT*T;  % Вектор времени, с
sinp= sin(2*pi*f0*t); % Вектор сигнала
cosp= cos(2*pi*f0*t); % Вектор сигнала

figure(1);
subplot(2, 1, 1);
plot(t, sinp, 'r');
grid on;
axis([0 NT*T -1.1 1.1]);
title('y = sin(t)');
xlabel('Время, с');
ylabel('Исходный сигнал');
subplot(2, 1, 2);
plot(t, cosp, 'r');
grid on;
axis([0 NT*T -1.1 1.1]);
title('y = cos(t)');
xlabel('Время, с');
ylabel('Исходный сигнал');

t   = 0:dt:(pnt-1)*dt;
sinn= sin(2*pi*f0*t);
cosn= cos(2*pi*f0*t);

figure(2);
subplot(2, 1, 1);
plot(t, sinn, 'r');
grid on;
axis([0 (pnt-1)*dt -1.1 1.1]);
title('y = sin(t)');
xlabel('Время, с');
ylabel('Исходный сигнал');
subplot(2, 1, 2);
plot(t, cosn, 'r');
grid on;
axis([0 (pnt-1)*dt -1.1 1.1]);
title('y = cos(t)');
xlabel('Время, с');
ylabel('Исходный сигнал');
                  
% Дискретное преобразование Фурье
N   = length(sinp);
k   = 0:N-1;
Ex  = exp(-j*2*pi/N*k'*k);
SY   = sinp*Ex;
CY   = cosp*Ex;

FSY = fft(sinp);
FCY = fft(cosp);

figure(3);
subplot(2, 2, 1);
hold on;
plot(k, real(SY), 'b','LineWidth',2);
plot(k, real(FSY), 'r');
grid on;
title('Реальная часть образа sin(t)');
xlabel('Частота');
ylabel('Реальная часть образа sin(t)');
legend('ДПФ', 'fft');

subplot(2, 2, 2);
hold on;
plot(k, imag(SY), 'b','LineWidth',2);
plot(k, imag(FSY), 'r');
grid on;
title('Мнимая часть образа sin(t)');
xlabel('Частота');
ylabel('Мнимая часть образа sin(t)');
legend('ДПФ', 'fft');

subplot(2, 2, 3);
hold on;
plot(k, real(CY), 'b','LineWidth',2);
plot(k, real(FCY), 'r');
grid on;
title('Реальная часть образа cos(t)');
xlabel('Частота');
ylabel('Реальная часть образа cos(t)');
legend('ДПФ', 'fft');

subplot(2, 2, 4);
hold on;
plot(k, imag(CY), 'b','LineWidth',2);
plot(k, imag(FCY), 'r');
grid on;
title('Мнимая часть образа cos(t)');
xlabel('Частота');
ylabel('Мнимая часть образа cos(t)');
legend('ДПФ', 'fft');

figure(4);
subplot(2, 1, 1);
hold on;
plot(k, abs(SY).^2, 'b','LineWidth',2);
plot(k, abs(FSY).^2, 'r');
grid on;
title('Квадрат модуля Фурье-образа sin(t)');
xlabel('Частота');
ylabel('Квадрат модуля образа');
legend('ДПФ', 'fft');

subplot(2, 1, 2);
hold on;
plot(k, abs(CY).^2, 'b','LineWidth',2);
plot(k, abs(FCY).^2, 'r');
grid on;
title('Квадрат модуля Фурье-образа cos(t)');
xlabel('Частота');
ylabel('Квадрат модуля образа');
legend('ДПФ', 'fft');

disp('**********   Конец работы   **********');