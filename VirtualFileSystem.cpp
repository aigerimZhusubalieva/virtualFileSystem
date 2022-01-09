#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<ctime>
#include <stdexcept>

using namespace std;

template <typename T>
class vector{  							//vector adt
	private:
		T* data; 						//array containing the elements
		int v_size;
		int v_cap;
	public:
		vector();
		~vector();
		void push_back(T element);
		void remove(T element); 		//find and remove the element
		int size() const;
		bool empty() const;
		T& remove(T element); 			//remove the element from the vector
};

template <typename T>
class queue{  //queue adt
	private:

	public:
		
};

string get_time(){  //function based off of https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
	time_t now = time(0);
	tm* ct = localtime(&now);
	string newTime = to_string(ct->tm_mday) + "-" +to_string(1+ct->tm_mon) + "-" + to_string(1900+ct->tm_year);
	return newTime;
}

class inode{
	private:
		string name;
		string date;
		int isize;
		bool isFile;
		bool isRoot;
		inode* parent;
		vector<inode*> children ;
	public:
		inode(inode* p, string name); 			//consutructor of a folder
		inode(inode* p, string name, int isize);   //constructor of a file
		inode();  //constructor of the root
		//~inode(); 						//desctructor
		int total_size();			    //calc the total size of a node
		string get_path();				//get path of a node (its parents until we reach the root)
		void add_child(inode* child);
		friend myTree;
};

class myTree{
	private:
		inode* root;
		queue trash; 					//trash can basically

	public:
		myTree();
		~myTree();
		void mkdir(); 					//create a folder
		void touch(); 					//create a file
		bool doesExist();   			//find if a node exists
		inode findPath();   			//find path of a node
		void mv(); 						//move a file
		bool isChild(); 				//check if an inode is a child of a given node
};

inode::inode(inode* p, string n){ //WORK ON FIXING HTE DATE
	name = n;
	isize = 10;
	isFile = false;
	isRoot = false;
	date = get_time();
	parent = p;
}

inode::inode(inode* p, string n, int s){
	name = n;
	isize = s;
	isFile = true;
	isRoot = false;
	date = get_time();
	parent = p;
}

inode::inode(){
	name = "root";
	isize = 0;
	isFile = false;
	isRoot = true;
	date = get_time();
}

int inode::total_size(){
	if(isFile) {
		return isize;
	}
	else if(children.size() == 0) {
		return isize;
	}
	else{
		int total= isize;
		for(int i = 0; i<children.size(); i++){
			total += children.at(i)->total_size();
		}
		return total;
	}
}

string inode::get_path(){
	string path;
	if(isRoot) return "/";
	else if (!isFile) path = parent->get_path() + name + "/";
	else if (isFile) path = parent->get_path() + name;
	return path;
}

void inode::add_child(inode* child){
	children.push_back(child);
}