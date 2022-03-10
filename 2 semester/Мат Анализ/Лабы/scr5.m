f=@(x,y)(y^2-y)/x;
x0=1; y0=0.5;
int=[1 2];
n0=100;
(f,x0,y0,int,n0);
figure(2)
hold on; grid on;
plot(x,y)
x2=x;
y2=1./x+1;
plot(x2,y2);
delta=max(abs(y2-y))
