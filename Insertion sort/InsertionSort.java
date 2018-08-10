package com.haram;

public class InsertionSort {

    public static void main(String[] args) {
        int arr[] = {5,4,9,0,1,2,3,8,11,12};

        for(int i=0; i<9; i++) {
            for(int j=i+1; j>0; j--){
                if(arr[j]<arr[j-1])
                    swap(arr, j, j-1);
            }
        }

        for(int i=0; i<10; i++) System.out.print(arr[i] + " ");
    }

    public static void swap(int arr[], int index1, int index2) {
        int temp = arr[index1];
        arr[index1] = arr[index2];
        arr[index2] = temp;
    }
}
