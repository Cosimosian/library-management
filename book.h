#pragma once
#include<iostream>
#include<string>
using namespace std;

class Book{
public:
	Book();
	//����ʼ�� 
	Book(string id, string name, string writer, double price);
	//���ļ���ʼ��                                                                                                                                                                                                                                                                                                                                                 
	Book(string id, string name, string writer, double price, int state, string r_id);
	
	void showInfo();
	
	string b_id; //ͼ���� 
	string b_name; //���� 
	string b_writer; //���� 
	double b_price; //�۸� 
//	int b_buynum;	//�������� 
	int b_state; //����״̬��0Ϊ�ڹݣ�1Ϊ��� 
	string r_id; //����Ķ��߱�ţ��ڹ�Ϊ��-�� 
};
