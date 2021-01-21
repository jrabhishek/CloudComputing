#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Process
{
	int pid;
	int cpu_burst;
	int AT;
	int WT;
	int TAT;
	//bool isSelected = false;

};
int time = 0;  
void swap(struct Process *xp, struct Process *yp) 
{ 
    struct Process temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}

void sortedProcess(struct Process p[],int n)
{
	int i,j,min_index;
	for (i = 0; i < n-1; ++i)
	{
		min_index = i;
		for (j = i+1; j < n; ++j)
		{
			if(p[j].AT < p[min_index].AT)
			{
				min_index = j;
			}
		}
		if (p[min_index].AT != p[i].AT)
		{
			/* code */
			swap(&p[min_index],&p[i]);
		}

		
		
	}
}
void sort(struct Process p[],int n)
{
	int i,j,min_index;
	for (i = 0; i < n-1; ++i)
	{
		

		if(p[i].AT == p[i+1].AT && p[i].pid > p[i+1].pid)
		{
            swap(&p[i+1],&p[i]);
		}
		
	}
}
void calculate_tat(struct Process p[],int n)
{
	 time = p[0].AT;
     for (int i = 0; i < n; ++i)
     {
     	if(time < p[i].AT)
     		time = p[i].AT;

     	p[i].TAT = p[i].cpu_burst +time - p[i].AT;
     	p[i].WT = p[i].TAT - p[i].cpu_burst;
     	time+=p[i].cpu_burst;

     }
}
int main()
{
	/* code */
	int n,i;
	printf("enter the no of Process\n");
	scanf("%d",&n);
	struct Process process[n];
	printf("enter the detail of process cpu_burst arrival time \n");
	for (i = 0; i < n; ++i)
	{
		
		scanf("%d%d",&process[i].cpu_burst,&process[i].AT);
		process[i].pid = i;

	}
	printf("process\tAt\tbt\ttat\twt\n");
	sortedProcess(process,n);
	sort(process,n);
	calculate_tat(process,n);

	for (i = 0; i < n; ++i)
	{
	
		printf("%d\t%d\t%d\t%d\t%d\n",process[i].pid+1,process[i].AT,process[i].cpu_burst,process[i].TAT,process[i].WT);
		
		

	}



	return 0;
}