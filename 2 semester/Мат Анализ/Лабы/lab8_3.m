function [p df] = lab8_3(f,x0,y0,dx,dy)
%функция раскладывает f(x y) по формуле тейлора в
%окрестности точки x0 y0
syms x y
X=diff(subs(f),x);
Y=diff(subs(f),y);
p=subs(f,{x y},{x0 y0})+subs(X,{x y},{x0 y0})*(x-x0)+ subs(Y,{x y},{x0 y0})*(y-y0);
df=subs(p,{x y},{x0+dx y0+dy});
end