package org.tukorea.ticketbox.payment;

public class CardPay implements Pay {
	@Override
	public Receipt charge(String product, double amount, String name, String number) {
		final double CARD_COMMISION = 0.15;
		double totalAmount = Math.round(amount * (1 + CARD_COMMISION));
		System.out.println("카드 결제가 완료되었습니다. : " + totalAmount + "원");
		return new Receipt(name, product, "CardPay", number, amount, totalAmount);
	}
}