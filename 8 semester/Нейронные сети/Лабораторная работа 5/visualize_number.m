function visualize_number(digit)

bnw = [1 1 1; 0 0 0];
clf;
subplot(1,1,1);
mx = max(digit);
mn = min(digit);
rn = mx - mn;
img = reshape(digit,7,9);
image((img'-mn)*255/rn);
axis image
axis off
colormap(bnw)


