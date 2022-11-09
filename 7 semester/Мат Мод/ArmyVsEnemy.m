function dydt = ArmyVsEnemy(t,y,a1,a2,b1,b2,g1,g2)
    dydt = zeros(2,1);
    dydt(1) = -a1*y(1)-b2*y(2)+g1;
    dydt(2) = -a2*y(2)-b1*y(1)*y(2)+g2;
end