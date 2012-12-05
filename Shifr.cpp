/*Данная программа шифрует текст из файла шифром Цезаря.*/
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void getHELP (){//функция для вывода справки
	 cout <<("$ crypt [options] <key> <source> [<dest>]\n\n")<< ("options:\n") <<
    ("-a, --alphabet=<alphabet>  alphabet - alphabet  for a work ALGORYTHM (defolt\n") <<
    ("                           have a latin word and numbers: AaBbCc..Zz0..9)\n") <<
    ("-t, --type=<type>          type may be 'encode' or 'decode', defolt - encode\n") <<        
    ("-h, --help                 display this massage\n\n") <<
("key:\n") <<
    ("key for encode/decode\n\n")<<
("source:\n")<<
    ("your file for encode/decode\n\n")<<
("dest:\n")<<
("file, where have written new, encode text. If not argument, then rewrite source\n");}

int main (int argc, char* argv[]) {

	string ALPHABET="ABCDEFGHIJKLMNOPQRSTUVWXYZ",alphabet="abcdefghijklmnopqrstuvwxyz",numbers="0123456789",newalphabet;/*описание основного алфавита,
в переменной newalphabet будет храниться алфавит заданный пользователем*/
	int newnumb,alphasize,ALPHAsize,numsize,key=0,count=0,usertype=0,usersourse=0,userdest=0,ravno; /* newnumb - служит новым числом для символа в алфавите, 
alphasize,ALPHAsize,numsize - размеры алфавитов, key - ключ, count - счетчик файлов заданных пользователем, usertype - тип шифрования по умолчанию 
стоит encode,usersourse-положение файла с исходным текстом,userdest - положение файла куда будет записываться шифр,ravno - потребуется при задании алфавита
вторым способом*/
	alphasize=alphabet.size(); ALPHAsize=ALPHABET.size(); numsize=numbers.size(); //начальная задача размеров алфавита
	string buffer="\0",stroka;//буффер куда будет записываться шифр, stroka - в ней будет храниться строка содержащая в себе "--alphabet" 
	char symb,newsymb, point='.', minus='-';//symb - символ считываемый из исходного шифра, newsymb - зашифрованный символ
	ifstream infile;// открыть поток для чтения
	ofstream outfile;//открыть поток для записи
	
	for (int e=1; e<argc; e++){//проверка на ошибки
		if ((argv[e][0]=='-')&&(isdigit(argv[e][1])!=0)){//проверка на корректное задание ключа
			cout<<"Error:Otricatelniy kluch, vvedite -h ili --help dlya vizova spravochnoi informacii";
			exit(1);}
		if ((argv[e][0]==minus)&&((argv[e][1]!='h')&&(argv[e][1]!='a')&&(argv[e][1]!='t')&&(argv[e][1]!=minus))){/*проверка аргументов программы
	на случайное задание неправильного аргумента*/
			cout<<"Error: Nepravilno zadani parametri, vvedite -h ili --help dlya vizova spravochnoi informacii";
			exit(1);}
		if ((!strcmp(argv[e],"-a"))&&(argv[e+1][0]==minus)){//проверка на корректное задание алфавита
			cout<<"Error: Nepravilnoe zadanie alfavita, vvedite -h ili --help dlya vizova spravochnoi informacii";
			exit(1);}
		if ((!strcmp(argv[e],"-t"))&&((argv[e+1][0]!='e')&&(argv[e+1][0]!='d'))){//проверка на корректное задание типа кодирования
			cout<<"Error:Nepravilnoe zadanie type, vvedite -h ili --help dlya vizova spravochnoi informacii ";
			exit(1);}
	}
	for (int t=1; t<argc; t++){ //поиск запроса типа кодирования
			if (((!strcmp(argv[t],"-t"))&&(!strcmp(argv[t+1],"encode")))||(!strcmp(argv[t],"--type=encode")))
			usertype=0;//замена программного типа на пользовательский тип encode
			if (((!strcmp(argv[t],"-t"))&&(!strcmp(argv[t+1],"decode")))||(!strcmp(argv[t],"--type=decode")))
			usertype=1;}//замена программного типа на пользовательский тип decode

	for (int k=1; k<argc; k++) //поиск ключа через функцию isdigit
		if (isdigit(argv[k][0])!=0)
			key=atoi(argv[k]);//передача в int key, argv[k] через atoi

	for (int help=1;help<argc;help++) // поиск запроса справки и вызов её
		if ((!strcmp(argv[help],"-h"))||(!strcmp(argv[help],"--help"))){
			getHELP();
			exit(1);}

	if (key==0){//проверка на задание ключа
			cout<<"Error: Net klucha";
			exit(1);}

	for (int i=1;i<argc; i++) // поиск заданя алфавита и создание его
		if (!strcmp(argv[i],"-a")){
			newalphabet=argv[i+1];// пользовательский алфавит
			ALPHABET="\0";alphabet="\0";numbers="\0"; //опустошение стандартного алфавита
			int newalphabetsize=newalphabet.size();//получение размера нового алфавита
			for (int j=0;j<newalphabetsize;j++){
				if (islower(newalphabet[j])!=0)//поиск строчных символов в новом алфавите и добавление их в программный алфавит
					alphabet+=newalphabet[j];
				if (isupper(newalphabet[j])!=0)//поиск заглавных символов в новом алфавите и добавление их в программный алфавит
					ALPHABET+=newalphabet[j];
				if (isdigit(newalphabet[j])!=0) //поиск цифровых символов в новом алфавите и добавление их в программный алфавит
					numbers+=newalphabet[j];}
		alphasize=alphabet.size(); ALPHAsize=ALPHABET.size(); numsize=numbers.size();}//подсчитываем размер строчного/заглавного/цифрового алфавита

	for (int i=1;i<argc; i++) // поиск заданя алфавита и создание его
		if (!strncmp(argv[i],"--alphabet",10)){//поиск другого способа задания алфавита
			stroka=argv[i];
			for (int a=0;a<(stroka.size());a++)
				if (stroka[a]=='=')//ищем позицию знака "=" в этой строчке
					ravno=a;
			for (int a=(ravno+1);a<(stroka.size());a++)//записываем в newalphabet все после знака "="
				newalphabet+=stroka[a];
			ALPHABET="\0";alphabet="\0";numbers="\0"; //опустошение стандартного алфавита
			int newalphabetsize=newalphabet.size();//получение размера нового алфавита
			for (int j=0;j<newalphabetsize;j++){
				if (islower(newalphabet[j])!=0)//поиск строчных символов в новом алфавите и добавление их в программный алфавит
					alphabet+=newalphabet[j];
				if (isupper(newalphabet[j])!=0)//поиск заглавных символов в новом алфавите и добавление их в программный алфавит
					ALPHABET+=newalphabet[j];
				if (isdigit(newalphabet[j])!=0) //поиск цифровых символов в новом алфавите и добавление их в программный алфавит
					numbers+=newalphabet[j];}
		alphasize=alphabet.size(); ALPHAsize=ALPHABET.size(); numsize=numbers.size();}//подсчитываем размер строчного/заглавного/цифрового алфавита

	for (int file=1; file<argc; file++)
			//поиск файлов введенных пользователем и подсчет их количества
		if (strchr(argv[file],point)!=0){
			count++;
		//сначала записываем usersourse и userdest одинаковыми, потом продолжаем искать второй файл и переписываем userdest
	if (count==1){//если задан один файл пользователем, то записываем 
			usersourse=file;// usersourse=userdest=file положения исходного файла и файла, который будет хранить шифр
			userdest=file;}
	else if (count==2)//если задано два файла пользователем, то переписываем в userdest расположение файла, который будет хранить шифр
			userdest=file;
	}
	infile.open(argv[usersourse]);//связываем исходный файл
		if (!infile.is_open())//проверяем его на существование
			{
			cout<<"Can't open file";
			exit(1);
			}
		else if (usertype==0)//проверка на тип кодирования текста: encode
		{
			while (!infile.eof())
		{
			infile.get(symb); //считываем символ до конца файла
				if (isalnum(symb)!=0){//проверяем является ли этот символ буквой или цифрой
					if (islower(symb)!=0){//проверяем является ли этот символ буквой строчного алфавита
						for (int i=0;i<(alphasize);i++)
							if (symb==alphabet[i])//ищем его номер в алфавите
								newnumb=(i+key)%alphasize;//получаем номер зашифрованного символа
						newsymb=alphabet[newnumb];//получаем зашифрованный символ
						buffer+=newsymb;}//добавляем символ в буфер
						
					if (isupper(symb)!=0){ //проверяем является ли этот символ буквой заглавного алфавита
						for (int i=0;i<ALPHAsize;i++)
							if (symb==ALPHABET[i])//ищем его номер в алфавите
								newnumb=(i+key)%ALPHAsize;//получаем номер зашифрованного символа
						newsymb=ALPHABET[newnumb];//получаем зашифрованный символ
						buffer+=newsymb;}//добавляем символ в буфер
						
					if (isdigit(symb)!=0){ //проверяем является ли этот символ буквой цифрового алфавита
						for (int i=0;i<numsize;i++)
							if (symb==numbers[i])//ищем его номер в алфавите
								newnumb=(i+key)%numsize;//получаем номер зашифрованного символа
						newsymb=numbers[newnumb];//получаем зашифрованный символ
						buffer+=newsymb;}//добавляем символ в буфер
								   }
		}
		}
		else if (usertype==1)//проверка на тип кодирования текста: decode
			{
				while (!infile.eof())//считываем символ до конца файла
			{
				infile.get(symb);//считываем символ до конца файла

				if (isalnum(symb)!=0){//проверяем является ли этот символ буквой или цифрой
					if (islower(symb)!=0){//проверяем является ли этот символ буквой строчного алфавита
						for (int i=0;i<(alphasize);i++)
							if (symb==alphabet[i]){//ищем его номер в алфавите
								key=key%alphasize;//для работы ключей большого значения
								newnumb=(i+alphasize-key)%alphasize;}//получаем номер зашифрованного символа
						newsymb=alphabet[newnumb];//получаем зашифрованный символ
						buffer+=newsymb;}//добавляем символ в буфер

					if (isupper(symb)!=0){ //проверяем является ли этот символ буквой заглавного алфавита
						for (int i=0;i<ALPHAsize;i++)
							if (symb==ALPHABET[i]){//ищем его номер в алфавите
								key=key%ALPHAsize;//для работы ключей большого значения
								newnumb=(i+ALPHAsize-key)%ALPHAsize;}//получаем номер зашифрованного символа
						newsymb=ALPHABET[newnumb];//получаем зашифрованный символ
						buffer+=newsymb;}//добавляем символ в буфер

					if (isdigit(symb)!=0){ //проверяем принадлежит ли этот символ цифровому алфавиту
						for (int i=0;i<numsize;i++)
							if (symb==numbers[i]){//ищем его номер в алфавите
								key=key%numsize;//для работы ключей большого значения
								newnumb=(i+numsize-key)%numsize;}//получаем номер зашифрованного символа
						newsymb=numbers[newnumb];//получаем зашифрованный символ
						buffer+=newsymb;}//добавляем символ в буфер
									}
			}
			}
	infile.close();//закрываем поток чтения
	outfile.open(argv[userdest]);//открываем для записи файл, который будет хранить шифр
		if (!outfile.is_open())//проверяем его на существование
				{
				cout<<"Can't open file";
				exit(1);
				}
		else
			{int len=buffer.size();//т.к. во время тестирования была обнаружена проблема с добавление лишнего символа в конец буффера
			for (int i=0;i<(len-1);i++)//записываем в файл буффер без лишнего символа
				outfile<<buffer[i];
			outfile.close();//закрываем поток записи
			}
	return 0;
}