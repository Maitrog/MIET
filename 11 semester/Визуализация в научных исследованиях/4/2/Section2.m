function [xL, zL] = Section2(xb, xe, N, yb, ye, M, x1, x2, y1, y2, x, y, z)
    % Шаги по осям Ox и Oy
    dx = (xe - xb) / (N - 1);
    dy = (ye - yb) / (M - 1);
    
    % Угловые коэффициенты линии сечения
    kx = x2 - x1;
    ky = y2 - y1;
    kl = sqrt(kx^2 + ky^2);
    
    % Число точек пересечения линии сечения с линиями сетки
    K = max(round(abs(kx) / dx), round(abs(ky) / dy));
    
    % Подготавливаем массивы для графика в сечении
    xL = zeros(1, K);
    zL = zeros(1, K);
    dt = 1 / (K - 1);
    
    for k = 1:K
        % Координаты точки линии сечения
        t = dt * (k - 1);
        xt = x1 + kx * t;
        yt = y1 + ky * t;
        
        % Номера узлов сетки ближайших к точке линии
        [~, n] = min(abs(x - xt));
        [~, m] = min(abs(y - yt));
        
        % Заполняем массивы графика в сечении
        xL(k) = kl * t;
        zL(k) = z(n, m);
    end
end
