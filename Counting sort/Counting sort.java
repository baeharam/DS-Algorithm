
public class CountingSort {
	public static void COUNTING_SORT(int A[], int B[], int k){
		int C[]=new int[k+1];
		for(int i=0; i<=k; i++) C[i]=0;
		for(int j=1; j<A.length; j++) C[A[j]]=C[A[j]]+1;
		for(int i=1; i<=k; i++) C[i]=C[i]+C[i-1];
		for(int j=A.length-1; j>=1; j--) {
			B[C[A[j]]]=A[j];
			C[A[j]]=C[A[j]]-1;
		}
	}
	
	public static void main(String[] args) {
		int A[]= {0,2,5,3,1,6,9,3,4,0,10};
		int B[]=new int[11];
		COUNTING_SORT(A,B,10);
		for(int i=1; i<B.length; i++) System.out.println(B[i]);
	}
}
