#include "workerManager.h"

WorkerManager::WorkerManager() {
	//初始化读取文件
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	//文件未创建
	if(!ifs.is_open()) {
		cout << "图书库不存在" << endl;
		this->books_FileisEmpty = true;
		this->book_sum = 0;
		this->book_array = nullptr;
		ifs.close();
		return;
	}

	//文件创建但为空
	char ch;
	ifs >> ch;
	if(ifs.eof()) {
		cout << "图书库存为空" << endl;
		this->books_FileisEmpty = true;
		this->book_sum = 0;
		this->book_array = nullptr;
		ifs.close();
		return;
	}
	
	//文件数据不为空,则获取书单记录数（数量+初始化数组）
	int num = this->getBooksNuminFile();
	cout << "库中图书数为：" << num << endl;
	this->book_sum = num;
	this->book_array = new Book*[num];
	this->initBookArray();
}

//展示菜单
void WorkerManager::showMenu() {
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用图书管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.新书入库  *************" << endl;
	cout << "*************  2.图书注销  *************" << endl;
	cout << "*************  3.查询图书信息  *************" << endl;
	cout << "*************  4.借书  *************" << endl;
	cout << "*************  5.还书  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//写文件
void WorkerManager::saveBookMenu() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for(int i = 0; i < this->book_sum; i++) {
		ofs << this->book_array[i]->b_id << " "
		    << this->book_array[i]->b_name << " "
		    << this->book_array[i]->b_writer << " "
		    << this->book_array[i]->b_price << " "
		    << this->book_array[i]->b_state << " "
		    << this->book_array[i]->r_id << endl;
	}
	ofs.close();
}

//获取书单记录数
int WorkerManager::getBooksNuminFile() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string id; //图书编号
	string name; //书名
	string writer; //作者
	double price; //价格
	int state;
	string r_id;

	int num = 0;
	while(ifs>>id && ifs>>name && ifs>>writer && ifs>>price && ifs>>state && ifs>>r_id) {
		num ++;
	}

	ifs.close();
	return num;
}

//读文件初始化书单列表
void WorkerManager::initBookArray() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string id; //图书编号
	string name; //书名
	string writer; //作者
	double price; //价格
	int state;
	string r_id;

	int index = 0;
	while(ifs>>id && ifs>>name && ifs>>writer && ifs>>price && ifs>>state && ifs>>r_id){
		Book* book = nullptr;
		book = new Book(id, name, writer, price, state, r_id);

		this->book_array[index] = book;
		index ++;
	}
}

//退出系统
void WorkerManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//判断图书是否存在
int WorkerManager::isExist(string id) {
	int index = -1;
	for(int i = 0; i < this->book_sum; i++) {
		if(this->book_array[i]->b_id == id) {
			index = i;
			break;
		}
	}
	return index;
}

//新书入库
void WorkerManager::addBooks() {
	cout << "请输入入库图书数量" << endl;

	int addNum = 0;
	cin >> addNum;

	if(addNum > 0) {
		//计算与开辟图书信息新空间
		int newSize = this->book_sum + addNum;
		Book** newSpace = new Book*[newSize];

		//将原空间内容放到新空间下
		if(this->book_array != nullptr) {
			for(int i = 0; i < this->book_sum; i++) {
				newSpace[i] = this->book_array[i];
			}
		}

		//输入图书信息
		for(int i = 0; i < addNum; i++) {
			string id; //图书编号
			string name; //书名
			string writer; //作者
			double price; //价格
//			int buynum;	//购买数量

			cout << "请输入第" << i + 1 << "本入库图书编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "本入库图书书名：" << endl;
			cin >> name;
			cout << "请输入第" << i + 1 << "本入库图书作者：" << endl;
			cin >> writer;
			cout << "请输入第" << i + 1 << "本入库图书价格：" << endl;
			cin >> price;
//			cout << "请输入第" << i + 1 << "本入库图书购买数量：" << endl;
//			cin >> buynum;

			Book* book = new Book(id, name, writer, price);
			newSpace[this->book_sum + i] = book;
		}

		//使指向图书信息数组的指针指向新空间
		delete[] this->book_array;
		this->book_array = newSpace;
		this->book_sum = newSize;

		this->saveBookMenu();
		this->books_FileisEmpty = false;
		cout << "成功入库" << addNum << "本图书" << endl;

	} else {
		cout << "输入信息有误" << endl;
	}
	system("pause");
	system("cls");
}

//图书注销
void WorkerManager::delBook() {
	if(this->books_FileisEmpty) {
		cout << "图书库存为空或不存在" << endl;
	} else {
		cout << "请输入要注销图书号" << endl;
		string id = " ";
		cin >> id;

		//先判断一下要注销的图书存不存在
		int index = this->isExist(id);
		if(index != -1) {
			for(int i = index; i < this->book_sum - 1; i++) {
				this->book_array[i] = this->book_array[i+1];
			}
			this->book_sum --;

			this->saveBookMenu();
			cout << "注销成功！" << endl;

		} else {
			cout << "注销失败，未找到该图书" << endl;
		}
	}

	system("pause");
	system("cls");
}

//图书查找
void WorkerManager::findBook() {
	if(this->books_FileisEmpty) {
		cout << "图书库存为空或不存在" << endl;
	} else {
		cout << "请输入查找的方式：" << endl;
		cout << "1、按图书编号查找" << endl;
		cout << "2、按书名查找" << endl;
		int select = 0;
		cin >> select;

		if(select == 1) {
			cout << "请输入查找的图书编号" << endl;
			string id;
			cin >> id;
			int index = isExist(id);
			if(index != -1) {
				cout << "该图书信息如下：" << endl;
				this->book_array[index]->showInfo();
			} else {
				cout << "查找失败，库中无此书信息" << endl;
			}
		} else if(select == 2) {
			cout << "请输入查找图书的书名" << endl;
			string name;
			cin >> name;

			bool flag = false;
			for(int i = 0; i < this->book_sum; i++) {
				if(this->book_array[i]->b_name == name) {
					flag = true;
					cout << "该图书信息如下：" << endl;
					this->book_array[i]->showInfo();
				}
			}
			if(flag == false) {
				cout << "查找失败，库中无此书信息" << endl;
			}
		} else {
			cout << "输入选项有误" << endl;
		}
	}

	system("pause");
	system("cls");
}

//借书
void WorkerManager::borrowBook(){
	if(this->books_FileisEmpty) {
		cout << "图书库存为空或不存在" << endl;
	} else {
		cout << "请输入借书的方式：" << endl;
		cout << "1、按图书编号查找" << endl;
		cout << "2、按书名查找" << endl;
		int select = 0;
		cin >> select;

		if(select == 1) {
			cout << "请输入借入的图书编号" << endl;
			string id;
			cin >> id;
			int index = isExist(id);
			if(index != -1) {
				if(this->book_array[index]->b_state == 1){
					cout << "借书失败，该书已借给读者" << this->book_array[index]->r_id << endl;
					return;
				}				
				
				cout << "请输入借阅人编号" << endl;
				string id;
				cin >> id;
				this->book_array[index]->r_id = id;
				this->book_array[index]->b_state = 1;
				this->saveBookMenu();
				
				cout << "借书成功！该图书信息如下：" << endl;
				this->book_array[index]->showInfo();
			} else {
				cout << "查找失败，库中无此书信息" << endl;
			}
		} else if(select == 2) {
			cout << "请输入查找图书的书名" << endl;
			string name;
			cin >> name;

			bool flag = false;
			for(int i = 0; i < this->book_sum; i++) {
				if(this->book_array[i]->b_name == name) {
					if(this->book_array[i]->b_state == 1){
						cout << "借书失败，该书已借给读者" << this->book_array[i]->r_id << endl;
						return;
					}					
					cout << "请输入借阅人编号" << endl;
					string id;
					cin >> id;
					this->book_array[i]->r_id = id;	
					this->book_array[i]->b_state = 1;				
					flag = true;
					this->saveBookMenu();
					
					cout << "借书成功！该图书信息如下：" << endl;
					this->book_array[i]->showInfo();
				}
			}
			if(flag == false) {
				cout << "查找失败，库中无此书信息" << endl;
			}
		} else {
			cout << "输入选项有误" << endl;
		}
	}

	system("pause");
	system("cls"); 
} 

//还书
void WorkerManager::returnBook(){
	cout << "请输入要还书的借阅人编号：" << endl;
	string r_id;
	cin >> r_id;
	
	//确定借阅者存在
	bool r_flag = false;
	for(int i = 0; i < this->book_sum; i++){
		if(this->book_array[i]->r_id == r_id){
			r_flag = true;
		}
	}
	if(!r_flag){
		cout << "该读者不存在，请检查输入" << endl;
		system("pause");
		system("cls");
		return;
	} 
	
	//确定借阅者存在后，查找图书信息，确认有此借阅记录，执行还书操作 
	bool b_flag = false;	
	
	cout << "请输入所还书籍信息：" << endl;
	cout << "1、按图书编号" << endl;
	cout << "2、按书名" << endl;
	int select = 0;
	cin >> select;  
	if(select == 1){
		cout << "请输入所还书籍图书编号：" << endl;
		string b_id;
		cin >> b_id; 
		
		for(int i = 0; i < this->book_sum; i++){
			if(this->book_array[i]->r_id == r_id){
				if(this->book_array[i]->b_id == b_id){
					this->book_array[i]->b_state = 0;
					this->book_array[i]->r_id = "-";
					this->saveBookMenu();
					
					b_flag = true;
					
					cout << "还书成功！该图书信息如下：" << endl; 
					this->book_array[i]->showInfo();
					break;
				}
			}
		} 

		if(!b_flag){
			cout << "该读者无此借阅记录" << endl;
		}
		
	} else if(select == 2){
		cout << "请输入所还书籍书名：" << endl;
		string b_name;
		cin >> b_name; 
		
		for(int i = 0; i < this->book_sum; i++){
			if(this->book_array[i]->r_id == r_id){
				if(this->book_array[i]->b_name == b_name){
					this->book_array[i]->b_state = 0;
					this->book_array[i]->r_id = "-";
					this->saveBookMenu();
					
					b_flag = true;
					
					cout << "还书成功！该图书信息如下：" << endl; 
					this->book_array[i]->showInfo();
					break;
				}
			}
		} 

		if(!b_flag){
			cout << "该读者无此借阅记录" << endl;
		}	
	}
	system("pause");
	system("cls");	
} 

WorkerManager::~WorkerManager() {
	if(this->book_array != nullptr) {
		delete[] this->book_array;
	}

}
