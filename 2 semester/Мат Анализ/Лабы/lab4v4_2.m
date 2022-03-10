function [x] = lab4v4_2(fname,a,x0,eps)
%функцию для решения уравнения f(X)=X с заданной точностью eps
%с выводом последовательности приближений
x1=feval(fname,x0);
x2=feval(fname,x1);
p=abs(x1-x2);
n=(log(eps*(1-a))-log(p))/log(a);
x=zeros(fix(n+1),1);
for i=1:1:(n+1);
x(i)=x0;
x0=feval(fname,x0);
end
end