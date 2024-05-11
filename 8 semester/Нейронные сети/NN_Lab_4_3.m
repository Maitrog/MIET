[alphabet,targets]=lab4Rus;
[R,Q] = size(alphabet);
[S3,Q] = size(targets);
S1 = 20;
S2 = 20;
netRus = newff(minmax(alphabet),[S1 S2 S3],{ 'logsig','logsig','logsig'},'trainlm');
netRus.LW{3,2} = netRus.LW{3,2}*0.01;
netRus.b{2} = netRus.b{2}*0.01;
netRus.b{3} = netRus.b{3}*0.01;

%Обучение нейронной сети с влиянием шума
P = alphabet;
T = targets;
netRus.performFcn = 'sse';
netRus.trainParam.goal = 0.3;
netRus.trainParam.show =20;
netRus.trainParam.epochs= 300;
netRus.trainParam.mc = 0.95;
T = [targets targets targets targets];
for pass = 1:10
P = [alphabet, alphabet, (alphabet + randn(R,Q) *0.1),(alphabet + randn(R,Q) *0.2) ];
[netRus,tr] = train (netRus, P,T);
end;
%%Повторное обучение в отсутствие шума
netRus.trainParam.goal = 0.1;
% Предельная среднеквадратичная погрешность
netn.trainParam.epochs = 500;
% Максимальное количество циклов обучения
netRus.trainParam.show = 5 ;
% Частота вывода результатов на экран
[netRus,tr] = train(netRus,P,T);

for iter = 1:9
    figure(iter)
    noisyA = alphabet(:,iter)+randn(35,1)*0.2;
    subplot(1,2,1);
    % Зашумленный символ
    plotchar(noisyA); 
    A2 = sim(netRus,noisyA);
    A2 = compet(A2);
    answer = find(compet(A2));
    subplot(1,2,2);
    %Восстановленный
    plotchar(alphabet(:,answer));
end;