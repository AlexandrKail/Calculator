#include<iostream>
#include<cmath>

//Константы
const int PRECESSION = 10000000;
//Глобальные переменные
bool fNumb{};

struct FloatNumb
{
	int intPart;
	int decPart;
};

//#Разделяет целую и дробную часть вещественного числ
//#Принимает: структура в которую заносится результат, число которое предстоит разделить
void devideFloat(FloatNumb& obj, float val)
{
	float tmpVal{};
	obj.intPart = static_cast<int>(val);
	tmpVal = val - static_cast<float>(obj.intPart);
	obj.decPart = static_cast<int>(tmpVal * PRECESSION);

}

void intToChar(char* buf,int& i ,int val)
{
	while (true)
	{
		buf[i] = static_cast<char>(val % 10 + '0');
		++i;
		if ((val /= 10) == 0)
			break;
	}

}

void inversArr(char* buf, const int SZ)
{
	char tmp[256]{};
	for (int j{},i{SZ}; i >= 0; --i, j++)
		tmp[j] = buf[i];

	for (int j{}; j <= SZ; ++j)
		buf[j] = tmp[j];
}


void floatToChar(char* buf, float f_result)
{
	FloatNumb obj;
	devideFloat(obj, f_result);
	int i{};
	intToChar(buf, i, obj.decPart);
	buf[i] = '.';
	++i;
	intToChar(buf, i, obj.intPart);
	
	inversArr(buf, i-1);

	//int factor{10};
	//float tmp;
	//int iTmp{};
	//for (int i{}; i < 6; i++)
	//{
	//	tmp = decPart * factor;
	//	iTmp = (int)tmp;
	//	factor *= 10;

	//}
}

//#Переводит символы в числа#
//#Принимает: массив данных, текущий указатель на последний символ пер. числа, кол. символов в переводимом числе# 
float charToFloat(std::string &input,int i,int numb)
{
	int i_numb{};
	float f_numb{};
	int tmp{i};

	int isDegree{ 1 };
	while (input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && input[i] != '!' && input[i] != '.')
	{
		i_numb += static_cast<int>(input[i] - (int)'0') * isDegree;		//Умнажаем число на степень десяти
		isDegree *= 10;
		i--;
	}

	if (input[i] == '.')
	{
		isDegree = 1;
		tmp = tmp - i;
		i--;
		f_numb = (float)i_numb;
		for (int j{}; j < tmp; j++)
		{
			isDegree *= 10;
		}
		f_numb /= isDegree;

		isDegree = 1;
		i_numb = 0;
		while (input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && input[i] != '!')
		{
			i_numb += static_cast<int>(input[i] - (int)'0') * isDegree;		//Умнажаем число на степень десяти
			isDegree *= 10;
			i--;
		}
		f_numb += static_cast<float> (i_numb);

		//Если число отрицательное делаем отрицательным
		if (input[i] == '-' && (input[i - 1] == '+' || input[i - 1] == '-' || input[i - 1] == '*' || input[i - 1] == '/' || input[i - 1] == '!'))
			f_numb = f_numb - f_numb * 2;

		return f_numb;
	}

	//Если число отрицательное делаем отрицательным
	if (input[i] == '-' && (input[i - 1] == '+' || input[i - 1] == '-' || input[i - 1] == '*' || input[i - 1] == '/' || input[i - 1] == '!'))
		i_numb = i_numb - i_numb * 2;

	return i_numb;
}


//#Вычесляет колличество символов числа, до арифмитического знака или после#
//#Принимает: массив с данными, текущая позиция в массиве, флаг направления  true - 
//в право(число находящаяся с право от ар. знака), false - влево.#
int numbCount(std::string &input, int i,bool direction)
{
	int numb{};

	//Если результат выражения отрицательное число
	if (input[1] == '-' && (input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/'))
	{
		i++;
	}

	if (direction != true)
	{
		//Считаем количество символов до следующего знака
		while (input[i - 1] != '+' && input[i - 1] != '-' && input[i - 1] != '*' && input[i - 1] != '/' && input[i-1] != '!')
		{
			if(input[i-1] == '.')
				fNumb = true;
			numb++;
			i--;
	
		}
	}
	else
	{
		if (input[i + 1] == '-')//Если унарный минус
		{
			i++;				//Начинаем с него
			numb++;				//И берём его в счёт(в левую сторону не надо)
		}

		while (input[i + 1] != '+' && input[i + 1] != '-' && input[i + 1] != '*' && input[i + 1] != '/' && input[i + 1] != '!')
		{
			if (input[i + 1] == '.')
				fNumb = true;
			numb++;
			i++;
		}
	}
	return numb;
}

void copy(std::string& input,int &i , int &lnumb ,char* buftmp)
{

	i -= lnumb;
	if (input[i - 1] == '-' && (input[i - 2] == '+' || input[i - 2] == '-' || input[i - 2] == '*' || input[i - 2] == '/' || input[i - 2] == '!'))
		i--;

	int j{};
	while (buftmp[j] != '\0')
	{
		input[i] = buftmp[j];
		j++;
		i++;
	}
}


//#Сжатие массива путём записи вычисленных значений#
//#Принимает: Массив с данными, размер массива, текущая поз. в массиве, результат вырожения,
//кол. символов лев. числа от ар. знака, кол. символов правого числа#
void compressionArr(std::string& input, int &i, float result, int lnumb, int rnumb)
{
	int count{};
	char buf[256]{};
	if (input[i + (rnumb + 1)] == '!')
	{
		floatToChar(buf, result);
	//	count= sprintf_s(buf, sizeof(buf) - i, "%d", result);
		copy(input,i,lnumb,buf);
		input[i] = '!';
		input[i+1] = '\0';
		i--;//Чтобы указать на последний символ в массиве и не делать проход по нему
	}
	else
	{
		char buftmp[256]{};
		int j{}, k{ i };

		while (input[k + rnumb + 1] != '\0')
		{
			buftmp[j] = input[k + rnumb + 1];
			j++;
			k++;
		}
		buftmp[j] = '\0';
		j = 0;

		floatToChar(buf, result);
	//	count = sprintf_s(buf, sizeof(buf) - i, "%d", result);


		copy(input, i, lnumb, buf);
		int tmp{i};  //Временная переменная для хранения индекса

		while (buftmp[j] != '\0')
		{
			if (i < input.size())
			{
				input[i] = buftmp[j];
				j++;
				i++;
			}
			else
			{
				input.push_back(buftmp[j]);
				j++;
				i++;
			}

		}
		input[i] = '\0';
		i = tmp-1;
	}

}

//#Вычесления значений вырожения# 
//#Принимает: массив преобразованных данных в символы, размер массива#
int doColculations(std::string& input)			
{
	int result{};	
	float f_result{};
	int lNumb{}, rNumb{};
	float f_lNumb{}, f_rNumb{};
	int lCount{}, rCount{};
	int i{1};

	//processing * and /
	while (input[i] != '!')
	{
		if (input[i] == '*')
		{
			//Считаем количество символов слево и справо от знака
			lCount = numbCount(input, i, false);
			rCount = numbCount(input, i, true);
			if (fNumb == true)
			{
				f_lNumb = charToFloat(input, i - 1, lCount);	//i указывает на символ перед знаком
				f_rNumb = charToFloat(input, i + rCount, rCount);	
				f_result = f_lNumb * f_rNumb;
				compressionArr(input, i, f_result, lCount, rCount);
			}
			else
			{
				lNumb = charToFloat(input, i - 1, lCount);	//i указывает на символ перед знаком
				rNumb = charToFloat(input, i + rCount, rCount);//i указываит на младший разряд числа после знака
				result = lNumb * rNumb;
				compressionArr(input, i, result, lCount, rCount);//Записываем результат в строку и сжимаем её на эти символы
			}

			fNumb = false;
		}
		else if(input[i] == '/')
		{
			lCount = numbCount(input, i, false);
			lNumb = charToFloat(input, i - 1, lCount);
			rCount = numbCount(input, i, true);
			rNumb = charToFloat(input, i + rCount, rCount);

			result = lNumb / rNumb;
			compressionArr(input, i, result, lCount, rCount);
		}

		i++;
	}
	//Pocessing + and -
	i = 1;
	while (input[i] != '!')
	{
		if (input[i] == '-' && input[i - 1] == '!')
		{
			i++;
			continue;
		}

		if (input[i] == '+')
		{
			lCount = numbCount(input, i, false);
			lNumb = charToFloat(input, i - 1, lCount);
			rCount = numbCount(input, i, true);
			rNumb = charToFloat(input, i + rCount, rCount);

			result = lNumb + rNumb;
			compressionArr(input, i, result, lCount, rCount);
		}
		else if(input[i] == '-')
		{
			lCount = numbCount(input, i, false);
			lNumb = charToFloat(input, i - 1, lCount);
			rCount = numbCount(input, i, true);
			rNumb = charToFloat(input, i + rCount, rCount);

			result = lNumb - rNumb;
			compressionArr(input, i, result, lCount, rCount);
		}

		i++;
	}

	i = 0;
	int numb{};
	numb = numbCount(input, 0, true);
	if (input[1] == '-')
		i = 1;

	result = charToFloat(input,numb+i,numb);
	return result;

}

int correctInput(std::string const& str,int size)
{
	int i{};
	while (str[i] != '\0')
	{
		//Корректно если: число, арифм. знак или знак дес. дроби 
		if ((int)str[i] >= (int)'0' && (int)str[i] <= (int)'9' || str[i] == '+' || str[i] == '-' ||
			str[i] == '*' || str[i] == '/' || str[i] == '.')
		{
			//Проверка на арифм. знак в начале
			if (i == 0)
			{
				if (str[i] == '+'|| str[i] == '*' || str[i] == '/')
				{
					return -1;
				}
			}

			// Проверка на два знака подряд
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
			{
				if (str[i + 1] == '+' || str[1] == '-' || (str[i+1] == '-' && str[i+2] == '-') || str[i + 1] == '*' || str[i + 1] == '/')
				{
					return -1;
				}
			}

			//Проверка на арифм. знак в конце
			if (str[size-1] == '+' || str[size-1] == '-' || str[size-1] == '*' || str[size-1] == '/')
			{
				return -1;
			}
			i++;
		}
		else
			return -1;
	}

	i = 0;
	//Проверка на корректность десятичной дроби
	if (str[0] != '-')
	{
		if (str[0] == '.')
			return -1;
	}
	else
	{
		if (str[1] == '.')
			return -1;
		i++;
	}

	int count{};
	while (true)
	{
		//Сканируем число на наличие точек
		while (str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && str[i] != '\0')
		{
			if (str[i] == '.')
				count++;

			i++;
		}

		if (count > 1)
			return -1;
		count = 0;

		//Выходим если конец строки 
		if (str[i] == '\0')
			return 0;

		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			if (str[i - 1] == '.' || str[i+1] == '.')
				return -1;
		}

		i++;
	}
	//return 0;

}

//#Получает значения от пользователя и переводет их в символы#
//#Принимает: массив для данных, размер массива#
void userInput(std::string &input)
{
	std::string str;
	while (true)
	{
		std::cout << "Введите вырожение типа \"a#b#c\" где \"#\" символы \"+,-,*,/\", а \"a,b,c\" десятичные числа:\n>> ";	//	std::cout << "Введите число: ";
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
	result = doColculations(input);
	std::cout << "Результат = " << result << '\n';
}