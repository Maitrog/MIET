function [threshold, hysteresis, logistical, th]=neuron_active(v, a1, a2)
v0 = 0;
threshold = v>v0;
hysteresis=[];
for i = v
    if i<=0
        hysteresis = [hysteresis, 0];
    elseif i<=1
        hysteresis = [hysteresis, i];
    else
        hysteresis = [hysteresis, 1];
    end;
end;

logistical = 1./(1+exp(-a1.*v));
th  = tanh(v./a2);
