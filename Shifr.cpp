/*������ ��������� ������� ����� �� ����� ������ ������.*/
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void getHELP (){//������� ��� ������ �������
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

	string ALPHABET="ABCDEFGHIJKLMNOPQRSTUVWXYZ",alphabet="abcdefghijklmnopqrstuvwxyz",numbers="0123456789",newalphabet;/*�������� ��������� ��������,
� ���������� newalphabet ����� ��������� ������� �������� �������������*/
	int newnumb,alphasize,ALPHAsize,numsize,key=0,count=0,usertype=0,usersourse=0,userdest=0,ravno; /* newnumb - ������ ����� ������ ��� ������� � ��������, 
alphasize,ALPHAsize,numsize - ������� ���������, key - ����, count - ������� ������ �������� �������������, usertype - ��� ���������� �� ��������� 
����� encode,usersourse-��������� ����� � �������� �������,userdest - ��������� ����� ���� ����� ������������ ����,ravno - ����������� ��� ������� ��������
������ ��������*/
	alphasize=alphabet.size(); ALPHAsize=ALPHABET.size(); numsize=numbers.size(); //��������� ������ �������� ��������
	string buffer="\0",stroka;//������ ���� ����� ������������ ����, stroka - � ��� ����� ��������� ������ ���������� � ���� "--alphabet" 
	char symb,newsymb, point='.', minus='-';//symb - ������ ����������� �� ��������� �����, newsymb - ������������� ������
	ifstream infile;// ������� ����� ��� ������
	ofstream outfile;//������� ����� ��� ������
	
	for (int e=1; e<argc; e++){//�������� �� ������
		if ((argv[e][0]=='-')&&(isdigit(argv[e][1])!=0)){//�������� �� ���������� ������� �����
			cout<<"Error:Otricatelniy kluch, vvedite -h ili --help dlya vizova spravochnoi informacii";
			exit(1);}
		if ((argv[e][0]==minus)&&((argv[e][1]!='h')&&(argv[e][1]!='a')&&(argv[e][1]!='t')&&(argv[e][1]!=minus))){/*�������� ���������� ���������
	�� ��������� ������� ������������� ���������*/
			cout<<"Error: Nepravilno zadani parametri, vvedite -h ili --help dlya vizova spravochnoi informacii";
			exit(1);}
		if ((!strcmp(argv[e],"-a"))&&(argv[e+1][0]==minus)){//�������� �� ���������� ������� ��������
			cout<<"Error: Nepravilnoe zadanie alfavita, vvedite -h ili --help dlya vizova spravochnoi informacii";
			exit(1);}
		if ((!strcmp(argv[e],"-t"))&&((argv[e+1][0]!='e')&&(argv[e+1][0]!='d'))){//�������� �� ���������� ������� ���� �����������
			cout<<"Error:Nepravilnoe zadanie type, vvedite -h ili --help dlya vizova spravochnoi informacii ";
			exit(1);}
	}
	for (int t=1; t<argc; t++){ //����� ������� ���� �����������
			if (((!strcmp(argv[t],"-t"))&&(!strcmp(argv[t+1],"encode")))||(!strcmp(argv[t],"--type=encode")))
			usertype=0;//������ ������������ ���� �� ���������������� ��� encode
			if (((!strcmp(argv[t],"-t"))&&(!strcmp(argv[t+1],"decode")))||(!strcmp(argv[t],"--type=decode")))
			usertype=1;}//������ ������������ ���� �� ���������������� ��� decode

	for (int k=1; k<argc; k++) //����� ����� ����� ������� isdigit
		if (isdigit(argv[k][0])!=0)
			key=atoi(argv[k]);//�������� � int key, argv[k] ����� atoi

	for (int help=1;help<argc;help++) // ����� ������� ������� � ����� �
		if ((!strcmp(argv[help],"-h"))||(!strcmp(argv[help],"--help"))){
			getHELP();
			exit(1);}

	if (key==0){//�������� �� ������� �����
			cout<<"Error: Net klucha";
			exit(1);}

	for (int i=1;i<argc; i++) // ����� ������ �������� � �������� ���
		if (!strcmp(argv[i],"-a")){
			newalphabet=argv[i+1];// ���������������� �������
			ALPHABET="\0";alphabet="\0";numbers="\0"; //����������� ������������ ��������
			int newalphabetsize=newalphabet.size();//��������� ������� ������ ��������
			for (int j=0;j<newalphabetsize;j++){
				if (islower(newalphabet[j])!=0)//����� �������� �������� � ����� �������� � ���������� �� � ����������� �������
					alphabet+=newalphabet[j];
				if (isupper(newalphabet[j])!=0)//����� ��������� �������� � ����� �������� � ���������� �� � ����������� �������
					ALPHABET+=newalphabet[j];
				if (isdigit(newalphabet[j])!=0) //����� �������� �������� � ����� �������� � ���������� �� � ����������� �������
					numbers+=newalphabet[j];}
		alphasize=alphabet.size(); ALPHAsize=ALPHABET.size(); numsize=numbers.size();}//������������ ������ ���������/����������/��������� ��������

	for (int i=1;i<argc; i++) // ����� ������ �������� � �������� ���
		if (!strncmp(argv[i],"--alphabet",10)){//����� ������� ������� ������� ��������
			stroka=argv[i];
			for (int a=0;a<(stroka.size());a++)
				if (stroka[a]=='=')//���� ������� ����� "=" � ���� �������
					ravno=a;
			for (int a=(ravno+1);a<(stroka.size());a++)//���������� � newalphabet ��� ����� ����� "="
				newalphabet+=stroka[a];
			ALPHABET="\0";alphabet="\0";numbers="\0"; //����������� ������������ ��������
			int newalphabetsize=newalphabet.size();//��������� ������� ������ ��������
			for (int j=0;j<newalphabetsize;j++){
				if (islower(newalphabet[j])!=0)//����� �������� �������� � ����� �������� � ���������� �� � ����������� �������
					alphabet+=newalphabet[j];
				if (isupper(newalphabet[j])!=0)//����� ��������� �������� � ����� �������� � ���������� �� � ����������� �������
					ALPHABET+=newalphabet[j];
				if (isdigit(newalphabet[j])!=0) //����� �������� �������� � ����� �������� � ���������� �� � ����������� �������
					numbers+=newalphabet[j];}
		alphasize=alphabet.size(); ALPHAsize=ALPHABET.size(); numsize=numbers.size();}//������������ ������ ���������/����������/��������� ��������

	for (int file=1; file<argc; file++)
			//����� ������ ��������� ������������� � ������� �� ����������
		if (strchr(argv[file],point)!=0){
			count++;
		//������� ���������� usersourse � userdest �����������, ����� ���������� ������ ������ ���� � ������������ userdest
	if (count==1){//���� ����� ���� ���� �������������, �� ���������� 
			usersourse=file;// usersourse=userdest=file ��������� ��������� ����� � �����, ������� ����� ������� ����
			userdest=file;}
	else if (count==2)//���� ������ ��� ����� �������������, �� ������������ � userdest ������������ �����, ������� ����� ������� ����
			userdest=file;
	}
	infile.open(argv[usersourse]);//��������� �������� ����
		if (!infile.is_open())//��������� ��� �� �������������
			{
			cout<<"Can't open file";
			exit(1);
			}
		else if (usertype==0)//�������� �� ��� ����������� ������: encode
		{
			while (!infile.eof())
		{
			infile.get(symb); //��������� ������ �� ����� �����
				if (isalnum(symb)!=0){//��������� �������� �� ���� ������ ������ ��� ������
					if (islower(symb)!=0){//��������� �������� �� ���� ������ ������ ��������� ��������
						for (int i=0;i<(alphasize);i++)
							if (symb==alphabet[i])//���� ��� ����� � ��������
								newnumb=(i+key)%alphasize;//�������� ����� �������������� �������
						newsymb=alphabet[newnumb];//�������� ������������� ������
						buffer+=newsymb;}//��������� ������ � �����
						
					if (isupper(symb)!=0){ //��������� �������� �� ���� ������ ������ ���������� ��������
						for (int i=0;i<ALPHAsize;i++)
							if (symb==ALPHABET[i])//���� ��� ����� � ��������
								newnumb=(i+key)%ALPHAsize;//�������� ����� �������������� �������
						newsymb=ALPHABET[newnumb];//�������� ������������� ������
						buffer+=newsymb;}//��������� ������ � �����
						
					if (isdigit(symb)!=0){ //��������� �������� �� ���� ������ ������ ��������� ��������
						for (int i=0;i<numsize;i++)
							if (symb==numbers[i])//���� ��� ����� � ��������
								newnumb=(i+key)%numsize;//�������� ����� �������������� �������
						newsymb=numbers[newnumb];//�������� ������������� ������
						buffer+=newsymb;}//��������� ������ � �����
								   }
		}
		}
		else if (usertype==1)//�������� �� ��� ����������� ������: decode
			{
				while (!infile.eof())//��������� ������ �� ����� �����
			{
				infile.get(symb);//��������� ������ �� ����� �����

				if (isalnum(symb)!=0){//��������� �������� �� ���� ������ ������ ��� ������
					if (islower(symb)!=0){//��������� �������� �� ���� ������ ������ ��������� ��������
						for (int i=0;i<(alphasize);i++)
							if (symb==alphabet[i]){//���� ��� ����� � ��������
								key=key%alphasize;//��� ������ ������ �������� ��������
								newnumb=(i+alphasize-key)%alphasize;}//�������� ����� �������������� �������
						newsymb=alphabet[newnumb];//�������� ������������� ������
						buffer+=newsymb;}//��������� ������ � �����

					if (isupper(symb)!=0){ //��������� �������� �� ���� ������ ������ ���������� ��������
						for (int i=0;i<ALPHAsize;i++)
							if (symb==ALPHABET[i]){//���� ��� ����� � ��������
								key=key%ALPHAsize;//��� ������ ������ �������� ��������
								newnumb=(i+ALPHAsize-key)%ALPHAsize;}//�������� ����� �������������� �������
						newsymb=ALPHABET[newnumb];//�������� ������������� ������
						buffer+=newsymb;}//��������� ������ � �����

					if (isdigit(symb)!=0){ //��������� ����������� �� ���� ������ ��������� ��������
						for (int i=0;i<numsize;i++)
							if (symb==numbers[i]){//���� ��� ����� � ��������
								key=key%numsize;//��� ������ ������ �������� ��������
								newnumb=(i+numsize-key)%numsize;}//�������� ����� �������������� �������
						newsymb=numbers[newnumb];//�������� ������������� ������
						buffer+=newsymb;}//��������� ������ � �����
									}
			}
			}
	infile.close();//��������� ����� ������
	outfile.open(argv[userdest]);//��������� ��� ������ ����, ������� ����� ������� ����
		if (!outfile.is_open())//��������� ��� �� �������������
				{
				cout<<"Can't open file";
				exit(1);
				}
		else
			{int len=buffer.size();//�.�. �� ����� ������������ ���� ���������� �������� � ���������� ������� ������� � ����� �������
			for (int i=0;i<(len-1);i++)//���������� � ���� ������ ��� ������� �������
				outfile<<buffer[i];
			outfile.close();//��������� ����� ������
			}
	return 0;
}