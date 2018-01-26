package datastructure;

public class SelectionSort {
	
	public static void swap(int index1, int index2, int[] data)
	{
		int temp=data[index1];
		data[index1]=data[index2];
		data[index2]=temp;
	}
	
	public static void selectionsort(int[] data)
	{
		int min_index;
		
		for(int i=0; i<data.length; i++) {
			min_index=i;
			for(int j=i+1; j<data.length; j++)
				if(data[min_index]>data[j]) min_index=j;
			swap(i,min_index,data);
		}
	}
	
	public static void main(String[] args) {
		int[] test= {1,8,4,3,5,6,1,0};
		selectionsort(test);
		for(int i=0; i<test.length; i++) System.out.print(test[i]+" ");
	}
}
