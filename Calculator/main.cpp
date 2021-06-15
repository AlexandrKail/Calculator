#include<iostream>

//#Пеоеводит символы в числа#
//#Принимает: массив данных, текущий указатель на последний символ пер. числа, кол. символов в переводимом числе# 
int charToInt(char* input,int i,int numb)
{
	int b{};
	for (int fac{1}; numb > 0; numb--, i--,fac*=10)
	{
		b += static_cast<int>(input[i] - (int)'0')*fac;

	}
	return b;
}

//#Получает значения от пользователя и переводет их в символы#
//#Принимает: массив для данных, размер массива#
void userInput(char* input, size_t size)
{
		int val{};
		char simb{};
		int i{1};
		input[0] = '!';
		std::cout << "Введите вырожение типа \"a#b#c=\" где \"#\" символы \"+,-,*,/\", а \"a,b,c\" десятичные числа:\n>> ";

		while(simb != '=')
		{

			std::cin >> val;
			i += sprintf_s(input + i,size-i, "%d", val);
			std::cin >> simb;
			input[i] = simb;
			i++;
		} 
}

//#Сжатие массива путём записи вычисленных значений#
//#Принимает: Массив с данными, размер массива, текущая поз. в массиве, результат вырожения,
//кол. символов лев. числа от ар. знака, кол. символов правого числа#
void compArray(char* input,size_t size,int i ,int result,int lnumb,int rnumb)
{
	int foo{};
	if (input[i + (rnumb+1)] == '=')
	{
		foo=sprintf_s(input + (i-lnumb), size - i, "%d", result);
		input[i-lnumb+foo] = '=';
	}
	else
	{
		char buf[256];
		int j{}, k{i};

		while(input[k + rnumb+1] != '=')
		{
			buf[j] = input[k+rnumb+1];
			j++;
			k++;
		}
		buf[j] = '=';
		j = 0;
		foo = sprintf_s(input + (i - lnumb), size - i, "%d", result);
		while (buf[j] != '=')
		{
			input[i-lnumb+foo] = buf[j];
			j++;
			i++;
		}
		input[i-lnumb+foo] = '=';
	}

}

//#Вычесляет колличество символов числа, до арифмитического знака или после#
//#Принимает: массив с данными, текущая позиция в массиве, флаг направления  true - 
//в право(число находящаяся с право от ар. знака), false - влево.#
int numbSize(char* input, int i,bool direction)
{
	int numb{};
	if (direction != true)
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

//#Вычесления значений вырожения# 
//#Принимает: массив преобразованных данных в символы, размер массива#
int compute(char* input,size_t size)			
{
	int result{};
	{	
//processing * and /
		int i{}, a{}, b{};
		int lnumb{}, rnumb{};
		while (input[i] != '=')
		{
			if (input[i] == '*' || input[i] == '/')
			{
				if (input[i] == '*')
				{

					lnumb = numbSize(input, i, false);
					a = charToInt(input, i - 1, lnumb);
					rnumb = numbSize(input, i, true);
					b = charToInt(input, i + rnumb, rnumb);

					result = a * b;
					compArray(input, size, i, result, lnumb, rnumb);
				}
				else
				{
					lnumb = numbSize(input, i, false);
					a = charToInt(input, i - 1, lnumb);
					rnumb = numbSize(input, i, true);
					b = charToInt(input, i + rnumb, rnumb);

					result = a / b;
					compArray(input, size, i, result, lnumb, rnumb);
				}

				i = 0;		//Снова ищем знак * или /
			}
			i++;
		}
	//Processing + and -
		i = 0;
		while (input[i] != '=')
		{
			if (input[i] == '+' || input[i] == '-')
			{
				if (input[i] == '+')
				{
					lnumb = numbSize(input, i, false);
					a = charToInt(input, i - 1, lnumb);
					rnumb = numbSize(input, i, true);
					b = charToInt(input, i + rnumb, rnumb);

					result = a + b;
					compArray(input, size, i, result, lnumb, rnumb);
				}
				else
				{
					lnumb = numbSize(input, i, false);
					a = charToInt(input, i - 1, lnumb);
					rnumb = numbSize(input, i, true);
					b = charToInt(input, i + rnumb, rnumb);

					result = a - b;
					compArray(input, size, i, result, lnumb, rnumb);
				}

				i = 0;			//Снова ищем знак + или -
			}
			i++;
		}
	}
	int numb{};
	numb = numbSize(input, 0, true);
	result = charToInt(input,numb,numb);
	return result;

}

int main()
{
	setlocale(0, "ru_RU.utf8");
	const size_t size = 256;
	char input[size]{};
	userInput(input,size);
	int result{};
	result = compute(input,size);
	std::cout << "Результат = " << result << '\n';
}