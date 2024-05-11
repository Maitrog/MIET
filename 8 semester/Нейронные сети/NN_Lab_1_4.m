close all; clear all;

f0  = 2000;
edft = [0];         % ����� ���������� ��� 
efft = [0];         % ����� ���������� ���
expMax = 14;

for e = 7:expMax
    pnt=2^e;

    fdn = 2*f0;       % ������� �������������
                  % � ������������ � ��������� ���������
    mvis= 8;
    fdv = mvis*fdn;   % ������� ������������� ��� ������������
    dt  = 1/fdv;      % �������� ������������� �� �������

    t   = 0:dt:(pnt-1)*dt;  % ������ �������, �
    y= sin(2*pi*f0*t);
    N   = length(y);
                  
    % ���
    k   = 0:N-1;
    tic
    SY  = y*exp(-j*2*pi/N*k'*k);
    edft = [edft, toc];

    % ���
    tic
    FSY = fft(y);
    efft = [efft, toc];
end

e = 7:expMax;
pnt = 2.^e;
pnt = [0, pnt];

figure(1);
subplot(2, 1, 1);
plot(pnt, edft);
grid on;
axis([0 max(pnt) 0 max(edft)]);
title('���������� ���');
xlabel('���������� �����');
ylabel('�����, �');
subplot(2, 1, 2);
plot(pnt, efft);
grid on;
axis([0 max(pnt) 0 max(efft)]);
title('���������� ���');
xlabel('���������� �����');
ylabel('�����, �');
