#include <iostream>
using namespace std;
#include "workerManager.h" 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	WorkerManager wm;
	int choice = 0;

	while(1){
		wm.showMenu();
		cout << "����������ѡ��: " << endl;
		cin >> choice;
		
		switch(choice){
			case 0: wm.exitSystem();//�˳�ϵͳ			
			break; 
			case 1: wm.addBooks(); //�������			
			break; 
			case 2: wm.delBook(); //ͼ��ע��
			break;
			case 3: wm.findBook(); //��ѯͼ����Ϣ 
			break;
			case 4: wm.borrowBook(); //����
			break;
			case 5: wm.returnBook(); //���� 
			break;		
		} 
	}
	
	return 0;
}
