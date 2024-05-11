close all; clear all;

f0  = 2000;
edft = [0];         % Время вычисления ДПФ 
efft = [0];         % Время вычисления БПФ
expMax = 14;

for e = 7:expMax
    pnt=2^e;

    fdn = 2*f0;       % Частота дискретизации
                  % в соответствии с критерием Найквиста
    mvis= 8;
    fdv = mvis*fdn;   % Частота дискретизации для визуализации
    dt  = 1/fdv;      % Интервал дискретизации по времени

    t   = 0:dt:(pnt-1)*dt;  % Вектор времени, с
    y= sin(2*pi*f0*t);
    N   = length(y);
                  
    % ДПФ
    k   = 0:N-1;
    tic
    SY  = y*exp(-j*2*pi/N*k'*k);
    edft = [edft, toc];

    % БПФ
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
title('Вычисление ДПФ');
xlabel('Количество точек');
ylabel('Время, с');
subplot(2, 1, 2);
plot(pnt, efft);
grid on;
axis([0 max(pnt) 0 max(efft)]);
title('Вычисление БПФ');
xlabel('Количество точек');
ylabel('Время, с');
