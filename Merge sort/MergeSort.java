package com.haram;

public class MergeSort {
    public static void main(String args[]) {
        int arr[] = {5,1,2,3,4,10,12,18,9,6};
        mergesort(arr, 0, 9);
        for(int i=0; i<10; i++) System.out.print(arr[i] + " ");
    }

    // 재귀로 2개가 남을 때까지 계속 쪼갠다. left<right이 주는 의미는 left=right 부터 조건에 해당하지 않기 때문에
    // 1개에선 아무일도 안 일어난다고 생각하면 된다.
    private static void mergesort(int arr[], int left, int right) {
        if(left<right) {
            int mid = (left+right)/2;
            mergesort(arr, left, mid);
            mergesort(arr, mid+1, right);
            merge(arr, left, mid, right);
        }
    }

    // left~mid로 배열을 하나 만들고 mid+1~right으로 배열을 하나 만든다.
    // 각 배열의 원소들을 비교하면서 작은 값들 부터 arr에 넣는 방식이다.
    // 이 함수의 핵심적인 개념은 이미 각각의 배열이 정렬되어 있다는 가정이다.
    // 그럴 수밖에 없는 것이 재귀로 계속 쪼개졌다 이 함수로 정렬이 되고 더 큰 배열로 가기 때문에 그렇다.
    private static void merge(int arr[], int left, int mid, int right) {
        int n1 = mid-left+1;
        int n2 = right-mid;

        int left_arr[] = new int[n1];
        int right_arr[] = new int[n2];

        // 왼쪽, 오른쪽에 해당하는 배열을 복사한다.
        for(int i=0; i<n1; i++)
            left_arr[i] = arr[left+i];
        for(int i=0; i<n2; i++)
            right_arr[i] = arr[mid+1+i];

        // 정렬하는 작업
        int left_index=0, right_index=0, k=left;
        while(left_index<n1 && right_index<n2) {
            if(left_arr[left_index]<right_arr[right_index]){
                arr[k] = left_arr[left_index];
                left_index++;
            } else {
                arr[k] = right_arr[right_index];
                right_index++;
            }
            k++;
        }

        // 반드시 왼쪽 아니면 오른쪽 원소들이 남아있을 수밖에 없음
        // 이 때 한쪽이 남을 경우 가정 자체가 정렬되어 있는 상태이므로 그냥 arr에 넣어주면 된다.
        if(left_index>=n1){
            for(int i=right_index; i<n2; i++){
                arr[k] = right_arr[i];
                k++;
            }
        } else if(right_index>=n2) {
            for(int i=left_index; i<n1; i++){
                arr[k] = left_arr[i];
                k++;
            }
        }
    }


}
