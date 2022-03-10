function [p df] = lab8_4(f,x0,y0,dx,dy)
%функция раскладывает f(x y) по формуле тейлора в
%окрестности точки x0 y0
syms x y
X=diff(subs(f),x);
Y=diff(subs(f),y,2);
XY=diff(subs(X),y);
X=diff(subs(X),x);
p=lab8_3(f,x0,y0,dx,dy)+0.5*subs(X,{x y},{x0 y0})*(x-x0)^2+...
0.5*subs(Y,{x y},{x0 y0})*(y-y0)^2+subs(XY,{x y},{x0 y0})*(x-x0)*(y-y0);
df=subs(p,{x y},{x0+dx y0+dy});
end