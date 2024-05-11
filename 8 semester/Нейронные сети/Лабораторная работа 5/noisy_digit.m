function result = noisy_digit(digit,noise)

% �������� ���������� ������ �������� ������
% ���������� digit ����� ������� ����� �� ��������������� ������ ��� ������������ �����
% ���������� noise ���������� ������� ����, ������������ � ��������� �������

if noise<0 | noise>1
    error('������� ���� ������ ���� � �������� �� 0 �� 1\n');
end

[r c] = size(digit);

if r~=1 | c~=63
    error('������� ������ ������ ����� �����������(1,63)\n');
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

