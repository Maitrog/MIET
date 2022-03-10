function lab7_1(Z,x0,y0)
syms x y
Zdx=diff(Z,x,1);
Zdy=diff(Z,y,1);
Zdx2=diff(Zdx,x,1);
Zdy2=diff(Zdy,y,1);
Zdxdy=diff(Zdx,y,1);
x=x0;
y=y0;
A=eval(Zdx2);
C=eval(Zdy2);
B=eval(Zdxdy);
if A*C-B^2>0
    if A<0
        str=sprintf('P%d(%d; %d) - max',i,x,y);
        disp(str)
    else
        str=sprintf('P%d(%d; %d) - min',i,x,y);
        disp(str)
    end
else
    if A*C-B^2<0
        str=sprintf('P%d(%d; %d) - не экстремум',i,x,y);
        disp(str)
    else
        str=sprintf('P%d(%d; %d) - требуются доп. исследования',i,x,y);
        disp(str)
    end
end
end

