function lab4v4(f, x1, eps, int)
df=char(diff(f));
i=1;
for x=int(1):0.001:int(2)
    res(i)=abs(eval(df));
    L(i)=abs(eval(df))<1;
    i = i + 1;
end
x=x1;
x2=eval(f);
res2=res(L);
alpha = max(res2)
n=(log(eps*(1-alpha))-log(abs(x2-x1)))/log(alpha);
n=ceil(n)
end