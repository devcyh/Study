import java.util.Scanner;

public class Biggest {
	static final int MAX_INPUT = 3;
	
	public static void main(String args[]) {
		int big; int temp;
		Scanner scanner = new Scanner(System.in);
		
		System.out.print("정수 " + MAX_INPUT + "개 입력>>");
		big = scanner.nextInt();
				
		for(int i = 0; i < MAX_INPUT - 1; i++) {
			temp = scanner.nextInt();
			if(big < temp)
				big = temp;
		}
		
		System.out.println(big);
		scanner.close();
	}
}