#include<iostream>

int* minus = nullptr;

//#Пеоеводит символы в числа#
//#Принимает: массив данных, текущий указатель на последний символ пер. числа, кол. символов в переводимом числе# 
int charToInt(std::string &input,int i,int numb,int* minus)
{
	int b{};

	for (int fac{1}; numb > 0; numb--, i--,fac*=10)
	{
		b += static_cast<int>(input[i] - (int)'0')*fac;
	}

	if (*minus == 1)
		b = b - b * 2;

	*minus = 0;
	return b;
}


//#Вычесляет колличество символов числа, до арифмитического знака или после#
//#Принимает: массив с данными, текущая позиция в массиве, флаг направления  true - 
//в право(число находящаяся с право от ар. знака), false - влево.#
int numbSize(std::string &input, int i,bool direction)
{
	int numb{};

	if (input[1] == '-' && (input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/'))
	{
		i++;
	}


	if (direction != true)
	{
		while (input[i - 1] != '+' && input[i - 1] != '-' && input[i - 1] != '*' && input[i - 1] != '/' && input[i-1] != '!')
		{
			numb++;
			i--;
		}
	}
	else
	{
		while (input[i + 1] != '+' && input[i + 1] != '-' && input[i + 1] != '*' && input[i + 1] != '/' && input[i + 1] != '!')
		{
			numb++;
			i++;
		}
	}
	return numb;
}

void copy(std::string& input,int i , int lnumb ,char* buftmp)
{
	//if (*minus == 1)
	//	lnumb++;

	int j{};
	while (buftmp[j] != '\0')
	{
		input[i - lnumb] = buftmp[j];
		j++;
		i++;
	}
	//input[i - lnumb] = '\0';
}


//#Сжатие массива путём записи вычисленных значений#
//#Принимает: Массив с данными, размер массива, текущая поз. в массиве, результат вырожения,
//кол. символов лев. числа от ар. знака, кол. символов правого числа#
void compArray(std::string& input, int i, int result, int lnumb, int rnumb)
{
	int foo{};
	char buftmp[256]{};
	if (input[i + (rnumb + 1)] == '!')
	{
		
		foo= sprintf_s(buftmp, sizeof(buftmp) - i, "%d", result);
		copy(input,i,lnumb,buftmp);
		input[i - lnumb + foo] = '!';
		input[i - lnumb + foo+1] = '\0';

	}
	else
	{
		char buf[256]{};
		int j{}, k{ i };

		while (input[k + rnumb + 1] != '\0')
		{
			buf[j] = input[k + rnumb + 1];
			j++;
			k++;
		}
		buf[j] = '\0';
		j = 0;
		foo = sprintf_s(buftmp, sizeof(buftmp) - i, "%d", result);
		copy(input, i, lnumb, buftmp);

		while (buf[j] != '\0')
		{

			input[i - lnumb + foo] = buf[j];
			j++;
			i++;
		}
		input[i - lnumb + foo] = '\0';
	}

}

//#Вычесления значений вырожения# 
//#Принимает: массив преобразованных данных в символы, размер массива#
int compute(std::string& input)			
{
	int result{};
	int min = 0;
	minus = &min;
	{	
		int valL{}, valR{};
		int lnumb{}, rnumb{};
		int i{1};

		//processing * and /
		while (input[i] != '!')
		{
			if (input[1] == '-')
			{
				{
					i++;
					while (input[i] != '!')
					{
						if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
						{
							*minus = 1;
							goto next1;
						}
						i++;
					}
				}
				*minus = 1;
				break;
			}
next1:

			if (input[i] == '*' || input[i] == '/')
			{
				if (input[i] == '*')
				{

					lnumb = numbSize(input, i, false);
					valL = charToInt(input, i - 1, lnumb,minus);
					rnumb = numbSize(input, i, true);
					valR = charToInt(input, i + rnumb, rnumb,minus);

					result = valL * valR;
					compArray(input, i, result, lnumb, rnumb);
				}
				else
				{
					lnumb = numbSize(input, i, false);
					valL = charToInt(input, i - 1, lnumb,minus);
					rnumb = numbSize(input, i, true);
					valR = charToInt(input, i + rnumb, rnumb,minus);

					result = valL / valR;
					compArray(input, i, result, lnumb, rnumb);
				}

				i = 0;		//Снова ищем знак * или /
			}
			i++;
		}
	//Processing + and -
		i = 1;
		while (input[i] != '!')
		{
			if (input[1] == '-')
			{
					i++;
					while (input[i] != '!')
					{
						if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
						{
							*minus = 1;
							goto next2;
						}
						i++;
					}

				*minus = 1;
				break;
			}
next2:
			if (input[i] == '+' || input[i] == '-')
			{
				if (input[i] == '+')
				{
					lnumb = numbSize(input, i, false);
					valL = charToInt(input, i - 1, lnumb,minus);
					rnumb = numbSize(input, i, true);
					valR = charToInt(input, i + rnumb, rnumb,minus);

					result = valL + valR;
					compArray(input, i, result, lnumb, rnumb);
				}
				else
				{
					lnumb = numbSize(input, i, false);
					valL = charToInt(input, i - 1, lnumb,minus);
					rnumb = numbSize(input, i, true);
					valR = charToInt(input, i + rnumb, rnumb,minus);

					result = valL - valR;
					compArray(input, i, result, lnumb, rnumb);
				}

				i = 0;			//Снова ищем знак + или
			}
			i++;
		}
	}
	int numb{};
	numb = numbSize(input, 0, true);
	int i{};
	if (*minus == 1)
		i = 1;

	result = charToInt(input,numb+i,numb,minus);
	return result;

}

int correctInput(std::string const& str,int size)
{
	int i{};
	while (str[i] != '\0')
	{
		if ((int)str[i] >= (int)'0' && (int)str[i] <= (int)'9' || str[i] == '+' || str[i] == '-' ||
			str[i] == '*' || str[i] == '/')
		{
//Проверка на ар. знак в начале
			if (i == 0)
			{
				if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
				{
					return -1;
				}
			}

// Проверка на два знака подряд
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
			{
				if (str[i - 1] == '+' || str[i - 1] == '-' || str[i - 1] == '*' || str[i - 1] == '/')
				{
					return -1;
				}
			}

			if (str[size-1] == '+' || str[size-1] == '-' || str[size-1] == '*' || str[size-1] == '/')
			{
				return -1;
			}
			i++;
		}
		else
			return -1;
	}
	return 0;

}

//#Получает значения от пользователя и переводет их в символы#
//#Принимает: массив для данных, размер массива#
void userInput(std::string &input)
{
	std::string str;
	while (true)
	{
		std::cout << "Введите вырожение типа \"a#b#c=\" где \"#\" символы \"+,-,*,/\", а \"a,b,c\" десятичные числа:\n>> ";	//	std::cout << "Введите число: ";
		std::cin >> str;
		if (correctInput(str,str.size()) == 0)
			break;
		std::cout << "Неверный ввод!\n";
	}

	input = '!';
	input += str;
	int i;
	i = input.size();
	input += "!";
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