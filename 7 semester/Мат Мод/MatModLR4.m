N0=0.0001;
t=0:0.5:20;
alpha=exp(0.00002.*t);
% alpha=0.1;
% Np=100000000-2000.*t;
Np=10-t.*0;
N=Np.*N0.*exp(alpha.*t)./(Np(1)-N0.*(1-exp(alpha.*t)));
plot(t,N);
hold on; grid on;
plot(t,Np,'--')
axis([ 0 20 -0.1 11])