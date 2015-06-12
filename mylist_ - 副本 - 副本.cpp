#include<iostream>
using namespace std;

template<class T>
class MyList{
private:
	T *a;
	int size;
	int number; 
	void double_space(){
		size*=2;
		T *b;
		b=new T[size];
		for(int i=0;i<number;++i){
			b[i]=a[i];
		} 
		a=new T[size];
		for(int i=0;i<number;++i){
			a[i]=b[i];
		} 
	}
public:
	MyList(){
		size = 100;
		a = new T [size];
		number=0;
	}
	MyList(int num, const T &item)
	{   
		a = new T [num];
		for(int i=0;i<num;++i){
			a[i]=item;
		}
		size=num;
		number=num;
	}
		
	MyList(const MyList<T> &l){
		size=l.get_size();
		a=new T [size];
		for(int i=0;i<size;++i){
			a[i]=l[i];
		}
		number=size; 
	}
	
    MyList(T* arr, int len){
    	a= new T [len+2];
    	for(int i=0;i<len;++i){
    		a[i]=arr[i];
		}
		number=len;
	}
	
    void push(const T &item){
    	if(number<size){
    		a[number]=item;
    		++number;
		}
		if(number>=size){
			double_space();
			a[number]=item;
			++number;
		}
	}
	
	T pop(){
		--number;
	}
	
	void insert(int index, const T &item){
		if(number<size){
    		for(int i=number;i>index;--i){
    			a[i]=a[i-1];
			}
			a[index]=item;
    		++number;
		}
		if(number>=size){
			double_space();
			for(int i=number;i>index;--i){
    			a[i]=a[i-1];
			}
			a[index]=item;
    		++number;
		}
	}
	
	void clean(){
		number=0;
	}
	
	int get_size() const{
		return number;
	}
	
	void erase(int start, int end){
		try{
			if(start<0||end>number-1||start>end) throw 1;
			for(int i=start;i<number-end+start-2;++i){
			a[i]=a[i+end-start+2];
			number-=(end-start+2);
			
		}
		}
		catch (int) {cout<<"Please input the number again"<<endl;}
	
		
	}
	
	T get_item(int index){
		return a[index];
	}
	
	MyList<T> get_item(int start, int end){
		T *b;
		if(end>0){
			try{
			if(start<0||end>number-1||start>end) throw 1;
			if(start>end){
				b=new T[size];
				MyList<T> l(b,  0);
				delete [] b;
				return l;
			}
			if(start<=end){
				b=new T[end-start+1];
				for(int i=start;i<end+1;++i){
					b[i-start]=a[i];
				}
				MyList<T> l(b,end-start+1);
				delete [] b;
				return l;
			}}
			catch (int) {cout<<"Please input the number again"<<endl;}
		}
		if(end<0){
			end=number+end;
			try{
			if(start<0||end>number-1||start>end) throw 1;
			if(start>end){
				b=new T[size];
				MyList<T> l(b,  0);
				delete [] b;
				return l;
			}
			if(start<=end){
				b=new T[end-start+1];
				for(int i=start;i<end+1;++i){
					b[i-start]=a[i];
				}
				MyList<T> l(b,end-start+1);
				delete [] b;
				return l;
			}}
			catch (int) {cout<<"Please input the number again"<<endl;}
		}
		
	}
	
	int count(const T &item){
		int sum=0;
		for(int i=0;i<number;++i){
			if(a[i]==item){
				++sum;
			}
		}
		return sum;
	}
	
	void remove(const T &item){
		int k=number;
		for(int i=0;i<number;++i){
    		if(a[i]==item){
    			k=i;
    			break;
			}
		}
		if(k<number){
			for(int i=k;i<number-1;++i){
				a[i]=a[i+1];
			}
			--number;
		}
	}


	friend MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2){
		T *b;
		int number=l1.get_size()+l2.get_size();
		b=new T[number];
		int k=l1.get_size();
		for(int i=0;i<k;++i){
			b[i]=l1[i];
		}
		for(int i=k;i<number;++i){
			b[i]=l2[i-k];
		}
		
		MyList<T> l(b, number);
		delete [] b;
		return l;
		
	}
	
    friend MyList<T> operator + (const MyList<T> &l1, const T &item){
    	T *b;
    	int number=l1.get_size()+1;
		b=new T[l1.get_size()];
		for(int i=0;i<l1.get_size();++i){
			b[i]=item;
		}
		MyList<T> l(b, l1.get_size() );
		delete [] b;
		return l;
		
	}
	
	MyList<T> &operator = (const MyList<T> &l){
		if(this==&l){
			return *this;
		}
		size=l.get_size();
		number=size;
		a=new T[size];
		for(int i=0;i<size;++i){
			a[i]=l[i];
		}
		return *this;
	}
	
	MyList<T> &operator += (const T &item){
		if(number<size){
    		a[number]=item;
    		++number;
		}
		if(number>=size){
			double_space();
			a[number]=item;
			++number;
		}
	}
	
	MyList<T> &operator += (const MyList<T> &l){
		*this=*this+l;
		return *this;
	}
	
	T &operator [](int index)const{
		return a[index];
	}
	
	friend ostream & operator<<(ostream &os, const MyList &obj){
		os<<'['; 
		for(int i=0;i<obj.number;++i){
			if(i<obj.number-1){
				os<<obj.a[i]<<','<<" ";
			}
			else os<<obj.a[i];
		}
		os<<']';
		return os;
	}

	void sort(bool less=true){
		int low=0;
		int high=0;
		if(less==true){
			low=0;
			high=number;
			quicksort1(a,low, high);
			T *b;
			b=new int [number];
			for(int i=0;i<number;++i){
				b[i]=a[number-i-1];
			}
			for(int i=0;i<number;++i){
				a[i]=b[i];
			}
		}
		else{
			low=0;
			high=number;
			quicksort1(a,low, high);
		}
	}
    
	void reverse(){
		T *b;
		b=new int [number];
		for(int i=0;i<number;++i){
			b[i]=a[number-i-1];
		}
		for(int i=0;i<number;++i){
			a[i]=b[i];
		}
		
	}
	
	void quicksort1(T a[],int low,int high){
		int mid;
	
		if(low>=high) return;
		mid=divide1( a, low, high);
		quicksort1(a,low, mid-1);
		quicksort1(a,mid+1, high);
	}

	T divide1(T a[],int low,int high){
		T k=a[low];
	
		do{
			while(low<high&&a[high]>=k) --high;
			if(low<high){
				a[low]=a[high];++low;
			}
			while(low<high&&a[low]<=k) ++low;
			if(low<high){
				a[high]=a[low];--high;
			}
		}while(low!=high);
		a[low]=k;
	
		return low;
	}
	
	void quicksort2(T a[],int low,int high){
		T mid;
	
		if(low>=high) return;
		mid=divide2( a, low, high);
		quicksort(a,low, mid-1);
		quicksort(a,mid+1, high);
		}

	T divide2(T a[],int low,int high){
		T k=a[low];
	
		do{
			while(low<high&&a[high]>=k) --high;
			if(low<high){
				a[low]=a[high];++low;
			}
			while(low<high&&a[low]<=k) ++low;
			if(low<high){
				a[high]=a[low];--high;
			}
		}while(low!=high);
		a[low]=k;
	
		return low;
	}


	~MyList(){delete [] a;}
};

int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
    // a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = [] *Èôstart > end£¬·µ»Ø¿ÕÊý×é
	b = a.get_item(3, -1); // b = [1, 0, 12] 
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 0, 12]
	b = a + a; // b = [15, 4, 0, 12, 15, 4, 0, 12]
	b.insert(3, 116); // b = [15, 4, 0, 116, 12, 15, 4, 0, 12]
	b.remove(4); // b = [15, 0, 116, ...]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	
	return 0;
}





