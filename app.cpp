#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<iostream>
#include<fstream>
#include<ctime>

#ifndef __COMPILE_IN_LINUX

#include<windows.h>
#include<conio.h>
void setColor(unsigned short ForeColor, unsigned short BackGroundColor) {
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle,ForeColor+BackGroundColor*0x10);
}
void resetColor(){
	setColor(7, 0);
}
void clearScreen()
{
	system("cls");
}

#else

#include <curses.h>
#include <unistd.h>
void setColor(unsigned short ForeColor, unsigned short BackGroundColor) {
	if(BackGroundColor == 0xA)printf("\033[0;37;42m");
	else if(BackGroundColor == 0xC)printf("\033[0;37;41m");
}
void resetColor(){
	printf("\e[0;37;40m");
}
void clearScreen()
{
	system("clear");
	printf("\e[2J");
}

#endif



class chooseProblem{
	public:
		string question;
		string items[4];
		string filename;
		int ans_index;
		chooseProblem(string filename){
			init(filename);
			suff();
		}
		bool run(){
			printf("%s\r\n", question.c_str());
			for(int i = 0;i < 4;i++)
				printf("%d : | %s\r\n", i, items[i].c_str());
			printf("Choose your answer:");
			int ch = getch();
			while(ch >= '4' || ch < '0')ch = getch();
			printf("%c\r\n", ch);
			if(ans_index == (ch - '0'))setColor(0x0, 0xA);
			else setColor(0x0, 0xC);
			printf("The right answer is %d, and your answer is %d.%s.\r\n",
				ans_index,
				ch - '0',
				ans_index == (ch - '0') ? "Accept" : "Wrong answer"
			);
			resetColor();
			#ifdef __COMPILE_IN_LINUX
			sleep(1);
			#else
			Sleep(1000);
			#endif
			return ans_index == (ch - '0');
		}
		void print(){
			printf("%s\r\n", question.c_str());
			for(int i = 0;i < 4;i++)
				printf("%d : | %s\r\n", i, items[i].c_str());
			printf("Answer is %d.\r\n", ans_index);
		}
		string toString(){
			char buf[2000];string ret("");
			sprintf(buf, "%s\r\n", question.c_str());
			ret = ret + buf;
			for(int i = 0;i < 4;i++){
				sprintf(buf, "%d : | %s\r\n", i, items[i].c_str());
				ret = ret + buf;
			}
			sprintf(buf, "Answer is %d.\r\n", ans_index);
			ret = ret + buf;
			return ret + filename + "\r\n";
		}
	private:
		void suff(){
			bool isAns[4];
			memset(isAns, false, sizeof(isAns));
			isAns[ans_index] = true;
			for(int i = 0;i < 20;i++){
				int l = rand() % 4, r = rand() % 4;
				if(l == r)continue;
				std::swap(items[l], items[r]);
				std::swap(isAns[l], isAns[r]);
			}
			for(int i = 0;i < 4;i++)if(isAns[i])ans_index = i;
		}
		void init(string filename){
			this->filename = filename;
			std::ifstream fin(filename.c_str());
			std::getline(fin, question);
			for(int i = 0;i < 4;i++)std::getline(fin, items[i]);
			ans_index = 0;
		}
};

vector<chooseProblem> wrong;
bool vst[300];

int main(){
	resetColor();
	srand(time(NULL));
	printf("How many questions do you want to solve?\r\n");
	int n;scanf("%d", &n);
	#ifdef __COMPILE_IN_LINUX
	initscr();
	cbreak();
	noecho();
	refresh();
	#endif
	for(int i = 0;i < n;i++){
		char buf[50];
		int x = rand() % 284 + 1;
		while(vst[x])x = rand() % 284 + 1;
		vst[x] = 1;
		#ifdef __USING_UTF8
		sprintf(buf, "data_utf8/%d.txt", x);
		#else
		sprintf(buf, "data/%d.txt", x);
		#endif
		chooseProblem cp(buf);
		clearScreen();
		printf("Solving question %d in %d:\r\n", i + 1, n);
		if(!cp.run())wrong.push_back(cp);
		std::ofstream out("wrong.txt");
		for(int i = 0;i < wrong.size();i++)out << wrong[i].toString() << std::endl;
		out.close();
	}
	clearScreen();
	printf("Your accepted radio is %lf%% (%d / %d).\r\n",
		(double)(n - wrong.size()) / n * 100,
		(int)(n - wrong.size()),
		n
	);
	if(n == 1)puts("The wrong problem has been saved to wrong.txt");
	else puts("All your wrong problems have been saved to wrong.txt");
	#ifdef __COMPILE_IN_LINUX
	endwin();
	#endif
	return 0;
}
