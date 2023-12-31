/* 2150265 济勤09班 王加炜 */

/* 允许按需加入系统的宏定义、需要的头文件等 */
#include <iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<iomanip>
using namespace std;

#define MAX_STU_NUM			256	//约定最大人数为256人（两轮的总和，包括退选、补选）
#define MAX_NAME_LEN			32	//学生姓名的最大长度不超过16个汉字
#define MAX_FILENAME_LEN		256	//文件名的最大长度
class stu_list;
/* stu_info 类存放每个学生的信息，包括学号、姓名、其它需要的私有信息，已有内容不准动，可加入符合限制要求的新内容 */
class stu_info {
private:
	int  stu_no;			//学号
	char stu_name[MAX_NAME_LEN];	//姓名

	/* 允许按需加入private数据成员、成员函数以及其它需要的内容 */
	friend stu_list;
public:
	/* 本类不允许定义任何的公有数据成员、成员函数 */
	
};

/* stu_list 类整个选课信息，已有内容不准动，可加入符合限制要求的新内容 */
class stu_list {
private:
	stu_info stu[MAX_STU_NUM + 1];//创建一个stu数组，每一个元素表示一个stu_info类的对象
	stu_info stu_qian[MAX_STU_NUM + 1];
	stu_info stu_hou[MAX_STU_NUM + 1];
	/* 允许按需加入private数据成员和成员函数 */
	int renshu_qian ;
	int renshu_hou ;
	int num;
public:
	int read(const char* filename, const int append = 0);	//从文件中读入选课信息并进行处理，第2个参数值为0表示覆盖方式，1表示追加方式
	int print(const char* prompt = NULL);			//打印当前读入的选课名单

	/* 允许按需加入其它public成员函数 */

};

/* --- 此处给出上面两个类的成员函数的体外实现 --- */
int stu_list::read(const char* filename, const int append )
{
	
	if (append == 0)//存入前一次选课的学生信息
	{
		int xuehao = 0;
		
		int i = 0;
		int p = 0;
		char ch;
		ifstream in;
		in.open(filename, ios::in || ios::binary);
		if (in.is_open() == 0)
		{
			cout << "文件打开失败" << endl;
			return -1;
		}
	
		while (in.get(ch))
		{
			if (ch >= '0' && ch <= '9')
			{
				i++;
				xuehao += int((ch - '0')) * int(pow(10, 7 - i));
				if (i == 7)
				{

					in.get();
					in.getline(stu_qian[p].stu_name, 256, '\n');//将所有学生的姓名存入stu_info中
					stu_qian[p].stu_no = xuehao;//将所有学生的学号存入stu_info中



					i = 0;
					p++;
					xuehao = 0;
				}
			}
		}
		renshu_qian = p + 1;
	}
	else//存入后一次选课的学生信息
	{
		int xuehao = 0;
		
		
		int i = 0;
		int p = 0;
		char ch;
		ifstream in;
		in.open(filename, ios::in || ios::binary);
		if (in.is_open() == 0)
		{
			cout << "文件打开失败" << endl;
			return -1;
		}
		
		while (in.get(ch))
		{
			if (ch >= '0' && ch <= '9')
			{
				i++;
				xuehao += int((ch - '0')) * int(pow(10, 7 - i));
				if (i == 7)
				{

					in.get();
					in.getline(stu_hou[p].stu_name, 256, '\n');//将所有学生的姓名存入stu_info中
					stu_hou[p].stu_no = xuehao;//将所有学生的学号存入stu_info中



					i = 0;
					p++;
					xuehao = 0;
				}
			}
		}
		renshu_hou = p + 1;
	}
	int i = 0;
	int j = 0;
	int p = renshu_qian - 1;
	//将两个数组中学生的并集存到stu中
	char t[256] = { };
	for (i = 0; i < renshu_qian-1; i++)
	{
		stu[i].stu_no = stu_qian[i].stu_no;
		strcpy_s(stu[i].stu_name, stu_qian[i].stu_name);
	}
	for (j = 0; j < renshu_hou - 1; j++)
	{
		for (i = 0; i < renshu_qian-1; i++)
		{
			if (stu_hou[j].stu_no == stu_qian[i].stu_no)
				break;
			
		}
		if (i == renshu_qian -1)
		{
			stu[p].stu_no = stu_hou[j].stu_no;
			strcpy_s(stu[p].stu_name, stu_hou[j].stu_name);
			p++;
		}
	}
	num = p;
	int c;

	//升序排列
	for (i = 0; i < num ; i++)
	{
		for (j = i+1; j < num; j++)
		{
			if (stu[i].stu_no > stu[j].stu_no)
			{
				c = stu[i].stu_no;
				stu[i].stu_no = stu[j].stu_no;
				stu[j].stu_no = c;
				strcpy_s(t, stu[i].stu_name);
				strcpy_s(stu[i].stu_name, stu[j].stu_name);
				strcpy_s(stu[j].stu_name, t);
			}
				

		}
	}

}

int stu_list::print(const char* prompt )
{
	cout << prompt<<endl;
	cout << "==========================================="<<endl;
	cout << "序号 学号    姓名             第一轮 第二轮"<< endl;
	cout << "===========================================" << endl;
	int qian[256] = {0};
	int hou[256] = {0};
	int i = 0;
	int j = 0;
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < renshu_qian - 1; j++)
		{
			if (stu_qian[j].stu_no == stu[i].stu_no)
			{
				qian[i] = 1;
				break;
			}
			
		}
		for (j = 0; j < renshu_hou - 1; j++)
		{
			if (stu_hou[j].stu_no == stu[i].stu_no)
			{
				hou[i] = 1;
				break;
			}
			
		}
	}



	for (i = 0; i < num; i++)
	{
		if (qian[i] == 1)
		{
			if (hou[i] == 1)
			{
				cout << setw(5) << setiosflags(ios::left) << i + 1 << stu[i].stu_no << " " << setw(8) << setiosflags(ios::left) << stu[i].stu_name << setw(10) << setiosflags(ios::right) << 'Y' << "      " << 'Y' << endl;
				cout << resetiosflags(ios::right);
				
			}
			else
			{
				cout << setw(5) << setiosflags(ios::left) << i + 1 << stu[i].stu_no << " " << setw(8) << setiosflags(ios::left) << stu[i].stu_name << setw(10) << setiosflags(ios::right) << 'Y' << "      " << "退课" << endl;
				cout << resetiosflags(ios::right);
				
			}
		}
		else
		{
			cout << setw(5) << setiosflags(ios::left) << i + 1 << stu[i].stu_no << " " << setw(8) << setiosflags(ios::left) << stu[i].stu_name << setw(10) << setiosflags(ios::right) << '/' << "      " << "补选" << endl;
			cout << resetiosflags(ios::right);
			
		}
	}
	/*for (i = 0; i < renshu_hou-1; i++)
	{
		for (j = 0; j < renshu_qian-1; j++)
		{
			if (stu_qian[j].stu_no == stu_hou[i].stu_no)
			{
				cout << setw(5) << setiosflags(ios::left) <<i + 1 << stu_hou[i].stu_no << " " << setw(8) << setiosflags(ios::left) << stu_hou[i].stu_name <<setw(10)<< setiosflags(ios::right)<< 'Y' << "      " << 'Y' << endl;
				cout << resetiosflags(ios::right);
				break;
			}
			
		}
		if (j == renshu_qian-1)
		{
			cout << setw(5) << setiosflags(ios::left) << i + 1 << stu_hou[i].stu_no << " " << setw(8) << setiosflags(ios::left) << stu_hou[i].stu_name << setw(10) << setiosflags(ios::right) << '/' << "      " << "补选" << endl;
			cout << resetiosflags(ios::right);
		}
	}*/
	cout << "===========================================" << endl;
	return 1;
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准动
***************************************************************************/
int main()
{
	char file1[MAX_FILENAME_LEN], file2[MAX_FILENAME_LEN];

	cout << "请输入前一轮选课的数据文件 : ";
	cin >> file1;
	cout << "请输入后一轮选课的数据文件 : ";
	cin >> file2;

	stu_list list;

	/* 读入第一个数据文件 */
	if (list.read(file1) < 0)
		return -1;

	/* 读入第二个数据文件，参数2的值为1表示追加方式 */
	if (list.read(file2, 1) < 0)
		return -1;

	list.print("最终选课名单");

	return 0;
}