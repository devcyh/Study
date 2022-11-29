package org.tukorea.ticketbox.payment;

public class MobliePay implements Pay {
	@Override
	public Receipt charge(String product, double amount, String name, String number) {
		final double MOBILE_COMMISION = 0.2;
		double totalAmount = Math.round(amount * (1 + MOBILE_COMMISION));
		System.out.println("모바일 결제가 완료되었습니다. : " + totalAmount + "원");
		return new Receipt(name, product, "MobliePay", number, amount, totalAmount);
	}
}