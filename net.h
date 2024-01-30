void buildNeighbor4(int);
int transfer_x(int, int);
int transfer_y(int, int); 
int transfer_x(int a, int n){
	 if (a%n==0) return a/n;
	 else  return (a-a%n)/n+1;
}

int transfer_y(int a, int n){
	if (a%n==0) return n;
	else return a%n;
}


void buildNeighbor4(int n){
        int i, x, y; 
        int No=n*n; 
		int N_temp = No + 1;
		neighbor = new int * [N_temp];
		for (i=1; i<=No; i++){
			neighbor[i] = new int[5];
			neighbor[i][0]=4;
		}
		int nn=4;
        for (i=1; i<=No; i++){
        x=transfer_x(i,n);  y=transfer_y(i,n);
        if (x==1){
		if (y==1) {
			int temp[4]={2,n,n+1,n*(n-1)+1};
			for (int j=1; j<=nn;j++){
                neighbor[i][j]=temp[j-1];
			}
		}
		else if(y==n) {
			int temp[4]={1,n-1,2*n,n*n};
			for (int j=1; j<=nn;j++){
			     neighbor[i][j]=temp[j-1];
			}
		}
                else {
			int temp[4]={i-1,i+1,i+n,i+n*(n-1)};
	        	for (int j=1; j<=nn;j++){
			     neighbor[i][j]=temp[j-1];
			}
		}
	   }
       	   else if(x==n){
		if (y==1) {
			int temp[4]={1,i-n,i+1,n*n};
			for (int j=1; j<=nn;j++){
			     neighbor[i][j]=temp[j-1];
			}
		}
		else if (y==n) {
			int temp[4]={n,n*(n-1),n*(n-1)+1,n*n-1};
			for (int j=1; j<=nn;j++){
			     neighbor[i][j]=temp[j-1];
			}
		}
		else {
			int temp[4]={y,i-n,i-1,i+1};
			for (int j=1; j<=nn;j++){
			     neighbor[i][j]=temp[j-1];
			}
		}
 	   }
	   else if(y==1) {
		int temp[4]={i-n,i+1,i+n-1,i+n};
		for (int j=1; j<=nn;j++){
		        neighbor[i][j]=temp[j-1];
		}
	   }
	   else if(y==n) {
		int temp[4]={i-n,i-n+1,i-1,i+n};
			for (int j=1; j<=nn;j++){
			     neighbor[i][j]=temp[j-1];
			}
           }
           else{
		int temp[4]={i-n,i-1,i+1,i+n};
		        for (int j=1; j<=nn;j++){
			     neighbor[i][j]=temp[j-1];
			}
	  }
      }
}


