%% Group 1
% Sheila Gallardo Redondo
% Christian Andrade
% Kendra Wong

clear all
format long

%% Problem 1

% Get Inputs
prompt1 = "3 digit mantissa: ";
mantissa = input(prompt1)/1000;
prompt2 = "exponent between -1 and 1: ";
exponent = input(prompt2);
prompt3 = "sign (1/-1): ";
sign = input(prompt3);

initialNum = mantissa * (10^exponent) * sign;

% Highest decimal number possible is 9.99, so highest exponent will be 3 b/c 2^3=8

% Decimal --> Binary
[binary, mantissaBinary, binExp] = decimal2binary(mantissa, exponent, sign);
% Binary --> Decimal
[decimalNum, decExp, mantissaDec] = binary2decimal(binary);

fprintf("\n\nThe number in binary is: "); fprintf('%#.12g', binary);
fprintf("\nMantissa: "); fprintf('%#.8g', mantissaBinary);
fprintf("\nExponent: " + binExp);
fprintf("\nSign: " + sign);

fprintf("\n\nThe number in decimal again is " + decimalNum);
fprintf("\nMantissa: " + mantissaDec);
fprintf("\nExponent: " + decExp);
fprintf("\nSign: " + sign);

% Calculate Errors
eAbs = abs(initialNum - decimalNum);
eRel = eAbs/abs(initialNum);

fprintf("\n\nThe absolute error is " + eAbs);
fprintf("\nThe relative error is " + eRel + "\n");

%% Problem 2

prompt4 = "\nIntroduce a value for k: ";
k = input(prompt4);
prompt5 = "Introduce a value for b bigger or equal than 1: ";
b = input(prompt5);
prompt6 = "Introduce a value for a bigger than b: ";
a = input(prompt6);

[sum0First, sum0Last, round1, round2, trunc] = s1(k, a, b);

fprintf("\nThe sum value adding first the first terms is "+ sum0First);
fprintf("\nThe sum value adding first the last terms is " + sum0Last);
fprintf("\n\nThe roundoff error bound when iterating forward is " + ...
    "(0, " + round1 + ")");
fprintf("\nThe roundoff error bound when iterating backward is " + ...
    "(0, " + round2 + ")");
fprintf("\nThe truncation error bound is (0, " + trunc + ")");    

    

%% Problem 2 part 2
% Graph
prompt7 = "\n\nIntroduce another value of a: ";
aGraph = input(prompt7);
[kOptimal, kOptimalExp, controundoff1, conttrunc1, controundoff2, conttrunc2] = kErrorPlot(aGraph);

fprintf("The optimal k value is " + kOptimal + ", or 2^" + kOptimalExp + "\n");
fprintf("This is because is the k with the least total error if we count the errors" + ...
    "\n iterating forward and backward.\n");
fprintf("\nThe total error is the sum of the greater bound " + ...
    "of each error." + "\nWith that we can calculate the contribution of each error " + ...
    "\nto the total, dividing them by the total error. It gives us a number between " + ...
    "\n0 and 1.");
fprintf("\n\nThe contribution of the roundoff error when iterating forward " + ...
    "is " + controundoff1);
fprintf("\nThe contribution of the truncation error when iterating forward " + ...
    "is " + conttrunc1 + "\n");
fprintf("\nThe contribution of the roundoff error when iterating backward " + ...
    "is " + controundoff2);
fprintf("\nThe contribution of the truncation error when iterating backward " + ...
    "is " + conttrunc2 + "\n");

%% 
%% Functions
function [binary, mantissaBinary, binExp] = decimal2binary(mantissa, exponent, sign)
    initialNum = mantissa * 10^exponent;
    initialExp = 3;
    binary = 0;
    numdigits = 0;
    num = initialNum;
    
    while numdigits < 8
        if num >= 2^initialExp
            num = num - 2^initialExp;
            binary = binary + 10^initialExp;
            numdigits = numdigits + 1;
        elseif binary ~= 0
            numdigits = numdigits + 1;
        end
        initialExp = initialExp - 1;
    end
    
    mantissaBinary = binary;
    binExp = 0;
    
    while mantissaBinary >= 1
        mantissaBinary = mantissaBinary / 10;
        binExp = binExp + 1;
    end
    
    while mantissaBinary < 0.1
        mantissaBinary = mantissaBinary * 10;
        binExp = binExp - 1;
    end

    binary = binary*sign;
end

function [decimalNum, decExp, nummantissa] = binary2decimal(binary)
    exp= 3;
    decimalNum = 0;
    x = binary;
    
    while exp > -10^6
        if abs(x) >= 10^exp
            decimalNum = decimalNum + 2^exp;
            x = x - 10^exp;
        end
        exp = exp - 1;
    end

    decExp = 0;
    nummantissa = decimalNum;
    while nummantissa >= 1
        nummantissa = nummantissa / 10;
        decExp = decExp + 1;
    end
    
    while nummantissa < 0.1
        nummantissa = nummantissa * 10;
        decExp = decExp - 1;
    end

    % We round the number to a mantissa with 3 digits since it has to have
    % the same conditions than the first one

    nummantissa = round(nummantissa * 1000)/1000;
    decimalNum = nummantissa * (10^decExp) * sign(binary);
end

function [sum0First, sum0Last, roundoffFirst, roundoffLast, truncation] = s1(k,a,b)
    sum1First = 0;
    sum1Last = 0;
    roundoffFirst = 0;
    roundoffLast = 0;

% This is the highest presicion since we can not compute the sum with a
% lower number of floating-point operations

    for n = 1:k
        nextSum = 1/((a*n+b)*(a*n+b+1));
        sum1First = sum1First + nextSum;
        % calc roundoff error, multiply by eps, make list 
        roundoffFirst = roundoffFirst + max(sum1First,nextSum) * eps;
    end

    for n = k:-1:1
        nextSum = 1/((a*n+b)*(a*n+b+1));
        sum1Last = sum1Last + nextSum;
        roundoffLast = roundoffLast + max(sum1Last,nextSum) * eps;
    end

    sum0First = sum1First + 1/(a*(a*k+b+1));
    sum0Last = sum1Last + 1/(a*(a*k+b+1));

% Calculate the roundoff error by adding 1/2 of eps per each floating-point
% operation

    truncation = 1/(a*k*(k + 1));

end

function [kOptimal, kOptimalExp, controundoff1, conttrunc1, controundoff2, conttrunc2] = kErrorPlot(a)
    kList = [2^1,2^2,2^3,2^4,2^5,2^6,2^7,2^8,2^9,2^10,2^11,2^12,2^13,2^14,2^15,2^16];
    fig1 = figure;

    for b = 1:a-1
        round1List = [];
        truncErrorList = [];
        errorList1 = [];
        for i = 1:16
            k = 2^i;
            [~, ~, round1, ~, trunc] = s1(k,a,b);
            round1List(i) = round1;
            truncErrorList(i) = trunc;
            totalError1 = round1 + trunc;
            errorList1(i) = totalError1;
        end

        loglog(kList,errorList1)
        hold on
    end

    xlabel('k'); ylabel('Total Error Forward')
    hold off

    fig2 = figure;

    for b = 1:a-1
        round2List = [];
        truncErrorList = [];
        errorList2 = [];
        for i = 1:16
            k = 2^i;
            [~, ~, ~, round2, trunc] = s1(k,a,b);
            round2List(i) = round2;
            truncErrorList(i) = trunc;
            totalError2 = round2 + trunc;
            errorList2(i) = totalError2;
        end
        
        loglog(kList,errorList2)
         hold on
       
    end
    xlabel('k'); ylabel('Total Error Backward')
    hold off


    minError1 = min(errorList1);
    minError2 = min(errorList2);
    if minError1 < minError2
        kOptimalExp = find(errorList1 == minError1);
    else
        kOptimalExp = find(errorList2 == minError2);
    end
    kOptimal = 2^kOptimalExp;


    [~, ~, round1, round2, trunc] = s1(kOptimal,a,b);

    % total error
    
    totale1 = round1 + trunc;
    totale2 = round2 + trunc;
    
    controundoff1 = round1/totale1;
    conttrunc1 = trunc/totale1;

    controundoff2 = round2/totale2;
    conttrunc2 = trunc/totale2;
    
end



