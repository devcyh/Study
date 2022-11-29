package org.tukorea.ticketbox.main;

import java.util.InputMismatchException;
import java.util.Scanner;

import org.tukorea.ticketbox.cinema.Screen;

public class TicketBoxMain {
	private static Scanner scan;

	public static Scanner getScanner() {
		if (scan == null)
			scan = new Scanner(System.in);
		return scan;
	}

	public static void main(String[] args) {
		TicketBox ticketBox = new TicketBox();
		Scanner scan = getScanner();
		Screen screen = null;
		boolean mainMenu = true; // 상영관 선택 메뉴 사용
		ticketBox.initScreen(); // 3개의 스크린 객체를 생성

		while (true) {
			try {
				if (mainMenu) {
					screen = ticketBox.selectScreen();
					if (screen == null) {
						System.out.print("\n안녕히 가세요 !");
						scan.close();
						System.exit(0);
					}
					mainMenu = false;
				}
				screen.showScreenMenu();
				System.out.print(" 메뉴를 선택하세요 >> ");
				int select = scan.nextInt();
				switch (select) {
				case 1: // 스크린 상영 영화 정보 보기
					screen.showMovieInfo();
					break;
				case 2:
					screen.showSeatMap();
					break;
				case 3:
					screen.reserveTicket();
					break;
				case 4:
					screen.cancelReservation();
					break;
				case 5:
					screen.payment();
					break;
				case 6:
					screen.printTicket();
					break;
				case 7:
					mainMenu = true;
					break;
				default:
					throw new InputMismatchException();
				}
			} catch (InputMismatchException e) {
				scan.nextLine();
				System.out.println("잘못된 입력입니다.");
			} catch (Exception e) { // if (screen == null) 점핑용
			}
		}
	}
}