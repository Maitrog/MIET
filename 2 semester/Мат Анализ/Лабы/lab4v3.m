function lab4v3(f, x0)
n(1)=x0;
for i=2:1:10
    n(i)=f(n(i-1));
end
n
end