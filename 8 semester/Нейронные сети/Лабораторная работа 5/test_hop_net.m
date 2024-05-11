function new_digit = test_hop_net(weights, digit, iterations)

% Тестирование нейронной сети Хопфилда
% Переменная weights описывает весовые коэффициенты рекуррентной сети с сохраненными элементами фундаментальной памяти
% Переменная digit - входной образ (может представлять собой и зашумленную версию исходного вектора)
% Переменная iterations - число "эпох" тестирования, имея в виду под эпохой
% полное обновление состояния каждого из нейронов в случайном порядке

new_digit = digit;

for epoch=1:iterations
    update_order = randperm(63);
    % Обновление состояния нейронов в случайном порядке
    for i=1:63
        neuron = update_order(1,i);
        net = new_digit * weights(:,neuron);
        if net>0
            new_digit(1,neuron) = +1;
        elseif net<0
            new_digit(1,neuron) = -1;
        end
    end
end

    
