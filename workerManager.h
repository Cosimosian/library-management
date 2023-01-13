#pragma once
#include <iostream>
#include <fstream>
#include "book.h"
#define FILENAME "booksMenu.txt"
using namespace std;


class WorkerManager
{
public:

	//���캯��
	WorkerManager();
	
	//�����鵥�ļ� 
	void saveBookMenu();
	
	//��ȡ�鵥�ļ��еļ�¼�������ڳ�ʼ���� 
	int getBooksNuminFile();
	
	//��ʼ��ͼ������
	void initBookArray(); 		
	
	//չʾ�˵�
	void showMenu(); 
	
	//�˳�ϵͳ
	void exitSystem(); 
	
	//�ж�ͼ���Ƿ����
	int isExist(string id); 	
	
	//ͼ�����
	void addBooks(); 
	
	//ͼ��ע��
	void delBook(); 
	
	//ͼ����� 
	void findBook();	
	
	//���� 
	void borrowBook(); 
	
	//����
	void returnBook(); 

	//��������
	~WorkerManager();

	
	int book_sum; //��¼�е�ͼ�������� 		
	Book** book_array; //ͼ������ָ��
	
	bool books_FileisEmpty; //��־�鵥�ļ��Ƿ�Ϊ�� 
};
