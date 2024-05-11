function net = get_net
net = feedforwardnet(15,'trainlm');
net.performFcn='sse';
net.trainParam.goal=0.01;
net.trainParam.epochs=1000;
end