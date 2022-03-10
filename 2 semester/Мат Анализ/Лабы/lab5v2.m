function [P] = lab5v2(f,x0,y0,a,b,n)
syms x t
p=y0;
P=p;
for i=1:1:n
    p=y0+int(feval(f,t,subs(p)),t,x0,x);
    P=[P p];
end
hold on
grid on
fplot(@(x)subs(P(n+1)),[a b])
end