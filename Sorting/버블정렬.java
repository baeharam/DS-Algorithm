package datastructure;

public class BubbleSort {
	public static void bubblesort(int[] data)
	{
		// �迭�� ��� ������ŭ �ݺ��Ѵ�.
		for(int i=0; i<data.length; i++) {
			// �� �ݺ��� �ϳ��� �پ��µ� �� ������ �ѹ� �񱳹ݺ��� ����� ������
			// �������� �ִ��� ���� �Ǳ� �����̴�.
			// data.length-1-i�� ������ ���� �� ������ �� ���� ������ ���� ���ؾ� �ϰ� index�̹Ƿ� data.length-1�̰�
			// �ִ��� ������ ������ i�� 1�� �����ϹǷ� data.length-1-i�̴�.
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
