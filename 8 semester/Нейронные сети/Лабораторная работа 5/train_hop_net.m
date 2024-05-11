function weights = train_hop_net(digits)

% ��������� ��������� ���� ��������. 
% ������� �������� ��� ���� �������� ������������ ���������������� � ��������
% ��������� ��������� ������ ����� ���������� �������� � ����� ���������
% ������ (�������������� "����-�����").
% ���������� digits = {four five six} - ������ �������� ���������������
% ������
% ���������� weights ���������� ������� ������� ������������� ��������� ���� ��������
% (������������� ������)

% MAXPICNUM = size(digits,2);

% weights = zeros(63, 63);
% 
% ��� ������� ���������� ������� �������, ������������ �����������
% ���������� ������� input
% 
% for P=1:MAXPICNUM
%     input = digits{P};
%     weights = weights + (input'*input);
% end
% 
% % ��������� ������������ ���������
%  weights = (weights).*~(eye(63));

digits = reshape([digits{:}], size(digits{1}, 2), size(digits{1}, 1) * numel(digits));

% digits = padarray(digits, [20, 0]);

weights = digits * digits';