function [E,n] = Euler(fname,x0,y0,a,b,n0,eps)
%функци€ находит приближенное решение уравнение y'=f(x,y),
%удовлетвор€ющее начальному условию y(x0)=y0, на отрезке [a;b]
%методом ломаных Ёйлера с заданной точностью eps
n=n0;
dx=(b-a)/n;
E0=[x0;y0];
x=x0;
y=y0;
for i=1:1:n
x=x+dx;
y=y+feval(fname,x,y)*dx;
E0=[E0(1,:) x; E0(2,:) y];
end
E1=E0;
n=n*2;
dx=(b-a)/n;
E0=[x0;y0];
x=x0;
y=y0;
for i=1:1:n
x=x+dx;
y=y+feval(fname,x,y)*dx;
E0=[E0(1,:) x; E0(2,:) y];
end
E2=E0;
dE=abs(max(E2(2,:))-max(E1(2,:)));
while dE>eps
n=n*2;
dx=(b-a)/n;
E=E0;
E0=[x0;y0];
x=x0;
y=y0;
for i=1:1:n
x=x+dx;
y=y+feval(fname,x,y)*dx;
E0=[E0(1,:) x; E0(2,:) y];
end
dE=abs(max(E0(2,:))-max(E(2,:)));
end
E=E0;
figure
hold on
grid on
plot(E1(1,:),E1(2,:),'b')
plot(E2(1,:),E2(2,:),'g')
plot(E(1,:),E(2,:),'r')
axis([a b min(E(2,:)) max(E(2,:))])
end