function [X,k] = lab4v5(A,B,eps)
%функция для решения методом простой итерации системы
%уравнений АХ=B
for i=1:length(A)
A(i,:)=A(i,:)/A(i,i);
B(i,:)=B(i,:)/A(i,i);
end
sum=0;
C=A-eye(size(A));
if abs(eig(C))<1
a=0.7;
x0=B; % за начальный вектор приближений берем
%правый столбец свободных членов x=b
x1=B+C*x0;
for q=1:1:length(B)
    sum=sum+(x0(q)-x1(q))^2;
end
p=sqrt(sum);
n=(log(eps*(1-a))-log(p))/log(a);
k=1; % счетчик числа итераций
x=zeros(length(B),fix(n+1));
for i=1:1:(n+1);
x(:,i)=x0;
x0=B+C*x0;
k=k+1;
end
X=x(:,k-1);
else disp('система не сходится')
end
end
