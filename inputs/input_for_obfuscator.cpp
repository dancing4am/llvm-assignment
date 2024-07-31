int foo(int arg_1) { return 1; }

int if_else(int arg_1) {
  int num;
  num = 0;
  num++;

  if (arg_1 > 0) {
    return num;
  }
  else {
    return num - 1;
  }
}
