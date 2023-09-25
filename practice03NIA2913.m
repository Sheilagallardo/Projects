clear
clc
syms x
format long
 
t = 20+3*9+2*1+3; %NIA: 100472913 --> x1=9, x2=1, x3=3

for i=1:12
    n = 2^i;
    %1º method --> from matlab
    fun = @(x) abs(sin(t.*x)./sqrt(x));
    q = integral(@(x) fun(x),1/(n+1),1);

    fprintf('\nFor n=%d:\nIntegral from matlab = %d\n',n,q);

    %2º method --> splines
    %Equidistance nodes:
    r(1) = 1/(n+1); %r0 = 1/(n+1)
    req = 1-1/(n+1); %to make the equidistance nodes
    req = req/n;

    %Linear system to solve to get the polynomials
    ls = zeros(4*n);
    sol = zeros(4*n,1);

    for j=1:n 
        r(j+1) = r(j) + req; %The last node is 1 --> rn = 1

        %Sk(Xk)
        ls(j,4*(j-1)+1) = 1;
        ls(j,4*(j-1)+2) = r(j);
        ls(j,4*(j-1)+3) = r(j)^2;
        ls(j,4*j) = r(j)^3;
        sol(j) = fun(r(j));
        
        %Sk(Xk+1)
        ls(j+n,4*(j-1)+1) = 1;
        ls(j+n,4*(j-1)+2) = r(j+1);
        ls(j+n,4*(j-1)+3) = r(j+1)^2;
        ls(j+n,4*j) = r(j+1)^3;
        sol(j+n) = fun(r(j+1));

        if j>1
            %first derivative
            ls(j+2*n-1,4*(j-2)+2)=1;
            ls(j+2*n-1,4*(j-2)+3)=r(j)*2;
            ls(j+2*n-1,4*(j-2)+4)=3*r(j)^2;
            ls(j+2*n-1,4*(j-2)+6)=-1;
            ls(j+2*n-1,4*(j-2)+7)=-r(j)*2;
            ls(j+2*n-1,4*(j-2)+8)=-3*r(j)^2;

            %second derivative
            ls(j+3*n-2,4*(j-2)+3)=2;
            ls(j+3*n-2,4*(j-2)+4)=6*r(j);
            ls(j+3*n-2,4*(j-2)+7)=-2;
            ls(j+3*n-2,4*(j-2)+8)=-6*r(j);
        end

    end
        %S0'(X0) = 0
        ls(4*n-1,2) = 1;
        ls(4*n-1,3) = 2*r(1);
        ls(4*n-1,4) = 3*(r(1)^2);
        %Sn'(Xn) = 0 
        ls(4*n,4*n-2) = 1;
        ls(4*n,4*n-1) = 2*r(n);
        ls(4*n,4*n) = 3*(r(n)^2);
    
        X = ls\sol;

        %Integrate
        q2 = 0;
        for j=1:n-1
        q2 = q2 + X((j-1)*4+1)*r(j+1) + X((j-1)*4+2)*(r(j+1)^2)*(1/2) + X((j-1)*4+3)*(r(j+1)^3)*(1/3) + X(j*4)*(r(j+1)^4)*(1/4) - (X((j-1)*4+1)*r(j) + X((j-1)*4+2)*(r(j)^2)*(1/2) + X((j-1)*4+3)*(r(j)^3)*(1/3) + X(j*4)*(r(j)^4)*(1/4));
        end

    fprintf('Integral from splines = %d\n',q2);

    %errors (absolute and relative)
    eabs2 = abs(q-q2);
    erel2 = eabs2/q;

    fprintf('\tAbsolute error = %d\n\tReletive error = %d\n',eabs2,erel2);

    
    if i<=5
    %3º method --> Hermite interpolation
        %r are the nodes (the x) here too

    deriv = @(x) (sin(t*x)*abs(sqrt(x))*(2*t*x*cos(t*x)-sin(t*x)))/(2*x^2*abs(sin(t*x)));

    z = zeros(2*(n+1));

    for j=1:n+1
        y(j) = fun(r(j));
        dy(j) = deriv(r(j));

        z(2*j-1,1) = y(j);
        z(2*j,1) = y(j);
        z(2*j,2) = dy(j);

    end
    
    %compute the piramid

    for j=2:n*2+1
        c=0;
        for k=j+1:2:2*(n+1)
            c=c+1;
            z(k,j) = (z(k,j-1)-z(k-1,j-1))/(r(ceil(k/2))-r(c));
            z(k,j+1) = (z(k,j)-z(k-1,j))/(r(ceil(k/2))-r(c));
        end
    end

    %compute the polynomial and the integrakl with it
    q3 = z(1,1)*1-z(1,1)*(1/(n+1));
    polh = 1;
    for j=1:2*n+1
        polh = polh*(x-r(ceil(j/2)));
        p = int(z(j+1,j+1)*polh,1/(n+1),1);
        q3 = q3 + p;
    end
    
    fprintf('Integral from Hermite = %d\n', double(q3))

    %errors (absolute and relative)
    eabs3 = abs(q-q3);
    erel3 = eabs3/q;

    fprintf('\tAbsolute error = %d\n\tReletive error = %d\n',double(eabs3),double(erel3));

    end

end

fprintf(['\n\nConclusion: With the splines interpolation method we can see that\n' ...
    'when we have more nodes (n is bigger) we have a better aproximation to\n' ...
    'the real integral value. With the Hermite interpolation method we can\n' ...
    'see the oposite, it starts better than the splines one but the Hermite\n' ...
    'method get worst with a bigger number of nodes (bigger n).\n' ...
    'For this purpose (stimate the value of an integral when n is bigger),\n' ...
    'I think that the splines method works better.'])
