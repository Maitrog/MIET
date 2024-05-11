function new_digit = test_hop_net_5(weights,digit)

% ������������ ��������� ���� �������� � ������� 5 �������� � ����������� ����������

clf; 
bnw = [1 1 1; 0 0 0];
new_digit = digit;

X = 7;
Y = 5;
k = 1;
iteration_visualization_step = 9; 

% 5 ������ ���� ������������
for i=1:5
    
% � ������ ����� ��������� �������� ����������� ��������� ������� 
    update_order = 1:63;
    
    for j=1:63
    
% ����������� ������ ������������ ����� ������ 9 ����������
        if mod(j-1,iteration_visualization_step)==0              
            subplot(Y,X,k);
            mx = max(new_digit);
            mn = min(new_digit);
            rn = mx - mn;
            img = reshape(new_digit,7,9);
            image((img'-mn)*255/rn);
        	axis image
        	axis off
        	colormap(bnw)
        	title(sprintf('Iteration %d', (k-1)*9));
            k = k + 1;
        end

% ���������� �������� ���������� ������� � ���� � ����� �� ������ ������ ��������� (4.5) � (4.6) 
% � �������� ������������ ������
%         neuron = update_order(1,j);
%         net = new_digit * weights(:,neuron);
%         if net>0
%             new_digit(1,neuron) = +1;
%         elseif net<0
%             new_digit(1,neuron) = -1;
%         end
        new_digit = (2*(weights * new_digit' >= 0) - 1)';
    end
end


    