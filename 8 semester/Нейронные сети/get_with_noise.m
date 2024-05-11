function P = get_with_noise(arr, noise)
noise = noise * 10000;
P=arr;
if noise > 0
    for i=1:length(arr)
        P(:,i) = P(:,i) + (randi(noise,[1,21])/10000)';
    end
end
end