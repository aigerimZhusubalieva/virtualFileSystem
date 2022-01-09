#include<iostream>
#include<ctime>
using namespace std;

template<typename T>
class vector{
	private:
		T *data;						
		int v_size;						
		int v_capacity;					
	public:
		vector();						
		vector(int cap);	
		~vector();					
		void push_back(T element);		
		void insert(int index, T element);
		T& at(int index); 				
		const T& front();				
		const T& back();				
		int size() const;				
		int capacity() const;			
		bool empty() const; 			
	};

template <typename T>
vector<T>::vector(){
	v_capacity = 0;
	v_size = 0;
}

template <typename T>
vector<T>::vector(int arg){
	v_capacity = arg;
	v_size = 0;
	data = new T[arg];
}

template <typename T>
vector<T>::~vector(){
	delete[] data;
}

template <typename T> 
void vector<T>::push_back(T elem){
	if (v_size != v_capacity){
		data[v_size] = elem;
	}else if (v_capacity == 0){
		data = new T[1];
		data[0] = elem;
		v_capacity = 1;
	}else{
		v_capacity *= 2;
		T* newArray = new T[v_capacity];
		T* temp = data;
		for (int i=0; i<v_size; i++){
			newArray[i] = data[i];
		}
		newArray[v_size] = elem;
		data = newArray;
		delete[] temp;
	}
	v_size++;
}

template <typename T>
void vector<T>::insert(int index, T elem){
	try{
		if(index>v_size || index<0){
			throw(OutOfRange());}
	}catch(OutOfRange()){}
	if(v_size==v_capacity){
		v_capacity *= 2;
		T* newArray = new T[v_capacity];
		for (int i=0; i<v_size+1; i++){ 
			if(i<index){
				newArray[i] = data[i];
			} else if(i==index){
				newArray[i] = elem;
			} else {
				newArray[i] = data[i-1];
			}
		}
		T* temp = data;
		data = newArray;
		delete[] temp;
		v_size++;
	} else {
		for (int i=v_size; i>index; i--){
			data[i] = data[i-1];
		}
		data[index] = elem;
		v_size++;
	}}


template <typename T>
T& vector<T>::at(int index){
	try{
		if(index>=v_size){
			throw(OutOfRange());
		}
	}catch(OutOfRange()){}	
	T& temp = data[index];
	return temp;
}

template <typename T>
const T& vector<T>::front(){
	T& temp = data[0];
	return temp;
}

template <typename T>
const T& vector<T>::back(){
	T& temp = data[v_size-1];
	return temp;
}

template <typename T>
int vector<T>::size() const{
	return v_size;
}

template <typename T>
int vector<T>::capacity() const{
	return v_capacity;
}

template <typename T>
bool vector<T>::empty() const{
	return(size()==0);
}


class inode{
	private:
		string name;
		string date;
		int size = 10;
		bool isFile;
		inode parent; //???
	
	public:
		inode(string name, bool file, int size);
		inode(string name, bool fime);
		string return_name() const;
};

inode::inode(string n, int s){
	name = n;
	size = s;
	isFile = true;
	time_t timez = time(0); //get current time on the current system
	date = ctime(&timez); 
}

inode::inode(string n){
	name = n;
	isFile = false;
	time_t timez = time(0); //get current time on the current system
	date = ctime(&timez); 
}

string inode::return_name()const{
	return("/"+name+" "+date);
}

template <typename T>
class Position<T>{
	public:
		T& operator*();
		Position parent() const;
		PositionList children() const;
		bool isRoot() const;
		bool isExternal() const;
}

template <typename T>
class Tree<T>{
	public: 
		class Position;
		class PositionList;
	public:
		int size() const;
		bool empty() const;
		Position root() const;
		PositionList positions() const;
}

int main(){
	inode help = inode("woah", true, 13);
	cout<<help.return_name()<<endl;
	return 0;
}