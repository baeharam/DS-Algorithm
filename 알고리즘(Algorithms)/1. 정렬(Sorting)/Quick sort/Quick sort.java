
public class QuickSort {
	static void swap(int arr[], int a, int b) {
		int temp=arr[a];
		arr[a]=arr[b];
		arr[b]=temp;
	}
	
	static void quickSort(int arr[], int from, int to) {
		if(from<to) {
			int m = Partition(arr,from,to);
			quickSort(arr,from,m-1);
			quickSort(arr,m+1,to);
		}
	}
	static int Partition(int arr[], int from, int to) {
		int p = arr[from];
		int i=from, j=from+1;
		while(j<=to) {
			if(arr[j]<=p) {
				i++;
				swap(arr,i,j);
			}
			j++;
		}
		swap(arr, from ,i);
		return i;
	}
	
	public static void main(String[] args) {
		int arr[]= {4,3,6,2,1,9,5,4,0,2,3};
		quickSort(arr,0,10);
		for(int i=0; i<=10; i++) System.out.println(arr[i]);
	}
}
