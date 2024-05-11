clear all; close all;
% Формирование входных массивов (входной массив P) и (эталоны T)
x=0:5.e-2:1;
count=100;
[P,T]=get_input(x,count);
% net=newff(minmax(P),[21,15,3],{'logsig' 'logsig' 'purelin'},'trainlm');
net = get_net();
[net,tr]=train(net,P,T);

%добавляем шум(0-0.01)
P1=get_with_noise(P, 0.01);
net1 = get_net();
[net1,tr1]=train(net1,P1,T);
%добавляем шум(0-0.05)
P2=get_with_noise(P, 0.05);
net2 = get_net();
[net2,tr2]=train(net2,P2,T);
% %добавляем шум(0-0.1)
P3=get_with_noise(P, 0.1);
net3 = get_net();
[net3,tr3]=train(net3,P3,T);
% %добавляем шум(0-0.2)
P4=get_with_noise(P, 0.2);
net4 = get_net();
[net4,tr4]=train(net4,P4,T);

p=0.2*exp(-((x-0.8).^2/0.7));
Y=sim(net,p')
Y1=sim(net1,p')
Y2=sim(net2,p')
Y3=sim(net3,p')
Y4=sim(net4,p')