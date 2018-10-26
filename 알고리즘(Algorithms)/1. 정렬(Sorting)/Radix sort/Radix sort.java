
public class RadixSort {
	
	static void RADIX_SORT(int A[], int d)
	{
		int C[]=new int[10];
		int B[]=new int[A.length];
		for(int i=1; i<A.length; i++) B[i]=0;
		for(int i=1; i<=d; i++) {
			int p=1;
			for(int j=1; j<=i-1; j++) p*=10;
			for(int j=0; j<=9; j++) C[j]=0;
			for(int j=1; j<A.length; j++) C[(A[j]/p)%10]++;
			for(int j=1; j<=9; j++) C[j]=C[j-1]+C[j];
			for(int j=A.length-1; j>=1; j--) {
				B[C[(A[j]/p)%10]]=A[j];
				C[(A[j]/p)%10]--;
			}
			for(int j=1; j<A.length; j++) A[j]=B[j];
		}
	}
	
	public static void main(String[] args) {
		int A[]= {0,329,457,657,839,436,720,355};
		RADIX_SORT(A,3);
		for(int i=1; i<A.length; i++)System.out.println(A[i]);
	}
}
