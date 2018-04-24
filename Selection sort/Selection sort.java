public class SelectionSort {
	public static void main(String[] args) {
		int[] arr= {4,5,2,7,8,1,9,10,3};
		int len=arr.length;
		
		int max=0, maxindex=0;
		for(int i=len-1; i>0; i--) {
			for(int j=0; j<=i; j++) 
				if(max<arr[j]) {
					max=arr[j];
					maxindex=j;
				}
			int temp=arr[maxindex];
			arr[maxindex]=arr[i];
			arr[i]=temp;
			max=0;
		}
	}
}
