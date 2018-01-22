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
		
		// left<right���� �����س��� ������ ���� �ڸ��� �ٲ� ���
		// �׶����� ���ĵǴ� ��Ȳ�� �Ƴ��� �����̴�.
		while(left<right) {
			while(data[left]<data[pivot] && left<right) left++;
			while(data[right]>=data[pivot] && left<right) right--;
			if(left<right) swap(left,right,data);
			// left�� right���� �۾ƾ� �ٲ۴�. left=right�̸� �ٲ� �ʿ䰡 ����
			// left>right�̸� ������ �������� �Ǳ� ������ �ٲٸ� �ȵȴ�.
		}
		
		// left�� pivot���� ū ��쿡 ���߱� ������ �������� ���� �ٲپ��־�� �Ѵ�.
		swap(left,pivot,data);
		
		return left;
	}
	
	
	
	public static void quicksort(int begin,int end, int[] data)
	{
		// �Ѱ��� ���� �� begin=end �̹Ƿ� ����Լ��� ��� ���� �ȴ�.
		// ���� ���ĵǾ�� �ϴ� ��ҵ��� �ݵ�� 2�� �̻��̾�� �Ѵ�.
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
