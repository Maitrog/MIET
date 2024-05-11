function [P,T] = get_input(x, count)
P=zeros(count,length(x));
T=zeros(3,count);
for i=1:count
 c=0.9*rand+0.1;
 a=0.9*rand+0.1;
 s=0.9*rand+0.1;
 T(1,i)=c;
 T(2,i)=a;
 T(3,i)=s;
 P(i,:)=c*exp(-((x-a).^2/s));
end
P=P';
end