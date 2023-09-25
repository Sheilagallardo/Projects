#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<list>
#include<algorithm>
using namespace std;


class Products{
	private:
		int id;
		string name;
		float price;
		
	public:
		//Default
		Products(){
			id=0;
			name="";
			price=0.00;
		}
		
		//Parametrized
		Products(int ID, string NAME, float PRICE){
			id=ID;
			name=NAME;
			price=PRICE;
		}
		int getid(){
			return id;
		}
		string getName(){
			return name;
		}
		float getprice(){
			return price;
		}
};

class Employee {
	protected:
		string name;
		int id;
		string address;
		int telephone;
		float salary;
		string type;
	public: 
	/* DEFAULT CONSTRUCTOR */
	Employee(){
		name = "";
		id = 0;
		address = "";
		telephone = 0;
		salary = 0;
		type = "";
	}
	
	/* PARAMETRIZED CONSTRUCTOR */
	Employee(string NAME, int ID, string ADDRESS, int TELEPHONE, float SALARY, string TYPE){
		name = NAME;
		id = ID;
		address = ADDRESS;
		telephone = TELEPHONE;
		salary = SALARY;
		type = TYPE;
	}
	string getName(){
		return name;
	}
	int getid(){
		return id;
	}
	string getaddress(){
		return address;
	}
	int gettelephone(){
		return telephone;
	}
	float getsalary(){
		return salary;
	}
	string gettype(){
		return type;
	}
};


class CCEmployee: public Employee{
	private:
	string occupation;
	public:
    /* DEFAULT CONSTRUCTOR */
    CCEmployee(): Employee(){
 	this ->occupation = "";
    }
 
    /* PARAMETERIZED CONSTRUCTOR */
    CCEmployee(string NAME, int ID, string ADDRESS, int TELEPHONE, float SALARY, string TYPE, string OCCUPATION):Employee(NAME, ID, ADDRESS, TELEPHONE, SALARY, TYPE){
    	this -> occupation = OCCUPATION;
    }
    string getoccupation(){
    	return occupation;
	}
};
		
class StoreEmployee: public Employee{
	private:
	string status;
	public:
	/*DEFAULT CONSTRUCTOR*/
	StoreEmployee(): Employee(){
		this -> status = "";
	}
	/*PARAMETERIZED CONSTRUCTOR*/
	StoreEmployee(string NAME, int ID, string ADDRESS, int TELEPHONE, float SALARY, string TYPE, string STATUS):Employee(NAME, ID, ADDRESS, TELEPHONE, SALARY, TYPE){
		this -> status = STATUS;
	}
	string getstatus(){
		return status;
	}
};

		
class Store{
	private:
		string name;
		int id;
		string area;
		vector<StoreEmployee> vEmployeesStore;
		vector<Products> catalogue;
		string status;
		
	public:
		/* DEFAULT CONSTRUCTOR */
		Store(){
			name = "";
			id = 0;
			area = "";
			vEmployeesStore = {};
			catalogue = {};
			status = "";
		}
		
		/* PARAMETRIZED CONSTRUCTOR */
		
		Store(string NAME, int ID, string AREA, vector<class StoreEmployee> VEMPLOYEESSTORE, vector<class Products> CATALOGUE, string STATUS){
			name = NAME;
			id = ID;
			area = AREA;
			vEmployeesStore = VEMPLOYEESSTORE;
			catalogue = CATALOGUE;
		
			if (STATUS == "Closed" || STATUS == "Open"){
			
				status = STATUS;
			}else{
				throw "Invalid status";
			}
		}
	string getName(){
		return name;
	}
	int getid(){
		return id;
	}
	string getarea(){
		return area;
	}
	vector<StoreEmployee> getemployees(){
		return vEmployeesStore;
	}
	vector<Products> getcatalogue(){
		return catalogue;
	}
	string getstatus(){
		return status;
	}
	void setcatalogue(vector<Products>vect){
		this -> catalogue = vect;
	}
};
		

class CityCenter{
	private:
		string name;
		string address;
		int parkingplaces;
		vector<class Store> vStores;
		vector<class CCEmployee> vCCEmployees;
		
	public:
		//DEFAULT
		CityCenter(){
			name=" ";
			address=" ";
			parkingplaces=0;
			vStores = {};
			vCCEmployees = {};
		
		}
				
		//PARAMETRIZED
		CityCenter(string NAME, string ADDRESS, int PARKING, vector<class Store> VSTORES, vector<class CCEmployee> VCCEMPLOYEES){
			name=NAME;
			address=ADDRESS;
			parkingplaces=PARKING;
			vStores=VSTORES;
			vCCEmployees=VCCEMPLOYEES;
		}
		string getName(){
			return name;
		}
		string getaddress(){
			return this -> address;
		}
		int getparkingplaces(){
			return parkingplaces;
		}
		vector<Store> getstores(){
			return vStores;
		}
		vector<CCEmployee> getemployeescc(){
			return vCCEmployees;
		}
		void setstores(vector<Store> vt){
			this -> vStores = vt;
		}
};

/* FUNCTIONS:*/

CityCenter readInitialData (string StoresInfo);
list <pair<string,string>> getAllEmployees(CityCenter CENTER);
void showAllEmployees (list<pair<string,string>>);
void showStorePriceGivenProduct(CityCenter CENTER);
void addProductInStore (CityCenter &CENTER);
void removeProductInStore (CityCenter &CENTER);
void showAllInformation (CityCenter CENTER);
void saveAllInformation (CityCenter CENTER);
int showMenu();


int main(){
	
CityCenter CENTER = readInitialData("Stores.txt");
int c = 0;
list <pair<string,string>> List = getAllEmployees(CENTER);

while(c==0){
	int op = showMenu();
	switch(op){
		case 1:
			showAllEmployees(List);
			break;
		case 2:
				showStorePriceGivenProduct(CENTER);
				break;
		case 3:
			addProductInStore (CENTER);
			break;
		case 4:
			removeProductInStore (CENTER);
			break;
		case 5:
			showAllInformation (CENTER);
			break;
		case 6:
			saveAllInformation(CENTER);
			break;
		case 7:
			cout<<"Bye!"<<endl;
			c=1;
			break;
		default:
			cout<<"The number is not valid. TRY AGAIN"<<endl;
	}
}
	return 0;

};


/* readInitialData */

CityCenter readInitialData (string StoresInfo){
	
	string name, area, status,x,nameP,nameE,addressE,statusE,type,address,occupationE;
	int id,idP,idE,telephoneE,parking;
	float priceP,salaryE;
	vector<Products>catalogue;
	vector<StoreEmployee>employees;
	vector<Store>Stores;
	vector<CCEmployee>employees_citycenter;
	CityCenter Center;
	
	ifstream STORES;
	STORES.open(StoresInfo);
	if (!STORES.good()){
		cout<<"Cannot open file"<<endl;
		exit(1);
	}else{
	while(!STORES.eof()){
		getline(STORES, x);
		while(x=="**Store"){
			employees.clear();
			catalogue.clear();
			getline(STORES, name);
			STORES>>id;
			STORES.ignore();
			getline(STORES, area);
			getline(STORES, status);
	        getline(STORES, x);
					
			while(x == "**Product"){
				STORES>>idP;
				STORES.ignore();
				getline(STORES, nameP);
				STORES>>priceP;
				STORES.ignore();
				Products product(idP, nameP, priceP);
				catalogue.push_back(product);
				getline(STORES,x);
			}
		
	    	while(x == "**Employee"){
				getline(STORES, nameE);
				STORES>>idE;
				STORES.ignore();
				getline(STORES, addressE);
				STORES>>telephoneE;
				STORES.ignore();
				STORES>>salaryE;
				STORES.ignore();
				getline(STORES, statusE);
				type = "Store";
				StoreEmployee employee(nameE,idE,addressE,telephoneE,salaryE,type,statusE);
				employees.push_back(employee);
				getline(STORES,x);
			}		
		 	Store st(name,id,area,employees,catalogue,status);
	    	Stores.push_back(st);
	}

	if(x=="**CityCenter"){
		getline(STORES, name);
		getline(STORES, address);
		STORES>>parking;
		STORES.ignore();
		
		getline(STORES, x);
		while(x == "**Employee"){
			getline(STORES, nameE);
			STORES>>idE;
			STORES.ignore();
			getline(STORES, addressE);
			STORES>>telephoneE;
			STORES.ignore();
			STORES>>salaryE;
			STORES.ignore();
			getline(STORES, occupationE);
			type = "CityCenter";
			CCEmployee ccEmployees(nameE,idE,addressE,telephoneE,salaryE,type,occupationE);
			employees_citycenter.push_back(ccEmployees);
			getline(STORES,x);
		}
	
	}
	} 
	CityCenter Center(name,address,parking,Stores,employees_citycenter);
	return Center;
}
	STORES.close();
}

/*getAllEmployees*/

list <pair<string,string>> getAllEmployees(CityCenter CENTER){
	vector<CCEmployee> vect = CENTER.getemployeescc();	
	vector<Store> stv = CENTER.getstores();
	list<pair<string,string>> List;
	for(CCEmployee i: vect){
		CCEmployee emp = i;
		pair<string,string> p (emp.getName(),emp.gettype());
		List.push_back(p);		
	}
	
	for(Store i:stv){
		Store store = i;
		vector<StoreEmployee>storee = store.getemployees();
		
		for(StoreEmployee i: storee){
			StoreEmployee s = i;
			pair<string,string> p (s.getName(),s.gettype());
			List.push_back(p);
		}
}

 	List.sort();
	return List;
}


//ShowAllEmployees//

void showAllEmployees (list<pair<string,string>>List){
	cout<<"EMPLOYEE NAME"<<"\t"<<"WORKPLACE"<<endl;
	cout<<"............................"<<endl;
	for(pair<string,string> i:List){
	pair<string,string> p = i;
	cout<<p.first<<"\t\t"<<p.second<<endl;
}
}


// showStorePriceGivenProduct //
void showStorePriceGivenProduct(CityCenter CENTER){
	string p;
	vector<Store> stv = CENTER.getstores();
	list<pair<string,float>> Lista;
	cout<<"Product Name: ";
	cin>>p;
	cout<<endl;
	
	for(Store i:stv){
		Store store = i;
		vector<Products> pro = store.getcatalogue();
		for(Products i:pro){
			Products produ = i;
			string pname = produ.getName();
			transform(pname.begin(), pname.end(),pname.begin(), ::toupper);
			transform(p.begin(), p.end(),p.begin(), ::toupper);
			if(pname== p){
				pair<string,float> Pair(store.getName(),produ.getprice());
				Lista.push_back(Pair);
			}
		}
	}
	cout<<"STORE"<<"\t\t"<<"PRICE"<<endl;
	cout<<"......................"<<endl;
	for(pair<string,float> i:Lista){
	pair<string,float> Pair = i;
	cout<<Pair.first<<"\t\t"<<Pair.second<<endl;
}
}

// addProductInStore //
void addProductInStore (CityCenter &CENTER){
	vector<Store> stv = CENTER.getstores();
	vector<Store> v;
	string t,n;
	int d,c;
	float f;
	cout<<"Store: ";
	cin>>t;
	cout<<"Name of product: ";
	cin>>n;
	cout<<"Id of product: ";
	cin>>d;
	cout<<"Price of product: ";
	cin>>f;
	
	for(Store i:stv){
		Store sto = i;
		string nst = sto.getName();
		transform(nst.begin(), nst.end(),nst.begin(), ::toupper);
		transform(t.begin(), t.end(),t.begin(), ::toupper);
		
		if(nst==t){
			vector<Products> pro = sto.getcatalogue();
		
		for(Products i:pro){
			Products produ = i;
			string pname = produ.getName();
			string n2 = n;
			transform(pname.begin(), pname.end(),pname.begin(), ::toupper);
			transform(n2.begin(), n2.end(),n2.begin(), ::toupper);
			if(pname== n2){
				c=1;	
			} 
		}
		if(c==0){
				Products newproduct(d,n,f);
				pro.push_back(newproduct);
				sto.setcatalogue(pro);
			}else if (c=1){
				cout<<"The product is already in the shop"<<endl;
			}
		}
		v.push_back(sto);
	}
	
	CENTER.setstores(v);
	
}


//removeProductInStore//
void removeProductInStore (CityCenter &CENTER){
	vector<Store> stv = CENTER.getstores();
	vector<Store> v;
	vector<Products> y;
	string t;
	int d;
	int c=0;
	cout<<"Store: ";
	cin>>t;
	cout<<"Id of product: ";
	cin>>d;
	
	
	for(Store i:stv){
		Store sto = i;
		string nst = sto.getName();
		transform(nst.begin(), nst.end(),nst.begin(), ::toupper);
		transform(t.begin(), t.end(),t.begin(), ::toupper);
		
		if(nst==t){
			vector<Products> pro = sto.getcatalogue();
		
		for(Products i:pro){
			Products produ = i;
			int id = produ.getid();
			if(id!=d){
				y.push_back(produ);
			}
		}
		sto.setcatalogue(y);
	}
	v.push_back(sto);
	}
	CENTER.setstores(v);
}			

//showAllInformation//
void showAllInformation (CityCenter CENTER){
	vector<CCEmployee> ccemployee = CENTER.getemployeescc();
	vector<Store> tiendas = CENTER.getstores();
	
	cout<<"CITY CENTER INFORMATION: "<<endl<<endl;
	cout<<"\t"<<"NAME: "<<CENTER.getName()<<endl;
	cout<<"\t"<<"ADDRESS: "<<CENTER.getaddress()<<endl;
	cout<<"\t"<<"PARKING PLACES: "<<CENTER.getparkingplaces()<<endl<<endl;
	cout<<"CITY CENTER EMPLOYEES: "<<endl;
	
	for(CCEmployee i: ccemployee){
		CCEmployee e = i;
		cout<<"\n"<<"\t"<<"NAME: "<< e.getName()<<endl;
		cout<<"\t"<<"ID: "<<e.getid()<<endl;
		cout<<"\t"<<"ADDRESS: "<<e.getaddress()<<endl;
		cout<<"\t"<<"TELEPHONE: "<<e.gettelephone()<<endl;
		cout<<"\t"<<"SALARY: "<<e.getsalary()<<endl;
		cout<<"\t"<<"OCCUPATION: "<<e.getoccupation()<<endl;
	} 
	
	cout<<"\n"<<"STORES: "<<endl;
	for(Store i: tiendas){
		Store q = i;
		cout<<"\n"<<"NAME OF STORE: "<<q.getName()<<endl;
		cout<<"ID OF STORE: "<<q.getid()<<endl;
		cout<<"AREA OF STORE: "<<q.getarea()<<endl;
		cout<<"STATUS OF STORE: "<<q.getstatus()<<endl;
		
		cout<<"\n"<<"STORE EMPLOYEES: "<<endl<<endl;
		vector<StoreEmployee> storeemployee = q.getemployees();
		for (StoreEmployee i: storeemployee){
			StoreEmployee se = i;
			cout<<"\t"<<"NAME OF EMPLOYEE: "<<se.getName()<<endl;
			cout<<"\t"<<"ID OF EMPLOYEE: "<<se.getid()<<endl;
			cout<<"\t"<<"ADDRESS OF EMPLOYEE: "<<se.getaddress()<<endl;
			cout<<"\t"<<"TELEPHONE OF EMPLOYEE: "<<se.gettelephone()<<endl;
			cout<<"\t"<<"SALARY OF EMPLOYEE: "<<se.getsalary()<<endl;
			cout<<"\t"<<"STATUS OF EMPLOYEE: "<<se.getstatus()<<endl;
			cout<<endl;
		}
		
		cout<<"CATALOGUE OF STORE: "<<endl<<endl;
		vector<Products>storeproducts = q.getcatalogue();
		
		for (Products i: storeproducts){
			Products p = i;
			cout<<"\t"<<"NAME OF PRODUCT: "<<p.getName()<<endl;
			cout<<"\t"<<"ID OF PRODUCT: "<<p.getid()<<endl;
			cout<<"\t"<<"PRICE OF PRODUCT: "<<p.getprice()<<endl;
			cout<<endl;
		}
	}
}

// saveAllInformation //
void saveAllInformation (CityCenter CENTER){
	ofstream outfile;	
	outfile.open("output.txt");
	vector<Store>tiendas = CENTER.getstores();
	
	vector<CCEmployee> ccempleados = CENTER.getemployeescc();
	
		for(Store i: tiendas){
		Store a = i;
		outfile<<"**Store"<<endl;
		outfile<<a.getName()<<endl;
		outfile<<a.getid()<<endl;
		outfile<<a.getarea()<<endl;
		outfile<<a.getstatus()<<endl;
		
		vector<Products>productos = a.getcatalogue();
		
		for(Products i: productos){
			Products b = i;
			outfile<<"**Product"<<endl;
			outfile<<b.getid()<<endl;
			outfile<<b.getName()<<endl;
			outfile<<b.getprice()<<endl;	
		}
		
		vector<StoreEmployee> empleados = a.getemployees();
		
		for(StoreEmployee i: empleados){
			StoreEmployee c = i;
			outfile<<"**Employee"<<endl;
			outfile<< c.getName()<<endl;
			outfile<<c.getid()<<endl;
			outfile<<c.getaddress()<<endl;
			outfile<<c.gettelephone()<<endl;
			outfile<<c.getsalary()<<endl;
			outfile<<c.getstatus()<<endl;
		}
	} 
	
		outfile<<"**CityCenter"<<endl;
		outfile<<CENTER.getName()<<endl;
		outfile<<CENTER.getaddress()<<endl;
		outfile<<CENTER.getparkingplaces()<<endl;
		
		for(CCEmployee i: ccempleados){
			CCEmployee d = i;
			outfile<<"**Employee"<<endl;
			outfile<< d.getName()<<endl;
			outfile<<d.getid()<<endl;
			outfile<<d.getaddress()<<endl;
			outfile<<d.gettelephone()<<endl;
			outfile<<d.getsalary()<<endl;
			outfile<<d.getoccupation()<<endl;
		} 
 outfile.close();
}


//showMenu function//
int showMenu(){
	
	int op;
		
	cout<<endl<<"Menu: "<<endl<<endl;
	cout<<"1. Show all employees"<<endl;
	cout<<"2. Get store and price of a given product"<<endl;
	cout<<"3. Add products in store"<<endl;
	cout<<"4. Remove product in store"<<endl;
	cout<<"5. Show all information"<<endl;
	cout<<"6. Save all information"<<endl;
	cout<<"7. End program"<<endl<<endl;
	
	cout<<"Select an option: ";
	cin>>op;
	
return op;
} 








