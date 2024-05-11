function show_digits(digits)

clf;

bnw = [1 1 1; 0 0 0];

MAXPICNUM = size(digits,2);

% Параметры для отображения массива образов на экране дисплея
X = 3;
Y = 4;

for P=1:MAXPICNUM
	subplot(Y,X,P);
    digit = digits{P};
    mx = max(digit);
    mn = min(digit);
    rn = mx - mn;
    img = reshape(digit,7,9);
    image((img'-mn)*255/rn);
	axis image
	axis off
	colormap(bnw)
	title(sprintf('Число %d', P));
end
