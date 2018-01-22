package datastructure;

public class BubbleSort {
	public static void bubblesort(int[] data)
	{
		// 배열의 요소 개수만큼 반복한다.
		for(int i=0; i<data.length; i++) {
			// 비교 반복은 하나씩 줄어드는데 그 이유는 한번 비교반복이 진행될 때마다
			// 마지막에 최댓값이 오게 되기 때문이다.
			// data.length-1-i인 이유는 비교할 때 마지막 전 값과 마지막 값을 비교해야 하고 index이므로 data.length-1이고
			// 최댓값이 고정될 때마다 i가 1씩 증가하므로 data.length-1-i이다.
			for(int j=0; j<data.length-1-i; j++) {
				if(data[j]>data[j+1]) {
					int temp=data[j];
					data[j]=data[j+1];
					data[j+1]=temp;
				}
			}
		}	
	}
	
	public static void main(String[] args)
	{
		int[] data= {4,3,2,5,7,1,2,0};
		bubblesort(data);
		for(int i=0; i<data.length; i++) System.out.print(data[i]+" ");
	}
}
