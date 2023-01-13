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
	cout << "ͼ���ţ�" << this->b_id 
		<<"\t������" << this->b_name
		<<"\t���ߣ�" << this->b_writer
		<<"\t�۸�" << this->b_price
//		<<"\t���������� " << this->b_buynum << endl; 
		<<"\t����״̬��" <<  this->b_state
		<<"\t�����˱�ţ�" << this->r_id << endl;
}
