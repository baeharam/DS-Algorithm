const bubbleSort = (list) => {
  for (let i = 0; i < list.length - 1; i++) {
    for (let j = i + 1; j < list[i].length; j++) {
      if (list[j - 1] > list[j]) {
        swap(list, i, j);
      }
    }
  }
  return list;
}