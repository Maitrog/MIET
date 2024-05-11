close all; clear all;

v = -10:0.01:10;
[threshold, hysteresis, logistical, th] = neuron_active(v, 1, 1);

threshold_result = [v; threshold]';
hysteresis_result = [v; hysteresis]';
logistical_result = [v; logistical]';

subplot(4, 1, 1);
plot(v, threshold,'LineWidth',2);
grid on;
title('Единичный скачок или пороговая функция');
xlabel('v');
ylabel('y');

subplot(4, 1, 2);
plot(v, hysteresis,'LineWidth',2);
grid on;
title('Линейный порог или гистерезис');
xlabel('v');
ylabel('y');

subplot(4, 1, 3);
plot(v, logistical,'LineWidth',2);
grid on;
title('Сигмоидная функция');
xlabel('v');
ylabel('y');

subplot(4, 1, 4);
plot(v, th,'LineWidth',2);
grid on;
title('Гиперболический тангенс');
xlabel('v');
ylabel('y');