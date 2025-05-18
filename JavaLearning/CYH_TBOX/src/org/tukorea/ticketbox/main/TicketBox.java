package org.tukorea.ticketbox.main;

import java.util.InputMismatchException;
import java.util.Scanner;

import org.tukorea.ticketbox.cinema.*;
import org.tukorea.ticketbox.util.*;

public class TicketBox {
	private FamillyScreen famillyScreen;
	private AnimationScreen animationScreen;
	private PremiumScreen premiumScreen;
	Scanner scan = TicketBoxMain.getScanner();

	public void initScreen() {
		// Screen(영화제목, 영화 줄거리, 티켓가격, 좌석(rowMax), 좌석(colMax))
		famillyScreen = new FamillyScreen("돈 룩 업", "천문학과 대학원생 케이트와 담당 교수 랜들 박사는 태양계 내의", 12000, 10, 10);
		animationScreen = new AnimationScreen("명탐정 코난:할로윈의 신부", "극악무도한 폭파범 ‘플라먀’에 의해 교묘한 함정에 빠진", 20000, 10, 10);
		premiumScreen = new PremiumScreen("블랙 아담", "기원전 가장 번성하고 위대한 고대 국가였지만 현재는 국제 군사 조직", 50000, 5, 5);
	}

	public Screen selectScreen() throws InputMismatchException, Exception {
		System.out.println();
		System.out.println("----------------------");
		System.out.println("-   상영관 선택 메인메뉴   -");
		System.out.println("----------------------");
		System.out.println("1. 가족 영화 1관");
		System.out.println("2. 애니메이션 고화질 영화 2관");
		System.out.println("3. 프리미엄 고화질 영화 3관 (맥주, 피자 등 음식 제공)");
		System.out.println("9. 관리자 메뉴");
		System.out.println("   선택(1~3, 9)외 종료");
		System.out.print("상영관 선택 : ");
		int select = 0;
		try { // Exception 발생해도 무시하고 진행하도록 하기 위한 try문.
			select = scan.nextInt();
		} catch (InputMismatchException e) {
		}
		switch (select) {
		case 1:
			return famillyScreen;
		case 2:
			return animationScreen;
		case 3:
			return premiumScreen;
		case 9:
			managerMode();
			throw new Exception();
		default:
			return null;
		}
	}

	public static final String ADMIN_PASSWORD = "admin";

	void managerMode() throws InputMismatchException { // 관리자 기능
		System.out.println();
		System.out.print("암호 입력 : ");
		if (!scan.next().equals(ADMIN_PASSWORD))
			throw new InputMismatchException();
		System.out.println();
		System.out.println("----------------------");
		System.out.println("----   관리자 기능    ----");
		System.out.println("----------------------");
		int numOfSales = famillyScreen.getReceiptMap().size() + animationScreen.getReceiptMap().size()
				+ premiumScreen.getReceiptMap().size();
		System.out.println("영화관 총 티켓 판매량 : " + numOfSales);
		System.out.println("가족 영화관 결제 총액 : " + Statistics.sum(famillyScreen.getReceiptMap()));
		System.out.println("애니메이션 영화관 결제 총액 : " + Statistics.sum(animationScreen.getReceiptMap()));
		System.out.println("프리미엄 영화관 결제 총액 : " + Statistics.sum(premiumScreen.getReceiptMap()));

		ReceiptWriter receiptWriter = new ReceiptWriter();
		System.out.println();
		receiptWriter.printConsole(famillyScreen.getReceiptMap());
		receiptWriter.printConsole(animationScreen.getReceiptMap());
		receiptWriter.printConsole(premiumScreen.getReceiptMap());
	}
}