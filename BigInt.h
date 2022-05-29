#include <bits/stdc++.h>
using namespace std;

class BigInt
{
private:
    string x;

    string ADD(string Num1, string Num2)
    {

        if (Num1[0] == '-' && Num2[0] != '-') // first number is -ve
        {
            string N1 = Num1.substr(1);
            return SUBTRACT(Num2, N1);
        }

        if (Num1[0] != '-' && Num2[0] == '-') // second number is -ve
        {
            string N2 = Num2.substr(1);
            return SUBTRACT(Num1, N2);
        }

        if (Num1[0] == '-' && Num2[0] == '-') // both -ve
        {
            string N1 = Num1.substr(1);
            string N2 = Num2.substr(1);
            string ANS = "-";
            ANS += ADD(N1, N2);
            return ANS;
        }

        if (Num1.size() < Num2.size())
            swap(Num1, Num2);

        Num1 = "0" + Num1;

        int diff = Num1.size() - Num2.size();

        string temp(diff, '0');

        Num2 = temp + Num2;

        for (int i = Num1.size() - 1; i >= 0; i--)
        {
            int add = (Num1[i] - '0') + (Num2[i] - '0');
            int Rem = add % 10;
            Num1[i] = Rem + '0';
            Num1[i - 1] += (add / 10);
        }

        if (Num1[0] == '0')
            Num1 = Num1.erase(0, 1);

        return Num1;
    }

    string MULTIPLY(string num1, string num2)
    {

        int n = num1.size(), m = num2.size();
        string sum(n + m, '0');

        if (num1[0] == '-' && num2[0] == '-') // both -ve
        {
            string N1 = num1.substr(1);
            string N2 = num2.substr(1);
            return MULTIPLY(N1, N2);
        }

        if (num1[0] == '-' && num2[0] != '-') // first -ve
        {
            string N1 = num1.substr(1);
            string ANS = "-";
            ANS += MULTIPLY(N1, num2);
            return ANS;
        }

        if (num1[0] != '-' && num2[0] == '-') // second -ve
        {
            string N2 = num2.substr(1);
            string ANS = "-";
            ANS += MULTIPLY(num1, N2);
            return ANS;
        }

        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                int value = (num1[i] - '0') * (num2[j] - '0') + (sum[i + j + 1] - '0');
                sum[i + j + 1] = value % 10 + '0';
                sum[i + j] += value / 10;
            }
        }

        reverse(sum.begin(), sum.end());

        int i = sum.size() - 1;
        while (i >= 0 && sum[i] == '0')
        {
            sum.pop_back();
            i--;
        }

        if (sum.size() == 0)
            return "0";
        else
        {
            reverse(sum.begin(), sum.end());
            return sum;
        }
    }

    string SUBTRACT(string num1, string num2)
    {
        bool flag = false;

        if (num1[0] == '-' && num2[0] != '-')
        { // only first is -ve
            string N1 = num1.substr(1);
            string ANS = "-";
            ANS += ADD(N1, num2);
            return ANS;
        }

        if (num1[0] != '-' && num2[0] == '-') // only second is -ve
        {
            string N2 = num2.substr(1);
            return ADD(num1, N2);
        }

        if (num1[0] == '-' && num2[0] == '-') // both -ve
        {
            // num2 becomes +ve ;
            string N2 = num2.substr(1);
            string N1 = num1.substr(1);
            return SUBTRACT(N2, N1);
        }

        if (num1[0] != '-' && num2[0] != '-')
        { // BOTH +ve
            if (num1.size() != num2.size())
            {

                if (num1.size() < num2.size())
                {
                    swap(num1, num2);
                    flag = true;
                }

                int diff = num1.size() - num2.size();
                string m = "";
                for (int i = 0; i < diff; i++)
                    m += "0";

                num2 = m + num2;
            }
            if (num1.size() == num2.size())
            {
                if (num1 < num2)
                {
                    swap(num1, num2);
                    flag = true;
                }
            }
        }

        for (int i = num1.size() - 1; i >= 0; i--)
        {
            int temp = (num1[i] - '0') - (num2[i] - '0');
            if (temp >= 0) //+ve
            {
                num1[i] = temp + '0';
            }
            else
            { //-ve

                //find first non zero in num1 so that I can get carry
                int f = i - 1;
                while (num1[f] == '0')
                {
                    f--;
                }

                num1[f] = ((num1[f] - '0') - 1) + '0';
                f++;
                while (f != i)
                {
                    num1[f] = '9';
                    f++;
                }

                int NOW = (num1[f] - '0') + 10;
                int rem = NOW - (num2[i] - '0');
                num1[i] = rem + '0';
            }
        }

        // removing extra zeroes from front
        string ANS = "";
        if (flag) // -ve
        {
            ANS = "-";
        }
        reverse(num1.begin(), num1.end());
        int i = num1.size() - 1;
        while (num1[i] == '0')
        {
            num1.pop_back();
            i--;
        }
        reverse(num1.begin(), num1.end());
        if (num1.size() == 0)
        {
            return "0";
        }
        else
        {
            ANS += num1;
        }

        return ANS;
    }

    string DIVIDE(string num, string den)
    {
        if (den == "0")
            return "NOT DEFINED";

        if (num[0] == '-' && den[0] == '-')
        {
            num = num.substr(1);
            den = den.substr(1);
            return DIVIDE(num, den);
        }

        if (num[0] == '-' && den[0] != '-')
        {
            num = num.substr(1);

            if (num.size() < den.size())
                return "0";

            if (num.size() == den.size())
            {
                if (den > num)
                    return "0";
            }

            string Ans = "-";
            Ans += DIVIDE(num, den);
            return Ans;
        }

        if (num[0] != '-' && den[0] == '-')
        {
            den = den.substr(1);

            if (num.size() < den.size())
                return "0";

            if (num.size() == den.size())
            {
                if (den > num)
                    return "0";
            }

            string Ans = "-";
            Ans += DIVIDE(num, den);
            return Ans;
        }

        if (num.size() < den.size())
            return "0";

        if (num.size() == den.size())
        {
            if (den > num)
                return "0";
        }

        string d = den;

        int count = 0;

        while (d.size() < num.size())
        {
            d.push_back('0');
            count++;
        }

        if (d > num)
        {
            d.pop_back();
            count--;
        }

        int divisor = 1;
        string str = d;
        while (true)
        {
            if (num.size() < d.size())
                break;

            if (num.size() == d.size())
            {
                if (d > num)
                    break;
            }

            d = ADD(d, str);
            divisor++;
        }

        divisor--;
        d = SUBTRACT(d, str);

        num = SUBTRACT(num, d);

        string Ans = to_string(divisor);
        while (count--)
        {
            Ans.push_back('0');
        }

        Ans = ADD(Ans, DIVIDE(num, den));

        return Ans;
    }

    string MOD(string num, string den)
    {
        if (num.size() < den.size())
            return num;

        if (num.size() == den.size())
        {
            if (den > num)
                return num;
        }

        string d = den;

        int count = 0;

        while (d.size() < num.size())
        {
            d.push_back('0');
            count++;
        }

        if (d > num)
        {
            d.pop_back();
            count--;
        }

        int divisor = 1;
        string str = d;
        while (true)
        {
            if (num.size() < d.size())
                break;

            if (num.size() == d.size())
            {
                if (d > num)
                    break;
            }

            d = ADD(d, str);
            divisor++;
        }

        divisor--;
        d = SUBTRACT(d, str);

        num = SUBTRACT(num, d);

        string Ans = MOD(num, den);

        return Ans;
    }

    string fact(string str)
    {
        if (str == "0" || str == "1")
            return "1";

        string two = SUBTRACT(str, "1");

        return MULTIPLY(str, fact(two));
    }

public:
    friend istream &operator>>(istream &in, BigInt &obj);
    friend ostream &operator<<(ostream &out, const BigInt &obj);

    // CONSTRUCTOR
    BigInt()
    {
        x = "0";
    }

    // ADD OPERATOR OVERLOADED

    BigInt &operator+(BigInt &obj)
    {
        BigInt SUM;

        string Num1 = x;
        string Num2 = obj.x;
        SUM.x = ADD(Num1, Num2);

        return SUM;
    }

    // MULTIPLY OPERATOR OVERLOADED

    BigInt &operator*(BigInt &obj)
    {
        BigInt MUL;

        string num1 = x;
        string num2 = obj.x;

        MUL.x = MULTIPLY(num1, num2);
        return MUL;
    }

    // SUBTRACT OPERATOR OVERLOADED

    BigInt &operator-(BigInt &obj)
    {
        BigInt SUB;
        string num1 = x;
        string num2 = obj.x;

        SUB.x = SUBTRACT(num1, num2);
        return SUB;
    }

    // DIVIDE OPERATOR OVERLOADED

    BigInt &operator/(BigInt &obj)
    {
        BigInt DIV;
        string num1 = x;
        string num2 = obj.x;

        DIV.x = DIVIDE(num1, num2);
        return DIV;
    }

    // MOD OPERATOR OVERLOADED

    BigInt &operator%(BigInt &obj)
    {
        BigInt M;
        string num1 = x;
        string num2 = obj.x;
        M.x = MOD(num1, num2);
        return M;
    }

    // += OPERATOR OVERLOADED

    BigInt &operator+=(BigInt &obj)
    {
        BigInt SUM;
        string Num1 = x;
        string Num2 = obj.x;
        x = ADD(Num1, Num2);
        SUM.x = x;
        return SUM;
    }

    // -= OPERATOR OVERLOADED

    BigInt &operator-=(BigInt &obj)
    {
        BigInt SUB;
        string Num1 = x;
        string Num2 = obj.x;
        x = SUBTRACT(Num1, Num2);
        SUB.x = x;
        return SUB;
    }

    // *= OPERATOR OVERLOADED

    BigInt &operator*=(BigInt &obj)
    {
        BigInt MUL;
        string Num1 = x;
        string Num2 = obj.x;
        x = MULTIPLY(Num1, Num2);
        MUL.x = x;
        return MUL;
    }

    // /= OPERATOR OVERLOADED

    BigInt &operator/=(BigInt &obj)
    {
        BigInt DIV;
        string num1 = x;
        string num2 = obj.x;
        x = DIVIDE(num1, num2);
        DIV.x = x;
        return DIV;
    }

    // %= OPERATOR OVERLOADED

    BigInt &operator%=(BigInt &obj)
    {
        BigInt M;
        string num1 = x;
        string num2 = obj.x;
        x = MOD(num1, num2);
        M.x = x;
        return M;
    }

    // Prefix ++
    BigInt &operator++()
    {
        BigInt SUM;
        x = ADD(x, "1");
        SUM.x = x;
        return SUM;
    }

    // Postfix ++
    BigInt &operator++(int)
    {
        BigInt SUM;
        string old = x;
        operator++();
        SUM.x = old;
        return SUM;
    }

    // Prefix --
    BigInt &operator--()
    {
        BigInt SUB;
        x = SUBTRACT(x, "1");
        SUB.x = x;
        return SUB;
    }

    // Postfix --
    BigInt &operator--(int)
    {
        BigInt SUB;
        string old = x;
        operator--();
        SUB.x = old;
        return SUB;
    }

    BigInt fact()
    {
        BigInt str;
        str.x = fact(x);

        return str;
    }

    // >

    bool operator>(BigInt &obj)
    {
        string num1 = x;
        string num2 = obj.x;

        if (num1.size() > num2.size())
            return true;

        if (num1.size() < num2.size())
            return false;

        return num1 > num2;
    }

    // <

    bool operator<(BigInt &obj)
    {
        string num1 = x;
        string num2 = obj.x;

        if (num1.size() < num2.size())
            return true;

        if (num1.size() > num2.size())
            return false;

        return num1 < num2;
    }

    // >=

    bool operator>=(BigInt &obj)
    {
        string num1 = x;
        string num2 = obj.x;

        if (num1.size() > num2.size())
            return true;

        if (num1.size() < num2.size())
            return false;

        return num1 >= num2;
    }

    // <=
    bool operator<=(BigInt &obj)
    {
        string num1 = x;
        string num2 = obj.x;

        if (num1.size() < num2.size())
            return true;

        if (num1.size() > num2.size())
            return false;

        return num1 <= num2;
    }
};

istream &operator>>(istream &in, BigInt &obj)
{
    in >> obj.x;
    return in;
}

ostream &operator<<(ostream &out, const BigInt &obj)
{
    out << obj.x;
    return out;
}
