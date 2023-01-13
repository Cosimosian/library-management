#include "workerManager.h"

WorkerManager::WorkerManager() {
	//��ʼ����ȡ�ļ�
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	//�ļ�δ����
	if(!ifs.is_open()) {
		cout << "ͼ��ⲻ����" << endl;
		this->books_FileisEmpty = true;
		this->book_sum = 0;
		this->book_array = nullptr;
		ifs.close();
		return;
	}

	//�ļ�������Ϊ��
	char ch;
	ifs >> ch;
	if(ifs.eof()) {
		cout << "ͼ����Ϊ��" << endl;
		this->books_FileisEmpty = true;
		this->book_sum = 0;
		this->book_array = nullptr;
		ifs.close();
		return;
	}
	
	//�ļ����ݲ�Ϊ��,���ȡ�鵥��¼��������+��ʼ�����飩
	int num = this->getBooksNuminFile();
	cout << "����ͼ����Ϊ��" << num << endl;
	this->book_sum = num;
	this->book_array = new Book*[num];
	this->initBookArray();
}

//չʾ�˵�
void WorkerManager::showMenu() {
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ͼ�����ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.�������  *************" << endl;
	cout << "*************  2.ͼ��ע��  *************" << endl;
	cout << "*************  3.��ѯͼ����Ϣ  *************" << endl;
	cout << "*************  4.����  *************" << endl;
	cout << "*************  5.����  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//д�ļ�
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

//��ȡ�鵥��¼��
int WorkerManager::getBooksNuminFile() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string id; //ͼ����
	string name; //����
	string writer; //����
	double price; //�۸�
	int state;
	string r_id;

	int num = 0;
	while(ifs>>id && ifs>>name && ifs>>writer && ifs>>price && ifs>>state && ifs>>r_id) {
		num ++;
	}

	ifs.close();
	return num;
}

//���ļ���ʼ���鵥�б�
void WorkerManager::initBookArray() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string id; //ͼ����
	string name; //����
	string writer; //����
	double price; //�۸�
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

//�˳�ϵͳ
void WorkerManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//�ж�ͼ���Ƿ����
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

//�������
void WorkerManager::addBooks() {
	cout << "���������ͼ������" << endl;

	int addNum = 0;
	cin >> addNum;

	if(addNum > 0) {
		//�����뿪��ͼ����Ϣ�¿ռ�
		int newSize = this->book_sum + addNum;
		Book** newSpace = new Book*[newSize];

		//��ԭ�ռ����ݷŵ��¿ռ���
		if(this->book_array != nullptr) {
			for(int i = 0; i < this->book_sum; i++) {
				newSpace[i] = this->book_array[i];
			}
		}

		//����ͼ����Ϣ
		for(int i = 0; i < addNum; i++) {
			string id; //ͼ����
			string name; //����
			string writer; //����
			double price; //�۸�
//			int buynum;	//��������

			cout << "�������" << i + 1 << "�����ͼ���ţ�" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "�����ͼ��������" << endl;
			cin >> name;
			cout << "�������" << i + 1 << "�����ͼ�����ߣ�" << endl;
			cin >> writer;
			cout << "�������" << i + 1 << "�����ͼ��۸�" << endl;
			cin >> price;
//			cout << "�������" << i + 1 << "�����ͼ�鹺��������" << endl;
//			cin >> buynum;

			Book* book = new Book(id, name, writer, price);
			newSpace[this->book_sum + i] = book;
		}

		//ʹָ��ͼ����Ϣ�����ָ��ָ���¿ռ�
		delete[] this->book_array;
		this->book_array = newSpace;
		this->book_sum = newSize;

		this->saveBookMenu();
		this->books_FileisEmpty = false;
		cout << "�ɹ����" << addNum << "��ͼ��" << endl;

	} else {
		cout << "������Ϣ����" << endl;
	}
	system("pause");
	system("cls");
}

//ͼ��ע��
void WorkerManager::delBook() {
	if(this->books_FileisEmpty) {
		cout << "ͼ����Ϊ�ջ򲻴���" << endl;
	} else {
		cout << "������Ҫע��ͼ���" << endl;
		string id = " ";
		cin >> id;

		//���ж�һ��Ҫע����ͼ��治����
		int index = this->isExist(id);
		if(index != -1) {
			for(int i = index; i < this->book_sum - 1; i++) {
				this->book_array[i] = this->book_array[i+1];
			}
			this->book_sum --;

			this->saveBookMenu();
			cout << "ע���ɹ���" << endl;

		} else {
			cout << "ע��ʧ�ܣ�δ�ҵ���ͼ��" << endl;
		}
	}

	system("pause");
	system("cls");
}

//ͼ�����
void WorkerManager::findBook() {
	if(this->books_FileisEmpty) {
		cout << "ͼ����Ϊ�ջ򲻴���" << endl;
	} else {
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ͼ���Ų���" << endl;
		cout << "2������������" << endl;
		int select = 0;
		cin >> select;

		if(select == 1) {
			cout << "��������ҵ�ͼ����" << endl;
			string id;
			cin >> id;
			int index = isExist(id);
			if(index != -1) {
				cout << "��ͼ����Ϣ���£�" << endl;
				this->book_array[index]->showInfo();
			} else {
				cout << "����ʧ�ܣ������޴�����Ϣ" << endl;
			}
		} else if(select == 2) {
			cout << "���������ͼ�������" << endl;
			string name;
			cin >> name;

			bool flag = false;
			for(int i = 0; i < this->book_sum; i++) {
				if(this->book_array[i]->b_name == name) {
					flag = true;
					cout << "��ͼ����Ϣ���£�" << endl;
					this->book_array[i]->showInfo();
				}
			}
			if(flag == false) {
				cout << "����ʧ�ܣ������޴�����Ϣ" << endl;
			}
		} else {
			cout << "����ѡ������" << endl;
		}
	}

	system("pause");
	system("cls");
}

//����
void WorkerManager::borrowBook(){
	if(this->books_FileisEmpty) {
		cout << "ͼ����Ϊ�ջ򲻴���" << endl;
	} else {
		cout << "���������ķ�ʽ��" << endl;
		cout << "1����ͼ���Ų���" << endl;
		cout << "2������������" << endl;
		int select = 0;
		cin >> select;

		if(select == 1) {
			cout << "����������ͼ����" << endl;
			string id;
			cin >> id;
			int index = isExist(id);
			if(index != -1) {
				if(this->book_array[index]->b_state == 1){
					cout << "����ʧ�ܣ������ѽ������" << this->book_array[index]->r_id << endl;
					return;
				}				
				
				cout << "����������˱��" << endl;
				string id;
				cin >> id;
				this->book_array[index]->r_id = id;
				this->book_array[index]->b_state = 1;
				this->saveBookMenu();
				
				cout << "����ɹ�����ͼ����Ϣ���£�" << endl;
				this->book_array[index]->showInfo();
			} else {
				cout << "����ʧ�ܣ������޴�����Ϣ" << endl;
			}
		} else if(select == 2) {
			cout << "���������ͼ�������" << endl;
			string name;
			cin >> name;

			bool flag = false;
			for(int i = 0; i < this->book_sum; i++) {
				if(this->book_array[i]->b_name == name) {
					if(this->book_array[i]->b_state == 1){
						cout << "����ʧ�ܣ������ѽ������" << this->book_array[i]->r_id << endl;
						return;
					}					
					cout << "����������˱��" << endl;
					string id;
					cin >> id;
					this->book_array[i]->r_id = id;	
					this->book_array[i]->b_state = 1;				
					flag = true;
					this->saveBookMenu();
					
					cout << "����ɹ�����ͼ����Ϣ���£�" << endl;
					this->book_array[i]->showInfo();
				}
			}
			if(flag == false) {
				cout << "����ʧ�ܣ������޴�����Ϣ" << endl;
			}
		} else {
			cout << "����ѡ������" << endl;
		}
	}

	system("pause");
	system("cls"); 
} 

//����
void WorkerManager::returnBook(){
	cout << "������Ҫ����Ľ����˱�ţ�" << endl;
	string r_id;
	cin >> r_id;
	
	//ȷ�������ߴ���
	bool r_flag = false;
	for(int i = 0; i < this->book_sum; i++){
		if(this->book_array[i]->r_id == r_id){
			r_flag = true;
		}
	}
	if(!r_flag){
		cout << "�ö��߲����ڣ���������" << endl;
		system("pause");
		system("cls");
		return;
	} 
	
	//ȷ�������ߴ��ں󣬲���ͼ����Ϣ��ȷ���д˽��ļ�¼��ִ�л������ 
	bool b_flag = false;	
	
	cout << "�����������鼮��Ϣ��" << endl;
	cout << "1����ͼ����" << endl;
	cout << "2��������" << endl;
	int select = 0;
	cin >> select;  
	if(select == 1){
		cout << "�����������鼮ͼ���ţ�" << endl;
		string b_id;
		cin >> b_id; 
		
		for(int i = 0; i < this->book_sum; i++){
			if(this->book_array[i]->r_id == r_id){
				if(this->book_array[i]->b_id == b_id){
					this->book_array[i]->b_state = 0;
					this->book_array[i]->r_id = "-";
					this->saveBookMenu();
					
					b_flag = true;
					
					cout << "����ɹ�����ͼ����Ϣ���£�" << endl; 
					this->book_array[i]->showInfo();
					break;
				}
			}
		} 

		if(!b_flag){
			cout << "�ö����޴˽��ļ�¼" << endl;
		}
		
	} else if(select == 2){
		cout << "�����������鼮������" << endl;
		string b_name;
		cin >> b_name; 
		
		for(int i = 0; i < this->book_sum; i++){
			if(this->book_array[i]->r_id == r_id){
				if(this->book_array[i]->b_name == b_name){
					this->book_array[i]->b_state = 0;
					this->book_array[i]->r_id = "-";
					this->saveBookMenu();
					
					b_flag = true;
					
					cout << "����ɹ�����ͼ����Ϣ���£�" << endl; 
					this->book_array[i]->showInfo();
					break;
				}
			}
		} 

		if(!b_flag){
			cout << "�ö����޴˽��ļ�¼" << endl;
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
