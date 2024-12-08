function [x1,y1,x2,y2] = Section1(xb,xe,yb,ye,xs1,ys1,xs2,ys2)

%находим точки пересечения линии заданной точками (xs1,xs2),(ys1,ys2)
%с границами прямоугольника (xb,xe,yb,ye)

%точки пересечения с линиями границ
xp = [];
yp = [];

x1 = [];
y1 = [];
x2 = [];
y2 = [];

kx = xs2 - xs1;
ky = ys2 - ys1;

%линия сечения вертикальная
if(kx == 0)
    if((xb <= xs1) && (xs1 <= xe))
        xp = [xp,xs1]; yp = [yp,ye];
        xp = [xp,xs1]; yp = [yp,yb];
    end
end

%линия сечения горизонтальная
if(ky == 0)
    if((yb <= ys1) && (ys1 <= ye))
        xp = [xp,xb]; yp = [yp,ys1];
        xp = [xp,xe]; yp = [yp,ys1];
    end
end


if((kx ~= 0) && (ky ~= 0))
    yt = ky/kx*(xb - xs1) + ys1;
    if((yb <= yt) && (yt <= ye))
        xp = [xp,xb]; yp = [yp,yt];
    end

    yt = ky/kx*(xe - xs1) + ys1;
    if((yb <= yt) && (yt <= ye))
        xp = [xp,xe]; yp = [yp,yt];
    end

    xt = kx/ky*(yb - ys1) + xs1;
    if((xb <= xt) && (xt <= xe))
        xp = [xp,xt]; yp = [yp,yb];
    end
    
    xt = kx/ky*(ye - ys1) + xs1;
    if((xb <= xt) && (xt <= xe))
        xp = [xp,xt]; yp = [yp,ye];
    end
end

Lx = length(xp); Ly = length(xp);
if((Lx == 2) && (Ly == 2))
    x1 = xp(1); y1 = yp(1);
    x2 = xp(2); y2 = yp(2);
end
if((Lx == 3) && (Ly == 3))
    x1 = xp(1); y1 = yp(1);
    if(xp(2) ~= xp(1))
        x2 = xp(2); y2 = yp(2);
    else
        x2 = xp(3); y2 = yp(3);
    end
end

if((Lx == 4) && (Ly == 4))
    x1 = xp(1); y1 = yp(1);
    if(xp(2) ~= xp(1))
        x2 = xp(2); y2 = yp(2);
    else
        if(xp(3) ~= xp(1))
            x2 = xp(3); y2 = yp(3);
        else
            x2 = xp(4); y2 = yp(4);
        end
    end
end


if(((x2-x1)*(xs2-xs1)<=0) && ((x2-x1)*(xs2-xs1)<=0))
    a = x1; x1 = x2; x2 = a;
    a = y1; y1 = y2; y2 = a;
end



xp
yp
