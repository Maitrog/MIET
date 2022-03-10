phi=const;
z=cos(phi)+i*sin(phi);
x=0:.1:1000;
y=x*real(z);
plot(x,y)
xlabel('Re(z)')
ylabel('Im(z)')
