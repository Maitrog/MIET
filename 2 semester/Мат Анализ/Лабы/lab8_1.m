function [df dz] = lab8_1(f,x0,y0,delx,dely)
%функция вычисляет первый дифференциал функции F(x,y)
syms dx dy x y
X=diff(subs(f),x);
Y=diff(subs(f),y);
df=subs(X,{x y},{x0 y0})*dx + subs(Y,{x y},{x0 y0})*dy;
dz=subs(df,{dx dy},{delx dely});
end