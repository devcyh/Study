package org.tukorea.ticketbox.payment;

public class MovieTicket {
	public static final char SEAT_EMPTY_MARK = '-';
	public static final char SEAT_RESERVED_MARK = 'R';
	public static final char SEAT_PAY_COMPLETION_MARK = '$';

	private int reservedId; // 예약 번호
	private int row; // 좌석 행
	private int col; // 좌석 열
	private char status; // 좌석 상태 - EMPTY, RESERVED, PAY_COMPLETION

	public MovieTicket(int row, int col) {
		this.row = row;
		this.col = col;
		this.status = SEAT_EMPTY_MARK;
		reservedId = 0;
	}

	public int getReservedId() { // 예약번호 읽기
		return reservedId;
	}

	public void setReservedId(int reservedId) { // 예약번호저장
		this.reservedId = reservedId;
	}

	/*
	 * public void setSeat(int row, int col) { // 좌석번호저장
	 * 
	 * }
	 */

	public int getRow() {
		return row;
	}

	public int getCol() {
		return col;
	}

	public char getStatus() {
		return status;
	}

	public void setStatus(char status) {
		this.status = status;
	}
}