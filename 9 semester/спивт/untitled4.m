%test = -10+(20)*rand(5,5)
%test = sort(test)
%test = sort(test,2)

format short
st = sort(-10+(20)*rand(1,25));
for i = 1:1:4
    for j = 1:1:5
        test(i,j) = st(i+j+(5*(i-1))-1);
    end
end

for j = 1:1:5
        test(5,j) = st(20+j)
end

writematrix(test, 'Tr.dat')
