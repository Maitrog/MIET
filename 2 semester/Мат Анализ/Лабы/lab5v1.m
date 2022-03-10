function [X,Y]=lab5v1(f,x0,y0,int,n0)
eps=0.001;
dx=(int(2)-int(1))/n0;
x=x0:dx:int(2);
y(1)=y0;
for i=2:1:n0+1
    y(i)=y(i-1)+f(x(i-1),y(i-1))*(x(i)-x(i-1));
end
figure(1)
plot(x,y)
hold on; grid on;
if (x(n0+1)-x(n0))>=eps
    n0=2*n0;
    [X,Y]=lab5v1(f,x0,y0,int,n0);
else
    X=x;
    Y=y;
end
end
