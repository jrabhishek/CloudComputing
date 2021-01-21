#include<stdio.h>
int main()
{
	int m,n;
	printf(" Enter the number of machines:");
	scanf("%d",&n);
	printf("Enter the number of tasks:");
	scanf("%d",&m);
	int a[n][m];
	printf(" Enter the data\n");
	int i,j,k,x;
	int flag=-1;
	for(i=0;i<n;i++)
	{
		printf("Enter details for machine %d: \n",i+1);
		for(j=0;j<m;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	
	int t[m];
	int me[n];
	for(i=0;i<n;i++)
	{
		me[i]=0;
	}
	int ctr=0;
	for(i=0;i<m;i++)
	{
		for(k=0;k<n;k++)
		{
			int min=9999,task=0,mac=0;
			for(j=0;j<m;j++)
			{
				if(a[k][j]<min && a[k][j]!=-1)
				{
					min=a[k][j];
					task=j;
					mac=k;
				}
			}
			
			t[task]=mac;
			me[mac]=min;
			ctr++;
			
			
			for(x=0;x<n;x++)
			{
				if(x!=task)
				a[mac][x]+=min;
			}
			for(x=0;x<n;x++)
			{
				a[x][task]=-1;
			}
			if(ctr==m)
			break;
		}
		if(ctr==m)
		break;
	}
	printf("Makespan time=\n");
	for(i=0;i<n;i++)
	{
		printf("%d\n",me[i]);
	}
	int makespan=0;
	for(i=0;i<n;i++)
	{
		if(me[i]>makespan)
		makespan=me[i];
	}
	printf("Makespan for the process= %d\n",makespan);
}