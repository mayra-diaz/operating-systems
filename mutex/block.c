int main() {
  int lock=0;
  int return_value;
  return_value = __sync_val_compare_and_swap(&lock, 0, 1);
}