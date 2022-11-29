import java.util.Scanner;

public class Middle {
	static final int MAX_INPUT = 3;
	
	public static void main(String args[]) {
		int big, nextBig, temp;
		Scanner scanner = new Scanner(System.in);
		
		System.out.print("정수 " + MAX_INPUT + "개 입력>>");
		
		big = scanner.nextInt();
		nextBig = Integer.MIN_VALUE;
		for(int i = 1; i < MAX_INPUT; i++) {
			temp = scanner.nextInt();
			if(temp > nextBig)
			{
				if(temp > big) {
					nextBig = big;
					big = temp;
				}
				else {
					nextBig = temp;
				}
			}
		}
		
		System.out.println(nextBig);
		scanner.close();
	}
}