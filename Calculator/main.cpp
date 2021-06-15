#include<iostream>

int charToInt(char* input,int i,int numb)
{
	int b{};
	for (int fac{1}; numb > 0; numb--, i--,fac*=10)
	{
		b += static_cast<int>(input[i] - (int)'0')*fac;

	}
	return b;
}

void userInput(char* input, size_t size)
{
	using namespace std;
	{
		int a{};
		char simb{};
		int i{1};
		input[0] = '!';
		cout << "Введите вырожение типа \"a#b#c=\" где # = +,-,*,/: ";
		do
		{

			cin >> a;
			i += sprintf_s(input + i,size-i, "%d", a);
//			cout << "Введите символ(+,-,*,/): ";
			cin >> simb;
			input[i] = simb;
			i++;
		} while (simb != '=');
	}
}

void compArray(char* input,size_t size,int i ,int result,int numb1,int numb2)
{
	int foo{};
	if (input[i + (numb2+1)] == '=')
	{
		foo=sprintf_s(input + (i-numb1), size - i, "%d", result);
//		input[i - 1] = intToChar(result);
		input[i-numb1+foo] = '=';
	}
	else
	{
		char buf[256];
		int j{}, k{i};

		while(input[k + numb2+1] != '=')
		{
			buf[j] = input[k+numb2+1];
			j++;
			k++;
		}
		buf[j] = '=';
		j = 0;
		foo = sprintf_s(input + (i - numb1), size - i, "%d", result);
		while (buf[j] != '=')
		{
			input[i-numb1+foo] = buf[j];
			j++;
			i++;
		}
		input[i-numb1+foo] = '=';
	}

}

int numbSize(char* input, int i,bool flag)
{
	int numb{};
	if (flag != true)
	{
		while (input[i - 1] != '+' && input[i - 1] != '-' && input[i - 1] != '*' && input[i - 1] != '/' && input[i - 1] != '=' && input[i-1] != '!')
		{
			numb++;
			i--;
		}
	}
	else
	{
		while (input[i + 1] != '+' && input[i + 1] != '-' && input[i + 1] != '*' && input[i + 1] != '/' && input[i + 1] != '=')
		{
			numb++;
			i++;
		}
	}
	return numb;
}

int compute(char* input,size_t size)
{
	int result{};
	{
		
		bool flag = true;

//processing * and /
		while (flag)
		{
			int a{}, b{}, i{};
			flag = false;
			while (input[i] != '=')
			{
				if (input[i] == '*' || input[i] == '/')
				{
					if (input[i] == '*')
					{
						int numb1{}, numb2{};
						numb1 = numbSize(input, i, false);
						a = charToInt(input, i - 1, numb1);
						numb2 = numbSize(input, i, true);
						b = charToInt(input, i + numb2, numb2);

						result = a * b;
						compArray(input, size, i, result, numb1, numb2);
						flag = true;
						break;;
					}
					else
					{
						int numb1{}, numb2{};
						numb1 = numbSize(input, i, false);
						a = charToInt(input, i - 1, numb1);
						numb2 = numbSize(input, i, true);
						b = charToInt(input, i + numb2, numb2);

						result = a / b;
						compArray(input, size, i, result, numb1, numb2);
						flag = true;
						break;
					}
				}
				i++;
			}
		}
		flag = true;
	//Processing + and -
		while (flag)
		{
			int a{}, b{}, i{};
			flag = false;
			while (input[i] != '=')
			{
				if (input[i] == '+' || input[i] == '-')
				{
					if (input[i] == '+')
					{
						int numb1{}, numb2{};
						numb1 = numbSize(input, i, false);
						a = charToInt(input, i - 1, numb1);
						numb2 = numbSize(input, i, true);
						b = charToInt(input, i + numb2, numb2);

						result = a + b;
						compArray(input, size, i, result, numb1, numb2);
						flag = true;
						break;
					}
					else
					{
						int numb1{}, numb2{};
						numb1 = numbSize(input, i, false);
						a = charToInt(input, i - 1, numb1);
						numb2 = numbSize(input, i, true);
						b = charToInt(input, i + numb2, numb2);

						result = a - b;
						compArray(input, size, i, result, numb1, numb2);
						flag = true;
						break;
					}
				}
				i++;
			}
		}
	}
	int numb{};
	numb = numbSize(input, 0, true);
	result = charToInt(input,numb,numb);
	return result;

}

int main()
{
	setlocale(0, "");
	const size_t size = 256;
	char input[size]{};
	
	userInput(input,size);
	int result{};
	result = compute(input,size);
	std::cout << "Результат = " << result << '\n';
}