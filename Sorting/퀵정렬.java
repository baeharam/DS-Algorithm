package datastructure;

public class QuickSort {
	
	public static void swap(int left, int right, int[] data)
	{
		int temp=data[left];
		data[left]=data[right];
		data[right]=temp;
	}
	
	public static int partition(int left, int right, int[] data)
	{
		int pivot=(left+right)/2;
		
		// left<right으로 설정해놓은 이유는 둘의 자리가 바뀔 경우
		// 그때부턴 정렬되는 상황이 아나기 때문이다.
		while(left<right) {
			while(data[left]<data[pivot] && left<right) left++;
			while(data[right]>=data[pivot] && left<right) right--;
			if(left<right) swap(left,right,data);
			// left가 right보다 작아야 바꾼다. left=right이면 바꿀 필요가 없고
			// left>right이면 정렬이 역순으로 되기 때문에 바꾸면 안된다.
		}
		
		// left는 pivot보다 큰 경우에 멈추기 때문에 마지막에 둘이 바꾸어주어야 한다.
		swap(left,pivot,data);
		
		return left;
	}
	
	
	
	public static void quicksort(int begin,int end, int[] data)
	{
		// 한개가 남을 때 begin=end 이므로 재귀함수를 계속 돌게 된다.
		// 따라서 정렬되어야 하는 요소들은 반드시 2개 이상이어야 한다.
		if(begin<end) {
			int p=partition(begin, end, data);
			quicksort(begin,p,data);
			quicksort(p+1,end,data);
		}
	}
	
	public static void main(String[] args) {
		int[] data= {4,9,1,2,0,3,5,4};
		quicksort(0,7,data);
		for(int i=0; i<8; i++) System.out.print(data[i]+" ");
	}
}
