#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string.h>
#include <iomanip>
#include <bitset>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <sstream>
#include <stdio.h>
#include <sys/stat.h>

using namespace std;

int c = 0;

struct record
{
	char author[12];
	char article[32];
	char izd[16];
	short int year;
	short int pages;


};

struct vertex {
	int num;
	int W;
	vertex* left;
	vertex* right;
	vertex* up;
	record record;
};

vertex *root=NULL;
struct record1
{
	int num;
	char author[12];
	char article[32];
	char izd[16];
	short int year;
	short int pages;
	record1* next;

};

struct Queue {
	record1* head;
	record1* tail;
};

void Pool(record1*& head, record base[], int m,int key);
void print(record1*& head);

int Less(record base, record x)
{
	char* auth1 = base.author;
	char* auth2 = x.author;
	if (base.year < x.year)
		return 1;
	else if (base.year > x.year)
		return 0;
	else if (strcmp(auth1, auth2) < 0)
		return 1;
	else
		return 0;

}

int More(record base, record x)
{
	char* auth1 = base.author;
	char* auth2 = x.author;
	if (base.year > x.year)
		return 1;
	else if (base.year < x.year)
		return 0;
	else if (strcmp(auth1, auth2) > 0)
		return 1;
	else
		return 0;

}


void PrintBase(record* base, int size)
{
	int n;
	cout << "Num" << setw(2) << "|" << "Author" << setw(6) << "|" << "Article" << setw(24) << "|" << "Publisher" << setw(7) << "|" << "Year" << "|" << "Pages" << "|" << endl;
	for (int i = 1, count = 1; i < 4000; ++i) {

		int check = 0;
		while (check < 20) {

			cout << setw(4) << count << "|";
			cout << base[i].author << "|" << base[i].article << "|" << base[i].izd << "|" << base[i].year << "|" << base[i].pages << "|" << endl;
			check++;
			count++;
			i++;
		}
		cout << endl << "Press the Enter to print another 20 entries" << endl;
		n = _getch();
		if (n != 13) break;



	}
}

void QuickSort(record* base, record* index, int l, int r)
{
	record x;
	x = base[l];
	int  i = l, j = r;
	while (i <= j) {
		while (Less(base[i], x) == 1) {
			i++;
		}
		while (More(base[j], x) == 1) {
			j--;
		}
		if (i <= j)
		{
			record tmp = index[i];
			index[i] = index[j];
			index[j] = tmp;
			i++;
			j--;

		}
	}
	if (l < j)
		QuickSort(base, index, l, j);
	if (i < r)
		QuickSort(base, index, i, r);

}

void BSearch1 (record base[], int n, record1 *&head)
{	int key;
cout<<"input key `Year`:";
	cin>>key;
	
	
	int L=1, R=n, Find=0, m=0;
if(1897<key&&key<1998){

	while (L<R)
	{

		m=(L+R)/2;

		if (base[m].year<key) L=m+1;
		else R=m;
		
			if (base[m].year==key) 
		{	L=R;
			while(base[m].year==key) {
			//	R++;
			//	if(R==3999) break;
			m=m+1;
			}
		Find=1;
		m=m-1;
		break;
		} 
	}
	if(Find==1){Pool(head,base,m,key);}
}
else cout<<"Wrong key"<<endl;
}

void Search(vertex *root){
	int X;
	cin>>X;
	vertex *p;
	p=root;
	if(!(X>=0&&X<=1000)){
	
		while(!(X>=0&&X<=1000)){
		
		cout<<"Enter the correct key!(0-1000)"<<endl;
		cin>>X;}
		
		
	}
	
	while(p!=NULL){
		if(X<p->record.pages) p=p->left;
		 else{
		 	if(X>p->record.pages) p=p->right;
		 	 else {
		 	 	break;
			  }
		 }
	}
	if(p!=NULL){
	 while(p!=NULL){
	 
	 cout << ' ' << p->num << setw(15) << p->record.author << ' ' << setw(14) << p->record.article << setw(6) << p->record.izd << setw(14) << ' ' << p->record.year << setw(18) << p->record.pages<<endl;
	p=p->up;
	}}
	else cout<<endl<<"NOT FOUND ";
	return;
}

void obhod(vertex *p){
	if(p!=NULL){
		obhod(p->left);
	cout << ' ' << p->num << setw(15) << p->record.author << ' ' << setw(14) << p->record.article << setw(6) << p->record.izd << setw(14) << ' ' << p->record.year << setw(18) << p->record.pages;
		cout << endl;
		obhod(p->right);
		if(p->up!=NULL){
			obhod(p->up);
		}
	}
	
	return;
}

void QuickSortW(vertex A[], int L, int R){
	int j=R,i=L,X=A[(L+R)/2].W;
	vertex t;
	while(i<=j){
		while(A[i].W>X) {i++; }
		while(A[j].W<X) {j--; }
		if(i<=j){
			t=A[j];
			A[j]=A[i];
			A[i]=t;
			i++;
			j--;
		}
	}
	if(L<j) QuickSortW(A,L,j);
	if(i<R)	QuickSortW(A,i,R);
	return;
}

void ADD(vertex *&p, vertex X){
	if(p==NULL){
		p=new vertex;
		p->num=X.num;
		p->W=X.W;
		strcpy(p->record.author,X.record.author);
		strcpy(p->record.article,X.record.article);
		strcpy(p->record.izd,X.record.izd);
		p->record.year=X.record.year;
		p->record.pages=X.record.pages;
		p->left=p->right=NULL;
	}
		else if(X.record.pages<p->record.pages) ADD(p->left,X);
		else if(X.record.pages>p->record.pages) ADD(p->right,X);
		else ADD(p->up,X);
}

void DOP1(vertex *&root, vertex V[]){
	int nn=c;
	QuickSortW(V,1,nn);
	for(int i=0;i<c;i++) {
	
	ADD(root,V[i]);}
	//obhod(root);
//	cout<<endl<<"Please input num of PAGES"<<endl;
	//Search(root);
}
void PullMass(record1 * &head, vertex mass[]) {
		record1* p = head;
		for (int i = 0; i<c; p = p->next, i++) {
			mass[i].num = p->num;
			strcpy(mass[i].record.author, p->author);
			strcpy(mass[i].record.article, p->article);
			strcpy(mass[i].record.izd, p->izd);
			mass[i].record.year = p->year;
			mass[i].record.pages = p->pages;
			mass[i].W = rand() % 15 + 1;
		
		}

		DOP1(root,mass);
	}

void Pool(record1*& head, record base[], int m,int key) {

	record1* p = head;


	while (base[m].year==key) {
		p = new record1;
		p->num = m;
		strcpy(p->author, base[m].author);
		strcpy(p->article, base[m].article);
		p->year = base[m].year;
		p->pages = base[m].pages;
		strcpy(p->izd, base[m].izd);
		p->next = head;
		head = p;
		m = m - 1;
		c++;

	}
	/*p = new record1;
	p->num = m;
	strcpy(p->author, base[m].author);
	strcpy(p->article, base[m].article);
	p->year = base[m].year;
	p->pages = base[m].pages;
	strcpy(p->izd, base[m].izd);
	p->next = head;
	head = p;
	c++;*/
	
	cout<<endl<<"Queue:"<<endl;
	
	

	print(head);
	
	vertex *mass= new vertex[c];

	PullMass(head, mass);
	
//	cout<<mass[0].num;
}
	



void print(record1*& head) {
	record1* p = head;
	int code;
	for (; p != NULL; p = p->next) {
		cout << ' ' << p->num << setw(15) << p->author << ' ' << setw(14) << p->article << setw(6) << p->izd << setw(14) << ' ' << p->year << setw(18) << p->pages;
		cout << endl;



	}
//	cout << endl << "DOP:"<<endl;
}

int Med(int l, int r, vector<pair<char, double>> p)
{
    double sl = 0, sr;
    int m = r;
    for (int i = l; i < r; i++) {
        sl += p[i].second;
    }
    sr = p[r].second;
    while (sl >= sr) {
        m--;
        sl -= p[m].second;
        sr += p[m].second;
    }
    if (!m) {
        return m;
    }
    return (fabs(sl - sr) < fabs(sl + p[m].second - sr + p[m].second) ? m - 1
                                                                      : m);
}

void Fano(
        int l,
        int r,
        int k,
        vector<pair<char, double>> p,
        vector<vector<int>>& c)
{
    if (l < r) {
        k++;
        int m = Med(l, r, p);
        for (int i = l; i <= r; i++) {
            if (i <= m) {
                c[i].push_back(0);
            } else {
                c[i].push_back(1);
            }
        }
        Fano(l, m, k, p, c);
        Fano(m + 1, r, k, p, c);
    }
}
void Code(vector<pair<char, double>> p, vector<vector<int>> c) {
    map<char, string> code;
    for (int i = 0; i < p.size(); i++) {
        stringstream ss;
        for (auto a : c[i]) {
            ss << a;
        }
        code[p[i].first] = ss.str();
    }
    ifstream input("testBase1.dat");
    ofstream output("code.txt");
    while (true) {
        char c = input.get();
        if (input.eof()) {
            break;
        }
        output << code[c];
    }
    input.close();
    output.close();
}

void Make() {
    map<char, int> _map;
    ifstream input("testBase1.dat");
    int count = 0;
    double length = 0;
    while (true) {
        char c = input.get();
        if (input.eof()) {
            break;
        }
        count++;
        _map[c]++;
    }
    vector<pair<char, double>> vec;
    for (auto i : _map) {
        vec.push_back({i.first, i.second / (double)count});
    }
    double entropy = 0;
    for (auto i : vec) {
        entropy += i.second * (-log2(i.second));
    }
    vector<vector<int>> c(vec.size());
    sort(vec.begin(), vec.end(), [](pair<char, double> a, pair<char, double> b) {
        return a.second > b.second;
    });
    vector<double> p;
    for (auto i : vec) {
        p.push_back(i.second);
    }
   Fano(0, p.size() - 1, 0, vec, c);
    int _max = 0;
    for (auto i : c) {
        _max = max(_max, (int)i.size());
    }
    for (int i = 0; i < vec.size(); i++) {
        cout << bitset<sizeof(vec[i].first) * CHAR_BIT>(vec[i].first) << " " << setw(11)<< fixed << vec[i].second << " ";
        for (auto j : c[i]) {
            cout << j;
        }
        for (int j = 0; j < _max - c[i].size() + 3; j++) {
            cout << " ";
        }
        cout << setw(5) << c[i].size() << endl;
    }
    for (int i = 0; i < p.size(); i++) {
        length += vec[i].second * c[i].size();
    }
    cout << endl << endl << "entropiya: " << entropy << endl << "Sr dlina:  " << length << endl << endl << endl;
    Code(vec,c);
    _map.clear();
    vec.clear();
    c.clear();
    p.clear();
}

void clear(void)
{
	system("cls");
}

int getFileSize(const char * fileName)
{
    struct stat file_stat;
    stat(fileName, &file_stat);
    return file_stat.st_size;
}
	int main()
	{
		int i = 0;
		record1* head, * tail;
		head = NULL;
		tail = (record1*)&head;
		int sizebase = 0;


		FILE* fp;
		int size;
		size = 4000;
		fp = fopen("testBase1.dat", "rb");
		record base[4000] = { 0 };
		record baseun[4000] = { 0 };
		record* index[4000] = { 0 };

		i = fread((record*)base, sizeof(record), size, fp);
		cout << i << endl;
		char but;
		
		while(true){clear();
		cout<<"1.Unsorted all base "<<endl<<"2.Sorted all base "<<endl<<"3.Unsorted base of 20 elements"<<endl<<"4.Sorted base of 20 elements"<<endl<<"5.Search"<<endl;
		cout<<"6.Tree (DOP)"<<endl<<"7.Code"<<endl;
		cin>>but;
		switch(but){
			case'1':{
			
			fp = fopen("testBase1.dat", "rb");
			i = fread((record*)baseun, sizeof(record), size, fp);
			fclose(fp);
				i = 0;
		int count = 4000, code;
		int countMax = count / 20;
		count = 1;
		while (i < 4000) {
			int temp = i;
			//cout<< setw(5) <<"Num:"<< setw(12) << "Author:" << setw(18)  << "Article:"<< setw(24)  << "Publisher:"<< setw(7)  << "Year:" << "Pages:" << endl;
			cout << "Num" << setw(2) << "|" << "Author" << setw(6) << "|" << "Article" << setw(24) << "|" << "Publisher" << setw(7) << "|" << "Year" << "|" << "Pag" << endl;
			for (i = temp; i < 4000; i++) {
				cout << setw(4) << i+1 << "|" << baseun[i].author << "|" << setw(4) << baseun[i].article << "|" << setw(6) << baseun[i].izd << "|" << baseun[i].year << "|" << baseun[i].pages;
				cout << endl;
			}
		cout<<"Press ESC to EXIT"<<endl;
			code = getche();
			//clear();
if (code == 27) {
				break;
			}
			//else if (code == 'k') {
			//cout<<search(KEY, head)<<endl;}

		}
			
			
		break;}
		
		case'2':{
			
			fp = fopen("testBase1.dat", "rb");
			i = fread((record*)base, sizeof(record), size, fp);
			fclose(fp);
			
			for (int i = 0; i < size; i++)
		{
			index[i] = &base[i];
		}
		
		
		QuickSort(base, *index, 0, size);
		
				i = 0;
		int count = 4000, code;
		int countMax = count / 20;
		count = 1;
		while (i < 4000) {
			int temp = i;
			//cout<< setw(5) <<"Num:"<< setw(12) << "Author:" << setw(18)  << "Article:"<< setw(24)  << "Publisher:"<< setw(7)  << "Year:" << "Pages:" << endl;
			cout << "Num" << setw(2) << "|" << "Author" << setw(6) << "|" << "Article" << setw(24) << "|" << "Publisher" << setw(7) << "|" << "Year" << "|" << "Pag" << endl;
			for (i = temp; i < 4000; i++) {
				cout << setw(4) << i+1 << "|" << base[i].author << "|" << setw(4) << base[i].article << "|" << setw(6) << base[i].izd << "|" << base[i].year << "|" << base[i].pages;
				cout << endl;
			}
		cout<<"Press ESC to EXIT"<<endl;
			code = getche();
			//clear();
if (code == 27) {
				break;
			}
			
			break;
		}
		break;}
		case'3':{
		
		fp = fopen("testBase1.dat", "rb");
			i = fread((record*)baseun, sizeof(record), size, fp);
			fclose(fp);
				i = 0;
		int count = 4000, code;
		int countMax = count / 20;
		count = 1;
		while (i < 4000) {
			int temp = i;
			//cout<< setw(5) <<"Num:"<< setw(12) << "Author:" << setw(18)  << "Article:"<< setw(24)  << "Publisher:"<< setw(7)  << "Year:" << "Pages:" << endl;
			cout << "Num" << setw(2) << "|" << "Author" << setw(6) << "|" << "Article" << setw(24) << "|" << "Publisher" << setw(7) << "|" << "Year" << "|" << "Pag" << endl;
			for (i = temp; i < temp +20; i++) {
				cout << setw(4) << i+1 << "|" << baseun[i].author << "|" << setw(4) << baseun[i].article << "|" << setw(6) << baseun[i].izd << "|" << baseun[i].year << "|" << baseun[i].pages;
				cout << endl;
			}
		cout << "Page " << temp/20+1 << ' ' << "of " << countMax << endl << "To view the next page press any key, exit  - esc " << endl;
			code = getche();
			cout<<"Press ESC to EXIT"<<endl;
			//clear();
if (code == 27) {
				break;
			}
			//else if (code == 'k') {
			//cout<<search(KEY, head)<<endl;}

		}
		if (code != 27) {
			
			while(code !=27){
			
			code=getche();
			if(code ==27)
			break;
			}}
			
			else	break;
			break;}
		
			case'4':{
			
		fp = fopen("testBase1.dat", "rb");
		i = fread((record*)base, sizeof(record), size, fp);
		fclose(fp);
		
		for (int i = 0; i < size; i++)
		{
			index[i] = &base[i];
		}
		
		
		QuickSort(base, *index, 0, size);
		
				i = 0;
		int count = 4000, code;
		int countMax = count / 20;
		count = 1;
		while (i < 4000) {
			int temp = i;
			//cout<< setw(5) <<"Num:"<< setw(12) << "Author:" << setw(18)  << "Article:"<< setw(24)  << "Publisher:"<< setw(7)  << "Year:" << "Pages:" << endl;
			cout << "Num" << setw(2) << "|" << "Author" << setw(6) << "|" << "Article" << setw(24) << "|" << "Publisher" << setw(7) << "|" << "Year" << "|" << "Pag" << endl;
			for (i = temp; i < temp + 20; i++) {
				cout << setw(4) << i+1 << "|" << base[i].author << "|" << setw(4) << base[i].article << "|" << setw(6) << base[i].izd << "|" << base[i].year << "|" << base[i].pages;
				cout << endl;
			}
			cout << "Page " << temp/20+1 << ' ' << "of " << countMax << endl << "To view the next page press any key, exit  - esc " << endl;
			code = getche();
			cout<<"Press ESC to EXIT"<<endl;
if (code == 27) {
				break;
			}
			
			
		
		}	
		if (code != 27) {
			
			while(code !=27){
			
			code=getche();
			if(code ==27)
			break;
			}}
			
			else	break;
			break;
	}
	
	case'5':{
		
	int count = 4000, code;
		fp = fopen("testBase1.dat", "rb");
		i = fread((record*)base, sizeof(record), size, fp);
		fclose(fp);
		
		for (int i = 0; i < size; i++)
		{
			index[i] = &base[i];
		}
		
		
		QuickSort(base, *index, 0, size);
		
		//cout<<"Input KEY:";
		
		//if(1897<key<1998){
		
		
		BSearch1(base, 4000, head);//}
		
	
	cout<<"Press ESC to EXIT"<<endl;
	code = getche();
if (code == 27|code == 13) {
				break;
			}
			break;
}	
	case'6':{
		int count = 4000, code;
		fp = fopen("testBase1.dat", "rb");
		i = fread((record*)base, sizeof(record), size, fp);
		fclose(fp);
		
		if(head!=NULL){
		
		cout<<"DOP"<<endl;
		obhod(root);
		cout<<endl<<"Please input num of PAGES"<<endl;
		Search(root);}
		else cout<<"Queue not a build"<<endl;
		cout<<"Press ESC to EXIT"<<endl;
		code = getche();
if (code == 27|code == 13) {
				break;}
				break;
}	

case'7':{
	int count = 4000, code;
	Make();

	int sizecode=0;
	sizecode=getFileSize("code.txt");
	sizebase=getFileSize("testBase1.dat");
	
	cout<<"The weight of the original file ="<<sizebase<<" byte"<<endl;
	cout<<"The weight of the encoded file ="<<sizecode<<" byte"<<endl;
	cout<<"The compression ratio ="<<(float)sizebase/sizecode<<endl;
	cout<<"Press ESC to EXIT"<<endl;
	code = getche();
if (code == 27) {
				break;}
}	
}
}
		
		return 0;
	}
