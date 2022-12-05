function X = matrix(n)
    X = randi([-100 100], n, n);
    for i = 1: n
        for j = i:n
            if (i == j)
                X(i,j) = 0;
            else
                X(i,j) = -X(j,i);
            end
        end
    end
end
