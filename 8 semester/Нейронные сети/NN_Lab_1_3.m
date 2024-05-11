close all; clear all;

f0  = 2000;

disp(strcat('*** ��������� ������������ ������� ������ � �������� � �������� ', num2str(f0), ' �� ***'));
Tnab= input('������� �������� ����������, ��.: ');
Tnab= Tnab / 1000;
pnt = input('������� ���������� ����� ����������: ');

fdn = 2*f0;       % ������� �������������
                  % � ������������ � ��������� ���������
mvis= 8;
fdv = mvis*fdn;   % ������� ������������� ��� ������������
dt  = 1/fdv;      % �������� ������������� �� �������
T   = 1/f0;       % ������ �������
NT  = f0 * Tnab;  % ���������� �������� ����������
t   = 0:dt:NT*T;  % ������ �������, �
sinp= sin(2*pi*f0*t); % ������ �������
cosp= cos(2*pi*f0*t); % ������ �������

figure(1);
subplot(2, 1, 1);
plot(t, sinp, 'r');
grid on;
axis([0 NT*T -1.1 1.1]);
title('y = sin(t)');
xlabel('�����, �');
ylabel('�������� ������');
subplot(2, 1, 2);
plot(t, cosp, 'r');
grid on;
axis([0 NT*T -1.1 1.1]);
title('y = cos(t)');
xlabel('�����, �');
ylabel('�������� ������');

t   = 0:dt:(pnt-1)*dt;
sinn= sin(2*pi*f0*t);
cosn= cos(2*pi*f0*t);

figure(2);
subplot(2, 1, 1);
plot(t, sinn, 'r');
grid on;
axis([0 (pnt-1)*dt -1.1 1.1]);
title('y = sin(t)');
xlabel('�����, �');
ylabel('�������� ������');
subplot(2, 1, 2);
plot(t, cosn, 'r');
grid on;
axis([0 (pnt-1)*dt -1.1 1.1]);
title('y = cos(t)');
xlabel('�����, �');
ylabel('�������� ������');
                  
% ���������� �������������� �����
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
title('�������� ����� ������ sin(t)');
xlabel('�������');
ylabel('�������� ����� ������ sin(t)');
legend('���', 'fft');

subplot(2, 2, 2);
hold on;
plot(k, imag(SY), 'b','LineWidth',2);
plot(k, imag(FSY), 'r');
grid on;
title('������ ����� ������ sin(t)');
xlabel('�������');
ylabel('������ ����� ������ sin(t)');
legend('���', 'fft');

subplot(2, 2, 3);
hold on;
plot(k, real(CY), 'b','LineWidth',2);
plot(k, real(FCY), 'r');
grid on;
title('�������� ����� ������ cos(t)');
xlabel('�������');
ylabel('�������� ����� ������ cos(t)');
legend('���', 'fft');

subplot(2, 2, 4);
hold on;
plot(k, imag(CY), 'b','LineWidth',2);
plot(k, imag(FCY), 'r');
grid on;
title('������ ����� ������ cos(t)');
xlabel('�������');
ylabel('������ ����� ������ cos(t)');
legend('���', 'fft');

figure(4);
subplot(2, 1, 1);
hold on;
plot(k, abs(SY).^2, 'b','LineWidth',2);
plot(k, abs(FSY).^2, 'r');
grid on;
title('������� ������ �����-������ sin(t)');
xlabel('�������');
ylabel('������� ������ ������');
legend('���', 'fft');

subplot(2, 1, 2);
hold on;
plot(k, abs(CY).^2, 'b','LineWidth',2);
plot(k, abs(FCY).^2, 'r');
grid on;
title('������� ������ �����-������ cos(t)');
xlabel('�������');
ylabel('������� ������ ������');
legend('���', 'fft');

disp('**********   ����� ������   **********');