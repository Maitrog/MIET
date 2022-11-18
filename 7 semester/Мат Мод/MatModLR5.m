b1=0.01;
b2=0.02;
a1=0.01;
a2=0;
g1=0;
g2=0;
N1_0=10000;
N2_0=10000;

range = [0 10000];
[t,y] = ode45(@(t,y) ArmyVsArmy(t,y,a1,a2,b1,b2,g1,g2), range, [N1_0; N2_0]);
plot(t,y(:,1),'-',t,y(:,2),'-')
hold on; grid on;

i=1;
while(i<=length(y) && y(i,1)>0 && y(i,2)>0)
    maxX=t(i);
    i=i+1;
end
axis([0, maxX, 0, max(N1_0, N2_0)])