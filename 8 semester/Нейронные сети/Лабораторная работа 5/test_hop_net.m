function new_digit = test_hop_net(weights, digit, iterations)

% ������������ ��������� ���� ��������
% ���������� weights ��������� ������� ������������ ������������ ���� � ������������ ���������� ��������������� ������
% ���������� digit - ������� ����� (����� ������������ ����� � ����������� ������ ��������� �������)
% ���������� iterations - ����� "����" ������������, ���� � ���� ��� ������
% ������ ���������� ��������� ������� �� �������� � ��������� �������

new_digit = digit;

for epoch=1:iterations
    update_order = randperm(63);
    % ���������� ��������� �������� � ��������� �������
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

    
