public class BubbleSort {
	public static void main(String[] args) {
		int[] arr= {4,5,2,7,8,1,9,10,3};
		int len=arr.length;
		
		for(int i=len-1; i>0; i--) {
			for(int j=0; j<i; j++) {
				if(arr[j]>arr[j+1]) {
					int temp=arr[j];
					arr[j]=arr[j+1];
					arr[j+1]=temp;
				}
			}
		}
	}
}
