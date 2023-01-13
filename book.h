#pragma once
#include<iostream>
#include<string>
using namespace std;

class Book{
public:
	Book();
	//入库初始化 
	Book(string id, string name, string writer, double price);
	//读文件初始化                                                                                                                                                                                                                                                                                                                                                 
	Book(string id, string name, string writer, double price, int state, string r_id);
	
	void showInfo();
	
	string b_id; //图书编号 
	string b_name; //书名 
	string b_writer; //作者 
	double b_price; //价格 
//	int b_buynum;	//购买数量 
	int b_state; //借阅状态，0为在馆，1为借出 
	string r_id; //借书的读者编号，在馆为“-” 
};
