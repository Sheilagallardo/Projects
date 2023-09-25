


clear
clc
format long

x = input('Choose an x value between -5 and 5: ');
y = input('Choose an y value between -5 and 5: ');

x1 = 0;
y1 = 0;

f = 2*x^(2)-1.05*x^(4)+((x^(6))/(6))+x*y+y^(2);

fx = 4*x - 4.2*x^3 + x^5 + y;
fy = x + 2*y;

vect = [x; y];
vect1 = [x1; y1];

vect1 = vect - (1/(2*(4 - 12.6*x^2 + 5*x^4)-1))*[2, -1; -1, 4 - 12.6*x^2 + 5*x^4] * [fx; fy];
contador = 0;

%Newton-Rampson

while (abs(vect(1) - vect1(1)) > 10^(-6)/2) && (abs(vect(2) - vect1(2)) > 10^(-6)/2) && contador<12
    vect(1) = vect1(1);
    vect(2) = vect1(2);

    fx = 4*vect(1) - 4.2*vect(1)^3 + vect(1)^5 + vect(2);
    fy = vect(1) + 2*vect(2);

    vect1 = vect - (1/(2*(4 - 12.6*vect(1)^2 + 5*vect(1)^4)-1))*[2, -1; -1, 4 - 12.6*vect(1)^2 + 5*vect(1)^4] * [fx; fy];
    contador = contador +1;
end

if contador <12 
    fprintf('For the chosen values the function converges to (%d,%d)\n\n', vect1(1),vect1(2))
else
    fprintf('For the chosen values the function does not converge\n\n')
end

z=[];
c1=[];
c2=[];
z2=[];
for x = -5:0.1:5
    nuevaFila = [];
    nuevaFila2 = [];
    nuevaFila3 = [];
    nuevaFila4 = [];

    for y = -5:0.1:5
        
        Jacobian = [4 - 12.6*x^2 + 5*x^4, 1; 1, 2];
        f = 2*x.^(2)-1.05*x.^(4)+((x.^(6))/(6))+x.*y+y.^(2);
        nuevaFila(end+1)=log(f);
        nuevaFila4(end+1)=log(cond(Jacobian));

        fx = 4*x - 4.2*x^3 + x^5 + y;
        fy = x + 2*y;
        
        vect = [x; y];
        vect1 = [x1; y1];
        
        vect1 = vect - (1/(2*(4 - 12.6*x^2 + 5*x^4)-1))*[2, -1; -1, 4 - 12.6*x^2 + 5*x^4] * [fx; fy];

        contador = 0;
        
        while ((abs(vect(1) - vect1(1)) > 10^(-6)/2) && (abs(vect(2) - vect1(2)) > 10^(-6)/2)) && contador<12
            vect(1) = vect1(1);
            vect(2) = vect1(2);
        
            fx = 4*vect(1) - 4.2*vect(1)^3 + vect(1)^5 + vect(2);
            fy = vect(1) + 2*vect(2);
        
            vect1 = vect - (1/(2*(4 - 12.6*vect(1)^2 + 5*vect(1)^4)-1))*[2, -1; -1, 4 - 12.6*vect(1)^2 + 5*vect(1)^4] * [fx; fy];
            contador = contador +1;
        end

        if round(vect1(1),5)==0 && round(vect1(2),5)==0
            nuevaFila2(end+1)=1;
        elseif contador == 12;
            nuevaFila2(end+1)=3;
        else
            nuevaFila2(end+1)=2;
        end
       
        nuevaFila3(end+1)=contador;

    end
    z=[z;nuevaFila];
    c1=[c1;nuevaFila2]; 
    c2=[c2;nuevaFila3];
    z2=[z2;nuevaFila4];
end

fig1 = figure;
surf((-5:0.1:5),(-5:0.1:5),z, c1)
hold on
title('Figure 1: Function according to convergence')
colorbar
fprintf('FOR FIGURE 1:\nColor for 1: converges to the global minimum\nColor for 2: converges to another point\nColor for 3: does not converge\n\n')
hold off
flig2 = figure;
surf((-5:0.1:5),(-5:0.1:5),z, c2)
hold on
title('Figure 2: Function according to iterations')
colorbar
hold off
fig3 = figure;
surf((-5:0.1:5),(-5:0.1:5),z2)
hold on
title('Figure 3: Function according to the condition number')
hold off


%Questions
fprintf(['Observation: we think that the process is ill-conditioned in general\n' ...
    'because the most part of the values give a condition number greater than 1.\n' ...
    'Moreover, when the values of x get closer to 0 (because the jacobian matrix\n' ...
    'only depends on x) the process gets more well-conditioned, except for the\n' ...
    'points near the points where the jacobian does not have an inverse (which\n' ...
    'are the local maximun of the figure 3).\n\n'])

fprintf(['Question 1:\nThe point returns fast to the square because the function increases\n' ...
    'very fast outside the square, then it is very easy for the point to return\n' ...
    'to the square using very few iterations of the Newton-Raphson method.\n\n'])

fprintf(['Question 2:\nWe have chosen to stop before reaching 12 iterations because we have\n' ...
    'seen that with 11 iterations every point converges for the interval we have chosen\n' ...
    '((-5:0.1:5),(-5:0.1:5)).\n' ...
    'There are also points that never converge, those where the jacobian does not have an\n' ...
    'inverse (when 10x^4-25.2x^2+7=0), but those points are not included in our interval with\n' ...
    'the step of 0.1 we are implementing.'])