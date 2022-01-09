#include<iostream>
#include<ctime>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;

class inode;
class MyTree;

//vector template
template <typename T>
class vector
{
	private:
		T *data;						
		int v_size;						
		int v_capacity;					
	public:
		vector();						
		vector(int cap);
		~vector();					
		void push_back(T element);		
		T& at(int index); 			
		int size() const;	
		void erase(int index);
};

template <typename T>
vector<T>::vector()
{
	v_size=0;
	v_capacity=0;
}

template <typename T>
vector<T>::vector(int cap)
{
	v_size=0;
	v_capacity=cap;
	data = new T[v_capacity];
}

template <typename T>
vector<T>::~vector()
{
	delete[] data;
}

template <typename T>
int vector<T>::size() const
{
	return v_size;
}

template <typename T>
void vector<T>::push_back(T element)
{

	if(v_size==0)							
	{
		v_capacity=1;
		data = new T[v_capacity];
	}
	else if(v_size==v_capacity)
	{
		v_capacity = v_capacity*2;					
		T *data2=new T[v_capacity];				

		for(int i=0; i<v_size; i++)	
			data2[i]=data[i];

		delete[] data;	

		data = data2;	

	}
	data[v_size++]=element; 
}

template <typename T>
T& vector<T>::at(int index)
{
	if(index>=0 and index<v_size)
		return data[index];
	else 
		 throw out_of_range("Vector Index out of range...!");
}

template <typename T>
void vector<T>::erase(int index){
	for (int i = index+1; i<v_size; i++){
		data[i-1] = data[i];	
	}
	v_size--;
}

//queue template 
template <typename T>
class Queue
{
	private:
		T *array;
		int n;	//number of current elements in the Queue
		int N;	//Array Size (Capacity)
		int f;	//index of front element
		int r;	//index where a new element will be added
	public:
		Queue(int cap);
		~Queue();
		void enqueue(T);
		T dequeue();
		T front();
		bool isEmpty();
		bool isFull();
		void display();
};

template <typename T> 
Queue<T>::Queue(int cap){
	array = new T[N];
	n = 0;
	N = cap;
	f = 0;
	r = 0;
}

template <typename T> 
Queue<T>::~Queue(){
	delete[] array;
}

template <typename T> 
void Queue<T>::enqueue(T t){
	array[r] = t;
	n++;
	r = (r+1)%N;
}

template <typename T> 
T Queue<T>::dequeue(){
	T temp = array[f];
	f = (f+1)%N;
	n--;
	return temp;
}

template <typename T> 
T Queue<T>::front(){
	if (isEmpty()){cout<<"bin is empty"<<endl;}
	return array[f];
}

template <typename T> 
bool Queue<T>::isEmpty(){
	return(n==0);
}

template <typename T> 
bool Queue<T>::isFull(){
	return(n==N);
}

//function to get current time and format it
string get_time() {  //function based off of https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
	time_t now = time(0);
	tm* ct = localtime(&now);
	string newTime = to_string(ct->tm_mday) + "-" +to_string(1+ct->tm_mon) + "-" + to_string(1900+ct->tm_year);
	return newTime;
}

//helper function to check if a character is in a string
bool isin(string big, char ch){
	for (int i = 0; i<big.size(); i++){
		if(big[i] == ch) return true;
	}
	return false;
}

//class of the tree
class myTree{
	private:
		inode* root; 														//pointer to the root of the tree
		Queue<inode*> bin = Queue<inode*>(10);								//queue of size 10
		inode* current;														//pointer to current directory
		inode* prev;														//pointer to the previous directory

	public:
		myTree();															//constructor
		void mkdir(string folder_name); 					                //create a folder
		void touch(string file_name, string file_size); 					//create a file
		string pwd();   			                                        //find path of a current node
		void mv(string& file_name, string& folde_rname);					//move a file to given folder
		bool isChild(inode* p, inode* c); 									//check if an inode is a child of a given node
		bool empty();														//check if the tree is empty
		void ls();															//print chidlren of the current inode
		void find_helper(string& to_find); 									//helper for the find functoin
		vector<inode*>* find(vector<inode*>* recurrences, string& to_find, inode* start); //find and return all recurrences of a given node
		void cd(string& arg1); 												//change directory from current inode to given inode
		inode* cd_path(inode* parent, string& path);						//cd helper
		void realpath(string& to_find);										//print full path of a file, given that it is child of the current inode
		void size(string& to_find);											//find the size of a file/node, give that it is child of the current inode
		void rm(string& to_remove);											//move given inode from the tree to the bin
		void showbin();														//show the oldest inode in the bin
		void emptybin();													//empty the bin
		void loadData(string sourcename);									//load files to the system
		void dumpline(inode* crnt, ofstream& sourcefile);					//helper of exit
		void exit();														//dump data to a file and quit exit the system

};

class inode{
	private:
		string name;														//name of the inode
		string cdate;														//date of inode creation
		int isize;															//size of the individual inode
		bool isFile;														//boolean indicating if an inode is a file or folder
		bool isRoot;														//boolean indicating if an inode is a root
		inode* parent;														//pointer to the parent of the inode
		vector<inode*> children ;											//vector containing pointers to the children of the inode
	public:
		inode(inode* p, string n, int s, string d);							//constructor for inode when loaded from the file
		inode(inode* p, string name); 										//consutructor of a folder
		inode(inode* p, string name, int isize);   							//constructor of a file
		inode();  															//constructor of the root
		~inode(); 															//desctructor
		int total_size();			 									    //calc the total size of a node
		string get_path();													//get path of a node (its parents until we reach the root)
		void add_child(inode* child);										//add a pointer of a new child to the vector of children of the node
		void remove_child(inode* child);									//remove pointer of a child from the vector of children of the node
		string print();														//display the inode information
		inode* find_child(string& to_find);									//return pointer to the child of an inode if found
		friend myTree;
};

inode::inode(inode* p, string n, int s, string d){
	name = n;
	isize = s;
	isFile = isin(n, '.');
	isRoot = false;
	parent = p;
	cdate = d;
}

inode::inode(inode* p, string n){
	name = n;
	isize = 10;
	isFile = false;
	isRoot = false;
	parent = p;
	cdate = get_time();
}

inode::inode(inode* p, string n, int s){
	name = n;
	isize = s;
	isFile = true;
	isRoot = false;
	parent = p;
	cdate = get_time();
}

inode::inode(){
	name = "/";
	isize = 0;
	isFile = false;
	isRoot = true;
	cdate = get_time();

}

inode::~inode(){
	delete parent;
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
	if(isRoot) return name;
	else if (!isFile) path = parent->get_path() + name + "/";
	else if (isFile) path = parent->get_path() + name;
	return path;
}

void inode::add_child(inode* child){
	children.push_back(child);
}

void inode::remove_child(inode* child){
	for(int i = 0; i<children.size(); i++){
		if(children.at(i)->name == child->name){
			children.erase(i);
		}
	}
}

string inode::print(){
	string to_print = "";
	string lsize = to_string(total_size());
	if(isFile) to_print += "file ";
	else to_print += "dir ";
	to_print += name + " " + cdate;
	//to_print += to_print + " " +lsize + "bytes";  adding these strings caused the name to display weirdly on my laptop but please try uncommenting
	return(to_print);
}

inode* inode::find_child(string& to_find){
	if (children.size()!=0){
		for(int i = 0; i<children.size(); i++){
			if(children.at(i)->name == to_find){
				return children.at(i);
			}
		}
	}
	return NULL;
}

myTree::myTree(){
	root = new inode();
	current = root;
	prev = root;
}

void myTree::mkdir(string folder_name){
	for(int i = 0; i<folder_name.size(); i++){
		if(!isalnum(folder_name[i])){
			cout<<"invalid folder name"<<endl;
			return;
		}
	}
	for(int i = 0; i<current->children.size(); i++){
		if(current->children.at(i)->name == folder_name){
			cout<<folder_name<<" already exists."<<endl;
			return;
		}
	}
	inode* new_folder = new inode(current, folder_name);
	current->add_child(new_folder);
}

void myTree::touch(string file_name, string file_size){
	for(int i = 0; i<file_name.size(); i++){
		if(! (isalnum(file_name[i]) || file_name[i] == '.') ){
			cout<<"invalid file name"<<endl;
			return;
		}
	}
	int s;
	try{
		s = stoi(file_size);
		for(int i = 0; i<current->children.size(); i++){
			if(current->children.at(i)->name == file_name){
				cout<<file_name<<" already exists."<<endl;
				return;
			}
		}
		inode* new_file = new inode(current, file_name, s);
		current->add_child(new_file); 
	}catch(...){
		cout<<"wrong format of the file size."<<endl;
		return;
	}
}

bool myTree::empty(){
	if(root->children.size()==0) return true;
	else return false;
}

bool myTree::isChild(inode* p, inode* c){
	return (p == c->parent);
}

string myTree::pwd(){
	return (current->get_path());
}

void myTree::ls(){
	inode* cchild;
	if(!current->isFile && current->children.size() != 0){
		string to_print;
		for (int i=0; i<current->children.size(); i++){
			cchild = current->children.at(i);
			to_print += cchild->print() + "\n";
		}
		cout<<to_print;
	}
}

void myTree::realpath(string& to_find){
	inode* node = current->find_child(to_find);
	if(node!=NULL) {
		if(node->isFile) cout<<node->get_path()<<endl;
		else cout<<"file "<<to_find<<" not found"<<endl;
	}
	else cout<<"file "<<to_find<<" not found"<<endl;
}

void myTree::cd(string& arg1){
	inode* temp = current;
	if(arg1 == "cd") current = root;
	else if(arg1 == ".." && current != root) current = current->parent;
	else if(arg1 == "-") current = prev;
	else if(arg1.substr(0, 1) == "/") {
		arg1 = arg1.substr(1);
		inode* t = cd_path(current, arg1);
		if(t == NULL) cout<<"directory not found"<<endl;
		else current = t;
	}
	else{
		inode* t = current->find_child(arg1);
		if(t==NULL) cout<<"directory not found"<<endl;
		else if(t->isFile){
			cout<<"directory not found"<<endl;
		} else current = t;
	}
	prev = temp;
}

inode* myTree::cd_path(inode* parent, string& path){
	string folder_name = path.substr(0, path.find("/"));
	inode* node = parent->find_child(folder_name);
	path = path.substr(path.find("/")+1);
	if(node == NULL) return node;
	if(folder_name != path){
		node = cd_path(node, path);
	}
	return node;
}
	
void myTree::find_helper(string& to_find){
	vector<inode*> recurrences;
	find(&recurrences, to_find, root);
	for (int i = 0; i<recurrences.size(); i++){
		cout<<recurrences.at(i)->get_path()<<endl;
	}
}

vector<inode*>* myTree::find(vector<inode*>* recurrences, string& to_find, inode* start){
	inode* temp;
	if(start->name==to_find) recurrences->push_back(start);
	if(start->children.size()!=0){
		for(int i=0; i<start->children.size(); i++){
			recurrences = find(recurrences, to_find, start->children.at(i));
		}
	}
	return recurrences;
}

void myTree::mv(string& file_name, string& folder_name){
	inode* file = current->find_child(file_name);
	inode* folder = current->find_child(folder_name);
	if(folder != NULL && file != NULL){
		if (file->isFile && !folder->isFile){
			file->parent->remove_child(file);
			folder->add_child(file);
			file->parent = folder;
		}else cout<<"file and/or folder not found"<<endl;
	}else cout<<"file and/or folder not found"<<endl;
}

void myTree::size(string& to_find){
	inode* node = current->find_child(to_find);
	if(node!=NULL) cout<<"Size of "<<node->name<<": "<<node->total_size()<<endl;
	else cout<<"file or folder "<<to_find<<" not found"<<endl;
}

void myTree::rm(string& to_remove){
	inode* node = current->find_child(to_remove);
	if(node==NULL) cout<<to_remove<<" not found"<<endl;
	else{
		if(!bin.isFull()){
			bin.enqueue(node);
			current->remove_child(node);
		} else cout<<"couldn't remove: bin is full. empty bin first."<<endl;
	}
}

void myTree::showbin(){
	if(bin.isEmpty()) cout<<"bin is empty"<<endl;
	else{
		inode* node = bin.front();
		cout<<node->get_path()<<endl;
	}
}

void myTree::emptybin(){
	inode* t;
	while(!bin.isEmpty()){
		t = bin.dequeue();
		cout<<t->name<<" deleted permanently"<<endl;
	}
}

void myTree::loadData(string sourcename){
	ifstream sourcefile(sourcename);
	inode* node;
	if(sourcefile.is_open()){
		string p;
		string s;
		string d;
		while(!sourcefile.eof()){
			getline(sourcefile, p, ',');
			getline(sourcefile, s, ',');
			getline(sourcefile, d, '\n');
	
			if(p == "/") root->cdate = d;
			else{
				inode* new_node;
				vector<string> path;
				string temp = "";

				current = root;

				for(int i=1; i<=p.size(); i++){
					if(p[i] == '/' || i==p.size()){
						path.push_back(temp);
						temp = "";
					}
					else temp+=p[i];
				}

				for(int i = 0; i<path.size(); i++){
					node = current->find_child(path.at(i));
					if (node==NULL){
						new_node = new inode(current, path.at(i), stoi(s), d);
						current->add_child(new_node);
					}
					current = node;
				}
			}
		}
		current = root;
		sourcefile.close();
	}
}

void myTree::dumpline(inode* crnt, ofstream& sourcefile){
	for(int i = 0; i < crnt->children.size(); i++){
		sourcefile<<crnt->children.at(i)->parent->get_path()<<crnt->children.at(i)->name<<","<<crnt->children.at(i)->isize<<","<<crnt->children.at(i)->cdate<<endl;
		dumpline(crnt->children.at(i), sourcefile);
	}
}

void myTree::exit(){
	ofstream sourcefile("vfs.dat");
	if(sourcefile.is_open()){
		sourcefile<<"/,"<<root->isize<<","<<root->cdate<<endl;
		dumpline(root, sourcefile);
		sourcefile.close();
	}
}


//display available commands
void help()   
{
	cout<<endl
		<<"           LIST OF AVAILABLE COMMANDS"<<endl
		<<"*words starred represent user input"<<endl
		<<endl
		<<" help                         print available commands"<<endl
		<<" pwd                          print current path"<<endl
		<<" realpath *filename*          print path of a file"<<endl
		<<" ls                           print folders/files in current directory"<<endl
		<<" mkdir *foldername*           a new FOLDER in current directory"<<endl
		<<" touch *filename size*        create a new FILE in current directory"<<endl
		<<" cd                           change the current directory"<<endl
		<<" find *folder/filename*       find and print a folder/file path"<<endl
		<<" mv *filename foldername*     move a folder/file"<<endl
		<<" rm *filename foldername*     remove a folder/file"<<endl
		<<" size *filename/foldername*   print size of a folder/file"<<endl
		<<" emptybin                     empty the bin"<<endl
		<<" showbin                      show the bin"<<endl
		<<" exit                         exit the Program"<<endl;
}

int main(){
	myTree directory = myTree();   		        //instantiate the directory
	string user;                    			//user input
	string command, argument1, argument2;		//break down user input
	directory.loadData("vfs.dat");              //upload files
	help();

	while(true){
		cout<<directory.pwd()<<" ";
		getline(cin, user);
		//break down user input
		command = user.substr(0, user.find(" "));
		argument1 = user.substr(user.find(" ")+1);
		argument2 = argument1.substr(argument1.find(" ")+1);
		argument1 = argument1.substr(0, argument1.find(" "));

		     if(command == "help")     help();
		else if(command == "pwd")      cout<<directory.pwd()<<endl; 
		else if(command == "ls")       directory.ls(); 
		else if(command == "mkdir")    directory.mkdir(argument1);
		else if(command == "touch")    directory.touch(argument1, argument2);
		else if(command == "size")     directory.size(argument1); 
		else if(command == "realpath") directory.realpath(argument1);
		else if(command == "cd")       directory.cd(argument1);
		else if(command == "mv")       directory.mv(argument1, argument2);
		else if(command == "rm")       directory.rm(argument1);
		else if(command == "find")     directory.find_helper(argument1);
		else if(command == "emptybin") directory.emptybin(); 
		else if(command == "showbin")  directory.showbin();
		else if(command == "exit")     {directory.exit(); break;}
		else cout<<"Command not available"<<endl;
		
	}
	return 0;
}