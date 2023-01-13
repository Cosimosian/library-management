#include <iostream>
using namespace std;
#include "workerManager.h" 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	WorkerManager wm;
	int choice = 0;

	while(1){
		wm.showMenu();
		cout << "请输入您的选择: " << endl;
		cin >> choice;
		
		switch(choice){
			case 0: wm.exitSystem();//退出系统			
			break; 
			case 1: wm.addBooks(); //新书入库			
			break; 
			case 2: wm.delBook(); //图书注销
			break;
			case 3: wm.findBook(); //查询图书信息 
			break;
			case 4: wm.borrowBook(); //借书
			break;
			case 5: wm.returnBook(); //还书 
			break;		
		} 
	}
	
	return 0;
}
