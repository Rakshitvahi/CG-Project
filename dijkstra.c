#include<stdio.h>
#include<stdlib.h>
#define SIZE 4

int p[SIZE];

void path(int k) {
	if(p[k] == -1 ) {
		return;
	}
	path(p[k]);

	printf("%d ",k);
} 
void dijkstra(int adj[SIZE][SIZE],int n,int src) {
	int visit[SIZE];
	int d[SIZE];
	int i,j,k;
	int min=0,w=0;
	for(i=0;i<n;i++) {
		visit[i]=0;
		d[i]= 999;
		p[i]= -1;
	}
	visit[src]=1;
	d[src]=0;
	p[src]=-1;
	for(i=0;i<n;i++) {
		if(adj[src][i] != 999 && adj[src][i] != 0) {
			d[i]=adj[src][i];
			p[i]=src;
		}

	}
	for(i=1;i<n;i++) {
		min = 999;
		for(j=0;j<n;j++) {
			if(visit[j]==0 && d[j] < min) {
				min =d[j];
				w=j;
			}
		}
		visit[w]=1;
		for(k=0;k<n;k++) {
			if(visit[k]==0 && adj[w][k] != 999 && adj[w][k] != 0) {
				if(d[k] > (d[w] + adj[w][k])) {
					d[k]= d[w] + adj[w][k];
					p[k]=w;
				}
			}
		}	
	}
	for(i=0;i<n;i++) {
		printf("Distence of node %d from source is %d parent is %d\n",i,d[i],p[i]);
		printf("path taken is");
		printf("%d ",src);
		path(i);
		printf("\n");
	}
}	




void main() {
	int i,j;
	int adj[SIZE][SIZE];
	for(i=0;i<SIZE;i++) {
		for(j=0;j<SIZE;j++) {
			if(i ==j ) {
				adj[i][j] = 0;
			} else {
				printf("Is %d connected to %d ?if yes enter weight, if not enter 999\n",i,j);
				scanf("%d",&adj[i][j]);
			}
		}

	}
	dijkstra(adj,SIZE,0);
}


