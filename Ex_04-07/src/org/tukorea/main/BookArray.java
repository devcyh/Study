package org.tukorea.main;
import java.util.Scanner;
import org.tukorea.library.Book;

public class BookArray {
	public static void main(String[] args) {
		Book [] book = new Book[2];
		Scanner scanner = new Scanner(System.in);
		
		for(int i=0; i<book.length; i++) {
			System.out.print("제목>>");
			String title = scanner.nextLine();
			System.out.print("저자>>");
			String author = scanner.nextLine();
			book[i] = new Book(title, author);
		}
		
		for(int i=0; i<book.length; i++) {
			System.out.print("(" + book[i].getTitle() + ", " + book[i].getAuthor() + ")");
		}
		
		scanner.close();
	}
}