% ��������� ���� 
% ������������ ������ 1

% ��������� ���������� ��� �������������� �������
close all; clear all;

disp('*** ��������� ���������� ��� �������������� ������� ***');
A   = input('������� ��������� �������, ��.: ');
f0  = input('������� ������� �������, ��: ');

fdn = 2*f0;       % ������� �������������
                  % � ������������ � ��������� ���������
mvis= 10;
fdv = mvis*fdn;   % ������� ������������� ��� ������������
dt  = 1/fdv;      % �������� ������������� �� �������
T   = 1/f0;       % ������ �������
NT  = 6;
t   = 0:dt:NT*T;  % ������ �������, �
y   = A*sin(2*pi*f0*t);
                  % ������ �������
N   = length(y);
                  
% ���������� �������������� �����
k   = 0:N-1;
Ex  = exp(-j*2*pi/N*k'*k);
Y   = y*Ex;

% �������� ���������� �������������� �����
Ex  = exp(j*2*pi/N*k'*k);
ys  = Y/(N-1)*Ex;

Y2  = Y.*conj(Y);  % ������� ������ �����-������
ff  = k*fdv/N; % ������ �������, ��

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

disp('**********   ����� ������   **********');