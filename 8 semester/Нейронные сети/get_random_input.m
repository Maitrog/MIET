function [P,T] = get_random_input(x, count)
P=zeros(count,length(x));
T=zeros(3,count);
for i=1:count
 c=0.9*rand+0.1;
 a=0.9*rand+0.1;
 s=0.9*rand+0.1;
 T(1,i)=c;
 T(2,i)=a;
 T(3,i)=s;
 P(i,:)=rand(1,21);
end
P=P';
end