run self_digits

% Первоначальные образы
w = train_hop_net({one four eight});
test_hop_net_5(w, noisy_digit(four, .0));
pause;

% Модифицированные образы
one2 = one;
one2(2:end-1) = one(1:end-2);

four2 = four;
four2(1:end-1) = four(2:end);

eight2 = eight;
eight2(8:end) = eight(1:end-7);

w = train_hop_net({one2 four2 eight2});
test_hop_net_5(w, noisy_digit(four2, .0));