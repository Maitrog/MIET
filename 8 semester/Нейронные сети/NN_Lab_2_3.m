clear;
clc;
% Задание весов и значения порога
disp('Введите веса');
w_11=input('Вес w_11 =');
w_12=input('Вес w_12 =');
w_21=input('Вес w_21 =');
w_22=input('Вес w_22 =');
w11=input('Вес w11 =');
w12=input('Вес w12 =');
disp('Введите величину порога');
theta=input('Порог =');
y1=[0 0 0 0];
y2=[0 0 0 0];
y=[0 0 0 0];
x1=[0 1 0 1];
x2=[0 0 1 1];
z=[0 1 1 0];
con=1;
while con
  zin1=x1*w_11+x2*w_21;
  zin2=x1*w_12+x2*w_22;
  for i=1:4
      if zin1(i)>=theta
          y1(i)=1;
      else
          y1(i)=0;
      end
      if zin2(i)>=theta
          y2(i)=1;
      else
          y2(i)=0;
      end
  end
  zin=y1*w11+y2*w12;
  for i=1:4
      if zin(i)>=theta
          y(i)=1;
      else
          y(i)=0;
      end
  end
  disp('Значение на входе нейрона x1');
  disp(x1);
  disp('Значение на входе нейрона x2');
  disp(x2);
  disp('Значение на выходе нейрона');
  disp(y);
  if y==z
      con=0;
  else
      disp('Нейрон не обучен. Ввведите другие значения весовых коэффициентов и порога');
      	  w_11=input('Вес w_11 =');
          w_12=input('Вес w_12 =');
          w_21=input('Вес w_21 =');
          w_22=input('Вес w_22 =');
          w11=input('Вес w11 =');
          w12=input('Вес w12 =');
      	  theta=input('Порог =');
  end
end
disp('Нейрон МакКаллока-Питса для функции "Исключающее ИЛИ" (англ. "XOR")');
disp('Веса нейрона');
disp(w_11);
disp(w_12);
disp(w_21);
disp(w_22);
disp(w11);
disp(w12);
disp('Пороговое значение');
disp(theta);
