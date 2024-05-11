function result = noisy_digit(digit,noise)

% Создание зашумлённой версии входного образа
% Переменная digit задаёт входной образ из фундаментальной памяти или произвольный образ
% Переменная noise определяет уровень шума, добавляемого к исходному вектору

if noise<0 | noise>1
    error('Уровень шума должен быть в пределах от 0 до 1\n');
end

[r c] = size(digit);

if r~=1 | c~=63
    error('Входной вектор должен иметь размерность(1,63)\n');
end

result = digit;
for i=1:r
    for j=1:c
        if rand<noise 
            if rand<0.5
                result(i,j)=-1;
            else
                result(i,j)=1;
            end
        end
    end
end

