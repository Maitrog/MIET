function MyClear
%функция MyClear.m обрабатывает нажатие кнопки CLEAR

%глобальные переменные, доступные из других функций
global hAxes1 hAxes2;

%стирает графический объект hAxes1
axes(hAxes1);
cla;

%стирает графический объект hAxes2
axes(hAxes2);
cla;
