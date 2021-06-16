#include<iostream>

//#Пеоеводит символы в числа#
//#Принимает: массив данных, текущий указатель на последний символ пер. числа, кол. символов в переводимом числе# 
int charToInt(std::string &input,int i,int numb)
{
	int b{};
	for (int fac{1}; numb > 0; numb--, i--,fac*=10)
	{
		b += static_cast<int>(input[i] - (int)'0')*fac;

	}
	return b;
}


//#Вычесляет колличество символов числа, до арифмитического знака или после#
//#Принимает: массив с данными, текущая позиция в массиве, флаг направления  true - 
//в право(число находящаяся с право от ар. знака), false - влево.#
int numbSize(std::string &input, int i,bool direction)
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

void copy(std::string& input,int i , int lnumb ,char* buftmp)
{
	int j{};
	while (buftmp[j] != '\0')
	{
		input[i - lnumb] = buftmp[j];
		j++;
		i++;
	}
	input[i - lnumb] = '=';
	input[i - lnumb+1] = '\0';
}


//#Сжатие массива путём записи вычисленных значений#
//#Принимает: Массив с данными, размер массива, текущая поз. в массиве, результат вырожения,
//кол. символов лев. числа от ар. знака, кол. символов правого числа#
void compArray(std::string& input, int i, int result, int lnumb, int rnumb)
{
	int foo{};
	char buftmp[64];
	if (input[i + (rnumb + 1)] == '=')
	{
		foo= sprintf_s(buftmp, sizeof(buftmp) - i, "%d", result);
		copy(input,i,lnumb,buftmp);
//		input[i - lnumb] += *buftmp;
//		foo = sprintf_s(input + (i - lnumb), sizeof(input) - i, "%d", result);
	}
	else
	{
		char buf[256];
		int j{}, k{ i };

		while (input[k + rnumb + 1] != '=')
		{
			buf[j] = input[k + rnumb + 1];
			j++;
			k++;
		}
		buf[j] = '=';
		buf[j + 1] = '\0';
		j = 0;
//		foo = sprintf_s(input + (i - lnumb), size - i, "%d", result);
		foo = sprintf_s(buftmp, sizeof(buftmp) - i, "%d", result);
		copy(input, i, lnumb, buftmp);

		while (buf[j] != '=')
		{

			input[i - lnumb + foo] = buf[j];
			j++;
			i++;
		}
		input[i - lnumb + foo] = '=';
		input[i - lnumb + foo] = '\0';
	}

}

//#Вычесления значений вырожения# 
//#Принимает: массив преобразованных данных в символы, размер массива#
int compute(std::string& input)			
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
					compArray(input, i, result, lnumb, rnumb);
				}
				else
				{
					lnumb = numbSize(input, i, false);
					a = charToInt(input, i - 1, lnumb);
					rnumb = numbSize(input, i, true);
					b = charToInt(input, i + rnumb, rnumb);

					result = a / b;
					compArray(input, i, result, lnumb, rnumb);
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
					compArray(input, i, result, lnumb, rnumb);
				}
				else
				{
					lnumb = numbSize(input, i, false);
					a = charToInt(input, i - 1, lnumb);
					rnumb = numbSize(input, i, true);
					b = charToInt(input, i + rnumb, rnumb);

					result = a - b;
					compArray(input, i, result, lnumb, rnumb);
				}

				i = 0;			//Снова ищем знак + или
			}
			i++;
		}
	}
	int numb{};
	numb = numbSize(input, 0, true);
	result = charToInt(input,numb,numb);
	return result;

}

//#Получает значения от пользователя и переводет их в символы#
//#Принимает: массив для данных, размер массива#
void userInput(std::string &input)
{
	std::string str;
	std::cout << "Введите вырожение типа \"a#b#c=\" где \"#\" символы \"+,-,*,/\", а \"a,b,c\" десятичные числа:\n>> ";	//	std::cout << "Введите число: ";
	std::cin >>str;
	input = '!';
	input += str;
}

int main()
{
	setlocale(0, "ru_RU.utf8");
	std::string input;
	userInput(input);
	int result{};
	result = compute(input);
	std::cout << "Результат = " << result << '\n';
}