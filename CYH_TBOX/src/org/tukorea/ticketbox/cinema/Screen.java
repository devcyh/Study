package org.tukorea.ticketbox.cinema;

import java.util.HashMap;
import java.util.InputMismatchException;
import java.util.Scanner;

import org.tukorea.ticketbox.main.TicketBoxMain;
import org.tukorea.ticketbox.payment.*;

public abstract class Screen {
	protected int ticketPrice; // 티켓 가격
	protected int rowMax; // 좌석 행 최대 값
	protected int colMax; // 좌석 열 최대 값
	protected String movieName; // 상영중인 영화 제목
	protected String movieStory; // 상영중인 영화 줄거리
	protected MovieTicket[][] seatArray; // 좌석 2차원 배열
	private int reservedNum = 0;
	Scanner scan = TicketBoxMain.getScanner();

	Screen(String name, String story, int price, int row, int col) { // 생성자
		this.movieName = name;
		this.movieStory = story;
		this.ticketPrice = price;
		this.rowMax = row;
		this.colMax = col;
		seatArray = new MovieTicket[row][col];
		for (int i = 0; i < rowMax; i++)
			for (int j = 0; j < colMax; j++)
				seatArray[i][j] = new MovieTicket(i + 1, j + 1);
	}

	public abstract void showMovieInfo(); // 영화 정보 보여주기

	public void showScreenMenu() { // 상영관 메뉴 보여주기
		System.out.println();
		System.out.println("----------------------");
		System.out.println("영화 메뉴 - " + movieName);
		System.out.println("----------------------");
		System.out.println("1. 상영 영화 정보");
		System.out.println("2. 좌석 예약 현황");
		System.out.println("3. 좌석 예약 하기");
		System.out.println("4. 좌석 예약 취소");
		System.out.println("5. 좌석 결제 하기");
		System.out.println("6. 티켓 출력 하기");
		System.out.println("7. 메인 메뉴 이동");
	}

	public void showSeatMap() { // 상영관 좌석 예약 현황 보여주기
		System.out.println();
		System.out.print("\t[ 좌석 예약 현황 ]\n\t");
		for (int i = 0; i < colMax; i++)
			System.out.print("[" + (i + 1) + "] ");
		System.out.println();
		for (int i = 0; i < rowMax; i++) {
			System.out.print("[" + (i + 1) + "]\t");
			for (int j = 0; j < colMax; j++) {
				System.out.print("[" + seatArray[i][j].getStatus() + "] ");
			}
			System.out.println();
		}
	}

	private int createReservedId() {
		// 랜덤으로 예약 번호 발급
		// 범위 : 100부터 (총 좌석수 * 4 + 100) 까지 부여
		int randId;
		boolean flag;
		do {
			randId = (int) (Math.random() * (rowMax * colMax * 4) + 1) + 100;
			flag = false;
			for (int i = 0; i < rowMax && !flag; i++)
				for (int j = 0; j < colMax; j++)
					if (randId == seatArray[i][j].getReservedId()) {
						flag = true;
						break;
					}
		} while (flag);
		return randId;
	}

	public void reserveTicket() throws InputMismatchException { // 좌석 예약
		System.out.println();
		if (reservedNum >= rowMax * colMax) {
			System.out.println("자리가 꽉찼습니다.");
			return;
		}
		int row, col, reservedId;
		System.out.println("[ 좌석 예약 ]");
		System.out.print("좌석 행 번호 입력(1 - " + rowMax + ") : ");
		row = scan.nextInt();
		System.out.print("좌석 행 번호 입력(1 - " + colMax + ") : ");
		col = scan.nextInt();
		if (row > 0 && row <= rowMax && col > 0 && col <= colMax) {
			if (seatArray[row - 1][col - 1].getStatus() != MovieTicket.SEAT_EMPTY_MARK)
				System.out.println("예약할 수 없는 좌석입니다.");
			else {
				reservedId = createReservedId();
				seatArray[row - 1][col - 1].setReservedId(reservedId);
				seatArray[row - 1][col - 1].setStatus(MovieTicket.SEAT_RESERVED_MARK);
				;
				reservedNum++;
				System.out.println("행[" + row + "] 열[" + col + "] " + reservedId + " 예약 번호로 접수되었습니다.");
			}
		} else
			System.out.println("없는 좌석입니다. 범위 내의 값을 입력해주세요.");
	}

	private MovieTicket checkReservedId(int id) { // 예약 번호로 티켓 체크하기
		for (int i = 0; i < rowMax; i++)
			for (int j = 0; j < colMax; j++)
				if (seatArray[i][j].getReservedId() == id)
					return seatArray[i][j];
		return null;
	}

	public void cancelReservation() throws InputMismatchException { // 예약 취소
		System.out.println();
		System.out.println("[ 좌석 예약 취소 ]");
		System.out.print("좌석 예약 번호 입력 : ");
		int reservedId = scan.nextInt();
		MovieTicket seat = checkReservedId(reservedId);
		if (seat == null) {
			System.out.println("해당하는 예약을 찾을 수 없습니다.");
			return;
		}
		if (seat.getStatus() == MovieTicket.SEAT_PAY_COMPLETION_MARK) {
			System.out.println("결제 완료 좌석은 예약 취소할 수 없습니다.");
			return;
		}
		seat.setReservedId(0);
		seat.setStatus(MovieTicket.SEAT_EMPTY_MARK);
		System.out.println("예약번호 " + reservedId + " 예약 취소 처리되었습니다.");
	}

	private HashMap<Integer, Receipt> receiptMap = new HashMap<Integer, Receipt>();

	public HashMap<Integer, Receipt> getReceiptMap() {
		return receiptMap;
	}

	public void payment() throws InputMismatchException { // 결제 하기
		System.out.println();
		System.out.println("[ 좌석 예약 결제 ]");
		System.out.print("예약 번호 입력 : ");
		int reservedId = scan.nextInt();
		MovieTicket seat = checkReservedId(reservedId);
		if (seat == null) {
			System.out.println("해당하는 예약을 찾을 수 없습니다.");
			return;
		}
		if (seat.getStatus() == MovieTicket.SEAT_PAY_COMPLETION_MARK) {
			System.out.println("이미 결제가 완료되었습니다.");
			return;
		}

		System.out.println();
		System.out.println("----------------------");
		System.out.println("      결제 방식 선택      ");
		System.out.println("----------------------");
		System.out.println("1. 은행 이체");
		System.out.println("2. 카드 결제");
		System.out.println("3. 모바일 결제");
		System.out.print("결제 방식 입력(1~3) : ");
		String name;
		String number;
		Pay pay;
		switch (scan.nextInt()) {
		case 1:
			System.out.println("\n[ 은행 이체 ]");
			System.out.print("이름 입력 : ");
			name = scan.next();
			System.out.print("은행 번호 입력(8자리수) : ");
			number = scan.next();
			if (number.length() != 8)
				throw new InputMismatchException();
			pay = new BankTransfer();
			break;
		case 2:
			System.out.println("\n[ 카드 결제 ]");
			System.out.print("이름 입력 : ");
			name = scan.next();
			System.out.print("카드 번호 입력(8자리수) : ");
			number = scan.next();
			if (number.length() != 8)
				throw new InputMismatchException();
			pay = new CardPay();
			break;
		case 3:
			System.out.println("\n[ 모바일 결제 ]");
			System.out.print("이름 입력 : ");
			name = scan.next();
			System.out.print("핸드폰 번호 입력(11자리수) : ");
			number = scan.next();
			if (number.length() != 11)
				throw new InputMismatchException();
			pay = new MobliePay();
			break;
		default:
			throw new InputMismatchException();
		}
		Receipt receipt = pay.charge(movieName, ticketPrice, name, number);
		receiptMap.put(reservedId, receipt); // 키(예약 번호) + Receipt 객체
		seat.setStatus(MovieTicket.SEAT_PAY_COMPLETION_MARK);
	}

	public void printTicket() throws InputMismatchException {
		System.out.println();
		System.out.println("[ 좌석 티켓 출력 ]");
		System.out.print("예약 번호 입력 : ");
		int reservedId = scan.nextInt();
		Receipt receipt = receiptMap.get(reservedId);
		if (receipt == null) {
			System.out.println("결제 정보가 없습니다.");
			return;
		}
		receipt.toString();
	}
}