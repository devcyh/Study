package org.tukorea.ticketbox.payment;

public class BankTransfer implements Pay {
	@Override
	public Receipt charge(String product, double amount, String name, String number) {
		final double BANK_TRANSFER_COMMISION = 0.1;
		double totalAmount = Math.round(amount * (1 + BANK_TRANSFER_COMMISION));
		System.out.println("은행 결제가 완료되었습니다. : " + totalAmount + "원");
		return new Receipt(name, product, "BankTransfer", number, amount, totalAmount);
	}
}