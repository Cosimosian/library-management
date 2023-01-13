#pragma once
#include <iostream>
#include <fstream>
#include "book.h"
#define FILENAME "booksMenu.txt"
using namespace std;


class WorkerManager
{
public:

	//构造函数
	WorkerManager();
	
	//保存书单文件 
	void saveBookMenu();
	
	//获取书单文件中的记录数（用于初始化） 
	int getBooksNuminFile();
	
	//初始化图书数组
	void initBookArray(); 		
	
	//展示菜单
	void showMenu(); 
	
	//退出系统
	void exitSystem(); 
	
	//判断图书是否存在
	int isExist(string id); 	
	
	//图书入库
	void addBooks(); 
	
	//图书注销
	void delBook(); 
	
	//图书查找 
	void findBook();	
	
	//借书 
	void borrowBook(); 
	
	//还书
	void returnBook(); 

	//析构函数
	~WorkerManager();

	
	int book_sum; //记录中的图书总类数 		
	Book** book_array; //图书数组指针
	
	bool books_FileisEmpty; //标志书单文件是否为空 
};
