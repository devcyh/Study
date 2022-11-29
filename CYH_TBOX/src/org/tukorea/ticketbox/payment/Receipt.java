package org.tukorea.ticketbox.payment;

public class Receipt {
	private String client; // 사용자 이름
	private String productName; // 영화 상품 이름
	private String payMethod; // 결제 수단
	private String payNumber; // 결제 정보(번호)
	private double subTotalAmount; // 커미션 제외한 금액
	private double totalAmount; // 커미션 포함한 금액

	public Receipt(String client, String productName, String payMethod, String payNumber, double subTotalAmount,
			double totalAmount) {
		this.client = client;
		this.productName = productName;
		this.payMethod = payMethod;
		this.payNumber = payNumber;
		this.subTotalAmount = subTotalAmount;
		this.totalAmount = totalAmount;
	}

	public double getTotalAmount() {
		return totalAmount;
	}

	@Override
	public String toString() {
		System.out.println();
		System.out.println("----------------------");
		System.out.println("       Receipt        ");
		System.out.println("----------------------");
		System.out.println("[ Received by : " + client + " ]");
		System.out.println("[ Product : " + productName + " ]");
		System.out.println("[ PayMethod : " + payMethod + " ]");
		System.out.println("[ PayNumber : " + payNumber + " ]");
		System.out.println("[ SubTotal : " + subTotalAmount + " ]");
		System.out.println("[ Total : " + totalAmount + " ]");
		return super.toString();
	}

	public String toBackupString() { // 영수증 내용을 구분자(,)를 사용하여 한 줄에 출력
		return client + ", " + productName + ", " + payMethod + ", " + payNumber + ", " + subTotalAmount + ", "
				+ totalAmount;
	}
}