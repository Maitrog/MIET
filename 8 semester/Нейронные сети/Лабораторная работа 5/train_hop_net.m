function weights = train_hop_net(digits)

% Настройка нейронной сети Хопфилда. 
% Весовые значения для сети Хопфилда определяются непосресдственно в процессе
% обработки обучающих данных минуя проведение обучения в более привычном
% смысле (сопоставлением "вход-выход").
% Переменная digits = {four five six} - список образцов фундаментальной
% памяти
% Переменная weights определяет матрицу весовых коэффициентов нейронной сети Хопфилда
% (ассоциативной памяти)

% MAXPICNUM = size(digits,2);

% weights = zeros(63, 63);
% 
% Это правило заполнения весовой матрицы, определяющее запоминание
% некоторого вектора input
% 
% for P=1:MAXPICNUM
%     input = digits{P};
%     weights = weights + (input'*input);
% end
% 
% % Обнуление диагональных элементов
%  weights = (weights).*~(eye(63));

digits = reshape([digits{:}], size(digits{1}, 2), size(digits{1}, 1) * numel(digits));

% digits = padarray(digits, [20, 0]);

weights = digits * digits';