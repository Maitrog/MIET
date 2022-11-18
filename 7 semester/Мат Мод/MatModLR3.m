A0=1;
P0=0.9;
k=0.1;
S=A0+P0;
% P=P0:0.001:S-0.1;

% t=1./(S.^2).*log(A0.*P./P0./(S-P))+1./S.*(1./(S-P)-1/A0)./k;

system=@(t,P)(k*(S-P^2)*P);
range = [0 20];
[t,P] = ode45(system, range, P0);


hold on; grid on;
A=S-P;
plot(t,P);
plot(t,A);

figure(2)
hold on, grid on
plot(P,A)