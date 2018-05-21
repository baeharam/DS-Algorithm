#include <stdio.h>

int D[1000][1000];
int PI[1000][1000];
int path[1000];
const int inf=210000000;

int main(void)
{
	int v,e; scanf("%d %d",&v,&e);

	// Initialization of graph
	// 1. self to self : 0
	// 2. No weight : inf
	for(int i=1; i<=v; i++){
		for(int j=1; j<=v; j++){
			if(i==j) D[i][j]=0;
			else D[i][j]=inf;
		}
	}

	int v1,v2,w;

	// Connect edge and add weight
	// predecessor is initialized by beginning vertex
	while(e--){
		scanf("%d%d%d",&v1,&v2,&w);
		D[v1][v2]=w;
		PI[v1][v2]=v1;
	}

	// Floyd algorithm
	// Consider the existence of intermediate vertices
	for(int k=1; k<=v; k++){
		for(int i=1; i<=v; i++){
			for(int j=1; j<=v; j++){
				if(D[i][k]+D[k][j]<D[i][j]){
					D[i][j]=D[i][k]+D[k][j];
					PI[i][j]=k;
				}
			}
		}
	}

	printf("Enter v1 and v2\n");

	while(v1&&v2){
		scanf("%d%d",&v1,&v2);
		printf("SP - from v1 to v2 : %d\n",D[v1][v2]);
		int i=1, k=PI[v1][v2];
		path[i]=v2;
		while(v1!=k){
			i++;
			path[i]=k;
			k=PI[v1][k];
		}
		i++; path[i]=v1;
		for(int j=i; j>=1; j--){
			printf("%d ",path[j]);
			if(j!=1) printf("-> ");
		}
		printf("\n");
	}
	
	return 0;	
}