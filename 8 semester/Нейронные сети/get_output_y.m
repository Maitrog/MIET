function [y] = get_output_y(n, w, input_x)
y=[power(w, 1) * input_x(n)];
for i=2:1:n
    y = [y, power(w, i) * input_x(n - i + 1)];
end
end