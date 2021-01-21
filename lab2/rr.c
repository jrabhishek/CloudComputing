#include<stdio.h>
//#include<stdlib.h>
#include<stdbool.h>

struct Process
{
	int pid;
	int cpu_burst;
	int AT;
	int WT;
	int TAT;
	int start_time;
	int exit_time;
	bool isSelected;
	int bb;

};
int time =0;
struct Process q[100];
int head = -1;
int tail = -1;
bool isEmpty()
{
	if(head == -1)
		return true;
	return false;
}
bool isFull()
{
	if(tail == 100)
		return true;
	else false;
}

void insert(struct Process n)
{
	if(head == -1)
	{
		
		head = 0;
	}
	tail++;

	q[tail] = n;
	
	printf("%d -->",n.pid+1 );



}
void delete()
{
	if(head == -1)
		return;
	if(head == tail)
	{
		head = -1;
		tail = -1;
		return;
	}
	head++;

}
struct Process peek()
{
	return q[head];
}
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

		swap(&p[min_index],&p[i]);
		
	}
}
void processCheck(int n,int time,struct Process p[],struct Process orignal_order[])
{
	 for(int j=0;j<n;j++)
        {
            if(p[j].AT > time)
                break;
            else if(p[j].AT == time){
                insert(orignal_order[p[j].pid]);
                //orignal_order[p[j].pid].start_time=i;
            }
        }
}
void calculate(struct Process p[],int n,int tq,struct Process orignal_order[])
{
	int processLeft = n;
	int time =0;
	sortedProcess(p,n);
	processCheck(n,time,p,orignal_order);
	while(processLeft>0)
	{
		int running_time_of_process = 0;
		struct Process currentP;
		if(isEmpty())
		{
			time++;
			processCheck(n,time,p,orignal_order);
			continue;

		}
		currentP = peek();
		delete();

		while(true)
		{
			if(running_time_of_process < tq && orignal_order[currentP.pid].cpu_burst >0 )
			{
				if(!orignal_order[currentP.pid].isSelected){
					orignal_order[currentP.pid].isSelected = true;
					orignal_order[currentP.pid].start_time = time;
				}
				orignal_order[currentP.pid].cpu_burst--;
				time++;
				running_time_of_process++;
				processCheck(n,time,p,orignal_order);
				continue;

			}
			if(orignal_order[currentP.pid].cpu_burst==0)
			{
				orignal_order[currentP.pid].exit_time = time;

				processLeft--;
				
			}
			else if (running_time_of_process == tq)
			{
				/* code */
			

				insert(orignal_order[currentP.pid]);
			}
			break;

		}


	}

	
}

int main()
{
	int n,i,tq;
	printf("enter the time quantum\n");
	scanf("%d",&tq);
	printf("enter the no of Process\n");
	scanf("%d",&n);
	struct Process process[n];
	struct Process orignal_order[n];
	printf("enter the detail of process cpu_burst arrival time \n");
	for (i = 0; i < n; ++i)
	{
		
		scanf("%d%d",&process[i].cpu_burst,&process[i].AT);
		process[i].pid = i;
		process[i].start_time = 0;
		process[i].exit_time = 0;
		process[i].isSelected = false;

		orignal_order[i].pid =i;
		orignal_order[i].start_time=0;
		orignal_order[i].exit_time=0;
		orignal_order[i].cpu_burst = process[i].cpu_burst;
		orignal_order[i].AT = process[i].AT;
		orignal_order[i].bb = process[i].cpu_burst;


	}
	printf("gang chart\n");
	calculate(process,n,tq,orignal_order);
	printf("\n");
	printf("process\tAt\tbt\tst\tet\tTAT\tWt\n");
	for (i = 0; i < n; ++i)
	{
	
		orignal_order[i].TAT = orignal_order[i].exit_time - orignal_order[i].AT;
		orignal_order[i].WT = orignal_order[i].TAT - orignal_order[i].bb;
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",orignal_order[i].pid,orignal_order[i].AT,orignal_order[i].bb,orignal_order[i].start_time,orignal_order[i].exit_time,orignal_order[i].TAT,orignal_order[i].WT);
		
		

	}
	//sortedProcess(p,n);


}