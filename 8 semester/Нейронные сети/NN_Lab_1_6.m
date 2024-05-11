close all; clear all;

syms t a
v = -10:0.01:10;

y=1/(1+exp(-a*t));  % ������������� �������

alpha = 1;

z = diff(y, t)      % �����������, ����������� ������������
z = subs(z, a, alpha);
z = subs(z, t, v);

z = double(collect(z));

[threshold, hysteresis, logistical, th] = neuron_active(v, 1, 1);
dydt = diff(logistical) ./ diff(v); % �����������, ����������� ��������

subplot(2, 1, 1);
plot(v, z,'LineWidth',2);
grid on;
title('����������� ������������');
xlabel('t');
ylabel('y');

subplot(2, 1, 2);
plot(v(1:length(v)-1), dydt,'LineWidth',2);
grid on;
title('����������� ��������');
xlabel('t');
ylabel('y');