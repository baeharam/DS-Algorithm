const swap = (list, a, b) => {
  let temp = list[a];
  list[a] = list[b];
  list[b] = temp;
}

const partition = (list, left, right) => {
  let pivot = list[right];
  let candidateIdx = left - 1;
  for (let j = left; j <= right - 1; j++) {
    if (list[j] <= pivot) {
      candidateIdx++;
      swap(list, j, candidateIdx);
    }
  }
  swap(list, right, candidateIdx + 1);
  return candidateIdx + 1;
}

const quickSort = (list, left, right) => {
  if (left < right) {
    const m = partition(list, left, right);
    quickSort(list, left, m-1);
    quickSort(list, m+1, right);
  }
}