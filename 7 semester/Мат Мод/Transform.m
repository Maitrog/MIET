function X1 = Transform(X,S,s,n)
    for i = 1: n
        for j=1:n
            X1(i,j) = (S(i)*abs(S(j))-S(j)*abs (S(i)))/s;
        end
    end
end
