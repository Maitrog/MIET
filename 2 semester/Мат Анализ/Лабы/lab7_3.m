function  lab7_3(F)
syms x y
%находим первые производные
Fdx=diff(F,x,1);
Fdy=diff(F,y,1);
%находим стационарные точки
s=solve(Fdx, Fdy);
x0=vpa(s.x);
y0=vpa(s.y);
%находим вторые производные
Fdx2=diff(Fdx,x,1);
Fdy2=diff(Fdy,y,1);
Fdxdy=diff(Fdx,y,1);
for i=1:1:size(x0)
    x=x0(i);
    y=y0(i);
    A=eval(Fdx2);
    C=eval(Fdy2);
    B=eval(Fdxdy);
    if A*C-B^2>0
    if A<0
        str=sprintf('P%d(%f; %f) - max',i,x,y);
        disp(str)
    else
        str=sprintf('P%d(%f; %f) - min',i,x,y);
        disp(str)
    end
else
    if A*C-B^2<0
        str=sprintf('P%d(%f; %f) - не экстремум',i,x,y);
        disp(str)
    else
        str=sprintf('P%d(%f; %f) - требуются доп. исследования',i,x,y);
        disp(str)
    end
    end
    
end
end
