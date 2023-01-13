#include "book.h"
Book::Book(){
	this->b_id = "-";
	this->b_name = "-";
	this->b_writer = "-";
	this->b_price = 0;
//	this->b_buynum = buynum;
	this->b_state = 0;
	this->r_id = "-";
}

Book::Book(string id, string name, string writer, double price){
	this->b_id = id;
	this->b_name = name;
	this->b_writer = writer;
	this->b_price = price;
//	this->b_buynum = buynum;
	this->b_state = 0;
	this->r_id = "-";
}

Book::Book(string id, string name, string writer, double price, int state, string r_id){
	this->b_id = id;
	this->b_name = name;
	this->b_writer = writer;
	this->b_price = price;
//	this->b_buynum = buynum;
	this->b_state = state;
	this->r_id = r_id;
}


void Book::showInfo(){
	cout << "图书编号：" << this->b_id 
		<<"\t书名：" << this->b_name
		<<"\t作者：" << this->b_writer
		<<"\t价格：" << this->b_price
//		<<"\t购买总数： " << this->b_buynum << endl; 
		<<"\t借阅状态：" <<  this->b_state
		<<"\t借阅人编号：" << this->r_id << endl;
}
