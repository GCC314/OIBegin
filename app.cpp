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
#include<conio.h>
#include<windows.h>
#include<ctime>

void setColor(unsigned short ForeColor, unsigned short BackGroundColor) {
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle,ForeColor+BackGroundColor*0x10);
}

void resetColor(){
	setColor(7, 0);
}

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
			printf("%s\n", question.c_str());
			for(int i = 0;i < 4;i++)
				printf("%d : | %s\n", i, items[i].c_str());
			printf("Choose your answer:");
			int ch = getch();
			while(ch >= '4' || ch < '0')ch = getch();
			printf("%c\n", ch);
			if(ans_index == (ch - '0'))setColor(0x0, 0xA);
			else setColor(0x0, 0xC);
			printf("Std ans is %d, and your ans is %d.%s.\n",
				ans_index,
				ch - '0',
				ans_index == (ch - '0') ? "Accept" : "Wrong answer"
			);
			resetColor();
			Sleep(1000);
			return ans_index == (ch - '0');
		}
		void print(){
			printf("%s\n", question.c_str());
			for(int i = 0;i < 4;i++)
				printf("%d : | %s\n", i, items[i].c_str());
			printf("Answer is %d.\n", ans_index);
		}
		string toString(){
			char buf[2000];string ret("");
			sprintf(buf, "%s\n", question.c_str());
			ret = ret + buf;
			for(int i = 0;i < 4;i++){
				sprintf(buf, "%d : | %s\n", i, items[i].c_str());
				ret = ret + buf;
			}
			sprintf(buf, "Answer is %d.\n", ans_index);
			ret = ret + buf;
			return ret + filename + "\n";
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
	printf("How many questions do you want to slove?\n");
	int n;scanf("%d", &n);
	for(int i = 0;i < n;i++){
		char buf[50];
		int x = rand() % 284 + 1;
		while(vst[x])x = rand() % 284 + 1;
		vst[x] = 1;
		sprintf(buf, "data/%d.txt", x);
		chooseProblem cp(buf);
		system("cls");
		printf("Sloving question %d in %d:\n", i + 1, n);
		if(!cp.run())wrong.push_back(cp);
		std::ofstream out("wrong.txt");
		for(int i = 0;i < wrong.size();i++)out << wrong[i].toString() << std::endl;
		out.close();
	}
	system("cls");
	printf("Your accept radio is %lf%% (%d / %d).\n",
		(double)(n - wrong.size()) / n * 100,
		n - wrong.size(),
		n
	);
	puts("All your wrong problem(s) has saved to wrong.txt");
	return 0;
}
