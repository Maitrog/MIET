function Lab5_1( f,X0,A,n0,e )
% f - функция с символьными х,у
% Х0 - координаты начальной точки
% А - отрезок [a,b]
% n0 - начальное число отрезкой разбиения
% е - точность

x0=X0(1);
y0=X0(2);
a=A(1);
b=A(2);

X=zeros(1,3);
Y=X;
dx=(b-a)/n0; %длина отрезка разбиения
X(1)=x0;
Y(1)=y0;
for i=1:1:n0
    syms x y
    y0=y0+subs(subs(f,x,x0),y,y0)*dx;
    x0=x0+dx;
    X(i+1)=x0;
    Y(i+1)=y0;
end
dx=dx/2; %длина отрезка разбиения
x0=X0(1);
y0=X0(2);
X1(1)=x0;

Y1(1)=y0;
for i=1:1:2*n0
    y0=y0+subs(subs(f,x,x0),y,y0)*dx;
    x0=x0+dx;
    X1(i+1)=x0;
    Y1(i+1)=y0;
end
maax=max(abs(Y-Y1(1:2:end)));
Y1_=Y1;
x0=X0(1);
y0=X0(2);

%------графики--figure------%
figure(1)
hold on
grid on
plot(X,Y,'r');
plot(X1,Y1,'g');
%---------------------------%

m=0;
while maax&gt;e
    m=m+1;
    dx=dx/2;
    X2(1)=x0;
    Y2(1)=y0;
    n=(b-a)/dx;
    for i=1:1:n
        y0=y0+subs(subs(f,x,x0),y,y0)*dx;
        x0=x0+dx;
        X2(i+1)=x0;
        Y2(i+1)=y0;
    end
    maax=max(Y1_-Y2(1:2:end));
    Y1_=Y2;
end
if m==0
    fprintf('Точности хватает для построение 2-х графиков\n');
else
%------графики--figure------%
plot(X2,Y2,'b');
%---------------------------%
end
end