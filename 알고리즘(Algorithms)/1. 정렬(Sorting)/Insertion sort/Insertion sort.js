function insertionSort(list) {
  for (let i = 1; i < list.length; i++) {
    const cur = list[i];
    for (let j = i - 1; j >= 0; j--) {
      if (list[j] > cur) swap(list,j,i);
    }
  }
  return list;
}