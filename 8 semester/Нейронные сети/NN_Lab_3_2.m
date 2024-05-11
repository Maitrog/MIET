clear all; close all;
% Формирование входных массивов (входной массив P) и (эталоны T)
x=0:5.e-2:1;
count=100;
[P,T]=get_random_input(x,count);
net = get_net();
[net,tr]=train(net,P,T);

y=sim(net,P);
figure(1)
postreg(y(1,:),T(1,:));
figure(2)
postreg(y(2,:),T(2,:));
figure(3)
postreg(y(3,:),T(3,:));

p=0.2*exp(-((x-0.8).^2/0.7));
Y=sim(net,p')