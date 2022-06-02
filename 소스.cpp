#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;
struct food{
	int number;int p;int f;int r;int v;int pr;
};
food min_food;
vector<food>answer;
vector<food>food_list;
vector<vector<food>>ans_food;
vector<food>select_food;
vector<food>sum_food;
int min_pr=INT_MAX;
bool compare_a(food a,food b){
	return a.pr<b.pr;
}
bool compare_b(food a,food b){
	return a.number<b.number;
}
bool check(int n,int p,int f,int r,int v){
	if(p+sum_food[n].p<min_food.p||f+sum_food[n].f<min_food.f||r+sum_food[n].r<min_food.r||v+sum_food[n].v<min_food.v){
		return false;
	}
	else return true;
}
void backtracking(int n,int p,int f,int r,int v,int pr){
	if(min_food.p<=p&&min_food.f<=f&&min_food.r<=r&&min_food.v<=v){
		vector<food>temp_sel=select_food;
		sort(temp_sel.begin(),temp_sel.end(),compare_b);
		if(min_pr>pr){
			min_pr=pr;
			ans_food.clear();
			ans_food.push_back(temp_sel);
			return;
		}
		else if(min_pr==pr){
			ans_food.push_back(temp_sel);
			return;
		}
		else return;
	}
	if(n>=food_list.size())return;
	if(check(n,p,f,r,v)==false)return;
	if(pr>min_pr)return;
	p+=food_list[n].p;f+=food_list[n].f;r+=food_list[n].r;v+=food_list[n].v;pr+=food_list[n].pr;
	select_food.push_back(food_list[n]);
	backtracking(n+1,p,f,r,v,pr);
	p-=food_list[n].p;f-=food_list[n].f;r-=food_list[n].r;v-=food_list[n].v;pr-=food_list[n].pr;
	select_food.pop_back();
	backtracking(n+1,p,f,r,v,pr);
}
void make_list(int n){
	food t_food;
	cin>>min_food.p>>min_food.f>>min_food.r>>min_food.v;
	for(int i=0;i<n;i++){
		cin>>t_food.p>>t_food.f>>t_food.r>>t_food.v>>t_food.pr;
		t_food.number=i+1;
		food_list.push_back(t_food);
	}
	sort(food_list.begin(),food_list.end(),compare_a);
	return;
}
int calc_energy(vector<food>food_list){
	int e=0;
	for(int i=0;i<food_list.size();i++){
		e=e+food_list[i].f+food_list[i].p+food_list[i].r+food_list[i].v;
	}
	return e;
}
void print_ans(){
	if(ans_food.empty()){
		cout<<0;
		return;
	}
	int energy=0;
	for(int i=0;i<ans_food.size();i++){
		int t_energy=calc_energy(ans_food[i]);
		if(energy<t_energy){
			energy=t_energy;
			answer.resize(ans_food[i].size());
			copy(ans_food[i].begin(),ans_food[i].end(),answer.begin());
		}
	}
	for(auto n:answer){
		cout<<n.number<<" ";
	}
	return;
}
void make_sum(){
	food t_food;
	int p=0,f=0,r=0,v=0;
	for(int i=0;i<food_list.size();i++){
		p+=food_list[i].p;f+=food_list[i].f;r+=food_list[i].r;v+=food_list[i].v;
	}
	t_food.p=p;t_food.f=f;t_food.r=r;t_food.v=v;
	sum_food.push_back(t_food);
	for(int j=0;j<food_list.size()-1;j++){
		p-=food_list[j].p;f-=food_list[j].f;r-=food_list[j].r;v-=food_list[j].v;
		t_food.p=p;t_food.f=f;t_food.r=r;t_food.v=v;
		sum_food.push_back(t_food);
	}
	return;
}
int main(){
	int n;
	cin>>n;
	make_list(n);
	make_sum();
	backtracking(0,0,0,0,0,0);
	print_ans();
	return 0;
}