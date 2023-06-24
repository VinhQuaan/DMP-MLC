#include"TSP.h"
//Main function calling different methods to solve TSP
//Print output into .sol and .trace file

using namespace std;

ofstream output_sol,output_trace;

int DP(int i, int mask, int **dist, int n, vector<int>memo[])
{	
    if (mask == ((1 << i) | 3))return dist[0][i];
    if (memo[i][mask] != 0)
        return memo[i][mask];
 
    int res = INT_MAX;
 
    for (int j = 0; j <= n; j++)
        if ((mask & (1 << j)) && j != i && j != 0)
            res = min(res, DP(j, mask & (~(1 << i)),dist,n,memo)
                                    + dist[j][i]);
    return memo[i][mask] = res;
}

int main(int argc, char* argv[])
{	
	string Methods []= {"DP", "Greedy", "LS1","LS2"," "};  //Cac phuong phap su dung
	string filename1,filename2;
	
	int **distance;
	int *d=new int;
	int *o=new int;
	distance=readgraph(argv[1],d,o); //Lay thong tin du lieu dau vao
	cout << "NAME" << NAME << endl;  
	int dim=*d;
	int opt=*o;
	double cutoff = strtod(argv[2],NULL);
	int seed=atoi(argv[4]);
	
	int i;
	int pathlength = 0;
	double gap;
	
	if(Methods[0].compare(argv[3])==0)
	{
		cout << "Method:" << "DP"<<endl;

		int ans = INT_MAX,n=dim;
		vector<int>memo[n + 1];
		
		for(int j=0;j<n+1;j++)
			for(int k=0;k<1<<(n+1);k++)memo[j].push_back(0);

    	for (int i = 0; i < n; i++)ans = min(ans, DP(i,(1<<(n+1))-1,distance,n,memo)+distance[i][0]);
		cout <<"Result: "<< ans;
	}

	if(Methods[1].compare(argv[3])==0)
	{	
		cout << "Method:" << "Greedy"<<endl;
		
		filename1 = NAME + "_" + Methods[1] + "_"+argv[2]+".sol";
		const char *name1 = filename1.c_str();
		output_sol.open(name1);
		
		if (!output_sol.is_open())
		{
			cout << "Failed to create output file!" << endl;
			return 0;
		}
		
		int *path;
		path=greedy_algo(distance, dim); 
		
		cout<<"Path:";
		
		for(i=0;i<dim-1;i++)
			pathlength += distance[path[i]][path[i+1]]*(dim-i-1);  //Ham muc tieu cho DMP
		pathlength += distance[path[dim-1]][path[0]];
		output_sol << pathlength <<endl;
		for(i=0;i<dim-1;i++)
		{
			cout<<path[i]+1<<",";
			output_sol << path[i]+1<<",";
		}
		cout<<path[dim-1]+1<<","<<path[0]+1<<endl;
		output_sol<<path[dim-1]+1<<","<<path[0]+1<<endl;
		
		cout<<"Result:";
		cout<<pathlength<<endl;
		
		//gap = (float)(pathlength-opt)/opt;
		//cout << "Solution gap:" << 100*gap << "%" << endl;
		
		cout << endl << "Output file created!" << endl;
		output_sol.close();
		output_trace.close();
		return 0;
	}
	
	if(Methods[2].compare(argv[3])==0)
	{
		cout << "Method:" << "Iterated Hill Climbing"<<endl;
		
		filename1 = NAME + "_" + Methods[2] + "_"+argv[2]+"_"+argv[4]+".sol";
		const char *name1 = filename1.c_str();
		filename2 = NAME + "_" + Methods[2] + "_"+argv[2]+"_"+argv[4]+".trace";
		const char *name2 = filename2.c_str();
		output_sol.open(name1);
		output_trace.open(name2);
		if (!output_sol.is_open()|| !output_trace.is_open())
		{
			cout << "Failed to create output file!" << endl;
			return 0;
		}

		int **path;
		int *initial;
		initial=greedy_algo(distance, dim);   //Dung tham lam de sinh nghiem ban dau

		for(i=0;i<dim-1;i++)
			pathlength += distance[*path[i]][*path[i+1]]*(dim-i-1);
		pathlength += distance[*path[dim-1]][*path[0]];
		output_sol << pathlength <<endl;
		for(i=0;i<dim-1;i++)
		{
			cout<<*path[i]+1<<",";
			output_sol << *path[i]+1<<",";
		}
		cout<<*path[dim-1]+1<<","<<*path[0]+1<<endl;
		output_sol<<*path[dim-1]+1<<","<<*path[0]+1<<endl;
		
		cout<<"Initial Result:";
		cout<<pathlength<<endl;

		path= HC(distance, dim, initial, cutoff, i); //Cai thien
		
		cout<<"Path:";
		
		for(i=0;i<dim-1;i++)
			pathlength += distance[*path[i]][*path[i+1]]*(dim-i-1);
		pathlength += distance[*path[dim-1]][*path[0]];
		output_sol << pathlength <<endl;
		for(i=0;i<dim-1;i++)
		{
			cout<<*path[i]+1<<",";
			output_sol << *path[i]+1<<",";
		}
		cout<<*path[dim-1]+1<<","<<*path[0]+1<<endl;
		output_sol<<*path[dim-1]+1<<","<<*path[0]+1<<endl;
		
		cout<<"Final Result:";
		cout<<pathlength<<endl;

		gap = (float)(pathlength-opt)/opt;
		//cout << "Solution gap:" << 100*gap << "%" << endl;
		cout << "Elapsed time:" << cutoff << "s" <<endl;
		
		cout << endl << "Output file created!" << endl;
		output_sol.close();
		output_trace.close();
		return 0;
	}
	
	if(Methods[3].compare(argv[3])==0)
	{
		cout << "Method:" << "Simulated Annealing"<<endl;
		
		filename1 = NAME + "_" + Methods[3] + "_"+argv[2]+"_"+argv[4]+".sol";
		const char *name1 = filename1.c_str();
		filename2 = NAME + "_" + Methods[3] + "_"+argv[2]+"_"+argv[4]+".trace";
		const char *name2 = filename2.c_str();
		output_sol.open(name1);
		output_trace.open(name2);
		if (!output_sol.is_open()|| !output_trace.is_open())
		{
			cout << "Failed to create output file!" << endl;
			return 0;
		}
		
		int **path;
		int *initial;
		initial=greedy_algo(distance, dim);

		int temp = distance[initial[9]][initial[10]]*2*dim;
		double cooling_r = 0.99;
		path = SA(initial, distance, temp, 0.1*dim, cooling_r, cutoff, dim, seed);
		
		cout<<"Path:";
		for(i=0;i<dim-1;i++)
			pathlength += distance[*path[i]][*path[i+1]]*(dim-i-1);
		pathlength += distance[*path[dim-1]][*path[0]];
		output_sol << pathlength <<endl;
		for(i=0;i<dim-1;i++)
		{
			cout<<*path[i]+1<<",";
			output_sol << *path[i]+1<<",";
		}
		cout<<*path[dim-1]+1<<","<<*path[0]+1<<endl;
		output_sol<<*path[dim-1]+1<<","<<*path[0]+1<<endl;
		
		cout<<"Result:";
		cout<<pathlength<<endl;
		
		gap = (float)(pathlength-opt)/opt;
		//cout << "Solution gap:" << 100*gap << "%" << endl;
		cout << "Elapsed time:" << cutoff << "s" <<endl;
		
		cout << endl << "Output file created!" << endl;
		output_sol.close();
		output_trace.close();
		return 0;
	}
}