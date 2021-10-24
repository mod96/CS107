int for_loop(int n){
				int sum = 0;
				for (int i = 1; i < n; i++) {
								sum += i;
				}
				return sum * 2;
}

int main(){
				int temp = for_loop(5);
				temp += 1;
				return 1;
}

