function  lab7_2(F)
syms x y z
%находим первые производные
Fdx=diff(F,x,1);
Fdy=diff(F,y,1);
Fdz=diff(F,z,1);
%находим стационарные точки
s=solve(Fdx, Fdy,Fdz);
x0=vpa(s.x);
y0=vpa(s.y);
z0=vpa(s.z);
%находим вторые производные
Fdx2=diff(Fdx,x,1);
Fdy2=diff(Fdy,y,1);
Fdz2=diff(Fdz,z,1);
Fdxdy=diff(Fdx,y,1);
Fdxdz=diff(Fdx,z,1);
Fdydz=diff(Fdy,z,1);
for i=1:1:size(x0)
    x=x0(i);
    y=y0(i);
    z=z0(i);
    A=eval(Fdx2);
    B=eval(Fdy2);
    C=eval(Fdz2);
    D=eval(Fdxdy);
    E=eval(Fdxdz);
    F=eval(Fdydz);
    if A*B*C+2*(D*F*E)-B*E^2-A*F^2-C*D^2==0 && A*B-D^2==0 && A==0
        str=sprintf('P%d(%f; %f; %f) - требуются доп. исследования',i,x,y,z);
        disp(str)
    else
    if A*B*C+2*(D*F*E)-B*E^2-A*F^2-C*D^2>0
        if  A*B-D^2>0
            if A>0
                str=sprintf('P%d(%f ;%f; %f) - min',i,x,y,z);
                disp(str)
            else
                str=sprintf('P%d(%f; %f; %f) - не экстремум',i,x,y,z);
                disp(str)
            end
        else
            str=sprintf('P%d(%f; %f; %f) - не экстремум',i,x,y,z);
            disp(str)
        end
    else
        if A*B*C+2*(D*F*E)-B*E^2-A*F^2-C*D^2<0
            if  A*B-D^2>0
                if A<0
                    str=sprintf('P%d(%f; %f; %f) - max',i,x,y,z);
                    disp(str)
                else
                    str=sprintf('P%d(%f; %f; %f) - не экстремум',i,x,y,z);
                    disp(str)
                end
            else
                str=sprintf('P%d(%f; %f; %f) - не экстремум',i,x,y,z);
                disp(str)
            end
        end
    end
    end
    
end

