function [df dz] = lab8_2(f,x0,y0,delx,dely)
%функция вычисляет второй дифференциал функции F(x,y)
syms dx dy x y
X=diff(subs(f),x,2);
Y=diff(subs(f),y,2);
XY=diff(diff(subs(f),x),y);
df=subs(X,{x y},{x0 y0})*dx^2 + subs(Y,{x y},{x0 y0})*dy^2 + 2*subs(XY,{x y},{x0 y0})*dx*dy;
dz=subs(df,{dx dy},{delx dely});
end